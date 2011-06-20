/*
    Miguel Ramirez, Nir Lipovetzky, Hector Geffner
    C^3: A planner for the sequential, satisficing track of the IPC-6
    Copyright (C) 2008  

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
#ifndef __BITARRAY__
#define __BITARRAY__

#include <cstring>
#include <cassert>

namespace aig_tk
{

class Bit_Array
{
public:

	Bit_Array();
	Bit_Array( unsigned dim );
	Bit_Array( const Bit_Array& other );
	~Bit_Array();

	void resize( unsigned dim );
	unsigned* packs()
	{
		return m_packs;
	}

	unsigned npacks()
	{
		return m_n_packs;
	}

	unsigned max_index()
	{
		return m_max_idx;
	}
	
	unsigned size() // in bytes
	{
		return m_n_packs*32;
	}

	void set_all()
	{
		memset( m_packs, 0xFFFFFFFF,  m_n_packs*sizeof(unsigned) );
	}

	void reset()
	{
		memset( m_packs, 0, m_n_packs*sizeof(unsigned) );
	}	

	bool equal( Bit_Array& other )
	{
		for ( unsigned i = 0; i < m_n_packs; i++ )
			if ( m_packs[i] != other.m_packs[i] )
				return false;
		return true;
	}
	
	void set( unsigned i )
	{
                assert(  i <= (unsigned)m_max_idx );
		unsigned base = i;
		unsigned index = base/32;
		unsigned offset = base%32;
		m_packs[index] |= (1 << offset);
	}
       
        void set( Bit_Array &other )
        {
	  for ( unsigned i = 0; i < m_n_packs; i++ )
	    m_packs[i] |= other.m_packs[i];
	}

	void unset( unsigned i )
	{
                assert( i <= (unsigned)m_max_idx );
		unsigned base = i;
		unsigned index = base/32;
		unsigned offset = base%32;
		m_packs[index] &= ~(1 << offset);
	}


        void unset( Bit_Array &other )
        {
	        for ( unsigned i = 0; i < m_n_packs; i++ )
		  m_packs[i] &= ~(other.m_packs[i]);
	}


	unsigned isset( unsigned i )
	{
                assert( i <= (unsigned)m_max_idx );
		return m_packs[i/32] & 1 << (i%32);
	}

	unsigned operator[]( unsigned i )
	{
		return m_packs[i/32] & 1 << (i%32);
	}
	/*
	int pack_population( unsigned char x )
	{
		x = ( ( x & 0xAA ) >> 1 ) + ( x & 0x55 );
		x = ( ( x & 0xCC ) >> 2 ) + ( x & 0x33 );
		x = ( ( x & 0xF0 ) >> 4 ) + ( x & 0x0F );
		
		return x;
	}

	int count_elements()
	{
		int count = 0;
		for ( unsigned i = 0; i < m_n_packs; i++ )
			count += pack_population( m_packs[i] );
		return count;
		
	}	
	*/
protected:
	unsigned*      m_packs;
	unsigned       m_n_packs;
	unsigned       m_pack_sz;
	unsigned       m_max_idx;

};

}

#endif // bitarray.hxx
