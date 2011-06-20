#include "Test_FF_PDDL_To_STRIPS.hxx"
#include <planning/FF_PDDL_To_STRIPS.hxx>
#include <planning/STRIPS_Problem.hxx>

CPPUNIT_TEST_SUITE_REGISTRATION( Test_FF_PDDL_To_STRIPS );

void Test_FF_PDDL_To_STRIPS::setUp()
{
}

void Test_FF_PDDL_To_STRIPS::tearDown()
{
}

void Test_FF_PDDL_To_STRIPS::test_load_ok()
{
	aig_tk::FF_PDDL_To_STRIPS adl_compiler;
	aig_tk::STRIPS_Problem	  result;

	adl_compiler.get_problem_description( "domain-blocksaips.pddl",
						"blocksaips03.pddl",
						result );

	CPPUNIT_ASSERT_EQUAL( (unsigned)25, result.num_fluents() );
	CPPUNIT_ASSERT_EQUAL( (unsigned)32, result.num_actions() );
}
