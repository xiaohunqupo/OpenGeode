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

#include <geode/mesh/io/triangulated_surface_input.h>

#include <geode/basic/detail/geode_input_impl.h>

#include <geode/mesh/core/mesh_factory.h>
#include <geode/mesh/core/triangulated_surface.h>

namespace geode
{
    template < index_t dimension >
    std::unique_ptr< TriangulatedSurface< dimension > >
        load_triangulated_surface(
            const MeshImpl& impl, absl::string_view filename )
    {
        try
        {
            const auto type =
                absl::StrCat( "TriangulatedSurface", dimension, "D" );
            auto triangulated_surface = detail::geode_object_input_impl<
                TriangulatedSurfaceInputFactory< dimension > >(
                type, filename, impl );
            Logger::info( type, " has: ", triangulated_surface->nb_vertices(),
                " vertices, ", triangulated_surface->nb_polygons(),
                " triangles" );
            return triangulated_surface;
        }
        catch( const OpenGeodeException& e )
        {
            Logger::error( e.what() );
            throw OpenGeodeException{
                "Cannot load TriangulatedSurface from file: ", filename
            };
        }
    }

    template < index_t dimension >
    std::unique_ptr< TriangulatedSurface< dimension > >
        load_triangulated_surface( absl::string_view filename )
    {
        return load_triangulated_surface< dimension >(
            MeshFactory::default_impl(
                TriangulatedSurface< dimension >::type_name_static() ),
            filename );
    }

    template < index_t dimension >
    typename TriangulatedSurfaceInput< dimension >::MissingFiles
        check_triangulated_surface_missing_files( absl::string_view filename )
    {
        const auto input = detail::geode_object_input_reader<
            TriangulatedSurfaceInputFactory< dimension > >( filename );
        return input->check_missing_files();
    }

    template std::unique_ptr< TriangulatedSurface< 2 > > opengeode_mesh_api
        load_triangulated_surface( const MeshImpl&, absl::string_view );
    template std::unique_ptr< TriangulatedSurface< 3 > > opengeode_mesh_api
        load_triangulated_surface( const MeshImpl&, absl::string_view );

    template std::unique_ptr< TriangulatedSurface< 2 > >
        opengeode_mesh_api load_triangulated_surface( absl::string_view );
    template std::unique_ptr< TriangulatedSurface< 3 > >
        opengeode_mesh_api load_triangulated_surface( absl::string_view );

    template TriangulatedSurfaceInput< 2 >::MissingFiles opengeode_mesh_api
        check_triangulated_surface_missing_files< 2 >( absl::string_view );
    template TriangulatedSurfaceInput< 3 >::MissingFiles opengeode_mesh_api
        check_triangulated_surface_missing_files< 3 >( absl::string_view );
} // namespace geode
