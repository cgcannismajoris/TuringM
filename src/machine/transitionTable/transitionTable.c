/*
 * Nome do Arquivo:  transitionTable.c
 *       Descricao:  Implementação do gerenciador da tabela de transições.
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


#include "transitionTable.h"

TABLE *table_new(){

	TABLE *novo = (TABLE*)malloc(sizeof(TABLE));
	
	novo->states = lista_new();
	novo->qtdTransitions = 0;
	return (novo);
}

void table_free(TABLE *table){
	lista_free(table->states, state_free);
	free(table);
}

int table_addState(TABLE *table, STATE *state){

	NODE *novo = NULL;
	
	if(state == NULL)
		return (TABLE_ERROR);

	if(table_getState(table, state_getName(state)) != NULL){
		//Estado ja existe
		return (TABLE_SUCCESS);
	}

	if((novo = lista_node_new(state)) == NULL){
		//Erro ao alocar no
		trgError_setDesc(TABLE_EALLOC_MSG);
		return (TABLE_ERROR);
	}

	lista_insertLastNode(table->states, novo);

	return (TABLE_SUCCESS);
}

int table_addTransition(TABLE *table, TRANSITION *transition){

	STATE *state = table_getState(table, transition_getActualState(transition));
	
	if(state == NULL){
		return (TABLE_ERROR);
	}

	state_addTransition(state, transition);
	table->qtdTransitions++;
	return (TABLE_SUCCESS);
}

TRANSITION *table_getTransition(TABLE *table, char *actualState, char *readedChars){

	TRANSITION *transition = NULL;
	STATE *state = table_getState(table, actualState);
	
	if(state == NULL){
		return (NULL);
	}

	transition = state_getTransition(state, readedChars);

	return (transition);

}

STATE *table_getState(TABLE *table, char *state){
	
	NODE *no = lista_search(table->states, state, state_cmpName);

	return (node_getData(no));
}

STATE *table_getStartState(TABLE *table){

	int id = STATE_TYPE_START;

	NODE *no = lista_search(table->states, &id, state_isThisType);

	return (node_getData(no));
}

uint64_t table_getQtdTransitions(TABLE *table){
	return (table->qtdTransitions);
}

void table_print(TABLE *table){
	printf("TABELA DE TRANSIÇÕES:\n");
	printf("QTD_TRANSITIONS = %lu\n", table->qtdTransitions);
	printf("Lista de estados e transições:\n");
	lista_printLista(table->states, state_print);
}

