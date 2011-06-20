#ifndef __PDDL_OPERATOR__
#define __PDDL_OPERATOR__
#include <planning/Types.hxx>
#include <planning/STRIPS_Problem.hxx>

namespace aig_tk
{

class PDDL_Operator
{
public:

	PDDL_Operator( STRIPS_Problem& p );
	~PDDL_Operator();

	unsigned	index() const;
	std::string	signature() const;
	std::string	name() const;
	std::vector<std::string>& args_name();
	Index_Vec&	pddl_types_idx();

	void		set_index( unsigned idx );
	void		set_signature( std::string signature );
	void		set_name( std::string n );
	void		add_arg_name( std::string name );
	void		add_pddl_type_idx( unsigned i );

	STRIPS_Problem& problem();

protected:

	STRIPS_Problem&			m_problem;
	unsigned			m_index;
	std::string			m_signature;
	std::string			m_name;	
	std::vector<std::string>        m_args_name;
	Index_Vec                       m_pddl_type_list_idx;
};

inline std::string	PDDL_Operator::name() const
{
	return m_name;
}

inline void		PDDL_Operator::set_name( std::string n)
{
	m_name = n;
}

inline std::vector<std::string>&	PDDL_Operator::args_name()
{
	return m_args_name;
}

inline void		PDDL_Operator::add_arg_name( std::string name )
{
	m_args_name.push_back( name );
}

inline Index_Vec&	PDDL_Operator::pddl_types_idx()
{
	return m_pddl_type_list_idx;
}

inline void		PDDL_Operator::add_pddl_type_idx( unsigned i )
{
	m_pddl_type_list_idx.push_back( i );
}

inline unsigned		PDDL_Operator::index() const
{
	return m_index;
}

inline	std::string	PDDL_Operator::signature() const
{
	return m_signature;
}

inline void	PDDL_Operator::set_index( unsigned idx ) 
{
	m_index = idx;
}

inline void	PDDL_Operator::set_signature( std::string sig )
{
	m_signature = sig;
}

}

#endif // PDDL_Operator.hxx
