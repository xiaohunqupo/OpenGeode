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

#include <geode/basic/identifier_builder.h>
#include <geode/basic/mapping.h>

#include <geode/model/common.h>
#include <geode/model/mixin/builder/corners_builder.h>
#include <geode/model/mixin/builder/lines_builder.h>
#include <geode/model/mixin/builder/model_boundaries_builder.h>
#include <geode/model/mixin/builder/surfaces_builder.h>
#include <geode/model/mixin/builder/topology_builder.h>
#include <geode/model/mixin/core/corners.h>
#include <geode/model/mixin/core/lines.h>
#include <geode/model/mixin/core/model_boundaries.h>
#include <geode/model/mixin/core/surfaces.h>
#include <geode/model/mixin/core/topology.h>
#include <geode/model/representation/core/mapping.h>

namespace geode
{
    FORWARD_DECLARATION_DIMENSION_CLASS( EdgedCurve );
    FORWARD_DECLARATION_DIMENSION_CLASS( PointSet );
    FORWARD_DECLARATION_DIMENSION_CLASS( SurfaceMesh );
    ALIAS_2D( Corner );
    ALIAS_2D( EdgedCurve );
    ALIAS_2D( PointSet );
    ALIAS_2D( Line );
    ALIAS_2D( ModelBoundary );
    ALIAS_2D( Surface );
    ALIAS_2D( SurfaceMesh );
    class Section;
    struct uuid;
} // namespace geode

namespace geode
{
    /*!
     * Class managing modification of a Section
     * @extends CornersBuilder
     * @extends LinesBuilder
     * @extends SurfacesBuilder
     * @extends ModelBoundariesBuilder
     */
    class opengeode_model_api SectionBuilder : public TopologyBuilder,
                                               public CornersBuilder2D,
                                               public LinesBuilder2D,
                                               public SurfacesBuilder2D,
                                               public ModelBoundariesBuilder2D,
                                               public IdentifierBuilder
    {
        OPENGEODE_DISABLE_COPY( SectionBuilder );

    public:
        static constexpr index_t dim{ 2 };

        SectionBuilder( Section& section );
        SectionBuilder( SectionBuilder&& other ) = default;

        ModelCopyMapping copy( const Section& section );

        ModelCopyMapping copy_components( const Section& section );

        void copy_components(
            ModelCopyMapping& mapping, const Section& section );

        void copy_component_geometry(
            const ModelCopyMapping& mapping, const Section& section );

        const uuid& add_corner();

        const uuid& add_corner( const MeshImpl& impl );

        const uuid& add_line();

        const uuid& add_line( const MeshImpl& impl );

        const uuid& add_surface();

        const uuid& add_surface( const MeshImpl& impl );

        const uuid& add_model_boundary();

        void add_corner( uuid corner_id );

        void add_corner( uuid corner_id, const MeshImpl& impl );

        void add_line( uuid line_id );

        void add_line( uuid line_id, const MeshImpl& impl );

        void add_surface( uuid surface_id );

        void add_surface( uuid surface_id, const MeshImpl& impl );

        void add_model_boundary( uuid model_boundary_id );

        void update_corner_mesh(
            const Corner2D& corner, std::unique_ptr< PointSet2D > mesh );

        void update_line_mesh(
            const Line2D& line, std::unique_ptr< EdgedCurve2D > mesh );

        void update_surface_mesh(
            const Surface2D& surface, std::unique_ptr< SurfaceMesh2D > mesh );

        void remove_corner( const Corner2D& corner );

        void remove_line( const Line2D& line );

        void remove_surface( const Surface2D& surface );

        void remove_model_boundary( const ModelBoundary2D& boundary );

        void add_corner_line_boundary_relationship(
            const Corner2D& corner, const Line2D& line );

        void add_line_surface_boundary_relationship(
            const Line2D& line, const Surface2D& surface );

        void add_corner_surface_internal_relationship(
            const Corner2D& corner, const Surface2D& surface );

        void add_line_surface_internal_relationship(
            const Line2D& line, const Surface2D& surface );

        void add_line_in_model_boundary(
            const Line2D& line, const ModelBoundary2D& boundary );

    private:
        Section& section_;
    };
} // namespace geode
