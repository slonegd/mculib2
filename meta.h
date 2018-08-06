#pragma once

template <class T, class ... Types> T get1stArg (T arg1, Types ... otherArgs)
{
   return arg1;
}



template <class T, class ... Types> struct get1stType {
   using Result = T;
};


#define IS_SAME(T1,T2) (std::is_same<T1,T2>::value)




// определяет количество типов вариадика, пример:
// const uint8_t qty = QtyTypes<Types...>::value;
template <class T, class ... Types> struct QtyTypes {
   static const uint8_t value = 1 + QtyTypes<Types...>::value;
};
template<class T> struct QtyTypes<T> {
   static const uint8_t value = 1;
};


// определяет конкретный тип аргумента вариадика, пример:
// using Type = At<2, Types...>::Result;
template<uint8_t n, class T, class ... Types> struct At {
   using Result = typename At<n-1, Types...>::Result;
};
template<class T, class ... Types> struct At<1,T,Types...> {
   using Result = T;
};

// определяет первое положение конкретного типа из вариадика, пример:
// const int at = Position<T, Types...>::value;
// возвращает -1 если такого нет
template<int n, class T, class U, class ... Types>
struct PositionIterator {
   static const int value =
      std::is_same<T,U>::value ? n : PositionIterator<n + 1, T, Types...>::value;
};
template<int n, class T, class U>
struct PositionIterator<n, T, U> {
   static const int value =
      std::is_same<T,U>::value ? n : -1;
};
template<class T, class U, class ... Types> struct Position {
   static const int value =
      PositionIterator<1, T, U, Types...>::value;
};

template<class T, class ... Ts>
constexpr int position_v = Position<T,Ts...>::value;





