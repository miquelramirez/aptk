#include <planning/heuristics/Additive_Heuristic.hxx>
#include <planning/Action.hxx>
#include <util/ext_math.hxx>

namespace aig_tk
{

Additive_Heuristic::Additive_Heuristic()
	: m_problem( NULL )
{
}

Additive_Heuristic::~Additive_Heuristic()
{
}

void Additive_Heuristic::initialize( STRIPS_Problem& p )
{
	m_fluent_values.resize( p.num_fluents() );
	m_best_supporter.resize( p.num_fluents() );
	for ( unsigned q = 0; q < p.num_fluents(); q++ )
		m_best_supporters[q] = Action_Ptr_Vec();

	set_problem( p );
}

unsigned Additive_Heuristic::eval( Fluent_Vec& C, Fluent_Vec& G )
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
			unsigned h_pre = 0;
			Action* a = problem().actions()[k];
			for ( unsigned l = 0; l < a->prec_vec().size(); l++ )
				h_pre = abs_add( fl_value(a->prec_vec()[l]), h_pre );
			// b. cutoff if infty
			if ( h_pre == infty ) continue;
			// c. update when a is a better support for p \in Add(a)
			unsigned v = a->cost() + h_pre;
			for ( unsigned l = 0; l < a->add_vec().size(); l++ )
				if ( v < fl_value( a->add_vec()[l] ) )
				{
					set_fl_value( a->add_vec()[l], v );
					changed = true;
					set_best_supporter( a->add_vec()[l], a );
					best_supporters(a->add_vec()[l]).push_back( a );

				}
				else if ( v == fl_value( a->add_vec()[l] ) )
					best_supporters(a->add_vec()[l]).push_back( a );
			
		}
	} while ( changed );

	// 3. Evaluate heuristic values for C

	unsigned h = 0;	

	for ( unsigned k = 0; k < G.size(); k++ )
		h = abs_add( h, fl_value( G[k] ) );

	return h;
}

}
