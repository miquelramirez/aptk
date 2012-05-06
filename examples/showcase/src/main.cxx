#include <planning/FF_PDDL_To_STRIPS.hxx>
#include <planning/STRIPS_Problem.hxx>
#include <planning/Fluent.hxx>
#include <planning/Action.hxx>
#include <planning/PDDL_Type.hxx>
#include <planning/PDDL_Object.hxx>
#include <planning/PDDL_Operator.hxx>
#include <planning/heuristics/Max_Heuristic.hxx>
#include <planning/heuristics/Relaxed_Plan_Extractor.hxx>
#include <planning/Types.hxx>
#include <planning/inference/Propagator.hxx>

#include <search/Node.hxx>
#include <search/Best_First_Search.hxx>

#include <util/time.hxx>
#include <util/ext_math.hxx>

#include <iostream>
#include <cstdlib>
#include <fstream>

void encode_as_text( aig_tk::STRIPS_Problem& prob, std::string destination )
{
	std::ofstream out_stream( destination.c_str() );


	/**
	 * Printing The Fluents of the problem. 
	 * Recall that all the information is accesible from STRIPS_Problem
	 */
	out_stream << "Types:"<<std::endl;
	for( unsigned i = 0; i < prob.num_types(); i++)
	{
		out_stream << "\t"<<prob.types()[i]->signature()<<std::endl;

		aig_tk::Fluent_Ptr_Vec fl_vec = prob.fluents_by_type( i );
		if( fl_vec.size() != 0)
		{
			out_stream << "\t\tFluents with this type"<<std::endl;	
			for( unsigned k = 0; k < fl_vec.size(); k++)
				out_stream<<"\t\t\t"<<fl_vec[ k ]->signature()<<std::endl;
		}
		out_stream << "\t\tObjects with this type"<<std::endl;
		aig_tk::PDDL_Object_Ptr_Vec obj_vec = prob.objects_by_type( i );
		for( unsigned k = 0; k < obj_vec.size(); k++)
			out_stream<<"\t\t\t"<<obj_vec[ k ]->signature()<<std::endl;
			
	}

	out_stream << "Objects:"<<std::endl;
	for( unsigned i = 0; i < prob.num_objects(); i++)
	{
		out_stream << "\t"<<prob.objects()[i]->signature()<<std::endl;
		out_stream << "\t\ttypes:"<<std::endl;

		aig_tk::Index_Vec& types_idx = prob.objects()[i]->types_idx();
		for( unsigned k = 0; k < types_idx.size(); k++)
			out_stream << "\t\t\t"<<prob.types()[ types_idx[k] ]->signature() << std::endl;
		
		out_stream << "\t\tFluents with this object"<<std::endl;
		aig_tk::Fluent_Ptr_Vec fl_vec = prob.fluents_by_object( i );
		for( unsigned k = 0; k < fl_vec.size(); k++)
			out_stream<<"\t\t\t"<<fl_vec[ k ]->signature()<<std::endl;
	}

	
	out_stream << "Fluents:"<<std::endl<<std::endl;
	for ( unsigned k = 0; k < prob.num_fluents(); k++ )
	{
		out_stream << "\t"<< prob.fluents()[k]->signature() << std::endl;	

		out_stream << "\t\tPredicate:"<<std::endl;
		out_stream << "\t\t\t"<< prob.fluents()[k]->predicate() << std::endl;	

		out_stream << "\t\tObjects - Types:"<<std::endl;
		aig_tk::Index_Vec obj_idxs = prob.fluents()[k]->pddl_objs_idx(); 
		aig_tk::Index_Vec types_idxs = prob.fluents()[k]->pddl_types_idx();       
		for( unsigned i = 0; i < obj_idxs.size(); i++)
			out_stream << "\t\t\t"<<prob.objects()[ obj_idxs[i] ]->signature() << " - "<< prob.types()[ types_idxs[i] ]->signature() <<std::endl;
		
	}


	/**
	 * Printing PDDL Abstract Operators of the problem. 
	 * Recall that all the information is accesible from STRIPS_Problem
	 */
	out_stream << "PDDL Operators:"<<std::endl<<std::endl;
	for ( unsigned k = 0; k < prob.num_pddl_ops(); k++ )
	{	
		aig_tk::PDDL_Operator* pddl_op = prob.pddl_ops()[k];
		out_stream << pddl_op->signature();
		out_stream << ":" << std::endl;

		out_stream << "\tBase Name:"<<std::endl;
		out_stream << "\t\t"<< pddl_op->name() << std::endl;	
		
		out_stream << "\tObjects - Types:"<<std::endl;
		aig_tk::Index_Vec types_idxs = pddl_op->pddl_types_idx();       
		for( unsigned i = 0; i < types_idxs.size(); i++)
			out_stream << "\t\t"<< pddl_op->args_name()[i] << " - "<< prob.types()[ types_idxs[i] ]->signature() <<std::endl;
		
		out_stream << "\t grounded actions:"<<std::endl;
		aig_tk::Action_Ptr_Vec a_vec = prob.actions_by_pddl_op( k );
		for(unsigned z = 0; z < a_vec.size(); z++)
			out_stream << "\t\t"<< a_vec[z]->signature()<<std::endl;
	}

	/**
	 * Printing the Actions of the problem. 
	 */
	out_stream << "Actions:"<<std::endl<<std::endl;
	for ( unsigned k = 0; k < prob.num_actions(); k++ )
	{
                
		aig_tk::Action* action = prob.actions()[k];
		out_stream << action->signature();


		/**
		 * Printing the precs adds and dels of the aciton
		 */
		out_stream << ":" << std::endl;

		out_stream << "\tBase Name:"<<std::endl;
		out_stream << "\t\t"<< prob.actions()[k]->name() << std::endl;	

		out_stream << "\tObjects - Types:"<<std::endl;
		aig_tk::Index_Vec obj_idxs = prob.actions()[k]->pddl_objs_idx(); 
		aig_tk::Index_Vec types_idxs = prob.actions()[k]->pddl_types_idx();       
		for( unsigned i = 0; i < obj_idxs.size(); i++)
			out_stream << "\t\t"<<prob.objects()[ obj_idxs[i] ]->signature() << " - "<< prob.types()[ types_idxs[i] ]->signature() <<std::endl;
		

		out_stream << "\t" << "Preconditions:" << std::endl;

		aig_tk::Fluent_Vec& precs = action->prec_vec();
		for ( unsigned j = 0; j < precs.size(); j++ )
		{
			unsigned p = precs[j];
			out_stream << "\t\t";
			out_stream << prob.fluents()[ p ]->signature() ;
			out_stream << std::endl;
		}

		out_stream << "\t" << "Adds:" << std::endl;

		aig_tk::Fluent_Vec& adds = action->add_vec();
		for ( unsigned j = 0; j < adds.size(); j++ )
		{
			unsigned p = adds[j];
			out_stream << "\t\t";
			out_stream << prob.fluents()[ p ]->signature() ;
			out_stream << std::endl;
		}

		out_stream << "\t" << "Deletes:" << std::endl;
		
		aig_tk::Fluent_Vec& dels = action->del_vec();
		for ( unsigned j = 0; j < dels.size(); j++ )
		{
			unsigned p = dels[j];
			out_stream << "\t\t";
			out_stream << prob.fluents()[ p ]->signature() ;
			out_stream << std::endl;
		}

		out_stream << std::endl;
	
		if( !action->ceff_vec().empty() )
		{
			out_stream << "\t" << action->ceff_vec().size() <<" Conditional Effects:" << std::endl;
			aig_tk::Conditional_Effect_Vec& ceffs = action->ceff_vec();
			for( unsigned k = 0; k < ceffs.size(); k++)
			{
				out_stream << "\t\t" << "Conditions:" << std::endl;	       
			
				aig_tk::Fluent_Vec& precs = ceffs[k]->prec_vec();
				for ( unsigned j = 0; j < precs.size(); j++ )
				{
					unsigned p = precs[j];
					out_stream << "\t\t\t";
					out_stream << prob.fluents()[ p ]->signature() ;
					out_stream << std::endl;
				}

				out_stream << "\t\t" << "Adds:" << std::endl;

				aig_tk::Fluent_Vec& adds = ceffs[k]->add_vec();
				for ( unsigned j = 0; j < adds.size(); j++ )
				{
					unsigned p = adds[j];
					out_stream << "\t\t\t";
					out_stream << prob.fluents()[ p ]->signature() ;
					out_stream << std::endl;
				}

				out_stream << "\t\t" << "Deletes:" << std::endl;
		
				aig_tk::Fluent_Vec& dels = ceffs[k]->del_vec();
				for ( unsigned j = 0; j < dels.size(); j++ )
				{
					unsigned p = dels[j];
					out_stream << "\t\t\t";
					out_stream << prob.fluents()[ p ]->signature() ;
					out_stream << std::endl;
				}
				out_stream << std::endl;
			}
		}
		out_stream << std::endl;

	}	

	/**
	 * Printing the Initial State of the problem. 
	 */
	out_stream << "Initial State:" << std::endl <<"\t";
	for ( unsigned k = 0; k < prob.init().size(); k++ )
	{
		unsigned p = prob.init()[k];
		out_stream << prob.fluents()[ p ]->signature();
		if ( k < prob.init().size() - 1 )
			out_stream << " ";
	}
	out_stream << std::endl << std::endl;

	/**
	 * Printing the Goal of the problem. 
	 */
	out_stream << "Goal:" << std::endl<<"\t";
	for ( unsigned k = 0; k < prob.goal().size(); k++ )
	{
		unsigned p = prob.goal()[k];                
		out_stream << prob.fluents()[ p ]->signature();
		if ( k < prob.goal().size() - 1 )
			out_stream << " ";
	}
	out_stream << std::endl;

	out_stream.close();
}

