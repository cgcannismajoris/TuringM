/*
 * Nome do Arquivo:  state.h
 *       Descricao:  Definição do TAD responsável por armazenar as informações
 *       de um estado.
 *
 * Exported functions from state.c.
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

#ifndef STATE_HEADER
#define STATE_HEADER

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../../trgError.h"

#include "stateTransition/stateTransition.h"
#include "../../linkedList/linkedList.h"
#include "../../decoder/scanner/tokens/tokens.h"

#define STATE_ERROR               NULL
#define STATE_ERROR_MSG           "Falha ao alocar memória para TRANSITIONTABLE."

#define STATE_TYPE_START 			1
#define STATE_TYPE_FINAL 			2
#define STATE_TYPE_INTERMEDIARY 	3

typedef struct _state{
	
	char *name;

	int type;

	STATETRANSITION *transitions;
	
} STATE;

#endif
