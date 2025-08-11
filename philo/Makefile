CC = cc 

SANITIZE = -fsanitize=address
CFLAGS = -Wall -Wextra -Werror -pthread #$(SANITIZE) -g
RM = rm -f

PARSE = philo.c parsing.c libft.c routine.c monitor.c destroy.c

OB = $(PARSE:.c=.o)


NOM = philo

all: $(NOM) 


$(NOM): $(OB)
	$(CC) $(CFLAGS) $(OB) -o $(NOM)

$(OB): philo.h

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM)  $(OB) *.d

fclean: clean
	$(RM) $(NOM)

re: fclean all
