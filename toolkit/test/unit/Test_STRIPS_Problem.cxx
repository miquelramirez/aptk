#include "Test_STRIPS_Problem.hxx"
#include <planning/Action.hxx>
#include <planning/STRIPS_Problem.hxx>

CPPUNIT_TEST_SUITE_REGISTRATION( Test_STRIPS_Problem );

void Test_STRIPS_Problem::setUp()
{
}

void Test_STRIPS_Problem::tearDown()
{
}

void Test_STRIPS_Problem::test_default_constructor()
{
	aig_tk::STRIPS_Problem prob;

	CPPUNIT_ASSERT_EQUAL( prob.num_fluents(), (unsigned)0 );
	CPPUNIT_ASSERT_EQUAL( prob.num_actions(), (unsigned)0 );
}

void Test_STRIPS_Problem::test_add_fluent_increases_fluent_count()
{
	aig_tk::STRIPS_Problem P;

	aig_tk::STRIPS_Problem::add_fluent( P, "(p)" );
	
	CPPUNIT_ASSERT_EQUAL( P.num_fluents(), (unsigned)1 );
}

void Test_STRIPS_Problem::test_add_action_increases_action_count()
{
	aig_tk::STRIPS_Problem P;

	unsigned q_idx = aig_tk::STRIPS_Problem::add_fluent( P, "(q)" );
	unsigned r_idx = aig_tk::STRIPS_Problem::add_fluent( P, "(r)" );

	aig_tk::Fluent_Vec a_pre;
	a_pre.push_back( q_idx );
	aig_tk::Fluent_Vec a_add;
	a_add.push_back( r_idx );
	aig_tk::Fluent_Vec a_del;
	a_del.push_back( q_idx );

	aig_tk::STRIPS_Problem::add_action( P, "(a1)", a_pre, a_add, a_del );	
	CPPUNIT_ASSERT_EQUAL( P.num_actions(), (unsigned)1 );
}

void Test_STRIPS_Problem::test_full_problem_builds_OK_fluent_set()
{
	aig_tk::STRIPS_Problem P;
	
	aig_tk::STRIPS_Problem::add_fluent( P, "(p)" );
	aig_tk::STRIPS_Problem::add_fluent( P, "(q)" );
	aig_tk::STRIPS_Problem::add_fluent( P, "(r)" );
	aig_tk::STRIPS_Problem::add_fluent( P, "(s)" );
	aig_tk::STRIPS_Problem::add_fluent( P, "(t)" );

	CPPUNIT_ASSERT_EQUAL( P.num_fluents(), (unsigned)5 );	
}

void Test_STRIPS_Problem::test_full_problem_builds_OK_action_set()
{
	aig_tk::STRIPS_Problem P;
	
	unsigned p_idx = aig_tk::STRIPS_Problem::add_fluent( P, "(p)" );
	unsigned q_idx = aig_tk::STRIPS_Problem::add_fluent( P, "(q)" );
	unsigned r_idx = aig_tk::STRIPS_Problem::add_fluent( P, "(r)" );
	unsigned s_idx = aig_tk::STRIPS_Problem::add_fluent( P, "(s)" );
	unsigned t_idx = aig_tk::STRIPS_Problem::add_fluent( P, "(t)" );
	
	aig_tk::Fluent_Vec a1_pre;
	a1_pre.push_back( q_idx );
	aig_tk::Fluent_Vec a1_add;
	a1_add.push_back( r_idx );
	aig_tk::Fluent_Vec a1_del;
	a1_del.push_back( q_idx );

	aig_tk::STRIPS_Problem::add_action( P, "(a1)", a1_pre, a1_add, a1_del );	

	aig_tk::Fluent_Vec a2_pre;
	aig_tk::Fluent_Vec a2_add;
	aig_tk::Fluent_Vec a2_del;

	aig_tk::STRIPS_Problem::add_action( P, "(a2)", a2_pre, a2_add, a2_del );	

	aig_tk::Fluent_Vec a3_pre;
	aig_tk::Fluent_Vec a3_add;
	aig_tk::Fluent_Vec a3_del;

	aig_tk::STRIPS_Problem::add_action( P, "(a3)", a3_pre, a3_add, a3_del );	

	aig_tk::Fluent_Vec a4_pre;
	aig_tk::Fluent_Vec a4_add;
	aig_tk::Fluent_Vec a4_del;

	aig_tk::STRIPS_Problem::add_action( P, "(a4)", a4_pre, a4_add, a4_del );	

	aig_tk::Fluent_Vec a5_pre;
	aig_tk::Fluent_Vec a5_add;
	aig_tk::Fluent_Vec a5_del;

	aig_tk::STRIPS_Problem::add_action( P, "(a5)", a5_pre, a5_add, a5_del );	
	
	CPPUNIT_ASSERT_EQUAL( P.num_actions(), (unsigned)5 );
}

