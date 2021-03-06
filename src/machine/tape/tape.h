/*
 * Nome do Arquivo:  tape.h
 *       Descricao:  Implementação do gerenciador da fita da máquina.
 *
 * Exported functions from tape.c.
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


#ifndef TAPE_HEADER
#define TAPE_HEADER

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../../trgError.h"

#include "../../gconio.h"

#include "../../linkedList/linkedList.h"

#include "../transitionTable/state/transition/transition.h"

#define TAPE_EALLOC			NULL
#define TAPE_EALLOC_MSG		"TAPE: Falha ao alocar memória."

#define TAPE_MOVE_RIGHT		TRANSITION_MOVE_RIGHT
#define TAPE_MOVE_LEFT		TRANSITION_MOVE_LEFT
#define TAPE_STOP			TRANSITION_STOP

typedef struct _tape{
	
	LIST *tape;
	NODE *actualSymbol;

	char whiteChar;

} TAPE;

typedef struct _symbol{
	char chr;
} SYMBOL;

TAPE *tape_new(char whiteChar);

void tape_free(TAPE *tape);

void tape_initialize(TAPE *tape, char *t);

//Se chegou no fim, cria um novo nó!
SYMBOL *tape_moveRight(TAPE *tape);

SYMBOL *tape_moveLeft(TAPE *tape);

SYMBOL *tape_move(TAPE *tape, char movement);

SYMBOL *tape_getActual(TAPE *tape);

char tape_read(TAPE *tape);

void tape_write(TAPE *tape, char chr);

void tape_print(TAPE *tape);
#endif
