/*
 * Nome do Arquivo:  machine.c
 *       Descricao:  Implementação do componente executor da máquina.
 * 
 * Machine for TuringM.
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

#include "machine.h"

MACHINE *machine_new(ALPHABET *inputAlphabet, ALPHABET *outputAlphabet, 
						char whiteChar, TRANSITIONTABLE *table){

	MACHINE *novo;

	if((novo = (MACHINE*)malloc(sizeof(MACHINE))) == NULL){
		trgError_setDesc(MACHINE_EALLOC_MSG);
		return (NULL);
	}

	novo->inputAlphabet = inputAlphabet;
	novo->outputAlphabet = outputAlphabet;
	novo->whiteChar = whiteChar;
	novo->table = table;

	return (novo);
}

void machine_free(MACHINE *machine){

}

int machine_run(MACHINE *machine){

}

