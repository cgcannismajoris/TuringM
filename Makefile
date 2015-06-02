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
#	   compilação do projeto (não compila a ferramenta dicwriter);
#
#	2. make clean : limpa o projeto (não limpa dicwriter);



# DEFINIÇÕES DE ARQUIVOS #####################
# Arquivos de código-fonte
IMAIN_SRC		= src/imain.c
DECODER_SRC		= src/decoder/decoder.c
TOKENS_SRC		= src/decoder/scanner/tokens/tokens.c
SCANNER_SRC		= src/decoder/scanner/scanner.c
LINKEDL_SRC     = src/linkedList/linkedList.c
GNODE_SRC       = src/linkedList/node.c
GDMANIP_SRC     = src/linkedList/genericDataManipulation.c
TRGERROR_SRC	= src/trgError.c
TRGLOADER_SRC	= src/decoder/trgLoader/trgLoader.c
TURINGM_SRC		= src/TuringM.c


# Arquivos-cabeçalho
DECODER_H		= src/decoder/decoder.h
TOKENS_H		= src/decoder/scanner/tokens/tokens.h
SCANNER_H		= src/decoder/scanner/scanner.h
LINKEDL_H       = src/linkedList/linkedList.h
GNODE_H         = src/linkedList/node.h
GDMANIP_H       = src/linkedList/genericDataManipulation.h
TRGERROR_H		= src/trgError.h
TRGLOADER_H		= src/decoder/trgLoader/trgLoader.h
TURINGM_H		= src/TuringM.h


# Arquivos-objeto
IMAIN_OBJ		= obj/imain.o
DECODER_OBJ		= obj/decoder.o
TOKENS_OBJ		= obj/tokens.o
SCANNER_OBJ		= obj/scanner.o
LINKEDL_OBJ     = obj/linkedList.o
GNODE_OBJ       = obj/node.o
GDMANIP_OBJ     = obj/genericDataManipulation.o
TRGERROR_OBJ	= obj/trgError.o
TRGLOADER_OBJ	= obj/trgLoader.o
TURINGM_OBJ		= obj/TuringM.o

# Símbolos de arquivos de saída
OUTPUT_NAME_EXEC		= TuringM
OUTPUT_FULLPATH_EXEC	= bin/$(OUTPUT_NAME_EXEC)

LN_SYMBOL				= $(OUTPUT_NAME_EXEC)



# DEFINIÇÕES PARA COMPILAÇÃO #################
COMPILER 		= gcc
CFLAG 			= -c
LFLAG 			= -o
#LIBFLAG 		=
SRC 			= $(IMAIN_SRC) $(TRGERROR_SRC) $(TOKENS_SRC) \
$(SCANNER_SRC) $(LINKEDL_SRC) $(GNODE_SRC) $(GDMANIP_SRC) \
$(TRGLOADER_SRC) $(TURINGM_SRC)

OBJ				= $(IMAIN_OBJ) $(TRGERROR_OBJ) $(TOKENS_OBJ) \
$(SCANNER_OBJ) $(LINKEDL_OBJ) $(GNODE_OBJ) $(GDMANIP_OBJ) \
$(TRGLOADER_OBJ) $(TURINGM_OBJ)

BIN					= $(OUTPUT_FULLPATH_EXEC)



# REGRAS DE COMPILAÇÃO #######################
all: mk_dir $(BIN)

$(IMAIN_OBJ): $(IMAIN_SRC)
	$(COMPILER) $(CFLAG) $(IMAIN_SRC) $(LFLAG) $(IMAIN_OBJ)

$(TOKENS_OBJ): $(TOKENS_H) $(TOKENS_SRC)
	$(COMPILER) $(CFLAG) $(TOKENS_SRC) $(LFLAG) $(TOKENS_OBJ)

$(SCANNER_OBJ): $(SCANNER_H) $(SCANNER_SRC)
	$(COMPILER) $(CFLAG) $(SCANNER_SRC) $(LFLAG) $(SCANNER_OBJ)

$(GDMANIP_OBJ): $(GDMANIP_H) $(GDMANIP_C)
	$(COMPILER) $(CFLAG) $(GDMANIP_SRC) $(LFLAG) $(GDMANIP_OBJ)

$(GNODE_OBJ): $(GNODE_H) $(GNODE_SRC)
	$(COMPILER) $(CFLAG) $(GNODE_SRC) $(LFLAG) $(GNODE_OBJ)
	
$(LINKEDL_OBJ): $(LINKEDL_H) $(LINKEDL_SRC) $(GNODE_OBJ) $(GDMANIP_OBJ)
	$(COMPILER) $(CFLAG) $(LINKEDL_SRC) $(LFLAG) $(LINKEDL_OBJ)

$(TRGERROR_OBJ): $(TRGERROR_SRC) $(TRGERRROR_H)
	$(COMPILER) $(CFLAG) $(TRGERROR_SRC) $(LFLAG) $(TRGERROR_OBJ)

$(TRGLOADER_OBJ): $(TRGLOADER_SRC) $(TRGLOADER_H)
	$(COMPILER) $(CFLAG) $(TRGLOADER_SRC) $(LFLAG) $(TRGLOADER_OBJ)

$(TURINGM_OBJ): $(TURINGM_SRC) $(TURINGM_H)
	$(COMPILER) $(CFLAG) $(TURINGM_SRC) $(LFLAG) $(TURINGM_OBJ)

$(BIN): $(OBJ)
	$(COMPILER) $(LFLAG) $(BIN) $(OBJ) $(LIBFLAG)

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

