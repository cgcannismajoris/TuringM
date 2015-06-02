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

	TRGLOADER *loader = NULL;

	TOKENS *token;
	
	ALPHABET *inputAlphabet;
	ALPHABET *outputAlphabet;
	TRANSITIONTABLE *table;
	char whiteChar;

	if((loader = trgLoader_new(filename)) == NULL){
		printf(DECODER_FILE_ERROR_MSG);
		printf("\n");
		return (NULL);
	}

	//Gera o alfabeto de entrada
	line = trgLoader_getLine(loader);
	token = scanner_scan(line, NULL, " \t", 0);
	tmpStr = token_toStringWithoutSeparator(token);
	inputAlphabet = alphabet_new(tmpStr, strlen(tmpStr));
	
	token_free(token);
	free(tmpStr);
	
	//Gera o alfabeto de saída
	line = trgLoader_getLine(loader);
	token = scanner_scan(line, NULL, " \t", 0);
	tmpStr = token_toStringWithoutSeparator(token);
	outputAlphabet = alphabet_new(tmpStr, strlen(tmpStr));

	token_free(token);
	free(tmpStr);

	//Obtém o caractere branco e o estado inicial


	return ((MACHINE*)loader);
}
