//
// Created by 006ma on 21.04.2024.
//

#include "shapecomposite.h"

namespace Shapes {
    ShapeComposite::ShapeComposite(std::shared_ptr<Shape> s1, std::shared_ptr<Shape> s2, ShapeOperation o) :
    shape1(s1),shape2(s2), operation(o) {}

    bool ShapeComposite::isIn(int x, int y) const {
        bool result;
        switch(operation) {
            case ShapeOperation::INTERSECTION:
                result = shape1->isIn(x, y) && shape2->isIn(x, y);
                break;
            case ShapeOperation::SUM:
                result = shape1->isIn(x, y) || shape2->isIn(x, y);
                break;
            case ShapeOperation::DIFFERENCE:
                result = shape1->isIn(x, y) && !shape2->isIn(x, y);
                break;
        }
        return result;
    }

} // Shapes