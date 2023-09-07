#include "unit_test.h"

Test(ray_casting, test_get_hit_0) {
	t_intersections	*intersections = NULL;
	t_intersections	*new = new_intersection(SP, 2);
	t_intersections	*new2 = new_intersection(SP, -2);

	intersections_list_add(&intersections, new);
	intersections_list_add(&intersections, new2);

	t_intersections	*result = get_hit(intersections);

	cr_assert(epsilon_eq(flt, 2, result->t, EPSILON));
	free_intersections(&intersections);
}

Test(ray_casting, test_get_hit_1) {
	t_intersections	*intersections = NULL;
	t_intersections	*new = new_intersection(SP, 2);
	t_intersections	*new2 = new_intersection(SP, -2);
	t_intersections	*new3 = new_intersection(SP, -52);
	t_intersections	*new4 = new_intersection(SP, 36);
	t_intersections	*new5 = new_intersection(SP, 0.95);
	t_intersections	*new6 = new_intersection(SP, -9);
	t_intersections	*new7 = new_intersection(SP, 3);

	intersections_list_add(&intersections, new);
	intersections_list_add(&intersections, new2);
	intersections_list_add(&intersections, new3);
	intersections_list_add(&intersections, new4);
	intersections_list_add(&intersections, new5);
	intersections_list_add(&intersections, new6);
	intersections_list_add(&intersections, new7);

	t_intersections	*result = get_hit(intersections);

	cr_assert(epsilon_eq(flt, 0.95, result->t, EPSILON));
	free_intersections(&intersections);
}

Test(ray_casting, test_get_hit_2) {
	t_intersections	*intersections = NULL;

	t_intersections	*result = get_hit(intersections);
	int	i;
	i = 1;
	if (!result)
		i = 0;

	cr_assert(epsilon_eq(flt, 0, i, EPSILON));
	free_intersections(&intersections);
}
