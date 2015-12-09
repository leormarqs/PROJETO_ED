INF-1203 - ESTRUTURAS DE DADOS 
SEMESTRE 2015/2 - DEZEMBRO DE 2015 
TRABALHO PRÁTICO FINAL

DUPLA: 	LEONARDO RODRIGUES - 00213751
	MARCOS VINICIOS - 00261600


PROGRAMA PARA FORNECER AS n PALAVRAS COM MAIOR ESTATISTICAS DE CO-OCORRENCIA 
PARA CADA PALAVRA CONSULTADA EM UM CORPUS FORNECIDO

  --- ESTE PROGRAMA FOI DESENVOLVIDO EM AMBIENTE LINUX, USANDO A LINGUAGEM C.

  --- PARA COMPILAÇÃO, SUGERE-SE O USO DO COMANDO make EM LINHA DE COMANDO DO SISTEMA LINUX.

  --- A CHAMADA DESTE PROGRAMA EM LINHA DE COMANDO, DEVE SER DA SEGUINTE FORMA:

      --- ./sugestao ./corpus.txt ./palavras_a_consultar.txt ./saidas_do_programa.txt n

      	  --- onde:

	      - ./sugestao -> programa gerado após compilação
	      - ./corpus.txt -> caminho do arquivo de texto contendo o corpus para o cálculo
	      - ./palavras_a_consultar.txt -> caminho do arquivo de texto contendo as palavras
	      	a serem consultadas.

	      - ./saidas_do_programa.txt -> camimnho do arquivo de texto onde deve-se gravar as
	      	sugestões para cada palavra consultada.