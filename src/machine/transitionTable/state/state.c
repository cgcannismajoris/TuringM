/*
 * Nome do Arquivo:  transitionTable.c
 *       Descricao:  Implementação do TAD responsável por armazenar as
 *       informações de um estado e suas transições.
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

#include "state.h"

STATE *state_new(char *name, int type){
	
	STATE *novo = NULL;
	
	if((novo = (STATE*)malloc(sizeof(STATE))) == NULL){
		trgError_setDesc(STATE_EALLOC_MSG);
		return (NULL);
	}
	
	if((novo->transitions = lista_new()) == NULL){

		free(novo);
		trgError_setDesc(STATE_EALLOC_MSG);
	
		return (NULL);
	}

	if((novo->name = (char*)malloc((sizeof(char) * strlen(name)) + 1)) == NULL){

		trgError_setDesc(STATE_EALLOC_MSG);

		free(novo);
	
		return (NULL);
	}
	
	strcpy(novo->name, name);
	novo->type = type;

	return (novo);
}

void _state_free(STATE *state){
	lista_free(state->transitions, transition_free);
	free(state->name);
	free(state);
}

void state_free(void *state){
	_state_free((STATE*)state);
}


void state_addTransition(STATE *state, TRANSITION *transition){
	NODE *no = lista_node_new(transition);
	lista_insertLastNode(state->transitions, no);
}

char *state_getName(STATE *state){
	return (state->name);
}

int state_getType(STATE *state){
	return (state->type);
}

void state_setType(STATE *state, int type){
	state->type = type;
}

TRANSITION *state_getTransition(STATE *state, char *readedChars){

	NODE *no = lista_search(state->transitions, readedChars, transition_cmpReadChar);
	return (node_getData(no));
}

int state_cmpName(const void *name, const void *state){
	return(strcmp(name, ((STATE*)state)->name));
}

int state_isThisType(const void *type, const void *state){
	return (((STATE*)state)->type - *((int*)type));
}

void state_print(void *state){
	printf("NAME = %s\n", ((STATE*)state)->name);
	printf("TYPE = %s\n", 
					((STATE*)state)->type == STATE_TYPE_START ? 
					"START" : ((STATE*)state)->type == STATE_TYPE_INTERMEDIARY ? 
					"INTERMEDIARY" : "FINAL");
	lista_printLista(((STATE*)state)->transitions, transition_print);
	printf("\n");
}
