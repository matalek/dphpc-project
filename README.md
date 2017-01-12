# Parallel convex hull

## Algorithms Comparator script

The comparator script is used to execute different algorithms for different inputs and evaluate the results in terms of time and correctness.
The resulting csv files are stored in the log_files folder.
Use -w for a linear gorwth in number of points, -m for exponential:
(example -c 5 -s 100 -m 10 -> 100, 1000, 10000, 100000, 1000000;
-c 5 -s 100 -w 10 -> 100, 110, 120, 130, 140)

Execute from prompt command:
```sh
$ chmod u+x scripts/algorithm_comparator.py
```
and then
```sh
$ ./scripts/algorithm_comparator.py
# -c <number of different combinations of number of points>
# -w <width of steps>   OR   -m <exponential base>
# -s <starting number of points>
# -r <range of points coordinates>
# -R <number of repetition for each number of points>
# -S <shape (circle, square or disk)>
# -a <algorithms to compare in the format <algo1:num_of_threads algo2:num_of_threads algo3:num_of_threads ...>>
```
For example:
```sh
./scripts/algorithm_comparator.py -c 10 -w 10000 -s 10000 -r 10000000 -R 2 -S disk -a SimpleParallel:4 SimpleParallel:8 Sequential:1 ...
```
REMEMBER to also provide a sequential version when needed, with 1 as num_of_threads

## Plotter script

This script prints the results of the given algorithms in term of execution time and speedup.

Execute from prompt command:
```sh
$ chmod u+x scripts/plotter_script.py
```
and then

```sh
$ ./scripts/plotter.py
# -a <algorithms to compare in the format <algo1:num_of_threads algo2:num_of_threads algo3:num_of_threads ...>>
```

## Algorithm results Printer script

Useful debugging tool.
It prints the convex hull generated by a given algorithm and cgal result, with the points stored in tmp.log.

Execute from prompt command:
```sh
$ chmod u+x scripts/alg_result_printer.py
```
and then

```sh
$ ./alg_result_printer.py
# <algorithm:num_of_threads>
```
For example:
```sh
./scripts/alg_result_printer.py SimpleParallel:4
```

## Generated points Printer script

Useful debugging tool.
It prints all the points in tmp.log.

Execute from prompt command:
```sh
$ chmod u+x scripts/original_generated_points_printer.py
```
and then

```sh
$ ./scripts/original_generated_points_printer.py
```

## Building tester program

Execute from prompt command:
```sh
$ make
```

## Running tester program

Execute from prompt command:
```sh
$ ./tester algorithm_name[:threads_count]
```
where:
- `algorithm_name` is the name of the algorithm. Available algorithms are listed in the
table below.
- `threads_count` (optional) is the number of threads in case of parallel version.

### Available algorithms
| Algorithm name | Type | Implementation |
|---|---|---|
| Sequential | Sequential | [AndrewAlgorithm](sequential/andrew_algorithm.hh) |
| SequentialGraham | Sequential | [GrahamAlgorithm](sequential/graham_algorithm.hh) |
| SimpleParallel | Parallel | [SimpleParallelAlgorithm](simple_parallel/simple_parallel_algorithm.hh) |

## CGAL implementation
In order to compile CGAL version of the algorithm in `cgal` directory execute:
```sh
$ cmake .
$ make
```
It should produce executable file `cgal_graham_andrew`.

CGAL algorithm implementation takes only points as an input (without number of points) and as an output it writes only points (without number of points).
