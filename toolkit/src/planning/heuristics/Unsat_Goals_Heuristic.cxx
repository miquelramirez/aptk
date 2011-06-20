#include <planning/heuristics/Unsat_Goals_Heuristic.hxx>

namespace aig_tk
{

Unsat_Goals_Heuristic::Unsat_Goals_Heuristic()
{
}

Unsat_Goals_Heuristic::~Unsat_Goals_Heuristic()
{
}

void	Unsat_Goals_Heuristic::initialize( STRIPS_Problem& p )
{
}

unsigned Unsat_Goals_Heuristic::eval( Fluent_Vec& C, Fluent_Vec& G )
{
	unsigned count = 0;

	for (unsigned i = 0; i < G.size(); i++ )
	{
		for ( unsigned k = 0; k < C.size(); k++ )
			if ( C[k] == G[i] )
			{
				count++;
				break;
			}
	}

	return G.size() - count;
}
	
}
