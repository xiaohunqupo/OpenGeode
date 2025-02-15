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

#pragma once

#include <geode/basic/range.h>

#include <geode/geometry/common.h>

namespace geode
{
    FORWARD_DECLARATION_DIMENSION_CLASS( Vector );
}

namespace geode
{
    /*!
     * Description of a vector in the given dimension with double coordinates
     */
    template < index_t dimension >
    class SquareMatrix
    {
    public:
        SquareMatrix() = default;
        SquareMatrix(
            std::array< Vector< dimension >, dimension > matrix_rows );

        double value( local_index_t row, local_index_t column ) const;

        Vector< dimension > operator*( const Vector< dimension > vector ) const;

        double determinant() const;

        SquareMatrix< dimension > transpose() const;

        SquareMatrix< dimension > inverse() const;

    private:
        std::array< Vector< dimension >, dimension > matrix_rows_;
    };
    ALIAS_2D_AND_3D( SquareMatrix );
} // namespace geode
