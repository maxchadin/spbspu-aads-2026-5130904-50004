#ifndef QUEUE_HPP
#define QUEUE_HPP
#include "../common/list.hpp"

namespace chadin
{
  template< class T >
  class Queue
  {
  public:
    void push(const T & val) { data_.pushBack(val); }
    void pop() { data_.popFront(); }
    T & front() { return data_.getFront(); }
    bool isEmpty() const { return data_.isEmpty(); }
  private:
    List< T > data_;
  };
}
#endif
