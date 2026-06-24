#ifndef STACK_HPP
#define STACK_HPP
#include "../common/list.hpp"

namespace chadin
{
  template< class T >
  class Stack
  {
  public:
    void push(const T & val) { data_.pushBack(val); }
    void pop() { data_.popBack(); }
    T & top() { return data_.getBack(); }
    bool isEmpty() const { return data_.isEmpty(); }
  private:
    List< T > data_;
  };
}
#endif
