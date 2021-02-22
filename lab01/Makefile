SRCS_DIR= ./srcs
OBJS_DIR= ./objs
HEADERS	= ./headers

ND1_OBJS= debug1.o matrix_nn.o
ND2_OBJS= debug2.o monome.o
NM_OBJS	= main.o matrix_nn.o parser.o monome.o

D1_OBJS	= $(addprefix $(OBJS_DIR)/,$(ND1_OBJS))
D2_OBJS	= $(addprefix $(OBJS_DIR)/,$(ND2_OBJS))
M_OBJS	= $(addprefix $(OBJS_DIR)/,$(NM_OBJS))

CC		= g++
CFLAGS	= -Wall -Wextra -std=c++2a

M_NAME	= a.out
D1_NAME	= d1.out
D2_NAME	= d2.out

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.cpp
		$(CC) $(CFLAGS) -I$(HEADERS) -c $< -o $@

dir_obj	: 
		mkdir -p objs

all		: $(M_NAME)
		
		
debug1	: $(D1_NAME)
		

debug2	: $(D2_NAME)
		

$(M_NAME)	: dir_obj $(M_OBJS)
		$(CC) $(CFLAGS) $(M_OBJS) -o $(M_NAME)

$(D1_NAME)	: dir_obj $(D1_OBJS)
		$(CC) $(CFLAGS) $(D1_OBJS) -o $(D1_NAME)

$(D2_NAME)	: dir_obj $(D2_OBJS)
		$(CC) $(CFLAGS) $(D2_OBJS) -o $(D2_NAME)

run		: $(M_NAME)
		echo "===================="
		./a.out test && cat test.tex

clean	:
		rm -f $(OBJS_DIR)/*

fclean	: clean
		rm -f $(M_NAME) $(D1_NAME) $(D2_NAME)

re		: fclean all
		
