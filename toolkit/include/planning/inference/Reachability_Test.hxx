#ifndef __REACHABILITY_TEST__
#define __REACHABILITY_TEST__

#include <planning/STRIPS_Problem.hxx>
#include <planning/Types.hxx>
#include <vector>

namespace aig_tk
{
	// MRJ: Reachability test in the delete-free relaxation
	class	Reachability_Test
	{
	public:

		Reachability_Test( STRIPS_Problem& p );
		~Reachability_Test();

		// Returns true if atom set g is reachable from state s 
		bool	is_reachable( Fluent_Vec& s, Fluent_Vec& g );
		// Returns true if atom set g is reachable from s, when removing action
		bool	is_reachable( Fluent_Vec& s, Fluent_Vec& g, unsigned action );
	protected:

		bool	apply_actions();
		void	initialize(Fluent_Vec& s);
		bool	check( Fluent_Vec& set );

	protected:

		STRIPS_Problem&		m_problem;
		std::vector<bool>	m_reachable_atoms;
		std::vector<bool>	m_action_mask;		
	};

}

#endif // Reachability_Test.hxx
