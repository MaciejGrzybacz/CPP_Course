//
// Created by 006ma on 21.04.2024.
//

#include "rectangle.h"

namespace Shapes {
    Rectangle::Rectangle(int xFrom, int yFrom, int xTo, int yTo):
        upperLeft(xFrom, yFrom), lowerRight(xTo, yTo) {
    }

    bool Rectangle::isIn(int x, int y) const {
        return upperLeft.x_ <= x && x <= lowerRight.x_ && upperLeft.y_ <= y && y <= lowerRight.y_;
    }

    int Rectangle::x() const {
        return upperLeft.x_;
    }

    int Rectangle::y() const {
        return upperLeft.y_;
    }

    int Rectangle::xTo() const {
        return lowerRight.x_;
    }

    int Rectangle::yTo() const {
        return lowerRight.y_;
    }
} // Shapes