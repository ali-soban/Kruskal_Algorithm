#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <cmath>
#include <set>
#include <tuple>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
using namespace std;
using namespace chrono;
 // to show wieghted edge
struct Edge {
    int u, v, weight;
};

// Generate random graph 
pair<vector<Edge>, int> generate_random_graph(int num_nodes, int num_edges) {
    vector<Edge> edges;
    set<pair<int, int>> edge_set;
    random_device rd;
    mt19937 gen(rd());
    // range of nodes
    uniform_int_distribution<> dist_node(0, num_nodes - 1);
    // range of weights
    uniform_int_distribution<> dist_weight(1, 100);

    // Eeach node has at least one edge
    for (int node = 0; node < num_nodes; ++node) {
        int other_node;
        do {
            other_node = dist_node(gen);
        } while (other_node == node || edge_set.count({ node, other_node }));

        int weight = dist_weight(gen);
        edges.push_back({ node, other_node, weight });
        edge_set.insert({ node, other_node });
        edge_set.insert({ other_node, node });
    }

    // Add remaining randomly
    int remaining_edges = num_edges - num_nodes;
    for (int i = 0; i < remaining_edges; ++i) {
        int u, v;
        do {
            u = dist_node(gen);
            v = dist_node(gen);
        } while (u == v || edge_set.count({ u, v }));

        int weight = dist_weight(gen);
        edges.push_back({ u, v, weight });
        edge_set.insert({ u, v });
        edge_set.insert({ v, u });
    }

    return { edges, num_nodes };
}

// Merge sort
void merge(vector<Edge>& arr, vector<Edge>& left_half, vector<Edge>& right_half) {
    size_t i = 0, j = 0, k = 0;
    while (i < left_half.size() && j < right_half.size()) {
        if (left_half[i].weight < right_half[j].weight) {
            arr[k++] = left_half[i++];
        }
        else {
            arr[k++] = right_half[j++];
        }
    }
    while (i < left_half.size()) {
        arr[k++] = left_half[i++];
    }
    while (j < right_half.size()) {
        arr[k++] = right_half[j++];
    }
}

void merge_sort(vector<Edge>& edges) {
    if (edges.size() > 1) {
        size_t mid = edges.size() / 2;
        vector<Edge> left_half(edges.begin(), edges.begin() + mid);
        vector<Edge> right_half(edges.begin() + mid, edges.end());

        merge_sort(left_half);
        merge_sort(right_half);
        merge(edges, left_half, right_half);
    }
}

// Disjoint Set Union
class DSU {
    vector<int> parent, rank;

public:
    DSU(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void union_sets(int x, int y) {
        int root_x = find(x);
        int root_y = find(y);
        if (root_x != root_y) {
            if (rank[root_x] > rank[root_y]) {
                parent[root_y] = root_x;
            }
            else if (rank[root_x] < rank[root_y]) {
                parent[root_x] = root_y;
            }
            else {
                parent[root_y] = root_x;
                rank[root_x]++;
            }
        }
    }
};

// Kruskal's Algorithm
pair<vector<Edge>, int> kruskal(vector<Edge>& edges, int num_nodes) {
    merge_sort(edges);
    DSU dsu(num_nodes);
    vector<Edge> mst;
    int total_weight = 0;

    for (const auto& edge : edges) {
        if (dsu.find(edge.u) != dsu.find(edge.v)) {
            dsu.union_sets(edge.u, edge.v);
            mst.push_back(edge);
            total_weight += edge.weight;
        }
    }

    return { mst, total_weight };
}

void analyze_performance(const vector<pair<vector<Edge>, int>>& graphs) {
    vector<int> node_sizes;
    vector<int> edge_sizes;
    vector<double> times;
    vector<size_t> memory_usages;

    for (const auto& graph : graphs) {
        auto& edges = graph.first;
        int num_nodes = graph.second;
        int num_edges = static_cast<int>(edges.size());
       
        node_sizes.push_back(num_nodes);
        edge_sizes.push_back(num_edges);

        // Measure execution time
        auto start_time = high_resolution_clock::now();

        // Run Kruskal's algorithm
        auto edges_copy = graph.first;
        auto mst_result = kruskal(edges_copy, num_nodes);

        auto elapsed_time = duration<double>(high_resolution_clock::now() - start_time).count();

        // Estimate memory and time usage
        size_t memory_usage = sizeof(edges) + edges.capacity() * sizeof(Edge);
        size_t mst_memory_usage = sizeof(mst_result) + mst_result.first.capacity() * sizeof(Edge);

        times.push_back(elapsed_time);
        memory_usages.push_back(memory_usage + mst_memory_usage);

        cout << "Nodes: " << num_nodes
            << ", Edges: " << num_edges
            << " -> Time: " << fixed << setprecision(6) << elapsed_time << "s"
            << ", Memory: " << (memory_usage + mst_memory_usage) / 1024.0 << " KB" << endl;
    }
    
    // export results for analysis
    ofstream result_file("cpp_performance_analysis.csv");
    result_file << "Nodes,Edges,ExecutionTime(s),MemoryUsage(KB)\n";
    for (size_t i = 0; i < node_sizes.size(); ++i) {
        result_file << node_sizes[i] << "," << edge_sizes[i] << ","
            << fixed << setprecision(6) << times[i] << ","
            << memory_usages[i] / 1024.0 << "\n";
    }
    result_file.close();

    cout << "Performance data saved to .csv\n";
}

int main() {
    vector<pair<vector<Edge>, int>> graphs;

    graphs.push_back(generate_random_graph(8, 16));
     graphs.push_back(generate_random_graph(50, 200));
    graphs.push_back(generate_random_graph(100, 500));
    graphs.push_back(generate_random_graph(500, 2000));
    graphs.push_back(generate_random_graph(1000, 5000));
    graphs.push_back(generate_random_graph(2000, 10000));
    analyze_performance(graphs);
   

    return 0;
}
