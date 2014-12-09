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

int find_set(int v, std::vector<int>& parent)
{
  if (v == parent[v])
  {
    return v;
  }
  return parent[v] = find_set(parent[v], parent);
}

void union_sets(int u, int v, std::vector<int>& parent)
{
  u = find_set(u, parent);
  v = find_set(v, parent);
  if (u != v)
  {
    parent[u] = v;
  }
}

void Kruskal(const std::vector<std::vector<Edge>>& graph,
    std::vector<Edge>& mst_edges)
{
  std::vector<int> components(graph.size());
  for (int i = 0; i < components.size(); ++i)
  {
    components[i] = i;
  }
  std::priority_queue<Edge> all_edges;
  for (int i = 0; i < graph.size(); ++i)
  {
    for (auto edge : graph[i])
    {
      if (edge.from < edge.to)
      {
        all_edges.push(edge);
      }
    }
  }
  for (int iteration = 0; iteration < graph.size() - 1; ++iteration)
  {
    Edge current_edge;
    do
    {
      current_edge = all_edges.top();
      all_edges.pop();
    }
    while (find_set(current_edge.to, components) ==
        find_set(current_edge.from, components));
    mst_edges.push_back(current_edge);
    union_sets(current_edge.from, current_edge.to, components);
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
  Kruskal(graph, mst);
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
