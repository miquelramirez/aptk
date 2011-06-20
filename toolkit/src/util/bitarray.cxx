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
#include <util/bitarray.hxx>
#include <iostream>

namespace aig_tk
{

Bit_Array::Bit_Array()
	: m_packs( NULL ), m_pack_sz( 32 )
{
}

Bit_Array::Bit_Array( unsigned dim )
		: m_packs( NULL ), m_pack_sz(32)
{
	m_max_idx = dim+1;
	unsigned nbits = (dim+1);
	m_n_packs = (nbits/32)+1;
	m_packs = new unsigned [m_n_packs];
	memset( m_packs, 0, m_n_packs*sizeof(unsigned) );
}

Bit_Array::Bit_Array( const Bit_Array& other )
{
	m_pack_sz = 32;
	m_n_packs = other.m_n_packs;
	m_packs = new unsigned [m_n_packs];
	memcpy( m_packs, other.m_packs, m_n_packs*sizeof(unsigned) );
}

void Bit_Array::resize( unsigned dim )
{
	m_max_idx = dim+1;
	unsigned nbits = (dim+1);
	m_n_packs = (nbits/32)+1;
	m_packs = new unsigned[m_n_packs];
	memset( m_packs, 0, m_n_packs*sizeof(unsigned) );
}

Bit_Array::~Bit_Array()
{
	if ( m_packs != NULL )
		delete [] m_packs;
}

}
