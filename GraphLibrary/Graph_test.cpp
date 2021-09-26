//
// Created by CaoRui on 2021/9/22.
//

#include "Graph.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string EdgeString(tuple<string, string, int>);

int main() {
  vector<string> nodes = {"A", "B", "C", "D"};
  Graph graph;
  graph.AddNode(1.1234, "A");
  graph.AddNode(-7.3, "B");
  graph.AddNode(420, "C");
  graph.AddNode(-12423, "D");

  graph.AddEdge("A", "B");
  graph.AddEdge("B", "C");
  graph.AddEdge("C", "D");
  graph.AddEdge("D", "A");

  cout << graph.GetInfo();
//  cout << graph.GetInfo();
  return 0;
}

string EdgeString(tuple<string, string, int> edge) {
  string str = get<0>(edge) + get<1>(edge) + to_string(get<2>(edge));
  return str;0
}