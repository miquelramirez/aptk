#ifndef __HEURISTIC__
#define __HEURISTIC__

#include <planning/STRIPS_Problem.hxx>
#include <planning/Types.hxx>
#include <planning/Action.hxx>

namespace aig_tk
{

class Heuristic
{
public:

	Heuristic() : m_problem(NULL) {};
	virtual ~Heuristic(){};

	virtual void	initialize( STRIPS_Problem& p )
        {
                m_fluent_values.resize( p.num_fluents() );
                m_best_supporter.resize( p.num_fluents() );
                m_best_supporters.resize( p.num_fluents() );
                for ( unsigned q = 0; q < p.num_fluents(); q++ )
                        m_best_supporters[q] = Action_Ptr_Vec();
                set_problem( p );
        };
        
        /**
         * Must implement compute AND eval
         */
	virtual void    	compute( Fluent_Vec& C ) = 0;

	virtual void		compute_without_supporters( Fluent_Vec& C )
	{
		compute(C);
	}

	virtual Cost_Type	eval( Fluent_Vec& G ) = 0;
        
        
        /**
         * Accessors
         */
        Cost_Type       op_value( unsigned op ){ return eval( problem().actions()[op]->prec_vec() ); }
	Cost_Type	fl_value( unsigned p ) const 			{ return m_fluent_values[p]; }	
        void		set_fl_value( unsigned p, Cost_Type v ) 		{ m_fluent_values[p] = v; }
	Action*		best_supporter( unsigned p ) 			{ return m_best_supporter[p]; }
	void		set_best_supporter( unsigned p, Action* a )	{ m_best_supporter[p] = a; }
	Action_Ptr_Vec&	best_supporters( unsigned p ) 			{ return m_best_supporters[p]; }

protected:

	Value_Vec&	fl_values() { return m_fluent_values; }
	void		set_problem( STRIPS_Problem& p ) { m_problem = &p; }
	STRIPS_Problem& problem() { return *m_problem; }

protected:
                
	Value_Vec		m_fluent_values;
	STRIPS_Problem*		m_problem;
	Action_Ptr_Vec		m_best_supporter;
	Fluent_Action_Table	m_best_supporters;
};

}

#endif // Heuristic.hxx
