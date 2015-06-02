# Makefile
#
# Makefile for TuringM.
# Copyright (C) 2015  Cristian Costa Mello and Gustavo Freitas de Amorim
#
# This is part of TuringM
# TuringM is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# TuringM is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
# ******************************************************************************
#
# ENTRADAS:
#	1. make	all ou make:
#	   compilação do projeto;
#
#	2. make clean : limpa o projeto;



# DEFINIÇÕES DE ARQUIVOS #####################
# Arquivos de código-fonte ###################
## Arquivos principais #######################
IMAIN_SRC		= src/imain.c
TURINGM_SRC		= src/TuringM.c

MAIN_SRCS	 	= $(IMAIN_SRC) $(TURINGM_SRC)

## Decoder ###################################
DECODER_SRC		= src/decoder/decoder.c
TOKENS_SRC		= src/decoder/scanner/tokens/tokens.c
SCANNER_SRC		= src/decoder/scanner/scanner.c
TRGLOADER_SRC	= src/decoder/trgLoader/trgLoader.c

DECODER_SRCS	= $(DECODER_SRC) $(TOKENS_SRC) $(SCANNER_SRC) $(TRGLOADER_SRC)

## Machine ##################################
MACHINE_SRC		= src/machine/machine.c
ALPHABET_SRC	= src/machine/alphabet/alphabet.c
TAPE_SRC		= src/machine/tape/tape.c
TRANSITIONT_SRC	= src/machine/transitionTable/transitionTable.c
STATE_SRC		= src/machine/transitionTable/state/state.c
TRANSITION_SRC	= src/machine/transitionTable/state/transition/transition.c

MACHINE_SRCS	= $(MACHINE_SRC) $(ALPHABET_SRC) $(TAPE_SRC) $(TRANSITIONT_SRC) \
$(STATE_SRC) $(TRANSITION_SRC)

## LinkedList ################################
LINKEDL_SRC     = src/linkedList/linkedList.c
GNODE_SRC       = src/linkedList/node.c
GDMANIP_SRC     = src/linkedList/genericDataManipulation.c

LINKEDLIST_SRCS	= $(LINKEDL_SRC) $(GNODE_SRC) $(GDMANIP_SRC)

## trgError ##################################
TRGERROR_SRC	= src/trgError.c


# Arquivos-cabeçalho #########################
## Cabeçalhos principais ######################
TURINGM_H		= src/TuringM.h

MAIN_H		 	= $(TURINGM_H)

## Decoder ###################################
DECODER_H		= src/decoder/decoder.h
TOKENS_H		= src/decoder/scanner/tokens/tokens.h
SCANNER_H		= src/decoder/scanner/scanner.h
TRGLOADER_H		= src/decoder/trgLoader/trgLoader.h

DECODER_HEADERS	= $(DECODER_H) $(TOKENS_H) $(SCANNER_H) $(TRGLOADER_H)

## Machine ##################################
MACHINE_H		= src/machine/machine.h
ALPHABET_H		= src/machine/alphabet/alphabet.h
TAPE_H			= src/machine/tape/tape.h
TRANSITIONT_H	= src/machine/transitionTable/transitionTable.h
STATE_H			= src/machine/transitionTable/state/state.h
TRANSITION_H	= src/machine/transitionTable/state/transition/transition.h

MACHINE_HEADERS	= $(MACHINE_H) $(ALPHABET_H) $(TAPE_H) $(TRANSITIONT_H) \
$(STATE_H) $(TRANSITION_H)

## LinkedList ################################
LINKEDL_H       = src/linkedList/linkedList.h
GNODE_H         = src/linkedList/node.h
GDMANIP_H       = src/linkedList/genericDataManipulation.h

LINKEDLIST_HEADERS	= $(LINKEDL_H) $(GNODE_H) $(GDMANIP_H)

## trgError ##################################
TRGERROR_H		= src/trgError.h


# Arquivos-objeto ############################
## Objetos principais ########################
IMAIN_OBJ		= obj/imain.o
TURINGM_OBJ		= obj/TuringM.o

MAIN_OBJS	 	= $(IMAIN_OBJ) $(TURINGM_OBJ)

## Decoder ###################################
DECODER_OBJ		= obj/decoder.o
TOKENS_OBJ		= obj/tokens.o
SCANNER_OBJ		= obj/scanner.o
TRGLOADER_OBJ	= obj/trgLoader.o

DECODER_OBJS	= $(DECODER_OBJ) $(TOKENS_OBJ) $(SCANNER_OBJ) $(TRGLOADER_OBJ)

## Machine ##################################
MACHINE_OBJ		= obj/machine.o
ALPHABET_OBJ	= obj/alphabet.o
TAPE_OBJ		= obj/tape.o
TRANSITIONT_OBJ	= obj/transitionTable.o
STATE_OBJ		= obj/state.o
TRANSITION_OBJ	= obj/transition.o

MACHINE_OBJS	= $(MACHINE_OBJ) $(ALPHABET_OBJ) $(TAPE_OBJ) $(TRANSITIONT_OBJ) \
$(STATE_OBJ) $(TRANSITION_OBJ)

## LinkedList ################################
LINKEDL_OBJ     = obj/linkedList.o
GNODE_OBJ       = obj/node.o
GDMANIP_OBJ     = obj/genericDataManipulation.o

LINKEDLIST_OBJS	= $(LINKEDL_OBJ) $(GNODE_OBJ) $(GDMANIP_OBJ)