void	Test_STRIPS_Problem::test_full_problem_builds_OK_initial_sit()
{
	aig_tk::STRIPS_Problem P;
	
	unsigned p_idx = aig_tk::STRIPS_Problem::add_fluent( P, "(p)" );
	unsigned q_idx = aig_tk::STRIPS_Problem::add_fluent( P, "(q)" );
	unsigned r_idx = aig_tk::STRIPS_Problem::add_fluent( P, "(r)" );
	unsigned s_idx = aig_tk::STRIPS_Problem::add_fluent( P, "(s)" );
	unsigned t_idx = aig_tk::STRIPS_Problem::add_fluent( P, "(t)" );
	
	aig_tk::Fluent_Vec a1_pre;
	a1_pre.push_back( q_idx );
	aig_tk::Fluent_Vec a1_add;
	a1_add.push_back( r_idx );
	aig_tk::Fluent_Vec a1_del;
	a1_del.push_back( q_idx );

	aig_tk::STRIPS_Problem::add_action( P, "(a1)", a1_pre, a1_add, a1_del );	

	aig_tk::Fluent_Vec a2_pre;
	aig_tk::Fluent_Vec a2_add;
	aig_tk::Fluent_Vec a2_del;

	aig_tk::STRIPS_Problem::add_action( P, "(a2)", a2_pre, a2_add, a2_del );	

	aig_tk::Fluent_Vec a3_pre;
	aig_tk::Fluent_Vec a3_add;
	aig_tk::Fluent_Vec a3_del;

	aig_tk::STRIPS_Problem::add_action( P, "(a3)", a3_pre, a3_add, a3_del );	

	aig_tk::Fluent_Vec a4_pre;
	aig_tk::Fluent_Vec a4_add;
	aig_tk::Fluent_Vec a4_del;

	aig_tk::STRIPS_Problem::add_action( P, "(a4)", a4_pre, a4_add, a4_del );	

	aig_tk::Fluent_Vec a5_pre;
	aig_tk::Fluent_Vec a5_add;
	aig_tk::Fluent_Vec a5_del;

	aig_tk::STRIPS_Problem::add_action( P, "(a5)", a5_pre, a5_add, a5_del );

	aig_tk::Fluent_Vec I;
	I.push_back( p_idx );

	aig_tk::STRIPS_Problem::set_init( P, I );

	CPPUNIT_ASSERT_EQUAL( P.init().size(), (unsigned)1 );
	CPPUNIT_ASSERT_EQUAL( P.init()[0], p_idx );
}

