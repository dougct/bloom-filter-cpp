
bloom: bloom_filter.cpp main.cpp
	clang++ -std=c++20 -Wall -Wextra bloom_filter.cpp main.cpp

test: bloom_filter.cpp bloom_filter_tests.cpp
	clang++ -std=c++20 -Wall -Wextra -lgtest bloom_filter.cpp bloom_filter_tests.cpp

clean:
	rm a.out
