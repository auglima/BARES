#include <cmath>
#include <cctype>  //isblank
#include <iostream>
#include "bares.h"
#include "stack.h"


using namespace augusto;

/**
 * @brief Construtor
 */
bares::bares( void ) : 
	_is_infx(false),
	_is_unary(false),
	_wait_operand(true)
{ }

/**
 * @brief Construtor + leitura de expressão
 */
bares::bares( std::string infx) : 
	_infx(infx),
	_is_infx(false),
	_is_unary(false),
	_wait_operand(true)
{ }


bares::~bares( void )
{
	_posfx.clear();
}

void bares::set_infx( std::string infx )
{
	_infx = infx;
	_posfx.clear();
}

std::string bares::get_infx( void )
{
	return _infx;
}

void bares::get_posfx( void )
{
	//como a lista ainda não tem suporte a iterator
	_posfx.print();
}




int bares::infx2posfx( void )
{
	//pilha para operadores
	augusto::stack<char> pilha;

	//checando cada posição da string
	for (int i(0); i < (int)_infx.size(); ++i)
	{
		//criando um token
		const char token = _infx.at(i);

		//checando se o token é diferente de nulo
		if (isblank(token)) continue;


		if (is_operator(token))
		{
			//primeira condição para ser unário ---X
			if (pilha.empty() && token == '-')
			{
				_is_unary = true;
				pilha.push(token);
				continue;
			}
			else if (_is_unary) // --X == X
			{
				//remove da pilha
				const char op = pilha.top(); 
				pilha.pop();

				
				if (op == '-' && token == '-')
					pilha.push('+');
				else
					pilha.push('-');

				continue;
			} 
			
			// A--B == A + B
			if (_wait_operand && token == '-')
			{
				//remove da pilha
				const char op = pilha.top(); 
				pilha.pop();

				//muda sinal *(-1)
				if (op == '-' && token == '-')
					pilha.push('+');
				else
					pilha.push('-');

				continue;
			} else if (_wait_operand && token != '-')
			{
				return 2; // falta operando
			}

			//se houver precedencia remover todos da pilha
			while (!pilha.empty() && precedence(pilha.top(), token))
			{
				//retira da pilha e joga na saida
				_posfx.push_back(std::string(1, pilha.top()));
				pilha.pop();
			}
			//insira novo operador na pilha
			pilha.push(token);
			_wait_operand = true;
		}


		else if (is_operand(token))
		{
			//if (_wait_operand == false ) return 5;// falta operador

			//operando completo
			std::string tmp = "";

			//se for unario
			if (_is_unary)
			{
				tmp.append(1, pilha.top());
				pilha.pop();
				_is_unary = false;
			}

			//enquanto for operando, concatene
			while(is_operand(_infx[i]))
			{
				//faz tratamento número 4
				if (_infx[i] == '.' || _infx[i]==',' || _infx[i] == '=') return 4;
				//concatena
				tmp.append(1, _infx[i]);
				++i;
			}
			//decrementar para não causar problemas ao loop principal
			--i;

			//faz tratamento 1
			std::string::size_type sz;   // alias of size_t

			int a = std::stoi (tmp,&sz);
			if (a < -32767 || a > 32767) return 1;

			//joga operando na saida
			_posfx.push_back(tmp);

			//espera receber operador
			_wait_operand = false;
		}

		else if (token == '(')
		{
			pilha.push(token);
		}

		else if (token == ')')
		{
			//enquando não encontrar o inicio da prioridade '('
			while(!pilha.empty() && pilha.top() != '(')
			{
				//jogue pilha na saida
				_posfx.push_back(std::string(1, pilha.top()));
				pilha.pop();
			}

			if (pilha.top() != '(')	return 6;

			// removendo o ')'
			pilha.pop();
		}
		else {
			// operando invalido
			return 3;
		}

		if (_wait_operand == true && i == (int)_infx.size()-1) return 2;// falta operador

	}

	//não a mais tokens para serem lidos
	//jogar resto da pilha na saida
	while (!pilha.empty())
	{
		if (pilha.top() == '(') return 7;

		_posfx.push_back(std::string(1, pilha.top()));
		pilha.pop();
	}

	_wait_operand = true;



	return 0; //Ok
}

int bares::evaluate( void )
{
	augusto::stack<int> pilha;

	while (!_posfx.empty()) {

		// se for um operando
		if (!is_operator(_posfx.front()[0]))
		{
			std::string::size_type sz;   // alias of size_t
			int i_dec = std::stoi(_posfx.front(),&sz);
			pilha.push(i_dec);
		}
		else 
		{
			int op1 = pilha.top();
			pilha.pop();
			int op2 = pilha.top();
			pilha.pop();

			int res = process(_posfx.front()[0], op2, op1); // bug
			std::cout << "> calculando: " << op2 << "" << _posfx.front() << "" << op1 << " = " << res << std::endl;

			pilha.push(res);
		}
		_posfx.pop_front();
	}
	return pilha.top();
}


bool bares::precedence(const char& op1, const char& op2)
{
	int peso1 = operator_weight(op1);
	int peso2 = operator_weight(op2);

	if (peso1 >= peso2) return true;

	return false;
}

