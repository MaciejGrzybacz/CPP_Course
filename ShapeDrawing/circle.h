//
// Created by 006ma on 21.04.2024.
//

#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

namespace Shapes {

    class Circle : public Shape {
    public:
        //private: same thing as in rectangle.h
        Point center;
        int radius_;

        Circle(int xCenter, int yCenter, int radius);
        [[nodiscard]] bool isIn(int x, int y) const override;
        [[nodiscard]] int x() const;
        [[nodiscard]] int y() const;
        [[nodiscard]] int radius() const;
    };

} // Shapes


#endif //CIRCLE_H
