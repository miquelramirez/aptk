#ifndef __PDDL_OBJECT__
#define __PDDL_OBJECT__
#include <planning/Types.hxx>
#include <planning/STRIPS_Problem.hxx>

namespace aig_tk
{

	class PDDL_Object
	{
	public:

		PDDL_Object( STRIPS_Problem& p) ;
		~PDDL_Object();

		unsigned			index() const;
		std::string			signature() const;
		std::string			name() const;
		Index_Vec&      		types_idx();
		
		void            set_types_idx( Index_Vec& tidx ) { m_types_idx = tidx; }
		void		set_index( unsigned idx );
		void		set_signature( std::string signature );
		void		set_name( std::string n );	
		
		STRIPS_Problem& problem();

	protected:

		STRIPS_Problem&			m_problem;
		unsigned			m_index;
		std::string			m_signature;
		Index_Vec                       m_types_idx;
	};

	inline std::string	PDDL_Object::name() const
	{
		return m_signature;
	}

	inline void		PDDL_Object::set_name( std::string n)
	{
		m_signature = n;
	}


	inline unsigned		PDDL_Object::index() const
	{
		return m_index;
	}

	inline	std::string	PDDL_Object::signature() const
	{
		return m_signature;
	}
	
	inline Index_Vec&      PDDL_Object::types_idx()
	{
		return m_types_idx;
	}
	
	inline void	PDDL_Object::set_index( unsigned idx ) 
	{
		m_index = idx;
	}

	inline void	PDDL_Object::set_signature( std::string sig )
	{
		m_signature = sig;
	}

}

#endif // PDDL_Object.hxx
