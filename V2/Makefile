
ifeq ($(DEBUG), yes)

CXXFLAGS						= -g -g3 -ggdb

else

CXXFLAGS						= -O2

endif

PATH_LIBRARY					= ./
PATH_SRCS						= ./srcs/

NAME							= $(PATH_LIBRARY)libObjects.so

CXXFLAGS						+= -w -Wall -Wextra -Werror -fPIC
CXXFLAGS						+= -I./include

## SRCS CPP
SRCS							= $(PATH_SRCS)Memory.cpp
SRCS							+= $(PATH_SRCS)Exception.cpp
SRCS							+= $(PATH_SRCS)Buffer.cpp
SRCS							+= $(PATH_SRCS)Char.cpp
SRCS							+= $(PATH_SRCS)String.cpp
SRCS							+= $(PATH_SRCS)Number.cpp

OBJS							= $(SRCS:.cpp=.o)

CXX								= g++

RM								= rm -f

#################### CUSTOM ####################

.cpp.o:
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo -e "\t\t\033[01;32m[COMPILE]\033[00m \t=> $<"

################################################

all: $(NAME)

$(NAME): print_compile_lib $(OBJS)
	@echo -e "\033[01;33mCREATE LIBRARY\033[00m"
	@$(CXX) -o $(NAME) -shared $(OBJS)
	@echo -e "\t\t\033[01;33m[LINK]\033[00m \t\t=> $(NAME)"

clean:
	@echo -e "\033[01;31mDELETE OBJECTS\033[00m"
	@$(RM) $(OBJS)

fclean: clean
	@echo -e "\033[01;31mDELETE LIBRARY\033[00m"
	@$(RM) $(NAME)

re: fclean all

print_compile_lib:
	@echo -e "\033[01;32mCOMPILE LIBRARY\033[00m"

.PHONY: all clean fclean print_compile_lib re
