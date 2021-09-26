//
// Created by CaoRui on 2021/9/22.
//

#include "Graph.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
#include <limits>
#include <queue>

Graph::Graph(bool directed) : directed_(directed) {}
Graph::Graph(const Graph &other) {
  directed_ = other.directed_;
  /* Add all nodes in original to new Graph */
  for (const auto &iter: other.node_map_) {
    double data = iter.second->GetData();
    std::string name = iter.first;
    Node *new_node = new Node(data, name);
    node_map_.emplace(name, new_node);
  }
  /* Add all edges in original to new Graph */
  std::vector<std::tuple<std::string, std::string, double>> edge_vec = other.GetEdges();
  for (const auto &edge: edge_vec) {
    std::string node_A = std::get<0>(edge);
    std::string node_B = std::get<1>(edge);
    double weight = std::get<2>(edge);

    AddEdge(node_A, node_B, weight);
  }
}

/* Constructor from File - when calling need to cast to string */
Graph::Graph(const std::string &input_file_name) {
  std::ifstream file(input_file_name);
  char specific_char = '%';
  char separator = '^';
  std::string line;

  /* If file is invalid, stop */
  if (!file.is_open()) {
    return;
  }

  /* Read Header */
  std::getline(file, line);
  while (line[0]!=specific_char) {
    /* Split up node name and node data using the separator character */
    std::string node_name = line.substr(0, line.find(separator));
    std::string data_string = line.substr(line.find(separator) + 1);
    double node_data = std::stod(data_string);

    /* Add Node to Graph, read next line */
    AddNode(node_data, node_name);
    std::getline(file, line);
  }

  /* Read Edges */
  if (line!=specific_char + std::string("EDGES (Do not edit this line):")) {
    return;
  }
  while (std::getline(file, line)) {
    std::string source_node = line.substr(0, line.find(separator));
    line = line.substr(line.find(separator) + 1);
    std::string target_node = line.substr(0, line.find(separator));
    std::string weight_string = line.substr(line.find(separator) + 1);
    double weight = std::stod(weight_string);

    std::cout << source_node << " " << target_node << " " << weight << std::endl;
    /* Add Edge to Graph */
    AddEdge(source_node, target_node, weight);
  }
}
Graph::~Graph() {
  for (const auto &iter: node_map_) {
    delete iter.second;
  }
}

/* BFS: Returns the shortest unweighted path from source_node to target_node */
std::vector<std::string> Graph::BFS(const std::string &source_node, const std::string &target_node) {
  /* If either Node DNE, return an empty vector */
  std::vector<std::string> path_vec;
  if (node_map_.find(source_node)==node_map_.end()) {
    return path_vec;
  }
  if (node_map_.find(target_node)==node_map_.end()) {
    return path_vec;
  }
  /* prev_map[X] will contain the Node previous to X. Also keeps track of which Nodes have been visited. */
  std::unordered_map<std::string, std::string> prev_map;
  prev_map.emplace(source_node, "");

  /* BFS */
  std::queue<std::string> que;
  que.push(source_node);

  while (!que.empty()) {
    std::string current_node = que.front();
    que.pop();
    /* For all neighbors N of current_node */
    std::vector<std::string> neighbor_current = NeighborNames(current_node);
    for (const std::string &N: neighbor_current) {
      if (prev_map.find(N)==prev_map.end()) {   /* 如果N不在临近节点中，将其放入que中，*/
        que.push(N);
        prev_map.emplace(N, current_node);
      }
    }
  }

  /* If the target_node was not found return an empty vector */
  if (prev_map.find(target_node)==prev_map.end()) {
    return path_vec;
  }
  /* use prev_map to get the path from target back to source */
  std::string curr = target_node;
  path_vec.push_back(curr);
  while (true) {
    curr = prev_map[curr];
    if (curr.empty()) {
      break;
    }
    path_vec.push_back(curr);
  }
  /* Reverse path_vec so the Node's are in order from Source to Target */
  std::reverse(path_vec.begin(), path_vec.end());
  return path_vec;
}

