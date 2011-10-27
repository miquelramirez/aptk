#include <planning/FF_PDDL_To_STRIPS.hxx>
#include <planning/STRIPS_Problem.hxx>
#include <planning/Fluent.hxx>
#include <planning/Action.hxx>
#include <planning/PDDL_Type.hxx>
#include <planning/PDDL_Object.hxx>
#include <planning/PDDL_Operator.hxx>
#include <planning/heuristics/Max_Heuristic.hxx>
#include <planning/Types.hxx>
#include <planning/inference/Propagator.hxx>

#include <search/Node.hxx>
#include <search/Regression_Best_First_Search.hxx>

#include <util/time.hxx>
#include <util/ext_math.hxx>

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <algorithm>

void output_plan(aig_tk::Regression_Best_First_Search& engine, std::vector<aig_tk::Node*> plan, float pt, float ht, float st, float tt )
{
	aig_tk::Cost_Type plan_cost = 0;

	for ( unsigned k = 0; k < plan.size(); k++ )
	{
		aig_tk::Action* a = plan[k]->op(); 
		plan_cost = aig_tk::add( plan_cost, a->cost() );

	}

	std::cout << std::endl;
	std::cout << "================================================"<<std::endl;                                 
	std::cout << ";; SOLUTION " <<std::endl;
	std::cout << ";;\t Plan cost: " << std::fixed << plan_cost << ", steps: " << plan.size() << std::endl;
	std::cout << ";;\t Time: " << std::endl;
	std::cout << ";;\t\t Parsing: " << pt << std::endl;
	std::cout << ";;\t\t Heuristic: " << ht << std::endl;
	std::cout << ";;\t\t Search: " << st << std::endl;
	std::cout << std::endl<<"================================================"<<std::endl;                  

	for ( unsigned k = 0; k < plan.size(); k++ )
	{
		aig_tk::Action* a = plan[k]->op(); 
		std::cout<<k+1 << " - "<< a->signature()<<std::endl;
	}

               
}

int main( int argc, char** argv )
{
	if ( argc < 3 )
	{
		std::cerr << "No prob description provided, bailing out!" << std::endl;
		std::exit(1);
	}

	float tf, t0, initial_time, parsing_time, heuristic_time, search_time;
	initial_time = t0 = time_used();
	
	std::string domain( argv[1] );
	std::string instance( argv[2] );

	aig_tk::FF_PDDL_To_STRIPS adl_compiler;
	aig_tk::STRIPS_Problem	  strips_prob;

	/**
	 * PARSING
	 * Parser that creates the problem representation given a domain and an instance pddl file
	 */
	adl_compiler.get_problem_description( domain, instance, strips_prob, true  );
	tf = time_used();
	parsing_time = tf - t0;

	std::cout << std::endl;
	std::cout << "Actions: " << strips_prob.num_actions();
	std::cout << " Fluents: " << strips_prob.num_fluents() << std::endl;

	/**
	 * HEURISTIC EXAMPLE
	 */
	t0 = time_used();
	aig_tk::Max_Heuristic estimator;
        
	/**
	 * Initializing heuristic with the problem
	 */
	estimator.initialize( strips_prob );

        
	/**
	 * computing heuristic from the initial state
	 */        
	estimator.compute_without_supporters( strips_prob.init() );
	tf = time_used();
	heuristic_time = tf - t0;
                
	/**
	 * Evaluates h_max to a given set of fluents
	 */        
	aig_tk::Cost_Type goal_cost = estimator.eval( strips_prob.goal()  );
        
	std::cout << "Goal Distance is "<<goal_cost<<std::endl;
        

	/**
	 * SEARCH
	 **/
	t0 = time_used();
	aig_tk::Regression_Best_First_Search engine;
	engine.set_heuristic(estimator);
	engine.set_problem(strips_prob);
	
	aig_tk::Node* n0 = aig_tk::Node::root( strips_prob, true );
	std::vector< aig_tk::Node* > plan;
	

	if( engine.solve(n0, plan) )
	{
		tf = time_used();
		search_time = tf - t0;
		std::reverse( plan.begin(), plan.end() );
		output_plan( engine, plan, parsing_time, heuristic_time, search_time, tf - initial_time);
	}
	else
		std::cerr<<"FAILED"<<std::endl;

	std::exit(0);
	return 0;
}
