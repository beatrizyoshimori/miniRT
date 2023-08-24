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

Test(parser, test_validate_camera_50_0_20__0_0_1__70) {
	t_rt	*rt = ft_calloc(1, sizeof(t_rt));
	rt->element = ft_split("C 50,0,20 0,0,1 70", ' ');
	t_rt	expected = (t_rt){.camera.point.x = 50, .camera.point.y = 0, .camera.point.z = 20, \
							.camera.vector.x = 0, .camera.vector.y = 0, .camera.vector.z = 1, \
							.camera.fov = 70};

	validate_camera(rt);

	cr_assert(epsilon_eq(flt, expected.camera.point.x, rt->camera.point.x, EPSILON));
	cr_assert(epsilon_eq(flt, expected.camera.point.y, rt->camera.point.y, EPSILON));
	cr_assert(epsilon_eq(flt, expected.camera.point.z, rt->camera.point.z, EPSILON));
	cr_assert(epsilon_eq(flt, expected.camera.vector.x, rt->camera.vector.x, EPSILON));
	cr_assert(epsilon_eq(flt, expected.camera.vector.y, rt->camera.vector.y, EPSILON));
	cr_assert(epsilon_eq(flt, expected.camera.vector.z, rt->camera.vector.z, EPSILON));
	cr_assert(epsilon_eq(flt, expected.camera.fov, rt->camera.fov, EPSILON));
	free_ptrptr(&rt->element);
	free(rt);
}

Test(parser, test_validate_camera_minus_75_minus_10_20__0_267261_minus_0_534522_0_801784__70) {
	t_rt	*rt = ft_calloc(1, sizeof(t_rt));
	rt->element = ft_split("C -75,-10,20 0.267261,-0.534522,0.801784 179", ' ');
	t_rt	expected = (t_rt){.camera.point.x = -75, .camera.point.y = -10, .camera.point.z = 20, \
							.camera.vector.x = 0.267261, .camera.vector.y = -0.534522, .camera.vector.z = 0.801784, \
							.camera.fov = 179};

	validate_camera(rt);

	cr_assert(epsilon_eq(flt, expected.camera.point.x, rt->camera.point.x, EPSILON));
	cr_assert(epsilon_eq(flt, expected.camera.point.y, rt->camera.point.y, EPSILON));
	cr_assert(epsilon_eq(flt, expected.camera.point.z, rt->camera.point.z, EPSILON));
	cr_assert(epsilon_eq(flt, expected.camera.vector.x, rt->camera.vector.x, EPSILON));
	cr_assert(epsilon_eq(flt, expected.camera.vector.y, rt->camera.vector.y, EPSILON));
	cr_assert(epsilon_eq(flt, expected.camera.vector.z, rt->camera.vector.z, EPSILON));
	cr_assert(epsilon_eq(flt, expected.camera.fov, rt->camera.fov, EPSILON));
	free_ptrptr(&rt->element);
	free(rt);
}

Test(parser, test_validate_camera_50_0_20__0_0_1__70__185, .exit_code = 1) {
	int		fd;
	int		bkp = dup(1);
	char	*name = "validate_camera_error";
	// char	*error = "Error\nInvalid number of arguments on ambient light.\n";
	// char	*read_str;
	t_rt	*rt = ft_calloc(1, sizeof(t_rt));
	rt->element = ft_split("C 50,0,20 0,0,1 70 185", ' ');

	set_output(&fd, name);
	validate_camera(rt);
	// read_str = read_output(name);
	unset_output(&fd, &bkp);

	free_ptrptr(&rt->element);
	free(rt);
	// free(read_str);
	// cr_assert_str_eq(read_str, error, "value expected [ %s ], result [ %s ].\n", read_str, error);
}

Test(parser, test_validate_camera_50_0f_20__0_0_1__70, .exit_code = 1) {
	int		fd;
	int		bkp = dup(1);
	char	*name = "validate_camera_error";
	// char	*error = "Error\nInvalid number of arguments on ambient light.\n";
	// char	*read_str;
	t_rt	*rt = ft_calloc(1, sizeof(t_rt));
	rt->element = ft_split("C 50,0f,20 0,0,1 70", ' ');

	set_output(&fd, name);
	validate_camera(rt);
	// read_str = read_output(name);
	unset_output(&fd, &bkp);

	free_ptrptr(&rt->element);
	free(rt);
	// free(read_str);
	// cr_assert_str_eq(read_str, error, "value expected [ %s ], result [ %s ].\n", read_str, error);
}

Test(parser, test_validate_camera_50_0_20__0_0_1l__70, .exit_code = 1) {
	int		fd;
	int		bkp = dup(1);
	char	*name = "validate_camera_error";
	// char	*error = "Error\nInvalid number of arguments on ambient light.\n";
	// char	*read_str;
	t_rt	*rt = ft_calloc(1, sizeof(t_rt));
	rt->element = ft_split("C 50,0,20 0,0,1l 70", ' ');

	set_output(&fd, name);
	validate_camera(rt);
	// read_str = read_output(name);
	unset_output(&fd, &bkp);

	free_ptrptr(&rt->element);
	free(rt);
	// free(read_str);
	// cr_assert_str_eq(read_str, error, "value expected [ %s ], result [ %s ].\n", read_str, error);
}

Test(parser, test_validate_camera_50_0_20__0_0_2__70, .exit_code = 1) {
	int		fd;
	int		bkp = dup(1);
	char	*name = "validate_camera_error";
	// char	*error = "Error\nInvalid number of arguments on ambient light.\n";
	// char	*read_str;
	t_rt	*rt = ft_calloc(1, sizeof(t_rt));
	rt->element = ft_split("C 50,0,20 0,0,2 70", ' ');

	set_output(&fd, name);
	validate_camera(rt);
	// read_str = read_output(name);
	unset_output(&fd, &bkp);

	free_ptrptr(&rt->element);
	free(rt);
	// free(read_str);
	// cr_assert_str_eq(read_str, error, "value expected [ %s ], result [ %s ].\n", read_str, error);
}

Test(parser, test_validate_camera_50_0_20__0_0_1__70k, .exit_code = 1) {
	int		fd;
	int		bkp = dup(1);
	char	*name = "validate_camera_error";
	// char	*error = "Error\nInvalid number of arguments on ambient light.\n";
	// char	*read_str;
	t_rt	*rt = ft_calloc(1, sizeof(t_rt));
	rt->element = ft_split("C 50,0,20 0,0,1 70k", ' ');

	set_output(&fd, name);
	validate_camera(rt);
	// read_str = read_output(name);
	unset_output(&fd, &bkp);

	free_ptrptr(&rt->element);
	free(rt);
	// free(read_str);
	// cr_assert_str_eq(read_str, error, "value expected [ %s ], result [ %s ].\n", read_str, error);
}

Test(parser, test_validate_camera_50_0_20__0_0_1__250, .exit_code = 1) {
	int		fd;
	int		bkp = dup(1);
	char	*name = "validate_camera_error";
	// char	*error = "Error\nInvalid number of arguments on ambient light.\n";
	// char	*read_str;
	t_rt	*rt = ft_calloc(1, sizeof(t_rt));
	rt->element = ft_split("C 50,0,20 0,0,1 250", ' ');

	set_output(&fd, name);
	validate_camera(rt);
	// read_str = read_output(name);
	unset_output(&fd, &bkp);

	free_ptrptr(&rt->element);
	free(rt);
	// free(read_str);
	// cr_assert_str_eq(read_str, error, "value expected [ %s ], result [ %s ].\n", read_str, error);
}
