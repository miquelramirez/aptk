#ifndef __TEST_FF_PDDL_TO_STRIPS__
#define __TEST_FF_PDDL_TO_STRIPS__

#include <cppunit/extensions/HelperMacros.h>
#include <planning/FF_PDDL_To_STRIPS.hxx>

class Test_FF_PDDL_To_STRIPS : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( Test_FF_PDDL_To_STRIPS );
	CPPUNIT_TEST( test_load_ok );
	CPPUNIT_TEST_SUITE_END();

public:
	void	setUp();
	void	tearDown();
	void 	test_load_ok();

};

#endif // Test_FF_PDDL_To_STRIPS.hxx
