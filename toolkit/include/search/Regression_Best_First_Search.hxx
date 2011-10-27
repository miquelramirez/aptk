#ifndef __REGRESSION_BEST_FIRST_SEARCH__
#define __REGRESSION_BEST_FIRST_SEARCH__

#include <search/Best_First_Search.hxx>

namespace aig_tk
{

	class Regression_Best_First_Search : public Best_First_Search
	{
	protected:
	
		// MRJ: Overrides
		virtual	bool	isGoal( Node* candidate );
		virtual	void	process( Node* head );
		virtual	void	eval( Node* head );
	
	public:
		Regression_Best_First_Search(float w = 1, float z = 1, Heuristic *h = NULL, STRIPS_Problem* p = NULL) :
			Best_First_Search( w, z, h, p )
                {
                }

		virtual ~Regression_Best_First_Search();
	};

}

#endif
