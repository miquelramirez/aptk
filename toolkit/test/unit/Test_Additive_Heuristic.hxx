#ifndef __TEST_ADDITIVE_HEURISTIC__
#define __TEST_ADDITIVE_HEURISTIC__

#include <cppunit/extensions/HelperMacros.h>
#include <planning/STRIPS_Problem.hxx>

class Test_Additive_Heuristic : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( Test_Additive_Heuristic );
	CPPUNIT_TEST( test_correctness_1 );
	CPPUNIT_TEST_SUITE_END();
public:

	void	setUp();
	void	tearDown();

	void	test_correctness_1();

protected:
	aig_tk::STRIPS_Problem*		the_problem;

};


#endif // Test_Additive_Heuristic.hxx
