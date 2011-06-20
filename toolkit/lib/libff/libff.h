#ifndef __LIB_FF_H__
#define __LIB_FF_H__

#ifdef __cplusplus
#define EXTERN extern "C"
#include <string>
#include <vector>
#else
#define EXTERN extern
#endif

#include "ff.h"

EXTERN int	FF_parse_problem( const char* domain_file, const char* instance_file );
EXTERN int	FF_instantiate_problem();

#ifdef __cplusplus

// C++ helper functions
namespace FF
{

	inline void 		get_initial_state( std::vector<unsigned>& init_atoms )
	{
		init_atoms.resize( ginitial_state.num_F );
		for ( int i = 0; i < ginitial_state.num_F; i++ )
			init_atoms[i] = ginitial_state.F[i];
	}

	inline void		get_goal_state( std::vector<unsigned>& goal_atoms )
	{
		goal_atoms.resize( gnum_logic_goal );
		for ( int i = 0; i < gnum_logic_goal; i++ )
			goal_atoms[i] = glogic_goal[i];
	}

	inline float		get_op_metric_cost( int index )
	{
		return gef_conn[index].cost + gtt;
	}

	inline std::string	get_op_name( int index )
	{
		int i;
		Action *a = gop_conn[index].action;
		std::string str;	

		if ( !a->norm_operator && !a->pseudo_action ) 
		{
			return std::string( "(REACH-GOAL)" );
		}
		str += "(";
		str += a->name;
		str += " ";
		for ( i = 0; i < a->num_name_vars; i++ ) 
		{
			str += gconstants[a->name_inst_table[i]];
			if ( i < a->num_name_vars-1 )
				str += " ";
		}
		str += " )";
		return str;
	}

	inline void 		get_pddl_op( int index, std::string& name,
					     std::vector<std::string>& args, 
					     std::vector<unsigned>& args_type )
	{

		int i;
		PDDLOperator *pddl_op = goperators[ index ];

		name = std::string( pddl_op->name );		
		for ( i = 0; i < pddl_op->num_vars; i++ ) 
		{
			args.push_back( std::string( pddl_op->var_names[i] ) );
			args_type.push_back( pddl_op->var_types[ i ] );
		}

	
	}

	inline std::string		get_pddl_op_name( int index )
	{

		int i;
		PDDLOperator *pddl_op = goperators[ index ];
		std::string str;	
		str += "(";
		str += std::string( pddl_op->name );	
		str += " ";
		for ( i = 0; i < pddl_op->num_vars; i++ ) 
		{
			str += std::string( pddl_op->var_names[i] );
			str += " - ";
			str += std::string( gtype_names[ pddl_op->var_types[ i ] ] );
			if ( i < pddl_op->num_vars-1 )
				str += " ";
		}
		str += " )";
		
		return str;
	
	}

	inline void 		get_op_arg_list( int index, std::vector<unsigned>& args, 
						 std::vector<unsigned>& args_type,
						 unsigned& pddl_op_idx)
	{

		int i;
		Action *a = gop_conn[index].action;

		if ( !a->norm_operator && !a->pseudo_action ) 
			return ;

		PDDLOperator *pddl_a = ( a->pseudo_action == NULL ) ? a->norm_operator->pddloperator : a->pseudo_action->pddloperator;
		for ( i = 0; i < a->num_name_vars; i++ ) 
		{
			args.push_back( a->name_inst_table[i] );
			args_type.push_back( pddl_a->var_types[ i ] );
		}

		for( i = 0; i < gnum_operators; i++ )
		{
			if( goperators[ i ] == pddl_a )
			{
				pddl_op_idx = i;
				break;
			}
		}
	
	}

	inline std::string	get_op_base_name( int index )
	{
		Action *a = gop_conn[index].action;

		if ( !a->norm_operator && !a->pseudo_action ) 
		{
			return std::string( "(REACH-GOAL)" );
		}

		return std::string( a->name );
	}

	inline std::string	get_ft_pred_name( int index )
	{
		Fact* f = &(grelevant_facts[index]);

		if ( f->predicate == -3 ) 
			return std::string( "GOAL-REACHED" );
		if ( f->predicate == -1 ) 
			return std::string( "=" );
		if ( f->predicate == -2 )
			return std::string( "!=" );
		return std::string( gpredicates[f->predicate] );
	}

