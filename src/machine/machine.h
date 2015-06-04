/*
 * Nome do Arquivo:  machine.h
 *       Descricao:  Implementação do componente executor da máquina.
 *
 * Exported functions from machine.c.
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

#ifndef MACHINE_HEADER
#define MACHINE_HEADER

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../trgError.h"

#include "tape/tape.h"
#include "alphabet/alphabet.h"
#include "transitionTable/transitionTable.h"

#define MACHINE_EALLOC               NULL
#define MACHINE_EALLOC_MSG           "Falha ao alocar memória para MACHINE."

typedef struct _machine {
	
	ALPHABET *inputAlphabet;
	ALPHABET *outputAlphabet;
	char whiteChar;

	TRANSITIONTABLE *table;

	TAPE *tape;	

} MACHINE;

MACHINE *machine_new(ALPHABET *inputAlphabet, ALPHABET *outputAlphabet, 
						char whiteChar, TRANSITIONTABLE *table, TAPE *tape);

void machine_free(MACHINE *machine);

int machine_run(MACHINE *machine);

#endif
