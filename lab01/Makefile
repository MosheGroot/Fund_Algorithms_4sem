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

all		: $(M_NAME)
		
		
debug	: $(D_NAME)
		

$(M_NAME)	: $(M_OBJS)
		$(CC) $(CFLAGS) $(M_OBJS) -o $(M_NAME)

$(D_NAME)	: $(D_OBJS)
		$(CC) $(CFLAGS) $(D_OBJS) -o $(D_NAME)

clean	:
		rm -f $(OBJS_DIR)/*

fclean	: clean
		rm -f $(M_NAME) $(D_NAME)

re		: fclean all
		
