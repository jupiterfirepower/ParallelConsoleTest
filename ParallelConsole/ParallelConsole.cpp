// ParallelConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream> 
#include <thread> 
#include <string> 
#include <array>
#include <sstream>
#include <fstream>
#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"
#include "omp.h"
#include <ppl.h>
#include <chrono>

using namespace tbb;
using namespace std;
using namespace chrono;
using namespace concurrency;
//using namespace std::execution;
//using namespace pstl::execution;

static const size_t N = 23;

int main()
{
	//std::cout
	//	<< std::this_thread::get_id() << ": " << i
	//	<< std::endl;

	const auto start_tbb = high_resolution_clock::now();
	tbb::parallel_for(1, 1000,
		[](int i) {
		;
	});
	const auto stop_tbb = high_resolution_clock::now();
	const auto duration_tbb = duration_cast<microseconds>(stop_tbb - start_tbb);
	std::cout << std::endl << "Time taken by function load and parse TBB: " << duration_tbb.count() << " microseconds" << std::endl << std::endl;

	tbb::parallel_for(blocked_range<int>(0, 10), [](const blocked_range<int>& range) {
		for (int i = range.begin(); i != range.end(); ++i)
			std::cout << "Range : " << i << std::endl;
	});

	const auto start_ppl = high_resolution_clock::now();
	concurrency::parallel_for(1, 1000,
		[](int i) {
		;
	});
	const auto stop_ppl = high_resolution_clock::now();
	const auto duration_ppl = duration_cast<microseconds>(stop_ppl - start_ppl);
	std::cout << std::endl << "Time taken by function load and parse PPL: " << duration_ppl.count() << " microseconds" << std::endl << std::endl;

	concurrency::parallel_for(1, 6, [](int value) {
		wstringstream ss;
		ss << value << L' ';
		wcout << ss.str();
	});

	// Get starting timepoint
	const auto start_single = high_resolution_clock::now();
	for (int i = 1; i < 1000; ++i) {
		;
	}
	const auto stop_single = high_resolution_clock::now();
	const auto duration_single = duration_cast<microseconds>(stop_single - start_single);
	std::cout << std::endl << "Time taken by function load and parse Serial: " << duration_single.count() << " microseconds" << std::endl << std::endl;

	const auto start = high_resolution_clock::now();
    #pragma omp parallel for
	for (int i = 1; i < 1000; ++i) {
		;
	}
	const auto stop = high_resolution_clock::now();
	const auto duration = duration_cast<microseconds>(stop - start);
	std::cout << std::endl << "Time taken by function load and parse OpenMP: " << duration.count() << " microseconds" << std::endl << std::endl;

	std::cin.get();
    return 0;
}

