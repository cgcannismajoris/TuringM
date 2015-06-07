/*
 * Nome do Arquivo:  decoder.h
 *       Descricao:  Módulo para decodificação do arquivo de entrada.
 *
 * Exported functions from decoder.c.
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


#ifndef DECODER_HEADER
#define DECODER_HEADER

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../trgError.h"

#include "trgLoader/trgLoader.h"
#include "scanner/scanner.h"

#include "../machine/machine.h"

#define DECODER_EALLOC		NULL
#define DECODER_EALLOC_MSG	"Falha ao alocar memória para DECODER."

#define DECODER_FILE_ERROR	-1
#define DECODER_FILE_ERROR_MSG	"DECODER: Falha ao manipular arquivo."

#define DECODER_EUSER_INVALID_LINE_MSG "DECODER: Erro na linha: "

#define DECODER_EUSER_FEWARGUMENTS_MSG "DECODER: Quantidade incorreta de termos."
#define DECODER_EUSER_INVALIDTRANSITION_MSG "DECODER: Erro na declaração da transição."
#define DECODER_EUSER_STATE_UNDECLARED_MSG "DECODER: Estado não declarado."
#define DECODER_EUSER_TRANSITIONSNOTDECLARED_MSG "DECODER: Nenhuma transição declarada."

#define DECODER_TOKEN_SEPARATOR	" \t"

#define DECODER_VERIFTRANSITION_PASS					0
#define DECODER_VERIFTRANSITION_ERROR_INVALIDQTD		-1
#define DECODER_VERIFTRANSITION_ERROR_INVALIDARGUMENT	-2
#define DECODER_VERIFTRANSITION_ERROR_CHRNOTINALPHABET	-3
#define DECODER_VERIFTRANSITION_ERROR_INVALIDMOVEMENT	-4
#define DECODER_VERIFTRANSITION_ERROR_UNDECLAREDSTATE	-5

MACHINE *decoder_decode(char *filename, uint32_t qtdTapes);

TABLE *decoder_getTransitionTable(TRGLOADER *loader, uint64_t *lineCounter, uint32_t qtdTapes, 
								ALPHABET *inputAlphabet, ALPHABET *outputAlphabet, 
								TABLE *table);

TRANSITION *decoder_getTransition(TRGLOADER *loader, uint64_t *lineCounter, uint32_t qtdTapes,
								  ALPHABET *inputAlphabet, ALPHABET *outputAlphabet,
								  TABLE *table);

TRANSITION *decoder_makeTransition(TOKENS *token, uint32_t qtdTapes);

TAPE **decoder_getTapes(TRGLOADER *loader, uint64_t *lineCounter, uint32_t qtdTapes, char whiteChar);

TABLE *decoder_loadAllStates(TRGLOADER *loader, uint64_t *lineCounter, char *startState);

void decoder_setStartState(TABLE *table, char *startState);

TABLE *decoder_getFinalStates(TRGLOADER *loader, uint64_t *lineCounter, TABLE *table);

ALPHABET *decoder_getAlphabet(TRGLOADER *loader, uint64_t *lineCounter);

TOKENS *decoder_getNextLineTokens(TRGLOADER *loader, uint64_t *lineCounter);

int decoder_verifChr(char *token);

int decoder_verifTransition(TOKENS *tokens, uint32_t qtdTapes, TABLE *table, 
							ALPHABET *inputAlphabet, ALPHABET *outputAlphabet);

void decoder_setErrorInLine(uint64_t lineCounter, char *aditionalStr);

#endif
