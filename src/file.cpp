#include "file.h"
#include <cctype> //isblank
#include <fstream>
#include <iostream>

using namespace augusto;


/**
 * @brief Construtor
 */
file::file( void ) : _isopen(false)
{ }

/**
 * @brief Construtor + leitura de arquivo
 * @details [long description]
 * 
 * @param filepath Caminho do arquivo
 */
file::file( std::string filepath ) : _isopen(false)
{
	this->open( filepath );
}

/**
 * @brief Destrutor
 */
file::~file( void )
{
	_expression.clear();
}

/**
 * @brief Ler arquivo de expressões matemáticas
 * @details [long description]
 * 
 * @param filepath [description]
 */
bool file::open( std::string filepath )
{
	//abre o arquivo
	std::ifstream data(filepath);

	//verifica se houve algum erro
	if (!data) 
	{
		_isopen = false;
		return false;
	}

	//limpa lista de expressões
	_expression.clear();

	//recebendo todas as expressões do arquivo
	std::string line;
	while(getline(data, line))
	{
		//limpe a string, removendo ' ' e '\t'
		this->clean_line(line);

		//se a linha não for vazia, insira na lista
		if (!line.empty()) _expression.push_back(line);
	}

	//fecha o arquivo
	data.close();

	_isopen = true;
	return true;
}

/**
 * @brief Verifica se o arquivo foi lido
 * 
 * @return Boolean
 */
bool file::is_open( void )
{
	return _isopen;
}

/**
 * @brief Verifica se ainda há expressões
 * 
 * @return Boolean
 */
bool file::has_expression( void )
{
	if (!is_open() || _expression.empty()) return false;

	return true;
}

/**
 * @brief Retorna expressão do incio da fila
 * @details Retorna expressão do inicio da fila e remove em seguida
 * 
 * @return [description]
 */
std::string file::get_expression( void )
{
	if (is_open() && !_expression.empty())
	{
		//guarda o inicio da lista
		std::string tmp = _expression.front();
		//elimina o inicio da lista
		_expression.pop_front();
		return tmp;
	}
	return "null";
}

/**
 * @brief Remove todos os espaços e tabulações
 * 
 * @param line String
 */
void file::clean_line( std::string& line )
{
	for(int i(0); i < (int)line.size(); ++i)
	{
		if (isblank(line[i]))
			line.erase(line.begin()+i);
	}
}




/**
 * @brief Salva resultado da expressão matemática
 * 
 * @param filepath Caminho do arquivo
 * @param result O resultado da expressão
 *//*
void file::save(std::string filepath, int result)
{
	// Abre arquivo para escrever
	std::ofstream data(filepath);
	if (!data) //or !file.is_open()
		throw std::invalid_argument("Arquivo invalido, tente outro!");

	// Escreve no arquivo
	data << result;

	// Fecha o arquivo
	data.close();
}*/