executa: programa
	@echo Trabalho compilado com sucesso.
	@echo tp1 = "solucao" com backtracking
	@echo tp1_2 = "solucao" com inducao por caso base
          
programa: tp1.cpp tp1_2.cpp
	g++ -o tp1 tp1.cpp
	g++ -o tp1_2 tp1_2.cpp
