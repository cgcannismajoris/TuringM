# TuringM
Um simulador da máquina universal conceitual de Turing.

##O que ele faz?
Realiza a simulação da execução de um autômato descrito por uma tabela em uma máquina de turing.
É permitido o uso de mais de uma fita.

##Requisitos recomendados
* Sistema Operacional Unix-like ou GNU/Linux mais recente;
* GCC 4.9.1 ou superior;
* GNU Make 4.0 ou superior.

##Estrutura do projeto

A seguir, está disposto a organização básica do projeto AssemblerM.

	/TuringM					: pasta-pai do projeto	
		/data					: arquivos de entrada/saída e relativos ao projeto
		/src					: pasta de códigos-fonte
		.gitignore				: arquivo gitignore
		COPYING3				: arquivo de licença
		Makefile				: arquivo Makefile
		README.md				: arquivo LEIA-ME

##Procedimento de compilação do TuringM
Estando-se na pasta pai do projeto ("/TuringM"), realize o comando abaixo:

	$ make

##Procedimentos de utilização via Terminal
Através de um terminal de comando do Linux, observa-se o formato de entrada abaixo:

	$ ./bin/TuringM <ARQUIVO_ENTRADA> <QUANTIDADE_DE_FITAS>
	
Descrição dos argumentos: 

	<ARQUIVO_ENTRADA>        : é um arquivo de texto codificado no padrão ANSI ASCII contendo a
		                       seguinte configuração:
		                       
		                       Primeira linha: Deve conter o alfabeto de entrada;
		                       Segunda linha : Deve conter o alfabeto de saída;
		                       Terceira linha: Deve conter o carectere branco seguido do
		                                       estado inicial;
		                       Quarta linha  : Deve conter o conjunto de todos os estados;
		                       Quinta linha  : Deve conter o conjunto de todos os estados
		                                       que são finais;
		                       Sexta linha   : Deve conter a configuração inicial da fita;
		                       A paritr da sétima linha deve ser escrita a tabela de transições.
		                       
	<QUANTIDADE_DE_FITAS>    : quantidade de fitas a serem utilizadas. Caso omitido, a quantidade
				   assumida é 1.

A tabela de transições deve respeitar a seguinte forma:
```
  <Estado atual> <Símbolo lido fita 0> <Símbolo lido fita 1> ... <Símbolo lido fita n> <Próximo estado> <Símbolo a ser escrito fita 0> <Símbolo a ser escrito fita 1> ... <Símbolo a ser escrito fita n> <Movimento fita 0> <Movimento fita 1> ... <Movimento fita n> 
```

Onde:

```
  <Estado atual>                : Estado atual da máquina;
  <Símbolo lido fita i>         : Símbolo a ser lido na fita i;
  <Próximo estado>              : Próximo estado caso o descrito símbolo seja lido;
  <Símbolo a ser escrito fita i>: Símbolo a ser escrito na fita i, caso a transição ocorra;
  <Movimento fita i>            : Movimento da fita i, onde:
                                    D ou d - Direita;
                                    E ou e - Esquerda;
                                    P ou p - Não mover a fita.
```

A chamada do programa sem argumentos resultará na exibição de uma descrição simplificada da lista de argumentos.
                               
Se a decodificação do arquivo for bem sucedida, o simulador irá iniciar a execução exibindo, a cada transição
de estados, as fitas com a posição atual na cor VERDE.

###Exemplo de Arquivo de Entrada

O input a seguir faz a soma de dois números binários utilizando quatro fitas.
As duas primeiras fitas são utilizadas para input, a terceira como auxiliar para o "vai um" e a última é utilizada para armazenar o resultado.

```
1 0 @ b
1 0 @ b
b q0
q0 q1 q2 q3
q3
@ 1 1 1 1
@ 0 0 0 1
@
@
q0 @ @ @ @ q1 @ @ @ @ d d d d
q1 1 1 b b q1 1 1 0 b d d d d
q1 1 0 b b q1 1 0 0 b d d d d
q1 0 1 b b q1 0 1 0 b d d d d
q1 0 0 b b q1 0 0 0 b d d d d
q1 b b b b q2 b b b b e e e e
q2 1 1 0 b q2 1 1 1 0 e e p e
q2 1 1 1 b q2 1 1 1 1 e e p e
q2 0 0 0 b q2 0 0 0 0 e e e e
q2 0 0 1 b q2 0 0 0 1 e e e e
q2 1 0 0 b q2 1 0 0 1 e e e e
q2 1 0 1 b q2 1 0 1 0 e e p e
q2 0 1 0 b q2 0 1 0 1 e e e e
q2 0 1 1 b q2 0 1 1 0 e e p e
q2 @ @ 0 @ q3 @ @ 0 0 p p e p
q2 @ @ 1 @ q3 @ @ 0 1 p p e p
```

##Diagrama do Projeto
Abaixo é mostrado o diagrama de classes (adaptado) do projeto.

##Licença
O TuringM é amparado pela licença [GNU General Public License V3.0](https://www.gnu.org/licenses/gpl.txt).

##Autores
Cristan Costa Mello - cristianc.mello@gmail.com<br/>
Gustavo Freitas de Amorim - gustavofreitasamorim@gmail.com
