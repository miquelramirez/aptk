#ifndef __AIG_TK_STATE_TEST__
#define __AIG_TK_STATE_TEST__

#include <cppunit/extensions/HelperMacros.h>
#include <planning/STRIPS_Problem.hxx>

class Test_State : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( Test_State );
	CPPUNIT_TEST( test_constructor );
	CPPUNIT_TEST( test_entails_fluent );
	CPPUNIT_TEST( test_entails_fluent_vec );
	CPPUNIT_TEST( test_doesnt_entail_fluent_vec );
	CPPUNIT_TEST( test_progress_through_action );
	CPPUNIT_TEST( test_regress_through_action );
	CPPUNIT_TEST( test_progress_through_action_not_applicable );
	CPPUNIT_TEST( test_regress_through_action_not_applicable );
	CPPUNIT_TEST_SUITE_END();

public:

	void setUp();
	void tearDown();

	void test_constructor();
	void test_entails_fluent();
	void test_entails_fluent_vec();
	void test_doesnt_entail_fluent_vec();
	void test_progress_through_action();
	void test_regress_through_action();
	void test_progress_through_action_not_applicable();
	void test_regress_through_action_not_applicable();

protected:

	aig_tk::STRIPS_Problem&		test_problem()
	{
		return *theProblem;
	}

	aig_tk::STRIPS_Problem*		theProblem;

};

#endif // Test_State.hxx
