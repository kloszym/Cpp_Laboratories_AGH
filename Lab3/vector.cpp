#include <algorithm>
#include <stdexcept>
#include <utility> // std::swap()
#include "vector.h"

Vector::Vector(std::size_t capacity):
	capacity_(capacity)
{
	this -> size_ = 0;
	this ->  data_ = std::make_unique<Fraction[]>(capacity_);
}

Vector::Vector(const Vector& other){
	this -> size_ = other.size_;
	this -> capacity_ = other.capacity_;
	this -> data_ = std::make_unique<Fraction[]>(capacity_);
	for(std::size_t i = 0; i < this -> size_; i++) {
		this -> data_[i] = other.data_[i];
	}
}

 Vector::Vector(Vector&& other) noexcept {
	*this = std::move(other);
}


Vector& Vector::operator=(const Vector& other) {
	Vector tmp(other);
	std::swap(*this, tmp);
	return *this;
}

Vector& Vector::operator=(Vector&& other) noexcept{
	data_ = std::move(other.data_);
	size_ = other.size_;
	capacity_ = other.capacity_;

	other.size_ = 0;
	other.capacity_ = 0;

	return *this;
}

std::size_t Vector::size() const{
	return this -> size_;
}

std::size_t Vector::capacity() const{
	return this -> capacity_;
}

std::unique_ptr<Fraction[]> Vector::data(){
	return std::move(this->data_);
}

void Vector::push_back(const Fraction& frac) {
	if (size_ == capacity_) {
		capacity_ += 1;
		std::unique_ptr<Fraction[]> tmp = std::make_unique<Fraction[]>(capacity_);
		for(std::size_t i = 0; i < this -> size_; i++) {
			tmp[i] = this->data_[i];
		}
		data_ = std::move(tmp);
	}
	this -> data_[this -> size_] = frac;
	this -> size_++;
}

Fraction& Vector::operator[](std::size_t index) {
	if (index >= this -> size_) {
		throw std::out_of_range("Vector::operator[]");
	}
	return data_[index];
}
const Fraction& Vector::operator[](std::size_t index) const {
	if (index >= this -> size_) {
		throw std::out_of_range("Vector::operator[]");
	}
	return data_[index];
}