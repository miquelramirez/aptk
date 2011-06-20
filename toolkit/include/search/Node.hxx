#ifndef __NODE__
#define __NODE__

#include <planning/State.hxx>
#include <planning/Action.hxx> 
#include <planning/Types.hxx>
#include <util/hash_table.hxx>

#include <iostream>
#include <cstdlib>

namespace aig_tk
{

  class Node
  {
  public:

    static unsigned long sm_mem_claimed_by_nodes;

    ~Node();
    Hash_Key&  hash() { return m_hash_key; }
    Cost_Type& fn() { return m_fn; }
    Cost_Type& gn() { return m_gn; }
    Cost_Type& hn() { return m_hn; }

    void* operator new(size_t num_bytes ){
      sm_mem_claimed_by_nodes += num_bytes;
      return malloc(num_bytes);
    }

    State* s() { return m_state; }
    Node* parent() { return m_parent; }
    Action* op() { return m_op; }

    template <typename Heuristic>
    static	Node*	progress_evaluate( Node* parent, Action& a, Heuristic& h );
    template <typename Heuristic>
    static	Node*	regress_evaluate( Node* parent, Action& a, Heuristic& h );
    static	Node*	progress( Node* parent, Action& a );
    static 	Node*	regress( Node* parent, Action& a );
    static	Node*	root(aig_tk::STRIPS_Problem &p);

    Node* successor(Action *a);

    Action_Ptr_Vec &helpful() { return m_helpful; }

    void set_parent(Node *np, Action *a);

    bool operator==(Node &a);

  protected:
	
    Node();

    State*		m_state;
    Cost_Type   m_fn;
    Cost_Type	m_gn;
    Cost_Type   m_hn;
    Hash_Key	m_hash_key;

    Node *m_parent;
    
    Action *m_op;

    Action_Ptr_Vec m_helpful;
  };

  inline bool Node::operator==(Node &a) {
    /*
    std::cout << "in Node::operator==, this: " << this << ", a: " << &a << std::endl;
    std::cout << "this->state = " << this->s() << "a->state = " << a.s() << std::endl;
    */
    return ( *(s()) == *(a.s()) );
  }

}

#endif // Node.hxx
