SRCS	= matrix_nn.cpp
HEADERS	= .

CC		= g++
CFLAGS	= -Wall -Wextra -std=c++20

NAME	= a.out

all		: $(NAME)

$(NAME)	:
		$(CC) $(CFLAGS) $(SRCS) main.cpp -o $(NAME)

clean	:
		rm -f $(NAME)

re		: clean all
		
debug	:
		$(CC) $(CFLAGS) $(SRCS) debug.cpp -o $(NAME)
