#ifndef __BESTFIRSTSEARCH__
#define __BESTFIRSTSEARCH__

#include <search/Heuristic_Search.hxx>
#include <search/Closed_List.hxx>
#include <search/Open_List.hxx>
#include <search/Node_Comparer.hxx>

namespace aig_tk {

        /**
         *  any search that uses an open list, closed list, and 
         * f = zg + wh
         */
        class Best_First_Search : public Heuristic_Search {
    
        protected:
                Closed_List<Node> m_closed, m_open_hash;
                bool isEnd;
                bool isIn;

                /**
                 * Compulsory to make a downcast to Node_Comparer
                 */
                Open_List<Node_Comparer, Node*> m_open;
    
                float m_w;
                float m_z;
    
                void close( Node* n ) {  m_closed.add_element(n->hash(), n); }
                Node* isClosed( Node* n ) { return m_closed.get_element(n->hash() ,n); }
                virtual std::vector<Node*> dumpOpen(Open_List<Node_Comparer, Node*> &o);
                
                /**
                 * End Criteria
                 */
                virtual bool isGoal(Node *candidate) { return candidate->s()->entails( problem().goal()); }
                /**
                 * Init Criteria
                 */
                virtual bool isInit(Node *candidate) { std::cout << "entro?" << std::endl; return candidate->s()->entails(problem().init());}

                /**
                 * Evaluate node
                 */
                void eval( Node *n ) { setHn(n); setFn(n); }
                
                /**
                 * Set Fn according to z and w factor
                 */
                virtual void setFn(Node *n) { n->fn() = (m_w * n->hn()) + (m_z * n->gn());}


                /**
                 * Initialize search
                 */
                virtual void initialize(Node *start);
                
                /**
                 * Get Node from open list
                 */
                virtual Node* getNode();
                
                /**
                 * Add to open list if possible
                 */
                virtual void openNode(Node *n, Hash_Key& h, Open_List<Node_Comparer,Node*> &in_open_list);

                /**
                 * Expand node
                 */
                virtual void process(Node *head);
                
                /**
                 * Main loop
                 */
                virtual Node* doSearch();

                /**
                 * Repeated Nodes control
                 */
                bool previously_hashed(Node *s, Hash_Key& h);
                
                void reset();
 
        public:
                Best_First_Search(float w = 1, float z = 1, Heuristic *h = NULL, STRIPS_Problem* p = NULL) :
                        Heuristic_Search(h), 
                        m_closed(8192), 
                        m_open_hash(8192), 
                        m_w(w), 
                        m_z(z)
                {
                        m_problem = p;
                        m_open_hash.setOwner(false);
                        if (z == 0)
                                Node_Comparer::set_greedy();
                        else
                                Node_Comparer::set_non_greedy();
                }

                virtual bool is_Goal(Node *candidate){return isGoal(candidate); }
                virtual bool is_Init(Node *candidate){ return isInit(candidate);}
                virtual ~Best_First_Search() {
                        m_open_hash.clear();
                        while(! m_open.empty() ) {
                                m_open.pop();
                        }
                        m_closed.clear();
                }

                virtual void init(Node* start){ initialize(start);}
                virtual Node* doStep();
                virtual bool solve( Node* start, std::vector<Node*> &global_plan);
                virtual Node* solveStep(Node* init, std::vector<Node*> &global_plan);
                virtual bool getIsEnd(){return isEnd;}
                virtual bool getIsInit(){std::cout << "entro?" << std::endl; return isIn;}
                virtual void setIsEnd(bool is_end){ isEnd = is_end;}
                virtual void setIsInit(bool is_init){ isIn = is_init;}
                virtual std::vector<Node*> getOpenList();
        };  
  
}

#endif // Best_First_Search.hxx
