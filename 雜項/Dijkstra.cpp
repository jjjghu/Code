#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <climits>

using namespace std;

class Graph
{
public:
    unordered_map<char, vector<pair<char, int>>> adjList;

    void addEdge(char u, char v, int weight)
    {
        adjList[u].emplace_back(v, weight);
        adjList[v].emplace_back(u, weight); // 對於無向圖，雙向添加
    }

    void dijkstra(char start)
    {
        // 儲存每個點的最短距離，初始化為無窮大
        unordered_map<char, int> distances;
        for (const auto &pair : adjList)
        {
            distances[pair.first] = INT_MAX;
        }
        distances[start] = 0;

        // 優先隊列儲存 (距離, 節點)
        set<pair<int, char>> priorityQueue;
        priorityQueue.emplace(0, start);

        cout << "從節點 " << start << " 開始 Dijkstra 演算法:" << endl;

        while (!priorityQueue.empty())
        {
            auto temp = *priorityQueue.begin();
            int currentDistance = temp.first;
            char currentNode = temp.second;
            priorityQueue.erase(priorityQueue.begin());

            cout << "處理節點 " << currentNode << "，當前距離為 " << currentDistance << endl;

            // 遍歷相鄰的節點
            for (const auto &neighbor : adjList[currentNode])
            {
                char neighborNode = neighbor.first;
                int edgeWeight = neighbor.second;

                int newDistance = currentDistance + edgeWeight;

                // 如果找到更短的路徑，更新距離並加入優先隊列
                if (newDistance < distances[neighborNode])
                {
                    if (distances[neighborNode] != INT_MAX)
                    {
                        cout << "更新節點 " << neighborNode << " 的距離從 " << distances[neighborNode]
                             << " 更新為 " << newDistance << endl;
                    }

                    priorityQueue.erase({distances[neighborNode], neighborNode});
                    distances[neighborNode] = newDistance;
                    priorityQueue.emplace(newDistance, neighborNode);
                }
            }
        }

        // 輸出最短距離
        cout << "\n最短距離結果:" << endl;
        for (const auto &pair : distances)
        {
            cout << "最短路徑到 " << pair.first << " 的距離是: " << pair.second << endl;
        }
    }
};

int main()
{
    Graph graph;

    // 添加邊，根據提供的圖
    graph.addEdge('a', 'g', 1);
    graph.addEdge('a', 'b', 3);
    graph.addEdge('a', 'c', 2);
    graph.addEdge('b', 'd', 4);
    graph.addEdge('c', 'e', 5);
    graph.addEdge('c', 'f', 3);
    graph.addEdge('g', 'f', 2);
    graph.addEdge('d', 'e', 9);
    graph.addEdge('d', 'd', 4); // d 到 d 的邊（自環）
    graph.addEdge('e', 'f', 7);

    // 從節點 a 開始 Dijkstra 演算法
    graph.dijkstra('a');

    return 0;
}
