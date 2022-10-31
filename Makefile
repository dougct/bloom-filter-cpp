
bloom: bloom_filter.h bloom_filter.cpp main.cpp
	clang++ -std=c++17 -Wall -Wextra bloom_filter.h bloom_filter.cpp main.cpp

clean:
	rm bloom
