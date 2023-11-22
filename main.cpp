#include <iostream>
#include <random>
#include <chrono>
#define DEBUG 1
#include "red_black_tree.hpp"

const size_t MAX_N = 10000000; // 10^7
#define HR_CLOCK_NOW() std::chrono::high_resolution_clock::now()

// random int generator
template <typename T>
T random_int(T min, T max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<T> dis(min, max);
    return dis(gen);
}

int main() {
    red_black_tree<int> tree;
    auto subcmp = [](int a, int b) { return a - b; };

    // showcase
    for(int i = 0; i < 12; i++) {
        int randi = random_int(0, 1009);
        tree.add(randi, subcmp);
    }
    std::cout << tree.to_string() << std::endl;
    tree.clear();

    // benchmark
    auto start = HR_CLOCK_NOW();
    for(int i = 0; i < MAX_N; i++) {

        int randi = random_int(-666, 2137);
		tree.add(randi, subcmp);
	}


    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(HR_CLOCK_NOW() - start).count();
    std::cout << "Insertion benchmark\nTime elapsed: "<< duration << "ms\n" 
        << "Avg time: " << (double)duration / MAX_N << "ms\n";

    std::cout << "\nTree height: " << tree.get_height() << std::endl;


    auto find_start = HR_CLOCK_NOW();
    size_t found = 0;
    for(int i = 0; i < MAX_N; i++) {
		int randi = random_int(-666, 2137);
		if(tree.find(randi, subcmp)) found++;
	}

    duration = std::chrono::duration_cast<std::chrono::milliseconds>(HR_CLOCK_NOW() - find_start).count();
    std::cout << "Seek benchmark\nTime elapsed: "<< duration << "ms\n" 
		<< "Found: " << found << " elements\n";

    return 0;
}
