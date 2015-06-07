/*
 * Nome do Arquivo:  imain.c
 *       Descrição:  Interface da TuringM. Aqui será fornecido recursos
 *                   de linha de comando para entrada feita pelo usuário.
 *
 * Main file of TuringM.
 * Copyright (C) 2015  Cristian Costa Mello and Gustavo Freitas de Amorim
 *
 * This is part of TuringM
 * TuringM is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * TuringM is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <stdlib.h>
#include <stdio.h>

#include "TuringM.h"

int main (int argc, char *argv[]){ 

	//Se a quantidade de argumentos for insuficiente...
	if(argc == 1)
	{
		printf("\nTuringM\n");
		printf("Copyright (C) 2015 Cristian Costa Mello and Gustavo \
Freitas de Amorim\n\n");
		printf("Linha de Comando:\n");
		printf("TuringM <NOME_DO_ARQUIVO_DE_ENTRADA> <QUANTIDADE_DE_FITAS>\n\n");
		printf("Descrição dos Argumentos:\n");
		printf("   <NOME_DO_ARQUIVO_DE_ENTRADA> : é um arquivo de \
texto codificado no padrão ANSI ASCII;\n");
		printf("   <QUANTIDADE_DE_FITAS>        : quantidades de \
fitas que serão utilizadas. Caso omitido,\n \
                                 o valor assumido é 1.\n\n");
		return (EXIT_SUCCESS);
	}
	//Se a quantidade de argumentos excede o limite...
	else if(argc > 3)
	{
		printf("Linha de comando inválida. Invoque o programa sem argumentos \
para mais informações.\n");
		return (EXIT_FAILURE);
	}
	
	if(argc == 2){
		turing_run(argv[1], 1);
	}	
	else{
		turing_run(argv[1], atoi(argv[2]));
	}

	return EXIT_SUCCESS;
}
