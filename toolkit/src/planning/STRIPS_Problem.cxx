#include <planning/STRIPS_Problem.hxx>
#include <planning/Action.hxx>
#include <planning/Fluent.hxx>
#include <planning/PDDL_Type.hxx>
#include <planning/PDDL_Object.hxx>
#include <planning/PDDL_Operator.hxx>
#include <cassert>
#include <map>

namespace aig_tk
{

	STRIPS_Problem::STRIPS_Problem()
		: m_num_fluents( 0 ), m_num_actions( 0 ), m_num_types(0), m_num_objects(0), m_num_pddl_ops(0)
	{
	}

	STRIPS_Problem::~STRIPS_Problem()
	{
	}

	void	STRIPS_Problem::make_action_tables()
	{
		m_requiring.resize( fluents().size() );
		m_deleting.resize( fluents().size() );
		m_adding.resize( fluents().size() );
		
		for ( unsigned k = 0; k < actions().size(); k++ )
			register_action_in_tables( actions()[k] );
	}

	void	STRIPS_Problem::register_action_in_tables( Action* a )
	{
		for ( unsigned k = 0; k < a->prec_vec().size(); k++ )
			actions_requiring(a->prec_vec()[k]).push_back( a );
		for ( unsigned k = 0; k < a->add_vec().size(); k++ )
			actions_adding(a->add_vec()[k]).push_back(a);
		for ( unsigned k = 0; k < a->del_vec().size(); k++ )
			actions_deleting(a->del_vec()[k]).push_back(a);	
		
		//register conditional effects
		for ( unsigned i = 0; i < a->ceff_vec().size(); i++ )
		{
			for ( unsigned k = 0; k < a->ceff_vec()[i]->prec_vec().size(); k++ )
				actions_requiring(a->ceff_vec()[i]->prec_vec()[k]).push_back( a );
			for ( unsigned k = 0; k < a->ceff_vec()[i]->add_vec().size(); k++ )
				actions_adding(a->ceff_vec()[i]->add_vec()[k]).push_back(a);
			for ( unsigned k = 0; k < a->ceff_vec()[i]->del_vec().size(); k++ )
				actions_deleting(a->ceff_vec()[i]->del_vec()[k]).push_back(a);	
		}
	}

	void	STRIPS_Problem::register_fluent_in_tables( Fluent* fl )
	{
		std::vector<bool> in_type(m_types.size(),false);
		for ( unsigned k = 0; k < fl->pddl_types_idx().size(); k++ )
		{
			unsigned type_idx = fl->pddl_types_idx()[k];
			if( ! in_type[ type_idx ] )
			{
				fluents_by_type( type_idx ).push_back( fl );
				in_type[ type_idx ]=true;
			}
		}
		std::vector<bool> in_obj(m_objects.size(),false);

		for ( unsigned k = 0; k < fl->pddl_objs_idx().size(); k++ )
		{
			unsigned obj_idx = fl->pddl_objs_idx()[k];
			if( ! in_obj[ obj_idx ] )
			{
				fluents_by_object( obj_idx ).push_back( fl );
				in_obj[ obj_idx ] = true;
			}
		}
	}

	void	STRIPS_Problem::register_object_in_tables( PDDL_Object* obj )
	{
		Index_Vec& types_idx = obj->types_idx();
		for( unsigned i = 0; i < types_idx.size(); i++)
			m_pddl_objects_by_type[ types_idx[i] ].push_back( obj );
	}

	unsigned STRIPS_Problem::add_pddl_operator( STRIPS_Problem& p, std::string signature,
						    std::string base_name, std::vector<std::string>& args,
						    Index_Vec& arg_types )
	{
		PDDL_Operator* new_op = new PDDL_Operator( p );
		new_op->set_signature( signature );
		new_op->set_name( base_name );

		for(unsigned i = 0; i < args.size(); i++)
			new_op->add_arg_name( args[i] );

		for(unsigned i = 0; i < arg_types.size(); i++)
			new_op->add_pddl_type_idx( arg_types[i] );

		p.increase_num_pddl_ops();
		p.pddl_ops().push_back( new_op );
		new_op->set_index( p.pddl_ops().size()-1 );
		p.make_pddl_op_table();
		return p.pddl_ops().size()-1;
	}

	
	unsigned STRIPS_Problem::add_action( STRIPS_Problem& p, std::string signature,
					     Fluent_Vec& pre, Fluent_Vec& add, Fluent_Vec& del,
					     std::string base_name, Index_Vec& args, Index_Vec& arg_types, unsigned pddl_op_idx, Conditional_Effect_Vec& ceffs )
	{
		Action* new_act = new Action( p );
		new_act->set_signature( signature );
		new_act->set_name( base_name );
		new_act->define( pre, add, del, ceffs );
		new_act->set_pddl_op_idx( pddl_op_idx );

		//NO-OBJECT
		if( args.empty() ) new_act->add_pddl_obj_idx( p.num_objects()-1 );
		for(unsigned i = 0; i < args.size(); i++)
			new_act->add_pddl_obj_idx( args[i] );
		//NO-TYPE
		if( arg_types.empty() ) new_act->add_pddl_type_idx( p.num_types()-1 );
		for(unsigned i = 0; i < arg_types.size(); i++)
			new_act->add_pddl_type_idx( arg_types[i] );

		p.increase_num_actions();
		p.actions().push_back( new_act );
		p.register_action_in_tables( new_act );
		p.actions_by_pddl_op( new_act->pddl_op_idx() ).push_back(new_act);
		new_act->set_index( p.actions().size()-1 );
		return p.actions().size()-1;
	}

