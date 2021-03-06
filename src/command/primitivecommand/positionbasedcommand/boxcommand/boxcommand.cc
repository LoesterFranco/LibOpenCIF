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

# include "boxcommand.hh"

/*
 * Default constructor. Nothing to do.
 */
OpenCIF::BoxCommand::BoxCommand ( void )
   : PositionBasedCommand ()
{
   command_type = Box;
   box_rotation.set ( 1 , 0 ); // Neutral rotation
}

/*
 * Non-default constructor. Initialize the instance using a string that contains the command itself.
 */
OpenCIF::BoxCommand::BoxCommand ( const std::string& str_command )
   : PositionBasedCommand ()
{
   command_type = Box;
   
   std::istringstream input_stream ( str_command );
   
   read ( input_stream );
}

/*
 * Destructor. Nothing to do.
 */
OpenCIF::BoxCommand::~BoxCommand ( void )
{
}

/*
 * Member function to return the rotation point.
 */
OpenCIF::Point OpenCIF::BoxCommand::getRotation ( void ) const
{
   return ( box_rotation );
}

/*
 * Member function to return the size.
 */
OpenCIF::Size OpenCIF::BoxCommand::getSize ( void ) const
{
   return ( box_size );
}

/*
 * Member function to set the rotation point.
 */
void OpenCIF::BoxCommand::setRotation ( const OpenCIF::Point& new_rotation )
{
   box_rotation = new_rotation;
   
   return;
}

/*
 * Member function to set the size.
 */
void OpenCIF::BoxCommand::setSize ( const OpenCIF::Size& new_size )
{
   box_size = new_size;
   
   return;
}

std::istream& operator>> ( std::istream& input_stream , OpenCIF::BoxCommand& command )
{
   command.read ( input_stream );
   
   return ( input_stream );
}

std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::BoxCommand& command )
{
   command.print ( output_stream );
   
   return ( output_stream );
}

std::istream& operator>> ( std::istream& input_stream , OpenCIF::BoxCommand* command )
{
   command->read ( input_stream );
   
   return ( input_stream );
}

std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::BoxCommand* command )
{
   command->print ( output_stream );
   
   return ( output_stream );
}

void OpenCIF::BoxCommand::print ( std::ostream& output_stream )
{
   output_stream << "B " << getSize () << " " << getPosition () << " " << getRotation () << " ;";
   
   return;
}

void OpenCIF::BoxCommand::read ( std::istream& input_stream )
{
   std::string word;
   OpenCIF::Point position;
   OpenCIF::Size size;
   long int x , y;
   
   
   // Read the B part, then, the size, then the position.
   input_stream >> word >> size >> position;
   
   // Check if there is a rotation
   input_stream >> word;
   
   if ( word != ";" )
   {
      std::istringstream iss ( word );
      iss >> x;
      input_stream >> y;
      
      OpenCIF::Point rotation ( x , y );
      
      setRotation ( rotation );
   }
   else
   {
      OpenCIF::Point rotation ( 1 , 0 );
      
      setRotation ( rotation );
   }
   
   setPosition ( position );
   setSize ( size );
   
   return;
}