void print_h( aig_tk::STRIPS_Problem& strips_prob, aig_tk::Max_Heuristic& estimator )
{
	std::cout<<"----Operators----"<<std::endl;
	for ( unsigned k = 0; k < strips_prob.num_actions(); k++ )
	{
                
		aig_tk::Action* action = strips_prob.actions()[k];
		std::cout << "h_1( "<<action->signature();
		std::cout <<" ): "<< estimator.op_value( k )<<std::endl;                           
	  
	}

	std::cout<<"----FLUENTS----"<<std::endl;        
	for ( unsigned k = 0; k < strips_prob.num_fluents(); k++ )
	{
		aig_tk::Fluent* fluent = strips_prob.fluents()[k];
		std::cout << "h_1( "<<fluent->signature();
		std::cout <<" ): "<< estimator.fl_value( k )<<std::endl;                           
	  
	}

}

void print_something_from_rel_plan( aig_tk::Propagator< aig_tk::Max_Heuristic >& rel_plan )
{
        
	/**
	 * Get node 0 From the Fluent layer 0
	 */
	if( !rel_plan.fl_layer( 0 ).empty() )
	{
		aig_tk::Propagator_Node *n = rel_plan.graph()[ rel_plan.fl_layer( 0 ) [0] ];
		
		std::cout<< std::endl << "I'm the first fluent of layer 0: "<< n->Atom->signature() << std::endl;
	
        
		/**
		 * Print all the operators that need the fluent to be true (Children). All ops have node "n" as their parent
		 */
		for(unsigned z = 0; z < n->Children.size(); z++)
		{
			aig_tk::Propagator_Node* n2 = rel_plan.graph()[ n->Children[z] ];
			if(n2->Type == aig_tk::ACTION)
			{
				std::cout << "I'm the Operator "<< n2->Operator->signature();
				std::cout << " that needs Fluent "<< n->Atom->signature() << " to be true"<<std::endl;        
			}
		}
	}
}
void output_plan(std::vector<aig_tk::Node*> plan, float t0, float tf)
{
	aig_tk::Cost_Type plan_cost = 0;

	std::cout << std::endl;
	std::cout << "================================================"<<std::endl;                                 
	std::cout << ";; SOLUTION " <<std::endl;
	std::cout << ";;\t Plan cost: " << std::fixed << plan_cost << ", steps: " << plan.size() << std::endl;
	std::cout << ";;\t Time: ";
	report_interval(t0, tf, std::cout);
	std::cout << std::endl<<"================================================"<<std::endl;                  

	for ( unsigned k = 0; k < plan.size(); k++ )
	{
		aig_tk::Action* a = plan[k]->op(); 
		std::cout<<k+1 << " - "<< a->signature()<<std::endl;
		plan_cost = aig_tk::add( plan_cost, a->cost() );
	}

               
}

