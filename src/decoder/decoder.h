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

#define DECODER_EUSER_INVALID_LINE "DECODER: Erro na linha: "

#define DECODER_TOKEN_SEPARATOR	" \t"

MACHINE *decoder_decode(char *filename);

ALPHABET *decoder_getAlphabet(TRGLOADER *loader, uint64_t *lineCounter);

TOKENS *decoder_getNextLineTokens(TRGLOADER *loader, uint64_t *lineCounter);

int decoder_verifChr(char *token);

int decoder_verifTransition(TOKENS *tokens, ALPHABET *inputAlphabet, 
												ALPHABET *outputAlphabet);

void decoder_setErrorInLine(uint64_t lineCounter);

#endif
