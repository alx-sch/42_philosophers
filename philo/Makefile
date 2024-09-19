# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/03 14:29:17 by aschenk           #+#    #+#              #
#    Updated: 2024/09/19 17:23:35 by aschenk          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#################
## DEFINITIONS ##
#################

NAME :=			philo

# SOURCE FILES
SRCS_DIR :=		src
SRCS_FILES :=	main.c \
				utils/libft.c \
				utils/check_args.c \
				utils/free.c \
				utils/mutex.c \
				utils/init.c

SRCS :=			$(addprefix $(SRCS_DIR)/, $(SRCS_FILES))

# OBJECT FILES
OBJS_DIR :=		obj
OBJS :=			$(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

# HEADER FILES
HDRS_DIR :=		include
HDRS_FILES := 	philo.h \
				types.h \
				errors.h \

HDRS :=			$(addprefix $(HDRS_DIR)/, $(HDRS_FILES))

# COMPILER
CC :=			cc
CFLAGS := 		-I$(HDRS_DIR)
CFLAGS :=		-Werror -Wextra -Wall -pthread -I$(HDRS_DIR)
CFLAGS +=		-Wpedantic -g
# CFLAGS +=		-fsanitize=address

# Used for progress bar
TOTAL_SRCS :=	$(words $(SRCS))
SRC_NUM :=		0

# ANSI escape codes for colors and styles
RESET =			\033[0m
BOLD =			\033[1m
RED =			\033[31;2m
GREEN =			\033[32m
YELLOW =		\033[33m
L_RED :=		\033[91m

###########
## RULES ##
###########

# Default target
all:		$(NAME)

# Target $(NAME) depends on object files $(OBJS)
$(NAME):	$(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(BOLD)$(YELLOW)\n$(NAME) successfully compiled.$(RESET)"
	@echo -n "$(BOLD)$(GREEN)"
	@echo "$(L_RED)             _____"
	@echo "            /      \\"
	@echo "           (____/\\  )"
	@echo "$(GREEN)            |___  $(L_RED)U$(GREEN)?$(L_RED)($(GREEN)____"
	@echo "            _\\L.   |      \\"
	@echo "           / /\"\"\"\\ /.-'    |"
	@echo "          ( /  _/u     |    \\"
	@echo "           \\|  \\\\       /   /|"
	@echo "            |   \\\\     /   / |"
	@echo "            |    )  _/   /  )"
	@echo "            _\\__/.-'    /__("
	@echo "         _/  __________/    \\"
	@echo "        //  / (             )"
	@echo "       ( \\__|_$(L_RED)_$(GREEN)\\    \\_____ /"
	@echo "        \\    $(L_RED)(___$(GREEN)\\   |$(L_RED)______)"
	@echo "$(GREEN)         \\   |$(L_RED)\\   $(GREEN)\\  \\     $(L_RED)/"
	@echo "$(GREEN)          \\  | $(L_RED)\\__ $(GREEN))  )$(L_RED)___/"
	@echo "$(GREEN)           \\  \\  $(L_RED))$(GREEN)/  /$(L_RED)__("
	@echo "$(GREEN)           |  / $(L_RED)/$(GREEN)/___|   $(L_RED)\\"
	@echo "$(GREEN)         _/  ( $(L_RED)/$(GREEN) OUuuu    $(L_RED)\\"
	@echo "$(GREEN)        \`----'$(L_RED)(____________)"
	@echo -n "$(RESET)"

	@echo "\n$(BOLD)$(YELLOW)Usage: './philo nr_philo t_die t_eat t_sleep (nr_meals)'$(RESET)"
	@echo "$(BOLD)\n- nr_philo (number_of_philosophers):$(RESET) The number of philosophers and also the number of forks."
	@echo "$(BOLD)- t_die (time_to_die) [in ms]:$(RESET) If a philosopher did not start eating in 't_die' since the beginning of their last meal or the beginning of the simulation, they die."
	@echo "$(BOLD)- t_eat (time_to_eat) [in ms]:$(RESET) The time it takes for a philosopher to eat. During that time, they will need to hold two forks."
	@echo "$(BOLD)- t_sleep (time_to_sleep) [in ms]:$(RESET) The time a philosopher will spend sleeping."
	@echo "$(BOLD)- nr_meals (number_of_times_each_philosopher_must_eat) (optional argument):$(RESET) If all philosophers have eaten at least 'nr_meals' times, the simulation stops. If not specified, the simulation stops when a philosopher dies.\n"

# COMPILATION PROGRESS BAR
# Rule to define how to generate object files (%.o) from corresponding
# source files (%.c). Each .o file depends on the associated .c file and the
# project header files.
# Last line:
# -c:		Generates o. files without linking.
# -$<:		Represents the first prerequisite (the c. file).
# -o $@:	Output file name;  '$@' is replaced with target name (the o. file).
$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.c $(HDRS)
	@mkdir -p $(@D)
	@$(eval SRC_NUM := $(shell expr $(SRC_NUM) + 1))
	@$(eval PERCENT := $(shell printf "%.0f" $(shell echo "scale=4; $(SRC_NUM) / $(TOTAL_SRCS) * 100" | bc)))
	@printf "$(BOLD)\rCompiling $(NAME): ["
	@$(eval PROGRESS := $(shell expr $(PERCENT) / 5))
	@printf "$(GREEN)%0.s#$(RESET)$(BOLD)" $(shell seq 1 $(PROGRESS))
	@if [ $(PERCENT) -lt 100 ]; then printf "%0.s-" $(shell seq 1 $(shell expr 20 - $(PROGRESS))); fi
	@printf "] "
	@if [ $(PERCENT) -eq 100 ]; then printf "$(GREEN)"; fi
	@printf "%d/%d - " $(SRC_NUM) $(TOTAL_SRCS)
	@printf "%d%% $(RESET)" $(PERCENT)
	@$(CC) $(CFLAGS) -D BUFFER_SIZE=$(BUFFER_SIZE) -D FD_SIZE=$(FD_SIZE) -c $< -o $@

# Rule to remove all generated object files.
clean:
	@rm -rf $(OBJS_DIR)
	@echo "$(BOLD)$(L_RED)$(NAME) object files removed.$(RESET)"

# Rule to remove all generated object files and the program executable and the command history file.
fclean:	clean
	@rm -f $(NAME)
	@echo "$(BOLD)$(L_RED)$(NAME) removed.$(RESET)"

# Rule to remove all generated object files, the program executable,
# and then rebuild the program.
re:	fclean all

.PHONY: all clean fclean re
