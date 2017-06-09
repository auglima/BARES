#ifndef _AUG_BARES_H_
#define _AUG_BARES_H_

#include <string>
#include "list.h"
//#include <iostream>
//#include <cstdlib>

//#include "file.h"

namespace augusto
{
	class bares
	{
	public:
		//
		bares( void );
		//
		bares( std::string infx );
		//
		~bares( void );
		//
		void set_infx( std::string infx );
		//
		std::string get_infx( void );
		//
		//std::string get_posfx( void );
		void get_posfx( void );
		int infx2posfx( void );
		int evaluate( void );

	private:
		bool precedence( const char& op1, const char& op2 );
		bool is_operand( const char& token );
		bool is_operator( const char& token );

		int operator_weight( const char & token );
		int process( const char sign, int op1, int op2 );
		
		bool _is_infx;
		bool _is_unary;
		bool _wait_operand;
		int _erro_col;
		std::string _infx;
		list<std::string> _posfx;
	};
}

/*
class bares
{
public:
	// Construtor
	bares( std::string _exp );
	// Imprime infixo
	void imprimirInfixo();
	// Imprime posfixo
	void imprimirPosfixo();
	// Transforma de infixo para posfixo
	int infixoParaPosfixo( void );
	// Avalia expressão posfixa
	int avaliarPosfixo( void );

	defina posfixo
	pegue  posfixo

 
private:
	// Checa se é operando
	bool ehOperando( char token );
	// Checa se é um operador
	bool ehOperador( char token );
	// Verifica 
	bool temPrecedencia( char pilha, char token );
	// Retornar o peso do operador
	int operadorPeso( char op );
	// Calcula resultado da expressão posfixa
	int calcular( char op, int token1, int token2 );	

	std::string infixo;
	list<std::string> posfixo;
};
*/
#endif