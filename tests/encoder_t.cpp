#define STM32F030x6

#include "RCC.h"
#include "encoder_.h"
#include <iostream>
#include <type_traits>
#include <thread>

template <int n>
struct MockPin
{
   static bool set_;
   using Mode = GPIO_ral::Mode_t;
   using OutType = GPIO_ral::OutType_t;
   using OutSpeed = GPIO_ral::OutSpeed_t;
   using PullResistor = GPIO_ral::PullResistor_t;
   using AF = GPIO_ral::AF;

   inline static void configure (Mode mode,
                           OutType type,
                           OutSpeed speed,
                           PullResistor res){}
   template<PinConf_t pinConf>
   static void configure() {}
   template<int f>
   static void configureAltFunction(){ }
   template <AF func> static void SetAltFunc(){}

   static void set()          {set_ = true;}
   static void clear()        {set_ = false;}
   static void set(bool b)    {}
   static bool isSet()        {return set_;}
   static bool isClear()      {return not set_;}
};

int16_t count {0};  // register CNT
int16_t valueCompare{0}; // register CCR
int IRQn_{0};
bool interrupt_{false};
bool clockEnable_{false};
bool counterEnable_{false};

struct MockTIM
{
   enum Polarity {rising, falling, both};
   enum SelectionCompareMode { Output = 0b00, Input, InputALT, InputTRC }; 
   enum SlaveMode { SMDisabled = 0b000, Encoder1, Encoder2, Encoder3, Reset, Gated, TriggerMode, ExternalClock };
   static constexpr int IRQn () {return IRQn_ = 14;}
   static int16_t getCounter () {return count;}
   static void clockEnable   () {clockEnable_ = true;}
   static void clearCounter  () {count = 0;}
   static void counterEnable () {counterEnable_ = true;}
   static void setCounter(int16_t v) {count = v;}
   static void setCompare(int16_t v) {valueCompare = v;}
   static void compareInterruptEnable () {interrupt_ = true;}
   static void compareInterruptDisable() {interrupt_ = false;}
   template <Polarity v, int channel> static void set() {}
   template <SlaveMode v> static void set() {}
   template <SelectionCompareMode v, int channel> static void selectCompareMode() {}
   template <class MockPin> static constexpr int channel();
   template <class MockPin> static constexpr int AltFunc() {return 2;}
};


using PinA = MockPin<1>;
using PinB = MockPin<2>;

bool subs {false};
template <>
struct Interrupt <MockTIM>
{
   static void subscribe (Interrupting *p){subs = true;}
};

Encoder <MockTIM, PinA, PinB, false> encoder;

bool subscribe()
{
   struct MockClass : Interrupting
   {
      void interrupt() override{};
   } mockClass;

   encoder.subscribe(&mockClass);
   return subs;
}

bool enableInterrupt()
{
   encoder.enableInterrupt();
   return interrupt_;
}

bool disableInterrupt()
{
   encoder.disableInterrupt();
   return not (interrupt_);
}

bool compare()
{
   encoder.compare(0xFFF);
   return valueCompare == 0xFFF;
}

bool operatorEqually()
{
   bool good{true};
   int16_t var = 101; 
   encoder = var;
   good &= (count == var);
   var = 0xFFC;
   encoder = var;
   good &= (count == var);
   var = -101;
   encoder = var;
   good &= (count == var);
   count = 0;
   return good;
}

bool operatorPlus()
{
   bool good{true};
   int16_t var = 101;
   auto sum = encoder + var;
   good &= (sum == var);
   var = 0xFFC;
   sum = encoder + var;
   good &= (sum == var);
   var = -101;
   sum = encoder + var;
   good &= (sum == var);
   return good;
}

bool operatorMinus()
{
   count = 0xFFF;
   bool good{true};
   int16_t var = 101;
   auto dif = encoder - var;
   good &= (dif == 0xFFF-var);
   var = 0xFFC; 
   dif = encoder - var;
   good &= (dif == 0xFFF-var);
   var = -101; 
   dif = encoder - var;
   good &= (dif == 0xFFF-var);
   return good;
}

bool operatorMore()
{
   bool good{true};
   count = 0xFFF;
   int16_t var = 101;
   good &= (encoder > var);
   var = 0xFFC;
   good &= (encoder > var);
   var = -101;
   good &= (encoder > var);
   return good;
}

bool operatorLess()
{
   bool good{true};
   count = 50;
   int16_t var = 101;
   good &= (encoder < var);
   var = 0xFFC;
   good &= (encoder < var);
   count = -50;
   var = -40;
   good &= (encoder < var);
   var = 100;
   good &= (encoder < var);
   return good;
}

bool operatorMoreEqually()
{
   bool good{true};
   count = 0xFFF;
   int16_t var = 101;
   good &= (encoder >= var);
   var = 0xFFF;
   good &= (encoder >= var);
   var = -100;
   good &= (encoder >= var);
   count = -50;
   good &= (encoder >= var);
   return good;
   // return (encoder >= int16_t(49) and encoder >= int16_t(50));
}

bool operatorLessEqually()
{
   bool good{true};
   count = -50;
   int16_t var = -50;
   good &= (encoder <= var);
   var = 100;
   good &= (encoder <= var);
   var = 1;
   good &= (encoder <= var);
   return good;
}

bool operatorCoercion()
{
   bool good {true};
   count = 101;
   int16_t var = encoder;
   good &= (var == 101);
   count = -101;
   var = encoder;
   good &= (var == -101);
   return good;
}

int main ()
{
   std::cout << '\n'
             << "Тесты класса Encoder для STM32:" << std::endl;

   auto test = [](auto s, auto f){
      std::cout << s << (f() ? "\033[32mпрошёл\033[0m" : "\033[31mпровален\033[0m") << std::endl;
   };

   test ("subscribe           ", subscribe);
   test ("enableInterrupt     ", enableInterrupt);
   test ("disableInterrupt    ", disableInterrupt);
   test ("compare             ", compare);
   test ("operatorEqually     ", operatorEqually);
   test ("operatorPlus        ", operatorPlus);
   test ("operatorMinus       ", operatorMinus);
   test ("operatorMore        ", operatorMore);
   test ("operatorLess        ", operatorLess);
   test ("operatorLessEqually ", operatorLessEqually);
   test ("operatorMoreEqually ", operatorMoreEqually);
   test ("operatorCoercion    ", operatorCoercion);
   std::cout << std::endl;
}

   template <class MockPin>
   constexpr int MockTIM::channel()
   {
      if      constexpr (std::is_same_v<MockPin,PinA>)  return 1;
      else if constexpr (std::is_same_v<MockPin,PinB>)  return 2;
   }