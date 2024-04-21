#include <cmath> /// sin(), floor()
#include <gtest/gtest.h>

#if __has_include("../shape.h")
    #include "../shape.h"
#elif __has_include("shape.h")
    #include "shape.h"
#else
    #error "File 'shape.h' not found!"
#endif

#if __has_include("../rectangle.h")
    #include "../rectangle.h"
    #define RECTANGLE_H_EXISTS
#elif __has_include("rectangle.h")
    #include "rectangle.h"
    #define RECTANGLE_H_EXISTS
#endif

#if __has_include("../circle.h")
    #include "../circle.h"
    #define CIRCLE_H_EXISTS
#elif __has_include("circle.h")
    #include "circle.h"
    #define CIRCLE_H_EXISTS
#endif

#if __has_include("../shapecomposite.h")
    #include "../shapecomposite.h"
    #define SHAPECOMPOSITE_H_EXISTS
#elif __has_include("shapecomposite.h")
    #include "shapecomposite.h"
    #define SHAPECOMPOSITE_H_EXISTS
#endif

#if __has_include("../stage.h")
    #include "../stage.h"
    #define STAGE_H_EXISTS
#elif __has_include("stage.h")
    #include "stage.h"
    #define STAGE_H_EXISTS
#endif


namespace
{
using namespace std;
using namespace ::testing;

using Shapes::Shape;

#ifndef M_PI
    constexpr double M_PI = 3.1415926;
#endif

void printShape(const Shapes::Shape* shape, size_t width, size_t heigh)
{
    #ifdef STAGE_H_EXISTS
        const Stage stage(width, heigh);
        stage.drawShape2Stream(shape, std::cout);
    #else
        static_cast<void>(shape); // to disable warnings
        static_cast<void>(width);
        static_cast<void>(heigh);
    #endif
}

class RectangleTester : public ::testing::Test
{};

class CircleTester : public ::testing::Test
{};

class ShapeCompositeTester : public ::testing::Test
{};
} // namespace


TEST_F(RectangleTester, constructorOfRectangleStartingInBeginningOfSystemCoordinate)
{
#ifdef RECTANGLE_H_EXISTS
    constexpr int xFrom = 0, yFrom = 0, xTo = 10, yTo = 10;
    const Shapes::Rectangle rectangle(xFrom, yFrom, xTo, yTo);

    ASSERT_EQ(xFrom, rectangle.x());
    ASSERT_EQ(yFrom, rectangle.y());
    ASSERT_EQ(xTo, rectangle.xTo());
    ASSERT_EQ(yTo, rectangle.yTo());
#else
    ADD_FAILURE() << "Rectangle not implemented!";
#endif
}

TEST_F(RectangleTester, isInMethodOfRectangleStartingInBeginningOfCoordinateSystem)
{
#ifdef RECTANGLE_H_EXISTS
    constexpr int xFrom = 0, xTo = 10;
    constexpr int yFrom = 0, yTo = 10;
    const Shapes::Rectangle rectangle(xFrom, yFrom, xTo, yTo);

    ASSERT_TRUE(rectangle.isIn(5, 7));
    ASSERT_TRUE(rectangle.isIn(0, 0));
    ASSERT_TRUE(rectangle.isIn(10, 10));

    ASSERT_FALSE(rectangle.isIn(5, 11));
    ASSERT_FALSE(rectangle.isIn(50, 1));
    ASSERT_FALSE(rectangle.isIn(-1, 13));
#else
    ADD_FAILURE() << "Rectangle not implemented!";
#endif
}

TEST_F(RectangleTester, isInMethodOfRectangleStartingNotInBeginningOfCoordinateSystem)
{
#ifdef RECTANGLE_H_EXISTS
    constexpr int xFrom = 5,  xTo = 15;
    constexpr int yFrom = 10, yTo = 20;
    const Shapes::Rectangle rectangle(xFrom, yFrom, xTo, yTo);

    ASSERT_TRUE(rectangle.isIn(7, 17));
    ASSERT_TRUE(rectangle.isIn(5, 10));
    ASSERT_TRUE(rectangle.isIn(10, 20));

    ASSERT_FALSE(rectangle.isIn(6, 9));
    ASSERT_FALSE(rectangle.isIn(14, 21));
    ASSERT_FALSE(rectangle.isIn(-5, -20));
#else
    ADD_FAILURE() << "Rectangle not implemented!";
#endif
}

