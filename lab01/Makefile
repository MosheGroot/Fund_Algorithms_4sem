SRCS_DIR= ./srcs
OBJS_DIR= ./objs
HEADERS	= ./headers

ND_OBJS	= debug.o matrix_nn.o 
NM_OBJS	= main.o matrix_nn.o parser.o

D_OBJS	= $(addprefix $(OBJS_DIR)/,$(ND_OBJS))
M_OBJS	= $(addprefix $(OBJS_DIR)/,$(NM_OBJS))

CC		= g++
CFLAGS	= -Wall -Wextra -std=c++2a

M_NAME	= a.out
D_NAME	= d.out

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.cpp
		$(CC) $(CFLAGS) -I$(HEADERS) -c $< -o $@

dir_obj	: 
		mkdir -p objs

all		: $(M_NAME)
		
		
debug	: $(D_NAME)

$(M_NAME)	: dir_obj $(M_OBJS)
		$(CC) $(CFLAGS) $(M_OBJS) -o $(M_NAME)

$(D_NAME)	: dir_obj $(D_OBJS)
		$(CC) $(CFLAGS) $(D_OBJS) -o $(D_NAME)

run		: $(M_NAME)
		echo "===================="
		./a.out test && cat test.tex

clean	:
		rm -f $(OBJS_DIR)/*

fclean	: clean
		rm -f $(M_NAME) $(D_NAME)

re		: fclean all
		
