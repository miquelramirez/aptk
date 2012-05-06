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
	for ( unsigned k = 0; k < m_fluent_vec.size(); k++ ) 
	{
		if ( !a.retracts(m_fluent_vec[k]) ) 
		{

			//Check Conditional Effects
			if( !a.ceff_vec().empty() )
			{
				bool retracts = false;
				for( unsigned i = 0; i < a.ceff_vec().size() && !retracts; i++ )
				{
					Conditional_Effect* ce = a.ceff_vec()[i];
					if( ce->can_be_applied_on( *this ) )
						if( ce->retracts( m_fluent_vec[k] ) )
							retracts = true;
				}
				if( !retracts )
					succ->set( m_fluent_vec[k] );
			}
			else
				succ->set( m_fluent_vec[k] );
		}
	}

	
	succ->set( a.add_vec() );

	//Add Conditional Effects
	if( !a.ceff_vec().empty() )
	{		
		for( unsigned i = 0; i < a.ceff_vec().size(); i++ )
		{
			Conditional_Effect* ce = a.ceff_vec()[i];
			if( ce->can_be_applied_on( *this ) )
				succ->set( ce->add_vec() );
		}
	}

	return succ;
}

State* State::regress_through( Action& a )
{
	if ( !a.can_be_applied_on( *this, true ) )
		return NULL;

	State* succ = new State( problem() );
	for ( unsigned k = 0; k < m_fluent_vec.size(); k++ )
		if ( !a.asserts( m_fluent_vec[k] ) )
		{
			//Check Conditional Effects
			if( !a.ceff_vec().empty() )
			{
				bool asserts = false;
				for( unsigned i = 0; i < a.ceff_vec().size() && !asserts; i++ )
				{
					Conditional_Effect* ce = a.ceff_vec()[i];
					if( ce->can_be_applied_on( *this, true) )
						if( ce->asserts( m_fluent_vec[k] ) )
							asserts = true;
				}
				if( !asserts )
					succ->set( m_fluent_vec[k] );
			}
			else
				succ->set( m_fluent_vec[k] );
		}
	
	succ->set( a.prec_vec() );

	//Add Conditional Effects
	if( !a.ceff_vec().empty() )
	{		
		for( unsigned i = 0; i < a.ceff_vec().size(); i++ )
		{
			Conditional_Effect* ce = a.ceff_vec()[i];
			if( ce->can_be_applied_on( *this, true ) )
				succ->set( ce->prec_vec() );
		}
	}

	return succ;
}

}

