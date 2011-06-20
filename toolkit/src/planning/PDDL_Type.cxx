#include <planning/PDDL_Type.hxx>

namespace aig_tk
{

PDDL_Type::PDDL_Type( STRIPS_Problem& p )
	: m_problem( p ),
	m_index( no_such_index ),
	m_signature( "(not-a-type)" )
{

}

PDDL_Type::~PDDL_Type()
{

}

}
