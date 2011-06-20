#include "Test_Action.hxx"
#include <cppunit/TestAssert.h>
#include <planning/Action.hxx>
#include <planning/State.hxx>

CPPUNIT_TEST_SUITE_REGISTRATION( Test_Action );

void Test_Action::setUp()
{
	theProblem = new aig_tk::STRIPS_Problem;
	theProblem->set_num_fluents( 8 );
	theProblem->set_num_actions( 8 );

	// make action a: p -> q, ~p
	aig_tk::Fluent_Vec	a_pre;
	a_pre.push_back(0);
	aig_tk::Fluent_Vec	a_adds;
	a_adds.push_back(1);
	aig_tk::Fluent_Vec	a_dels;
	a_dels.push_back(0);
	m_action_A = new aig_tk::Action( test_problem() );
	m_action_A->define( a_pre, a_adds, a_dels );

	// make action b: q -> r, ~s
	aig_tk::Fluent_Vec	b_pre;
	b_pre.push_back( 1 );
	aig_tk::Fluent_Vec	b_adds;
	b_adds.push_back( 2 );
	aig_tk::Fluent_Vec	b_dels;
	b_dels.push_back( 3 );
	m_action_B = new aig_tk::Action( test_problem() );
	m_action_B->define( b_pre, b_adds, b_dels );

	// make action c: q -> s, ~q
	aig_tk::Fluent_Vec	c_pre;
	c_pre.push_back( 1 );
	aig_tk::Fluent_Vec	c_adds;
	c_adds.push_back( 3 );
	aig_tk::Fluent_Vec	c_dels;
	c_dels.push_back( 1 );
	m_action_C = new aig_tk::Action( test_problem() );
	m_action_C->define( c_pre, c_adds, c_dels );

	// make action d: s -> t, ~s
	aig_tk::Fluent_Vec	d_pre;
	d_pre.push_back( 3 );
	aig_tk::Fluent_Vec	d_adds;
	d_adds.push_back( 4 );
	aig_tk::Fluent_Vec	d_dels;
	d_dels.push_back( 3 );
	m_action_D = new aig_tk::Action( test_problem() );
	m_action_D->define( d_pre, d_adds, d_dels );
}

void Test_Action::tearDown()
{
	delete theProblem;
	delete m_action_A;
	delete m_action_B;
	delete m_action_C;
	delete m_action_D;
}

void Test_Action::test_default_constructor()
{
	aig_tk::Action	a(test_problem());

	CPPUNIT_ASSERT_EQUAL( a.prec_vec().size(), (unsigned)0 );
	CPPUNIT_ASSERT_EQUAL( a.add_vec().size(), (unsigned)0 );
	CPPUNIT_ASSERT_EQUAL( a.del_vec().size(), (unsigned)0 );
}

void Test_Action::test_make_action()
{
	aig_tk::Action	a(test_problem());

	aig_tk::Fluent_Vec precs;
	precs.push_back( 3 );
	precs.push_back( 5 );
	aig_tk::Fluent_Vec adds;
	adds.push_back( 7 );
	aig_tk::Fluent_Vec dels;
	dels.push_back( 3 );
	dels.push_back( 5 );	

	a.define( precs, adds, dels );

	CPPUNIT_ASSERT_EQUAL_MESSAGE( "Action should require 2 fluents", a.prec_vec().size(), (unsigned)2 );
	CPPUNIT_ASSERT_MESSAGE( "Action should be requiring fluent #3", a.requires(3) );
	CPPUNIT_ASSERT_MESSAGE( "Action should be requiring fluent #5", a.requires(5) );
	CPPUNIT_ASSERT_EQUAL_MESSAGE( "Action should assert 1 fluent", a.add_vec().size(), (unsigned)1 );
	CPPUNIT_ASSERT_MESSAGE( "Action should be asserting fluent #7", a.asserts(7) );
	CPPUNIT_ASSERT_EQUAL_MESSAGE( "Action should be retracting 2 fluents", a.del_vec().size(), (unsigned)2 );
	CPPUNIT_ASSERT_MESSAGE( "Action should be retracting fluent #3", a.retracts(3) );
	CPPUNIT_ASSERT_MESSAGE( "Action should be retracting fluent #5", a.retracts(5) );

}

void	Test_Action::test_applicable_yes()
{
	aig_tk::State	s( test_problem() );
	s.set(1); s.set(2); s.set(3); s.set(4);
	aig_tk::Action	a( test_problem() );
	aig_tk::Fluent_Vec precs, adds, dels;
	precs.push_back(1); precs.push_back(2);
	adds.push_back(5);
	dels.push_back(1); dels.push_back(2);
	a.define( precs, adds, dels );
	
	CPPUNIT_ASSERT_MESSAGE( "Action should be applicable", a.can_be_applied_on( s ) );	
}

void	Test_Action::test_applicable_no()
{
	aig_tk::State	s( test_problem() );
	s.set(1); s.set(2); s.set(3); s.set(4);
	aig_tk::Action	a( test_problem() );
	aig_tk::Fluent_Vec prec, adds, dels;
	prec.push_back(1); prec.push_back(6);
	adds.push_back(5);
	dels.push_back(1); dels.push_back(2);
	a.define( prec, adds, dels );
	
	CPPUNIT_ASSERT_MESSAGE( "Action should not be applicable", !a.can_be_applied_on( s ) );	
}

void Test_Action::test_effect_interfering_yes()
{
	CPPUNIT_ASSERT_MESSAGE( "Actions b and c should be effect interfering",
				aig_tk::Action::are_effect_interfering( action_B(), action_C() ) );
}

void Test_Action::test_effect_interfering_no()
{
	CPPUNIT_ASSERT_MESSAGE( "Actions a and b shoudn't be effect interfering",
				!aig_tk::Action::are_effect_interfering( action_A(), action_B() ) );
}

void Test_Action::test_deletes_precondition_yes()
{
	CPPUNIT_ASSERT_MESSAGE( "Action b is deleting precondition of action d",
				aig_tk::Action::deletes_precondition_of( action_B(), action_D() ) );
}

void Test_Action::test_deletes_precondition_no()
{
	CPPUNIT_ASSERT_MESSAGE( "Action d is not deleting precondition of action a",
				!aig_tk::Action::deletes_precondition_of( action_D(), action_A() ) );
}

void Test_Action::test_potential_supporter()
{
	aig_tk::Fluent_Vec	sp;
	aig_tk::Action::possible_supporter( action_A(), action_B(), sp );

	CPPUNIT_ASSERT_EQUAL_MESSAGE( "a adds one precondition of b",
				sp.size(), (unsigned)1 );
	CPPUNIT_ASSERT_EQUAL_MESSAGE( "the atom involved in the causal link is q",
				sp[0], (unsigned)1 );
}

void Test_Action::test_consumes_fluent_yes()
{
	CPPUNIT_ASSERT_MESSAGE( "Action a consumes fluent p",
				action_A().consumes(0) );
}

void Test_Action::test_consumes_fluent_no()
{
	CPPUNIT_ASSERT_MESSAGE( "Action b does not consume fluent q",
				!action_B().consumes(1) );
}