TEST_F(RectangleTester, constructorOfRectangleWithBothSitesEqualToZero)
{
#ifdef RECTANGLE_H_EXISTS
    constexpr int x = 5;
    constexpr int y = 10;
    const Shapes::Rectangle rectangle(x, y, x, y);

    ASSERT_TRUE(rectangle.isIn(x, y));
    ASSERT_FALSE(rectangle.isIn(x + 1, y));
    ASSERT_FALSE(rectangle.isIn(x,      y + 1));
#else
    ADD_FAILURE() << "Rectangle not implemented!";
#endif
}

TEST_F(CircleTester, constructorOfCircleStartingInBeginningOfCoordinateSystem)
{
    /**
     y
    10: ****
     9: ******
     8: *******
     7: ********
     6: *********
     5: **********
     4: **********
     3: ***********
     2: ***********
     1: ***********
     0: ***********
     0: 01234567890 x
     **/
#ifdef CIRCLE_H_EXISTS
    constexpr int xCenter = 0, yCenter = 0, radius = 10;
    const Shapes::Circle circle(xCenter, yCenter, radius);
    printShape(&circle, radius+1, radius+1);

    ASSERT_EQ(xCenter, circle.x());
    ASSERT_EQ(yCenter, circle.y());
    ASSERT_EQ(radius,  circle.radius());
#else
    ADD_FAILURE() << "Circle not implemented!";
#endif
}

TEST_F(CircleTester, isInMethodOfCircleStartingInBeginningOfCoordinateSystem)
{
    /** circle:
     y
    10: ****
     9: ******
     8: *******
     7: ********
     6: *********
     5: **********
     4: **********
     3: ***********
     2: ***********
     1: ***********
     0: ***********
      : 01234567890 x **/
#ifdef CIRCLE_H_EXISTS
    constexpr int xCenter = 0, yCenter = 0, radius = 10;
    const Shapes::Circle circle(xCenter, yCenter, radius);
    printShape(&circle, radius, radius);

    ASSERT_TRUE(circle.isIn(5, 7));
    ASSERT_TRUE(circle.isIn(0, 0));

    constexpr auto angleInDegree = 45;
    constexpr auto angleInRadians = angleInDegree * M_PI / 180;
    const auto xyValueWhenHypothenuseEqualsRadius = floor(sin(angleInRadians) * radius);
    ASSERT_TRUE(circle.isIn(xyValueWhenHypothenuseEqualsRadius, xyValueWhenHypothenuseEqualsRadius));

    ASSERT_FALSE(circle.isIn(5,  11));
    ASSERT_FALSE(circle.isIn(11, 1));
    ASSERT_FALSE(circle.isIn(xyValueWhenHypothenuseEqualsRadius+1, xyValueWhenHypothenuseEqualsRadius+1));
#else
    ADD_FAILURE() << "Circle not implemented!";
#endif
}

TEST_F(CircleTester, isInMethodOfCircleStartingNotInBeginningOfCoordinateSystem)
{
    /** circle:
      y
     12:     *****
     11:    *******
     10:   *********
      9:  ***********
      8:  ***********
      7:  ***********
      6:  ***********
      5:  ***********
      4:   *********
      3:    *******
      2:     *****
       : 012345678901 x */
#ifdef CIRCLE_H_EXISTS
    constexpr int xCenter = 6, yCenter = 7, radius = 5;
    const Shapes::Circle circle(xCenter, yCenter, radius);
    printShape(&circle, xCenter+radius, yCenter+radius);

    ASSERT_TRUE(circle.isIn(xCenter, 7));
    ASSERT_TRUE(circle.isIn(xCenter, yCenter+radius));
    ASSERT_TRUE(circle.isIn(xCenter+radius, yCenter));

    ASSERT_FALSE(circle.isIn(xCenter-radius,  yCenter-radius));
    ASSERT_FALSE(circle.isIn(xCenter+radius,  yCenter+radius));
#else
    ADD_FAILURE() << "Circle not implemented!";
#endif
}

TEST_F(CircleTester, constructorOfCircleWithRadiusEqualToZero)
{
#ifdef CIRCLE_H_EXISTS
    constexpr int x = 6, y = 7, radius = 0;
    const Shapes::Circle circle(x, y, radius);
    printShape(&circle, x+radius, y+radius);

    ASSERT_TRUE(circle.isIn(x, y));
    ASSERT_FALSE(circle.isIn(x,   y+1));
    ASSERT_FALSE(circle.isIn(x+1, y));
#else
    ADD_FAILURE() << "Circle not implemented!";
#endif
}


