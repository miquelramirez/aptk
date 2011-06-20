#include <planning/PDDL_Object.hxx>

namespace aig_tk
{

PDDL_Object::PDDL_Object( STRIPS_Problem& p )
	: m_problem( p ),
	m_index( no_such_index ),
	m_signature( "(not-a-object)" )
{

}

PDDL_Object::~PDDL_Object()
{

}

}
