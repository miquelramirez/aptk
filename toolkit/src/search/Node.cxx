#include <search/Node.hxx>
#include <planning/Types.hxx>
#include <util/hash_table.hxx>
#include <util/memory.hxx>
#include <iostream>

namespace aig_tk
{

  unsigned long Node::sm_mem_claimed_by_nodes = 0;

  Node::Node()
    : m_state( NULL ),
      m_fn( 0 ), m_gn( 0 ), m_hn( 0 ),
      m_parent(NULL), m_op(NULL)
  {
  }

  Node::~Node()
  {
    delete m_state;
  }

  Node*	Node::root(aig_tk::STRIPS_Problem &p, bool regress)
  {
    Node *r = new Node;

    // can't get this statically for now
    r->m_state = new State(p);

    if (regress)
    {
	for (unsigned i = 0; i < p.goal().size(); i++ )
		r->m_state->set(p.goal()[i]);
    }
    else
    {
    	for(unsigned i = 0; i < p.init().size(); i++) {
      		r->m_state->set(p.init()[i]);
    	}
    }

    std::sort(r->m_state->fluent_vec().begin(),
	      r->m_state->fluent_vec().end());

    return r;
  }

  Node*	Node::progress( Node* parent, Action& a )
  {
//          parent->succesor(&a);
    return NULL;
  }

  Node*	Node::regress( Node* parent, Action& a )
  {
    return NULL;
  }

  Node* Node::successor(aig_tk::Action *a, bool regress) {

    Node *succ = new Node();
	
    if (regress)
	succ->m_state = s()->regress_through(*a);
    else
    	succ->m_state = s()->progress_through(*a);

    // enforce orderedness of fluent_vec
    //NIR: Do not need that, need to check with MRJ
    //std::sort(succ->s()->fluent_vec().begin(),
    //	      succ->s()->fluent_vec().end());

    succ->m_op = a;
    succ->m_parent = this;
    succ->m_gn = this->gn() + a->cost();

    succ->m_hash_key.add( succ->s()->fluent_vec() );


    /*
    std::cout << "returning successor node " << succ << " for " << this << std::endl;
    std::cout << "succesor node state: " << succ->s() << std::endl;
    */
    return succ;
  }

  void Node::set_parent(Node *np, Action *a) {
    m_parent = np;
    m_op = a;
    m_gn = m_parent->gn() + a->cost();
  }

}
