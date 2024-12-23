#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <set>
using namespace std;

struct PathCost 
{
    vector<int> path;
    int node;
    int cost;  
    bool operator>(const PathCost& other) const {
        return cost > other.cost;
    }
};

PathCost uniformCostSearch(unordered_map<int, unordered_map<int,int>> &graph,int start, int target)
{
    PathCost pathCost;
    priority_queue<PathCost, vector<PathCost>, greater<PathCost>> pq;
    PathCost firstPathCost;
    firstPathCost.path = {start};
    firstPathCost.cost = 0;
    firstPathCost.node = start;
    pq.push(firstPathCost);
    set<int> visited;
    while(!pq.empty())
    {
        PathCost currPathCost = pq.top();
        pq.pop();
        if (currPathCost.node == target)
        {
            return currPathCost;
        }
        if (visited.find(currPathCost.node) != visited.end()) 
        {
            continue;
        }

        unordered_map<int,int> edgeValues = graph[currPathCost.node];
        for (const auto& [neighbor, weight] : edgeValues) 
        {
            if (visited.find(neighbor) == visited.end()) 
            {
                PathCost newPathCost = currPathCost;
                newPathCost.path.push_back(neighbor);
                newPathCost.cost += weight;
                newPathCost.node = neighbor;
                pq.push(newPathCost);
            }
        }
    }
    return pathCost;
}

int main()
{
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
    PathCost result = uniformCostSearch(graph, start, goal);
    if (!result.path.empty()) 
    {
        cout << "The shortest path from " << start << " to " << goal << " is: ";
        for (int node : result.path) 
        {
            cout << node << " ";
        }
        cout << "\nTotal cost: " << result.cost << endl;
    } else 
    {
        cout << "No path found from " << start << " to " << goal << endl;
    }

    return 0;
}
