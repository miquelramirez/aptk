#ifndef STRIPS_PROBLEM_TEST
#define STRIPS_PROBLEM_TEST

#include <cppunit/extensions/HelperMacros.h>

class Test_STRIPS_Problem : public CppUnit::TestFixture
{

	CPPUNIT_TEST_SUITE( Test_STRIPS_Problem );
	CPPUNIT_TEST( test_default_constructor );
	CPPUNIT_TEST( test_add_fluent_increases_fluent_count );
	CPPUNIT_TEST( test_add_action_increases_action_count );
	CPPUNIT_TEST( test_full_problem_builds_OK_fluent_set );
	CPPUNIT_TEST( test_full_problem_builds_OK_action_set );
	CPPUNIT_TEST( test_full_problem_builds_OK_initial_sit );
	CPPUNIT_TEST( test_full_problem_builds_OK_goal_sit );
	CPPUNIT_TEST( test_full_problem_builds_OK_adding_list );
	CPPUNIT_TEST( test_full_problem_builds_OK_deleting_list );
	CPPUNIT_TEST( test_full_problem_builds_OK_requiring_list );
	CPPUNIT_TEST_SUITE_END();

public:

	void setUp();
	void tearDown();

	void test_default_constructor();
	void test_add_fluent_increases_fluent_count();
	void test_add_action_increases_action_count();
	void test_full_problem_builds_OK_fluent_set();
	void test_full_problem_builds_OK_action_set();
	void test_full_problem_builds_OK_initial_sit();
	void test_full_problem_builds_OK_goal_sit();
	void test_full_problem_builds_OK_adding_list();
	void test_full_problem_builds_OK_deleting_list();
	void test_full_problem_builds_OK_requiring_list();
};

#endif // Test_STRIPS_Problem.hxx
