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

# include "file.h"

/*
 * Default constructor. Nothing to do.
 */
OpenCIF::File::File ( void )
{
}

/*
 * Destructor. Delete the commands stored (if any).
 */
OpenCIF::File::~File ( void )
{
   for ( int i = 0; i < file_commands.size (); i++ )
   {
      delete file_commands[ i ];
      file_commands[ i ] = 0;
   }
}

/*
 * Member function to return the commands vector.
 */
std::vector< OpenCIF::Command* > OpenCIF::File::getCommands ( void ) const
{
   return ( file_commands );
}

/*
 * Member function to return the file path.
 */
std::string OpenCIF::File::getPath ( void ) const
{
   return ( file_path );
}

/*
 * Member function to set a vector of commands.
 */
void OpenCIF::File::setCommands ( const std::vector< OpenCIF::Command* >& new_commands )
{
   file_commands = new_commands;
   
   return;
}

/*
 * Member function to set the path to the file.
 */
void OpenCIF::File::setPath ( const std::string& new_path )
{
   file_path = new_path;
   
   return;
}

/*
 * Member function to return the messages generated during the load of the file.
 */
std::vector< std::string > OpenCIF::File::getMessages ( void )
{
   return ( file_messages );
}

/*
 * Member function to load the input file. There is returned a LoadStatus
 * value that indicates the result of the process.
 */
OpenCIF::File::LoadStatus OpenCIF::File::loadFile ( void )
{
   LoadStatus end_status;
   
   file_messages.clear ();
   
   end_status = openFile ();
   
   if ( end_status != AllOk )
   {
      return ( end_status );
   }
   
   end_status = validateSintax ();
   
   if ( end_status != AllOk )
   {
      return ( end_status );
   }
   
   end_status = loadCommands ();
   
   if ( end_status != AllOk )
   {
      return ( end_status );
   }
   
   return ( AllOk );
}

/*
 * This member function try to open the input file.
 */
OpenCIF::File::LoadStatus OpenCIF::File::openFile ( void )
{
   if ( file_input.is_open () )
   {
      file_messages.push_back ( std::string ( "File:openFile:Warning: Input file already opened. Closing." ) );
      file_input.close ();
   }
   
   file_input.open ( file_path.c_str () );
   
   if ( !file_input.is_open () )
   {
      file_messages.push_back ( std::string ( "File:openFile:Error: Can't open input file." ) );
      
      return ( CantOpenInputFile );
   }
   
   return ( AllOk );
}

/*
 * This member function validates the contents of the input file using
 * a finite state machine.
 */
OpenCIF::File::LoadStatus OpenCIF::File::validateSintax ( void )
{
   /*
    * The process of validation isn't that complex.
    * 
    * I need to create a CIFFSM class instance. Such instance will help me to validate
    * the file contents. The file is already opened. So, I'll read char by char and feed
    * them to the CIFFSM instance. The CIFFSM instance will start, by default, in state 1.
    * 
    * I'll feed the instance characters until the I reach end of file or the instance reports
    * an error (jump state equal to -1). After feeding the characters, if I finish feeding the
    * file and none error was reported, I will check the current state of the instance.
    * 
    * The instance should end in state 91 or 92. If the FSM is in such states, the file is 
    * correct and the format is supported.
    * 
    * If the FSM ends in any other state, the file is not neccessarally incorrect, but incomplete.
    * 
    * If there is a jump to a negative state, the file is invalid.
    */
   
   OpenCIF::CIFFSM* fsm;
   int jump_state = 1; // By default, start in 1
   int previous_state; // Previous state.
   char input_char;
   
   fsm = new OpenCIF::CIFFSM ();
   
   // Iterate over the contents of the file, until the file end is
   // reached or the FSM reports a problem.
   
   while ( !file_input.eof () && jump_state != -1 )
   {
      input_char = file_input.get ();
      
      if ( !file_input.eof () )
      {
         previous_state = jump_state;
         jump_state = fsm->operator[] ( input_char );
      }
   }
   
   // File validated. What is the result?
   std::ostringstream oss;
   
   if ( jump_state == -1 )
   {
      // There is an invalid input.
      file_messages.push_back ( std::string ( "File:validateSintax:Error: Error detected when validating contents of input file." ) );
      oss << previous_state;
      file_messages.push_back ( std::string ( "                           State: " ) + oss.str () );
      oss.str ( std::string ( "" ) );
      oss << input_char;
      file_messages.push_back ( std::string ( "                           Input char: " ) +
                                oss.str () +
                                std::string ( " (ASCII=" ) +
                                (
                                   ( oss.str ( std::string ( "" ) ) , oss << (int)input_char ) ,
                                   oss.str ()
                                ) );
      
      return ( IncorrectInputFile );
   }
   
   if ( jump_state != 91 && jump_state != 92 )
   {
      file_messages.push_back ( std::string ( "File:validateSintax:Error: The file contents are incomplete (maybe a missing END command)." ) );
      
      return ( IncompleteInputFile );
   }
   
   return ( AllOk );
}

/*
 * This member function loads the contents of the input file and converts them
 * into Command instances.
 */
OpenCIF::File::LoadStatus OpenCIF::File::loadCommands ( void )
{
   return ( AllOk );
}
