#include <cstdlib>
#include <ctime>

#include <iostream>
#include <vector>
#include <algorithm>

const int GRAPH_SIZE = 1000;

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

int main(int argc, char **argv)
{
  if (argc == 1)
  {
    std::cerr << "Usage: " << argv[0] << " graph_density" << std::endl;
    std::cerr << "graph_density: 0-100 - percent of edges in a graph" <<
      std::endl;
  }
  srand(time(NULL));
  int density = atoi(argv[1]);
  std::vector<std::vector<double>> graph(GRAPH_SIZE,
      std::vector<double>(GRAPH_SIZE, 0));
  std::vector<int> component_number(GRAPH_SIZE);
  for (int i = 0; i < component_number.size(); ++i)
  {
    component_number[i] = i;
  }
  int required_number = GRAPH_SIZE * (GRAPH_SIZE - 1) / 2 * density / 100;
  int added_edges = 0;
  while (added_edges < required_number)
  {
    int from = 0;
    int to = 0;
    while (from == to || graph[from][to] > 0.0 ||
        (added_edges < GRAPH_SIZE - 1 &&
         find_set(from, component_number) ==
         find_set(to, component_number)))
    {
      from = rand() % GRAPH_SIZE;
      to = rand() % GRAPH_SIZE;
    }
    union_sets(from, to, component_number);
    graph[from][to] = graph[to][from] = rand() / (RAND_MAX + 1.0);
    added_edges++;
  }
  for (int i = 0; i < GRAPH_SIZE; ++i)
  {
    for (int j = 0; j < i; ++j)
    {
      if (graph[i][j] != 0.0)
      {
        std::cout << j << ' ' << i << ' ' << graph[i][j] << std::endl;
      }
    }
  }

  return 0;
}
