//
// Created by klosz on 15.05.2025.
//

#include "rectangle.h"

Shapes::Rectangle::Rectangle(int xFrom, int yFrom, int xTo, int yTo): xFrom_{xFrom}, yFrom_{yFrom}, xTo_{xTo}, yTo_{yTo}{}

bool Shapes::Rectangle::isIn(int x, int y) const{
	return (x>=this->xFrom_ && x<=this->xTo_ && y>=this->yFrom_ && y<=this->yTo_);
}

int Shapes::Rectangle::x() const{
	return this->xFrom_;
}
int Shapes::Rectangle::y() const{
  return this->yFrom_;
}
int Shapes::Rectangle::xTo() const{
  return this->xTo_;
}
int Shapes::Rectangle::yTo() const{
  return this->yTo_;
}