TEST_F(ShapeCompositeTester, sumOfSqhareAndCircle)
{
#if defined(SHAPECOMPOSITE_H_EXISTS) && defined(CIRCLE_H_EXISTS) && defined(RECTANGLE_H_EXISTS)
    constexpr int xFrom = 2, xTo = 8;
    constexpr int yFrom = 0, yTo = 6;
    shared_ptr<Shape> rectangle(new Shapes::Rectangle(xFrom, yFrom, xTo, yTo));
    printShape(rectangle.get(), xTo, yTo);
    /** (rectangle)
     y
     6:   *******
     5:   *******
     4:   *******
     3:   *******
     2:   *******
     1:   *******
     0:   *******
      : 012345678 x
     */

    constexpr auto squareXCenter = xFrom+(xTo-xFrom)/2, yCenter = yTo, radius = (xTo-xFrom)/2;
    shared_ptr<Shape> circle(new Shapes::Circle(squareXCenter, yCenter, radius));
    printShape(circle.get(), xTo, yTo+radius);
    /** circle:
     y
     9:     ***
     8:    *****
     7:   *******
     6:   *******
     5:   *******
     4:    *****
     3:     ***
     2:
     1:
     0:
      : 012345678
     */


    const Shapes::ShapeComposite composite(rectangle, circle, Shapes::ShapeOperation::SUM);
    printShape(&composite, xTo, yTo+radius);
    /** circle + square:
     y
     9:     ***
     8:    *****
     7:   *******
     6:   *******
     5:   *******
     4:   *******
     3:   *******
     2:   *******
     1:   *******
     0:   *******
      : 012345678 x **/
    ASSERT_TRUE(composite.isIn(7, 6));
    ASSERT_TRUE(composite.isIn(squareXCenter, yTo+radius));
#else
    ADD_FAILURE() << "Required classes not implemented not implemented!";
#endif
}

TEST_F(ShapeCompositeTester, intersectionOfSqhareAndCircle)
{
#if defined(SHAPECOMPOSITE_H_EXISTS) && defined(CIRCLE_H_EXISTS) && defined(RECTANGLE_H_EXISTS)
    constexpr int xFrom = 2, xTo = 8;
    constexpr int yFrom = 0, yTo = 6;
    shared_ptr<Shape> rectangle(new Shapes::Rectangle(xFrom, yFrom, xTo, yTo));
    printShape(rectangle.get(), xTo, yTo);
    /** (rectangle)
     y
     6:   *******
     5:   *******
     4:   *******
     3:   *******
     2:   *******
     1:   *******
     0:   *******
      : 012345678 x
     */

    constexpr auto squareXCenter = xFrom+(xTo-xFrom)/2, yCenter = yTo, radius = (xTo-xFrom)/2;
    shared_ptr<Shape> circle(new Shapes::Circle(squareXCenter, yCenter, radius));
    printShape(circle.get(), xTo, yTo+radius);
    /** circle:
     y
     9:     ***
     8:    *****
     7:   *******
     6:   *******
     5:   *******
     4:    *****
     3:     ***
     2:
     1:
     0:
      : 012345678
     */

    const Shapes::ShapeComposite composite(rectangle, circle, Shapes::ShapeOperation::INTERSECTION);
    printShape(&composite, xTo, yTo+radius);
    /** circle + square:
     y
     7:
     6:   *******
     5:   *******
     4:    *****
     3:     ***
     2:
     1:
     0:
      : 012345678 x **/
    ASSERT_TRUE(composite.isIn(xFrom, yTo));
    ASSERT_FALSE(composite.isIn(xFrom, yFrom));
#else
    ADD_FAILURE() << "Required classes not implemented not implemented!";
#endif
}

TEST_F(ShapeCompositeTester, differenceOfSqhareAndCircle)
{
#if defined(SHAPECOMPOSITE_H_EXISTS) && defined(CIRCLE_H_EXISTS) && defined(RECTANGLE_H_EXISTS)
    constexpr int xFrom = 2, xTo = 8;
    constexpr int yFrom = 0, yTo = 6;
    shared_ptr<Shape> rectangle(new Shapes::Rectangle(xFrom, yFrom, xTo, yTo));
    printShape(rectangle.get(), xTo, yTo);
    /** (rectangle)
     y
     6:   *******
     5:   *******
     4:   *******
     3:   *******
     2:   *******
     1:   *******
     0:   *******
      : 012345678 x
     */

    constexpr auto squareXCenter = xFrom+(xTo-xFrom)/2, yCenter = yTo, radius = (xTo-xFrom)/2;
    shared_ptr<Shape> circle(new Shapes::Circle(squareXCenter, yCenter, radius));
    printShape(circle.get(), xTo, yTo+radius);
    /** circle:
     y
     9:     ***
     8:    *****
     7:   *******
     6:   *******
     5:   *******
     4:    *****
     3:     ***
     2:
     1:
     0:
      : 012345678
     */

    const Shapes::ShapeComposite composite(rectangle, circle, Shapes::ShapeOperation::DIFFERENCE);
    printShape(&composite, xTo, yTo+radius);
    /** circle + square:
     y
     5:
     4:   *     *
     3:   **   **
     2:   *******
     1:   *******
     0:   *******
      : 012345678 x **/
    ASSERT_FALSE(composite.isIn(xFrom, yTo));
    ASSERT_TRUE(composite.isIn(xFrom, yFrom));
#else
    ADD_FAILURE() << "Required classes not implemented not implemented!";
#endif
}

