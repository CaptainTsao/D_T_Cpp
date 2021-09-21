//
// Created by CaoRui on 2021/9/22.
//

#ifndef GRAPH_LIBRARY_NODE_HPP
#define GRAPH_LIBRARY_NODE_HPP

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <set>

class Node {
  double data_;
  std::string name_;
  /* neighborMap: List of Nodes that */
  std::unordered_map<std::string, std::multiset<double>> *neighborMap;
};

#endif //GRAPH_LIBRARY_NODE_HPP
