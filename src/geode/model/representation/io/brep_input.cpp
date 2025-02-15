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

#include <geode/model/representation/io/brep_input.h>

#include <geode/basic/detail/geode_input_impl.h>

#include <geode/model/representation/builder/brep_builder.h>
#include <geode/model/representation/core/brep.h>

namespace geode
{
    BRep load_brep( absl::string_view filename )
    {
        try
        {
            const auto type = "BRep";
            auto brep = detail::geode_object_input_impl< BRepInputFactory >(
                type, filename );
            auto message = absl::StrCat( type, " has: " );
            detail::add_to_message( message, brep.nb_blocks(), " Blocks, " );
            detail::add_to_message(
                message, brep.nb_surfaces(), " Surfaces, " );
            detail::add_to_message( message, brep.nb_lines(), " Lines, " );
            detail::add_to_message( message, brep.nb_corners(), " Corners, " );
            detail::add_to_message(
                message, brep.nb_model_boundaries(), " ModelBoundaries" );
            Logger::info( message );
            return brep;
        }
        catch( const OpenGeodeException& e )
        {
            Logger::error( e.what() );
            throw OpenGeodeException{ "Cannot load BRep from file: ",
                filename };
        }
    }

    typename BRepInput::MissingFiles check_brep_missing_files(
        absl::string_view filename )
    {
        const auto input =
            detail::geode_object_input_reader< BRepInputFactory >( filename );
        return input->check_missing_files();
    }
} // namespace geode
