#include <planning/heuristics/Max_Pair_Heuristic.hxx>
#include <planning/Fluent.hxx>
#include <planning/Action.hxx>
#include <util/ext_math.hxx>
#include <fstream>


namespace aig_tk
{

Max_Pair_Heuristic::Max_Pair_Heuristic()
	: m_problem( NULL )
{
}

Max_Pair_Heuristic::~Max_Pair_Heuristic()
{
}

void Max_Pair_Heuristic::initialize( STRIPS_Problem& p )
{
	set_problem( p );
}

unsigned Max_Pair_Heuristic::eval( Fluent_Vec& C, Fluent_Vec& G )
{
	// 1. Initialize fluent values
	fl_values().clear();
	for ( unsigned k = 0; k < C.size(); k++ )
		for ( unsigned l = k; l < C.size(); l++ )
			fl_values().update_value( C[k], C[l], 0 );

	// 2. Compute heuristic values for all fluents
	bool fixed_point;	
	do
	{
		fixed_point = true;

		for ( unsigned a_idx = 0; a_idx < problem().num_actions(); a_idx++ )
		{
			Action* a = problem().actions()[a_idx];
			// a. compute h²(Pre(a))
			Fluent_Vec& a_prec = a->prec_vec();
			unsigned h2_pre_a = 0;
			for ( unsigned k = 0; k < a_prec.size() && h2_pre_a != infty; k++ )
				for ( unsigned l = k; l < a_prec.size() && h2_pre_a != infty; l++ ) 
					h2_pre_a = std::max( fl_values().get_value( a_prec[k], a_prec[l] ), h2_pre_a );
			if ( h2_pre_a == infty ) continue;
			Fluent_Vec& a_adds = a->add_vec();
			for ( unsigned i = 0; i < a_adds.size(); i++ )
			{
				for ( unsigned j = i; j < a_adds.size(); j++ )
				{
					unsigned curr_v = fl_values().get_value(a_adds[i],a_adds[j]);
					unsigned new_v = a->cost() + h2_pre_a;
					if ( new_v < curr_v )
					{
						fl_values().update_value( a_adds[i], a_adds[j], new_v );
						fixed_point = false;
					}
				}
				for ( unsigned q = 0; q < problem().num_fluents(); q++ )
				{
					if ( a->add_set().isset(q) || a->del_set().isset(q) ) continue;
					unsigned h2_pre_a_noop = std::max( h2_pre_a, fl_values().get_value( q, q ) );
					for ( unsigned j = 0; j < a_prec.size() && h2_pre_a_noop != infty; j++ )
						h2_pre_a_noop = std::max( h2_pre_a_noop, fl_values().get_value( q, a_prec[j] ) );
					if ( h2_pre_a_noop == infty ) continue;
					unsigned old_v = fl_values().get_value( a_adds[i], q );
					unsigned new_v = a->cost() + h2_pre_a_noop;
					if ( new_v < old_v )
					{
						fl_values().update_value( a_adds[i], q, new_v );
						fixed_point = false;
					}
				}
			}
		}
	} while ( !fixed_point );

	#ifdef DEBUG
	std::ofstream out( "h2.values" );
	for ( unsigned p = 0; p < problem().num_fluents(); p++ )
		for ( unsigned q = p; q < problem().num_fluents(); q++ )
		{
			out << "h^2( " << problem().fluents()[p]->signature();
			out << ", " << problem().fluents()[q]->signature();
			out << " ) = " << fl_values().get_value( p, q ) << std::endl;
		}
	out.close();
	#endif

	// 3. Evaluate heuristic values for C
	unsigned h = 0;
	for ( unsigned k = 0; k < G.size(); k++ )
		for ( unsigned l = k; l < G.size(); l++ )
			h = std::max( h, fl_values().get_value( G[k], G[l]) );

	return h;
}

}
