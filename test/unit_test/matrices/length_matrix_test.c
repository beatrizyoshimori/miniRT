#include "unit_test.h"

Test(matrices, test_length_matrix_0) {
	int				size = 0;
	double			**E = create_matrix(size);
	
	int				result = length_matrix(E);

	cr_assert(epsilon_eq(flt, size, result, EPSILON));
	free_matrix(&E);
}

Test(matrices, test_length_matrix_1) {
	int				size = 1;
	double			**E = create_matrix(size);
	
	int				result = length_matrix(E);

	cr_assert(epsilon_eq(flt, size, result, EPSILON));
	free_matrix(&E);
}

Test(matrices, test_length_matrix_2) {
	int				size = 2;
	double			**E = create_matrix(size);
	
	int				result = length_matrix(E);

	cr_assert(epsilon_eq(flt, size, result, EPSILON));
	free_matrix(&E);
}

Test(matrices, test_length_matrix_3) {
	int				size = 3;
	double			**E = create_matrix(size);
	
	int				result = length_matrix(E);

	cr_assert(epsilon_eq(flt, size, result, EPSILON));
	free_matrix(&E);
}

Test(matrices, test_length_matrix_4) {
	int				size = 4;
	double			**E = create_matrix(size);
	
	int				result = length_matrix(E);

	cr_assert(epsilon_eq(flt, size, result, EPSILON));
	free_matrix(&E);
}

Test(matrices, test_length_matrix_5) {
	int				size = 5;
	double			**E = create_matrix(size);
	
	int				result = length_matrix(E);

	cr_assert(epsilon_eq(flt, size, result, EPSILON));
	free_matrix(&E);
}