TEST_F(ShapeCompositeTester, drawingHouse)
{
#if defined(SHAPECOMPOSITE_H_EXISTS) && defined(CIRCLE_H_EXISTS) && defined(RECTANGLE_H_EXISTS)
    constexpr int homeWidth = 20, homeHeigh = 10;
    constexpr int homeXFrom = 4, homeXTo = homeXFrom+homeWidth, homeYFrom = 1, homeYTo = homeYFrom + homeHeigh;
    shared_ptr<Shape> home(new Shapes::Rectangle(homeXFrom, homeYFrom, homeXTo, homeYTo));

    constexpr int homeXCenter = homeXFrom + homeWidth/2, roofHeigh = homeWidth/2;
    shared_ptr<Shape> roof(new Shapes::Circle(homeXCenter, homeYTo, roofHeigh));

    shared_ptr<Shape> homeWithRoof(new Shapes::ShapeComposite(home, roof, Shapes::ShapeOperation::SUM));

    constexpr int doorXFrom = homeXFrom + homeWidth/6, doorXTo = doorXFrom + homeWidth/4;
    constexpr int doorYFrom = homeYFrom + 1, doorYTo = doorYFrom + homeHeigh/2 + homeHeigh/3 + homeHeigh/4;
    shared_ptr<Shape> door(new Shapes::Rectangle(doorXFrom, doorYFrom, doorXTo, doorYTo));

    shared_ptr<Shape> homeWithDoor(new Shapes::ShapeComposite(homeWithRoof, door, Shapes::ShapeOperation::DIFFERENCE));

    constexpr int doorWidth = doorXTo - doorXFrom, doorHeigh = doorYTo - doorYFrom;
    constexpr int windowXFrom = homeXTo - homeWidth/2 + doorWidth/2;
    constexpr int windowXTo = windowXFrom + doorWidth;
    constexpr int windowYFrom = doorYFrom + doorHeigh/2;
    constexpr int windowYTo = doorYTo;
    shared_ptr<Shape> window(new Shapes::Rectangle(windowXFrom, windowYFrom, windowXTo, windowYTo));
    shared_ptr<Shape> homeWithDoorAndWindow(new Shapes::ShapeComposite(homeWithDoor, window, Shapes::ShapeOperation::DIFFERENCE));
    printShape(homeWithDoorAndWindow.get(), homeXTo, homeYTo+roofHeigh);
    /** entire home:
     y
     21:            *******
     20:          ***********
     19:         *************
     18:        ***************
     17:       *****************
     16:      *******************
     15:      *******************
     14:     *********************
     13:     *********************
     12:     ***      ***      ***
     11:     ***      ***      ***
     10:     ***      ***      ***
      9:     ***      ***      ***
      8:     ***      ***      ***
      7:     ***      ***      ***
      6:     ***      ************
      5:     ***      ************
      4:     ***      ************
      3:     ***      ************
      2:     ***      ************
      1:     *********************
      0:
       : 0123456789012345678901234 x **/

    ASSERT_FALSE(homeWithDoorAndWindow->isIn(doorXFrom, doorYFrom));
    ASSERT_FALSE(homeWithDoorAndWindow->isIn(doorXTo, doorYTo));
    ASSERT_FALSE(homeWithDoorAndWindow->isIn(windowXFrom, windowYFrom));
    ASSERT_FALSE(homeWithDoorAndWindow->isIn(windowXTo, windowYTo));

    ASSERT_TRUE(homeWithDoorAndWindow->isIn(homeXFrom, homeYFrom));
    ASSERT_TRUE(homeWithDoorAndWindow->isIn(homeXTo, homeYTo));
#else
    ADD_FAILURE() << "Required classes not implemented not implemented!";
#endif
}
