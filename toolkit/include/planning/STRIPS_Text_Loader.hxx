#ifndef __STRIPS_TEXT_LOADER__
#define __STRIPS_TEXT_LOADER__

#include <planning/STRIPS_Problem.hxx>

namespace aig_tk
{

class STRIPS_Text_Loader
{
public:

	STRIPS_Text_Loader();
	~STRIPS_Text_Loader();

	void load_from( std::string location, STRIPS_Problem& prob );

};

}

#endif // STRIPS_Text_Loader.hxx
