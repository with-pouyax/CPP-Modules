NAME = bureaucrat
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98
DEPFLAGS = -MMD -MP

# -MMD tells the compiler to generate a .d file (dependency file) for each .cpp file.
# This .d file lists all the header files (.hpp) that the .cpp file depends on.

# -MP tells the compiler to add phony targets for each header file in the .d file.
# This prevents make from crashing if a header file is deleted.


SRCS = main.cpp Bureaucrat.cpp
OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

# here after compiling the .o files, we include the .d files
# this tells make to include the dependency files in the build process
#  that means if a .cpp file is modified, the compiler will recompile the .o file
# also if a .hpp file is modified, the compiler will recompile the .o file that depends on it

-include $(DEPS)

clean:
	rm -f $(OBJS) $(DEPS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 