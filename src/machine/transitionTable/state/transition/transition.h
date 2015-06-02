/*
 * Nome do Arquivo:  stateTransition.h
 *       Descricao:  Implementação do gerenciador da tabela de transições.
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

#define STATE_TRANSITION_ERROR               NULL
#define STATE_TRANSITION_ERROR_MSG           "Falha ao alocar memória para TRANSITIONTABLE."

typedef struct _stateTransition{

	TOKENS *transitions;
	uint32_t qtdTransitions;

} STATETRANSITION;


#endif
