#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>

const int GRAPH_SIZE = 1000;

struct Edge
{
  int from;
  int to;
  double weight;

  bool operator<(const Edge& rhs) const
  {
    return weight > rhs.weight;
  }
};

void Prim(const std::vector<std::vector<Edge>>& graph,
    std::vector<Edge>& mst_edges)
{
  std::priority_queue<Edge> edges_list;
  edges_list.push({0, 0, 0.0});
  std::vector<bool> currently_in_mst(graph.size(), false);
  while (!edges_list.empty())
  {
    Edge current_edge = edges_list.top();
    int v = current_edge.to;
    edges_list.pop();
    if (currently_in_mst[v])
    {
      continue;
    }
    if (current_edge.from != current_edge.to)
    {
      mst_edges.push_back(current_edge);
    }
    currently_in_mst[v] = true;
    for (const Edge& edge : graph[v])
    {
      if (!currently_in_mst[edge.to])
      {
        edges_list.push(edge);
      }
    }
  }
}

int main()
{
  int graph_size, edges;
  std::cin >> graph_size >> edges;
  std::vector<std::vector<Edge>> graph(graph_size);
  for (int i = 0; i < edges; ++i)
  {
    int from, to;
    double weight;
    std::cin >> from >> to >> weight;
    graph[from].push_back({from, to, weight});
    graph[to].push_back({to, from, weight});
  }
  std::vector<Edge> mst;
  Prim(graph, mst);
  std::sort(mst.begin(), mst.end(),
      [](const Edge& e1, const Edge& e2)
      { return std::make_pair(
          std::min(e1.from, e1.to), std::max(e1.from, e1.to)) <
              std::make_pair(
                  std::min(e2.from, e2.to), std::max(e2.from, e2.to));
              });
  for (auto edge : mst)
  {
    std::cout << std::min(edge.from, edge.to) << ' ' <<
      std::max(edge.from, edge.to) << ' ' << edge.weight << std::endl;
  }

  return 0;
}
