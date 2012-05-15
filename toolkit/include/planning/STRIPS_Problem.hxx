#ifndef __STRIPS_PROBLEM__
#define __STRIPS_PROBLEM__

#include <string>
#include <planning/Types.hxx>
#include <map>

namespace aig_tk
{

	class STRIPS_Problem
	{
	public:
	
		STRIPS_Problem();
		~STRIPS_Problem();

		unsigned 		num_fluents() 			{ return m_num_fluents; }
		unsigned 		num_actions() 			{ return m_num_actions; }
		unsigned 		num_types() 			{ return m_num_types; }
		unsigned 		num_objects() 			{ return m_num_objects; }
		unsigned                num_pddl_ops()                  { return m_num_pddl_ops; }

		void			set_num_fluents( unsigned nf ) { m_num_fluents = nf; }
		void			set_num_actions( unsigned na ) { m_num_actions = na; }

		static void             add_type( STRIPS_Problem& p, std::string type );
		static void             add_object( STRIPS_Problem& p, std::string object,
						    Index_Vec& types_idx);
		static unsigned		add_action( STRIPS_Problem& p, std::string signature, 
						    Fluent_Vec& pre, Fluent_Vec& add, Fluent_Vec& del,
						    std::string base_name, Index_Vec& args, Index_Vec& arg_types,
						    unsigned pddl_op_idx, Conditional_Effect_Vec& ceffs);
		static unsigned 	add_action( STRIPS_Problem& p, std::string signature,
						    Fluent_Vec& pre, Fluent_Vec& add, Fluent_Vec& del,
						    Conditional_Effect_Vec& ceffs );
		static unsigned         add_pddl_operator( STRIPS_Problem& p, std::string signature,
							   std::string base_name, std::vector<std::string>& args,
							   Index_Vec& arg_types );
		static unsigned 	add_fluent( STRIPS_Problem& p, std::string signature );
		static unsigned		add_fluent( STRIPS_Problem& p, std::string signature, 
						    std::string predicate, Index_Vec& args,
						    Index_Vec& arg_types);

		static void		set_init( STRIPS_Problem& p, Fluent_Vec& init );
		static void		set_goal( STRIPS_Problem& p, Fluent_Vec& goal, bool createEndOp = true );

	  	
	  Fluent_Ptr_Vec&		fluents() 			{ return m_fluents; }
		Action_Ptr_Vec&		actions() 			{ return m_actions; }
		PDDL_Operator_Ptr_Vec&  pddl_ops() 			{ return m_pddl_ops; }
		PDDL_Type_Ptr_Vec&      types()                         { return m_types; }
		PDDL_Object_Ptr_Vec&    objects()                       { return m_objects; }
		Fluent_Vec&		init()	  			{ return m_init; }
		Fluent_Vec&		goal()	  			{ return m_goal; }
		Action_Ptr_Vec&		actions_adding( unsigned f ) 	{ return m_adding[f]; }
		Action_Ptr_Vec&		actions_deleting( unsigned f ) 	{ return m_deleting[f]; }
		Action_Ptr_Vec&		actions_requiring( unsigned f ) { return m_requiring[f]; }
		Action_Ptr_Vec&		actions_by_pddl_op( unsigned pddl_op_idx ) { return m_actions_by_pddl_op[ pddl_op_idx ]; }
		Fluent_Ptr_Vec&         fluents_by_type( unsigned t )   { return m_fluents_by_type[ t ]; }
		Fluent_Ptr_Vec&         fluents_by_object( unsigned t ) { return m_fluents_by_object[ t ]; }
		PDDL_Object_Ptr_Vec&    objects_by_type( unsigned t )   { return m_pddl_objects_by_type[t]; }
		bool			is_in_init( unsigned f )	{ return m_in_init[f]; }
		bool			is_in_goal( unsigned f )	{ return m_in_goal[f]; }
		void                    print_fluent_vec(const Fluent_Vec &a);
		unsigned                end_operator() { return m_end_operator_id; }
	        int                     getFluentIndex(std::string signature);
		void			make_action_tables();	
	protected:
	
		void			increase_num_fluents()        { m_num_fluents++; }
		void			increase_num_actions()        { m_num_actions++; }
		void			increase_num_types()     { m_num_types++; }
		void			increase_num_objects()   { m_num_objects++; }
		void			increase_num_pddl_ops()   { m_num_pddl_ops++; }
		void                    make_types_table() { m_fluents_by_type.resize( m_types.size() ); m_pddl_objects_by_type.resize( m_types.size() );}
		void                    make_object_table() { m_fluents_by_object.resize( m_objects.size() ); }
		void                    make_pddl_op_table() { m_actions_by_pddl_op.resize( m_pddl_ops.size() ); }
		void			make_table_entries_for( unsigned f );
		void			register_action_in_tables( Action* act );
		void			register_fluent_in_tables( Fluent* fl );
		void			register_object_in_tables( PDDL_Object* obj );
	protected:

		unsigned		 m_num_fluents;
		unsigned		 m_num_actions;
		unsigned                 m_num_types;
		unsigned                 m_num_objects;
		unsigned		 m_num_pddl_ops;
		Action_Ptr_Vec		 m_actions;
		Fluent_Ptr_Vec		 m_fluents;
		Fluent_Vec		 m_init;
		Fluent_Vec		 m_goal;
		Fluent_Action_Table	 m_adding;
		Fluent_Action_Table	 m_requiring;
		Fluent_Action_Table	 m_deleting;
		std::vector<bool>	 m_in_init;
		std::vector<bool>	 m_in_goal;
		unsigned                 m_end_operator_id;
		PDDL_Type_Ptr_Vec        m_types;
		PDDL_Object_Ptr_Vec      m_objects;
		Type_Fluent_Table        m_fluents_by_type;
		Object_Fluent_Table      m_fluents_by_object;
		PDDL_Operator_Ptr_Vec    m_pddl_ops;
		PDDLop_Action_Table      m_actions_by_pddl_op;
		PDDL_Type_Object_Table   m_pddl_objects_by_type; 
	  	std::map<std::string,int> m_fluents_map;
	  };

}

#endif // STRIPS_Problem.hxx
