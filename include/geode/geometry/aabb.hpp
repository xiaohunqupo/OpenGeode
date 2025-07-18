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

/*
 * Modified from RINGMesh https://github.com/ringmesh/RINGMesh
 * Copyright (c) 2012-2018, Association Scientifique pour la Geologie et ses
 * Applications (ASGA)
 */

#pragma once

#include <absl/types/span.h>

#include <geode/basic/pimpl.hpp>

#include <geode/geometry/basic_objects/infinite_line.hpp>
#include <geode/geometry/basic_objects/triangle.hpp>
#include <geode/geometry/bounding_box.hpp>
#include <geode/geometry/common.hpp>

namespace geode
{
    template < index_t dimension >
    class AABBTree
    {
        OPENGEODE_DISABLE_COPY( AABBTree );

    public:
        /*!
         * @brief AABB is a search tree for fast spatial request using the
         * bounding box organisation of elements stored in a single container.
         * @param bboxes container containing elements bounding boxes.
         * Each element can then be accessed using the index of its box in the
         * tree which should match the index in its initial container.
         */
        AABBTree();
        explicit AABBTree(
            absl::Span< const BoundingBox< dimension > > bboxes );
        AABBTree( AABBTree&& other ) noexcept;
        ~AABBTree();

        AABBTree& operator=( AABBTree&& other ) noexcept;

        /*!
         * @brief Gets the number of boxes in the lower level of the aabb tree.
         * @note This value should match the initial size of the container that
         * store all objects to organize the the aabb tree.
         */
        [[nodiscard]] index_t nb_bboxes() const;

        [[nodiscard]] const BoundingBox< dimension >& bounding_box() const;

        /*!
         * @brief Gets all the boxes containing a point
         * @param[in] query the point to test
         */
        [[nodiscard]] std::vector< index_t > containing_boxes(
            const Point< dimension >& query ) const;

        /*!
         * @brief Gets the closest element to a point
         * @param[in] query the point to test
         * @param[in] action the functor to compute the distance between
         * the \p query and the tree element in boxes
         * @return a tuple containing:
         * - the index of the closest element/box.
         * - the nearest point on the element in box.
         * - the distance between the \p query and \p nearest_point.
         *
         * @tparam EvalDistance this functor should have an operator()
         * defined like this: double operator()( const Point< dimension >&
         * query, index_t curent_element_box ) const ; the output is the
         * distance between the point \p query and the element stored in the
         * \p curent_element_box.
         *
         * @note if several elements box match the
         * distance computation, then one of them will be randomly returned.
         */
        template < typename EvalDistance >
        [[nodiscard]] std::tuple< index_t, double > closest_element_box(
            const Point< dimension >& query, const EvalDistance& action ) const;

        /*!
         * @brief Computes the intersections between a given
         * box and the all element boxes.
         * @param[in] box the box to test
         * @param[in] action The functor to run when an element box intersects
         * \p box
         *
         * @tparam EvalIntersection this functor should have an operator()
         * defined like this:
         * bool operator()( index_t cur_element_box ) ;
         * @note The returned boolean indicates if the search should stop or
         * continue. Return true to stop the search, false to continue.
         * @note the operator define what to do with the box \p cur_element_box
         * if it is intersected by the \p box.
         */
        template < class EvalIntersection >
        void compute_bbox_element_bbox_intersections(
            const BoundingBox< dimension >& box,
            EvalIntersection& action ) const;

        /*!
         * @brief Computes the self intersections of the element boxes.
         * @param[in] action The functor to run when two boxes intersect
         * @tparam EvalIntersection this functor should have an operator()
         * defined like this:
         * bool operator()( index_t cur_element_box1, index_t cur_element_box2
         * );
         * @note cur_element_box1 and cur_element_box2 are the element box
         * indices that intersect.
         * @note the operator defines what to do when two boxes of the
         * tree ( \p cur_element_box1 and \p cur_element_box2 ) intersect each
         * other (for example: test real intersection between each element in
         * boxes and store the result.)
         * @note The returned boolean indicates if the search should stop or
         * continue. Return true to stop the search, false to continue.
         */
        template < class EvalIntersection >
        void compute_self_element_bbox_intersections(
            EvalIntersection& action ) const;

