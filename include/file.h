#ifndef _AUG_file_H_
#define _AUG_file_H_

#include <string>
#include <sstream>
#include "list.h"


namespace augusto
{
	class file
	{
	public:
		//Construtor
		file( void );
		//Construtor + leitura de arquivo
		file( std::string filepath );
		//Destrutor
		~file();
		//Ler arquivo de expressões matemáticas
		bool open ( std::string filepath );
		//Verifica se o arquivo foi lido
		bool is_open( void );
		//Verifica se ainda há expressões
		bool has_expression( void );
		//Retorna expressão do incio da fila + remove do inicio
		std::string get_expression( void );
 
		//void set_outpath( std::string filepath );
		//void save( void );

	private:
		//remove todos os espaços e tabulações
		void clean_line( std::string& line );

		bool _isopen;
		list<std::string> _expression;
	};
}
/*
class file
{
public:
	// Construtor
	file( void );
	// Construtor + leitura de arquivo
	file( std::string filepath );
	// Ler arquivo com a expressão matemática
	void read(std::string filepath);
	// Salva resultado da expressão matemática
	void save(std::string filepath, int result);
	// Retornar a expressão matemática
	std::string get_expression( void );

private:
	std::string m_expression;     ///> Expressão matemática
};
*/

#endif