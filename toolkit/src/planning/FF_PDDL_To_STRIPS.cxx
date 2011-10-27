#include <planning/FF_PDDL_To_STRIPS.hxx>
#include <planning/Action.hxx>
#include <iostream>

namespace aig_tk
{

FF_PDDL_To_STRIPS::FF_PDDL_To_STRIPS()
{
}

FF_PDDL_To_STRIPS::~FF_PDDL_To_STRIPS()
{
}

void	FF_PDDL_To_STRIPS::get_problem_description( std::string pddl_domain_path,
					std::string pddl_problem_path,
					STRIPS_Problem& strips_problem,
					bool get_detailed_fluent_names )
{
	
	FF_parse_problem( pddl_domain_path.c_str(), pddl_problem_path.c_str() );
	//	std::cout << "FF-preprocessing of PDDL problem description" << std::endl;
	FF_instantiate_problem();
	//	std::cout << "Facts in problem:" << gnum_ft_conn << std::endl;
	
	std::vector<std::string> types;
	FF::get_types( types );
	for ( std::vector<std::string>::iterator it_str = types.begin();
		      it_str != types.end(); it_str++)
		STRIPS_Problem::add_type(strips_problem, *it_str);

	std::vector<std::string> objects;
	std::vector<Index_Vec> objects_types;
	FF::get_objects( objects, objects_types );

	for ( unsigned i=0;i<objects.size();i++)			
		STRIPS_Problem::add_object( strips_problem, objects[i], objects_types[i] );
	
	for ( int i = 0; i < gnum_ft_conn; i++ )
	{
		if ( !get_detailed_fluent_names )
		{
			std::string ft_name = FF::get_ft_name(i);
			STRIPS_Problem::add_fluent( strips_problem, ft_name);
			continue;
		}
		std::string ft_signature = FF::get_ft_name(i);
		std::string pred_name = FF::get_ft_pred_name(i);
		Index_Vec ft_args_idx;
		Index_Vec ft_arg_types_idx;
		FF::get_ft_arg_list( i, ft_args_idx, ft_arg_types_idx );
		STRIPS_Problem::add_fluent( strips_problem, ft_signature, pred_name, ft_args_idx, ft_arg_types_idx );
	}
	Fluent_Vec I, G;
	FF::get_initial_state( I );
	FF::get_goal_state( G );
	STRIPS_Problem::set_init( strips_problem, I);
	STRIPS_Problem::set_goal( strips_problem, G);		

	//	std::cout << "Operators in problem:" << gnum_ef_conn << std::endl;
	/**
	 * Load PDDL Operators
	 */
	if ( get_detailed_fluent_names )
	{
		for(int i = 0; i < gnum_operators; i++)
		{
			std::string op_name = FF::get_pddl_op_name(i) ;
			std::string base_name;
			std::vector<std::string> op_args;
			Index_Vec op_arg_types_idx;
			FF::get_pddl_op( i, base_name, op_args, op_arg_types_idx );
			STRIPS_Problem::add_pddl_operator( strips_problem, op_name, base_name, op_args, op_arg_types_idx );
		}
	}
				
        bool with_costs = false;
        for ( int i = 0; i < gnum_ef_conn; i++ )
                if( FF::get_op_metric_cost( i ) != 0 )
                {
                        with_costs = true;
                        break;
                }
        

	for ( int i = 0; i < gnum_ef_conn; i++ )
	{
		if ( gef_conn[i].removed == TRUE ) continue;
		if ( gef_conn[i].illegal == TRUE ) continue;

		std::string op_name = FF::get_op_name(i);
		Fluent_Vec  op_prec, op_adds, op_dels;
		

		for ( int j = 0; j < gef_conn[i].num_PC; j++ )
			op_prec.push_back( gef_conn[i].PC[j] );
		for ( int j = 0; j < gef_conn[i].num_A; j++ )
			op_adds.push_back( gef_conn[i].A[j] );
		for ( int j = 0; j < gef_conn[i].num_D; j++ )
			op_dels.push_back( gef_conn[i].D[j] );

		aig_tk::Cost_Type op_cost = 0;
                if(with_costs)
                {
                        if ( gef_conn[i].num_IN == 0 ) {
                                op_cost = 0;
                        }
                        else if ( gef_conn[i].num_IN >= 1 ) {
                                op_cost = gef_conn[i].cost;
                        }
                }
                else
                        op_cost = 1;
                                
		unsigned op_idx;
		if ( !get_detailed_fluent_names )
			op_idx = STRIPS_Problem::add_action( strips_problem, op_name, op_prec, op_adds, op_dels );
		else
		{
			std::string op_base_name = FF::get_op_base_name(i);
			Index_Vec op_args_idx;
			Index_Vec op_arg_types_idx;
			unsigned pddl_op_idx=0;
			FF::get_op_arg_list( i, op_args_idx, op_arg_types_idx, pddl_op_idx );
			op_idx = STRIPS_Problem::add_action( strips_problem, op_name, op_prec, op_adds, op_dels, op_base_name, op_args_idx, op_arg_types_idx, pddl_op_idx );
		}

		strips_problem.actions()[op_idx]->set_cost( op_cost );
	}

}

}
