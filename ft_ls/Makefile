# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amovchan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/09 19:36:54 by amovchan          #+#    #+#              #
#    Updated: 2017/10/09 19:37:11 by amovchan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ----- Colors -----
BLACK ="\033[1;30m"
RED ="\033[1;31m"
GREEN ="\033[1;32m"
YELLOW = "\x1b[33m"
BLUE = "\x1b[34m"
MAGENTA = "\x1b[35m"
CYAN ="\033[1;35m"
PURPLE ="\033[1;36m"
WHITE ="\033[1;37m"
EOC ="\033[0;0m"
RESET = "\x1b[0m"
# ==================

LIBRARY = ./libft/libft.a

NAME = ft_ls
HEAD = ft_ls.h

FLAGS = -Wall -Wextra -Werror

#------ path -------
FILES_PATH		= ./
OBJECTS_PATH	= ./objects


#------ files ------
FILES_FILES		= ft_access ft_is_file ft_ls ft_print_colum ft_read_dir ft_sort_alhpa name_color\
				print_ls sort_time sourc main sort_time_nano

#------ other ------
FILES_OBJ 		= $(addprefix $(OBJECTS_PATH)/, $(addsuffix .o, $(FILES_FILES)))

#------ make ------
all: $(NAME)

$(NAME): $(FILES_OBJ)
	@echo "\n"
	@make -C ./libft/
	@echo $(CYAN) "\tCompiling $@"$(RESET)
	@gcc $(FLAGS) -o $@ $^ $(LIBRARY)
	@echo $(GREEN) "\tft_ls\t\t- has been made\n"$(RESET)

$(OBJECTS_PATH)/%.o: $(FILES_PATH)/%.c
	@echo $(PURPLE) "\tCompiling $<"$(RESET)
	@mkdir $(OBJECTS_PATH) 2> /dev/null || true
	@gcc $(FLAGS) -o $@ -c $<

#------ make clean ------
cleanlib:
	@make clean -C ./libft

clean: cleanlib
	@echo $(YELLOW)"\t\t\t\tFT_LS"$(RESET)
	@rm -f $(FILES_OBJ)
	@echo $(RED) "\t.o files have been cleaned.\n"$(RESET)
	@rm -rf $(OBJECTS_PATH)
	@echo $(RED) "\t./objects path have been cleaned."$(RESET)

#------ make fclean ------
fcleanlib:
	@make fclean -C ./libft

fclean: fcleanlib
	@echo $(YELLOW)"\t\t\t\tFT_LS"$(RESET)
	@rm -f $(FILES_OBJ)
	@echo $(RED) "\t.o files have been cleaned.\n"$(RESET)
	@rm -rf $(OBJECTS_PATH)
	@echo $(RED) "\t./objects path have been cleaned."$(RESET)
	@rm -f $(NAME)
	@echo $(RED) "\tft_ls have been cleaned.\n"$(RESET)

#------ make re ------
re: fclean all
