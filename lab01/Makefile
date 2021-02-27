SRCS_DIR= ./srcs
OBJS_DIR= ./objs
HEADERS	= ./headers

ND1_OBJS= debug1.o matrix_nn.o
ND2_OBJS= debug2.o monome.o polynome.o
ND3_OBJS= debug3.o monome.o polynome.o 
NM1_OBJS= main.o matrix_nn.o parser1.o
NM2_OBJS= main.o polynome.o monome.o parser2.o

D1_OBJS	= $(addprefix $(OBJS_DIR)/,$(ND1_OBJS))
D2_OBJS	= $(addprefix $(OBJS_DIR)/,$(ND2_OBJS))
D3_OBJS	= $(addprefix $(OBJS_DIR)/,$(ND3_OBJS))
M1_OBJS	= $(addprefix $(OBJS_DIR)/,$(NM1_OBJS))
M2_OBJS	= $(addprefix $(OBJS_DIR)/,$(NM2_OBJS))

CC		= g++
CFLAGS	= -Wall -Wextra -std=c++2a

M1_NAME	= a1.out
M2_NAME	= a2.out
D1_NAME	= d1.out
D2_NAME	= d2.out
D3_NAME	= d3.out

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.cpp
		$(CC) $(CFLAGS) -I$(HEADERS) -c $< -o $@

dir_obj	: 
		mkdir -p objs

all		: $(M1_NAME) $(M2_NAME)
		
		
debug1	: $(D1_NAME)
		

debug2	: $(D2_NAME)
		

debug3	: $(D3_NAME)
		

$(M1_NAME)	: dir_obj $(M1_OBJS)
		$(CC) $(CFLAGS) $(M1_OBJS) -o $(M1_NAME)

$(M2_NAME)	: dir_obj $(M2_OBJS)
		$(CC) $(CFLAGS) $(M2_OBJS) -o $(M2_NAME)

$(D1_NAME)	: dir_obj $(D1_OBJS)
		$(CC) $(CFLAGS) $(D1_OBJS) -o $(D1_NAME)

$(D2_NAME)	: dir_obj $(D2_OBJS)
		$(CC) $(CFLAGS) $(D2_OBJS) -o $(D2_NAME)

$(D3_NAME)	: dir_obj $(D3_OBJS)
		$(CC) $(CFLAGS) $(D3_OBJS) -o $(D3_NAME)


run1		: $(M1_NAME)
		echo "===================="
		./a1.out test1 && cat test1.tex

run2		: $(M2_NAME)
		echo "===================="
		./a2.out test2 && cat test2.tex

clean	:
		rm -f $(OBJS_DIR)/*

fclean	: clean
		rm -f $(M1_NAME) $(M2_NAME)
		rm -f $(D1_NAME) $(D2_NAME) $(D3_NAME)

re		: fclean all
		
