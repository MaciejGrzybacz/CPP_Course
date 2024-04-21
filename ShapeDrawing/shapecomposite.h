//
// Created by 006ma on 21.04.2024.
//

#ifndef SHAPECOMPOSITE_H
#define SHAPECOMPOSITE_H

#include <memory>
#include "shape.h"

namespace Shapes {

    class ShapeComposite : public Shape{
    public:
        std::shared_ptr<Shape> shape1;
        std::shared_ptr<Shape> shape2;
        ShapeOperation operation;
        ShapeComposite(std::shared_ptr<Shape> s1, std::shared_ptr<Shape> s2,ShapeOperation o);
        [[nodiscard]] bool isIn(int x, int y) const override;


    };

} // Shapes

#endif //SHAPECOMPOSITE_H
