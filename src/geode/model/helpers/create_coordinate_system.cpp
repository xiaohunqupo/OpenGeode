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

#include <geode/model/helpers/create_coordinate_system.h>

#include <geode/mesh/builder/edged_curve_builder.h>
#include <geode/mesh/builder/point_set_builder.h>
#include <geode/mesh/builder/solid_mesh_builder.h>
#include <geode/mesh/builder/surface_mesh_builder.h>
#include <geode/mesh/core/edged_curve.h>
#include <geode/mesh/core/point_set.h>
#include <geode/mesh/core/solid_mesh.h>
#include <geode/mesh/core/surface_mesh.h>
#include <geode/mesh/helpers/create_coordinate_system.h>

#include <geode/model/mixin/core/block.h>
#include <geode/model/mixin/core/corner.h>
#include <geode/model/mixin/core/line.h>
#include <geode/model/mixin/core/surface.h>
#include <geode/model/representation/builder/brep_builder.h>
#include <geode/model/representation/builder/section_builder.h>
#include <geode/model/representation/core/brep.h>
#include <geode/model/representation/core/section.h>

namespace
{
    template < typename Model >
    void create_generic_model_coordinate_system( const Model& model,
        typename Model::Builder& builder,
        absl::string_view new_coordinate_system_name,
        const geode::CoordinateSystem2D& input,
        const geode::CoordinateSystem2D& output )
    {
        for( const auto& corner : model.corners() )
        {
            const auto& mesh = corner.mesh();
            auto mesh_builder = builder.corner_mesh_builder( corner.id() );
            create_point_set_coordinate_system( mesh, *mesh_builder,
                new_coordinate_system_name, input, output );
        }
        for( const auto& line : model.lines() )
        {
            const auto& mesh = line.mesh();
            auto mesh_builder = builder.line_mesh_builder( line.id() );
            create_edged_curve_coordinate_system( mesh, *mesh_builder,
                new_coordinate_system_name, input, output );
        }
        for( const auto& surface : model.surfaces() )
        {
            const auto& mesh = surface.mesh();
            auto mesh_builder = builder.surface_mesh_builder( surface.id() );
            create_surface_mesh_coordinate_system( mesh, *mesh_builder,
                new_coordinate_system_name, input, output );
        }
    }
} // namespace

namespace geode
{
    void create_brep_coordinate_system( const BRep& model,
        BRepBuilder& builder,
        absl::string_view new_coordinate_system_name,
        const CoordinateSystem2D& input,
        const CoordinateSystem2D& output )
    {
        create_generic_model_coordinate_system(
            model, builder, new_coordinate_system_name, input, output );
        for( const auto& block : model.blocks() )
        {
            const auto& mesh = block.mesh();
            auto mesh_builder = builder.block_mesh_builder( block.id() );
            create_solid_mesh_coordinate_system( mesh, *mesh_builder,
                new_coordinate_system_name, input, output );
        }
    }

    void create_section_coordinate_system( const Section& model,
        SectionBuilder& builder,
        absl::string_view new_coordinate_system_name,
        const CoordinateSystem2D& input,
        const CoordinateSystem2D& output )
    {
        create_generic_model_coordinate_system(
            model, builder, new_coordinate_system_name, input, output );
    }

} // namespace geode