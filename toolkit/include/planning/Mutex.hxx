#ifndef __MUTEX__
#define __MUTEX__

#include <planning/STRIPS_Problem.hxx>
#include <planning/Types.hxx>

#include <iostream>

namespace aig_tk
{

  class Mutex {
    
  public:
    Mutex( STRIPS_Problem& p);
    ~Mutex( ) {}

    void compute_mutexes();
    bool is_mutex(unsigned p, unsigned q);

    void print_mutexes(std::ostream &out);

    void print_mutexes() { print_mutexes( std::cout ); }

  protected:

    STRIPS_Problem &problem() { return m_problem; }
    STRIPS_Problem &m_problem;

    std::vector<std::vector<bool> > m_mutexes;
    void unset_mutex(unsigned p, unsigned q);

  };

}

#endif
