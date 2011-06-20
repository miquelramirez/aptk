#ifndef __CLOSED_LIST__
#define __CLOSED_LIST__

#include <util/hash_table.hxx>

namespace aig_tk
{

template <typename Node>
class Closed_List : public Hash_Table<Node>
{
public:
	Closed_List(unsigned table_size);
	~Closed_List();

	bool 	contains( Node n );
	void	insert( Node n );
};

template < typename Node >
Closed_List<Node>::Closed_List(unsigned table_size) :
  Hash_Table<Node>(table_size)
{
  
}

template < typename Node >
Closed_List<Node>::~Closed_List()
{
}

template < typename Node >
bool	Closed_List<Node>::contains( Node n )
{
	return get_element( n->hash(), n ) != NULL;
}

template < typename Node >
void	Closed_List<Node>::insert( Node n )
{
	if ( get_element( n->hash(), n ) != NULL ) return;
	add_element( n->hash(), n );	
}

}

#endif
