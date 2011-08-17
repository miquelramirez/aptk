#include <planning/Plan.hxx>
#include <planning/STRIPS_Problem.hxx>
#include <planning/Action.hxx>
#include <cassert>

namespace aig_tk
{
	Plan::Plan( STRIPS_Problem& p )
		: m_task( p )
	{
	}

	Plan::~Plan()
	{
	}

	void	Plan::set_action_at( unsigned a, unsigned t )
	{
		assert( a < m_task.num_actions() );
		m_actions[t] = m_task.actions()[a];
	}

	void	Plan::add_action( unsigned a )
	{
		assert( a < m_task.num_actions() );
		m_actions.push_back( m_task.actions()[a] );
	}

	void	Plan::print_fancy( std::ostream& os )
	{
		for ( unsigned i = 0; i < m_actions.size(); i++ )
		{
			if ( m_actions[i] == NULL )
			{
				os << i+1 << ". GAP! [0]" << std::endl;
			}
			os << i+1 << ". " << m_actions[i]->signature();
			os << " [" << m_actions[i]->cost() << "]" <<  std::endl;
		}	
	}
}
