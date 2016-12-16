#include <vector>
#include <memory>
#include <cassert>
#include <stdio.h>
#include <chrono>
#include <string>

#include <iostream>

#include "geometric_helpers.hh"
#include "merge_hull.hh"

#include "algorithm_interfaces/convex_hull_sequential_algorithm.hh"
#include "algorithm_interfaces/convex_hull_parallel_algorithm.hh"
#include "data_structures/convex_hull_representation.hh"
#include "data_structures/vector_convex_hull_representation.hh"

#include "sequential/andrew_algorithm.hh"

#include "simple_parallel/simple_parallel_algorithm.hh"
#include "naive_parallel/naive_parallel_algorithm.hh"
#include "algorithm_interfaces/convex_hull_parallel_tree_algorithm.hh"
#include "hull_tree/hull_tree_algorithm.hh"

using namespace std;
using namespace std::chrono;

// In order to add a new algorithm:
// - create a class subtyping ConveHullAlgorithm providing implementation
// of the new algorithm,
// - include its header file in this file,
// - add an apropriate 'if' statement in the 'load_algorithm' function.

// Loads an appropriate algorithm based on command line params.
ConvexHullAlgorithm* load_algorithm(char* argv[]) {
	ConvexHullAlgorithm* algorithm;
	// TODO(matalek): provide nicer way to create an appropriate algorithm.
	string arg = (string) argv[1];

	int threads;
	string name;
	size_t split_point = arg.find(':');

	if (split_point != string::npos) {
		name = arg.substr(0, split_point);
		threads = stoi(arg.substr(split_point + 1));
	} else {
		name = arg;
	}

	if (name == "Sequential") {
		algorithm = new AndrewAlgorithm();
	} else if (name == "NaiveParallel") {
		assert(threads > 0);
		algorithm = new NaiveParallelAlgorithm(threads);
	} else if (name == "SimpleParallel") {
		assert(threads > 0);
		algorithm = new SimpleParallelAlgorithm(threads);
	} else if (name == "HullTree") {
		assert(threads > 0);
		algorithm = new HullTreeAlgorithm(threads);
	} else {
		assert(false && "No algorithm found with this name");
	}
	return algorithm;
}

int main(int argc, char* argv[]) {
	// Number of points.
	int n;
	scanf("%d", &n);

	// Reading from standard input points.
	vector<POINT> points(n);
	vector<POINT*> points_pointers(n);
	for (int i = 0; i < n; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		points[i] = POINT(x, y);
		points_pointers[i] = &points[i];
	}

	ConvexHullAlgorithm* algorithm;
	algorithm = load_algorithm(argv);

	//computing exec time (could find better way)
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
    shared_ptr<HullWrapper> convex_hull_points = shared_ptr<HullWrapper>(algorithm->convex_hull(points_pointers));
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	printf("TIME: ");
	printf("%ld", duration_cast<microseconds>( t2 - t1 ).count());
    shared_ptr<vector<POINT*>> result = convex_hull_points->get_points();
    printf("\n%lu\n", result->size());
    for (POINT* point : (*result)) {
        point->print();
    }
	delete(algorithm);

	return 0;
}
