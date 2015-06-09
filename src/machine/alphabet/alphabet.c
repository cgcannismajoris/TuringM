/*
 * Nome do Arquivo:  alphabet.h
 *       Descricao:  Gerenciador dos alfabetos da máquina.
 *
 * Alphabet for TuringM.
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

#include "alphabet.h"

ALPHABET *alphabet_new(char* letters, uint32_t qtdLetters){
	
	ALPHABET *novo;

	if((novo = (ALPHABET*)malloc(sizeof(ALPHABET))) == NULL){
		trgError_setDesc(ALPHABET_ERROR_MSG);
		return (ALPHABET_ERROR);
	}

	if((novo->letters = (char*)malloc(qtdLetters * sizeof(char) + 1)) == NULL){
		free(novo);
		trgError_setDesc(ALPHABET_ERROR_MSG);
		return (ALPHABET_ERROR);
	}

	memcpy(novo->letters, letters, qtdLetters);

	novo->qtd = qtdLetters;
	
	return (novo);
}

void alphabet_free(ALPHABET *alphabet){
	free(alphabet->letters);
	free(alphabet);
}

int64_t alphabet_verif(ALPHABET *alphabet, char letter){
	
	uint32_t i;

	for(i = 0; i < alphabet->qtd; i++){
		if((alphabet->letters)[i] == letter){
			return (i);
		}
	}
	
	return (-1);
}