/* BFS: Returns the shortest unweighted path from source_node to target_node */
std::vector<std::string> Graph::DFS(const std::string &source_node, const std::string &target_node) {
  /* If either Node DNE, return an empty vector */
  std::vector<std::string> path_vec;
  if (node_map_.find(source_node)==node_map_.end()) {
    return path_vec;
  }
  if (node_map_.find(target_node)==node_map_.end()) {
    return path_vec;
  }
  std::unordered_map<std::string, std::string> prev_map;
  prev_map.emplace(source_node, "");

  /* Recursive Kick-Off */
  DFSHelper(source_node, target_node, prev_map);
  /* If the target node was not found return an empty vector */
  if (prev_map.find(target_node)==prev_map.end()) {
    return path_vec;
  }

  /* use prev_map to get the path from Target back to Source */
  std::string curr = target_node;
  path_vec.push_back(curr);
  while (true) {
    curr = prev_map[curr];
    if (curr.empty()) {
      break;
    }
    path_vec.push_back(curr);
  }
  std::reverse(path_vec.begin(), path_vec.end());
  return {};
}
void Graph::DFSHelper(const std::string &current_node,
                      const std::string &target_node,
                      std::unordered_map<std::string, std::string> &prev_map) {
  if (current_node==target_node) {
    return;
  }
  std::vector<std::string> neighbors = NeighborNames(current_node);
  for (const std::string &neighbor: neighbors) {
    /* If */
    if (prev_map.find(neighbor)==prev_map.end()) {
      prev_map.emplace(neighbor, current_node);
      DFSHelper(neighbor, target_node, prev_map);
    }
  }
}
bool Graph::AddNode(double data, std::string name) {
  /* If node already exist, return false */
  if (node_map_.find(name)!=node_map_.end()) {
    return false;
  }

  /* Else, Dynamically Allocate a new Node and put it in `node_map_` */
  Node *new_node = new Node(data, name);
  node_map_.emplace(name, new_node);

  return true;
}
void Graph::AddNode(const std::vector<std::string> &nodes) {
  for (const auto &node: nodes) {
    AddNode(node);
  }
}
bool Graph::AddNode(const std::string &name) {
  return AddNode(1, name);
}

/* GetInfo: Returns a string of all Nodes along with their Edges. */
std::string Graph::GetInfo() {
  std::stringstream ss;
  ss << std::fixed;   /* Prevented scientific-notation */
  ss << "\n\nGraph Info: " << std::endl;
  /* For Every Node */
  for (const auto &iterA: node_map_) {
    ss << "[" << iterA.first << ": " << iterA.second->GetData() << "] ";
    /* For Every Neighbor of Node */
    for (const auto &iterB: *(iterA.second->GetMapPtr())) {
      ss << "(" << iterB.first << "): ";
      /* Print Each Edge of Neighbor */
      for (const auto &weight: iterB.second) {
        ss << weight << ", ";
      }
    }
    ss << "\n\n";
  }
  return ss.str();
}
std::vector<std::tuple<std::string, std::string, double>> Graph::GetEdges() const {
  std::vector<std::tuple<std::string, std::string, double>> edge_vec;

  /* For all Nodes K in node_map */
  for (const auto &iter: node_map_) {
    auto K = iter.second;
    /* For all neighbors N of K */
    for (const auto &iter1: *(K->GetMapPtr())) {
      auto tmp_set = iter1.second;
      /* For all weights from K to N, add it to the edge_vec */
      for (const auto &i: tmp_set) {
        std::string node_A = iter.first;
        std::string node_B = iter1.first;
        std::tuple<std::string, std::string, double> tmp_tuple(node_A, node_B, i);
        edge_vec.push_back(tmp_tuple);
      }
    }
  }

  /* If the graph is undirected, post-process to delete duplicate ie(NodeA, NodeB), and */
  if (!directed_) {
    std::vector<std::tuple<std::string, std::string, double>> delete_these_edges;
    for (const auto &edge: edge_vec) {
      std::string node_A = std::get<0>(edge);
      std::string node_B = std::get<1>(edge);
      double weight = std::get<2>(edge);

      std::tuple<std::string, std::string, double> delete_me(node_B, node_A, weight);
      if (node_A > node_B) {
        delete_these_edges.push_back(delete_me);
      }
    }
    for (const auto &edge: delete_these_edges) {
      edge_vec.erase(std::remove(edge_vec.begin(), edge_vec.end(), edge), edge_vec.end());
    }
  }

  return edge_vec;
}
std::vector<std::tuple<std::string, std::string, double>> Graph::GetEdgesAscending() const {
  std::vector<std::tuple<std::string, std::string, double>> edges = GetEdges();
  std::sort(edges.begin(), edges.end(),
            [](const std::tuple<std::string, std::string, double> &a,
               const std::tuple<std::string, std::string, double> &b) -> bool {
              return std::get<2>(a) < std::get<2>(b);
            });
  return edges;
}
std::vector<std::tuple<std::string, std::string, double>> Graph::GetEdgesDescending() const {
  std::vector<std::tuple<std::string, std::string, double>> edges = GetEdges();
  std::sort(edges.begin(), edges.end(),
            [](const std::tuple<std::string, std::string, double> &a,
               const std::tuple<std::string, std::string, double> &b) -> bool {
              return std::get<2>(a) > std::get<2>(b);
            });
  return edges;
}
Graph::tp_size Graph::NumNodes() {
  return node_map_.size();
}
Graph::tp_size Graph::NumEdges() const {
  return GetEdges().size();
}
bool Graph::NodeExists(const std::string &name) {
  return (node_map_.find(name)!=node_map_.end());
}
std::vector<std::string>
Graph::NeighborNames(const std::string &name) {
  std::vector<std::string> return_vec;

  std::unordered_map<std::string, std::multiset<double>> *neighbor_map_ptr = node_map_[name]->GetMapPtr();
  for (const auto &it: *neighbor_map_ptr) {
    return_vec.push_back(it.first);
  }
  return return_vec;
}

