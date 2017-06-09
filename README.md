# Programa BARES
 > Basic Arithmetic Expression Evaluator based on Stacks

 > Aluno: Augusto Lima
 > Disciplina: Estutura de Dados Básicas I

  - make – cria executável (ainda não há suporte para subpastas em src e include)
  - make doc – cria documentação
  - make clean – limpa projeto
  - $.\main arquivo_entrada [arquivo_saida] – executa programa

### Estrutura

* `bin`: executáveis | *.o 
* `doc`: documentação gerada pelo doxygen
* `include`: *.h | *.inl
* `lib`: *.a (static link)
* `src`: *.cpp

### Execução

`$.\bares arquivo_entrada [arquivo_saida]`, ie.

* ./bin/main data/exp1  > Ok
* ./bin/main data/exp2  > Ok
* ./bin/main data/exp3  > Ok
* ./bin/main data/exp4  > Erro escopo aberto
* ./bin/main data/exp5  > Erro fechamento de escopo invalido 
* ./bin/main data/exp6  > Operando invalido 2 * d
* ./bin/main data/exp7  > Operando invalido 2 = 4


### Bugs
Dos 8 tratamentos de erros + unário (-), faltam:

* (bug 2) Falta operando: em alguma parte da expressão está faltando um operador;
* (bug 5) Falta operador: operador não está associado. 
* (bug 8) Divisão por 0.
* (bug -) Identificar unário (-).

### Mudanças
Insersão namespace augusto

Class file -> 
 * lê mais de uma fórmula por aquivo
 * salva os dados de saida em um arquivo
Class bares ->
 * 
