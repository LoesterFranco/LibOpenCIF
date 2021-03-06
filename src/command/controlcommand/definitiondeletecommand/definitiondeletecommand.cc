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

# include "definitiondeletecommand.hh"

/*
 * Default constructor. Nothing to do.
 */
OpenCIF::DefinitionDeleteCommand::DefinitionDeleteCommand ( void )
   : ControlCommand ()
{
   command_type = DefinitionDelete;
}

/*
 * Non-default constructor. Initialice the command based on a string version of itself.
 */
OpenCIF::DefinitionDeleteCommand::DefinitionDeleteCommand ( const std::string& str_command ) 
   : ControlCommand ()
{
   command_type = DefinitionDelete;
   
   std::istringstream input_stream ( str_command );
   
   read ( input_stream );
}

/*
 * Default constructor.
 */
OpenCIF::DefinitionDeleteCommand::~DefinitionDeleteCommand ( void )
{
}

std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::DefinitionDeleteCommand& command )
{
   command.print ( output_stream );
   
   return ( output_stream );
}
std::istream& operator>> ( std::istream& input_stream , OpenCIF::DefinitionDeleteCommand& command )
{
   command.read ( input_stream );
   
   return ( input_stream );
}

std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::DefinitionDeleteCommand* command )
{
   command->print ( output_stream );
   
   return ( output_stream );
}
std::istream& operator>> ( std::istream& input_stream , OpenCIF::DefinitionDeleteCommand* command )
{
   command->read ( input_stream );
   
   return ( input_stream );
}

void OpenCIF::DefinitionDeleteCommand::print ( std::ostream& output_stream )
{
   output_stream << "D D " << getID () << " ;";
   
   return;
}

void OpenCIF::DefinitionDeleteCommand::read ( std::istream& input_stream )
{
   // Load the "D D " part to read, after that, the ID
   std::string word;
   unsigned long int id;
   
   input_stream >> word >> word >> id;
   
   setID ( id );
   
   return;
}
