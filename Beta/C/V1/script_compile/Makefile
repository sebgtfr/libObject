##
## Makefile for libobjects in /home/le-mai_s/librairie/C.V.1.0/libobject
## 
## Made by Sébastien Le Maire
## Login   <le-mai_s@epitech.net>
## 
## Started on  Fri Dec 23 11:13:16 2016 Sébastien Le Maire
## Last update Mon Feb  5 12:32:15 2018 Sébastien Le Maire
##

ifndef RELEASE

RELEASE			= ../

endif

ifndef INCLUDE

INCLUDE			= ../include

endif

ifeq ($(DEBUG), on)

CFLAGS			+= -g -g3 -ggdb -ggdb3

endif

PATH_LIB		= $(RELEASE)/

NAME			= $(PATH_LIB)libobjects.a
OBJS			= $(DIR_BOOL)/bool.o

CFLAGS			+= -Wall -Wextra -Werror
CFLAGS			+= -I"$(INCLUDE)"

ifeq ($(MODULE_STRING), on)

PATH_STRING_SRCS	= ${DIR_STRING}/srcs/

SRCS_STRING		= $(PATH_STRING_SRCS)string_ctor.c
SRCS_STRING		+= $(PATH_STRING_SRCS)string_dtor.c
SRCS_STRING		+= $(PATH_STRING_SRCS)string_copy.c
SRCS_STRING		+= $(PATH_STRING_SRCS)string_reset.c
SRCS_STRING		+= $(PATH_STRING_SRCS)string_resize.c
SRCS_STRING		+= $(PATH_STRING_SRCS)string_assign.c
SRCS_STRING		+= $(PATH_STRING_SRCS)string_change.c
SRCS_STRING		+= $(PATH_STRING_SRCS)string_push.c
SRCS_STRING		+= $(PATH_STRING_SRCS)string_concat.c
SRCS_STRING		+= $(PATH_STRING_SRCS)string_print.c
SRCS_STRING		+= $(PATH_STRING_SRCS)string_getline.c
SRCS_STRING		+= $(PATH_STRING_SRCS)string_delline.c
SRCS_STRING		+= $(PATH_STRING_SRCS)string_shift.c
SRCS_STRING		+= $(PATH_STRING_SRCS)string_trim.c
SRCS_STRING		+= $(PATH_STRING_SRCS)string_split.c

OBJS			+= $(SRCS_STRING:.c=.o)

endif

ifeq ($(MODULE_VECTOR), on)

PATH_VECTOR_SRCS	= ${DIR_VECTOR}/srcs/

SRCS_VECTOR		= $(PATH_VECTOR_SRCS)vector_ctor.c
SRCS_VECTOR		+= $(PATH_VECTOR_SRCS)vector_dtor.c
SRCS_VECTOR		+= $(PATH_VECTOR_SRCS)vector_copy.c
SRCS_VECTOR		+= $(PATH_VECTOR_SRCS)vector_push.c
SRCS_VECTOR		+= $(PATH_VECTOR_SRCS)vector_pop.c
SRCS_VECTOR		+= $(PATH_VECTOR_SRCS)vector_clear.c
SRCS_VECTOR		+= $(PATH_VECTOR_SRCS)vector_resize.c
SRCS_VECTOR		+= $(PATH_VECTOR_SRCS)vector_foreach.c
SRCS_VECTOR		+= $(PATH_VECTOR_SRCS)vector_compare.c

OBJS			+= $(SRCS_VECTOR:.c=.o)

endif

ifeq ($(MODULE_LIST), on)

PATH_LIST_SRCS		= ${DIR_LIST}/srcs/

SRCS_LIST		= $(PATH_LIST_SRCS)list_ctor.c
SRCS_LIST		+= $(PATH_LIST_SRCS)list_dtor.c
SRCS_LIST		+= $(PATH_LIST_SRCS)list_copy.c
SRCS_LIST		+= $(PATH_LIST_SRCS)list_push.c
SRCS_LIST		+= $(PATH_LIST_SRCS)list_pop.c
SRCS_LIST		+= $(PATH_LIST_SRCS)list_item.c
SRCS_LIST		+= $(PATH_LIST_SRCS)list_clear.c
SRCS_LIST		+= $(PATH_LIST_SRCS)list_erase.c
SRCS_LIST		+= $(PATH_LIST_SRCS)list_foreach.c
SRCS_LIST		+= $(PATH_LIST_SRCS)list_compare.c
SRCS_LIST		+= $(PATH_LIST_SRCS)list_to_vector.c

