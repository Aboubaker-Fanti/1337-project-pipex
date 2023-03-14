NAME = pipex

NAME1 = pipex_bonus

CC = CC

CFLAGS = -Wall -Wextra -Werror

 SRC =	pipex.c\
		split.c\
		pipex_uti.c\
		pipex_par.c\
		get_next_line/get_next_line.c\
		get_next_line/get_next_line_utils.c\

SRC_BONUS = pipex_bonuss.c\
			pipex_uti_bonus.c\
			split_bonus.c\
			get_next_line/get_next_line.c\
			get_next_line/get_next_line_utils.c\
			pipex_here_bonus.c\

OBJS = $(SRC:.c=.o)

OBJS_BONUS = $(SRC_BONUS:.c=.o)

all : $(NAME)

bonus : $(NAME1)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(NAME1) : $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME1)

clean :
	@rm -rf $(OBJS) $(OBJS_BONUS)

fclean : clean
	@rm -rf $(NAME) $(NAME1)

re : fclean all bonus

