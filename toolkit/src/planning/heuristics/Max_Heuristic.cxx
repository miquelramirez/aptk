#include <planning/heuristics/Max_Heuristic.hxx>
#include <util/ext_math.hxx>

namespace aig_tk
{

void Max_Heuristic::initialize_values( Fluent_Vec& C )
{
	for ( unsigned k = 0; k < fl_values().size(); k++ )
		set_fl_value( k, infty );
                
	for ( unsigned k = 0; k < C.size(); k++ )
	{
		set_fl_value( C[k], 0 );
		updated.push_back( C[k] );
	}
	
}

void Max_Heuristic::compute_without_supporters( Fluent_Vec& C )
{
	// 1. Initialize fluent values
	initialize_values(C);

        // 2. Compute heuristic values for all fluents

	while ( !updated.empty() )
	{
		unsigned p = updated.front();
		updated.pop_front();
		Action_Ptr_Vec& actions = problem().actions_requiring(p);
		
		for ( unsigned k = 0; k < actions.size(); k++ )
		{
			// a. evaluate precondition
			Cost_Type h_pre = eval( actions[k]->prec_vec() );

			// b. cutoff if infty
			if (h_pre == infty ) continue;

			// c. update when a is a better support for p \in Add(a)
			Cost_Type v = actions[k]->cost() + h_pre;                        
			for ( unsigned l = 0; l < actions[k]->add_vec().size(); l++ )
				if ( v < fl_value( actions[k]->add_vec()[l] ) )
				{
					set_fl_value( actions[k]->add_vec()[l], v );
					updated.push_back( actions[k]->add_vec()[l] );
				}
		}
	}
}

void Max_Heuristic::compute( Fluent_Vec& C )
{

	// 1. Initialize fluent values
	initialize_values(C);

        // 2. Compute heuristic values for all fluents

	while ( !updated.empty() )
	{
		unsigned p = updated.front();
		updated.pop_front();
		Action_Ptr_Vec& actions = problem().actions_requiring(p);
		
		for ( unsigned k = 0; k < actions.size(); k++ )
		{
			// a. evaluate precondition
			Cost_Type h_pre = eval( actions[k]->prec_vec() );

			// b. cutoff if infty
			if (h_pre == infty ) continue;

			// c. update when a is a better support for p \in Add(a)
			Cost_Type v = actions[k]->cost() + h_pre;                        
			for ( unsigned l = 0; l < actions[k]->add_vec().size(); l++ )
				if ( v < fl_value( actions[k]->add_vec()[l] ) )
				{
					set_fl_value( actions[k]->add_vec()[l], v );
					updated.push_back( actions[k]->add_vec()[l] );
					set_best_supporter( actions[k]->add_vec()[l], actions[k] );
					best_supporters(actions[k]->add_vec()[l]).push_back( actions[k] );
				}
				else if ( v == fl_value( actions[k]->add_vec()[l] ) )
					best_supporters(actions[k]->add_vec()[l]).push_back( actions[k] );

		}
	}
}

}
