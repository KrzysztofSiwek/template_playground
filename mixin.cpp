#include <vector>
#include <iostream>
#include <string>

template<typename... Mixins>
struct PointMixin: public Mixins...{
    double x, y;
    PointMixin(): Mixins()..., x(0.0), y(0.0){};
    PointMixin(const double x, const double y): Mixins()..., x(x), y(y){};
};

struct Label{
    std::string label;
};

struct Colour{
    uint8_t red = 0, green = 0, blue = 0;
};

using MyPoint = PointMixin<Label, Colour>;

template<typename... Mixins>
struct Polygon{
    std::vector<PointMixin<Mixins...>> points;
};

template<template<typename> class... Mixins>
struct CrtpPointMixin: public Mixins<CrtpPointMixin<>>...{
    double x, y;
    CrtpPointMixin(): Mixins<CrtpPointMixin>()..., x(0.0), y(0.0){};
    CrtpPointMixin(const double x, const double y): Mixins<CrtpPointMixin>()..., x(x), y(y){};
};

int main(){
    Polygon<MyPoint> a;
}
