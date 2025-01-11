# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: codespace <codespace@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/11 00:00:00 by pouya             #+#    #+#              #
#    Updated: 2025/01/11 00:14:03 by codespace        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME = megaphone

# Compiler and flags
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98

# Source and object files
SRC = megaphone.cpp
OBJ = $(SRC:.cpp=.o)

# Default target
all: $(NAME)

# Build the program
$(NAME): $(OBJ)
	@echo "-> Building the executable: $(NAME)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "-> Build complete: $(NAME) is ready!"



# Compile source files into object files
%.o: %.cpp
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	@echo "Removing object files..."
	@rm -f $(OBJ)

# Clean all generated files
fclean: clean
	@echo "Removing $(NAME)..."
	@rm -f $(NAME)

# Rebuild the program
re: fclean all

# Mark targets as not actual files
.PHONY: all clean fclean re
