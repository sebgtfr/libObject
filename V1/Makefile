
ifeq ($(DEBUG), yes)

CXXFLAGS						= -g -g3 -ggdb

else

CXXFLAGS						= -O2

endif

PATH_LIBRARY					= ./
PATH_SRCS						= ./srcs/
PATH_OBJECTS_C					= $(PATH_SRCS)C/
PATH_OBJECTS_CPP				= $(PATH_SRCS)C++/

NAME							= $(PATH_LIBRARY)libObjects.so

CXXFLAGS						+= -Wall -Wextra -Werror -fPIC
CXXFLAGS						+= -I./include

## SRCS C
SRCS_C							= $(PATH_OBJECTS_C)Bool.c
SRCS_C							+= $(PATH_OBJECTS_C)Buffer.c
SRCS_C							+= $(PATH_OBJECTS_C)Char.c
SRCS_C							+= $(PATH_OBJECTS_C)String.c

## SRCS CPP
SRCS_CPP						= $(PATH_OBJECTS_CPP)Memory.cpp
SRCS_CPP						+= $(PATH_OBJECTS_CPP)Exception.cpp
SRCS_CPP						+= $(PATH_OBJECTS_CPP)Buffer.cpp
SRCS_CPP						+= $(PATH_OBJECTS_CPP)Char.cpp
SRCS_CPP						+= $(PATH_OBJECTS_CPP)String.cpp

OBJS							= $(SRCS_C:.c=.o) $(SRCS_CPP:.cpp=.o)

CXX								= g++

RM								= rm -f

#################### CUSTOM ####################

.c.o:
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo -e "\t\t\033[01;32m[COMPILE]\033[00m \t=> $<"

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
