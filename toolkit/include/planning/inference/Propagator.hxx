/*
  Miguel Ramirez, Nir Lipovetzky, Hector Geffner
  C^3: A planner for the sequential, satisficing track of the IPC-6
  Copyright (C) 2008  

  Modified By: Nir Lipovetzky
  PROBE: A planner for the sequential, satisficing track of the IPC-7
  Copyright (C) 2011  
  
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef __PROPAGATOR__
#define __PROPAGATOR__

#include <planning/inference/Prop_Util.hxx>
#include <planning/STRIPS_Problem.hxx>
#include <planning/Types.hxx>
#include <planning/Action.hxx>
#include <planning/Fluent.hxx>

namespace aig_tk
{
                                
        template <typename Heuristic>
        class Propagator
        {
        protected:
                void				make_goal_nodes( );
        public:
                STRIPS_Problem&                 problem() { return *m_problem; }
        public:
                
                /**
                 * Accessors
                 */  	
                void                            initialize( STRIPS_Problem& prob);
                
                std::map<unsigned, unsigned>& 	get_m_operator_indices(){return m_operator_indices;}
                void				get_applicable_ops( Action_Ptr_Vec& min_action_set );
    
                bool                            op_in_mingraph(unsigned op){ return m_operator_indices[op] != 0;}
                bool                            fl_in_mingraph(unsigned p){ return m_fluent_indices[p] != 0;} 


                Index_Vec&                      op_layer(unsigned i){return m_op_layers[i];}
                Index_Vec&                      fl_layer(unsigned i){return m_fl_layers[i];}

                Propagation_Graph&              graph() {return m_graph;}
                Heuristic&                      getH(){return H;}
                void                            print();
                //getters
                std::vector<Index_Vec> get_m_op_layers(){return m_op_layers;}
                std::vector<Index_Vec> get_m_fl_layers(){return m_fl_layers;}

        private:
                /**
                 * Members
                 */

                typedef  Heuristic	        Heuristic_Type;
                Heuristic			H;  

                STRIPS_Problem*		        m_problem;
                Propagation_Graph               m_graph;

                std::map<unsigned, unsigned> 	m_fluent_indices;
                std::map<unsigned, unsigned> 	m_operator_indices;                

                std::vector<Index_Vec>	        m_fl_layers;
                std::vector<Index_Vec>	        m_op_layers;                  



        public:                
                Propagator( STRIPS_Problem& prob)                        
                {
                        m_problem = &prob;
                        m_graph.reserve( problem().num_fluents() + problem().num_actions() + 2);
                        H.initialize( prob );
                }
	
                ~Propagator()
                {  
      
                        for ( unsigned k = 0; k < m_graph.size(); k++ )
                                delete m_graph[k];
                }
    
                void clear()
                {
      
                        for ( unsigned k = 0; k < m_graph.size(); k++ )
                        { 
                                if(m_graph[k])
                                        delete m_graph[k];
                                m_graph[k]=NULL;
                        }


      
                        m_graph.reserve( problem().num_fluents() + problem().num_actions() + 2);
                        m_fl_layers.clear();
                        m_op_layers.clear();

                        m_fluent_indices.clear();
                        m_operator_indices.clear();

                }

                template <typename Node_Type>
                float build_propagation_graph(  Node_Type* n_o, bool only_one_sup = true )
                {      
                        /**
                         * Compute heuristic
                         */

                        H.compute( n_o->s()->fluent_vec() );      
      
                        Cost_Type h_s = H.op_value( problem().end_operator() );      
                        if ( h_s == std::numeric_limits<float>::max() )
                                return h_s;

	
                        m_fl_layers.resize( (unsigned)h_s +2 ); // leave room for dummy
                        m_op_layers.resize( (unsigned)h_s + 1 ); // leave room for End
      
                        /**
                         * insert Goals in the graph
                         */
                        make_goal_nodes();

                        /**
                         * Propagate backward from the goal
                         */
                        for ( unsigned i = (unsigned)h_s; i > 0; i-- )	
                        {
                                for ( unsigned j = 0; j < m_fl_layers[i].size(); j++ )
                                {
                                        Propagator_Node* n = m_graph.at( m_fl_layers[i][j] );
                                        Action_Ptr_Vec& best_supporters = H.best_supporters( n->Atom->index() );

                                        for ( unsigned k = 0; k < best_supporters.size(); k++ )
                                        {                                                 		  

                                                unsigned a_p_idx = m_operator_indices[ best_supporters[k]->index() ];

                                                /**
                                                 * Action is not in the graph
                                                 */
                                                if ( a_p_idx == 0 ) 
                                                {
                                                        Propagator_Node* n2 = new Propagator_Node;
                                                        n2->Type = ACTION;
                                                        n2->Operator = best_supporters[k];
			  
                                                        m_graph.push_back( n2 );
                                                        
                                                        /**
                                                         * put the node in its H.vaule layer 
                                                         */
                                                        m_op_layers.at( (unsigned) H.op_value( n2->Operator->index() ) ).push_back( m_graph.size() - 1 );
                                                        m_operator_indices[ n2->Operator->index() ] = m_graph.size() - 1;

                                                        n->Parents.push_back( m_graph.size() - 1 );
                                                        n2->Children.push_back( m_fl_layers[i][j] );

                                                }	
                                                else
                                                {
                                                        n->Parents.push_back( a_p_idx );
                                                        Propagator_Node* n2 = m_graph[a_p_idx];			  
                                                        n2->Children.push_back( m_fl_layers[i][j] );
                                                }

                                                
                                                if(only_one_sup) break;			
                                                
                                        }
                                }
                               
                                /**
                                 * Propagate backward ops
                                 */
                                for ( unsigned j = 0; j < m_op_layers[i-1].size(); j++ )
                                {
                                        Propagator_Node* n = m_graph.at(m_op_layers[i-1][j]);
                                        Action* op_ptr =  n->Operator;
                                        
                                        Fluent_Vec& preconditions = op_ptr->prec_vec();
                                        for ( unsigned k = 0; k < preconditions.size(); k++ )
                                        {
                                                unsigned prec_idx = m_fluent_indices[ preconditions[k] ];

                                                
                                                /**
                                                 * Fluent is not in the graph
                                                 */
                                                if ( prec_idx == 0 )
                                                {
                                                        Propagator_Node* n2 = new Propagator_Node;
                                                        n2->Type = FLUENT;
                                                        n2->Atom = problem().fluents()[ preconditions[k] ];		      
                                                        
                                                        m_graph.push_back( n2 );
                                                        /**
                                                         * put the node in its H.vaule layer 
                                                         */
                                                        m_fl_layers.at( (unsigned)H.fl_value( n2->Atom->index() ) ).push_back(m_graph.size()-1);
                                                        m_fluent_indices[ n2->Atom->index() ] = m_graph.size()-1;

                                                        n->Parents.push_back( m_graph.size()-1 );
                                                        n2->Children.push_back( m_op_layers[i-1][j] );

                                                }
                                                else
                                                {
                                                        n->Parents.push_back( prec_idx );
                                                        Propagator_Node* n2 = m_graph[prec_idx];
		                                        n2->Children.push_back( m_op_layers[i-1][j] );
                                                }
                                        }
                                }

                        }


                        return h_s;
                }

	
        };

        template <typename Heuristic>
        inline void	Propagator<Heuristic>::initialize( STRIPS_Problem& prob)                        
        {
                        m_problem = &prob;
                        m_graph.reserve( problem().num_fluents() + problem().num_actions() + 2);
                        H.initialize(prob);

        }
       
        template <typename Heuristic>
        void	Propagator<Heuristic>::get_applicable_ops( Action_Ptr_Vec& min_action_set )
        {
                for ( unsigned j = 0; j < m_op_layers[0].size(); j++ )
                        min_action_set.push_back( m_graph[ m_op_layers[0][j] ]->Operator );
        }

        template <typename Heuristic>
        void Propagator<Heuristic>::make_goal_nodes()
        {
                /**
                 * Add End() layer
                 */
                Propagator_Node* end_op_node = new Propagator_Node;
                end_op_node->Type = ACTION;
                end_op_node->Operator = problem().actions()[ problem().end_operator() ];
//                end_op_node->Children.push_back(0);
  
                m_graph.push_back( end_op_node );
                m_op_layers.back().push_back( m_graph.size() - 1 );
                m_operator_indices[  problem().end_operator() ] = m_graph.size() - 1;
      
                Action* end_op = end_op_node->Operator;
                for ( unsigned k = 0; k < end_op->prec_vec().size(); k++ )
                {
	
                        Propagator_Node* n = new Propagator_Node;
                        n->Type = FLUENT;
                        n->Atom = problem().fluents()[ end_op->prec_vec()[k] ];
		
                        m_graph.push_back( n );
                        end_op_node->Parents.push_back( m_graph.size()-1 );
                        n->Children.push_back( 0 );

                        /**
                         * put the node in its H.vaule layer 
                         */
                        m_fl_layers[ (unsigned)H.fl_value( n->Atom->index() ) ].push_back( m_graph.size() -1 );
                        m_fluent_indices[ n->Atom->index() ] = m_graph.size()-1;	

                }
        }



        template <typename Heuristic>
        void Propagator<Heuristic>::print()
        {

                float h_s = H.op_value( problem().end_operator() );
                for ( int i = h_s; i > 0; i-- )
                {
                        std::cout << "Proposition Layer #" << i << ": ";
                        for ( unsigned j = 0; j < m_fl_layers[i].size(); j++ )
                        {
                                std::cout << m_graph[ m_fl_layers[i][j] ]->Atom->signature();                                

                                if ( j < m_fl_layers[i].size()-1 )
                                        std::cout << ", ";
                        }
                        std::cout << std::endl<< std::endl;

                        std::cout << "Action Layer #" << i-1 << ": ";
                        for ( unsigned j = 0; j < m_op_layers[i-1].size(); j++ )
                        {
                                std::cout << m_graph[m_op_layers[i-1][j]]->Operator->signature();
                                if ( j < m_op_layers[i-1].size()-1 )
                                        std::cout << ", ";
                        }
                        std::cout << std::endl;
                }
                std::cout << "Proposition Layer #" << 0 << ": ";
                for ( unsigned j = 0; j < m_fl_layers[0].size(); j++ )
                {
                        std::cout << m_graph[ m_fl_layers[0][j] ]->Atom->signature();
                        if ( j < m_fl_layers[0].size()-1 )
                                std::cout << ", ";
                }
                std::cout << std::endl;
	

        }
}

#endif // propagator.hxx
