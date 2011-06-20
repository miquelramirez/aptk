#include "Test_Max_Heuristic.hxx"
#include <planning/heuristics/Max_Heuristic.hxx>

CPPUNIT_TEST_SUITE_REGISTRATION( Test_Max_Heuristic );

void Test_Max_Heuristic::setUp()
{
	the_problem = new aig_tk::STRIPS_Problem();	

	unsigned p_idx = aig_tk::STRIPS_Problem::add_fluent( *the_problem, "(p)" );
	unsigned q_idx = aig_tk::STRIPS_Problem::add_fluent( *the_problem, "(q)" );
	unsigned r_idx = aig_tk::STRIPS_Problem::add_fluent( *the_problem, "(r)" );
	unsigned s_idx = aig_tk::STRIPS_Problem::add_fluent( *the_problem, "(s)" );
	unsigned t_idx = aig_tk::STRIPS_Problem::add_fluent( *the_problem, "(t)" );
	
	aig_tk::Fluent_Vec a1_pre;
	a1_pre.push_back( q_idx );
	aig_tk::Fluent_Vec a1_add;
	a1_add.push_back( r_idx );
	aig_tk::Fluent_Vec a1_del;
	a1_del.push_back( q_idx );

	aig_tk::STRIPS_Problem::add_action( *the_problem, "(a1)", a1_pre, a1_add, a1_del );	

	aig_tk::Fluent_Vec a2_pre;
	a2_pre.push_back( r_idx );
	a2_pre.push_back( p_idx );
	aig_tk::Fluent_Vec a2_add;
	a2_add.push_back( t_idx );
	aig_tk::Fluent_Vec a2_del;
	a2_del.push_back( r_idx );
	a2_del.push_back( p_idx );

	aig_tk::STRIPS_Problem::add_action( *the_problem, "(a2)", a2_pre, a2_add, a2_del );	

	aig_tk::Fluent_Vec a3_pre;
	a3_pre.push_back( q_idx );
	aig_tk::Fluent_Vec a3_add;
	a3_add.push_back( p_idx );
	aig_tk::Fluent_Vec a3_del;
	a3_del.push_back( q_idx );

	aig_tk::STRIPS_Problem::add_action( *the_problem, "(a3)", a3_pre, a3_add, a3_del );	

	aig_tk::Fluent_Vec a4_pre;
	a4_pre.push_back( p_idx );
	aig_tk::Fluent_Vec a4_add;
	a4_add.push_back( q_idx );
	aig_tk::Fluent_Vec a4_del;
	a4_del.push_back( p_idx );

	aig_tk::STRIPS_Problem::add_action( *the_problem, "(a4)", a4_pre, a4_add, a4_del );	

	aig_tk::Fluent_Vec a5_pre;
	a5_pre.push_back( t_idx );
	aig_tk::Fluent_Vec a5_add;
	a5_add.push_back( s_idx );
	aig_tk::Fluent_Vec a5_del;
	a5_del.push_back( t_idx );

	aig_tk::STRIPS_Problem::add_action( *the_problem, "(a5)", a5_pre, a5_add, a5_del );

	aig_tk::Fluent_Vec I;
	I.push_back( p_idx );
	
	aig_tk::STRIPS_Problem::set_init( *the_problem, I );
	
	aig_tk::Fluent_Vec G;
	G.push_back( s_idx );

	aig_tk::STRIPS_Problem::set_goal( *the_problem, G );

}

void Test_Max_Heuristic::tearDown()
{
	delete the_problem;
}

void Test_Max_Heuristic::test_correctness_1()
{

	aig_tk::Max_Heuristic	h;
	h.initialize( *the_problem );
	CPPUNIT_ASSERT_EQUAL( h.eval( the_problem->init(), the_problem->goal() ), (unsigned) 4 );
	
}