void Test_STRIPS_Problem::test_full_problem_builds_OK_goal_sit()
{
	aig_tk::STRIPS_Problem P;
	
	unsigned p_idx = aig_tk::STRIPS_Problem::add_fluent( P, "(p)" );
	unsigned q_idx = aig_tk::STRIPS_Problem::add_fluent( P, "(q)" );
	unsigned r_idx = aig_tk::STRIPS_Problem::add_fluent( P, "(r)" );
	unsigned s_idx = aig_tk::STRIPS_Problem::add_fluent( P, "(s)" );
	unsigned t_idx = aig_tk::STRIPS_Problem::add_fluent( P, "(t)" );
	
	aig_tk::Fluent_Vec a1_pre;
	a1_pre.push_back( q_idx );
	aig_tk::Fluent_Vec a1_add;
	a1_add.push_back( r_idx );
	aig_tk::Fluent_Vec a1_del;
	a1_del.push_back( q_idx );

	aig_tk::STRIPS_Problem::add_action( P, "(a1)", a1_pre, a1_add, a1_del );	

	aig_tk::Fluent_Vec a2_pre;
	aig_tk::Fluent_Vec a2_add;
	aig_tk::Fluent_Vec a2_del;

	aig_tk::STRIPS_Problem::add_action( P, "(a2)", a2_pre, a2_add, a2_del );	

	aig_tk::Fluent_Vec a3_pre;
	aig_tk::Fluent_Vec a3_add;
	aig_tk::Fluent_Vec a3_del;

	aig_tk::STRIPS_Problem::add_action( P, "(a3)", a3_pre, a3_add, a3_del );	

	aig_tk::Fluent_Vec a4_pre;
	aig_tk::Fluent_Vec a4_add;
	aig_tk::Fluent_Vec a4_del;

	aig_tk::STRIPS_Problem::add_action( P, "(a4)", a4_pre, a4_add, a4_del );	

	aig_tk::Fluent_Vec a5_pre;
	aig_tk::Fluent_Vec a5_add;
	aig_tk::Fluent_Vec a5_del;

	aig_tk::STRIPS_Problem::add_action( P, "(a5)", a5_pre, a5_add, a5_del );

	aig_tk::Fluent_Vec I;
	I.push_back( p_idx );
	
	aig_tk::STRIPS_Problem::set_init( P, I );
	
	aig_tk::Fluent_Vec G;
	G.push_back( s_idx );

	aig_tk::STRIPS_Problem::set_goal( P, G );

	CPPUNIT_ASSERT_EQUAL( P.goal().size(), (unsigned)1 );
	CPPUNIT_ASSERT_EQUAL( P.goal()[0], s_idx );
}

void Test_STRIPS_Problem::test_full_problem_builds_OK_adding_list()
{
	aig_tk::STRIPS_Problem P;
	
	unsigned p_idx = aig_tk::STRIPS_Problem::add_fluent( P, "(p)" );
	unsigned q_idx = aig_tk::STRIPS_Problem::add_fluent( P, "(q)" );
	unsigned r_idx = aig_tk::STRIPS_Problem::add_fluent( P, "(r)" );
	unsigned s_idx = aig_tk::STRIPS_Problem::add_fluent( P, "(s)" );
	unsigned t_idx = aig_tk::STRIPS_Problem::add_fluent( P, "(t)" );
	
	aig_tk::Fluent_Vec a1_pre;
	a1_pre.push_back( q_idx );
	aig_tk::Fluent_Vec a1_add;
	a1_add.push_back( r_idx );
	aig_tk::Fluent_Vec a1_del;
	a1_del.push_back( q_idx );

	unsigned a1_idx = aig_tk::STRIPS_Problem::add_action( P, "(a1)", a1_pre, a1_add, a1_del );	

	aig_tk::Fluent_Vec a2_pre;
	aig_tk::Fluent_Vec a2_add;
	a2_add.push_back( t_idx );
	aig_tk::Fluent_Vec a2_del;

	unsigned a2_idx = aig_tk::STRIPS_Problem::add_action( P, "(a2)", a2_pre, a2_add, a2_del );	

	aig_tk::Fluent_Vec a3_pre;
	aig_tk::Fluent_Vec a3_add;
	a3_add.push_back( p_idx );
	aig_tk::Fluent_Vec a3_del;

	unsigned a3_idx = aig_tk::STRIPS_Problem::add_action( P, "(a3)", a3_pre, a3_add, a3_del );	

	aig_tk::Fluent_Vec a4_pre;
	aig_tk::Fluent_Vec a4_add;
	a4_add.push_back( q_idx );
	aig_tk::Fluent_Vec a4_del;

	unsigned a4_idx = aig_tk::STRIPS_Problem::add_action( P, "(a4)", a4_pre, a4_add, a4_del );	

	aig_tk::Fluent_Vec a5_pre;
	aig_tk::Fluent_Vec a5_add;
	a5_add.push_back( s_idx );
	aig_tk::Fluent_Vec a5_del;

	unsigned a5_idx = aig_tk::STRIPS_Problem::add_action( P, "(a5)", a5_pre, a5_add, a5_del );

	aig_tk::Fluent_Vec I;
	I.push_back( p_idx );
	
	aig_tk::STRIPS_Problem::set_init( P, I );
	
	aig_tk::Fluent_Vec G;
	G.push_back( s_idx );

	aig_tk::STRIPS_Problem::set_goal( P, G );

	CPPUNIT_ASSERT_EQUAL( P.actions_adding(p_idx).size(), (unsigned)1 );
	CPPUNIT_ASSERT_EQUAL( P.actions_adding(p_idx)[0]->signature(), std::string("(a3)") );	
}

