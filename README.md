# Kruskal_Algorithm
 A project focusing on implementation and visualization of Kruskal algorithm

#Implementation and Visualization of Kruskal’s Algorithm

This project showcases the implementation of Kruskal’s Algorithm in both Python and C++ to efficiently find the Minimum Spanning Tree (MST) of a graph. It includes performance analysis and visualization for a comprehensive understanding of the algorithm’s behavior in different programming environments.


#Problem Statement

The goal of this project is to find the Minimum Spanning Tree (MST) for a given graph using Kruskal’s Algorithm. The algorithm ensures an efficient solution with minimal cost and time complexity.

#Real-World Applications

Designing efficient cable or TV networks

Planning optimal tours

Laying water distribution pipelines

#Features of the Implementation

#Python Implementation

Sorting: Leverages an efficient Merge Sort algorithm for sorting edge weights.

Cycle Detection: Utilizes the disjoint set (union-find) data structure to prevent cycles.

Visualization: Employs the graphviz library to generate MST visualizations.

Performance Analysis: Measures memory usage with tracemalloc and execution time using built-in libraries.

Graph Analysis: Visualizes performance data using matplotlib.

#C++ Implementation

Sorting: Implements Merge Sort for edge weight sorting.

Cycle Detection: Incorporates the disjoint set approach for efficient cycle management.

Performance Measurement: Uses chrono for precise time and resource tracking.

#Performance Comparison

Graphs of various sizes were used to evaluate and compare the performance of Python and C++ implementations.

#Key Insights

#Python:

Easier to implement and supports visualization tools.

Slightly slower in execution compared to C++.

#C++:

Superior in terms of speed and resource efficiency.

More complex to implement and lacks native visualization options.

#Visualization

The Python implementation provides graphical representations of the MST for different graph sizes:

10-Node Graph:

Original Graph

Corresponding MST

50-Node Graph:

Original Graph

Corresponding MST

#Prerequisites

#Python

Install the following libraries:

graphviz

matplotlib

tracemalloc

Ensure you have Python 3.8 or higher installed.

#C++

A modern C++ compiler (e.g., GCC or Clang).

Basic knowledge of compiling and running C++ programs.
