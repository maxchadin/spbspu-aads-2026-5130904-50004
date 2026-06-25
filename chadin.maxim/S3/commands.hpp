#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "graph.hpp"
#include "hashTable.hpp"
#include "blake2.hpp"
#include <string>
#include <istream>
#include <ostream>

namespace chadin {
  using GraphTable = HashTable< std::string, Graph, Blake2sHash, StringEqual >;

  void printGraphs(GraphTable& allGraphs, std::ostream& out);
  void printVertexes(GraphTable& allGraphs, const std::string& graphName, std::ostream& out);
  void printOutbound(GraphTable& allGraphs, const std::string& graphName, const std::string& vertexName, std::ostream& out);
  void printInbound(GraphTable& allGraphs, const std::string& graphName, const std::string& vertexName, std::ostream& out);
  void executeBind(GraphTable& allGraphs, std::istream& in, std::ostream& out);
  void executeCut(GraphTable& allGraphs, std::istream& in, std::ostream& out);
  void executeCreate(GraphTable& allGraphs, std::istream& in, std::ostream& out);
  void executeMerge(GraphTable& allGraphs, std::istream& in, std::ostream& out);
  void executeExtract(GraphTable& allGraphs, std::istream& in, std::ostream& out);
  void processCommands(std::istream& in, std::ostream& out, GraphTable& allGraphs);
}

#endif
