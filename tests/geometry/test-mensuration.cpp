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

#include <geode/basic/assert.h>
#include <geode/basic/logger.h>

#include <geode/geometry/point.h>

#include <geode/geometry/basic_objects/tetrahedron.h>
#include <geode/geometry/basic_objects/triangle.h>
#include <geode/geometry/mensuration.h>

#include <geode/tests/common.h>

void test_triangle_area_2d()
{
    const geode::Point2D a{ { 0.0, 0.0 } };
    const geode::Point2D b{ { 1.0, 0.0 } };
    const geode::Point2D c{ { 1.0, 1.0 } };

    const geode::Triangle2D triangle2D_1{ a, b, c };
    const auto area1 = geode::triangle_area( triangle2D_1 );
    OPENGEODE_EXCEPTION( std::fabs( area1 - 0.5 ) < geode::global_epsilon,
        "[Test] Wrong result for triangle_area "
        "with query triangle triangle2D_1" );

    const geode::Triangle2D triangle2D_2{ a, b, a };
    const auto area2 = geode::triangle_area( triangle2D_2 );
    OPENGEODE_EXCEPTION( std::fabs( area2 ) < geode::global_epsilon,
        "[Test] Wrong result for triangle_area "
        "with query triangle triangle2D_2" );
}

void test_triangle_area_3d()
{
    const geode::Point3D a{ { 0.0, 0., 0.0 } };
    const geode::Point3D b{ { 1.0, 0.0, 0.0 } };
    const geode::Point3D c{ { 1.0, 1.0, 0.0 } };

    const geode::Triangle3D triangle3D_1{ a, b, c };
    const auto area1 = geode::triangle_area( triangle3D_1 );
    OPENGEODE_EXCEPTION( std::fabs( area1 - 0.5 ) < geode::global_epsilon,
        "[Test] Wrong result for triangle_area "
        "with query triangle triangle3D_1" );

    const geode::Triangle3D triangle3D_2{ a, b, a };
    const auto area2 = geode::triangle_area( triangle3D_2 );
    OPENGEODE_EXCEPTION( std::fabs( area2 ) < geode::global_epsilon,
        "[Test] Wrong result for triangle_area "
        "with query triangle triangle3D_2" );

    const geode::Point3D d{ { 1, 1, -0.300000011920929 } };
    const geode::Point3D e{ { 0, 0, -0.300000011920929 } };
    const geode::Point3D f{ { 0.555555555555556, 0.555555555555555,
        -0.300000011920929 } };
    const geode::Triangle3D triangle3D_3{ d, e, f };
    const auto area3 = geode::triangle_area( triangle3D_3 );
    OPENGEODE_EXCEPTION( std::fabs( area3 ) < geode::global_epsilon,
        "[Test] Wrong result for triangle_area "
        "with query triangle triangle3D_3" );
}

void test_triangle_area()
{
    test_triangle_area_2d();
    test_triangle_area_3d();
}

void test_triangle_signed_area_2d()
{
    const geode::Point2D a{ { 0.0, 0.0 } };
    const geode::Point2D b{ { 1.0, 0.0 } };
    const geode::Point2D c{ { 1.0, 1.0 } };

    const geode::Triangle2D triangle2D_1{ a, b, c };
    const auto area1 = geode::triangle_signed_area( triangle2D_1 );
    OPENGEODE_EXCEPTION( std::fabs( area1 - 0.5 ) < geode::global_epsilon,
        "[Test] Wrong result for triangle_signed_area "
        "with query triangle triangle2D_1 : result: ",
        area1, " | expected: 0.5" );

    const geode::Triangle2D triangle2D_2{ a, c, b };
    const auto area2 = geode::triangle_signed_area( triangle2D_2 );
    OPENGEODE_EXCEPTION( std::fabs( area2 + 0.5 ) < geode::global_epsilon,
        "[Test] Wrong result for triangle_signed_area "
        "with query triangle triangle2D_2" );

    const geode::Triangle2D triangle2D_3{ a, b, a };
    const auto area3 = geode::triangle_signed_area( triangle2D_3 );
    OPENGEODE_EXCEPTION( std::fabs( area3 ) < geode::global_epsilon,
        "[Test] Wrong result for triangle_signed_area "
        "with query triangle triangle2D_3" );
}

void test_triangle_signed_area_3d()
{
    const geode::Point3D a{ { 0.0, 0.0, 0.0 } };
    const geode::Point3D b{ { 1.0, 0.0, 0.0 } };
    const geode::Point3D c{ { 1.0, 1.0, 0.0 } };
    const geode::Vector3D upward{ { { 0.0, 0.0, 0.0 } },
        { { 0.0, 0.0, 1.0 } } };

    const geode::Triangle3D triangle3D_1{ a, b, c };
    const auto area1 = geode::triangle_signed_area( triangle3D_1, upward );
    OPENGEODE_EXCEPTION( std::fabs( area1 - 0.5 ) < geode::global_epsilon,
        "[Test] Wrong result for triangle_signed_area "
        "with query triangle triangle3D_1" );

    const geode::Triangle3D triangle3D_2{ a, c, b };
    const auto area2 = geode::triangle_signed_area( triangle3D_2, upward );
    OPENGEODE_EXCEPTION( std::fabs( area2 + 0.5 ) < geode::global_epsilon,
        "[Test] Wrong result for triangle_signed_area "
        "with query triangle triangle3D_2" );

    const geode::Triangle3D triangle3D_3{ a, b, a };
    const auto area3 = geode::triangle_signed_area( triangle3D_3, upward );
    OPENGEODE_EXCEPTION( std::fabs( area3 ) < geode::global_epsilon,
        "[Test] Wrong result for triangle_signed_area "
        "with query triangle triangle3D_3" );
}

void test_triangle_signed_area()
{
    test_triangle_signed_area_2d();
    test_triangle_signed_area_3d();
}

void test_tetrahedron_signed_area()
{
    const geode::Point3D a{ { 0.0, 0.0, 0.0 } };
    const geode::Point3D b{ { 1.0, 0.0, 0.0 } };
    const geode::Point3D c{ { 0.0, 1.0, 0.0 } };
    const geode::Point3D d{ { 0.0, 0.0, 1.0 } };

    const geode::Tetrahedron tetra1{ a, b, c, d };
    const auto volume1 = geode::tetrahedron_signed_volume( tetra1 );
    OPENGEODE_EXCEPTION( std::fabs( volume1 - 1. / 6. ) < geode::global_epsilon,
        "[Test] Wrong result for tetrahedron_signed_volume "
        "with query tetra tetra1" );

    const geode::Tetrahedron tetra2{ a, b, d, c };
    const auto volume2 = geode::tetrahedron_signed_volume( tetra2 );
    OPENGEODE_EXCEPTION( std::fabs( volume2 + 1. / 6. ) < geode::global_epsilon,
        "[Test] Wrong result for tetrahedron_signed_volume "
        "with query tetra tetra2" );
}

void test()
{
    test_triangle_area();
    test_triangle_signed_area();
    test_tetrahedron_signed_area();
}

OPENGEODE_TEST( "signed-mensuration" )