        /*!
         * @brief Computes all the intersections of the element boxes between
         * this tree and another one.
         * @param[in] action The functor to run when two boxes intersect
         * @tparam EvalIntersection this functor should have an operator()
         * defined like this:
         * bool operator()( index_t cur_element_box1, index_t cur_element_box2
         * );
         * @note cur_element_box1 and cur_element_box2 are the element box
         * indices that intersect in the current tree and in the other tree.
         * @note The returned boolean indicates if the search should stop or
         * continue. Return true to stop the search, false to continue.
         */
        template < class EvalIntersection >
        void compute_other_element_bbox_intersections(
            const AABBTree< dimension >& other_tree,
            EvalIntersection& action ) const;

        /*!
         * @brief Computes the intersections between a given ray and all
         * element boxes.
         * @param[in] ray The ray to test.
         * @param[in] action The functor to run when a box is intersected by the
         * ray.
         * @tparam EvalIntersection this functor should have an operator()
         * defined like this:
         * bool operator()( index_t cur_element_box ) ;
         * @note the operator define what to do with the box \p cur_element_box
         * if it is intersected by the \p ray.
         * @note The returned boolean indicates if the search should stop or
         * continue. Return true to stop the search, false to continue.
         */
        template < class EvalIntersection >
        void compute_ray_element_bbox_intersections(
            const Ray< dimension >& ray, EvalIntersection& action ) const;

        /*!
         * @brief Computes the intersections between a given infinite line and
         * all element boxes.
         * @param[in] line The line to test.
         * @param[in] action The functor to run when a box is intersected by the
         * line.
         * @tparam EvalIntersection this functor should have an operator()
         * defined like this:
         * bool operator()( index_t cur_element_box ) ;
         * @note the operator define what to do with the box \p cur_element_box
         * if it is intersected by the \p line.
         * @note The returned boolean indicates if the search should stop or
         * continue. Return true to stop the search, false to continue.
         */
        template < class EvalIntersection >
        void compute_line_element_bbox_intersections(
            const InfiniteLine< dimension >& line,
            EvalIntersection& action ) const;

        /*!
         * @brief Computes the intersections between any object (for which
         * intersection against an arbitrary axis-aligned bounding box can be
         * detected efficiently) and all element boxes.
         * @param[in] box_filter The functor to run to determine whether a box
         * is intersected by the searched object or not. The box may correspond
         * either to an internal tree node or to a tree element.
         * @param[in] action The functor to run when a tree element box is
         * intersected by the search object.
         * @tparam EvalBox this functor should have an operator() defined like
         * this: bool operator( const BoundingBox<dimension> & ) ;
         * @tparam EvalIntersection this functor should have an operator()
         * defined like this:
         * bool operator()( index_t cur_element_box ) ;
         * @note the operator define what to do with the box \p cur_element_box
         * if it is intersected by the searched object.
         * @note The returned boolean indicates if the search should stop or
         * continue. Return true to stop the search, false to continue.
         */
        template < class EvalBox, class EvalIntersection >
        void compute_generic_element_bbox_intersections(
            const EvalBox& box_filter, EvalIntersection& action ) const;

        /*!
         * @brief Computes the intersections between a given Segment and
         * all element boxes.
         * @param[in] segment The segment to test.
         * @param[in] action The functor to run when a box is intersected by the
         * segment.
         * @tparam EvalIntersection this functor should have an operator()
         * defined like this:
         * bool operator()( index_t cur_element_box ) ;
         * @note the operator define what to do with the box \p cur_element_box
         * if it is intersected by the \p segment.
         * @note The returned boolean indicates if the search should stop or
         * continue. Return true to stop the search, false to continue.
         */
        template < class EvalIntersection >
        void compute_segment_element_bbox_intersections(
            const Segment< dimension >& segment,
            EvalIntersection& action ) const;

        /*!
         * @brief Computes the intersections between a given Triangle and
         * all element boxes.
         * @param[in] triangle The triangle to test.
         * @param[in] action The functor to run when a box is intersected by the
         * segment.
         * @tparam EvalIntersection this functor should have an operator()
         * defined like this:
         * bool operator()( index_t cur_element_box ) ;
         * @note the operator define what to do with the box \p cur_element_box
         * if it is intersected by the \p triangle.
         * @note The returned boolean indicates if the search should stop or
         * continue. Return true to stop the search, false to continue.
         */
        template < class EvalIntersection >
        void compute_triangle_element_bbox_intersections(
            const Triangle< dimension >& triangle,
            EvalIntersection& action ) const;

    private:
        IMPLEMENTATION_MEMBER( impl_ );
    };
    ALIAS_1D_AND_2D_AND_3D( AABBTree );
} // namespace geode

#include <geode/geometry/detail/aabb_impl.hpp>
