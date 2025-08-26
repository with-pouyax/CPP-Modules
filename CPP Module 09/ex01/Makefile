NAME = RPN
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98 -MMD -MP -g
SRCS = main.cpp RPN.cpp
OBJS = $(SRCS:.cpp=.o)

# Debug flags add -DDEBUG to enable debug prints
DFLAGS = -DDEBUG

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

# Build with debug prints enabled; force clean and rebuild without recursive make wrapper
debug: CFLAGS += $(DFLAGS)
debug: re

.PHONY: all clean fclean re debug 