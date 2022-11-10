NAME = s21_grep
HEADER = grep.h

COMPILLER = gcc

FLDR_S  =   srcs/
FLDR_O  =   objs/
FLDR_I  =   includes/

SRCS    =   main.c		parser.c	template_concatenation.c \
			get_templates_from_files.c		output.c

OBJS    =   ${SRCS:.c=.o}

SRCS_WD   =   $(addprefix ${FLDR_S},${SRCS})
OBJS_WD   =   $(addprefix ${FLDR_O},${OBJS})
INCS_WD   =   $(addprefix ${FLDR_I},${HEADER})

# FLAGS     =   -Wall -Wextra -Werror

all: $(FLDR_O) $(NAME)

$(FLDR_O):
		echo $(SRCS_WD)
		mkdir $(FLDR_O)

$(NAME): ${OBJS_WD} $(INCS_WD)
		$(COMPILLER) $(OBJS_WD) -o $(NAME)

$(FLDR_O)%.o : $(FLDR_S)%.c $(INCS_WD)
		$(COMPILLER) ${FLAGS} -I$(FLDR_I) -c $< -o $@

clean:
		rm -rf ${OBJS_WD}

fclean: clean
		rm -rf ${NAME}


re: fclean all