int main( int argc, char** argv )
{
	if ( argc < 3 )
	{
		std::cerr << "No prob description provided, bailing out!" << std::endl;
		std::exit(1);
	}

	std::string domain( argv[1] );
	std::string instance( argv[2] );

	aig_tk::FF_PDDL_To_STRIPS adl_compiler;
	aig_tk::STRIPS_Problem	  strips_prob;

	/**
	 * PARSING
	 * Parser that creates the problem representation given a domain and an instance pddl file
	 */
	adl_compiler.get_problem_description( domain, instance, strips_prob, true  );


	std::cout << std::endl;
	std::cout << "Actions: " << strips_prob.num_actions();
	std::cout << " Fluents: " << strips_prob.num_fluents() << std::endl;

	std::string txt_output_filename( "prob.txt.strips" );
	encode_as_text( strips_prob, txt_output_filename ); 
        
	/**
	 * HEURISTIC EXAMPLE
	 */

	aig_tk::Max_Heuristic estimator;
        
	/**
	 * Initializing heuristic with the problem
	 */
	estimator.initialize( strips_prob );

        
	/**
	 * computing heuristic from the initial state
	 */        
	estimator.compute( strips_prob.init() );

                
	/**
	 * Evaluates h_max to a given set of fluents
	 */        
	aig_tk::Cost_Type goal_cost = estimator.eval( strips_prob.goal()  );
        
	std::cout<<"Goal Distance is "<<goal_cost<<std::endl;
        

	/**
	 * Printing heuristic Costs
	 */
	print_h( strips_prob, estimator );
        
	/**
	 * RELAXED PLAN EXAMPLE
	 */
        
	/**
	 * call generator of initial search node
	 */
	aig_tk::Node* n0 = aig_tk::Node::root( strips_prob );
        
	/**
	 * Create a propagator that uses h_max
	 */
	aig_tk::Propagator< aig_tk::Max_Heuristic > rel_plan( strips_prob );
        
	/**
	 * builds relax plan
	 */
	rel_plan.build_propagation_graph( n0 );

	/**
	 * Prints Relax Plan
	 */
	rel_plan.print();
        
	print_something_from_rel_plan( rel_plan );
        
	/**
	 * EFFICIENT RELAXED PLAN EXTRACTOR
	 */
	
	aig_tk::Relaxed_Plan_Extractor< aig_tk::Max_Heuristic > h_ff;
	
	h_ff.initialize( strips_prob );
	
	unsigned  cost_rel_plan = h_ff.eval( strips_prob.init(), strips_prob.goal() );
	
	std::cout<<std::endl<<"Cost of Relaxed Plan: "<< cost_rel_plan << std::endl;
	
	/**
	 * SEARCH
	 **/

	aig_tk::Best_First_Search engine;        
        
	engine.set_heuristic(estimator);
	engine.set_problem(strips_prob);

	std::vector<aig_tk::Node*> plan;
	float t0, tf;

	t0 = time_used();

	if( engine.solve(n0, plan) )
	{
		tf = time_used();
		output_plan( plan, t0, tf);
	}

	plan.clear();
	n0 = aig_tk::Node::root( strips_prob );

	if( engine.solve(n0, plan) )
	{
		tf = time_used();
		output_plan( plan, t0, tf);
	}
	else
		std::cerr<<"FALLO"<<std::endl;

	std::exit(0);
	return 0;
}
