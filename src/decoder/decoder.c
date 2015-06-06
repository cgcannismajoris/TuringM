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
	if((loader = trgLoader_new(filename)) == NULL){
		printf(DECODER_FILE_ERROR_MSG);
		printf("\n");
		
		return (NULL);
	}

	//Gera o alfabeto de entrada
	if((inputAlphabet = decoder_getAlphabet(loader, &lineCounter)) == NULL){
		
		trgLoader_free(loader);
		
		return (NULL);
	}

	//Gera o alfabeto de saída
	if((outputAlphabet = decoder_getAlphabet(loader, &lineCounter)) == NULL){
		
		alphabet_free(inputAlphabet);
		trgLoader_free(loader);
		
		return (NULL);
	}

	//Obtém o caractere branco e o estado inicial
	token = decoder_getNextLineTokens(loader, &lineCounter);
	
	if(token_getQtd(token) != 2){
		decoder_setErrorInLine(lineCounter, DECODER_EUSER_FEWARGUMENTS_MSG);
		
		alphabet_free(inputAlphabet);
		alphabet_free(outputAlphabet);
		trgLoader_free(loader);
			
		return (NULL);
	}

	//Obtém o caractere branco
	if(decoder_verifChr(token_getToken(token, 0)) != 0){
		decoder_setErrorInLine(lineCounter, NULL);
		
		alphabet_free(inputAlphabet);
		alphabet_free(outputAlphabet);
		trgLoader_free(loader);

		return (NULL);
	}
	whiteChar = (token_getToken(token, 0))[0];

	//Obtém a lista de todos os estados
	table = decoder_loadAllStates(loader, &lineCounter, token_getToken(token, 1));
	
	if(table == NULL){
		//O erro já foi setado em decoder_loadAllStates
		//Basta limpar a memória

		alphabet_free(inputAlphabet);
		alphabet_free(outputAlphabet);
		trgLoader_free(loader);

		return (NULL);
	}

	//Obtém o estado inicial da fita
	tape = decoder_getTape(loader, &lineCounter, whiteChar);
	if(table == NULL){
		//O erro já foi setado em decoder_loadAllStates
		//Basta limpar a memória

		alphabet_free(inputAlphabet);
		alphabet_free(outputAlphabet);
		trgLoader_free(loader);

		return (NULL);
	}

	//Obtém a tabela de transições
	table = decoder_getTransitionTable(loader, &lineCounter, inputAlphabet, 
														outputAlphabet, table);
	if(table == NULL){
		alphabet_free(inputAlphabet);
		alphabet_free(outputAlphabet);
		trgLoader_free(loader);
		return (NULL);
	}

	machine = machine_new(inputAlphabet, outputAlphabet, whiteChar, table, tape);

	return (machine);
}

TABLE *decoder_getTransitionTable(TRGLOADER *loader, uint64_t *lineCounter, 
								ALPHABET *inputAlphabet, ALPHABET *outputAlphabet, 
								TABLE *table){
	
	TOKENS *token;
	TRANSITION *transition;	

	while((token = decoder_getNextLineTokens(loader, lineCounter)) != NULL){
		if(decoder_verifTransition(token, inputAlphabet, outputAlphabet) != 0){
			token_free(token);
			decoder_setErrorInLine(*lineCounter, DECODER_EUSER_INVALIDTRANSITION_MSG);
			table_free(table);
			return (NULL);
		}
	
		transition = transition_new(token_getToken(token, 0), 
						token_getToken(token, 1)[0], token_getToken(token, 2), 
						token_getToken(token, 3)[0], token_getToken(token, 4)[0]);
		
		if(table_addTransition(table, transition) != TABLE_SUCCESS){
			trgError_setDesc(DECODER_EUSER_STATE_UNDECLARED_MSG);
			token_free(token);
			table_free(table);
			return (NULL);
		}

		token_free(token);
	}
	//Se não foram inseridas transições...	
	if(table_getQtdTransitions(table) == 0){
		trgError_setDesc(DECODER_EUSER_TRANSITIONSNOTDECLARED_MSG);
		table_free(table);
		table = NULL;
	}

	return (table);
}

