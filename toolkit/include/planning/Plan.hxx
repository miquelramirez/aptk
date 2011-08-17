#ifndef __PLAN__
#define __PLAN__

#include <planning/Types.hxx>
#include <fstream>

namespace aig_tk
{
	class	STRIPS_Problem;

	class	Plan
	{
	public:
		Plan( STRIPS_Problem& p );
		~Plan();

		void		set_num_steps( unsigned n );
		unsigned	num_steps( ) const;
		void		set_action_at( unsigned a, unsigned t );
		void		add_action( unsigned a );

		void		print_fancy( std::ofstream& os );

	protected:
		
		STRIPS_Problem& 	m_task;
		float			m_cost;
		Action_Ptr_Vec		m_actions;
	};

	inline	void		Plan::set_num_steps( unsigned n )
	{
		m_actions.resize( n );
	}

	inline	unsigned	Plan::num_steps() const
	{
		return m_actions.size();
	}
	
}

#endif
