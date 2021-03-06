/*
 * LibOpenCIF, a library to read the contents of a CIF (Caltech Intermediate
 * Form) file. The library also includes a finite state machine to validate
 * the contents, acording to the specifications found in the technical
 * report 2686, from february 11, 1980.
 * 
 * Copyright (C) 2014, Moises Chavez Martinez
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */  

# ifndef LIBOPENCIF_BOXCOMMAND_HH_
# define LIBOPENCIF_BOXCOMMAND_HH_

# include <iostream>
# include <string>
# include <sstream>

# include "../positionbasedcommand.hh"
# include "../../../point/point.hh"
# include "../../../size/size.hh"

namespace OpenCIF { class BoxCommand; }
std::istream& operator>> ( std::istream& input_stream , OpenCIF::BoxCommand& command );
std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::BoxCommand& command );
std::istream& operator>> ( std::istream& input_stream , OpenCIF::BoxCommand* command );
std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::BoxCommand* command );

namespace OpenCIF
{
   class BoxCommand : public OpenCIF::PositionBasedCommand
   {
      public:
         explicit BoxCommand ( void );
         explicit BoxCommand ( const std::string& str_command );
         virtual ~BoxCommand ( void );
         void setRotation ( const OpenCIF::Point& new_rotation );
         void setSize ( const OpenCIF::Size& new_size );
         OpenCIF::Size getSize ( void ) const;
         OpenCIF::Point getRotation ( void ) const;
         
         friend std::istream& (::operator>>) ( std::istream& input_stream , BoxCommand& command );
         friend std::ostream& (::operator<<) ( std::ostream& output_stream , BoxCommand& command );
         friend std::istream& (::operator>>) ( std::istream& input_stream , BoxCommand* command );
         friend std::ostream& (::operator<<) ( std::ostream& output_stream , BoxCommand* command );
         
      protected:
         virtual void print ( std::ostream& output_stream );
         virtual void read ( std::istream& input_stream );
         
      protected:
         OpenCIF::Size box_size;
         OpenCIF::Point box_rotation;
   };
}

# endif
