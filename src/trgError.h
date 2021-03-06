/*
 * Nome do Arquivo:  trgError.h
 *       Descricao:  Módulo para auxílio no tratamento de erro.
 *
 * Exported functions from trgError.c.
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

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define TRGERROR_FAILEUREDESCLENGTH     100

/* -> char *trgError_new(uint32_t desc_length)
 * 
 * - DESCRIÇÃO: Instancia uma nova string para armazenamento de erros.
 *
 * - PARÂMETROS: 
 *      -> uint32_t desc_length: Tamanho da string a ser alocada.
 *
 * - RETORNO: String alocada para armazenar o erro.
 *   	-> Se NULL    - Erro na operação.
 *   	-> Se != NULL - Sucesso na operação.
 */
char *   trgError_new(uint32_t desc_length);


/* -> void trgError_free()
 * 
 * - DESCRIÇÃO: Destrói a string.
 *
 * - PARÂMETROS: void.
 *
 * - RETORNO: void.
 */
void     trgError_free();


/* -> void trgError_setDesc(const char *failureDesc)
 * 
 * - DESCRIÇÃO: Seta a mensagem a ser armazenada pela string de erros.
 *
 * - PARÂMETROS: 
 *      -> const char *failureDesc: Mensagem a ser gravada. 
 *
 * - RETORNO: void.
 */
void     trgError_setDesc(const char *failureDesc);


/* -> char *trgError_getDesc()
 * 
 * - DESCRIÇÃO: Retorna o ponteiro para a string de erros.
 *
 * - PARÂMETROS: void. 
 *
 * - RETORNO: Ponteiro para a string.
 */
char *   trgError_getDesc();

