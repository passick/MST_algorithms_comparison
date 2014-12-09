#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
#include <set>
#include <list>

struct Edge
{
  int from;
  int to;
  double weight;

  bool operator<(const Edge& rhs) const
  {
    int min = std::min(from, to);
    int max = std::max(from, to);
    int min_rhs = std::min(rhs.from, rhs.to);
    int max_rhs = std::max(rhs.from, rhs.to);
    return weight < rhs.weight ||
      (weight == rhs.weight && (min < min_rhs ||
                                (min == min_rhs && max < max_rhs)));
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

void Boruvka(const std::vector<std::vector<Edge>>& input_graph,
    std::vector<Edge>& mst_edges)
{
  std::vector<std::list<Edge>> graph(input_graph.size());
  for (int i = 0; i < graph.size(); ++i)
  {
    graph[i].assign(input_graph[i].begin(), input_graph[i].end());
  }
  std::set<Edge> edges;
  std::vector<int> components(graph.size());
  for (int i = 0; i < components.size(); ++i)
  {
    components[i] = i;
  }
  std::vector<Edge> minimum_components_edges(graph.size(), {-1, -1, -1.0});
  while (edges.size() < graph.size() - 1)
  {
    for (int i = 0; i < graph.size(); ++i)
    {
      for (auto it = graph[i].begin(); it != graph[i].end();)
      {
        if (find_set(i, components) == find_set(it->to, components))
        {
          it = graph[i].erase(it);
          continue;
        }
        int component = find_set(i, components);
        if (minimum_components_edges[component].from < 0 ||
            *it < minimum_components_edges[component])
        {
          minimum_components_edges[component] = *it;
        }
        it++;
      }
    }
    for (auto& edge : minimum_components_edges)
    {
      if (edge.to >= 0)
      {
        union_sets(edge.from, edge.to, components);
        edges.insert(edge);
      }
      edge = {-1, -1, -1.0};
    }
  }
  mst_edges.assign(edges.begin(), edges.end());
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
  Boruvka(graph, mst);
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
