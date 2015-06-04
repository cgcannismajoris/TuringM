/*
 * Nome do Arquivo:  TuringM.c
 *       Descricao:  Módulo principal do simulador.
 * 
 * Scanner for TuringM.
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

#include "TuringM.h"
#include <stdio.h>
int turing_run(char *file){

	MACHINE *machine = NULL;
	
	trgError_new(512);

	//Se ocorrer erro no processamento
	if((machine = decoder_decode(file)) == NULL){
		printf("%s\n", trgError_getDesc());
		printf(TURINGM_DECODER_ERROR_MSG);
		printf("\n");
		return (TURINGM_DECODER_ERROR);
	}
	
	//Chama machine_run e verifica o retorno

	return (0);
}

