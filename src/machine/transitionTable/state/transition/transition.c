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

TRANSITION *transition_new(char *actualState, char *readChar, char *nextState,
							char *writeChar, char *move, uint32_t qtdTapes){
	
	TRANSITION *novo = NULL;
	uint32_t counter;

	if((novo = (TRANSITION*)malloc(sizeof(TRANSITION))) == NULL){
		trgError_setDesc(TRANSITION_EALLOC_MSG);
		return (NULL);
	}

	if((novo->actualState = (char*)malloc(sizeof(char) * (strlen(actualState) + 1))) == NULL){

		free(novo);

		trgError_setDesc(TRANSITION_EALLOC_MSG);
		return (NULL);
	}

	if((novo->readChar = (char*)malloc(sizeof(char) * qtdTapes)) == NULL){

		free(novo->actualState);
		free(novo);

		trgError_setDesc(TRANSITION_EALLOC_MSG);
		return (NULL);
	}

	if((novo->nextState = (char*)malloc(sizeof(char) * (strlen(nextState) + 1))) == NULL){

		free(novo->actualState);
		free(novo->readChar);
		free(novo);

		trgError_setDesc(TRANSITION_EALLOC_MSG);
		return (NULL);
	}


	if((novo->writeChar = (char*)malloc(sizeof(char) * qtdTapes)) == NULL){

		free(novo->actualState);
		free(novo->readChar);
		free(novo->nextState);
		free(novo);

		trgError_setDesc(TRANSITION_EALLOC_MSG);
		return (NULL);
	}

	if((novo->move = (char*)malloc(sizeof(char) * qtdTapes)) == NULL){

		free(novo->actualState);
		free(novo->readChar);
		free(novo->nextState);
		free(novo->move);
		free(novo);

		trgError_setDesc(TRANSITION_EALLOC_MSG);
		return (NULL);
	}

	//Faz com que o idicador de movimento esteja dentro do padrão (maiúsculo)	
	for(counter = 0; counter < qtdTapes; counter++){
		if((novo->move)[counter] > 80){
			(novo->move)[counter] = (novo->move)[counter] - 32;
		}
	}
	

	memcpy(novo->move, move, qtdTapes);
	memcpy(novo->readChar, readChar, qtdTapes);
	memcpy(novo->writeChar, writeChar, qtdTapes);

	strcpy(novo->actualState, actualState);
	strcpy(novo->nextState, nextState);

	novo->qtdTapes = qtdTapes;

	return (novo);
}

void _transition_free(TRANSITION *transition){

	free(transition->actualState);
	free(transition->readChar);
	free(transition->nextState);
	free(transition->writeChar);
	free(transition->move);
	free(transition);

}

void transition_free(void *transition){
	_transition_free((TRANSITION*)transition);
}

char *transition_getActualState(TRANSITION *transition){
	return (transition->actualState);
}

char *transition_getReadChar(TRANSITION *transition){
	return (transition->readChar);
}

char *transition_getNextState(TRANSITION *transition){
	return (transition->nextState);
}

char *transition_getWriteChar(TRANSITION *transition){
	return (transition->writeChar);
}

char *transition_getMove(TRANSITION *transition){
	return (transition->move);
}

uint32_t transition_getQtdTapes(TRANSITION *transition){
	return (transition->qtdTapes);
}

int transition_cmpReadChar(const void *chars, const void *transition){
	return (strncmp(chars, ((TRANSITION*)transition)->readChar, ((TRANSITION*)transition)->qtdTapes));
}

void transition_print(void *transition){
	
	uint32_t i;

	printf("  STATE\t\t= %s\n", ((TRANSITION*)transition)->actualState);
	
	printf("  READ_CHR\t= ");
	for(i = 0; i < ((TRANSITION*)transition)->qtdTapes; i++){
		printf("%c ", ((TRANSITION*)transition)->readChar[i]);
	}
	printf("\n");

	printf("  NEXT_STATE\t= %s\n", ((TRANSITION*)transition)->nextState);

	printf("  WRITE_CHR\t= ");
	for(i = 0; i < ((TRANSITION*)transition)->qtdTapes; i++){
		printf("%c ", ((TRANSITION*)transition)->writeChar[i]);
	}
	printf("\n");

	printf("  MOVEMENT\t= ");
	for(i = 0; i < ((TRANSITION*)transition)->qtdTapes; i++){
		printf("%c ", ((TRANSITION*)transition)->move[i]);
	}
	printf("\n");

	printf("  QTD_TAPES\t= %u\n\n", ((TRANSITION*)transition)->qtdTapes);
}