## trgError ##################################
TRGERROR_OBJ	= obj/trgError.o



# Símbolos de arquivos de saída
OUTPUT_NAME_EXEC		= TuringM
OUTPUT_FULLPATH_EXEC	= bin/$(OUTPUT_NAME_EXEC)

LN_SYMBOL				= $(OUTPUT_NAME_EXEC)



# DEFINIÇÕES PARA COMPILAÇÃO #################
COMPILER 		= gcc
CFLAG 			= -c
LFLAG 			= -o
#LIBFLAG 		=
SRC 			= $(MAIN_SRCS) $(DECODER_SRCS) $(MACHINE_SRCS) $(LINKEDLIST_SRCS) $(TRGERROR_SRCS) $(TRGERROR_SRC)

OBJ				= $(MAIN_OBJS) $(DECODER_OBJS) $(MACHINE_OBJS) $(LINKEDLIST_OBJS) $(TRGERROR_OBJS) $(TRGERROR_OBJ)

BIN				= $(OUTPUT_FULLPATH_EXEC)



# REGRAS DE COMPILAÇÃO #######################
all: mk_dir $(BIN)

$(BIN): $(OBJ)
	$(COMPILER) $(LFLAG) $(BIN) $(OBJ) $(LIBFLAG)

$(IMAIN_OBJ): $(IMAIN_SRC)
	$(COMPILER) $(CFLAG) $(IMAIN_SRC) $(LFLAG) $(IMAIN_OBJ)

$(TURINGM_OBJ): $(TURINGM_SRC) $(TURINGM_H)
	$(COMPILER) $(CFLAG) $(TURINGM_SRC) $(LFLAG) $(TURINGM_OBJ)

## Decoder ###################################
$(DECODER_OBJ): $(DECODER_SRC) $(DECODER_H)
	$(COMPILER) $(CFLAG) $(DECODER_SRC) $(LFLAG) $(DECODER_OBJ)

$(TRGLOADER_OBJ): $(TRGLOADER_SRC) $(TRGLOADER_H)
	$(COMPILER) $(CFLAG) $(TRGLOADER_SRC) $(LFLAG) $(TRGLOADER_OBJ)

$(TOKENS_OBJ): $(TOKENS_H) $(TOKENS_SRC)
	$(COMPILER) $(CFLAG) $(TOKENS_SRC) $(LFLAG) $(TOKENS_OBJ)

$(SCANNER_OBJ): $(SCANNER_H) $(SCANNER_SRC)
	$(COMPILER) $(CFLAG) $(SCANNER_SRC) $(LFLAG) $(SCANNER_OBJ)

## Machine ##################################
$(MACHINE_OBJ): $(MACHINE_H) $(MACHINE_SRC)
	$(COMPILER) $(CFLAG) $(MACHINE_SRC) $(LFLAG) $(MACHINE_OBJ)

$(ALPHABET_OBJ): $(ALPHABET_H) $(ALPHABET_SRC)
	$(COMPILER) $(CFLAG) $(ALPHABET_SRC) $(LFLAG) $(ALPHABET_OBJ)

$(TAPE_OBJ): $(TAPE_H) $(TAPE_SRC)
	$(COMPILER) $(CFLAG) $(TAPE_SRC) $(LFLAG) $(TAPE_OBJ)

$(TRANSITIONT_OBJ): $(TRANSITIONT_H) $(TRANSITIONT_SRC)
	$(COMPILER) $(CFLAG) $(TRANSITIONT_SRC) $(LFLAG) $(TRANSITIONT_OBJ)

$(STATE_OBJ): $(STATE_H) $(STATE_SRC)
	$(COMPILER) $(CFLAG) $(STATE_SRC) $(LFLAG) $(STATE_OBJ)

$(TRANSITION_OBJ): $(TRANSITION_H) $(TRANSITION_SRC)
	$(COMPILER) $(CFLAG) $(TRANSITION_SRC) $(LFLAG) $(TRANSITION_OBJ)

## LinkedList ################################
$(GDMANIP_OBJ): $(GDMANIP_H) $(GDMANIP_C)
	$(COMPILER) $(CFLAG) $(GDMANIP_SRC) $(LFLAG) $(GDMANIP_OBJ)

$(GNODE_OBJ): $(GNODE_H) $(GNODE_SRC)
	$(COMPILER) $(CFLAG) $(GNODE_SRC) $(LFLAG) $(GNODE_OBJ)
	
$(LINKEDL_OBJ): $(LINKEDL_H) $(LINKEDL_SRC) $(GNODE_OBJ) $(GDMANIP_OBJ)
	$(COMPILER) $(CFLAG) $(LINKEDL_SRC) $(LFLAG) $(LINKEDL_OBJ)

## trgError ##################################
$(TRGERROR_OBJ): $(TRGERROR_SRC) $(TRGERRROR_H)
	$(COMPILER) $(CFLAG) $(TRGERROR_SRC) $(LFLAG) $(TRGERROR_OBJ)


# GERAÇÃO DO LINK SIMBÓLICO #################
LN_SYMBOL:
	rm -f $(OUTPUT_NAME_EXEC)
	ln -s $(OUTPUT_FULLPATH_EXEC)

# CRIAÇÃO DE PASTAS #########################
mk_dir:
	mkdir -p bin data obj

# LIMPEZA DA PASTA ##########################
clean:
	rm -f $(OUTPUT_FULLPATH_EXEC) $(LN_SYMBOL) *~ *.swp *.swo \
	$(OBJ)

