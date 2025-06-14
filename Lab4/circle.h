//
// Created by klosz on 15.05.2025.
//

#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

namespace Shapes
{
class Circle : public Shapes::Shape{
  public:
    Circle(int, int, int);
    virtual bool isIn(int x, int y) const override;
	int x() const;
	int y() const;
	int radius() const;

   private:
     int xCenter_, yCenter_, radius_;
};
} //namespace Shapes
#endif //CIRCLE_H
