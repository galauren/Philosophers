#-------------  Variables  ---------------#

NAME	=	philo

CC		=	cc

CFLAGS  =	-Wall -Wextra -Werror -pthread -I$(HEADER_P) -MMD

DEBUG	=	-g3 -fsanitize=thread

HEADER_P = 	./includes
HEADER_N =	philosophers.h
HEADER   =	$(addprefix $(HEADER_P)/,$(HEADER_N))

SRC_PATH =	./srcs
SRC_TMP :=	actions.c \
			exceptions.c \
			ft_strtod.c \
			list_functions.c \
			main.c \
			threads.c \
			time.c


CHECKER_NAME	=	Checker
TMP				=	checker.c
CHECKER_SRC		=	$(SRC_TMP) $(TMP)
CHECKER_OBJS	=	$(CHECKER_SRC:%.c=$(OBJ_PATH)/%.o)

SRC_NAME	=	$(SRC_TMP)
SRC			=	$(addprefix $(SRC_PATH)/,$(SRC_NAME))

DEP  = $(OBJ:%.o=%.d)

OBJ_PATH =	./.objs
OBJ_NAME =	$(SRC_NAME:.c=.o)
OBJ      =	$(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

#----------------  Rules  ----------------#

all		:	$(NAME)

$(NAME)	:	$(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $@
	@echo "COMPILED 🥣"

-include $(DEP)

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -MMD -o $@ -c $<
	@printf "\e[1;30mTrying to compile : \e[1;37m./%-51s\e[1;0m" "$<"
	@printf "\e[32mcheck\e[1;0m\n"

d	:	debug

debug :	$(OBJ)
	@$(CC) $(CFLAGS) $(DEBUG) $(OBJ) -o debug
	@echo "\e[3;35mDEBUGGING\e[0m with '\e[32mdebug\e[0m' file"

save : fclean
	git add .
	git commit -m "$m"
	git push

f : fclean

clean :
	@rm -rf $(OBJ_PATH)

fclean : clean
	@rm -rf $(NAME)
	@rm -rf debug
	@rm -rf $(CHECKER_NAME)

re : fclean all
