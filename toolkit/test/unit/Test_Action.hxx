#ifndef __ACTION_TEST__
#define __ACTION_TEST__

#include <cppunit/extensions/HelperMacros.h>
#include <planning/STRIPS_Problem.hxx>

namespace aig_tk
{
	class Action;
}

class Test_Action : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( Test_Action );
	CPPUNIT_TEST( test_default_constructor );
	CPPUNIT_TEST( test_make_action );
	CPPUNIT_TEST( test_applicable_yes );
	CPPUNIT_TEST( test_applicable_no );
	CPPUNIT_TEST( test_effect_interfering_yes );
	CPPUNIT_TEST( test_effect_interfering_no );
	CPPUNIT_TEST( test_deletes_precondition_yes );
	CPPUNIT_TEST( test_deletes_precondition_no );
	CPPUNIT_TEST( test_potential_supporter );
	CPPUNIT_TEST( test_consumes_fluent_yes );
	CPPUNIT_TEST( test_consumes_fluent_no );
	CPPUNIT_TEST_SUITE_END();

public:

	void	setUp();
	void 	tearDown();

	void	test_default_constructor();
	void	test_make_action();
	void	test_applicable_yes();
	void	test_applicable_no();
	void	test_effect_interfering_yes();
	void	test_effect_interfering_no();
	void	test_deletes_precondition_yes();
	void	test_deletes_precondition_no();
	void	test_potential_supporter();
	void	test_consumes_fluent_yes();
	void	test_consumes_fluent_no();

protected:

	aig_tk::Action&		action_A() { return *m_action_A; }
	aig_tk::Action&		action_B() { return *m_action_B; }
	aig_tk::Action&		action_C() { return *m_action_C; }
	aig_tk::Action&		action_D() { return *m_action_D; }

	aig_tk::STRIPS_Problem&	test_problem() { return *theProblem; }

	aig_tk::STRIPS_Problem*	theProblem;
	aig_tk::Action*		m_action_A;
	aig_tk::Action*		m_action_B;
	aig_tk::Action*		m_action_C;
	aig_tk::Action*		m_action_D;

};

#endif // action_test.hxx
