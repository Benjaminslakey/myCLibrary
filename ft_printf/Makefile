
NAME= libftprintf.a

SRCS= fstr_parser \
	  fstr_tokens \
	  get_format \
	  get_var \
	  get_variables \
	  get_handler \
	  printf_lists \
	  unsigned \
	  wide_string \
	  wide_chr \
	  chr \
	  decimal \
	  string \
	  pointer \
	  percent \
	  pf_lib1 \
	  pf_lib2 \
	  pf_lib3 \
	  pf_lib4 \
	  pf_lib5 \
	  pf_lib6 \
	  pf_lib7 \

MAIN= ft_printf.c

CFILES= $(addprefix srcs/, $(addsuffix .c, $(SRCS))) $(MAIN)

OFILES= $(addsuffix .o, $(SRCS)) ft_printf.o

HEADER= -I./ft_printf

FLAGS= -Wall -Wextra -Werror

.PHONY: test all clean fclean re

all: $(NAME)

$(NAME): $(OFILES)
	ar rc $(NAME) $(OFILES)
	ranlib $(NAME)

$(OFILES): $(CFILES)
	gcc $(HEADER) $(FLAGS) $(CFILES) -c

test: $(NAME) clean
	gcc -o printf_test main.c libftprintf.a
	./printf_test

clean:
	rm -rf $(OFILES)

fclean: clean
	rm -rf $(NAME)
	rm -rf printf_test

re: fclean all
