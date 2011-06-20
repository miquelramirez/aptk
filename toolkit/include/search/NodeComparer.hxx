#ifndef __NODECOMPARER__
#define __NODECOMPARER__

#include <search/node.hxx>
#include <util/ext_math.hxx>

namespace aig_tk {

        typedef bool (*NodeComparisonFunc)(Node*, Node*);

        class NodeComparer {

                static NodeComparisonFunc currentCompFunc;

                /**
                 * bigger g higher priority
                 */
                static bool WAStarComp(Node *a, Node *b) {
                        return (dless(b->fn, a->fn) || (dequal(a->fn, b->fn) && dless(a->gn, b->gn)));
                }
    
                /**
                 * lower g higher priority
                 */
                static bool GBFSComp(Node *a, Node *b) {
                        return (dless(b->fn, a->fn) || (dequal(a->fn, b->fn) && dless(b->gn, a->gn)));
                }

        public:
                bool operator()( Node* a, Node* b ) {
                        return (*currentCompFunc)(a, b);
                }
    
                static void setGreedy() {
                        currentCompFunc = &GBFSComp;
                }
                static void setNonGreedy() {
                        currentCompFunc = &WAStarComp;
                }
        };
}

#endif
