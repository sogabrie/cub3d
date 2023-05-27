#	Main Variables
NAME = miniRT
FLAGS = -Wall -Wextra -Werror
CC = cc
RM = rm -rf
HEADERS = includes
LIBS = -I./includes/
INCLUDE = -I /usr/local/include

#	42
MLX = -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit
#	Home
# MLX = -L. -lmlx -framework OpenGL -framework AppKit

#	Libft
LIBFT_DIR = ./libft
LIBFT_PATH = -L./libft -lft
LIBFT_SRC := ${shell find ${LIBFT_DIR} -name '*.c' -type f}

#	Compiled directories
SRC = src
OBJ = obj
SUBDIRS = main

#	Folder directions
SRC_DIR = ${foreach dir, ${SUBDIRS}, ${addprefix ${SRC}/, ${dir}}}
OBJ_DIR = ${foreach dir, ${SUBDIRS}, ${addprefix ${OBJ}/, ${dir}}}

#	File directions
SRCS = ${foreach dir, ${SRC_DIR}, ${wildcard $(dir)/*.c}}
OBJS = ${subst ${SRC}, ${OBJ}, ${SRCS:.c=.o}}
HEADER_DIR = ${shell find ./includes -name '*.h' -type f}

all : ${NAME}
bonus : all

${NAME} : Makefile ${OBJS} ${HEADERS_DIR} ${LIBFT_SRC}
	@${MAKE} -C ${LIBFT_DIR} all
	@${CC} ${FLAGS} ${INCLUDE} ${LIBFT_PATH} ${OBJS} ${MLX} -o ${NAME}
	@make DONE_MSG

${OBJ}/%.o : ${SRC}/%.c ${HEADER_DIR}
	@mkdir -p ${OBJ} ${OBJ_DIR}
	@${MAKE} CREATE_OBJECT_FILES
	@${CC} ${CFLAGS} ${LIBS} -c $< -o $@

clean : DELETE_OBJ_MSG
	@${MAKE} -C ${LIBFT_DIR} clean
	@${RM} ${OBJ}

fclean : clean DELETE_PROGRAM_MSG
	@${MAKE} -C ${LIBFT_DIR} fclean
	@${RM} ${NAME}

re : fclean all

.PHONY : all bonus clean fclean re

#	Colors
RESET = \033[0m
RED   = \033[31m
BLUE  = \033[34m
GREEN = \033[32m

#	Helper messages
DONE_MSG:
	@echo "${GREEN}! ${NAME} is ready !${RESET}"
DELETE_OBJ_MSG:
	@echo "${RED}Object Files Deleting..${RESET}"
CREATE_OBJECT_FILES :
	@echo "${BLUE}Create Obj Files..${RESET}"
DELETE_PROGRAM_MSG:
	@echo "${RED}${NAME} is deleting..${RESET}"