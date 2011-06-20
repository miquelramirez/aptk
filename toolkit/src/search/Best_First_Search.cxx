#include <limits.h>
#include <search/Best_First_Search.hxx>

namespace aig_tk {

        NodeComparisonFunc aig_tk::Node_Comparer::currentCompFunc = NULL;        


        /**
         * just for debugging
         */
        std::vector<Node*>
        Best_First_Search::dumpOpen(Open_List<Node_Comparer, Node*> &o) {

            Open_List<Node_Comparer, Node* > var;
            std::vector<Node*> v;

            if(o.empty()) return v;

            Node *t;
            for(unsigned i = 0; i < 10 && !o.empty() ; i++)
            {

                    t = o.pop();
                    v.push_back(t);
            }
            for(std::vector<Node*>::iterator it = v.begin(); it != v.end(); it++)
            {
                o.insert(*it);
            }
            return v;
        }


        bool
        Best_First_Search::solve(Node *start, std::vector<Node*> &plan) {
                
                
                initialize(start);
                Node *end = doSearch();
                if (end) {
                        extractPlan(start, end, plan);
                        return true;
                }
                return false;
        }

        Node* Best_First_Search::solveStep(Node *init, std::vector<Node*> &plan){

            Node *end = doStep();
            extractPlan(init, end, plan);

            return end;
        }


        /**
         * Initialize search
         */
        void
        Best_First_Search::initialize(Node *start) {

                reset();             
                isEnd = false;
                isIn = true;
                Hash_Key& h = start->hash();
                eval(start);
                m_open.insert(start);
                m_open_hash.add_element(h(), start);
                m_gen_count++;
        }

        /**
         * Main loop
         */
        Node*
        Best_First_Search::doSearch() {
                Node *head = getNode();
                int counter =0;
                while(head) {
                                                        
                        if(isGoal(head)) {
                                close(head);
                                std::cout << "counter: " << counter << std::endl;
                                return head;
                        }
                        process(head);
                        close(head);        
                        head = getNode();
                        counter++;
                }
                return NULL;
        }
        Node*
        Best_First_Search::doStep() {
            Node *head = getNode();

            std::cout << "entro en doStep" << std::endl;
            if(isGoal(head)) {
                std::cout << "entro en isGoal" << std::endl;
                isEnd = true;
                close(head);
                return head;
            }
            process(head);
            close(head);
            return head;

        }

        /**
         * Get Node from open list
         */
        Node*
        Best_First_Search::getNode() {
                Node *next = NULL;
                if(! m_open.empty() ) {
                        next = m_open.pop();
                        m_open_hash.remove_element(next->hash(), next);
                }
                return next;
        }
        
        /**
         * Add to open list if possible
         */
        void
        Best_First_Search::openNode(Node *n, Hash_Key& h, Open_List<Node_Comparer,Node*> &o) {

                eval(n);
                if(n->hn() == std::numeric_limits<float>::infinity()) {
                        close(n);
                }
                else {
                        o.insert(n);
                        m_open_hash.add_element(h, n);
                }
                m_gen_count++;
        }


/**
 * expand PP - 1 nodes resulting from preferred operators for every 1
 * from a non-preferred operator
 */
#define PREFERRED_PRIORITY 2

        void
        Best_First_Search::process(Node *head) {
                for(unsigned i = 0; i < problem().num_actions(); i++) {
                        Action* a = problem().actions()[i];
                        if( a->can_be_applied_on( *( head->s() ) ) ) {
                                Node *suc = head->successor(a);
                                Hash_Key& h = suc->hash();
                                if(previously_hashed(suc, h)) {
                                        delete suc;
                                }
                                else {
                                        openNode(suc, h, m_open);
                                }
                        }
                }
                m_expand_count++;
        }

        /**
         * check hash tables, reset parents if necessary
         */
        bool 
        Best_First_Search::previously_hashed(Node *n, Hash_Key& h) {
                Node *previous_copy = NULL;


                if((previous_copy = m_closed.get_element(h, n)))
                {
                        if(n->gn() < previous_copy->gn())
                                return false;

                        return true;
		}

		if( (previous_copy = m_open_hash.get_element(h, n)) )
                {
                        
                        if(n->gn() < previous_copy->gn())
                        {
                                previous_copy->set_parent(n->parent(), n->op());
                                setFn(previous_copy);
                        }
                        return true;
                }
               return false;
        }

        void Best_First_Search::reset()
        {
                m_open_hash.clear();
                while(! m_open.empty() ) {
                        m_open.pop();
                }
                m_closed.clear();
        }

        std::vector<Node*> Best_First_Search::getOpenList(){
            return dumpOpen(m_open);
        }
}
