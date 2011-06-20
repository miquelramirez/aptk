#ifndef __FLUENT__
#define __FLUENT__
#include <planning/Types.hxx>
#include <planning/STRIPS_Problem.hxx>

namespace aig_tk
{

class Fluent
{
public:

	Fluent( STRIPS_Problem& p );
	~Fluent();

	unsigned	index() const;
	std::string	signature() const;
	std::string	predicate() const;
	Index_Vec&	pddl_objs_idx();
	Index_Vec&	pddl_types_idx();

	void		set_index( unsigned idx );
	void		set_signature( std::string signature );
	void		set_predicate( std::string n );
	void		add_pddl_obj_idx( unsigned i );
	void		add_pddl_type_idx( unsigned i );

	STRIPS_Problem& problem();

protected:

	STRIPS_Problem&			m_problem;
	unsigned			m_index;
	std::string			m_signature;
	std::string			m_predicate;	
	Index_Vec                       m_pddl_obj_list_idx;
	Index_Vec                       m_pddl_type_list_idx;
};

inline std::string	Fluent::predicate() const
{
	return m_predicate;
}

inline void		Fluent::set_predicate( std::string n)
{
	m_predicate = n;
}

inline Index_Vec&	Fluent::pddl_objs_idx()
{
	return m_pddl_obj_list_idx;
}

inline void		Fluent::add_pddl_obj_idx( unsigned i )
{
	m_pddl_obj_list_idx.push_back( i );
}

inline Index_Vec&	Fluent::pddl_types_idx()
{
	return m_pddl_type_list_idx;
}

inline void		Fluent::add_pddl_type_idx( unsigned i )
{
	m_pddl_type_list_idx.push_back( i );
}

inline unsigned		Fluent::index() const
{
	return m_index;
}

inline	std::string	Fluent::signature() const
{
	return m_signature;
}

inline void	Fluent::set_index( unsigned idx ) 
{
	m_index = idx;
}

inline void	Fluent::set_signature( std::string sig )
{
	m_signature = sig;
}

}

#endif // Fluent.hxx
