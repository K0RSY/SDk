compile_file = main.cpp
run_file = main

all: $(run_file)

clean:
	@rm $(run_file)

main: $(compile_file)
	@g++ $(compile_file) -o $(run_file) -llua5.3 -ldl

run:
	@make
	@echo "\n------------------run------------------"
	@./$(run_file)
	@echo "---------------------------------------\n"
	@make clean
