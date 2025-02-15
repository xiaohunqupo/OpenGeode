/*
 * Copyright (c) 2019 - 2023 Geode-solutions
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include <geode/basic/progress_logger.h>

#include <mutex>

#include <absl/time/clock.h>

#include <geode/basic/logger.h>
#include <geode/basic/pimpl_impl.h>
#include <geode/basic/progress_logger_manager.h>
#include <geode/basic/uuid.h>

namespace
{
    constexpr absl::Duration SLEEP = absl::Seconds( 1 );
} // namespace

namespace geode
{
    class ProgressLogger::Impl
    {
    public:
        Impl( const std::string& message, index_t nb_steps )
            : nb_steps_( nb_steps ), current_time_{ absl::Now() }
        {
            ProgressLoggerManager::start( id_, message, nb_steps_ );
        }

        ~Impl()
        {
            if( current_ == nb_steps_ )
            {
                ProgressLoggerManager::completed( id_ );
            }
            else
            {
                ProgressLoggerManager::failed( id_ );
            }
        }

        index_t increment( index_t nb_increments )
        {
            const std::lock_guard< std::mutex > locking{ lock_ };
            current_ += nb_increments;
            auto now = absl::Now();
            if( now - current_time_ > SLEEP )
            {
                current_time_ = now;
                ProgressLoggerManager::update( id_, current_, nb_steps_ );
            }
            return current_;
        }

        index_t increment_nb_steps( index_t nb_steps )
        {
            const std::lock_guard< std::mutex > locking{ lock_ };
            nb_steps_ += nb_steps;
            return nb_steps_;
        }

    private:
        uuid id_;
        index_t nb_steps_;
        index_t current_{ 0 };
        absl::Time current_time_;
        std::mutex lock_;
    };

    ProgressLogger::ProgressLogger(
        const std::string& message, index_t nb_steps )
        : impl_( message, nb_steps )
    {
    }

    ProgressLogger::~ProgressLogger() {} // NOLINT

    index_t ProgressLogger::increment()
    {
        return impl_->increment( 1 );
    }

    index_t ProgressLogger::increment( index_t nb_increments )
    {
        return impl_->increment( nb_increments );
    }

    index_t ProgressLogger::increment_nb_steps()
    {
        return impl_->increment_nb_steps( 1 );
    }

    index_t ProgressLogger::increment_nb_steps( index_t nb_steps )
    {
        return impl_->increment_nb_steps( nb_steps );
    }
} // namespace geode
