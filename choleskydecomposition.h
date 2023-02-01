#include <memory>
#include <Halide.h>


void CholeskyDecomposition(
	std::shared_ptr<Halide::Buffer<float>> pA,
	std::shared_ptr<Halide::Buffer<float>> pL,
	std::shared_ptr<Halide::Buffer<float>> pD) {
	int size = (*pA).height();
	Halide::Func f, zeros;
	Halide::Var i, j;

	zeros(i, j) = 0.f;
	f(i, j) = 0.f;
	for (int k = 0; k < size; k++) {
		for (int g = 0; g < k; g++) {
			f(k, k) = f(k, k) + f(k, g) * f(k, g) * f(g, g);
		}
		f(k, k) = (*pA)(k, k) - f(k, k);
		for (int r = k + 1; r < size; r++) {
			for (int g = 0; g < k; g++) {
				f(r, k) = f(r, k) + f(k, g) * f(r, g) * f(g, g);
			}
			f(r, k) = ((*pA)(r, k) - f(r, k)) / f(k, k);
		}
	}
	*pD = f.realize({ size, size });
	*pL = f.realize({ size, size });
	for (int i = 0; i < size; i++) {
		(*pD)(i, i) = (*pL)(i, i);
		(*pL)(i, i) = 1.f;
		for (int j = i + 1; j < size; j++) {
			(*pL)(j, i) = tmp(j, i);
		}
	}
}

