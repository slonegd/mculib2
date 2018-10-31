#include "meta.h"
#include <iostream>

bool get1stArg_()
{
   bool good = true;
   good &= (get1stArg(1,2,5) == 1);
   static_assert (get1stArg(1,2,5) == 1);
   good &= (get1stArg(true,2.0,3) == true);
   static_assert (get1stArg(true,2.0,3) == true);
   return good;
}

bool get1stType_()
{
   bool good = true;
   good &= std::is_same_v<get1st_t<int, bool>, int>;
   return good;
}

int main()
{
   std::cout << '\n'
             << "Тесты файла meta.h:" << std::endl;

   auto test = [](auto s, auto f){
      std::cout << s << (f() ? "\033[32mпрошёл\033[0m" : "\033[31mпровален\033[0m") << std::endl;
   };

   test ("meta::get1stArg              ", get1stArg_);
   test ("meta::get1stType             ", get1stType_);
   // test ("Flash::change                ", change);
   // test ("Flash::ctor_after_change     ", ctor_after_change);
   // test ("Flash::end_of_sector         ", end_of_sector);
   // test ("Flash::off_when_erase        ", off_when_erase);
   // test ("Flash::new_data              ", new_data);
}