NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
HEADER = included/minishell.h
RM = rm -rf 

READLINE_L = $(shell brew --prefix readline)/lib
READLINE_I = $(shell brew --prefix readline)/include

SRCS = minishell.c \
	   libft/ft_strcmp.c \
	   libft/ft_split.c \
	   libft/ft_putstr_fd.c \
	   libft/ft_strtrim.c \
	   libft/ft_strlen.c \
	   libft/ft_strdup.c \
	   libft/ft_substr.c \
	   memory/alocate_error.c \
	   parser/check_syntax.c \
	   parser/check_tokens.c \
	   parser/start_parsing.c \
	   parser/linked_list.c \
	   parser/parsing.c \
	   parser/infix_postfix.c\
	   parser/building_tree.c

OBJS = ${SRCS:.c=.o}

all : ${NAME}

%.o : %.c ${HEADER}
	${CC} ${CFLAG} -I ${READLINE_I} -c $< -o $@

${NAME} : ${OBJS}
	${CC} ${CFLAG} ${OBJS} -o ${NAME} -L ${READLINE_L} -lreadline

clean :
	${RM} ${OBJS}

fclean : clean
		${RM} ${NAME}

re : fclean all