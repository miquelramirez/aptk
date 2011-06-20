#ifndef __MAX_HEURISTIC__
#define __MAX_HEURSITIC__

#include <planning/STRIPS_Problem.hxx>
#include <planning/Types.hxx>
#include <planning/Action.hxx>
#include <planning/heuristics/Heuristic.hxx>

namespace aig_tk
{

class Max_Heuristic : public Heuristic
{
public:
	

	void    	compute( Fluent_Vec& C );
	Cost_Type	eval( Fluent_Vec& G );
        
};


inline Cost_Type Max_Heuristic::eval( Fluent_Vec& C )
{
	// 3. Evaluate heuristic values for C
	Cost_Type h = 0;	

	for ( unsigned k = 0; k < C.size(); k++ )
		h = std::max( h, fl_value( C[k] ) );

	return h;
}

}

#endif // Max_Heuristic.hxx
