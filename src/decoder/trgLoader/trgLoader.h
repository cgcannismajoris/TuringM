/*
 * Nome do Arquivo:  trgLoader.h
 *       Descricao:  TAD para leitura do arquivo contendo a máquina.
 *
 * Exported functions from trgLoader.c.
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


#ifndef TRGLOADER_HEADER
#define TRGLOADER_HEADER

#include <stdio.h>  /* para I/O */
#include <stdlib.h>
#include <string.h>

#include "../../trgError.h"

#define TRGLOADER_EALLOC        NULL    /* FALHA DE ALOCAÇÃO */
#define TRGLOADER_EGETINST      NULL    /* Falha ao se obter nova instrução */

#define TRGLOADER_EALLOC_MSG    "Falha na alocação da estrutura TRGLOADER."
#define TRGLOADER_EGETINST_MSG  "Falha ao se obter nova linha."

#define TRGLOADER_EFOPEN_MSG    "Falha na abertura do arquivo de código-fonte."

#define TRGLOADER_MAXCHARLENGTH   256 /* Quantidade máxima de caracteres da instrução */


typedef struct _trgLoader
{
    FILE *          file;       // Ponteiro para o arquivo a ser lido.
	char *			last;		// Última linha carregada
} TRGLOADER;


/* -> TRGLOADER *trgLoader_new(const char *filename)
 * 
 * - DESCRIÇÃO: Instancia um novo loader do decodificador que será utilizado na leitura
 *   do arquivo.
 *
 * - PARÂMETROS: 
 *      -> const char *filename: Nome do arquivo a ser utilizado.
 *
 * - RETORNO: Estrutura do tipo TRGLOADER instanciada.
 *   	-> Se NULL    - Erro na operação.
 *   	-> Se != NULL - Sucesso na operação.
 */
TRGLOADER *     trgLoader_new(const char *filename);


/* -> void trgLoader_free(TRGLOADER *trgLoader)
 * 
 * - DESCRIÇÃO: Destrói uma estrutura existente em memória.
 *
 * - PARÂMETROS: 
 *      -> TRGLOADER *trgLoader: Estrutura a ser destruída.
 *
 * - RETORNO: void.
 */
void            trgLoader_free(TRGLOADER *trgLoader);


/* -> void trgLoader_getLine(TRGLOADER *trgLoader)
 * 
 * - DESCRIÇÃO: Carrega a próxima linha escrita do arquivo.
 *   	- Se nenhuma linha foi lida até o momento, carrega a primeira.
 *   	- Se já leu alguma, carrega a linha subsequênte à anteriormente carregada.
 *
 * - PARÂMETROS: 
 *      -> TRGLOADER *trgLoader: Estrutura a ser utilizada para a leitura do
 *      arquivo.
 *
 * - RETORNO: Linha carregada.
 *   	-> Se NULL    - Erro na operação.
 *   	-> Se != NULL - Sucesso na operação.
 */
char *         trgLoader_getLine(TRGLOADER *trgLoader);


/* -> void trgLoader_rewind(TRGLOADER *trgLoader)
 * 
 * - DESCRIÇÃO: Retorna para o início do arquivo.
 *
 * - PARÂMETROS: 
 *      -> TRGLOADER *trgLoader: Estrutura a ser utilizada ma operação. 
 *
 * - RETORNO: void.
 */
void            trgLoader_rewind(TRGLOADER *trgLoader);

#endif /* TRGLOADER_HEADER */