OBJS			+= $(SRCS_LIST:.c=.o)

endif

ifeq ($(MODULE_BUFFER), on)

PATH_BUFFER_SRCS	= ${DIR_BUFFER}/srcs/

SRCS_BUFFER		= $(PATH_BUFFER_SRCS)buffer_ctor.c
SRCS_BUFFER		+= $(PATH_BUFFER_SRCS)buffer_dtor.c
SRCS_BUFFER		+= $(PATH_BUFFER_SRCS)buffer_copy.c
SRCS_BUFFER		+= $(PATH_BUFFER_SRCS)buffer_resize.c
SRCS_BUFFER		+= $(PATH_BUFFER_SRCS)buffer_assign.c
SRCS_BUFFER		+= $(PATH_BUFFER_SRCS)buffer_change.c
SRCS_BUFFER		+= $(PATH_BUFFER_SRCS)buffer_concat.c
SRCS_BUFFER		+= $(PATH_BUFFER_SRCS)buffer_print.c
SRCS_BUFFER		+= $(PATH_BUFFER_SRCS)buffer_shift.c

OBJS			+= $(SRCS_BUFFER:.c=.o)

endif

ifeq ($(MODULE_INI), on)

PATH_INI_SRCS		= ${DIR_INI}/srcs/

SRCS_INI		= $(PATH_INI_SRCS)ini_ctor.c
SRCS_INI		+= $(PATH_INI_SRCS)ini_dtor.c
SRCS_INI		+= $(PATH_INI_SRCS)ini_load.c
SRCS_INI		+= $(PATH_INI_SRCS)ini_push_new_section.c
SRCS_INI		+= $(PATH_INI_SRCS)ini_push_new_dataMap.c
SRCS_INI		+= $(PATH_INI_SRCS)ini_push_dataMap.c
SRCS_INI		+= $(PATH_INI_SRCS)ini_get_section.c
SRCS_INI		+= $(PATH_INI_SRCS)ini_get_dataMap.c
SRCS_INI		+= $(PATH_INI_SRCS)ini_save.c

OBJS			+= $(SRCS_INI:.c=.o)

endif

ifeq ($(MODULE_TIMER), on)

PATH_TIMER_SRCS		= ${DIR_TIMER}/srcs/

SRCS_TIMER		= $(PATH_TIMER_SRCS)timer_ctor.c
SRCS_TIMER		+= $(PATH_TIMER_SRCS)timer_setFrequency.c
SRCS_TIMER		+= $(PATH_TIMER_SRCS)timer_checkTicks.c

OBJS			+= $(SRCS_TIMER:.c=.o)

endif

ifeq ($(MODULE_SOCKET), on)

PATH_SOCKET_SRCS	= ${DIR_SOCKET}/srcs/

SRCS_SOCKET		= $(PATH_SOCKET_SRCS)socket_start_end.c
SRCS_SOCKET		+= $(PATH_SOCKET_SRCS)socket_ctor.c
SRCS_SOCKET		+= $(PATH_SOCKET_SRCS)socket_init.c
SRCS_SOCKET		+= $(PATH_SOCKET_SRCS)socket_dtor.c
SRCS_SOCKET		+= $(PATH_SOCKET_SRCS)socket_recv.c
SRCS_SOCKET		+= $(PATH_SOCKET_SRCS)socket_send.c

OBJS			+= $(SRCS_SOCKET:.c=.o)

endif

ifeq ($(MODULE_SERVER), on)

PATH_SERVER_SRCS	= ${DIR_SERVER}/srcs/

