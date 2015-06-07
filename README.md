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
		                       
	<QUANTIDADE_DE_FITAS>    : quantidade de fitas a serem utilizadas. É opicional. Caso omitido, a quantidade
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

O input a seguir faz a detecção de padrões dentro de uma única fita.
A fita começa em @ e contém uma sequencia de H, M e b (símbolo branco).
Caso encontre um H seguido de M ou o inverso, escreve 1 no símbolo b após o par.
Caso encontre uma repetição de dois Hs ou dois Ms, escreve 0 no símbolo b após o par.
No retorno, escreve 1 no símbolo b após o @ caso não forem encontradas repetições. Caso contrário escreve 0.

```
	1 0 H M @ b
	1 0 H M @ b
	b q0
	q0 q1 q2 q3 q4 q5 q6 q7 q8 q9 q10
	q9
	@ b H M b M H b H M b M M b
	q0 @ q1 @ d
	q1 b q2 b d
	q2 H q3 H d
	q2 M q4 M d
	q4 H q6 H d
	q6 b q2 1 d
	q4 M q7 M d
	q7 b q2 0 d
	q3 H q5 H d
	q5 b q2 0 d
	q3 M q6 M d
	q2 b q8 b e
	q8 M q8 M e
	q8 H q8 H e
	q8 1 q8 1 e
	q8 0 q10 0 e
	q10 H q10 H e
	q10 M q10 M e
	q10 1 q10 1 e
	q10 0 q10 0 e
	q8 b q9 1 e
	q10 b q9 0 e
```

##Diagrama do Projeto
Abaixo é mostrado o diagrama de classes (adaptado) do projeto.

##Licença
O TuringM é amparado pela licença [GNU General Public License V3.0](https://www.gnu.org/licenses/gpl.txt).

##Autores
Cristan Costa Mello - cristianc.mello@gmail.com<br/>
Gustavo Freitas de Amorim - gustavofreitasamorim@gmail.com