void	Test_STRIPS_Problem::test_full_problem_builds_OK_deleting_list()
{
	aig_tk::STRIPS_Problem P;
	
	unsigned p_idx = aig_tk::STRIPS_Problem::add_fluent( P, "(p)" );
	unsigned q_idx = aig_tk::STRIPS_Problem::add_fluent( P, "(q)" );
	unsigned r_idx = aig_tk::STRIPS_Problem::add_fluent( P, "(r)" );
	unsigned s_idx = aig_tk::STRIPS_Problem::add_fluent( P, "(s)" );
	unsigned t_idx = aig_tk::STRIPS_Problem::add_fluent( P, "(t)" );
	
	aig_tk::Fluent_Vec a1_pre;
	a1_pre.push_back( q_idx );
	aig_tk::Fluent_Vec a1_add;
	a1_add.push_back( r_idx );
	aig_tk::Fluent_Vec a1_del;
	a1_del.push_back( q_idx );

	unsigned a1_idx = aig_tk::STRIPS_Problem::add_action( P, "(a1)", a1_pre, a1_add, a1_del );	

	aig_tk::Fluent_Vec a2_pre;
	a2_pre.push_back( r_idx );
	a2_pre.push_back( p_idx );
	aig_tk::Fluent_Vec a2_add;
	a2_add.push_back( t_idx );
	aig_tk::Fluent_Vec a2_del;
	a2_del.push_back( r_idx );
	a2_del.push_back( p_idx );

	unsigned a2_idx = aig_tk::STRIPS_Problem::add_action( P, "(a2)", a2_pre, a2_add, a2_del );	

	aig_tk::Fluent_Vec a3_pre;
	a3_pre.push_back( q_idx );
	aig_tk::Fluent_Vec a3_add;
	a3_add.push_back( p_idx );
	aig_tk::Fluent_Vec a3_del;
	a3_del.push_back( q_idx );

	unsigned a3_idx = aig_tk::STRIPS_Problem::add_action( P, "(a3)", a3_pre, a3_add, a3_del );	

	aig_tk::Fluent_Vec a4_pre;
	a4_pre.push_back( p_idx );
	aig_tk::Fluent_Vec a4_add;
	a4_add.push_back( q_idx );
	aig_tk::Fluent_Vec a4_del;
	a4_del.push_back( p_idx );

	unsigned a4_idx = aig_tk::STRIPS_Problem::add_action( P, "(a4)", a4_pre, a4_add, a4_del );	

	aig_tk::Fluent_Vec a5_pre;
	a5_pre.push_back( t_idx );
	aig_tk::Fluent_Vec a5_add;
	a5_add.push_back( s_idx );
	aig_tk::Fluent_Vec a5_del;
	a5_del.push_back( t_idx );

	unsigned a5_idx = aig_tk::STRIPS_Problem::add_action( P, "(a5)", a5_pre, a5_add, a5_del );

	aig_tk::Fluent_Vec I;
	I.push_back( p_idx );
	
	aig_tk::STRIPS_Problem::set_init( P, I );
	
	aig_tk::Fluent_Vec G;
	G.push_back( s_idx );

	aig_tk::STRIPS_Problem::set_goal( P, G );

	CPPUNIT_ASSERT_EQUAL( (unsigned)1, P.actions_deleting(r_idx).size() );
	CPPUNIT_ASSERT_EQUAL( std::string("(a2)"),  P.actions_deleting(r_idx)[0]->signature() );		
}

