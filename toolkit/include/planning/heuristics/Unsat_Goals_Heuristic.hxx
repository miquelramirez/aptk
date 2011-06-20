#ifndef __UNSAT_GOALS_HEURISTIC__
#define __UNSAT_GOALS_HEURISTIC__

#include <planning/STRIPS_Problem.hxx>
#include <planning/Types.hxx>

namespace aig_tk
{

class Unsat_Goals_Heuristic
{
public:

	Unsat_Goals_Heuristic();
	~Unsat_Goals_Heuristic();

	void		initialize( STRIPS_Problem& p );
	unsigned 	eval( Fluent_Vec& C, Fluent_Vec& G );

protected:

};


}

#endif // Unsat_Goals_Heuristic.hxx
