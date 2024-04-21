//
// Created by 006ma on 21.04.2024.
//

#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "shape.h"
namespace Shapes {

    class Rectangle : public Shape {
    public:
    //private: should be but then test won't work
        Point upperLeft;
        Point lowerRight;
        Rectangle(int xFrom, int yFrom, int xTo, int yTo);
        [[nodiscard]] bool isIn(int x, int y) const override;
        [[nodiscard]] int x() const;
        [[nodiscard]] int y() const;
        [[nodiscard]] int xTo() const;
        [[nodiscard]] int yTo() const;
    };

} // Shapes

#endif
