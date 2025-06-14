//
// Created by klosz on 17.05.2025.
//

#include "shapecomposite.h"

Shapes::ShapeComposite::ShapeComposite(std::shared_ptr<Shapes::Shape> firstShape, std::shared_ptr<Shapes::Shape> secondShape, Shapes::ShapeOperation operation):
 	firstShape_{firstShape},
 	secondShape_{secondShape},
 	operation_{operation}{}

bool Shapes::ShapeComposite::isIn(int x, int y) const {
	switch (this->operation_) {
		case Shapes::ShapeOperation::SUM: {
			return firstShape_->isIn(x, y) || secondShape_->isIn(x, y);
		}
		case Shapes::ShapeOperation::INTERSECTION: {
			return firstShape_->isIn(x, y) && secondShape_->isIn(x, y);
		}
		case Shapes::ShapeOperation::DIFFERENCE: {
			return firstShape_->isIn(x, y) && !secondShape_->isIn(x, y);
		}
		default: return false;
	}
}
