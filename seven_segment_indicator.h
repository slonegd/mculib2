#pragma once

#include "pinlist.h"
#include "pins_variadic.h"

/// управление семимегментными индикаторами
/// A_...H_ - классы выводов сегментов, чтобы зажечь подать ноль 
/// Ks - классы выводов, управляющие катодами. для выбора подать 1
template<
   class A_, class B_, class C_, class D_, class E_, class F_, class G_, class H_,
   class ... Ks_
>
class SSI : private ItickSubscribed // seven-segment indicator 
{
public:
   static constexpr uint32_t indicatorQty = sizeof...(Ks_);
   uint8_t buffer [indicatorQty];
   bool    point  [indicatorQty];


   SSI (uint8_t refreshTime = 10_ms)
      : buffer      {0},
        refreshTime {refreshTime}
   {
      Pins<A_,B_,C_,D_,E_,F_,G_,H_,Ks_...>
         ::template configure<PinConf_t::Output>();
      tickUpdater.subscribe (this);
   }






private:
   uint8_t index {0};
   uint8_t tickCounter {0};
   const uint8_t refreshTime;
   using indicators = PinList<Ks_...>;
   using segments = PinList<H_,G_,F_,E_,D_,C_,B_,A_>;
   void tick() override;

};





static constexpr uint8_t symbols[] = {
   //ABCDEFGH
   0b00000011, // 0   ==A==
   0b10011111, // 1  ||   ||
   0b00100101, // 2  F|   |B
   0b00001101, // 3  ||   ||
   0b10011001, // 4   ==G==
   0b01001001, // 5  ||   ||
   0b01000001, // 6  E|   |C
   0b00011111, // 7  ||   ||
   0b00000001, // 8   ==D==  (H)
   0b00001001, // 9
   0b10010001, // 10 H
   0b11100011, // 11 L
   0b11111111, // 12 Space
   0b11111101  // 13 -
};






template<class A_, class B_, class C_, class D_, class E_, class F_, class G_, class H_,class ... Ks_>
void SSI<A_,B_,C_,D_,E_,F_,G_,H_,Ks_...>::tick()
{
   if (++tickCounter == refreshTime) {
      tickCounter = 0;
      indicators::Write(0);
      ++index;
      if (index == indicatorQty)
         index = 0;
      uint8_t symbol = symbols[buffer[index]];
      if (point[index])
         symbol &= ~1u;
      segments::Write(symbol);
      indicators::Write(1u << index);
   }
}