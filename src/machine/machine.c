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
						char whiteChar, TABLE *table, TAPE **tapes, 
						uint32_t qtdTapes){

	MACHINE *novo;

	if((novo = (MACHINE*)malloc(sizeof(MACHINE))) == NULL){
		trgError_setDesc(MACHINE_EALLOC_MSG);
		return (NULL);
	}

	novo->inputAlphabet = inputAlphabet;
	novo->outputAlphabet = outputAlphabet;
	novo->whiteChar = whiteChar;
	novo->table = table;
	novo->tapes = tapes;
	novo->qtdTapes = qtdTapes;

	return (novo);
}

void machine_free(MACHINE *machine){
	
	alphabet_free(machine->inputAlphabet);
	alphabet_free(machine->outputAlphabet);
	table_free(machine->table);

	//Desaloca as fitas
	for(machine->qtdTapes; machine->qtdTapes > 0; (machine->qtdTapes)--){
		tape_free((machine->tapes)[(machine->qtdTapes) - 1]);
	}
	
	free(machine);
}

int machine_run(MACHINE *machine){

	char *tmp;
	TRANSITION *transition;
	STATE *actualState;	

	machine_printTapes(machine);

	actualState = table_getStartState(machine->table);

	while(state_getType(actualState) != STATE_TYPE_FINAL){

		transition = table_getTransition(machine->table, 
							state_getName(actualState), 
							(tmp = machine_readTapes(machine)));

		if(tmp != NULL)
			free(tmp);

		if(transition != NULL){		
	
			machine_writeTapes(machine, transition_getWriteChar(transition));
	
			machine_moveTapes(machine, transition_getMove(transition));	

			actualState = table_getState(machine->table, 
												transition_getNextState(transition));
			machine_printTapes(machine);
		}

		else{
				machine_printTapes(machine);
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

char *machine_readTapes(MACHINE *machine){
	
	char *readed;
	uint32_t counter;

	if((readed = (char*)malloc(sizeof(char) * (machine->qtdTapes))) == NULL){
		trgError_setDesc(MACHINE_EALLOC_MSG);
		return (NULL);
	}

	for(counter = 0; counter < machine->qtdTapes; counter++){
		readed[counter] = tape_read((machine->tapes)[counter]);
	}

	return (readed);
}

void machine_writeTapes(MACHINE *machine, char *toWrite){

	uint32_t counter;

	for(counter = 0; counter < machine->qtdTapes; counter++){
		tape_write((machine->tapes)[counter], toWrite[counter]);
	}

}

void machine_moveTapes(MACHINE *machine, char *movements){

	uint32_t counter;

	for(counter = 0; counter < machine->qtdTapes; counter++){
		tape_move((machine->tapes)[counter], movements[counter]);
	}
}

void machine_printTapes(MACHINE *machine){

	uint32_t counter;

	for(counter = 0; counter < machine->qtdTapes; counter++){
		printf("FITA %u: ", counter);
		tape_print((machine->tapes)[counter]);
	}
	printf("\n");

}
