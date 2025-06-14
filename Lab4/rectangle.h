//
// Created by klosz on 15.05.2025.
//

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

namespace Shapes
{
class Rectangle: public Shapes::Shape{
 	public:

        Rectangle(int, int, int, int);
		virtual bool isIn(int x, int y) const override;
		int x() const;
        int y() const;
        int xTo() const;
        int yTo() const;


  	private:

          int xFrom_, yFrom_, xTo_, yTo_;

};
} //namespace Shapes
#endif //RECTANGLE_H
