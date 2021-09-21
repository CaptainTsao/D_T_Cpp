//
// Created by CaoRui on 2021/9/22.
//

#ifndef GRAPH_LIBRARY_NODE_HPP
#define GRAPH_LIBRARY_NODE_HPP

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <utility>

class Node {
  double data_;
  std::string name_;
  /* neighborMap: List of Nodes that this node has an edge to */
  std::unordered_map<std::string, std::multiset<double>> *neighbor_map_{};
  /* neighborSet: List of Nodes that have an edge to this node */
  std::unordered_set<std::string> neighbor_set_{};

public:
  Node(double data, std::string name);
  ~Node();

  void AddNeighbor(const std::string &neighbor_name, double weight);

  /* Access */
  double GetData() const;
  std::unordered_map<std::string, std::multiset<double>> *GetMapStr();
  std::unordered_set<std::string> &GetSetRef();
};

#endif //GRAPH_LIBRARY_NODE_HPP
