# Program name
NAME = phonebook

# Compiler and flags
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98

# Source and object files
SRC = main.cpp Contact.cpp PhoneBook.cpp
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