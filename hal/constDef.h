#pragma once

template<class T> struct ConstDef {
    T val;
    bool defined;
};
template<class T, class U> struct Const2Def {
    T val1;
    U val2;
    bool defined;
};