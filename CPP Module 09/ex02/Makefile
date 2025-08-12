################################################################################
######                             PROPERTIES                             ######
################################################################################

CXX      = c++
RM       = rm -rf

# Mandatory flags per project rules
# Add optional defines via DEFINES from special targets (count/debug)
CXXFLAGS = -Wall -Wextra -Werror -MD -MP -std=c++98 $(DEFINES)

NAME     = PmergeMe

SRCS = \
  main.cpp \
  PmergeMe.cpp \
  FordJohnsonVectorSorter.cpp \
  FordJohnsonDequeSorter.cpp

OBJDIR = objs
OBJS   = $(addprefix $(OBJDIR)/,$(SRCS:.cpp=.o))
DEPS   = $(OBJS:.o=.d)

################################################################################
######                               RULES                                ######
################################################################################

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJDIR)

fclean:
	$(RM) $(OBJDIR) $(NAME)

re: fclean all

# Convenience targets
count: DEFINES += -DPMERGEME_SHOW_COMPARISONS
count: re

debug: DEFINES += -g -DPMERGEME_DEBUG -DPMERGEME_SHOW_COMPARISONS
debug: re

-include $(DEPS)

.PHONY: all clean fclean re count debug
