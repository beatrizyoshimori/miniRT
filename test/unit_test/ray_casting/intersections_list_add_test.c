#include "unit_test.h"

Test(ray_casting, test_intersections_list_add_0) {
	t_intersections	*intersections = NULL;
	t_intersections	*new = new_intersection(SP, 2);

	intersections_list_add(&intersections, new);

	cr_assert(epsilon_eq(flt, SP, intersections->object, EPSILON));
	cr_assert(epsilon_eq(flt, 2, intersections->t, EPSILON));
	free_intersections(&intersections);
}

Test(ray_casting, test_intersections_list_add_1_0) {
	t_intersections	*intersections = NULL;
	t_intersections	*new = new_intersection(SP, 2);
	t_intersections	*new2 = new_intersection(SP, 5);

	intersections_list_add(&intersections, new);
	intersections_list_add(&intersections, new2);

	cr_assert(epsilon_eq(flt, SP, intersections->object, EPSILON));
	cr_assert(epsilon_eq(flt, 2, intersections->t, EPSILON));
	cr_assert(epsilon_eq(flt, SP, intersections->next->object, EPSILON));
	cr_assert(epsilon_eq(flt, 5, intersections->next->t, EPSILON));
	free_intersections(&intersections);
}

Test(ray_casting, test_intersections_list_add_1_1) {
	t_intersections	*intersections = NULL;
	t_intersections	*new = new_intersection(SP, 5);
	t_intersections	*new2 = new_intersection(SP, 2);

	intersections_list_add(&intersections, new);
	intersections_list_add(&intersections, new2);

	cr_assert(epsilon_eq(flt, SP, intersections->object, EPSILON));
	cr_assert(epsilon_eq(flt, 2, intersections->t, EPSILON));
	cr_assert(epsilon_eq(flt, SP, intersections->next->object, EPSILON));
	cr_assert(epsilon_eq(flt, 5, intersections->next->t, EPSILON));
	free_intersections(&intersections);
}

Test(ray_casting, test_intersections_list_add_2) {
	t_intersections	*intersections = NULL;
	t_intersections	*new = new_intersection(SP, 2);
	t_intersections	*new2 = new_intersection(SP, 5);
	t_intersections	*new3 = new_intersection(SP, 3);

	intersections_list_add(&intersections, new);
	intersections_list_add(&intersections, new2);
	intersections_list_add(&intersections, new3);

	cr_assert(epsilon_eq(flt, SP, intersections->object, EPSILON));
	cr_assert(epsilon_eq(flt, 2, intersections->t, EPSILON));
	cr_assert(epsilon_eq(flt, SP, intersections->next->object, EPSILON));
	cr_assert(epsilon_eq(flt, 3, intersections->next->t, EPSILON));
	cr_assert(epsilon_eq(flt, SP, intersections->next->next->object, EPSILON));
	cr_assert(epsilon_eq(flt, 5, intersections->next->next->t, EPSILON));
	free_intersections(&intersections);
}

Test(ray_casting, test_intersections_list_add_3) {
	t_intersections	*intersections = NULL;
	t_intersections	*new = new_intersection(SP, 2);
	t_intersections	*new2 = new_intersection(SP, 3);
	t_intersections	*new3 = new_intersection(SP, 5);

	intersections_list_add(&intersections, new);
	intersections_list_add(&intersections, new2);
	intersections_list_add(&intersections, new3);

	cr_assert(epsilon_eq(flt, SP, intersections->object, EPSILON));
	cr_assert(epsilon_eq(flt, 2, intersections->t, EPSILON));
	cr_assert(epsilon_eq(flt, SP, intersections->next->object, EPSILON));
	cr_assert(epsilon_eq(flt, 3, intersections->next->t, EPSILON));
	cr_assert(epsilon_eq(flt, SP, intersections->next->next->object, EPSILON));
	cr_assert(epsilon_eq(flt, 5, intersections->next->next->t, EPSILON));
	free_intersections(&intersections);
}

Test(ray_casting, test_intersections_list_add_4) {
	t_intersections	*intersections = NULL;
	t_intersections	*new = new_intersection(SP, 5);
	t_intersections	*new2 = new_intersection(SP, -6.96);
	t_intersections	*new3 = new_intersection(SP, 2);
	t_intersections	*new4 = new_intersection(SP, 0);
	t_intersections	*new5 = new_intersection(SP, -10);

	intersections_list_add(&intersections, new);
	intersections_list_add(&intersections, new2);
	intersections_list_add(&intersections, new3);
	intersections_list_add(&intersections, new4);
	intersections_list_add(&intersections, new5);

	cr_assert(epsilon_eq(flt, SP, intersections->object, EPSILON));
	cr_assert(epsilon_eq(flt, -10, intersections->t, EPSILON));
	cr_assert(epsilon_eq(flt, SP, intersections->next->object, EPSILON));
	cr_assert(epsilon_eq(flt, -6.96, intersections->next->t, EPSILON));
	cr_assert(epsilon_eq(flt, SP, intersections->next->next->object, EPSILON));
	cr_assert(epsilon_eq(flt, 0, intersections->next->next->t, EPSILON));
	cr_assert(epsilon_eq(flt, SP, intersections->next->next->next->object, EPSILON));
	cr_assert(epsilon_eq(flt, 2, intersections->next->next->next->t, EPSILON));
	cr_assert(epsilon_eq(flt, SP, intersections->next->next->next->next->object, EPSILON));
	cr_assert(epsilon_eq(flt, 5, intersections->next->next->next->next->t, EPSILON));
	free_intersections(&intersections);
}
