py:
	python chaos_game.py
cpp:
	clang++ -std=c++20 chaos_game.cpp -o chaos
	./chaos
	rm chaos
	python plot_cpp_out.py