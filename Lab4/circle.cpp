//
// Created by klosz on 15.05.2025.
//

#include "circle.h"
#include <cmath>

Shapes::Circle::Circle(int xCenter, int yCenter, int radius): xCenter_{xCenter}, yCenter_{yCenter}, radius_{radius}{};

bool Shapes::Circle::isIn(int x, int y) const {
  return (sqrt(pow((x-xCenter_),2)+pow((y-yCenter_),2)) <= this->radius_);
}

int Shapes::Circle::x() const{
	return this->xCenter_;
}
int Shapes::Circle::y() const{
	return this->yCenter_;
}
int Shapes::Circle::radius() const{
	return this->radius_;
}