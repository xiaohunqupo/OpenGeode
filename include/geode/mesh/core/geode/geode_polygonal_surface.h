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

#include <geode/basic/passkey.h>
#include <geode/basic/pimpl.h>

#include <geode/mesh/common.h>
#include <geode/mesh/core/polygonal_surface.h>

namespace geode
{
    FORWARD_DECLARATION_DIMENSION_CLASS( OpenGeodePolygonalSurfaceBuilder );
    FORWARD_DECLARATION_DIMENSION_CLASS( Point );
} // namespace geode

namespace geode
{
    template < index_t dimension >
    class OpenGeodePolygonalSurface : public PolygonalSurface< dimension >
    {
        OPENGEODE_DISABLE_COPY( OpenGeodePolygonalSurface );
        PASSKEY( OpenGeodePolygonalSurfaceBuilder< dimension >,
            OGPolygonalSurfaceKey );

    public:
        using Builder = OpenGeodePolygonalSurfaceBuilder< dimension >;
        static constexpr auto dim = dimension;

        OpenGeodePolygonalSurface();
        OpenGeodePolygonalSurface( OpenGeodePolygonalSurface&& other );
        OpenGeodePolygonalSurface& operator=(
            OpenGeodePolygonalSurface&& other );
        ~OpenGeodePolygonalSurface();

        static MeshImpl impl_name_static()
        {
            return MeshImpl{ absl::StrCat(
                "OpenGeodePolygonalSurface", dimension, "D" ) };
        }

        MeshImpl impl_name() const override
        {
            return impl_name_static();
        }

        MeshType type_name() const override
        {
            return PolygonalSurface< dimension >::type_name_static();
        }

        static absl::string_view native_extension_static()
        {
            static const auto extension =
                absl::StrCat( "og_psf", dimension, "d" );
            return extension;
        }

        absl::string_view native_extension() const override
        {
            return native_extension_static();
        }

    public:
        void set_vertex( index_t vertex_id,
            Point< dimension > point,
            OGPolygonalSurfaceKey );

        void set_polygon_vertex( const PolygonVertex& polygon_vertex,
            index_t vertex_id,
            OGPolygonalSurfaceKey );

        void set_polygon_adjacent( const PolygonEdge& polygon_edge,
            index_t adjacent_id,
            OGPolygonalSurfaceKey );

        void add_polygon(
            absl::Span< const index_t > vertices, OGPolygonalSurfaceKey );

        void remove_polygons(
            const std::vector< bool >& to_delete, OGPolygonalSurfaceKey );

        void permute_polygons(
            absl::Span< const index_t > permutation, OGPolygonalSurfaceKey );

        void copy_polygons(
            const OpenGeodePolygonalSurface< dimension >& surface_mesh,
            OGPolygonalSurfaceKey );

    private:
        friend class bitsery::Access;
        template < typename Archive >
        void serialize( Archive& archive );

        index_t get_polygon_vertex(
            const PolygonVertex& polygon_vertex ) const override;

        local_index_t get_nb_polygon_vertices(
            index_t polygon_id ) const override;

        absl::optional< index_t > get_polygon_adjacent(
            const PolygonEdge& polygon_edge ) const override;

    private:
        IMPLEMENTATION_MEMBER( impl_ );
    };
    ALIAS_2D_AND_3D( OpenGeodePolygonalSurface );
} // namespace geode