TAPE *decoder_getTape(TRGLOADER *loader, uint64_t *lineCounter, char whiteChar){

	TAPE *tape;
	TOKENS *token;
	if((tape = tape_new(whiteChar)) == NULL){
		return (NULL);
	}

	if((token = decoder_getNextLineTokens(loader, lineCounter)) == NULL){
		return (NULL);
	}

	tape_initialize(tape, token_toStringWithoutSeparator(token));

	return (tape);
}

TABLE *decoder_loadAllStates(TRGLOADER *loader, uint64_t *lineCounter, char *startState){

	TABLE *table;
	uint32_t counter;
	TOKENS *token;

	if((table = table_new()) == NULL){
		return (NULL);
	}

	//seta o estado inicial
	decoder_setStartState(table, startState);
	
	//Obtém a lista de todos os estados
	token = decoder_getNextLineTokens(loader, lineCounter);

	for(counter = 0; counter < token_getQtd(token); counter++){
		table_addState(table, state_new(token_getToken(token, counter), 
								STATE_TYPE_INTERMEDIARY));
	}

	//Obtém e Seta os estados finais
	table = decoder_getFinalStates(loader, lineCounter, table);
	
	return (table);
}

void decoder_setStartState(TABLE *table, char *startState){
	table_addState(table, state_new(startState, STATE_TYPE_START));
}

TABLE *decoder_getFinalStates(TRGLOADER *loader, uint64_t *lineCounter, TABLE *table){

	uint32_t counter;
	TOKENS *token = decoder_getNextLineTokens(loader, lineCounter);

	for(counter = 0; counter < token_getQtd(token); counter++){
		STATE *state = table_getState(table, token_getToken(token, counter));

		if(state == NULL){
			//Erro: Estado não definido
			decoder_setErrorInLine(*lineCounter, DECODER_EUSER_STATE_UNDECLARED_MSG);

			table_free(table);

			return (NULL);
		}

		state_setType(state, STATE_TYPE_FINAL);
	}

	return (table);
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

	if(token_getQtd(tokens) != 5){
		return (DECODER_VERIFTRANSITION_ERROR_INVALIDQTD);
	}

	if(strlen(token_getToken(tokens, 1)) != 1 ||
	   strlen(token_getToken(tokens, 3)) != 1 || 
	   strlen(token_getToken(tokens, 4)) != 1){

		return (DECODER_VERIFTRANSITION_ERROR_INVALIDARGUMENT);
	}
	
	if(alphabet_verif(inputAlphabet, token_getToken(tokens, 1)[0]) < 0 ||
	   alphabet_verif(outputAlphabet, token_getToken(tokens, 3)[0]) < 0){

		return (DECODER_VERIFTRANSITION_ERROR_CHRNOTINALPHABET);
	}
	
	if(strcasecmp(token_getToken(tokens, 4), TRANSITION_MOVE_LEFT_STR) != 0 && 
	   strcasecmp(token_getToken(tokens, 4), TRANSITION_MOVE_RIGHT_STR) != 0 && 
	   strcasecmp(token_getToken(tokens, 4), TRANSITION_STOP_STR) != 0){

		return (DECODER_VERIFTRANSITION_ERROR_INVALIDMOVEMENT);
	}

	return (DECODER_VERIFTRANSITION_PASS);	

}

void decoder_setErrorInLine(uint64_t lineCounter, char *aditionalStr){
	
	char *errorStr = (char*)malloc(strlen(DECODER_EUSER_INVALID_LINE_MSG) + 30 + 
								   strlen(aditionalStr));

	if(errorStr == NULL){
		//Fudeu, deu erro dentro do erro! hahahah
		trgError_setDesc("DECODER: ERRO AO PROCESSAR ERRO - FALHA NA ALOCAÇÃO DE \
MEMÓRIA!");
		return;
	}

	strncpy(errorStr, DECODER_EUSER_INVALID_LINE_MSG, 
						strlen(DECODER_EUSER_INVALID_LINE_MSG) + 1);
	
	if(aditionalStr == NULL){
		snprintf(errorStr + strlen(DECODER_EUSER_INVALID_LINE_MSG), 29, "%lu", 
						lineCounter);
	}
	else{
		snprintf(errorStr + strlen(DECODER_EUSER_INVALID_LINE_MSG), 
						29 + strlen(aditionalStr), "%lu\n%s", 
						lineCounter, aditionalStr);

	}

	trgError_setDesc(errorStr);		

	free(errorStr);
}
