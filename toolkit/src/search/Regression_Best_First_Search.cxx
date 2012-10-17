#include <search/Regression_Best_First_Search.hxx>

namespace aig_tk
{

	Regression_Best_First_Search::~Regression_Best_First_Search()
	{
	}

	bool	Regression_Best_First_Search::isGoal( Node* candidate )
	{

		for(unsigned i = 0; i < candidate->s()->fluent_vec().size(); i++)
			if( ! problem().is_in_init( candidate->s()->fluent_vec()[ i ] ) )
				return false;

		return true;
	} 

	void	Regression_Best_First_Search::eval( Node* n )
	{
                n->hn() = heuristic().eval( n->s()->fluent_vec() );
		setFn(n);		
	}

	void	Regression_Best_First_Search::process( Node* head )
	{
		for(unsigned i = 0; i < problem().num_actions(); i++) 
		{
			Action* a = problem().actions()[i];
			if( a->can_be_applied_on( *( head->s() ), true ) ) 
			{
				Node *suc = head->successor(a, true);
				Hash_Key& h = suc->hash();
				if(previously_hashed(suc, h)) 
				{
					delete suc;
				}
				else {
					openNode(suc, h, m_open);
				}
			}
		}
                m_expand_count++;
	} 
}
