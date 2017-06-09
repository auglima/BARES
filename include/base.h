#ifndef _AUG_BASE_H_
#define _AUG_BASE_H_

#include <iostream>
#include <string>


/**
 * @brief [brief description]
 * @details [long description]
 */
/*class node_base
{
public:
	node_base( void ) : next(nullptr), prev(nullptr) {}
	//void set_prev( node_base* ptr) { this->prev = ptr; }
	//void set_next( node_base* ptr) { this->next = ptr; }
	//node_base * get_prev( void ) { return this->prev; }
	//node_base * get_next( void ) { return this->next; }

//private:
	node_base *next;
	node_base *prev;
};*/



/**
 * @brief [brief description]
 * @details [long description]
 */
/*template < typename T >
class node : public node_base
{
public:
	node( void ) {}
	node( const T _data) : data(_data) {}

//private:
	T data;
};*/


template < typename T >
struct node {
	T data;
	node *next;
	node *prev;
	node( void ) : next(nullptr), prev(nullptr) {}
	node( const T _data ) : data(_data), next(nullptr), prev(nullptr) {}
};

/**
 * @brief [brief description]
 * @details [long description]
 */
template < typename T >
class base
{
public:
	//Ok
	base( void );
	//Ok
	virtual ~base( void );
	//Ok
	int size( void );
	//Ok
	bool empty( void );
	//Ok
	void clear( void );
	//Ok
	void print( void );

protected:
	//Ok
	T back( void );
	//Ok
	T front( void );
	//Ok
	void pop_back( void );
	//Ok
	void pop_front( void );
	//Ok
	void push_back( const T data );
	//Ok
	void push_front( const T data );
	

private:
	int mi_length;

	node<T> *mp_head;
	node<T> *mp_tail;
};



template < typename T >
base< T >::base( ) : mi_length(0)
{
	//criando a cabeça e o rabo
	this->mp_head = new node<T>();
	this->mp_tail = new node<T>();

	//linkando cabeça <-> rabo
	this->mp_head->next = this->mp_tail;
	this->mp_tail->prev = this->mp_head;

	//debug
	//std::cout << ">>> create *head: " << this->mp_head << std::endl;
	//std::cout << ">>> create *tail: " << this->mp_tail << std::endl;
	//std::cout << ">>> head->next: " << this->mp_head->get_next() << std::endl;
	//std::cout << ">>> head->prev: " << this->mp_head->get_prev() << std::endl;
	//std::cout << ">>> tail->next: " << this->mp_tail->get_next() << std::endl;
	//std::cout << ">>> tail->prev: " << this->mp_tail->get_prev() << std::endl;
}


template < typename T >
base< T >::~base( void )
{
	this->clear();

	delete this->mp_head;
	delete this->mp_tail;
}


template < typename T >
int base< T >::size( void )
{
	return this->mi_length;
}


template < typename T >
bool base< T >::empty( void )
{
	return (this->mp_head->next == this->mp_tail ? true : false);
}


template < typename T >
void base< T >::clear( void )
{
	/*//capturando o primeiro elemento
	node<T> *tmp = this->mp_head->next;
	node<T> *del; 

	//enquanto não chegar no final
	while (tmp->next != nullptr)
	{
		//capturando o bloco atual, antes de pular para o próximo
		del = tmp;
		std::cout << "deleted: " << tmp->data << std::endl;
		tmp = tmp->next;
		delete del;
	}

	//linkando novamente a cabeça <-> rabo
	this->mp_head->next = this->mp_tail;
	this->mp_tail->prev = this->mp_head;*/

	while(!this->empty())
	{
		//std::cout << "deleted: " << this->front() << std::endl;
		this->pop_front();
	}

}


template < typename T >
T base< T >::back( void )
{
	return this->mp_tail->prev->data;
}


template < typename T >
T base< T >::front( void )
{
	return this->mp_head->next->data;
}


template < typename T >
void base< T >::pop_back( void )
{
	if (!this->empty())
	{
		//capturando o bloco que deverá ser deletado
		node<T> *del = this->mp_tail->prev;
		//anterior do rabo aponto para bloco anterior ao que será deletado
		this->mp_tail->prev = del->prev;
		//o bloco anterior ao que será deletado, aponta para o rabo
		del->prev->next = this->mp_tail;
		//delete
		delete del;
		//decrementa contador
		this->mi_length--;	
	}
}


template < typename T >
void base< T >::pop_front( void )
{
	if (!this->empty())
	{
		//capturando o bloco que deverá ser deletado
		node<T> *del = this->mp_head->next;
		//proximo da cabeça aponta para o prox do que será deletado
		this->mp_head->next = del->next;
		//o anterior do bloco posterior ao que vai ser deletado, aponta para head		
		del->next->prev = this->mp_head;
		//delete
		delete del;
		//decrementa contador
		this->mi_length--;	
	}
}


template < typename T >
void base< T >::push_back( const T data )
{
	//cria um novo bloco
	node<T> *newNode = new node<T>(data);
	//o prox. do novo bloco é o rabo
	newNode->next = this->mp_tail;
	//o anterior do novo bloco é o anterior do rabo
	newNode->prev = this->mp_tail->prev;
	//o ex. ultimo bloco apontarar para o novo bloco
	this->mp_tail->prev->next = newNode;
	//agora o anterior do rabo é o novo bloco
	this->mp_tail->prev = newNode;
	this->mi_length++;
}


template < typename T >
void base< T >::push_front( const T data )
{
	//cria um novo bloco
	node<T> *newNode = new node<T>(data);
	//o prox. do novo bloco é o ex. primeiro bloco
	newNode->next = this->mp_head->next;
	//o anterior do novo bloco é a cabeça
	newNode->prev = this->mp_head;
	//o anteriror do ex primeriro bloco é o novo bloco
	this->mp_head->next->prev = newNode;
	//agora a cabeça aponta para o novo bloco
	this->mp_head->next = newNode;
	this->mi_length++;
}


template < typename T >
void base< T >::print( void )
{
	//capturando o primeiro elemento
	node<T> *tmp = this->mp_head->next;

	std::cout << "[ ";

	while (tmp->next != nullptr)
	{
		std::cout << tmp->data << " ";
		tmp = tmp->next;
	}

	std::cout << "]" << std::endl;
}

#endif