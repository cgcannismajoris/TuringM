/*
 * Nome do Arquivo:  TuringM.h
 *       Descricao:  Módulo principal do simulador.
 *
 * Exported functions from TuringM.c.
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

#ifndef TURINGM_HEADER
#define TURINGM_HEADER

#include "decoder/decoder.h"

#define TURINGM_DECODER_ERROR	-1
#define TURINGM_DECODER_ERROR_MSG	"TURINGM: Falha ao decodificar arquivo de entrada."


int turing_run(char *file);

#endif
