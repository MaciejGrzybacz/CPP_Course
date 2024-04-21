//
// Created by 006ma on 21.04.2024.
//

#include "circle.h"

namespace Shapes {
    Circle::Circle(int xCenter, int yCenter, int radius) :
            center(xCenter, yCenter), radius_(radius) {
    }

    bool Circle::isIn(int x, int y) const {
        return (x - center.x_) * (x - center.x_) + (y - center.y_) * (y - center.y_) <= radius_ * radius_;
    }

    int Circle::x() const {
        return center.x_;
    }

    int Circle::y() const {
        return center.y_;
    }

    int Circle::radius() const {
        return radius_;
    }
}