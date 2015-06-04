/*
 * Nome do Arquivo:  stateTransition.c
 *       Descricao:  Implementação do TAD responsável por armazenar as transições de
 *       um estado.
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

#include "transition.h"

TRANSITION *transition_new(char *actualState, char readChar, char *nextState,
							char writeChar, char move){
	
	TRANSITION *novo = NULL;

	if((novo = (TRANSITION*)malloc(sizeof(TRANSITION))) == NULL){
		trgError_setDesc(TRANSITION_EALLOC_MSG);
		return (NULL);
	}

	if((novo->actualState = (char*)malloc(strlen(actualState) + 1)) == NULL){

		free(novo);

		trgError_setDesc(TRANSITION_EALLOC_MSG);
		return (NULL);
	}

	if((novo->nextState = (char*)malloc(strlen(nextState) + 1)) == NULL){

		free(novo->actualState);
		free(novo);

		trgError_setDesc(TRANSITION_EALLOC_MSG);
		return (NULL);
	}
	
	//Faz com que o idicador de movimento esteja dentro do padrão (maiúsculo)	
	if(move > 80)
		move = move - 32;

	novo->move = move;
	novo->readChar = readChar;
	novo->writeChar = writeChar;

	strcpy(novo->actualState, actualState);
	strcpy(novo->nextState, nextState);

	return (novo);
}

void transition_free(TRANSITION *transition){
	
	free(transition->actualState);
	free(transition->nextState);
	free(transition);

}

char *transition_getActualState(TRANSITION *transition){
	return (transition->actualState);
}

char transition_getReadChar(TRANSITION *transition){
	return (transition->readChar);
}

char *transition_getNextState(TRANSITION *transition){
	return (transition->nextState);
}

char transition_getWriteChar(TRANSITION *transition){
	return (transition->writeChar);
}

char transition_getMove(TRANSITION *transition){
	return (transition->move);
}

int transition_cmpReadChar(const void *chr, const void *transition){
	return (*((char*)chr) - (((TRANSITION*)transition)->readChar)); 
}

void transition_print(void *transition){
	
	TRANSITION *t = transition;

	printf("STATE\t\t= %s\nREAD_CHR\t= %c\nNEXT_STATE\t= %s\nTO_WRITE_CHR\t= %c\nMOVEMENT\t= %c\n", t->actualState, t->readChar, t->nextState, t->writeChar, t->move);

}
