################################################################################
######                             PROPERTIES                             ######
################################################################################

CXX			= c++
RM			= rm -rf
CXXFLAGS	= -Wall -Wextra -Werror -MD -MP -std=c++98
MAKEFLAGS	= -j$(nproc) --no-print-directory

NAME		= PMergeMe

SRCSDIR		= srcs

SRCS		= \
			main.cpp \
			PmergeMe.cpp \
			FordJohnsonSorter.cpp \

OBJSDIR		= objs
OBJS		= $(addprefix $(OBJSDIR)/, $(SRCS:.cpp=.o))
DEPS		= $(addprefix $(OBJSDIR)/, $(SRCS:.cpp=.d))

#------------------------------------------------------------------------------#
#------------------------------------RULES-------------------------------------#
#------------------------------------------------------------------------------#

all		: $(NAME)

debug: 
	$(MAKE) CXXFLAGS="$(CXXFLAGS) -g"

$(NAME)	: ${OBJS}
		$(CXX) ${CXXFLAGS} -o $@ $^ 

${OBJSDIR}/%.o	: %.cpp
		@mkdir -p $(dir $@)
		${CXX} ${CXXFLAGS} -c $< -o $@

clean	:
		$(RM) $(OBJSDIR)

fclean	:
		$(RM) $(OBJSDIR) $(NAME)

re		:
		$(RM) $(OBJSDIR) $(NAME)
		$(MAKE) all

-include $(DEPS)

.PHONY	: all clean fclean re
