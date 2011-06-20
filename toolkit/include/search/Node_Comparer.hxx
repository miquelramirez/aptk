#ifndef __NODE_COMPARER__
#define __NODE_COMPARER__

#include <util/ext_math.hxx>
#include <search/Node.hxx>

namespace aig_tk
{
          
        typedef bool (*NodeComparisonFunc)(Node*, Node*);

  
        class Node_Comparer
        {             
                static NodeComparisonFunc currentCompFunc;
                
                
                /**
                 * bigger g higher priority
                 */
                static bool WAStarComp( Node* a, Node* b) {
                        return (dless(b->fn(), a->fn()) || (dequal(a->fn(), b->fn()) && dless(a->gn(), b->gn())));
                }
        
                /**
                 * lower g higher priority
                 */
                static bool GBFSComp( Node* a, Node* b) {
                        return (dless(b->fn(), a->fn()) || (dequal(a->fn(), b->fn()) && dless(b->gn(), a->gn())));
                }
        public:
                bool operator()( Node* a, Node* b ) {
                        return (*currentCompFunc)(a, b);
                }
                
                static void set_greedy() {
                        currentCompFunc = &GBFSComp;
                }
                static void set_non_greedy() {
                        currentCompFunc = &WAStarComp;
                }
        };
        
        
}

#endif // Node_Comparer.hxx
