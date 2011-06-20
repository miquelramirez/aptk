#ifndef __HEURISTICSEARCH__
#define __HEURISTICSEARCH__

#include <search/Search.hxx>
#include <planning/heuristics/Heuristic.hxx>

namespace aig_tk {
             
        /**
         * Abstract Class HeuristicSearch
         */
        class Heuristic;
        class Heuristic_Search : public Search {

        protected:
                Heuristic* m_heuristic;
                Heuristic& heuristic(){return *m_heuristic;}
        public:
                Heuristic_Search( Heuristic* h = NULL) : 
                        m_heuristic(h) { }
    
                void set_heuristic( Heuristic &h){m_heuristic = &h;}
                
                void setHn( Node* n );

        };
  
        inline void Heuristic_Search::setHn( Node* n ) 
        {                
                heuristic().compute( n->s()->fluent_vec() );
                n->hn() = heuristic().eval( problem().goal() );	
        }

}

#endif // Heurstic_Search.hxx
