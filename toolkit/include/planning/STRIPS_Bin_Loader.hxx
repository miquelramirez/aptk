#ifndef __STRIPS_BIN_LOADER__
#define __STRIPS_BIN_LOADER__

#include <planning/STRIPS_Problem.hxx>

namespace aig_tk
{

class STRIPS_Bin_Loader
{
public:

	STRIPS_Bin_Loader();
	~STRIPS_Bin_Loader();

	void load_from( std::string location, STRIPS_Problem& prob );

};

}

#endif // STRIPS_Bin_Loader.hxx
