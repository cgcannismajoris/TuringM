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

MACHINE *decoder_decode(char *filename, uint32_t qtdTapes){

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
	TAPE **tapes;
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
	
	token_free(token);

	if(table == NULL){
		//O erro já foi setado em decoder_loadAllStates
		//Basta limpar a memória

		alphabet_free(inputAlphabet);
		alphabet_free(outputAlphabet);
		trgLoader_free(loader);

		return (NULL);
	}
	
	//Obtém o estado inicial das fitas
	if((tapes = decoder_getTapes(loader, &lineCounter, qtdTapes, whiteChar)) == NULL){

		alphabet_free(inputAlphabet);
		alphabet_free(outputAlphabet);
		trgLoader_free(loader);

		return (NULL);
	}

	//Obtém a tabela de transições
	table = decoder_getTransitionTable(loader, &lineCounter, qtdTapes,
									   inputAlphabet, outputAlphabet, table);

	if(table == NULL){

		alphabet_free(inputAlphabet);
		alphabet_free(outputAlphabet);

		for(qtdTapes; qtdTapes > 0; qtdTapes--){
			tape_free(tapes[qtdTapes - 1]);
		}

		free(tapes);

		trgLoader_free(loader);
		
		return (NULL);
	}
	
	machine = machine_new(inputAlphabet, outputAlphabet, whiteChar, table, tapes, qtdTapes);

	return (machine);
}

TABLE *decoder_getTransitionTable(TRGLOADER *loader, uint64_t *lineCounter, 
								  uint32_t qtdTapes, ALPHABET *inputAlphabet, 
								  ALPHABET *outputAlphabet, TABLE *table){
	
	TOKENS *token;
	TRANSITION *transition;	

	while((token = decoder_getNextLineTokens(loader, lineCounter)) != NULL){
		
		if(decoder_verifTransition(token, qtdTapes, table, inputAlphabet, 
									outputAlphabet) != DECODER_VERIFTRANSITION_PASS){

			token_free(token);
			decoder_setErrorInLine(*lineCounter, DECODER_EUSER_INVALIDTRANSITION_MSG);
			table_free(table); 
			return (NULL);
		}
		
		transition = decoder_makeTransition(token, qtdTapes);
		
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
		return (NULL);
	}

	return (table);
}

TRANSITION *decoder_makeTransition(TOKENS *tokens, uint32_t qtdTapes){
	
	TRANSITION *transition;

	uint32_t i;

	char *readChars;
	char *writeChars;
	char *movements;
	
	if((readChars = (char*)malloc(sizeof(char) * qtdTapes)) == NULL){
		return (NULL);
	}

	if((writeChars = (char*)malloc(sizeof(char) * qtdTapes)) == NULL){
		free(readChars);
		return (NULL);
	}
	
	if((movements = (char*)malloc(sizeof(char) * qtdTapes)) == NULL){
		free(readChars);
		free(writeChars);
		return (NULL);
	}

	for(i = 1; i <= qtdTapes; i++){
		readChars[i - 1] = token_getToken(tokens, i)[0];
		writeChars[i - 1] = token_getToken(tokens, i + qtdTapes + 1)[0];
		movements[i - 1] = token_getToken(tokens, i + (2 * qtdTapes) + 1)[0];
	}
	
	transition = transition_new(token_getToken(tokens, 0), readChars, 
								token_getToken(tokens, qtdTapes + 1),
								writeChars, movements, qtdTapes);

	free(readChars);
	free(writeChars);
	free(movements);

	return (transition);
}

