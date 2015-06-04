/*
 * Nome do Arquivo:  decoder.c
 *       Descricao:  Implementação do módulo de decodificação do arquivo de entrada.
 * 
 * Decoder for TuringM.
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

#include "decoder.h"

#include <stdio.h>
MACHINE *decoder_decode(char *filename){

	char *line = NULL;
	char *tmpStr;

	uint64_t lineCounter = 0;
	uint32_t counter;

	TRGLOADER *loader = NULL;

	TOKENS *token;
	
	ALPHABET *inputAlphabet;
	ALPHABET *outputAlphabet;
	TRANSITIONTABLE *table;
	TRANSITION *transition;
	TAPE *tape;
	char whiteChar;

	MACHINE *machine;

	if((table = table_new()) == NULL){
		return (NULL);
	}

	if((loader = trgLoader_new(filename)) == NULL){
		printf(DECODER_FILE_ERROR_MSG);
		printf("\n");
		table_free(table);
		return (NULL);
	}

	//Gera o alfabeto de entrada
	if((inputAlphabet = decoder_getAlphabet(loader, &lineCounter)) == NULL){
		trgLoader_free(loader);
		table_free(table);
		return (NULL);
	}

	//Gera o alfabeto de saída
	if((outputAlphabet = decoder_getAlphabet(loader, &lineCounter)) == NULL){
		alphabet_free(inputAlphabet);
		trgLoader_free(loader);
		table_free(table);
		return (NULL);
	}

	//Obtém o caractere branco e o estado inicial
	token = decoder_getNextLineTokens(loader, &lineCounter);

	//Obtém o caractere branco
	if(decoder_verifChr(token_getToken(token, 0)) != 0){

		decoder_setErrorInLine(lineCounter);

		alphabet_free(inputAlphabet);
		trgLoader_free(loader);
		table_free(table);

		return (NULL);
	}
	whiteChar = (token_getToken(token, 0))[0];

	//Obtém o estado inicial
	table_addState(table, state_new(token_getToken(token, 1), STATE_TYPE_START));
	
	//Obtém a lista de todos os estados
	token = decoder_getNextLineTokens(loader, &lineCounter);

	for(counter = 0; counter < token_getQtd(token); counter++){
		table_addState(table, state_new(token_getToken(token, counter), 
								STATE_TYPE_INTERMEDIARY));
	}

	//Obtém e Seta os estados finais
	token = decoder_getNextLineTokens(loader, &lineCounter);

	for(counter = 0; counter < token_getQtd(token); counter++){
		STATE *state = table_getState(table, token_getToken(token, counter));

		if(state == NULL){
			//Erro: Estado não definido
			printf("ERRO!");
			return (NULL);
		}

		state_setType(state, STATE_TYPE_FINAL);
	}

	//Obtém o estado inicial da fita
	tape = tape_new(TAPE_START_SYMBOL, whiteChar);
	token = decoder_getNextLineTokens(loader, &lineCounter);
	tape_initialize(tape, token_toStringWithoutSeparator(token));

	//Obtém a tabela de transições
	while((token = decoder_getNextLineTokens(loader, &lineCounter)) != NULL){
		if(decoder_verifTransition(token, inputAlphabet, outputAlphabet) != 0){
			decoder_setErrorInLine(lineCounter);
			return (NULL);
		}
	
		transition = transition_new(token_getToken(token, 0), 
						token_getToken(token, 1)[0], token_getToken(token, 2), 
						token_getToken(token, 3)[0], token_getToken(token, 4)[0]);
		
		if(table_addTransition(table, transition) != TABLE_SUCCESS){
			return (NULL);
		}
	}
	
	machine = machine_new(inputAlphabet, outputAlphabet, whiteChar, table);

	return (machine);
}

ALPHABET *decoder_getAlphabet(TRGLOADER *loader, uint64_t *lineCounter){

	TOKENS *token;
	char *tmpStr;
	ALPHABET *alphabet;

	//Se não conseguir gerar os tokens retorna erro
	if((token = decoder_getNextLineTokens(loader, lineCounter)) == NULL){
		return (NULL);
	}
	
	//Se consegue transferir os tokens para uma string
	if((tmpStr = token_toStringWithoutSeparator(token)) != NULL){
		//Gera o alfabeto e desaloca memória que não é mais útil
		alphabet = alphabet_new(tmpStr, strlen(tmpStr));
		free(tmpStr);
	}
		
	token_free(token);

	return (alphabet);
}

TOKENS *decoder_getNextLineTokens(TRGLOADER *loader, uint64_t *lineCounter){

	TOKENS *token = NULL;
	char *line = trgLoader_getLine(loader);

	(*lineCounter)++;

	if(line != NULL){
		token = scanner_scan(line, NULL, DECODER_TOKEN_SEPARATOR, 0);
	}
	
	return (token);
}

int decoder_verifChr(char *token){
	if(strlen(token) != 1){
		return (-1);
	}

	return (0);
}

int decoder_verifTransition(TOKENS *tokens, ALPHABET *inputAlphabet, 
												ALPHABET *outputAlphabet){

	if(token_getQtd(tokens) != 5 || strlen(token_getToken(tokens, 1)) != 1 ||
	   strlen(token_getToken(tokens, 3)) != 1 || 
	   strlen(token_getToken(tokens, 4)) != 1){

		return (-1);
	}
	
	if(alphabet_verif(inputAlphabet, token_getToken(tokens, 1)[0]) < 0 ||
	   alphabet_verif(outputAlphabet, token_getToken(tokens, 3)[0]) < 0){
		return (-1);
	}
	
	if(strcasecmp(token_getToken(tokens, 4), TRANSITION_MOVE_LEFT_STR) != 0 && 
	   strcasecmp(token_getToken(tokens, 4), TRANSITION_MOVE_RIGHT_STR) != 0 && 
	   strcasecmp(token_getToken(tokens, 4), TRANSITION_STOP_STR) != 0){
		return (-1);
	}

	return (0);	

}

void decoder_setErrorInLine(uint64_t lineCounter){
	//Seta o erro
	char *errorStr = (char*)malloc(strlen(DECODER_EUSER_INVALID_LINE) + 25);

	if(errorStr == NULL){
		//Fudeu, deu erro dentro do erro! hahahah
		trgError_setDesc("DECODER: ERRO AO PROCESSAR ERRO - FALHA NA ALOCAÇÃO DE \
MEMÓRIA!");
		return;
	}
	
	strncpy(errorStr, DECODER_EUSER_INVALID_LINE, 
						strlen(DECODER_EUSER_INVALID_LINE) + 1);

	snprintf(errorStr + strlen(DECODER_EUSER_INVALID_LINE), 24, "%lu", 
					lineCounter);

	trgError_setDesc(errorStr);		

	free(errorStr);
}
