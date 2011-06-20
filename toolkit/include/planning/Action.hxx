#ifndef __AIG_TK_ACTION__
#define __AIG_TK_ACTION__

#include <planning/Types.hxx>
#include <planning/STRIPS_Problem.hxx>
#include <planning/State.hxx>
#include <planning/Conditional_Effect.hxx>

namespace aig_tk
{

class Action
{
public:
	Action(STRIPS_Problem& p);
	virtual ~Action();

	Fluent_Vec&	prec_vec() { return m_prec_vec; }
	Fluent_Set&	prec_set() { return m_prec_set; }
	Fluent_Vec&	add_vec()  { return m_add_vec; }
	Fluent_Set&	add_set()  { return m_add_set; }
	Fluent_Vec&	del_vec()  { return m_del_vec; }
	Fluent_Set&	del_set()  { return m_del_set; }
	std::string	signature() { return m_signature; }
	void		set_signature(std::string sig) { m_signature = sig; }
	std::string	name() { return m_name; }
	void		set_name(std::string nam) { m_name = nam; }
	unsigned	index() const { return m_index; }
	void		set_index( unsigned idx ) { m_index = idx; }

	void		define( Fluent_Vec& precs, Fluent_Vec& adds, Fluent_Vec& dels );

	void		define_fluent_list( Fluent_Vec& in, Fluent_Vec& list, Fluent_Set& set );

	bool		requires( unsigned f );
	bool		asserts( unsigned f );
	bool		retracts( unsigned f );
	bool		consumes( unsigned f );

	bool		can_be_applied_on( State& s, bool regress=false );
	bool		can_be_applied_on( Fluent_Vec& s );

	Index_Vec&	pddl_objs_idx();
	Index_Vec&	pddl_types_idx();

	void		add_pddl_obj_idx( unsigned i );
	void		add_pddl_type_idx( unsigned i );

	void            set_pddl_op_idx( unsigned idx) { m_pddl_op_idx = idx; }
	unsigned        pddl_op_idx() { return m_pddl_op_idx; }

	void		set_cost( Cost_Type c ) { m_cost = c; }
	Cost_Type	cost() { return m_cost; }

	static bool	are_effect_interfering( Action& a1, Action& a2 );
	static bool	deletes_precondition_of( Action& a1, Action& a2 );
	static bool	possible_supporter( Action& a1, Action& a2, Fluent_Vec& pvec );
protected:
	// Preconditions and Effects ( Adds and Deletes)
	std::string			m_signature;
	std::string			m_name;
	Fluent_Vec			m_prec_vec;
	Fluent_Set			m_prec_set;
	Fluent_Vec			m_add_vec;
	Fluent_Set			m_add_set;
	Fluent_Vec			m_del_vec;
	Fluent_Set			m_del_set;
	Conditional_Effect_Vec		m_cond_effects;
	Cost_Type			m_cost;	
	unsigned			m_index;
	Index_Vec                       m_pddl_obj_list_idx;
	Index_Vec                       m_pddl_type_list_idx;
	unsigned                        m_pddl_op_idx;

};

inline bool	Action::possible_supporter( Action& a1, Action& a2, Fluent_Vec& pvec )
{
	pvec.clear();
	for ( unsigned k = 0; k < a1.add_vec().size(); k++ )
		if ( a2.requires( a1.add_vec()[k] ) )
			pvec.push_back( a1.add_vec()[k] );
	return !pvec.empty();
}

inline bool	Action::deletes_precondition_of( Action& a1, Action& a2 )
{
	for ( unsigned k = 0; k < a1.del_vec().size(); k++ )
		if ( a2.requires( a1.del_vec()[k]) )
			return true;

	return false;
}

inline bool	Action::are_effect_interfering( Action& a1, Action& a2 )
{
	for ( unsigned k = 0; k < a1.add_vec().size(); k++ )
		if ( a2.retracts( a1.add_vec()[k] ) )
			return true;
	for ( unsigned k = 0; k < a1.del_vec().size(); k++ )
		if ( a2.asserts( a1.del_vec()[k] ) )
			return true;
	return false;
}

inline bool	Action::requires( unsigned f )
{
	return prec_set().isset(f);
}

inline bool	Action::asserts( unsigned f )
{
	return add_set().isset(f);
}

inline bool	Action::retracts( unsigned f )
{
	return del_set().isset(f);
}

inline bool	Action::can_be_applied_on( State& s, bool regress )
{
	if ( regress ) 
	{
		// Relevance testing
		bool relevant = false;
		for ( unsigned k = 0; k < add_vec().size() && !relevant; k++ )
			if ( s.entails( add_vec()[k] ) ) relevant = true;
		if (!relevant) return false;
		// Now test if no deletes from a are entailed by s
		for ( unsigned k = 0; k < del_vec().size(); k++ )
			if ( s.entails( del_vec()[k] ) ) return false;
		return true;
	}

	return s.entails( prec_vec() );
}

inline bool	Action::can_be_applied_on( Fluent_Vec& s)
{
  for(unsigned i = 0; i < prec_vec().size(); i++) {
    unsigned j;
    for(j = 0; j < s.size(); j++) {
      if(s[j] == prec_vec()[i])
	break;
    }
    if (j == s.size())
      return false;
  }
  return true;
}

inline bool	Action::consumes( unsigned f )
{
	return requires(f) && retracts(f);
}

inline Index_Vec&	Action::pddl_objs_idx()
{
	return m_pddl_obj_list_idx;
}

inline void		Action::add_pddl_obj_idx( unsigned i )
{
	m_pddl_obj_list_idx.push_back( i );
}

inline Index_Vec&	Action::pddl_types_idx()
{
	return m_pddl_type_list_idx;
}

inline void		Action::add_pddl_type_idx( unsigned i )
{
	m_pddl_type_list_idx.push_back( i );
}

}

#endif // Action.hxx
