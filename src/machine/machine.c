/*
 * Nome do Arquivo:  machine.c
 *       Descricao:  Implementação do componente executor da máquina.
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

#include "machine.h"

MACHINE *machine_new(ALPHABET *inputAlphabet, ALPHABET *outputAlphabet, 
						char whiteChar, TRANSITIONTABLE *table, TAPE *tape){

	MACHINE *novo;

	if((novo = (MACHINE*)malloc(sizeof(MACHINE))) == NULL){
		trgError_setDesc(MACHINE_EALLOC_MSG);
		return (NULL);
	}

	novo->inputAlphabet = inputAlphabet;
	novo->outputAlphabet = outputAlphabet;
	novo->whiteChar = whiteChar;
	novo->table = table;
	novo->tape = tape;

	return (novo);
}

void machine_free(MACHINE *machine){
	alphabet_free(machine->inputAlphabet);
	alphabet_free(machine->outputAlphabet);
	table_free(machine->table);
	tape_free(machine->tape);
	free(machine);
}

int machine_run(MACHINE *machine){

	TRANSITION *transition;
	STATE *actualState;	

	tape_print(machine->tape);

	actualState = table_getStartState(machine->table);

	while(state_getType(actualState) != STATE_TYPE_FINAL){

		transition = table_getTransition(machine->table, 
							state_getName(actualState), 
							tape_read(machine->tape));

		if(transition != NULL){
			
			tape_write(machine->tape, transition_getWriteChar(transition));
	
			switch(transition_getMove(transition)){
				case TRANSITION_MOVE_RIGHT:
					tape_moveRight(machine->tape);
					break;
	
				case TRANSITION_MOVE_LEFT:
					tape_moveLeft(machine->tape);
					break;
			}
	
			actualState = table_getState(machine->table, transition_getNextState(transition));
			tape_print(machine->tape);
		}
		else{
				tape_print(machine->tape);
				textcolor(RED);
				printf("MACHINE: NÃO CHEGOU A UM ESTADO FINAL!\n");
				textcolor(WHITE);
				return (-1);
		}
	}

	textcolor(GREEN);
	printf("MACHINE: EXECUTADO COM SUCESSO!\n");
	textcolor(WHITE);

	return (0);
}

