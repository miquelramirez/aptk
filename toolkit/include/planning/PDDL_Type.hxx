#ifndef __PDDL_TYPES__
#define __PDDL_TYPES__
#include <planning/Types.hxx>
#include <planning/STRIPS_Problem.hxx>

namespace aig_tk
{

	class PDDL_Type
	{
	public:

		PDDL_Type( STRIPS_Problem& p) ;
		~PDDL_Type();

		unsigned			index() const;
		std::string			signature() const;
		std::string			name() const;

		void		set_index( unsigned idx );
		void		set_signature( std::string signature );
		void		set_name( std::string n );	

		STRIPS_Problem& problem();

	protected:

		STRIPS_Problem&			m_problem;
		unsigned			m_index;
		std::string			m_signature;
	};

	inline std::string	PDDL_Type::name() const
	{
		return m_signature;
	}

	inline void		PDDL_Type::set_name( std::string n)
	{
		m_signature = n;
	}

	inline unsigned		PDDL_Type::index() const
	{
		return m_index;
	}

	inline	std::string	PDDL_Type::signature() const
	{
		return m_signature;
	}

	inline void	PDDL_Type::set_index( unsigned idx ) 
	{
		m_index = idx;
	}

	inline void	PDDL_Type::set_signature( std::string sig )
	{
		m_signature = sig;
	}

}

#endif // PDDL_Type.hxx
