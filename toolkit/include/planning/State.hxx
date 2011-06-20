#ifndef __AIG_TK_STATE__
#define __AIG_TK_STATE__

#include <planning/STRIPS_Problem.hxx>
#include <planning/Types.hxx>
#include <planning/Fluent.hxx>
#include <iostream>

namespace aig_tk
{

class Action;

class State
{
public:
	State( STRIPS_Problem& p );
	~State();

	Fluent_Vec& fluent_vec() { return m_fluent_vec; }
	Fluent_Set& fluent_set() { return m_fluent_set; }
	
	void	set( unsigned f );
	void	set( Fluent_Vec& fv );
	bool	entails( unsigned f ) { return fluent_set().isset(f); }
	bool	entails( State& s );
	bool	entails( Fluent_Vec& fv );
	bool	entails( Fluent_Vec& fv, unsigned& num_unsat );

	State*	progress_through( Action& a );
	State*	regress_through( Action& a );

	STRIPS_Problem&		problem();
  
        bool operator==(State &a);

protected:

	Fluent_Vec	m_fluent_vec;
	Fluent_Set	m_fluent_set;
	STRIPS_Problem&	m_problem;

};

inline bool State::operator==(State &a) {
  return fluent_vec() == a.fluent_vec();
}

inline STRIPS_Problem& State::problem()
{
	return m_problem;
}

inline	void State::set( unsigned f ) 
{
	m_fluent_vec.push_back( f );
	m_fluent_set.set( f );
}

inline	void State::set( Fluent_Vec& f )
{

	for ( unsigned i = 0; i < f.size(); i++ )
	{
		if ( !entails(f[i]) )
		{
			m_fluent_vec.push_back(f[i]);
			m_fluent_set.set(f[i]);
		}
	}
}

inline bool	State::entails( State& s )
{
	for ( unsigned i = 0; i < s.m_fluent_vec.size(); i++ )
		if ( !m_fluent_set.isset(s.m_fluent_vec[i]) ) return false;
	return true;
	
}

inline std::ostream& operator<<(std::ostream &os, State &s);


inline bool	State::entails( Fluent_Vec& fv )
{
	for ( unsigned i = 0; i < fv.size(); i++ )
	  if ( !m_fluent_set.isset(fv[i]) ) {
	    return false;
	  }
	return true;
}

inline bool	State::entails( Fluent_Vec& fv, unsigned& num_unsat )
{
	num_unsat = 0;
	for ( unsigned i = 0; i < fv.size(); i++ )
		if ( !m_fluent_set.isset(fv[i]) ) num_unsat++;
	return num_unsat == 0;
	
}

inline std::ostream& operator<<(std::ostream &os, State &s) {
  for(unsigned i = 0; i < s.fluent_vec().size(); i++) {
    os << s.problem().fluents()[s.fluent_vec()[i]]->signature();
    os << ", ";
  }
  os << std::endl;
  return os;
}


}

#endif // State.hxx
