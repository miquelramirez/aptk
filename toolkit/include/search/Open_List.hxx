#ifndef __OPEN_LIST__
#define __OPEN_LIST__

#include <vector>
#include <queue>
#include <planning/Types.hxx>

namespace aig_tk
{
            
template < class Node_Comp, class Node_Ptr >
class Open_List
{

        std::priority_queue< Node_Ptr, std::vector< Node_Ptr >, Node_Comp > m_queue;
	//std::priority< Node_Ptr, std::vector< Node_Ptr >, Node_Comp > m_queue;
public:
	Open_List();
	~Open_List();

	void 		insert( Node_Ptr );
	Node_Ptr 	pop();
	bool		empty() const;
	Cost_Type	min() const;
	void		clear();
};

template < class Node_Comp, class Node_Ptr >
Open_List<Node_Comp, Node_Ptr>::Open_List()
{
}

template < typename Node_Comp, typename Node_Ptr >
Open_List<Node_Comp, Node_Ptr>::~Open_List()
{
}

template < typename Node_Comp, typename Node_Ptr >
void	Open_List<Node_Comp, Node_Ptr>::insert( Node_Ptr n )
{
	m_queue.push( n );
}

template <typename Node_Comp, typename Node_Ptr >
Node_Ptr	Open_List<Node_Comp, Node_Ptr>::pop()
{
        if( empty() ) return NULL;
	Node_Ptr elem = m_queue.top();
	m_queue.pop();
	return elem;
}

template < typename Node_Comp, typename Node_Ptr >
bool	Open_List<Node_Comp, Node_Ptr>::empty() const
{
	return m_queue.empty();
}

template < typename Node_Comp, typename Node_Ptr >
Cost_Type     Open_List<Node_Comp, Node_Ptr>::min() const
{
	if ( empty() ) return 0.0f;
	return m_queue.top()->f;
}

template < typename Node_Comp, typename Node_Ptr >
void	Open_List<Node_Comp, Node_Ptr>::clear() 
{
	while ( !empty() )
	{
		Node_Ptr elem = pop();
		delete elem;
	}	
}


}

#endif // Open_List.hxx
