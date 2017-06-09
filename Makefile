### https://www3.ntu.edu.sg/home/ehchua/programming/cpp/gcc_make.html
### http://courses.cs.washington.edu/courses/cse326/02wi/unix/g++.html
### http://www.puxan.com/web/blog/HowTo-Write-Generic-Makefiles
### http://hiltmon.com/blog/2013/07/03/a-simple-c-plus-plus-project-structure/
### https://www.gnu.org/software/make/manual/html_node/File-Name-Functions.html
### http://www.gnu.org/software/make/manual/html_node/Wildcard-Function.html
### https://www.gnu.org/software/make/manual/html_node/Foreach-Function.html
### https://pt.wikibooks.org/wiki/Programar_em_C/Makefiles


### Programas
CXX = g++

### Variáveis
APP = main
AVISA = -Wall
DEPURA = -g
OTIMIZA = -O2
PADRAO_LINGUAGEM = c++11  # c++0x  # c++98
#BIBLIOTECA_PADRAO = -stdlib=libc++  # http://libcxx.llvm.org/ mac??
BIBLIOTECAS = # -fopenmp # -lsfml-graphics -lsfml-window -lsfml-system  #-fopenmp

### Diretórios
DIRFONTE = src
DIRINCLUDE = include
DIRBIBLIOTECA = lib
DIREXECUTAVEL = bin
DIRDOCUMENTACAO = doc

### Flags de compilação
CFLAGS = $(AVISA) $(DEPURA) $(OTIMIZA) -I $(DIRINCLUDE)/ -std=$(PADRAO_LINGUAGEM) $(BIBLIOTECAS)

### Flags de linkedição
LFLAGS = $(AVISA) $(BIBLIOTECA_PADRAO) -L $(DIRBIBLIOTECA)/ $(BIBLIOTECAS) 

### Dependências
# rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))
# SOURCES = $(notdir $(call rwildcard,$(DIRFONTE),*.cpp))
# SOURCES := $(shell find $(DIRFONTE) -type f -name *.cpp)
SOURCES = $(wildcard $(DIRFONTE)/*.cpp)
OBJECTS = $(patsubst $(DIRFONTE)/%,$(DIREXECUTAVEL)/%,$(SOURCES:.cpp=.o))

### Entradas
# a primeira entrada eh para o programa alvo
$(APP): $(OBJECTS)
	@echo ">>> Gerando executavel."
	$(CXX) $(LFLAGS) $(OBJECTS) -o $(DIREXECUTAVEL)/$(APP)

	
# essa entrada define como produzir o arquivo
#arquivo.o: arquivo.cpp arquivo.h
$(DIREXECUTAVEL)/%.o: $(DIRFONTE)/%.cpp
	@echo ">>> Compilando dependencias."
	@mkdir -p $(DIREXECUTAVEL)
	$(CXX) $(CFLAGS) -c $< -o $@

# essa entrada define como produzir a documentação
.PHONY: doc
doc:
	@echo ">>> Gerando documentacao."
	@mkdir -p $(DIRDOCUMENTACAO)
	@doxygen Doxygen

# a entrada seguinte elimina os arquivos inuteis.
.PHONY: clean
clean:
	@echo ">>> Limpando projeto."
	@rm -f $(DIREXECUTAVEL)/*
	@rm -R -f $(DIRDOCUMENTACAO)/html
