#include "criterion.h"
#include "new/assert.h"
#include "unit_test.h"

Test(parser, test_validate_amb_light_1_0_0_0) {
	t_rt	*rt = ft_calloc(1, sizeof(t_rt));
	rt->element = ft_calloc(4, sizeof(char *));
	rt->element[0] = ft_strdup("A");
	rt->element[1] = ft_strdup("1");
	rt->element[2] = ft_strdup("0,0,0");
	t_rt	expected = (t_rt){.amb_light.ratio = 1, .amb_light.color.red = 0, .amb_light.color.green = 0, .amb_light.color.blue = 0};

	validate_amb_light(rt);

	cr_assert(epsilon_eq(flt, expected.amb_light.ratio, rt->amb_light.ratio, EPSILON));
	cr_assert(epsilon_eq(flt, expected.amb_light.color.red, rt->amb_light.color.red, EPSILON));
	cr_assert(epsilon_eq(flt, expected.amb_light.color.green, rt->amb_light.color.green, EPSILON));
	cr_assert(epsilon_eq(flt, expected.amb_light.color.blue, rt->amb_light.color.blue, EPSILON));
	free_ptrptr(rt->element);
	free(rt);
}

// Test(parser, test_validate_amb_light_1_0_0_0_1) {
// 	t_rt	*rt = ft_calloc(1, sizeof(t_rt));
// 	rt->element = ft_calloc(5, sizeof(char *));
// 	rt->element[0] = ft_strdup("A");
// 	rt->element[1] = ft_strdup("1");
// 	rt->element[2] = ft_strdup("0,0,0");
// 	rt->element[3] = ft_strdup("1");
// 	rt->elements = NULL;
// 	char	*expected = (t_rt){.amb_light.ratio = 1, .amb_light.color.red = 0, .amb_light.color.green = 0, .amb_light.color.blue = 0};

// 	validate_amb_light(rt);

// 	cr_assert(epsilon_eq(flt, expected.amb_light.ratio, rt->amb_light.ratio, EPSILON));
// 	free_ptrptr(rt->element);
// 	free(rt);
// }