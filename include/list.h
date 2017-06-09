#ifndef _AUG_LIST_H_
#define _AUG_LIST_H_

#include "base.h"

/**
 * @brief [brief description]
 * @details [long description]
 */
template < typename T >
class list : public base<T>
{
public:
	//Ok
	list( void ) { }
	//Ok
	virtual ~list( void ) { }
	//Ok
	//int size( void );
	//Ok
	//bool empty( void );
	//Ok
	//void clear( void );
	//Ok
	//void print( void );

	//Ok
	T front( void ) { return base<T>::front(); }
	//Ok
	void pop_front( void ) { base<T>::pop_front( ); }
	//Ok
	void push_back( const T data ) { base<T>::push_back(data); }
};

#endif