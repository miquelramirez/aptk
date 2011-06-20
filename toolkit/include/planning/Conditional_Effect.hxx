#ifndef __CONDITIONAL_EFFECT__
#define __CONDITIONAL_EFFECT__

#include <planning/Types.hxx>

namespace aig_tk
{

class Conditional_Effect
{
public:

	Conditional_Effect();
	~Conditional_Effect();

	void		define( Fluent_Vec& precs, Fluent_Vec& adds, Fluent_Vec& dels );

	Fluent_Vec&	prec_vec() { return m_prec_vec; }
	Fluent_Set&	prec_set() { return m_prec_set; }
	Fluent_Vec&	add_vec()  { return m_add_vec; }
	Fluent_Set&	add_set()  { return m_add_set; }
	Fluent_Vec&	del_vec()  { return m_del_vec; }
	Fluent_Set&	del_set()  { return m_del_set; }

protected:
	Fluent_Vec			m_prec_vec;
	Fluent_Set			m_prec_set;
	Fluent_Vec			m_add_vec;
	Fluent_Set			m_add_set;
	Fluent_Vec			m_del_vec;
	Fluent_Set			m_del_set;

};

}

#endif // Conditional_Effect.hxx
