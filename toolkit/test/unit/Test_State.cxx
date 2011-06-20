#include "Test_State.hxx"
#include <planning/State.hxx>
#include <planning/Action.hxx>

CPPUNIT_TEST_SUITE_REGISTRATION( Test_State );

void Test_State::setUp()
{
	theProblem = new aig_tk::STRIPS_Problem;
	theProblem->set_num_fluents( 8 );
	theProblem->set_num_actions( 8 );
}

void Test_State::tearDown()
{
	delete theProblem;
}

void Test_State::test_constructor()
{
	aig_tk::State s( test_problem() );

	CPPUNIT_ASSERT_EQUAL( s.fluent_vec().size(), test_problem().num_fluents() );

}

void Test_State::test_entails_fluent()
{
	aig_tk::State s( test_problem() );
	s.set( 3 );
	
	CPPUNIT_ASSERT_EQUAL( s.entails( 3 ), true );
}

void Test_State::test_entails_fluent_vec()
{
	aig_tk::State s( test_problem() );
	aig_tk::Fluent_Vec I;
	I.push_back( 3 ); I.push_back( 4 ); I.push_back( 7 );
	s.set(I);
	
	aig_tk::Fluent_Vec P;
	P.push_back( 3 ); P.push_back( 4 ); P.push_back( 7 );

	CPPUNIT_ASSERT_MESSAGE( "State should entail fluent set P", s.entails(P) );	
}

void Test_State::test_doesnt_entail_fluent_vec()
{
	aig_tk::State s( test_problem() );
	aig_tk::Fluent_Vec I;
	I.push_back( 3 ); I.push_back( 4 ); I.push_back( 7 );
	s.set(I);
	
	aig_tk::Fluent_Vec P;
	P.push_back( 3 ); P.push_back( 4 ); P.push_back( 8 );

	CPPUNIT_ASSERT_MESSAGE( "State shouldn't entail fluent set P", !s.entails(P) );
	unsigned num_unsat = 0;
	s.entails( P, num_unsat );
	CPPUNIT_ASSERT_EQUAL_MESSAGE( "Number of not entailed fluents should be 1", num_unsat, (unsigned)1 );
}

void Test_State::test_progress_through_action()
{
	aig_tk::Action test_a( test_problem() );
	aig_tk::Fluent_Vec test_a_precs;
	test_a_precs.push_back( 2 );
	aig_tk::Fluent_Vec test_a_adds;
	test_a_adds.push_back( 3 );
	aig_tk::Fluent_Vec test_a_dels;
	test_a_dels.push_back( 2 );
	test_a.define( test_a_precs, test_a_adds, test_a_dels );

	aig_tk::State test_s( test_problem() );
	test_s.set(2);

	aig_tk::State* succ = test_s.progress_through( test_a );
	
	CPPUNIT_ASSERT_MESSAGE( "Successor shouldn't be NULL", succ != NULL );
	CPPUNIT_ASSERT_MESSAGE( "Atom 3 should be true in the state", succ->entails( 3 ) );
	CPPUNIT_ASSERT_MESSAGE( "Atom 2 shouldn't be true in the state", !succ->entails( 2 ) );
}

void Test_State::test_regress_through_action()
{
	aig_tk::Action test_a( test_problem() );
	aig_tk::Fluent_Vec test_a_precs;
	test_a_precs.push_back( 2 );
	aig_tk::Fluent_Vec test_a_adds;
	test_a_adds.push_back( 3 );
	aig_tk::Fluent_Vec test_a_dels;
	test_a_dels.push_back( 2 );
	test_a.define( test_a_precs, test_a_adds, test_a_dels );

	aig_tk::State test_s( test_problem() );
	test_s.set(3);

	aig_tk::State* succ = test_s.regress_through( test_a );
	
	CPPUNIT_ASSERT_MESSAGE( "Successor shouldn't be NULL", succ != NULL );
	CPPUNIT_ASSERT_MESSAGE( "Atom 2 should be true in the state", succ->entails( 2 ) );
	CPPUNIT_ASSERT_MESSAGE( "Atom 3 shouldn't be true in the state", !succ->entails( 3 ) );
}

void Test_State::test_progress_through_action_not_applicable()
{
	aig_tk::Action test_a( test_problem() );
	aig_tk::Fluent_Vec test_a_precs;
	test_a_precs.push_back( 2 );
	aig_tk::Fluent_Vec test_a_adds;
	test_a_adds.push_back( 3 );
	aig_tk::Fluent_Vec test_a_dels;
	test_a_dels.push_back( 2 );
	test_a.define( test_a_precs, test_a_adds, test_a_dels );

	aig_tk::State test_s( test_problem() );
	test_s.set(4);

	aig_tk::State* succ = test_s.progress_through( test_a );
	
	CPPUNIT_ASSERT_MESSAGE( "Successor should be NULL", succ == NULL );
}

void Test_State::test_regress_through_action_not_applicable()
{
	aig_tk::Action test_a( test_problem() );
	aig_tk::Fluent_Vec test_a_precs;
	test_a_precs.push_back( 2 );
	aig_tk::Fluent_Vec test_a_adds;
	test_a_adds.push_back( 3 );
	aig_tk::Fluent_Vec test_a_dels;
	test_a_dels.push_back( 2 );
	test_a.define( test_a_precs, test_a_adds, test_a_dels );

	aig_tk::State test_s( test_problem() );
	test_s.set(2);

	aig_tk::State* succ = test_s.regress_through( test_a );
	
	CPPUNIT_ASSERT_MESSAGE( "Successor should be NULL", succ == NULL );
}