TAPE **decoder_getTapes(TRGLOADER *loader, uint64_t *lineCounter, uint32_t qtdTapes, char whiteChar){

	TAPE **tapes;
	TOKENS *token;
	int64_t counter;

	if((tapes = (TAPE**)malloc(sizeof(TAPE*) * qtdTapes)) == NULL){
		return (NULL);
	}

	for(counter = 0; counter < qtdTapes; counter++){
		
		if((tapes[counter] = tape_new(whiteChar)) == NULL){
			
			for(counter - 1; counter > 0; counter--){
				tape_free(tapes[counter]);
			}
			free(tapes);

			return (NULL);
		}

	
		if((token = decoder_getNextLineTokens(loader, lineCounter)) == NULL){
			for(counter - 1; counter > 0; counter--){
				tape_free(tapes[counter]);
			}
			free(tapes);

			return (NULL);
		}
	
		tape_initialize(tapes[counter], token_toStringWithoutSeparator(token));
	}

	return (tapes);
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
		if(table_addState(table, state_new(token_getToken(token, counter), 
								STATE_TYPE_INTERMEDIARY)) == TABLE_ERROR){
			table_free(table);
			token_free(token);
			return (NULL);
		}
	}

	//Obtém e Seta os estados finais
	table = decoder_getFinalStates(loader, lineCounter, table);
	
	token_free(token);

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
	
	token_free(token);

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
	char *line;

	line = trgLoader_getLine(loader);
	
	(*lineCounter) += 1;
	
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

int decoder_verifTransition(TOKENS *tokens, uint32_t qtdTapes, TABLE *table, 
							ALPHABET *inputAlphabet, ALPHABET *outputAlphabet){

	uint32_t i;

	if(token_getQtd(tokens) != (2 + (3 * qtdTapes))){ 
		return (DECODER_VERIFTRANSITION_ERROR_INVALIDQTD);
	}
	
	//O i <= qtdTapes é devido a maneira como o cálculo é realizado
	//ex: temos 4 fitas, logo 14 argumentos (2 para estados + 8 para lidos e escritos
	//+ 4 para movimentos). No pior caso acessaremos a posição (4 + (2 * 4) + 1) = 13,
	//que é a última posição do vetor de tokens;
	for(i = 1; i <= qtdTapes; i++){
		//Verifica se os simbolos e movimentos possuem apenas um caractere
		if(strlen(token_getToken(tokens, i)) != 1 ||
		   strlen(token_getToken(tokens, i + qtdTapes + 1)) != 1 ||
		   strlen(token_getToken(tokens, i + (2 * qtdTapes) + 1)) != 1){

			return (DECODER_VERIFTRANSITION_ERROR_INVALIDARGUMENT);
		}

		//Verifica se os símbolos estão presentes nos alfabetos
		if(alphabet_verif(inputAlphabet, token_getToken(tokens, i)[0]) < 0 ||
	alphabet_verif(outputAlphabet, token_getToken(tokens, i + qtdTapes + 1)[0]) < 0){

			return (DECODER_VERIFTRANSITION_ERROR_CHRNOTINALPHABET);
		}
		
		//Verifica se os movimentos definidos são válidos
		if(strcasecmp(token_getToken(tokens, i + (2 * qtdTapes) + 1), 
													TRANSITION_MOVE_LEFT_STR) != 0 && 
		   strcasecmp(token_getToken(tokens, i + (2 * qtdTapes) + 1), 
				   								TRANSITION_MOVE_RIGHT_STR) != 0 && 
		   strcasecmp(token_getToken(tokens, i + (2 * qtdTapes) + 1), 
				   									TRANSITION_STOP_STR) != 0){

			return (DECODER_VERIFTRANSITION_ERROR_INVALIDMOVEMENT);
		}
	}
	
	//Verifica se o estado atual é válido
	if(table_getState(table, token_getToken(tokens, 0)) == NULL){
		return (DECODER_VERIFTRANSITION_ERROR_UNDECLAREDSTATE);
	}	
	//Verifica se o estado destido é válido
	if(table_getState(table, token_getToken(tokens, qtdTapes + 1)) == NULL){
		return (DECODER_VERIFTRANSITION_ERROR_UNDECLAREDSTATE);
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
