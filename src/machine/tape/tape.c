/*
 * Nome do Arquivo:  tape.c
 *       Descricao:  Implementação do gerenciador da fita da máquina.
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


#include "tape.h"

TAPE *tape_new(char whiteChar){
	
	TAPE *novo;
	
	if((novo = (TAPE*)malloc(sizeof(TAPE))) == NULL){
		trgError_setDesc(TAPE_EALLOC_MSG);
		return (NULL);
	}

	if((novo->tape = lista_new()) == NULL){
		trgError_setDesc(TAPE_EALLOC_MSG);

		free(novo);

		return (NULL);
	}

	novo->whiteChar = whiteChar;	
	novo->actualSymbol = lista_getRaiz(novo->tape);
	return (novo);
}

void tape_free(TAPE *tape){
	lista_free(tape->tape, free);
	free(tape);
}

void tape_initialize(TAPE *tape, char *t){

	uint64_t i;
	for(i = 0; i < strlen(t); i++){
		tape_moveRight(tape);
		tape_write(tape, t[i]);
	}

	tape->actualSymbol = lista_getRaiz(tape->tape);
}

//Se chegou no fim, cria um novo nó!
SYMBOL *tape_moveRight(TAPE *tape){
	
	if(node_getProx(tape->actualSymbol) == NULL){

		SYMBOL *simbolo = (SYMBOL*)malloc(sizeof(SYMBOL));
		NODE *novo = lista_node_new(simbolo);
		
		simbolo->chr = tape->whiteChar;
		lista_insertLastNode(tape->tape, novo);
		tape->actualSymbol = lista_getLast(tape->tape);
	}
	else{
		tape->actualSymbol = node_getProx(tape->actualSymbol);
	}

	return (node_getData(tape->actualSymbol));
}

SYMBOL *tape_moveLeft(TAPE *tape){

	if(node_getAnte(tape->actualSymbol) == NULL){
		return (NULL);
	}

	tape->actualSymbol = node_getAnte(tape->actualSymbol);

	return (node_getData(tape->actualSymbol));
}

SYMBOL *tape_move(TAPE *tape, char movement){
	switch(movement){
		case (TAPE_MOVE_RIGHT):
		case (TAPE_MOVE_RIGHT + 32):
			return (tape_moveRight(tape));

		case (TAPE_MOVE_LEFT):
		case (TAPE_MOVE_LEFT + 32):
			return (tape_moveLeft(tape));

		default:
			return (tape_getActual(tape));
	}
}

SYMBOL *tape_getActual(TAPE *tape){
	return (node_getData(tape->actualSymbol));
}

char tape_read(TAPE *tape){
	return (((SYMBOL*)node_getData(tape->actualSymbol))->chr);
}

void tape_write(TAPE *tape, char chr){
	((SYMBOL*)node_getData(tape->actualSymbol))->chr = chr;
}

void symbol_showNaTela(void *symbol){
	printf("%c ", ((SYMBOL*)symbol)->chr);
}

void tape_print(TAPE *tape){
	
	uint32_t i;
	NODE *tmp;

	if(lista_getQuant(tape->tape) == 0){
		return;
	}

//	lista_printLista(tape->tape, symbol_showNaTela);	
	
	tmp = lista_getRaiz(tape->tape);
	
	for(i = 0; i < lista_getQuant(tape->tape); i++){
		
		if(tmp == tape->actualSymbol){
			textcolor(GREEN);
			printf("%c ", ((SYMBOL*)node_getData(tmp))->chr);
			textcolor(WHITE);
		}
		else{
			printf("%c ", ((SYMBOL*)node_getData(tmp))->chr);
		}
		tmp = node_getProx(tmp);	
	}
	printf("\n");
}
