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

# include "ciffsm.h"

/*
 * Default contructor. This constructor prepares the FSM to have enough
 * states (constructor of the father class). After setting such things,
 * the constructor adds enough transitions to represent a valid FSM to
 * validate the contents of a CIF file.
 * 
 * Refer to the documentation to see a visual representation of the FSM.
 */
OpenCIF::CIFFSM::CIFFSM ( void )
   : FiniteStateMachine ( 89 ) // The finite state machine designed requires such amount of states to validate the contents of the CIF file.
{
   /*
    * The process to add states will be this:
    * 
    * For every state, there will be added every transition from such state.
    * After that, there will be added a new state.
    * 
    * To this point, thanks to the constructor of the father class,
    * the FSM is ready to be configured (there is enough transitions and states).
    * 
    * By default, every "jump" (transition) not configured is an invalid transition.
    * 
    * There are defined some strings and constants to ease the process of coding the transitions.
    * For example, there is a KeyValue named "LayerNameChar", that represents a digit (0 to 9) or
    * and upper char (A to Z).
    */
   
   add ( 1 , BlankChar , 1 );
   add ( 1 , "P" , 2 );
   add ( 1 , "B" , 14 );
   add ( 1 , "R" , 31 );
   add ( 1 , "W" , 40 );
   add ( 1 , "L" , 54 );
   add ( 1 , "D" , 57 );
   add ( 1 , "C" , 70 );
   add ( 1 , Digit , 88 );
   add ( 1 , "(" , 89 );
   
   /*
    * POLYGON STATES
    */
   
   add ( 2 , BlankChar , 2 );
   add ( 2 , "-" , 3 );
   add ( 2 , Digit , 4 );
   
   add ( 3 , Digit , 4 );
   
   add ( 4 , Digit , 4 );
   add ( 4 , SeparatorChar , 5 );
   
   add ( 5 , SeparatorChar , 5 );
   add ( 5 , "-" , 6 );
   add ( 5 , Digit , 7 );
   
   add ( 6 , Digit , 7 );
   
   add ( 7 , Digit , 7 );
   add ( 7 , SeparatorChar , 8 );
   add ( 7 , ";" , 1 );
   
   add ( 8 , SeparatorChar , 8 );
   add ( 8 , "-" , 9 );
   add ( 8 , Digit , 10 );
   add ( 8 , ";" , 1 );
   
   add ( 9 , Digit , 10 );
   
   add ( 10 , Digit , 10 );
   add ( 10 , SeparatorChar , 11 );
   
   add ( 11 , SeparatorChar , 11 );
   add ( 11 , "-" , 12 );
   add ( 11 , Digit , 13 );
   
   add ( 12 , Digit , 13 );
   
   add ( 13 , SeparatorChar , 7 );
   add ( 13 , Digit , 13 );
   add ( 13 , ";" , 1 );
   
   /*
    * BOX STATES
    */
   
   add ( 14 , BlankChar , 14 );
   add ( 14 , Digit , 15 );
   
   add ( 15 , Digit , 15 );
   add ( 15 , SeparatorChar , 16 );

   add ( 16 , SeparatorChar , 16 );
   add ( 16 , Digit , 17 );
   
   add ( 17 , Digit , 17 );
   add ( 17 , SeparatorChar , 18 );
   
   add ( 18 , SeparatorChar , 18 );
   add ( 18 , "-" , 19 );
   add ( 18 , Digit , 20 );
   
   add ( 19 , Digit , 20 );
   
   add ( 20 , Digit , 20 );
   add ( 20 , SeparatorChar , 21 );
   
   add ( 21 , SeparatorChar , 21 );
   add ( 21 , "-" , 22 );
   add ( 21 , Digit , 23 );
   
   add ( 22 , Digit , 23 );
   
   add ( 23 , Digit , 23 );
   add ( 23 , SeparatorChar , 24 );
   add ( 23 , ";" , 1 );
   
   add ( 24 , SeparatorChar , 24 );
   add ( 24 , "-" , 25 );
   add ( 24 , Digit , 26 );
   add ( 24 , ";" , 1 );
   
   add ( 25 , Digit , 26 );
   
   add ( 26 , Digit , 26 );
   add ( 26 , SeparatorChar , 27 );
   
   add ( 27 , SeparatorChar , 27 );
   add ( 27 , "-" , 28 );
   add ( 27 , Digit , 29 );
   
   add ( 28 , Digit , 29 );
   
   add ( 29 , Digit , 29 );
   add ( 29 , SeparatorChar , 30 );
   add ( 29 , ";" , 1 );
   
   add ( 30 , SeparatorChar , 30 );
   add ( 30 , ";" , 1 );
   
   /*
    * ROUNDFLASH STATES
    */
}

/*
 * Destructor. Nothing to do.
 */
OpenCIF::CIFFSM::~CIFFSM ( void )
{
}

/* 
 * Member function to add a special group of transitions.
 */
void OpenCIF::CIFFSM::add ( const int& input_state , const OpenCIF::CIFFSM::Transition& input_chars , const int& output_state )
{
   switch ( input_chars )
   {
      case Digit:
         for ( int i = '0'; i <= '9'; i++ )
         {
            add ( input_state , std::string ( char ( i ) ) , output_state );
         }
         break;
         
      case UpperChar:
         for ( int i = 'A'; i <= 'Z'; i++ )
         {
            add ( input_state , std::string ( char ( i ) ) , output_state );
         }
         break;
         
      case BlankChar:
         for ( int i = 0; i < 256; i++ )
         {
            if ( !( std::isdigit ( i ) ||
                    std::isupper ( i ) ||
                    i == '-' || 
                    i == '(' ||
                    i == ')' ||
                    i == ';' ) )
            {
               add ( input_state , std::string ( char ( i ) ) , output_state );
            }
         }
         break;
         
      case UserChar:
         for ( int i = 0; i < 256; i++ )
         {
            if ( i != ';' )
            {
               add ( input_state , std::string ( char ( i ) ) , output_state );
            }
         }
         break;
         
      case CommentChar:
         for ( int i = 0; i < 256; i++ )
         {
            if ( !( i == '(' || i == '(' ) )
            {
               add ( input_state , std::string ( char ( i ) ) , output_state );
            }
         }
         break;
         
      case SeparatorChar:
         add ( input_state , UpperChar , output_state );
         add ( input_state , BlankChar , output_state );
         break;
         
      case LayerNameChar:
         add ( input_state , Digit , output_state );
         add ( input_state , UpperChar , output_state );
         break;
         
      default:
         std::cerr << "OpenCIF->CIFFSM->add: Logical error detected." << std::endl;
         std::cerr << "                      Adding a special group of input chars, detected an unknown group of values." << std::endl;
         std::cerr << "                      Such group will be skipped, but there can be errors validating files." << std::endl;
         break;
   }
   
   return;
}