void	Test_STRIPS_Problem::test_full_problem_builds_OK_requiring_list()
{
	aig_tk::STRIPS_Problem P;
	
	unsigned p_idx = aig_tk::STRIPS_Problem::add_fluent( P, "(p)" );
	unsigned q_idx = aig_tk::STRIPS_Problem::add_fluent( P, "(q)" );
	unsigned r_idx = aig_tk::STRIPS_Problem::add_fluent( P, "(r)" );
	unsigned s_idx = aig_tk::STRIPS_Problem::add_fluent( P, "(s)" );
	unsigned t_idx = aig_tk::STRIPS_Problem::add_fluent( P, "(t)" );
	
	aig_tk::Fluent_Vec a1_pre;
	a1_pre.push_back( q_idx );
	aig_tk::Fluent_Vec a1_add;
	a1_add.push_back( r_idx );
	aig_tk::Fluent_Vec a1_del;
	a1_del.push_back( q_idx );

	unsigned a1_idx = aig_tk::STRIPS_Problem::add_action( P, "(a1)", a1_pre, a1_add, a1_del );	

	aig_tk::Fluent_Vec a2_pre;
	a2_pre.push_back( r_idx );
	a2_pre.push_back( p_idx );
	aig_tk::Fluent_Vec a2_add;
	a2_add.push_back( t_idx );
	aig_tk::Fluent_Vec a2_del;
	a2_del.push_back( r_idx );
	a2_del.push_back( p_idx );

	unsigned a2_idx = aig_tk::STRIPS_Problem::add_action( P, "(a2)", a2_pre, a2_add, a2_del );	

	aig_tk::Fluent_Vec a3_pre;
	a3_pre.push_back( q_idx );
	aig_tk::Fluent_Vec a3_add;
	a3_add.push_back( p_idx );
	aig_tk::Fluent_Vec a3_del;
	a3_del.push_back( q_idx );

	unsigned a3_idx = aig_tk::STRIPS_Problem::add_action( P, "(a3)", a3_pre, a3_add, a3_del );	

	aig_tk::Fluent_Vec a4_pre;
	a4_pre.push_back( p_idx );
	aig_tk::Fluent_Vec a4_add;
	a4_add.push_back( q_idx );
	aig_tk::Fluent_Vec a4_del;
	a4_del.push_back( p_idx );

	unsigned a4_idx = aig_tk::STRIPS_Problem::add_action( P, "(a4)", a4_pre, a4_add, a4_del );	

	aig_tk::Fluent_Vec a5_pre;
	a5_pre.push_back( t_idx );
	aig_tk::Fluent_Vec a5_add;
	a5_add.push_back( s_idx );
	aig_tk::Fluent_Vec a5_del;
	a5_del.push_back( t_idx );

	unsigned a5_idx = aig_tk::STRIPS_Problem::add_action( P, "(a5)", a5_pre, a5_add, a5_del );

	aig_tk::Fluent_Vec I;
	I.push_back( p_idx );
	
	aig_tk::STRIPS_Problem::set_init( P, I );
	
	aig_tk::Fluent_Vec G;
	G.push_back( s_idx );

	aig_tk::STRIPS_Problem::set_goal( P, G );

	CPPUNIT_ASSERT_EQUAL( (unsigned)1, P.actions_requiring(r_idx).size() );
	CPPUNIT_ASSERT_EQUAL( std::string("(a2)"),  P.actions_requiring(r_idx)[0]->signature() );		
}
