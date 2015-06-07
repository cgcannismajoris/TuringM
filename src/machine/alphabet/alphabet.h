/*
 * Nome do Arquivo:  alphabet.h
 *       Descricao:  Gerenciador dos alfabetos da máquina.
 *
 * Exported functions from alphabet.c.
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

#ifndef ALPHABET_HEADER
#define ALPHABET_HEADER

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../../trgError.h"

#define ALPHABET_ERROR               NULL
#define ALPHABET_ERROR_MSG           "Falha ao alocar memória para ALPHABET."

typedef struct _alphabet{
	char 		*letters;
	uint32_t 	qtd;
} ALPHABET;


/* -> ALPHABET *alphabet_new(char* letters, uint32_t qtdLetters)
 * 
 * - DESCRIÇÃO: Instancia um novo alfabeto.
 *
 * - PARÂMETROS: 
 *      -> char *letters: Letras do alfabeto.
 *      -> uint32_t n_ignore: Total de letras do alfabeto.
 *
 * - RETORNO: Estrutura do tipo ALPHABET contendo os tokens gerados.
 *   	-> Se NULL    - Erro na operação.
 *   	-> Se != NULL - Sucesso na operação.
 */
ALPHABET *alphabet_new(char* letters, uint32_t qtdLetters);

/* -> void alphabet_free(ALPHABET *alphabet)
 *
 * - DESCRIÇÃO: Destrói uma estrutura existente em memória.
 *
 * - PARÂMETROS: 
 *      -> ALPHABET *alphabet: Estrutura a ser destruída.
 *
 * - RETORNO: void.
 */
void alphabet_free(ALPHABET *alphabet);

/* -> int alphabet_verif(ALPHABET *alphabet, char letter)
 *
 * - DESCRIÇÃO: Verifica a existência de uma letra no alfabeto.
 *
 * - PARÂMETROS: 
 *      -> ALPHABET *alphabet: Estrutura a ser verificada.
 *      -> char letter: Letra a ser procurada.
 *
 * - RETORNO: Posição da letra no alfabeto.
 *   	-> Se <  0 - Não encontrado
 *   	-> Se >= 0 - Encontrado.
 */
int64_t alphabet_verif(ALPHABET *alphabet, char letter);

#endif
