#pragma once

template<std::size_t n, class T = uint32_t>
class RingBuffer
{
   T data[n];
   std::size_t index {0};
public:
   void push (T val) {
      data[index++] = val;
      if (index == n) index = 0;
   }
};