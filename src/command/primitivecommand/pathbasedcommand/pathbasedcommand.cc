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

# include "pathbasedcommand.hh"

/*
 * Default constructor. Nothing to do.
 */
OpenCIF::PathBasedCommand::PathBasedCommand ( void )
   : PrimitiveCommand ()
{
   command_type = PathBased;
}

/*
 * Destructor. Nothing to do.
 */
OpenCIF::PathBasedCommand::~PathBasedCommand ( void )
{
}

/*
 * This member function returns the points stored in the command.
 */
std::vector< OpenCIF::Point > OpenCIF::PathBasedCommand::getPoints ( void ) const
{
   return ( command_points );
}

/*
 * This member function help to set the points for this command.
 */
void OpenCIF::PathBasedCommand::setPoints ( const std::vector< OpenCIF::Point >& new_points )
{
   command_points = new_points;
   
   return;
}

