#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <Eigen>
#include "choleskydecomposition.h"

TEST_CASE("cholesky decomposition", "cholesky decomposition") {
	int size = 10;

	Eigen::MatrixXf TestMatrix(size, size);
	Eigen::MatrixXf L(size, size);
	Eigen::MatrixXf D(size, size);
	Eigen::MatrixXf LDLt(size, size);
	TestMatrix.setRandom();
	TestMatrix = TestMatrix.transpose() * TestMatrix; // make it symmetrical

	std::shared_ptr<Halide::Buffer<float>> pLBuffer(new Halide::Buffer<float>(size, size));
	std::shared_ptr<Halide::Buffer<float>> pDBuffer(new Halide::Buffer<float>(size, size));
	std::shared_ptr<Halide::Buffer<float>> pTestMatrixBuffer(new Halide::Buffer<float>(size, size));

	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			(*pTestMatrixBuffer)(row, col) = TestMatrix(row, col);
		}
	}

	CholeskyDecomposition(pTestMatrixBuffer, pLBuffer, pDBuffer);

	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			L(row, col) = (*pLBuffer)(row, col);
			D(row, col) = (*pDBuffer)(row, col);
		}
	}
	LDLt = L * D * L.transpose();
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			CHECK(std::abs(LDLt(row, col) - TestMatrix(row, col)) < 0.00001f );
		}
	}
}
