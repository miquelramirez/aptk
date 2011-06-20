#include <planning/Fluent.hxx>

namespace aig_tk
{

Fluent::Fluent( STRIPS_Problem& p )
	: m_problem( p ),
	m_index( no_such_index ),
	m_signature( "(not-a-fluent)" )
{

}

Fluent::~Fluent()
{

}

}
