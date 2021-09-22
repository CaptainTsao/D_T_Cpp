//
// Created by CaoRui on 2021/9/22.
//

#ifndef GRAPH_LIBRARY_GRAPH_HPP
#define GRAPH_LIBRARY_GRAPH_HPP
#include <vector>
#include <utility>
#include <tuple>
#include "Node.hpp"

class Graph {
private:
  std::unordered_map<std::string, Node *> node_map_;
  bool directed_{true};
public:
  /* Constructors & Destructor */
  Graph() = default; // Graph are directed by default
  explicit Graph(bool directed);
  Graph(const Graph &other); /* Copy constructor, uses GetEdges function */
  explicit Graph(const std::string &input_file_name); /* Constructor Graph from .txt file */
  ~Graph();

  /* Trivial */
  bool AddNode(double data, std::string name);
  bool AddNode(const std::string &name);
  void AddNode(const std::vector<std::string> &nodes);
  void AddNode(std::vector<std::pair<double, std::string>> nodes);
  bool AddEdge(std::string from_node, std::string to_node, double weight);
  bool AddEdge(std::string from_node, std::string to_node);
  bool AddEdge(std::tuple<std::string, std::string, double> edge);
  bool DeleteNode(std::string target_node);
  bool DeleteNode(std::string from_node, std::string to_node, double weight);
  bool DeleteNode(std::string from_node, std::string to_node);

  /* Undirected Graph specific functions */
  bool connected();

  /* Directed graph specific functions */
  bool WeaklyConnected() const;
  bool StronglyConnected();

  /* Modification Functions */
  Graph Transpose() const;    /* Create a copy, reverses edges of that copy and returns it. */

  /* Neighbor functions */
  std::vector<std::string> NeighborNames(std::string name);
  std::vector<std::pair<std::string, double>> NeighborDistMin(std::string name);
  std::vector<std::pair<std::string, double>> NeighborDistMax(std::string name);
  bool DeleteNeighbors(std::string name);

  /* Explore Functions */
  std::unordered_set<std::string> Explore(std::string source_node);
  void ExploreHelper(std::unordered_set<std::string> &visited, std::string name);
  std::vector<std::string> ReachableNames(std::string source_node);
  std::vector<std::string, double> ReachableDists(std::string source_node);
  bool PathCheck(std::string from_node, std::string to_node);

  /* Core Graph Functions */
  std::vector<std::string> BFS(const std::string &source_node, const std::string &target_node);
  std::vector<std::string> DFS(const std::string &source_node, const std::string &target_node);
  void DFSHelper(const std::string &current_node,
                 const std::string &target_node,
                 std::unordered_map<std::string, std::string> &prev_map);
  std::vector<std::string> Dijktras(std::string source_node, std::string target_node);
  std::unordered_map<std::string, double> Dijktras(std::string source_node);

  /* MST Functions */
  Graph Prims();
  Graph Kruskals();

  /* About Graph Functions */
  std::string GetInfo();    /* Return a list of all Nodes along with their Edges */
  std::vector<std::tuple<std::string, std::string, double>> GetEdges() const;
  /* Return a vector edge, when Edges are represented with a 3-tuple*/
  std::vector<std::tuple<std::string, std::string, double>> GetEdgesAscending() const;
  std::vector<std::tuple<std::string, std::string, double>> GetEdgesDescending() const;
  int NumNodes();
  int NumEdges();
  bool NodeExists(std::string node);

  /* Persistent Graph Functions */
  bool SaveGraph(const std::string &out_put_file_name);
};
#endif //GRAPH_LIBRARY_GRAPH_HPP