	unsigned STRIPS_Problem::add_action( STRIPS_Problem& p, std::string signature,
					     Fluent_Vec& pre, Fluent_Vec& add, Fluent_Vec& del,
					     Conditional_Effect_Vec& ceffs )
	{
		Action* new_act = new Action( p );
		new_act->set_signature( signature );
		new_act->define( pre, add, del, ceffs );
		p.increase_num_actions();
		p.actions().push_back( new_act );
		new_act->set_index( p.actions().size()-1 );
		return p.actions().size()-1;
	}

	void	STRIPS_Problem::make_table_entries_for( unsigned f )
	{
		/*
		  m_adding.insert( std::make_pair( f, Action_Ptr_Vec() ) );
		  m_deleting.insert( std::make_pair( f, Action_Ptr_Vec() ) );
		  m_requiring.insert( std::make_pair( f, Action_Ptr_Vec() ) );
		*/

		m_adding.resize(f+1);
		m_deleting.resize(f+1);
		m_requiring.resize(f+1);
	}

	void STRIPS_Problem::add_type( STRIPS_Problem& p, std::string type )
	{

		PDDL_Type* new_type = new PDDL_Type( p );
		new_type->set_index( p.types().size() );
		new_type->set_signature( type );
		p.increase_num_types();
		p.types().push_back( new_type );	       
		
		p.make_types_table();	
	}

	void STRIPS_Problem::add_object( STRIPS_Problem& p, std::string object, Index_Vec& types_idx )
	{

		PDDL_Object* new_object = new PDDL_Object( p );
		new_object->set_index( p.objects().size() );
		new_object->set_signature( object );
		new_object->set_types_idx( types_idx );
		p.increase_num_objects();
		p.objects().push_back( new_object );		
		p.register_object_in_tables( new_object );		
		p.make_object_table();
	}

	unsigned STRIPS_Problem::add_fluent( STRIPS_Problem& p, std::string signature )
	{
		Fluent* new_fluent = new Fluent( p );
		new_fluent->set_index( p.fluents().size() );
		new_fluent->set_signature( signature );
		p.m_fluents_map[signature] = p.fluents().size();
		p.increase_num_fluents();
		p.fluents().push_back( new_fluent );
		return p.fluents().size()-1;
	}

	unsigned STRIPS_Problem::add_fluent( STRIPS_Problem& p, std::string signature,
					     std::string pred_name, Index_Vec& args, Index_Vec& arg_types )
	{
		Fluent* new_fluent = new Fluent( p );
		new_fluent->set_index( p.fluents().size() );
		new_fluent->set_signature( signature );
		new_fluent->set_predicate( pred_name );
		p.m_fluents_map[pred_name] = p.fluents().size();
		//NO-OBJECT
		if( args.empty() ) new_fluent->add_pddl_obj_idx( p.num_objects()-1 );
		for(unsigned i = 0; i < args.size(); i++)
			new_fluent->add_pddl_obj_idx( args[i] );
		//NO-TYPE
		if( arg_types.empty() ) new_fluent->add_pddl_type_idx( p.num_types()-1 );
		for(unsigned i = 0; i < arg_types.size(); i++)
			new_fluent->add_pddl_type_idx( arg_types[i] );
		p.increase_num_fluents();
		p.fluents().push_back( new_fluent );
		p.register_fluent_in_tables( new_fluent );
		p.make_table_entries_for( new_fluent->index() );	
		return p.fluents().size()-1;
	}

	void	STRIPS_Problem::set_init( STRIPS_Problem& p, Fluent_Vec& init_vec )
	{
#ifdef DEBUG
		for ( unsigned k = 0; k < init_vec.size(); k++ )
			assert( init_vec[k] < p.num_fluents() );
#endif	
		if ( p.m_in_init.empty() )
		  p.m_in_init.resize( p.num_fluents(), false );
		else
		  for ( unsigned k = 0; k < p.num_fluents(); k++ )
		    p.m_in_init[k] = false;

		p.init().assign( init_vec.begin(), init_vec.end() );
		for ( unsigned k = 0; k < init_vec.size(); k++ )
			p.m_in_init[ init_vec[k] ] = true;
	}

	void	STRIPS_Problem::set_goal( STRIPS_Problem& p, Fluent_Vec& goal_vec, bool createEndOp )
	{
#ifdef DEBUG
		for ( unsigned k = 0; k < goal_vec.size(); k++ )
			assert( goal_vec[k] < p.num_fluents() );
#endif
		if ( p.m_in_goal.empty() )
		  p.m_in_goal.resize( p.num_fluents(), false );
		else
		  for ( unsigned k = 0; k < p.num_fluents(); k++ )
		    p.m_in_goal[k] = false;

		p.goal().assign( goal_vec.begin(), goal_vec.end() );
		for ( unsigned k = 0; k < goal_vec.size(); k++ )
			p.m_in_goal[ goal_vec[k] ] = true;
		
		if ( createEndOp )
		{
			Fluent_Vec dummy;
			Conditional_Effect_Vec dummy_ceffs;
			p.m_end_operator_id = add_action( p, "(END)", goal_vec, dummy, dummy, dummy_ceffs);
			p.actions()[ p.m_end_operator_id ]->set_cost( 0 );
		}
	}

	void STRIPS_Problem::print_fluent_vec(const Fluent_Vec &a) {
		for(unsigned i = 0; i < a.size(); i++) {
			std::cout << fluents()[a[i]]->signature() << ", ";
		}
	}

        int STRIPS_Problem::getFluentIndex(std::string signature){
              return m_fluents_map[signature];
        }
}
