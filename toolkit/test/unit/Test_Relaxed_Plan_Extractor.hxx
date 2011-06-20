#ifndef __TEST_RELAXED_PLAN_EXTRACTOR__
#define __TEST_RELAXED_PLAN_EXTRACTOR__

#include <cppunit/extensions/HelperMacros.h>
#include <planning/STRIPS_Problem.hxx>

class Test_Relaxed_Plan_Extractor : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( Test_Relaxed_Plan_Extractor );
	CPPUNIT_TEST( test_correctness_max_heuristic );
	CPPUNIT_TEST( test_correctness_additive_heuristic );
	CPPUNIT_TEST_SUITE_END();

public:

	void 	setUp();
	void	tearDown();

	void	test_correctness_max_heuristic();
	void	test_correctness_additive_heuristic();

protected:
	aig_tk::STRIPS_Problem*		the_problem;
};

#endif // Test_Relaxed_Plan_Extractor.hxx
