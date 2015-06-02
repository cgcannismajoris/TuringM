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

	if((novo->name = (char*)malloc(strlen(name) + 1)) == NULL){

		free(novo);
		trgError_setDesc(STATE_EALLOC_MSG);
	
		return (NULL);
	}
	
	strcpy(novo->name, name);
	novo->type = type;

	return (novo);
}

void state_free(STATE *state){
	lista_free(state->transitions);
	free(state->name);
	free(state);
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

TRANSITION *state_getTransition(STATE *state, char readedChar){
	NODE *no = lista_search(state->transitions, &readedChar, transition_cmpReadChar);

	if(no != NULL)
		return (node_getData(no));

	return (NULL);
}


