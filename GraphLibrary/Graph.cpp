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
  while (line[0] != specific_char) {
    /* Split up node name and node data using the separator character */
    std::string node_name = line.substr(0, line.find(separator));
    std::string data_string = line.substr(line.find(separator) + 1);
    double node_data = std::stod(data_string);

    /* Add Node to Graph, read next line */
    AddNode(node_data, node_name);
    std::getline(file, line);
  }

  /* Read Edges */
  if (line != specific_char + std::string("EDGES (Do not edit this line):")) {
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
  if (node_map_.find(source_node) == node_map_.end()) {
    return path_vec;
  }
  if (node_map_.find(target_node) == node_map_.end()) {
    return path_vec;
  }
  /* prev_map[X] will contain the Node*/
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
    for (std::string N: neighbor_current) {
      if (prev_map.find(N) == prev_map.end()) {
        que.push(N);
        prev_map.emplace(N, current_node);
      }
    }
  }

  /* If the target_node was not found return an empty vector */
  if (prev_map.find(target_node) == prev_map.end()) {
    return path_vec;
  }
  /* use prev_map to get the path from target back to source */
  std::string curr_node = target_node;
  path_vec.push_back(curr_node);
  while (true) {
    curr_node = prev_map[curr_node];
    if (curr_node.empty()) {
      break;
    }
    path_vec.push_back(curr_node);
  }
  /* Reverse path_vec so the Node's are in order from Source to Target */
  std::reverse(path_vec.begin(), path_vec.end());
  return path_vec;
}

/* BFS: Returns the shortest unweighted path from source_node to target_node */
std::vector<std::string> Graph::DFS(const std::string &source_node, const std::string &target_node) {
  /* If either Node DNE, return an empty vector */
  std::vector<std::string> path_vec;
  if (node_map_.find(source_node) == node_map_.end()) {
    return path_vec;
  }
  if (node_map_.find(target_node) == node_map_.end()) {
    return path_vec;
  }
  std::unordered_map<std::string, std::string> prev_map;
  prev_map.emplace(source_node, "");

  /* Recursive Kick-Off */
  DFSHelper(source_node, target_node, prev_map);
  if (prev_map.find(target_node) == prev_map.end()) {
    return path_vec;
  }

  /* use prev_map to get the path from Target back to Source */
  std::string current_node = target_node;
  path_vec.push_back(current_node);
  while (true) {
    current_node = prev_map[current_node];
    if (current_node.empty()) {
      break;
    }
    path_vec.push_back(current_node);
  }
  std::reverse(path_vec.begin(), path_vec.end());
  return {};
}
void Graph::DFSHelper(const std::string &current_node,
                      const std::string &target_node,
                      std::unordered_map<std::string, std::string> &prev_map) {
  if (current_node == target_node) {
    return;
  }
  std::vector<std::string> neighbors = NeighborNames(current_node);
  for (const std::string &neighbor: neighbors) {
    /* If */
    if (prev_map.find(neighbor) == prev_map.end()) {
      prev_map.emplace(neighbor, current_node);
      DFSHelper(neighbor, target_node, prev_map);
    }
  }
}
