//
// Created by CaoRui on 2021/9/22.
//

#include <utility>
#include "Node.hpp"

void Node::AddNeighbor(const std::string &neighbor_name, double weight) {
  /* If the new neighbor is not already a neighbor add it to the list */
  if (neighbor_map_->find(neighbor_name) == neighbor_map_->end()) {
    std::multiset<double> tmp_set;
    std::pair<std::string, std::multiset<double>> tmp_pair(neighbor_name, tmp_set);
    neighbor_map_->insert(tmp_pair);
  }

  /* Add edge of this 'weight' */
  (*neighbor_map_)[neighbor_name].insert(weight);
}
std::unordered_map<std::string, std::multiset<double>> *Node::GetMapStr() {
  return neighbor_map_;
}
std::unordered_set<std::string> &Node::GetSetRef() {
  return neighbor_set_;
}
double Node::GetData() const {
  return data_;
}
Node::Node(double data, std::string name) : data_(data),
                                            name_(std::move(name)),
                                            neighbor_map_(new std::unordered_map<std::string,
                                                                                 std::multiset<double>>()),
                                            neighbor_set_({}) {}
Node::~Node() {
  delete neighbor_map_;
}
