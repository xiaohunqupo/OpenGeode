# Copyright (c) 2019 - 2025 Geode-solutions
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

add_geode_library(
    NAME model
    FOLDER "geode/model"
    SOURCES
        "common.cpp"
        "helpers/aabb_model_helpers.cpp"
        "helpers/component_mesh_edges.cpp"
        "helpers/component_mesh_polygons.cpp"
        "helpers/component_mesh_polyhedra.cpp"
        "helpers/component_mesh_vertices.cpp"
        "helpers/component_mensurations.cpp"
        "helpers/convert_brep_section.cpp"
        "helpers/convert_model_meshes.cpp"
        "helpers/convert_to_mesh.cpp"
        "helpers/create_coordinate_system.cpp"
        "helpers/model_component_filter.cpp"
        "helpers/model_concatener.cpp"
        "helpers/model_coordinate_reference_system.cpp"
        "helpers/simplicial_brep_creator.cpp"
        "helpers/simplicial_section_creator.cpp"
        "helpers/surface_radial_sort.cpp"
        "helpers/ray_tracing.cpp"
        "helpers/detail/build_model_boundaries.cpp"
        "helpers/detail/mappings_merger.cpp"
        "helpers/detail/solid_mesh_validity_fix.cpp"
        "helpers/detail/split_along_surface_mesh_borders.cpp"
        "helpers/detail/split_along_block_mesh_borders.cpp"
        "helpers/detail/surface_mesh_validity_fix.cpp"
        "mixin/builder/blocks_builder.cpp"
        "mixin/builder/block_collections_builder.cpp"
        "mixin/builder/component_registry_builder.cpp"
        "mixin/builder/corners_builder.cpp"
        "mixin/builder/corner_collections_builder.cpp"
        "mixin/builder/lines_builder.cpp"
        "mixin/builder/line_collections_builder.cpp"
        "mixin/builder/model_boundaries_builder.cpp"
        "mixin/builder/surfaces_builder.cpp"
        "mixin/builder/surface_collections_builder.cpp"
        "mixin/builder/relationships_builder.cpp"
        "mixin/builder/vertex_identifier_builder.cpp"
        "mixin/core/detail/relationships_impl.cpp"
        "mixin/core/bitsery_archive.cpp"
        "mixin/core/block.cpp"
        "mixin/core/blocks.cpp"
        "mixin/core/block_collections.cpp"
        "mixin/core/block_collection.cpp"
        "mixin/core/component.cpp"
        "mixin/core/component_mesh_element.cpp"
        "mixin/core/component_registry.cpp"
        "mixin/core/component_type.cpp"
        "mixin/core/corner.cpp"
        "mixin/core/corners.cpp"
        "mixin/core/corner_collections.cpp"
        "mixin/core/corner_collection.cpp"
        "mixin/core/line.cpp"
        "mixin/core/lines.cpp"
        "mixin/core/line_collections.cpp"
        "mixin/core/line_collection.cpp"
        "mixin/core/model_boundaries.cpp"
        "mixin/core/model_boundary.cpp"
        "mixin/core/relationships.cpp"
        "mixin/core/surface.cpp"
        "mixin/core/surfaces.cpp"
        "mixin/core/surface_collections.cpp"
        "mixin/core/surface_collection.cpp"
        "mixin/core/vertex_identifier.cpp"
        "representation/builder/brep_builder.cpp"
        "representation/builder/section_builder.cpp"
        "representation/core/detail/clone.cpp"
        "representation/core/detail/transfer_collections.cpp"
        "representation/core/detail/transfer_metadata.cpp"
        "representation/core/brep.cpp"
        "representation/core/section.cpp"
        "representation/io/brep_input.cpp"
        "representation/io/section_input.cpp"
        "representation/io/brep_output.cpp"
        "representation/io/section_output.cpp"
        "representation/io/geode/geode_brep_input.cpp"
        "representation/io/geode/geode_brep_output.cpp"
        "representation/io/geode/geode_section_input.cpp"
        "representation/io/geode/geode_section_output.cpp"
    PUBLIC_HEADERS
        "common.hpp"
        "helpers/aabb_model_helpers.hpp"
        "helpers/component_mesh_edges.hpp"
        "helpers/component_mesh_polygons.hpp"
        "helpers/component_mesh_polyhedra.hpp"
        "helpers/component_mesh_vertices.hpp"
        "helpers/component_mensurations.hpp"
        "helpers/convert_brep_section.hpp"
        "helpers/convert_model_meshes.hpp"
        "helpers/convert_to_mesh.hpp"
        "helpers/create_coordinate_system.hpp"
        "helpers/model_component_filter.hpp"
        "helpers/model_concatener.hpp"
        "helpers/model_coordinate_reference_system.hpp"
        "helpers/simplicial_brep_creator.hpp"
        "helpers/simplicial_creator_definitions.hpp"
        "helpers/simplicial_section_creator.hpp"
        "helpers/surface_radial_sort.hpp"
        "helpers/ray_tracing.hpp"
        "mixin/builder/blocks_builder.hpp"
        "mixin/builder/block_collections_builder.hpp"
        "mixin/builder/component_registry_builder.hpp"
        "mixin/builder/corners_builder.hpp"
        "mixin/builder/corner_collections_builder.hpp"
        "mixin/builder/lines_builder.hpp"
        "mixin/builder/line_collections_builder.hpp"
        "mixin/builder/model_boundaries_builder.hpp"
        "mixin/builder/surfaces_builder.hpp"
        "mixin/builder/surface_collections_builder.hpp"
        "mixin/builder/relationships_builder.hpp"
        "mixin/builder/topology_builder.hpp"
        "mixin/builder/vertex_identifier_builder.hpp"
        "mixin/core/bitsery_archive.hpp"
        "mixin/core/block.hpp"
        "mixin/core/blocks.hpp"
        "mixin/core/block_collections.hpp"
        "mixin/core/block_collection.hpp"
        "mixin/core/component.hpp"
        "mixin/core/component_mesh_element.hpp"
        "mixin/core/component_registry.hpp"
        "mixin/core/component_type.hpp"
        "mixin/core/corner.hpp"
        "mixin/core/corners.hpp"
        "mixin/core/corner_collections.hpp"
        "mixin/core/corner_collection.hpp"
        "mixin/core/line.hpp"
        "mixin/core/lines.hpp"
        "mixin/core/line_collections.hpp"
        "mixin/core/line_collection.hpp"
        "mixin/core/model_boundary.hpp"
        "mixin/core/model_boundaries.hpp"
        "mixin/core/relationships.hpp"
        "mixin/core/surface.hpp"
        "mixin/core/surfaces.hpp"
        "mixin/core/surface_collections.hpp"
        "mixin/core/surface_collection.hpp"
        "mixin/core/topology.hpp"
        "mixin/core/vertex_identifier.hpp"
        "representation/builder/brep_builder.hpp"
        "representation/builder/section_builder.hpp"
        "representation/core/brep.hpp"
        "representation/core/section.hpp"
        "representation/core/mapping.hpp"
        "representation/io/brep_input.hpp"
        "representation/io/section_input.hpp"
        "representation/io/brep_output.hpp"
        "representation/io/section_output.hpp"
        "representation/io/geode/geode_brep_input.hpp"
        "representation/io/geode/geode_section_input.hpp"
        "representation/io/geode/geode_brep_output.hpp"
        "representation/io/geode/geode_section_output.hpp"
    ADVANCED_HEADERS
        "helpers/detail/build_model_boundaries.hpp"
        "helpers/detail/mappings_merger.hpp"
        "helpers/detail/solid_mesh_validity_fix.hpp"
        "helpers/detail/split_along_surface_mesh_borders.hpp"
        "helpers/detail/split_along_block_mesh_borders.hpp"
        "helpers/detail/surface_mesh_validity_fix.hpp"
        "mixin/core/detail/components_storage.hpp"
        "mixin/core/detail/mesh_storage.hpp"
        "mixin/core/detail/uuid_to_index.hpp"
        "mixin/core/detail/relationships_impl.hpp"
        "representation/builder/detail/copy.hpp"
        "representation/builder/detail/filter.hpp"
        "representation/builder/detail/register.hpp"
        "representation/core/detail/clone.hpp"
        "representation/core/detail/transfer_collections.hpp"
        "representation/core/detail/transfer_metadata.hpp"
    INTERNAL_HEADERS
        "helpers/internal/simplicial_model_creator.hpp"
    PUBLIC_DEPENDENCIES
        absl::flat_hash_map
        Bitsery::bitsery
        ${PROJECT_NAME}::basic
        ${PROJECT_NAME}::geometry
        ${PROJECT_NAME}::mesh
    PRIVATE_DEPENDENCIES
        Async++
)

