#ifndef __RELAXED_PLAN_EXTRACTOR__
#define __RELAXED_PLAN_EXTRACTOR__

#include <planning/STRIPS_Problem.hxx>
#include <planning/Types.hxx>
#include <planning/Action.hxx>
#include <planning/Fluent.hxx>
#include <queue>
#include <util/bitarray.hxx>
#include <iostream>

namespace aig_tk
{

template < typename Heuristic >
class Relaxed_Plan_Extractor
{
	typedef std::queue<Action* >	Action_Queue;
public:

	Relaxed_Plan_Extractor() {}
	~Relaxed_Plan_Extractor() {}

	void		initialize( STRIPS_Problem& p );
	Cost_Type	eval( Fluent_Vec& C, Fluent_Vec& G );

protected:

	Heuristic&		heuristic() { return m_base_heuristic; }
	STRIPS_Problem&		problem() { return *m_problem; }
	Bit_Array&		actions_seen() { return m_act_seen; }
	Action_Queue&		actions_pending() { return m_pending; }
	Bit_Array&		init_fluents() { return m_init_fluents; }

	bool			extract_best_supporters_for( Fluent_Vec& C, Action_Ptr_Vec& relaxed_plan );

protected:


	Heuristic		m_base_heuristic;
	Bit_Array		m_act_seen;
	Bit_Array		m_init_fluents;
	Action_Queue		m_pending;
	STRIPS_Problem*		m_problem;
};

template <typename Heuristic>
void	Relaxed_Plan_Extractor<Heuristic>::initialize( STRIPS_Problem& p )
{
	heuristic().initialize( p );
	m_problem = &p;
	m_act_seen.resize( p.num_actions() );
	m_init_fluents.resize( p.num_fluents() );
}

template <typename Heuristic>
bool	Relaxed_Plan_Extractor<Heuristic>::extract_best_supporters_for( Fluent_Vec& C, Action_Ptr_Vec& relaxed_plan )
{
	for ( unsigned k = 0; k < C.size(); k++ )
	{
		if ( init_fluents().isset( C[k] ) ) continue;
		Action* sup = heuristic().best_supporter( C[k] );
		if ( sup == NULL )
		{
			std::cerr << "No best supporter found for fluent ";
			std::cerr << problem().fluents()[C[k]]->signature() << std::endl;
			return false;
		}
#ifdef DEBUG
		std::cout << a->signature() << "[" << a->index() <<  "] <- " << problem().fluents()[C[k]]->signature();
		std::cout << " <- " << sup->signature() << "[" << sup->index() << "]" << std::endl;
#endif
		if ( actions_seen().isset( sup->index() ) ) continue;
		actions_pending().push( sup );
		actions_seen().set( sup->index() );
		relaxed_plan.push_back( sup );
	} 
	return true;
}

template <typename Heuristic>
Cost_Type Relaxed_Plan_Extractor<Heuristic>::eval( Fluent_Vec& C, Fluent_Vec& G )
{
	heuristic().compute(C);
	Cost_Type v = heuristic().eval( G );
	if ( v == std::numeric_limits<Cost_Type>::infinity() )
		return 	std::numeric_limits<Cost_Type>::infinity();
	// 0. Initialize data structures
	actions_seen().reset();
	init_fluents().reset();
	for ( unsigned k = 0; k < C.size(); k++ )
		init_fluents().set( C[k] );
	while ( !actions_pending().empty() )
		actions_pending().pop();
	Action_Ptr_Vec relaxed_plan;

	// 1. Add to the pending queue best supporters for goal fluents
	for ( unsigned k = 0; k < G.size(); k++ )
	{
		if ( init_fluents().isset( G[k] ) ) continue;
		Action* sup = heuristic().best_supporter( G[k] );
		if ( sup == NULL ) // No best supporter for fluent
		{
			std::cerr << "No best supporter found for goal fluent ";
			std::cerr << problem().fluents()[G[k]]->signature() << std::endl;
			return infty;
		}
		actions_pending().push( sup );
		actions_seen().set( sup->index() );
		relaxed_plan.push_back( sup );
	}	

	while ( !actions_pending().empty() )
	{
		Action* a = actions_pending().front();
		actions_pending().pop();
/*		
		Fluent_Vec prec = a->prec_vec();

 		unsigned ce_idx = 0;
 		do{
	
			for ( unsigned k = 0; k < prec.size(); k++ )
	  		{
	   			if ( init_fluents().isset( prec[k] ) ) continue;
	    			Action* sup = heuristic().best_supporter( prec[k] );
	     			if ( sup == NULL )
	      			{
#ifdef DEBUG
	     				std::cerr << "No best supporter found for fluent ";
	      				std::cerr << problem().fluents()[prec[k]]->signature() << std::endl;
#endif
			 		return infty;
			  	}
#ifdef DEBUG
			   	std::cout << a->signature() << "[" << a->index() <<  "] <- " << problem().fluents()[prec[k]]->signature();
			    	std::cout << " <- " << sup->signature() << "[" << sup->index() << "]" << std::endl;
#endif
       				if ( actions_seen().isset( sup->index() ) ) continue;
				actions_pending().push( sup );
	 			actions_seen().set( sup->index() );
	  			relaxed_plan.push_back( sup );
	   		} 
	    		if( ce_idx < a->ceff_vec().size() )
	     		{
	      			prec = a->ceff_vec()[ ce_idx ]->prec_vec();
	       			ce_idx++;
			}
		 	else
		  		break;
               
		}while( true );
*/

		if ( !extract_best_supporters_for( a->prec_vec(), relaxed_plan ) )
		{
			assert( false );
			return infty;
		}
		for ( unsigned k = 0; k < a->ceff_vec().size(); k++ )
		{
			if ( !extract_best_supporters_for( a->ceff_vec()[ k ]->prec_vec(), relaxed_plan ) )
			{
				assert( false );
				return infty;
			}
		}
	}
	
	return relaxed_plan.size();
}

}

#endif // Relaxed_Plan_Extractor.hxx
