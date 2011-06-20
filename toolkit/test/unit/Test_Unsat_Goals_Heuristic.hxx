#ifndef __TEST_UNSAT_GOALS_HEURISTIC__
#define __TEST_UNSAT_GOALS_HEURISTIC__

#include <cppunit/extensions/HelperMacros.h>
#include <planning/STRIPS_Problem.hxx>

class Test_Unsat_Goals_Heuristic : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( Test_Unsat_Goals_Heuristic );
	CPPUNIT_TEST( test_correctness_1 );
	CPPUNIT_TEST_SUITE_END();

public:

	void	setUp();
	void	tearDown();

	void	test_correctness_1();

protected:

	aig_tk::STRIPS_Problem*		the_problem;	

};

#endif // Unsat_Goals_Heuristic.hxx
