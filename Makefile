.PHONY : all buffer bonus clean

BUFFER_SIZE ?= 1

all : clean
	@gcc -Wall -Wextra -Werror main.c get_next_line.c get_next_line_utils.c -o gnl_prog
	valgrind ./gnl_prog
	@echo "\e[0;32mTest effectué sans précision de buffer 🧬\e[0m"

buffer : clean
	@gcc -Wall -Wextra -Werror -DBUFFER_SIZE=$(BUFFER_SIZE) main.c get_next_line.c get_next_line_utils.c -o gnl_prog
	valgrind --leak-check=full --show-leak-kinds=all -s ./gnl_prog
	@echo "\e[0;32mTest effectué avec une taille de buffer de $(BUFFER_SIZE) 🧬\e[0m"

bonus : clean
	@gcc -Wall -Wextra -Werror -DBUFFER_SIZE=$(BUFFER_SIZE) main_bonus.c get_next_line_bonus.c get_next_line_utils_bonus.c -o gnl_bonus_prog
	valgrind --leak-check=full --show-leak-kinds=all -s ./gnl_bonus_prog
	@echo "\e[0;32mTest effectué avec une taille de buffer de $(BUFFER_SIZE) sur plusieurs fichiers 🧬\e[0m"

% :
	@if [ "$(MAKECMDGOALS)" = "bonus" ]; then \
		$(MAKE) bonus BUFFER_SIZE=$@; \
	else \
		$(MAKE) buffer BUFFER_SIZE=$@; \
	fi

clean :
	rm -f gnl_prog gnl_bonus_prog

negative : clean
	@gcc -Wall -Wextra -Werror -DBUFFER_SIZE=-2 main.c get_next_line.c get_next_line_utils.c -o gnl_prog
	@./gnl_prog
	@echo "\e[0;32mTest effectué avec une taille de buffer de -2 🧬\e[0m"

bnegative : clean
	@gcc -Wall -Wextra -Werror -DBUFFER_SIZE=-2 main_bonus.c get_next_line_bonus.c get_next_line_utils_bonus.c -o gnl_bonus_prog
	@./gnl_bonus_prog
	@echo "\e[0;32mTest effectué avec une taille de buffer de -2 🧬\e[0m"