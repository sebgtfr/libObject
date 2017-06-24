##
## Makefile for libobjects in /home/le-mai_s/librairie/C.V.1.0/libobject
## 
## Made by Sébastien Le Maire
## Login   <le-mai_s@epitech.net>
## 
## Started on  Fri Dec 23 11:13:16 2016 Sébastien Le Maire
## Last update Tue Mar  7 22:17:52 2017 Sébastien Le Maire
##

ifndef RELEASE

RELEASE			= .

endif

ifndef INCLUDE

INCLUDE			= ./include

endif

ifeq ($(DEBUG), on)

CXXFLAGS		+= -g -g3 -ggdb

endif

PATH_LIB		= $(RELEASE)/

NAME			= $(PATH_LIB)libobjects.a
OBJS			=

CXXFLAGS		+= -Wall -Wextra -Werror
CXXFLAGS		+= -I"$(INCLUDE)"

#ifeq ($(MODULE_MEMORY), on)

#PATH_MEMORY_SRCS	= ${DIR_MEMORY}/srcs/

#SRCS_MEMORY		= $(PATH_MEMORY_SRCS)Memory.cpp

#OBJS			+= $(SRCS_MEMORY:.cpp=.o)

#endif

CPP			= g++

AR			= ar rc

RAN			= ranlib

RM			= rm -f

###################### DECO #######################

.cpp.o:
	@$(CPP) $(CXXFLAGS) -c $< -o $@
	@echo -e "\t\t\033[01;32m[COMPILE]\033[00m \t=> $<"

##################################################

all: $(NAME)

$(NAME): print_compile_lib $(OBJS)
	@echo -e "\033[01;33mCREATE LIBRARY\033[00m"
	@$(AR) $(NAME) $(OBJS)
	@echo -e "\t\t\033[01;33m[AR]\033[00m \t\t=> $(NAME)"
	@$(RAN) $(NAME)
	@echo -e "\t\t\033[01;33m[RAN]\033[00m \t\t=> $(NAME)"

clean:
	@echo -e "\033[01;31mDELETE OBJECTS\033[00m"
	@$(RM) $(OBJS)
	@echo -e "\t\t\033[01;31m[DELETE]\033[00m \t=> $(OBJS)"

fclean: clean
	@echo -e "\033[01;31mDELETE LIBRARY\033[00m"
	@$(RM) $(NAME)
	@echo -e "\t\t\033[01;31m[DELETE]\033[00m \t=> $(NAME)"

re: fclean all

print_compile_lib:
	@echo -e "\033[01;32mCOMPILE LIBRARY\033[00m"

.PHONY: all clean fclean re print_compile_lib
