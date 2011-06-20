#ifndef __MAX_PAIR_HEURISTIC__
#define __MAX_PAIR_HEURSITIC__

#include <planning/STRIPS_Problem.hxx>
#include <planning/Types.hxx>

namespace aig_tk
{

class Max_Pair_Heuristic
{
public:

	Max_Pair_Heuristic();
	~Max_Pair_Heuristic();

	void 		initialize( STRIPS_Problem& p );
	unsigned	eval( Fluent_Vec& C, Fluent_Vec& G );

protected:

	Pair_Value_Table&	fl_values() { return m_fluent_values; }
	void			set_problem( STRIPS_Problem& p ) { m_problem = &p; }
	STRIPS_Problem& 	problem() { return *m_problem; }

protected:

	Pair_Value_Table	m_fluent_values;
	STRIPS_Problem*		m_problem;
};

}

#endif // Max_Pair_Heuristic.hxx