	inline void get_types(std::vector<std::string> &types)
	{
		int i;
		for( i = 0; i < gnum_types; i++)
			types.push_back( std::string( gtype_names[i] ) );

		types.push_back("NO-TYPE");
	}

	inline void get_objects(std::vector<std::string> &objs, std::vector< std::vector< unsigned > > &objs_types)
	{
		int i,j;
		for( i = 0; i < gnum_constants; i++)
		{			
			objs.push_back( std::string( gconstants[i] ) );
			std::vector< unsigned > types;
			for( j = 0; j < gnum_types; j++)
				if(gis_member[i][j])
					types.push_back( j );
			objs_types.push_back(types);
		}

		objs.push_back("NO-OBJECT");
		std::vector< unsigned > types;
		types.push_back(0);
		types.push_back(1);
		types.push_back(2);
		objs_types.push_back(types);
		
		
	}


	inline void 		get_ft_pred_arg_list( int index, 
						      std::vector<std::string>& args )
	{
		Fact* f = &(grelevant_facts[index]);
		int j;

		if ( f->predicate == -3 ) return;
		if ( f->predicate == -1 || f->predicate == -2 )
		{
			for ( j = 0; j < 2; j++ )
			{
				if ( f->args[j] >= 0 )
					args.push_back( std::string(gconstants[(f->args)[j]]) ); 
				else
				{
					std::string arg_name( "x" );
					arg_name += DECODE_VAR( f->args[j] );
					args.push_back( arg_name );
				}
			}
			return;
		} 
		for ( j = 0; j < garity[f->predicate]; j++ )
		{
			if ( f->args[j] >= 0 )
				args.push_back( std::string(gconstants[(f->args)[j]]));
			else
			{
				std::string arg_name( "x" );
				arg_name += DECODE_VAR( f->args[j] );
				args.push_back( arg_name );
			}
		}
	}

	inline void 		get_ft_arg_list( int index, std::vector<unsigned>& args, 
						 std::vector<unsigned>& args_type )
	{
		Fact* f = &(grelevant_facts[index]);
		int j;

		if ( f->predicate == -3 ) return;
		if ( f->predicate == -1 || f->predicate == -2 )
		{
			for ( j = 0; j < 2; j++ )
			{
				if ( f->args[j] >= 0 )
					args.push_back( (f->args)[j] ); 
			
			}
			return;
		} 
		for ( j = 0; j < garity[f->predicate]; j++ )
		{
			if ( f->args[j] >= 0 )
			{
				args.push_back( (f->args)[j] );			
				args_type.push_back( gpredicates_args_type[ f->predicate ][ j ] );
			}
		}
	
	}

	inline std::string	get_ft_name( int index )
	{
		Fact* f = &(grelevant_facts[index]);
		int j;

		if ( f->predicate == -3 ) 
		{
			return std::string( "GOAL-REACHED" );
		}

		if ( f->predicate == -1 ) 
		{
			std::string str( "(=" );
			for ( j=0; j<2; j++ ) 
			{
				str += " ";
				if ( f->args[j] >= 0 ) 
				{
					str += gconstants[(f->args)[j]];
				} 
				else 
				{
					str += "x";
					str += DECODE_VAR( f->args[j] );
				}
			}
			str += ")";
			return str;
		}

		if ( f->predicate == -2 ) 
		{
			std::string str( "(!=" ); 
			for ( j=0; j<2; j++ ) 
			{
				str += " ";
				if ( f->args[j] >= 0 ) 
				{
					str += gconstants[(f->args)[j]];
				} 
				else 
				{
					str += "x";
					str += DECODE_VAR( f->args[j] );
				}
			}
			str += ")";
			return str;
		}
    
		std::string str( "(" );
		str += gpredicates[f->predicate];
		if (garity[f->predicate] > 0 )
			str += " ";
		for ( j=0; j<garity[f->predicate]; j++ ) 
		{
			if ( f->args[j] >= 0 ) 
			{
				str += gconstants[(f->args)[j]];
			} 
			else 
			{
				str += "x";
				str += DECODE_VAR( f->args[j] );
			}
			if ( j < garity[f->predicate] -1 )
				str += " ";
		}
		str += ")";	
		return str;
	}

}

#endif

#endif //libff.h
