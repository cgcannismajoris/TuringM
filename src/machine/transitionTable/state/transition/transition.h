/*
 * Nome do Arquivo:  stateTransition.h
 *       Descricao:  Implementação do TAD responsável por armazenar uma transição
 *       de estados.
 *
 * Exported functions from stateTransition.c.
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

#ifndef STATE_TRANSITION_HEADER
#define STATE_TRANSITION_HEADER

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../../../../trgError.h"

#include "../../../../linkedList/linkedList.h"
#include "../../../../decoder/scanner/tokens/tokens.h"

#define TRANSITION_EALLOC		NULL
#define TRANSITION_EALLOC_MSG	"Falha ao alocar memória para TRANSITIONTABLE."

typedef struct _stateTransition{

	char *actualState;
	char readChar;
	char *nextState;
	char writeChar;
	char move;

} STATETRANSITION, TRANSITION;

TRANSITION *transition_new(char *actualState, char readChar, char *nextState,
							char writeChar, char move);

char *transition_getActualState(TRANSITION *transition);

char transition_getReadChar(TRANSITION *transition);

char *transition_getNextState(TRANSITION *transition);

char transition_getWriteChar(TRANSITION *transition);

char transition_getMove(TRANSITION *transition);

int transition_cmpReadChar(const void *transition, const void *chr);
#endif
