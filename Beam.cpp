#include <unordered_map>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct State 
{
    int currentNode; 
    vector<int> path;        
    double score;

    bool operator<(const State& other) const {
        return score < other.score;
    }
};

vector<int> beamSearch(const unordered_map<int, unordered_map<int, double>> &graph, int start, int target, int beamWidth)
{
     priority_queue<State> beam;
     beam.push({start, {start}, 1.0});
     while(!beam.empty())
     {
         State currentState = beam.top();
         beam.pop();
         int currentNode = currentState.currentNode;
         if(currentNode == target)
         {
             return currentState.path;
         }
         vector<State> candidates;
         if (graph.find(currentNode) != graph.end()) 
         {
            for (const auto& [neighbor, weight] : graph.at(currentNode)) 
            {
                double newScore = currentState.score * weight;
                vector<int> newPath = currentState.path;
                newPath.push_back(neighbor);
                candidates.push_back({neighbor, newPath, newScore});
            }
         }
         sort(candidates.begin(), candidates.end());
         reverse(candidates.begin(), candidates.end());
         for(int i = 0 ; i < min(beamWidth, (int)candidates.size()); ++i)
         {
             beam.push(candidates[i]);
         }
     }
     
     return {};
}

int main() 
{
    unordered_map<int, unordered_map<int, double>> graph;

    graph[0][1] = 0.5;  // Edge from 0 to 1 with weight 0.5
    graph[0][2] = 0.8;  // Edge from 0 to 2 with weight 0.8
    graph[0][3] = 0.2;  // Edge from 0 to 3 with weight 0.2
    graph[1][4] = 0.6;  // Edge from 1 to 4 with weight 0.6
    graph[1][5] = 0.3;  // Edge from 1 to 5 with weight 0.3
    graph[2][4] = 0.9;  // Edge from 2 to 4 with weight 0.9
    graph[2][5] = 0.7;  // Edge from 2 to 5 with weight 0.7
    graph[3][5] = 0.4;  // Edge from 3 to 5 with weight 0.4
    graph[3][6] = 0.5;  // Edge from 3 to 6 with weight 0.5
    graph[4][7] = 0.8;  // Edge from 4 to 7 with weight 0.8
    graph[5][7] = 0.6;  // Edge from 5 to 7 with weight 0.6
    graph[6][8] = 0.9;  // Edge from 6 to 8 with weight 0.9
    graph[7][9] = 1.0;  // Edge from 7 to 9 with weight 1.0
    graph[8][9] = 0.7;  // Edge from 8 to 9 with weight 0.7

    int start = 0, target = 9, beamWidth = 2;
    vector<int> result = beamSearch(graph, start, target, beamWidth);
    if (!result.empty()) 
    {
        cout << "Beam Search Path: ";
        for (int node : result) 
        {
            cout << node << " ";
        }
        cout << endl;
    } 
    else 
    {
        cout << "No path found from " << start << " to " << target << endl;
    }

    return 0;
}
