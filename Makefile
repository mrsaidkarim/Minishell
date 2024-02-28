NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
HEADER = headers/minishell.h
RM = rm -rf 

READLINE_L = $(shell brew --prefix readline)/lib
READLINE_I = $(shell brew --prefix readline)/include

SRCS = minishell.c

OBJS = ${SRCS:.c=.o}

all : ${NAME}

%.o : %.c 
	${CC} ${CFLAG} -I ${READLINE_I} -c $< -o $@

${NAME} : ${OBJS}
	${CC} ${CFLAG} ${OBJS} -o ${NAME} -L ${READLINE_L} -lreadline

clean :
	${RM} ${OBJS}

fclean : clean
		${RM} ${NAME}

re : fclean all