bool bares::is_operand(const char& token)
{
	if (token >= '0' && token <= '9') return true;
	if (token == '.' || token == ',' || token == '=') return true;
	return false;
}

bool bares::is_operator(const char& token)
{
	return (token == '+' || token == '-' || token == '*' || 
			token == '/' || token == '%' || token == '^');
}

int bares::operator_weight( const char & token )
{
	int peso = -1;
	switch(token)
	{
		case '+':
		case '-': peso = 1; break;
		case '*':
		case '/': 
		case '%': peso = 2; break;
		case '^': peso = 3; break;
	}
	return peso;
}

int bares::process( const char sign, int op1, int op2 )
{
	if (sign == '/' && op2 == 0) return -1;

	switch(sign)
	{
		case '+': return (op1 + op2); break;
		case '-': return (op1 - op2); break;
		case '*': return (op1 * op2); break;
		case '/': return (op1 / op2); break;
		case '%': return (op1 % op2); break;
		case '^': return pow(op1, op2); break;
	}
}







//
/*

 * @brief Transforma uma expressão infixa para posfixa
 * @return [1: Constante numúerica inválida,
 * 			4: Operando invalido]
 *
int bares::infixoPara_posfx(void)
{
	stack<char> pilha;
	std::string operandoTemp;

	//enquanto tiver  tokens para ler
	for (int i(0); i < (int)infixo.size(); ++i)
	{
		const char token = infixo[i];

		//evita
		if (!isblank(token))
		{
			//se token for número add à saida
			if (ehOperando(token))
			{
				//gambiarra, avaliar código
				operandoTemp = "";
				//enquanto for operando, capture
				while(ehOperando(infixo[i]))
				{
					if (infixo[i] == '.' || infixo[i] == ',' || infixo[i] == '=') return 4;
					operandoTemp.append(1, infixo[i]);
					++i;
				}
				//decrementar para não causar problemas ao loop principal
				--i;

				//Checando tamanho do operando
				if (std::stoi(operandoTemp) < -32767 || std::stoi(operandoTemp) > 32767) return 1;

				_posfx.push_back(operandoTemp);
			}

			else if (ehOperador(token))
			{
				//enquanto houver operadores
				//e exista precedência
				while (!pilha.empty() && temPrecedencia(pilha.top(), token))
				{
					// Retire da pilha e jogue na saida
					this->_posfx.push_back(std::string(1, pilha.top()));
					pilha.pop();
				}
				// insira novo operador na pilha
				pilha.push(token);
			}

			else if (token == '(')
			{
				pilha.push(token);
			}

			else if (token == ')')
			{
				//enquando não encontrar o inicio da prioridade '('
				while(!pilha.empty() && pilha.top() != '(')
				{
					//jogue pilha na saida
					this->_posfx.push_back(std::string(1, pilha.top()));
					pilha.pop();
				}

				if (pilha.top() != '(')	return 6;

				// removendo o ')'
				pilha.pop();
			}

			else {
				// operando invalido
				return 3;
			}
		}
	}
	//não a mais tokens para serem lidos
	//jogar resto da pilha na saida
	while (!pilha.empty())
	{
		if (pilha.top() == '(') return 7;

		this->_posfx.push_back(std::string(1, pilha.top()));
		pilha.pop();
	}

	return 0;
}

*
 * @brief Calcula a expressão no formato infixo
 * @return Resultado da expressão
 *
int bares::avaliar_posfx(void)
{

}

*
 * @brief Valída se um caracter é um operando
 * 
 * @param token Um caracter da expressão
 * @return Boolean
 *
bool bares::ehOperando(char token)
{
	if (token >= '0' && token <= '9') return true;
	if (token == '.' || token == ',' || token == '=') return true;
	return false;
}

*
 * @brief Checa se o dado é um operador
 * 
 * @param token Um caracter da expressão
 * @return Boolean
 *
bool bares::ehOperador(char token)
{
	return (token == '+' || token == '-' || token == '*' || 
			token == '/' || token == '%' || token == '^');
}

*
 * @brief Checa se um operador tem procedência em relação ao outro
 * 
 * @param pilha Operador do top da pilha
 * @param token Operador corrente
 * 
 * @return Bool
 *
bool bares::temPrecedencia(char pilha, char token)
{
	int peso1 = operadorPeso(pilha);
	int peso2 = operadorPeso(token);

	if (peso1 >= peso2) return true;

	return false;
}

*
 * @brief Pesos dos operadores
 * 
 * @param op Operador
 * @return Peso do operador
 *
int bares::operadorPeso(char op)
{
	int peso = -1;
	switch(op)
	{
		case '+':
		case '-': peso = 1; break;
		case '*':
		case '/': 
		case '%': peso = 2; break;
		case '^': peso = 3; break;
	}
	return peso;
}

*
 * @brief Calcula operações matemáticas
 * 
 * @param op Operador
 * @param token1 Operando A
 * @param token2 Operando B
 * @return <A> <?> <B>
 *
int bares::calcular(char op, int token1, int token2)
{
	switch(op)
	{
		case '+': return (token1 + token2); break;
		case '-': return (token1 - token2); break;
		case '*': return (token1 * token2); break;
		case '/': return (token1 / token2); break;
		case '%': return (token1 % token2); break;
		case '^': return pow(token1, token2); break;
	}
}*/