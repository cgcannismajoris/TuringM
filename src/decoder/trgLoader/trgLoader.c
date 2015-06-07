/*
 * Nome do Arquivo:  trgLoader.c
 *       Descricao:  Implementação do TAD TRGLOADER.
 * 
 * TrgLoader for TuringM.
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


#include "trgLoader.h"


TRGLOADER *trgLoader_new(const char *filename)
{
    TRGLOADER *novo;

    if ((novo = (TRGLOADER *)malloc(sizeof(TRGLOADER))) == NULL)
    {
        trgError_setDesc(TRGLOADER_EALLOC_MSG);
        return TRGLOADER_EALLOC; /* stderr => TRGLOADER_EALLOC_MSG */
    }

    if ((novo->last = (char *)malloc(TRGLOADER_MAXCHARLENGTH)) == NULL)
    {
        trgError_setDesc(TRGLOADER_EALLOC_MSG);
        free(novo);
        return TRGLOADER_EALLOC;
    }

    if ((novo->file = fopen(filename, "rb+")) == NULL)
    {
        free(novo);

        trgError_setDesc(TRGLOADER_EFOPEN_MSG);
        return TRGLOADER_EALLOC;
    }

    return novo;
}

void trgLoader_free(TRGLOADER *trgLoader)
{
    fclose(trgLoader->file);
    free(trgLoader);
}

char *trgLoader_getLine(TRGLOADER *trgLoader)
{
    if (feof(trgLoader->file))
        return NULL;

    fscanf(trgLoader->file, "%[^\n]\n", trgLoader->last);

    return trgLoader->last;
}

void trgLoader_rewind(TRGLOADER *trgLoader)
{
    rewind(trgLoader->file);
}
