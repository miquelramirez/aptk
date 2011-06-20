#include <planning/Mutex.hxx>
#include <planning/Action.hxx>

namespace aig_tk
{
  Mutex::Mutex( STRIPS_Problem &p ) : m_problem(p) {

    m_mutexes.resize(problem().fluents().size());

    // higher index always first
    for(unsigned i = 0; i < problem().fluents().size(); i++) {
      m_mutexes[i].resize(i+1, true);
    }
  }

  bool 
  Mutex::is_mutex(unsigned p, unsigned q) {
    return ((p < q) ? is_mutex(q, p) : m_mutexes[p][q]);
  }

  void
  Mutex::unset_mutex(unsigned p, unsigned q) {
    if (p < q) {
      m_mutexes[q][p] = false;
    }
    else {
      m_mutexes[p][q] = false;
    }
  }

  void
  Mutex::compute_mutexes() {

    std::cout << "initsize: " << problem().init().size();

    for(unsigned i = 0; i < problem().init().size(); i++) {
      for(unsigned j = i; j < problem().init().size(); j++) {
	unset_mutex(problem().init()[i], problem().init()[j]);
      }
    }

    bool fixed_point;
    do {
      fixed_point = true;
      for(Action_Ptr_Vec::iterator a_it = problem().actions().begin(); a_it != problem().actions().end(); ++a_it) {
	bool app = true;
	Fluent_Vec &pre = (*a_it)->prec_vec();
	for(unsigned i = 0; (i < pre.size()) && app; i++)
	  for(unsigned j = i; (j < pre.size()) && app; j++)
	    app &= (! is_mutex(pre[i], pre[j]) );

	if (app) {
	  Fluent_Vec &adds = (*a_it)->add_vec();
	  for(unsigned i = 0; i < adds.size(); i++) {
	    for(unsigned j = i; j < adds.size(); j++) {
	      if(is_mutex(adds[i], adds[j])) {
		unset_mutex(adds[i], adds[j]);
		fixed_point = false;
	      }
	    }
	  }
	  for(unsigned i = 0; i < problem().fluents().size(); i++) {
	    if( is_mutex(i, i) ||
		(*a_it)->add_set().isset(i) ||
		(*a_it)->del_set().isset(i))
	      continue;
	    bool noop_app = true;
	    for(unsigned j = 0; (j < pre.size()) && noop_app; j++)
	      noop_app &= (! is_mutex(i, pre[j]));
	    
	    if (noop_app) {
	      for(unsigned j = 0; j < adds.size(); j++) {
		if(is_mutex(adds[j], i)) {
		  fixed_point = false;
		  unset_mutex(adds[j], i);
		}
	      }
	    }
	  }
	}
      }
    } while (! fixed_point );
  }

  void
  Mutex::print_mutexes(std::ostream &out) {

    for(unsigned i = 0; i < problem().fluents().size(); i++) {

      out << "Fluent " << problem().fluents()[i]->signature() 
	  << "(" << i << ") is mutex with: " << std::endl;
      for(unsigned j = 0; j < problem().fluents().size(); j++) {
	if(is_mutex(i, j)) {
	  out << "\t" << problem().fluents()[j]->signature()
	      << "(" << j << ")" << std::endl;
	}
      }
    }
  }



}
