#include <iostream>
#include <string>
#include <stdexcept> // std::out_of_range()
#include <iomanip>   // std::setw()

using namespace std;

#include "matrix.h"

///1.

TwoDimensionMatrix::TwoDimensionMatrix() {
	for (int i = 0; i < static_cast<int>(size_); i++) {
		for (int j = 0; j < static_cast<int>(size_); j++) {
			matrix_[i][j] = 0;
		}
	}
}

TwoDimensionMatrix::TwoDimensionMatrix(const TwoDimensionMatrix &matrix) {
	for (int i = 0; i < static_cast<int>(size_); i++) {
		for (int j = 0; j < static_cast<int>(size_); j++) {
			matrix_[i][j] = matrix.matrix_[i][j];
		}
	}
}

TwoDimensionMatrix::TwoDimensionMatrix(const MatrixElement matrix[size_][size_]) {
	for (int i = 0; i < static_cast<int>(size_); i++) {
		for (int j = 0; j < static_cast<int>(size_); j++) {
			matrix_[i][j] = matrix[i][j];
		}
	}
}

///2.

TwoDimensionMatrix TwoDimensionMatrix::operator=(const TwoDimensionMatrix &other) {
	this->matrix_[0][0] = other.matrix_[0][0];
	this->matrix_[0][1] = other.matrix_[0][1];
	this->matrix_[1][0] = other.matrix_[1][0];
	this->matrix_[1][1] = other.matrix_[1][1];
	return *this;
}


TwoDimensionMatrix operator+(const TwoDimensionMatrix& matrix1, const TwoDimensionMatrix& matrix2) {
	MatrixElement matrix[matrix1.size()][matrix1.size()];
	for (int i = 0; i < static_cast<int>(matrix1.size()); i++) {
		for (int j = 0; j < static_cast<int>(matrix1.size()); j++) {
			matrix[i][j] = matrix1.get(i,j) + matrix2.get(i,j);
		}
	}
	return TwoDimensionMatrix(matrix);
}

TwoDimensionMatrix& TwoDimensionMatrix::operator*=(MatrixElement number) {

	this->matrix_[0][0] *= number;
	this->matrix_[0][1] *= number;
	this->matrix_[1][0] *= number;
	this->matrix_[1][1] *= number;
	return *this;

}

TwoDimensionMatrix TwoDimensionMatrix::operator&&(const TwoDimensionMatrix& matrix) const {

	MatrixElement res[matrix.size()][matrix.size()];
	for (int i = 0; i < static_cast<int>(matrix.size()); i++) {
		for (int j = 0; j < static_cast<int>(matrix.size()); j++) {
			res[i][j] = this->get(i,j) && matrix.get(i,j);
		}
	}
	return TwoDimensionMatrix(res);

}

MatrixElement* TwoDimensionMatrix::operator[](int num) {
	return this -> matrix_[num];

}

const MatrixElement *TwoDimensionMatrix::operator[](int num) const {
	return this -> matrix_[num];
}

TwoDimensionMatrix::operator size_t() const {
	return this->size();
}

//#warning "Klasa jest do zaimplementowania. Instrukcja w pliku naglowkowym, po zaimplementowaniu sugeruje usunac te linijke - po co komu warning?!"