SRCS_SERVER		= $(PATH_SERVER_SRCS)server_ctor.c
SRCS_SERVER		+= $(PATH_SERVER_SRCS)server_dtor.c
SRCS_SERVER		+= $(PATH_SERVER_SRCS)server_setEvent.c
SRCS_SERVER		+= $(PATH_SERVER_SRCS)server_connect.c
SRCS_SERVER		+= $(PATH_SERVER_SRCS)server_launch.c
SRCS_SERVER		+= $(PATH_SERVER_SRCS)serverTCP_ctor.c
SRCS_SERVER		+= $(PATH_SERVER_SRCS)serverUDP_ctor.c

ifeq ($(OS_SYSTEM), 'linux')

SRCS_SERVER		+= $(PATH_SERVER_SRCS)serverUNIX_ctor.c

endif

OBJS			+= $(SRCS_SERVER:.c=.o)

endif

ifeq ($(MODULE_CLIENT), on)

PATH_CLIENT_SRCS	= ${DIR_CLIENT}/srcs/

SRCS_CLIENT		= $(PATH_CLIENT_SRCS)client_ctor.c
SRCS_CLIENT		+= $(PATH_CLIENT_SRCS)client_dtor.c
SRCS_CLIENT		+= $(PATH_CLIENT_SRCS)client_setEvent.c
SRCS_CLIENT		+= $(PATH_CLIENT_SRCS)client_connect.c
SRCS_CLIENT		+= $(PATH_CLIENT_SRCS)client_launch.c
SRCS_CLIENT		+= $(PATH_CLIENT_SRCS)clientTCP_ctor.c
SRCS_CLIENT		+= $(PATH_CLIENT_SRCS)clientUDP_ctor.c

ifeq ($(OS_SYSTEM), 'linux')

SRCS_CLIENT		+= $(PATH_CLIENT_SRCS)clientUNIX_ctor.c

endif

OBJS			+= $(SRCS_CLIENT:.c=.o)

endif

ifeq ($(MODULE_NUMBER), on)

PATH_NUMBER_SRCS	= ${DIR_NUMBER}/srcs/

SRCS_NUMBER		= $(PATH_NUMBER_SRCS)number_ctor.c
SRCS_NUMBER		+= $(PATH_NUMBER_SRCS)number_dtor.c
SRCS_NUMBER		+= $(PATH_NUMBER_SRCS)number_copy.c
SRCS_NUMBER		+= $(PATH_NUMBER_SRCS)number_allocation.c
SRCS_NUMBER		+= $(PATH_NUMBER_SRCS)number_equal.c
SRCS_NUMBER		+= $(PATH_NUMBER_SRCS)number_great.c
SRCS_NUMBER		+= $(PATH_NUMBER_SRCS)number_low.c
SRCS_NUMBER		+= $(PATH_NUMBER_SRCS)number_intFunction.c
SRCS_NUMBER		+= $(PATH_NUMBER_SRCS)number_assign.c
SRCS_NUMBER		+= $(PATH_NUMBER_SRCS)number_change.c
SRCS_NUMBER		+= $(PATH_NUMBER_SRCS)number_print.c
SRCS_NUMBER		+= $(PATH_NUMBER_SRCS)number_delUselessZero.c
SRCS_NUMBER		+= $(PATH_NUMBER_SRCS)number_integer.c
SRCS_NUMBER		+= $(PATH_NUMBER_SRCS)number_init_res.c
SRCS_NUMBER		+= $(PATH_NUMBER_SRCS)number_sum.c
SRCS_NUMBER		+= $(PATH_NUMBER_SRCS)number_multiplication.c

OBJS			+= $(SRCS_NUMBER:.c=.o)

endif

ifeq ($(MODULE_THREAD), on)

PATH_THREAD_SRCS		= ${DIR_THREAD}/srcs/

SRCS_THREAD		= $(PATH_THREAD_SRCS)thread.c
SRCS_THREAD		+= $(PATH_THREAD_SRCS)mutex.c

OBJS			+= $(SRCS_THREAD:.c=.o)

endif

CC			= gcc

AR			= ar rc

RAN			= ranlib

RM			= rm -f

###################### DECO #######################

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@
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
