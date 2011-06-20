#include <planning/heuristics/Max_Heuristic.hxx>
#include <util/ext_math.hxx>

namespace aig_tk
{

void Max_Heuristic::compute( Fluent_Vec& C )
{
	// 1. Initialize fluent values
	for ( unsigned k = 0; k < fl_values().size(); k++ )
		set_fl_value( k, infty );
                
	for ( unsigned k = 0; k < C.size(); k++ )
		set_fl_value( C[k], 0 );


        // 2. Compute heuristic values for all fluents
	
	bool changed;

	do
	{
		changed = false;
		for ( unsigned k = 0; k < problem().actions().size(); k++ )
		{
			// a. evaluate precondition

			Action* a = problem().actions()[k];
                        Cost_Type h_pre = eval( a->prec_vec() );

			// b. cutoff if infty
			if ( h_pre == infty ) continue;
                        
			// c. update when a is a better support for p \in Add(a)
			Cost_Type v = a->cost() + h_pre;                        
			for ( unsigned l = 0; l < a->add_vec().size(); l++ )
				if ( v < fl_value( a->add_vec()[l] ) )
				{
					set_fl_value( a->add_vec()[l], v );
					set_best_supporter( a->add_vec()[l], a );
					best_supporters(a->add_vec()[l]).push_back( a );
					changed = true;
				}
				else if ( v == fl_value( a->add_vec()[l] ) )
					best_supporters(a->add_vec()[l]).push_back( a );
			
		}
	} while ( changed );



}

}
