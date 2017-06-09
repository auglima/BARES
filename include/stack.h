#ifndef _AUG_STACK_H_
#define _AUG_STACK_H_

#include "base.h"


namespace augusto
{
	template < typename T >
	class stack : public base<T>
	{
	public:	
		//Ok
		stack( void ) { };
		//Ok
		virtual ~stack( void ) { };
		//Ok
		T top( void );
		//Ok
		void push( const T data );
		//Ok
		void pop( void );
		//Ok
		//int size( void );
		//Ok
		//bool empty( void );
		//Ok
		//void clear( void );
		//Ok
		//void print( void );
	};

	/**
	 * @brief Retorna o elemento do top da pilha
	 */
	template < typename T >
	inline T stack< T >::top( void )
	{
		return this->front();
	}

	/**
	 * @brief Insere um elemento no topo da pilha
	 * 
	 * @param const T data
	 */
	template < typename T >
	inline void stack< T >::push( const T data )
	{
		this->push_front(data);
	}

	/**
	 * @brief Remove o elemento do top da pilha
	 */
	template < typename T >
	inline void stack< T >::pop( void )
	{
		this->pop_front();
	}
}

#endif