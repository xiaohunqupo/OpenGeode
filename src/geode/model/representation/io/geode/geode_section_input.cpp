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

#include <geode/model/representation/io/geode/geode_section_input.h>

#include <async++.h>

#include <geode/basic/uuid.h>
#include <geode/basic/zip_file.h>

#include <geode/model/mixin/core/corner.h>
#include <geode/model/mixin/core/line.h>
#include <geode/model/mixin/core/model_boundary.h>
#include <geode/model/mixin/core/surface.h>
#include <geode/model/representation/builder/detail/filter.h>
#include <geode/model/representation/builder/section_builder.h>
#include <geode/model/representation/core/section.h>

namespace geode
{
    void OpenGeodeSectionInput::load_section_files(
        Section& section, absl::string_view directory )
    {
        SectionBuilder builder{ section };
        async::parallel_invoke(
            [&builder, &directory] {
                builder.load_identifier( directory );
            },
            [&builder, &directory] {
                builder.load_corners( directory );
                builder.load_lines( directory );
                builder.load_surfaces( directory );
            },
            [&builder, &directory] {
                builder.load_model_boundaries( directory );
            },
            [&builder, &directory] {
                builder.load_relationships( directory );
            },
            [&builder, &directory] {
                builder.load_unique_vertices( directory );
            } );
        for( const auto& corner : section.corners() )
        {
            builder.register_mesh_component( corner );
        }
        for( const auto& line : section.lines() )
        {
            builder.register_mesh_component( line );
        }
        for( const auto& surface : section.surfaces() )
        {
            builder.register_mesh_component( surface );
        }
    }

    Section OpenGeodeSectionInput::read()
    {
        const UnzipFile zip_reader{ filename(), uuid{}.string() };
        zip_reader.extract_all();
        Section section;
        load_section_files( section, zip_reader.directory() );
        detail::filter_unsupported_components( section );
        return section;
    }
} // namespace geode
