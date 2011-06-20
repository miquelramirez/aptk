#include <planning/PDDL_Operator.hxx>

namespace aig_tk
{

PDDL_Operator::PDDL_Operator( STRIPS_Problem& p )
	: m_problem( p ),
	m_index( no_such_index ),
	m_signature( "(not-a-pddl-operator)" )
{

}

PDDL_Operator::~PDDL_Operator()
{

}

}
