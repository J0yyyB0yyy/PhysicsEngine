#ifndef SHAPE_H
#define SHAPE_H

enum class ShapeType{
    Circle, Rectangle
};
class Shape{
public:
    virtual ShapeType getType() const = 0;
    virtual ~Shape() = default;
};

#endif