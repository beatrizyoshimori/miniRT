#include "criterion.h"
#include "new/assert.h"
#include "unit_test.h"

# define __PATH_TEST_ "fd_test/%s.test"

void	set_output(int *fd, char *name)
{
	char	path[300] = {0};
	sprintf(path, __PATH_TEST_, name);
	*fd = open(path, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU | S_IRWXG | S_IRWXO);
	dup2(*fd, 1);
}

void	unset_output(int *fd, int *bkp)
{
	dup2(*bkp, 1);
	close(*fd);
}

char	*read_output(char *name)
{
	int		fd;
	int		rd;
	char	c;
	char	*buffer;

	fd = open(name, O_RDONLY);
	rd = read(fd, &c, 1);
	while (read(fd, &c, 1))
		rd++;
	close(fd);
	buffer = (char *)ft_calloc(rd + 1, sizeof(char));
	fd = open(name, O_RDONLY);
	read(fd, buffer, rd);
	close(fd);
	return (buffer);
}

Test(parser, test_validate_amb_light_1__0_0_0) {
	t_rt	*rt = ft_calloc(1, sizeof(t_rt));
	rt->element = ft_split("A 1 0,0,0", ' ');
	t_rt	expected = (t_rt){.amb_light.ratio = 1, .amb_light.color.red = 0, \
								.amb_light.color.green = 0, .amb_light.color.blue = 0};

	validate_amb_light(rt);

	cr_assert(epsilon_eq(flt, expected.amb_light.ratio, rt->amb_light.ratio, EPSILON));
	cr_assert(epsilon_eq(flt, expected.amb_light.color.red, rt->amb_light.color.red, EPSILON));
	cr_assert(epsilon_eq(flt, expected.amb_light.color.green, rt->amb_light.color.green, EPSILON));
	cr_assert(epsilon_eq(flt, expected.amb_light.color.blue, rt->amb_light.color.blue, EPSILON));
	free_ptrptr(&rt->element);
	free(rt);
}

Test(parser, test_validate_amb_light_1__0_1_0) {
	t_rt	*rt = ft_calloc(1, sizeof(t_rt));
	rt->element = ft_split("A 1 0,1,0", ' ');
	t_rt	expected = (t_rt){.amb_light.ratio = 1, .amb_light.color.red = 0, \
								.amb_light.color.green = 1, .amb_light.color.blue = 0};

	validate_amb_light(rt);

	cr_assert(epsilon_eq(flt, expected.amb_light.ratio, rt->amb_light.ratio, EPSILON));
	cr_assert(epsilon_eq(flt, expected.amb_light.color.red, rt->amb_light.color.red, EPSILON));
	cr_assert(epsilon_eq(flt, expected.amb_light.color.green, rt->amb_light.color.green, EPSILON));
	cr_assert(epsilon_eq(flt, expected.amb_light.color.blue, rt->amb_light.color.blue, EPSILON));
	free_ptrptr(&rt->element);
	free(rt);
}

Test(parser, test_validate_amb_light_1__0_0_0__1, .exit_code = 1) {
	int		fd;
	int		bkp = dup(1);
	char	*name = "validate_amb_light_error";
	// char	*error = "Error\nInvalid number of arguments on ambient light.\n";
	// char	*read_str;
	t_rt	*rt = ft_calloc(1, sizeof(t_rt));
	rt->element = ft_split("A 1 0,0,0 1", ' ');

	set_output(&fd, name);
	validate_amb_light(rt);
	// read_str = read_output(name);
	unset_output(&fd, &bkp);

	free_ptrptr(&rt->element);
	free(rt);
	// free(read_str);
	// cr_assert_str_eq(read_str, error, "value expected [ %s ], result [ %s ].\n", read_str, error);
}

Test(parser, test_validate_amb_light_1f__0_0_0, .exit_code = 1) {
	int		fd;
	int		bkp = dup(1);
	char	*name = "validate_amb_light_error";
	// char	*error = "Error\nInvalid number of arguments on ambient light.\n";
	// char	*read_str;
	t_rt	*rt = ft_calloc(1, sizeof(t_rt));
	rt->element = ft_split("A 1f 0,0,0", ' ');

	set_output(&fd, name);
	validate_amb_light(rt);
	// read_str = read_output(name);
	unset_output(&fd, &bkp);

	free_ptrptr(&rt->element);
	free(rt);
	// free(read_str);
	// cr_assert_str_eq(read_str, error, "value expected [ %s ], result [ %s ].\n", read_str, error);
}

Test(parser, test_validate_amb_light_1_point_2__0_0_0, .exit_code = 1) {
	int		fd;
	int		bkp = dup(1);
	char	*name = "validate_amb_light_error";
	// char	*error = "Error\nInvalid number of arguments on ambient light.\n";
	// char	*read_str;
	t_rt	*rt = ft_calloc(1, sizeof(t_rt));
	rt->element = ft_split("A 1.2 0,0,0", ' ');
	rt->color = NULL;
	rt->elements = NULL;

	set_output(&fd, name);
	validate_amb_light(rt);
	// read_str = read_output(name);
	unset_output(&fd, &bkp);

	free_ptrptr(&rt->element);
	free(rt);
	// free(read_str);
	// cr_assert_str_eq(read_str, error, "value expected [ %s ], result [ %s ].\n", read_str, error);
}

Test(parser, test_validate_amb_light_1__0_0_256, .exit_code = 1) {
	int		fd;
	int		bkp = dup(1);
	char	*name = "validate_amb_light_error";
	// char	*error = "Error\nInvalid number of arguments on ambient light.\n";
	// char	*read_str;
	t_rt	*rt = ft_calloc(1, sizeof(t_rt));
	rt->element = ft_split("A 1 0,0,256", ' ');
	rt->color = NULL;
	rt->elements = NULL;

	set_output(&fd, name);
	validate_amb_light(rt);
	// read_str = read_output(name);
	unset_output(&fd, &bkp);

	free_ptrptr(&rt->element);
	free(rt);
	// free(read_str);
	// cr_assert_str_eq(read_str, error, "value expected [ %s ], result [ %s ].\n", read_str, error);
}
