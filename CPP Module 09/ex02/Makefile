################################################################################
######                             PROPERTIES                             ######
################################################################################

CXX			= c++
RM			= rm -rf
CXXFLAGS	= -Wall -Wextra -Werror -MD -MP -std=c++98
MAKEFLAGS	= -j$(nproc) --no-print-directory

NAME		= PmergeMe

SRCSDIR		= srcs

SRCS		= \
			main.cpp \
			PmergeMe.cpp \
			FordJohnsonVectorSorter.cpp \
			FordJohnsonDequeSorter.cpp \

OBJSDIR		= objs
OBJS		= $(addprefix $(OBJSDIR)/, $(SRCS:.cpp=.o))
DEPS		= $(addprefix $(OBJSDIR)/, $(SRCS:.cpp=.d))

#------------------------------------------------------------------------------#
#------------------------------------RULES-------------------------------------#
#------------------------------------------------------------------------------#

all		: $(NAME)

debug: CXXFLAGS += -g -DPMERGEME_DEBUG -DPMERGEME_SHOW_COMPARISONS
debug: re

count: CXXFLAGS += -DPMERGEME_SHOW_COMPARISONS
count: re

$(NAME)	: ${OBJS}
		$(CXX) ${CXXFLAGS} -o $@ $^ 

${OBJSDIR}/%.o	: %.cpp
		@mkdir -p $(OBJSDIR)
		${CXX} ${CXXFLAGS} -c $< -o $@


clean	:
		$(RM) $(OBJSDIR)

fclean	:
		$(RM) $(OBJSDIR) $(NAME)

re		: fclean all

-include $(DEPS)

.PHONY	: all clean fclean re
