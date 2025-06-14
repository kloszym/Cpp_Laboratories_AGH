//
// Created by klosz on 17.05.2025.
//

#ifndef SHAPECOMPOSITE_H
#define SHAPECOMPOSITE_H

#include <memory>
#include "shape.h"
#include "shapeoperation.h"

namespace Shapes {

class ShapeComposite: public Shape{
  public:

    ShapeComposite(std::shared_ptr<Shape>, std::shared_ptr<Shape>, ShapeOperation);
    virtual bool isIn(int x, int y) const override;

  private:
    std::shared_ptr<Shapes::Shape> firstShape_;
    std::shared_ptr<Shapes::Shape> secondShape_;
    Shapes::ShapeOperation operation_;

};

}

#endif //SHAPECOMPOSITE_H
