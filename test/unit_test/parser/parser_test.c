#include "criterion.h"
#include "new/assert.h"

# define EPSILON 0.001

typedef struct s_sphere
{
	int			id;
	double		point[3];
	double		diameter;
	int			rgb[3];
}				t_sphere;

t_sphere sphere(char *str)
{
	return (t_sphere){0};
	(void)str;
}

Test(parser, test_sphere) {
	char		*str = "sp 10,0,-5 2.0 255,55,35";
	t_sphere	expected = (t_sphere){.id = 0, .point = {10, 0, -5}, .diameter = 2.0, .rgb = {255, 55, 35}};
	t_sphere	result;

	result = sphere(str);

	cr_assert(eq(expected.id, result.id));
	cr_assert(epsilon_eq(flt, expected.point[0], result.point[0], EPSILON));
}