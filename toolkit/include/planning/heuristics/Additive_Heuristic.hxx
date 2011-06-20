#ifndef __ADDITIVE_HEURISTIC__
#define __ADDITIVE_HEURISTIC__

#include <planning/STRIPS_Problem.hxx>
#include <planning/Types.hxx>

namespace aig_tk
{

class Additive_Heuristic
{
public:

	Additive_Heuristic();
	~Additive_Heuristic();

	void 		initialize( STRIPS_Problem& p );
	unsigned	eval( Fluent_Vec& C, Fluent_Vec& G );

	unsigned	fl_value( unsigned p ) const { return m_fluent_values[p]; }
	void		set_fl_value( unsigned p, unsigned v ) { m_fluent_values[p] = v; }
	Action*		best_supporter( unsigned p ) 			{ return m_best_supporter[p]; }
	void		set_best_supporter( unsigned p, Action* a )	{ m_best_supporter[p] = a; }
	Action_Ptr_Vec&	best_supporters( unsigned p ) 			{ return m_best_supporters[p]; }

protected:

	Value_Vec&	fl_values() { return m_fluent_values; }
	void		set_problem( STRIPS_Problem& p ) { m_problem = &p; }
	STRIPS_Problem& problem() { return *m_problem; }

protected:

	Value_Vec		m_fluent_values;
	STRIPS_Problem*		m_problem;
	Action_Ptr_Vec		m_best_supporter;
	Fluent_Action_Table	m_best_supporters;
};

}

#endif // Additive_Heuristic.hxx