/* NeighborDistMin: returns a list of names of neighbors along with the lowest edge weight to each neighbor */
std::vector<std::pair<std::string, double>> Graph::NeighborDistMin(const std::string &name) {
  std::vector<std::pair<std::string, double>> return_vec;

  std::unordered_map<std::string, std::multiset<double>> *neighbor_map_ptr = node_map_[name]->GetMapPtr();
  for (const auto &iter: *neighbor_map_ptr) {
    std::pair<std::string, double> temp_pair(iter.first, *std::min_element(iter.second.begin(), iter.second.end()));
    return_vec.push_back(temp_pair);
  }

  return return_vec;
}

/* NeighborDistMax: returns a list of names of neighbors along with the highest edge weight to each neighbor */
std::vector<std::pair<std::string, double>> Graph::NeighborDistMax(const std::string &name) {
  std::vector<std::pair<std::string, double>> return_vec;

  std::unordered_map<std::string, std::multiset<double>> *neighbor_map_ptr = node_map_[name]->GetMapPtr();
  for (const auto &iter: *neighbor_map_ptr) {
    std::pair<std::string, double> temp_pair(iter.first, *std::max_element(iter.second.begin(), iter.second.end()));
    return_vec.push_back(temp_pair);
  }

  return return_vec;
}

/* DeleteNeighbors: moves all neighbors of name along with all the edges associated with the neighbors */
bool Graph::DeleteNeighbors(const std::string &name) {
  if (node_map_.find(name)==node_map_.end()) {
    return false;
  }

  std::vector<std::string> neighbors = NeighborNames(name);
  for (const auto &neighbor: neighbors) {
    DeleteNode(neighbor);
  }
  return true;
}

/* Explore: returns a set of nodes reachable from source_node */
std::unordered_set<std::string> Graph::Explore(const std::string &source_node) {
  std::unordered_set<std::string> reachable;
  ExploreHelper(reachable, source_node);
  return reachable;
}

void Graph::ExploreHelper(std::unordered_set<std::string> &visited, const std::string &name) {
  visited.insert(name);
  std::vector<std::string> neighbors = NeighborNames(name);

  for (const auto &neighbor: neighbors) {
    if (visited.find(neighbor)==visited.end()) {
      ExploreHelper(visited, neighbor);
    }
  }
}
std::vector<std::string> Graph::ReachableNames(const std::string &source_node) {
  std::vector<std::string> return_vec;
  std::unordered_set<std::string> reachable = Explore(source_node);
  return_vec.reserve(reachable.size());
  for (const std::string &name: reachable) {
    return_vec.push_back(name);
  }
  return return_vec;
}

/* connected: returns true if the Graph is connected, for undirected graphs. */
bool Graph::connected() {
  if (node_map_.empty()) {
    return true;
  }

  /* Return explore on a random node */
  auto iter = node_map_.begin();
  std::unordered_set<std::string> tmp_set = Explore(iter->first);
  /* Is the set of node reachable == # of all nodes in the Graph? */
  return (tmp_set.size()==node_map_.size());
}

/**
 * @brief returns true if the Graph is strong-connected, for directed graphs.
 * A directed graph is called strongly connected if there is a path in each
 * direction between each pair of vertices of the graph
 * */
bool Graph::StronglyConnected() {
  /* DFS on arbitrary node. If arbitrary node can't reach all other nodes, return false */
  std::string arbitrary_node = node_map_.begin()->first;
  std::unordered_set<std::string> tmp_set = Explore(arbitrary_node);
  if (tmp_set.size()!=node_map_.size()) {
    return false;
  }
  /* DFS on same */
  Graph T = Transpose();
  std::unordered_set<std::string> tmp_set1 = T.Explore(arbitrary_node);
  std::cout << "***" << tmp_set1.size() << std::endl;

  return (tmp_set1.size()==node_map_.size());
}


bool Graph::WeaklyConnected() const {
  if (node_map_.empty()) {
    return true;
  }

  Graph modified_copy(*this);
  /* replace all directed edges with undirected edges */
  std::vector<std::tuple<std::string, std::string, double>> edge_vec = modified_copy.GetEdges();
  for (const auto &edge: edge_vec) {
    std::string node_A = std::get<0>(edge);
    std::string node_B = std::get<1>(edge);
    double weight = std::get<2>(edge);
    modified_copy.AddEdge(node_B, node_A, weight);
  }
  /* Test if the modified copy is connected */
  return modified_copy.connected();
}

/**
 * @brief Transpose: Returns a Graph object with reversed edges of the original Graph.
 **/
Graph Graph::Transpose() const {
  /* Create a new Graph object. */
  Graph graph(directed_);

  /* Add all existing nodes to the new graph. */
  for (const auto &iter : node_map_) {
    double data = iter.second->GetData();
    graph.AddNode(data, iter.first);
  }

  /* For all edges A, B, w  in the original*/
  std::vector<std::tuple<std::string, std::string, double>> edge_vec = this->GetEdges();
  for (const auto &edge: edge_vec) {
    std::string node_A = std::get<0>(edge);
    std::string node_B = std::get<1>(edge);
    double weight = std::get<2>(edge);

    graph.AddEdge(node_B, node_A, weight);
  }
  return graph;
}

