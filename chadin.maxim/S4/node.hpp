#ifndef NODE_HPP
#define NODE_HPP

#include <utility>

namespace chadin {

struct NodeBase {
  NodeBase* left;
  NodeBase* right;
  NodeBase* parent;
};

template <class Key, class Value>
struct Node : public NodeBase {
  std::pair<const Key, Value> data;

  Node(const Key& k, const Value& v):
    data(k, v)
  {
  }
};

}

#endif
