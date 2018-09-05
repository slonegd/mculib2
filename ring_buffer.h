#pragma once

#include <cstdint>

template<int n, class T = uint32_t>
class RingBuffer
{
protected:
   T data[n] {0};
   int index {0};
public:
   void push (T val) {
      data[index++] = val;
      index %= n;
   }
};


/// дополнительно хранит сумму
template<int n, class T = uint32_t>
class SumRingBuffer : private RingBuffer<n, T>
{
   T sum;
public:
   void pushAndCompute (T val) {
      sum -= this->data[this->index];
      this->push(val);
      sum += val;
   }
   T getSum() { return sum; }
   T getAvg() { return sum / n; }
};