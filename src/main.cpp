#include <iostream>
#include <string>

#include "file.h"
#include "bares.h"

//http://stackoverflow.com/questions/17201590/c-convert-from-1-char-to-string
//https://www.youtube.com/watch?v=vq-nUF0G4fI&list=PL2_aWCzGMAwI3W_JlcBbtYTwiQSsOTa6P&index=21
//http://www.geeksforgeeks.org/expression-evaluation/
//https://en.wikipedia.org/wiki/Shunting-yard_algorithm


int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cerr << "Wrong syntaxe!" << std::endl;
		std::cerr << "Use: " << argv[0] <<" [arquivo_entrada] [arquivo_saida]" << std::endl;
		return 1;
	}

	//instanciar objeto para tratar o arquivo de expressões mat.
	augusto::file data;

	//instanciar objeto para tratar das expressões
	augusto::bares calc;


	if (!data.open(argv[1]))
	{
		std::cerr << "Arquivo invalido, tente outro!" << std::endl;
		return 1;
	}

	//imprime cabeçalho
	std::cout << "*=============================================*\n";
	std::cout << "| Programa BARES v0.0.2                       |\n";
	std::cout << "| Aluno: Augusto Lima                         |\n";
	std::cout << "*=============================================*\n\n";


	//por não usar 'iterator', utilizarei o seguinte método, neste 
	//caso, após cada loop o dado do topo da lista será lido e perdido
	while(data.has_expression())
	{
		std::string expression = data.get_expression();

		calc.set_infx( expression );
		
		std::cout << ">>> Avaliando: " << expression << std::endl;
				
		switch(calc.infx2posfx())
		{
			case 1: std::cout << "Constante numerica invalida [-32767 a 32767]\n"; break;
			case 2: std::cout << "Falta Operando.ie: 2+, 2**2\n"; break;
			case 3: std::cout << "Operando invalido.ie: 3*d\n"; break;
			case 4: std::cout << "Operando invalido.ie: 2.3 ou 2 = 2\n"; break;
			case 5: std::cout << "Falta operador.ie 2*2 3 \n"; break;
			case 6: std::cout << "Fechamento de escopo invalido.ie: )2-4\n"; break;
			case 7: std::cout << "Escopo aberto.ie: ((2%3)*8\n"; break;
			default:
				
				std::cout << ">>> Posfixo: "; calc.get_posfx();
				
				int result = calc.evaluate();
				if (result == -1)
					std::cout << "Operacao invalida, a/0" << std::endl;
				else
					std::cout << ">>> Resultado: " << result << std::endl;

				if (argc >= 3) {
					//data.save(argv[2], resultado);
				}
		}

		std::cout << std::endl;
	
	}

    return 0;
}