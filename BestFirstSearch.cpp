/*
    Greedy Best-First Search (GBFS) Algorithm:
    ------------------------------------------
    This implementation of Greedy Best-First Search (GBFS) is an informed search 
    algorithm that prioritizes expanding nodes based solely on a heuristic 
    function, h(n), which estimates the cost from the current node to the goal. 
    The algorithm uses a priority queue (min-heap) to always expand the node with 
    the smallest heuristic value first. While GBFS is efficient and often faster 
    than uninformed search methods, it does not guarantee finding the shortest 
    path as it entirely disregards edge weights (cumulative cost). Its performance 
    heavily depends on the quality of the heuristic function provided. This 
    algorithm is suitable for applications where speed is critical, and the 
    heuristic is reliable, but it may fail to find the optimal solution in cases 
    where edge weights play a significant role.
*/


#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <set>
using namespace std;

struct Node
{
	int id;        // Node ID
	int heuristic; // Heuristic value
	vector<int> pathTillNow;

	// Comparator for priority queue (min-heap based on heuristic)
	bool operator>(const Node& other) const {
		return heuristic > other.heuristic;
	}

	Node(int id, int heuristic, vector<int> pathTillNow) : id(id), heuristic(heuristic), pathTillNow(pathTillNow)
	{
	}
};

vector<int> greedyBestFirstSearch(unordered_map<int, unordered_map<int, int>> &graph, int start, int goal, unordered_map<int, int> &heuristic)
{
	priority_queue<Node, vector<Node>, greater<Node>> pq;
	Node firstNode(start, heuristic[start], {start});
	pq.push(firstNode);
	set<int> visited;
	while(!pq.empty())
	{
		Node currNode = pq.top();
		pq.pop();
		if(currNode.id == goal)
		{
			return currNode.pathTillNow;
		}
		int currId = currNode.id;
		if (visited.find(currId) != visited.end())
		{
			continue;
		}
		visited.insert(currId);
		unordered_map<int,int> childrenMap = graph[currId];
		for (auto el : childrenMap)
		{
			int neighbour = el.first;
			if (visited.find(neighbour) == visited.end())
			{
				vector<int> pathTillNeighbour = currNode.pathTillNow;
				pathTillNeighbour.push_back(neighbour);
				int heuristicNew = heuristic[neighbour];
				Node newNode(neighbour, heuristicNew, pathTillNeighbour);
				pq.push(newNode);
			}
		}
	}
	return {};
}

int main()
{
	unordered_map<int, unordered_map<int, int>> graph;
	// Graph definition
	graph[0] = {{1, 4}, {2, 2}, {3, 5}};
	graph[1] = {{4, 1}, {5, 6}};
	graph[2] = {{4, 2}, {6, 3}};
	graph[3] = {{5, 3}, {6, 2}};
	graph[4] = {{7, 5}, {8, 8}};
	graph[5] = {{7, 4}, {9, 7}};
	graph[6] = {{8, 6}, {9, 3}};
	graph[7] = {{9, 1}};
	graph[8] = {{9, 2}};

	// Arbitary heuristic values
	unordered_map<int, int> heuristic =
	{
		{0, 10},
		{1, 8},
		{2, 5},
		{3, 7},
		{4, 6},
		{5, 4},
		{6, 3},
		{7, 3},
		{8, 2},
		{9, 0}
	};
	int start = 0, goal = 9;
	vector<int> result = greedyBestFirstSearch(graph, start, goal, heuristic);

	// Display the result
	if (!result.empty())
	{
		cout << "Path found: ";
		for (int node : result)
		{
			cout << node << " ";
		}
		cout << endl;
	}
	else
	{
		cout << "No path found" << endl;
	}
	return 0;
}
