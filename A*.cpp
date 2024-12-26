#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <set> // For set
using namespace std;

// Node structure for A* search
struct Node {
    int id;                     // Node ID
    vector<int> pathTillNow;    // Path from start to this node
    int gcost;                  // g(n): Cost to reach this node
    int hcost;                  // h(n): Heuristic cost to the goal

    // Comparator for priority queue (min-heap based on gcost + hcost)
    bool operator>(const Node& other) const {
        return gcost + hcost > other.gcost + other.hcost;
    }

    // Constructor for convenience
    Node(int id, vector<int> pathTillNow, int gcost, int hcost) 
        : id(id), pathTillNow(pathTillNow), gcost(gcost), hcost(hcost) {}
};

// A* Search function
vector<int> getAStarSearch(unordered_map<int, unordered_map<int, int>>& graph, unordered_map<int, int>& heuristic, int start, int goal) {
    // Priority queue for A* (min-heap)
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    // Push the start node into the priority queue
    pq.push(Node(start, {start}, 0, heuristic[start]));

    // Set to track visited nodes
    set<int> visited;

    while (!pq.empty()) {
        // Get the node with the smallest fCost
        Node currNode = pq.top();
        pq.pop();

        // If the goal is reached, return the path
        if (currNode.id == goal) {
            return currNode.pathTillNow;
        }

        // Skip already visited nodes
        if (visited.find(currNode.id) != visited.end()) {
            continue;
        }

        // Mark the current node as visited
        visited.insert(currNode.id);

        // Explore neighbors
        for (const auto& [neighbor, weight] : graph[currNode.id]) {
            int newGCost = currNode.gcost + weight;     // Calculate new g(n)
            int newHCost = heuristic[neighbor];        // Heuristic for the neighbor
            vector<int> newPath = currNode.pathTillNow;
            newPath.push_back(neighbor);               // Append the neighbor to the path
            pq.push(Node(neighbor, newPath, newGCost, newHCost));
        }
    }

    // If no path is found, return an empty vector
    return {};
}

int main() {
    // Declaring and constructing a bushy graph
    unordered_map<int, unordered_map<int, int>> graph;
    graph[0] = {{1, 4}, {2, 2}, {3, 5}};
    graph[1] = {{4, 1}, {5, 6}};
    graph[2] = {{4, 2}, {6, 3}};
    graph[3] = {{5, 3}, {6, 2}};
    graph[4] = {{7, 5}, {8, 8}};
    graph[5] = {{7, 4}, {9, 7}};
    graph[6] = {{8, 6}, {9, 3}};
    graph[7] = {{9, 1}};
    graph[8] = {{9, 2}};

    int start = 0;
    int goal = 9;

    // Heuristic values
    unordered_map<int, int> heuristic = {
        {0, 10}, {1, 8}, {2, 5}, {3, 7},
        {4, 6}, {5, 4}, {6, 3}, {7, 3},
        {8, 2}, {9, 0}
    };

    // Run A* search
    vector<int> resultPath = getAStarSearch(graph, heuristic, start, goal);

    // Display the result
    if (!resultPath.empty()) {
        cout << "Path found: ";
        for (auto el : resultPath) {
            cout << el << " ";
        }
        cout << endl;
    } else {
        cout << "No path found" << endl;
    }

    return 0;
}
