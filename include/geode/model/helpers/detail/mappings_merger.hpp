/*
 * Copyright (c) 2019 - 2025 Geode-solutions
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

#include <geode/model/common.hpp>
#include <geode/model/representation/core/mapping.hpp>

namespace geode
{
    namespace detail
    {
        [[nodiscard]] ModelGenericMapping opengeode_model_api merge_mappings(
            const ModelGenericMapping& mappings1,
            const ModelCopyMapping& mappings2 );

        [[nodiscard]] ModelGenericMapping opengeode_model_api merge_mappings(
            const ModelGenericMapping& mappings1,
            const ModelGenericMapping& mappings2 );

        [[nodiscard]] ModelGenericMapping opengeode_model_api
            copy_to_generic_mappings( const ModelCopyMapping& mappings2 );

        [[nodiscard]] SectionMappings opengeode_model_api merge_mappings(
            const SectionMappings& mappings1,
            const SectionMappings& mappings2 );

        [[nodiscard]] BRepMappings opengeode_model_api merge_mappings(
            const BRepMappings& mappings1, const BRepMappings& mappings2 );
    } // namespace detail
} // namespace geode
