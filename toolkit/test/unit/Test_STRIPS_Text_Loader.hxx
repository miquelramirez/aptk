#ifndef __TEST_STRIPS_TEXT_LOADER__
#define __TEST_STRIPS_TEXT_LOADER__

#include <cppunit/extensions/HelperMacros.h>
#include <planning/STRIPS_Text_Loader.hxx>

class Test_STRIPS_Text_Loader : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( Test_STRIPS_Text_Loader );
	CPPUNIT_TEST( test_fluents_load_ok );
	CPPUNIT_TEST_SUITE_END();

public:
	
	void setUp();
	void tearDown();
	void test_fluents_load_ok();

};

#endif // Test_STRIPS_Text_Loader.hxx
