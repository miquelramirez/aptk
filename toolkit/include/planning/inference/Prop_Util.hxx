/*
    Miguel Ramirez, Nir Lipovetzky, Hector Geffner
    C^3: A planner for the sequential, satisficing track of the IPC-6
    Copyright (C) 2008  

    Modified by: Nir Lipovetzky
    PROBE: A planner for the sequential, satisficing track of the IPC-7
    Copyright (C) 2011    
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef __PROP_UTILS__
#define __PROP_UTILS__

#include <vector>
#include <queue>
#include <planning/Types.hxx>
#include <planning/Action.hxx>
#include <planning/Fluent.hxx>

namespace aig_tk
{

/**
 * Node type in the relax planning graph
 */

enum Propagator_Node_Type
{
	FLUENT = 0,
	ACTION,
	NONE
};

/**
 * Node in the relax planning graph
 */
class Propagator_Node
{
public:

        Propagator_Node() : Type( NONE ), Atom( NULL ), Operator( NULL ){};
	~Propagator_Node(){};

	Propagator_Node_Type		Type; // Node type
	Fluent*				Atom;
	Action*				Operator;
        
        /**
         * Indexes of the graph in Propagator.hxx
         */
	Index_Vec			Parents;
	Index_Vec			Children;	
};

typedef std::vector<Propagator_Node*>	Propagation_Graph;


}

#endif // prop_utils.hxx
