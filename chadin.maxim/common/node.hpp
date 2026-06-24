#ifndef NODE_HPP
#define NODE_HPP

namespace chadin
{
  template< class T >
  struct Node
  {
    T data;
    Node * next;
    Node * prev;
  };
}

#endif
