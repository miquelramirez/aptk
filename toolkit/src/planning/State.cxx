#include <planning/State.hxx>
#include <planning/Action.hxx>
#include <planning/Fluent.hxx>
#include <util/memory.hxx>

namespace aig_tk
{

State::State( STRIPS_Problem& problem )
	: m_fluent_set( problem.num_fluents() ), m_problem( problem )
{
}

State::~State()
{
}

State* State::progress_through( Action& a )
{
	if ( !a.can_be_applied_on(*this) )
		return NULL;
	State* succ = new State( problem() );
	for ( unsigned k = 0; k < m_fluent_vec.size(); k++ ) {
	  if ( !a.retracts(m_fluent_vec[k]) ) {
	    succ->set( m_fluent_vec[k] );
	  }
	}
	succ->set( a.add_vec() );	

	return succ;
}

State* State::regress_through( Action& a )
{
	if ( !a.can_be_applied_on( *this, true ) )
		return NULL;

	State* succ = new State( problem() );
	for ( unsigned k = 0; k < m_fluent_vec.size(); k++ )
		if ( !a.asserts( m_fluent_vec[k] ) )
			succ->set( m_fluent_vec[k] );
	succ->set( a.prec_vec() );

	return succ;
}

}

