#ifndef __SEARCH__
#define __SEARCH__

#include <vector>
#include <search/Node.hxx>
#include <planning/STRIPS_Problem.hxx>

namespace aig_tk {
             
        /**
         * Abstract Class Search
         */
        class Search
        {
        protected:
    
                STRIPS_Problem*		        m_problem;
                STRIPS_Problem&                 problem() { return *m_problem; }

                int m_expand_count;
                int m_gen_count;


    
        public:
                Search(): m_problem(NULL) ,m_expand_count(0), m_gen_count(0) { }
                Search(STRIPS_Problem& prob): m_problem(&prob) ,m_expand_count(0), m_gen_count(0) { }
                void initialize()
                {
                        m_problem = NULL;
                        m_expand_count = 0;
                        m_gen_count = 0;
                }
                                
                virtual ~Search() { }
                
                void		set_problem( STRIPS_Problem& p ) { m_problem = &p; }
                
                virtual void setFn(Node* n) {
                        n->fn() = n->gn();
                }
                virtual bool solve(Node* start, std::vector<Node*> &plan) = 0;
                void extractPlan(Node *start, Node *end, std::vector<Node*> &plan);
                int getExpanded() { return m_expand_count; }
                int getGenerated() { return m_gen_count; }

        };

        inline void Search::extractPlan(Node *start, Node *end, std::vector<Node*> &plan)
        {
    
                Node *tmp = end;
		
                while(!(*tmp == *start &&  tmp->gn() == start->gn()) ) {
                        plan.push_back(tmp);
                        tmp = tmp->parent();
                }
                std::reverse(plan.begin(), plan.end());
        }

}

#endif // Search.hxx
