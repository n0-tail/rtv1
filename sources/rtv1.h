/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 09:35:11 by anikkane          #+#    #+#             */
/*   Updated: 2020/10/05 10:10:11 by anikkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "../libft/libft.h"
# include "mlx.h"
# include <math.h>
# include <fcntl.h>

# define WIDTH 			1000
# define HEIGHT			1000

# define FOV			90

# define MAIN_PAD_ESC	53

# define DTR(k)	((double)k * (M_PI / 180))

typedef struct		s_material
{
	double			diffuse_red;
	double			diffuse_green;
	double			diffuse_blue;

}					t_material;

typedef	struct		s_color
{
	int8_t			channel[4];

}					t_color;

typedef struct		s_vector
{
	double			x;
	double			y;
	double			z;
}					t_vector;

typedef	struct		s_ray
{
	t_vector		start;
	t_vector		target;
	t_vector		newstart;

}					t_ray;

typedef struct		s_rgb2
{
	int				red;
	int				blue;
	int				green;
}					t_rgb2;

typedef struct		s_rgb
{
	double			red;
	double			blue;
	double			green;
}					t_rgb;

typedef	struct		s_hit
{
	double			t;
	char			*obj_name;
	int				obj_idx;
	char 			*preobj_name;
	int				preobj_idx;
	int				find_shadow;
	double			a;
	double			b;
}					t_hit;

typedef struct		s_sphere
{
	t_vector		xyz[10];
	t_material		material[10];
	int				radius[10];
	int				rot_x[10];
	int				rot_y[10];
	int				rot_z[10];
	t_rgb2			rgb2[10];
	int				nbr;
}					t_sphere;

typedef struct		s_plane
{
	int				nbr;
	t_vector		xyz[10];
	t_vector		normal[10];
	t_rgb2			rgb2[10];
	t_vector		rot[10];
}					t_plane;

typedef struct		s_spot
{
	int				x[10];
	int				y[10];
	int				z[10];
	double			intensity_red[10];
	double			intensity_green[10];
	double			intensity_blue[10];
	t_color			color[10];
	int				power[10];
	int				nbr;
}					t_spot;

typedef struct		s_cylinder
{
	t_vector		start_xyz[10];
	t_vector		end_xyz[10];
	t_vector		axis[10];
	t_vector		rot[10];
	int				radius[10];
	int				nbr;
	t_rgb2			rgb2[10];
}					t_cylinder;

typedef struct		s_cone
{
	t_vector		start_xyz[10];
	t_vector		rot[10];
	t_vector		axis[10];
	double			angle[10];
	t_rgb2			rgb2[10];
	int				nbr;
}					t_cone;

typedef struct		s_camera
{
	t_vector		xyz;
	t_vector		target;
	t_vector		rot;
	t_vector		direction;
	t_vector		right;
	t_vector		up;
}					t_camera;

typedef struct		s_data
{
	void			*win;
	void			*mlx;
	char			*data_addr;
	int				bits_per_pixel;
	void			*image;
	int				size_line;
	int				endian;
	int				start_line;
	int				finish_line;
	int				objnbr;
	double			light_scale;
	int				org_iter;
	int				iter;
	t_hit			hit;
	t_sphere		*sphere;
	t_cylinder		*cylinder;
	t_cone			*cone;
	t_spot			*spot;
	t_plane			*plane;
	t_camera		*camera;
}					t_data;

int					read_scene(const int fd, t_data *data);
int					get_next_line(const int fd, char **line);
void				parse_scene(char *line, t_data *data);
void				init_data(t_data *data);
void				init_camera(t_data *data);
t_vector			init_target(int x, int y);
void				parse_sphere(char *line, t_data *data);
void				parse_cylinder(char *line, t_data *data);
void				parse_cone(char *line, t_data *data);
void				parse_spot(char *line, t_data *data);
void				parse_plane(char *line, t_data *data);
void				parse_camera(char *line, t_data *data);
void				draw(t_data *data);
void				get_color(t_data *data, int x, int y);
double				vectordot(t_vector v1, t_vector v2);
t_vector			vectoradd(t_vector v1, t_vector v2);
t_vector			vectorscale(double c, t_vector v);
t_vector			vector_minus(t_vector v1, t_vector v2);
t_vector			normalized_vector(t_vector v);
t_vector			vector_plus(t_vector v1, t_vector v2);
t_vector			return_vector(int x, int y, int z);
int					intersectsphere(t_ray ray, t_data *data, int i);
t_rgb				get_light(t_data *data, t_rgb rgb, t_ray ray, int i);
t_vector			cross_vector(t_vector v1, t_vector v2);
t_vector			rotate_vector(t_vector origin, t_vector target,
		t_vector rot, int no_z);
int					intersectcylinder(t_ray ray, t_data *data, int i);
double				double_sqr(double n);
t_vector			vectorsub(t_vector a, t_vector b);
t_vector			vectoradd(t_vector v1, t_vector v2);
int					intersectplane(t_data *data, int i, t_ray ray);
int					intersectcone(t_ray ray, t_data *data, int i);
void				set_hit(t_data *data, char *name, int i);
t_vector			new_start_dir_plane(t_data *data, t_ray *ray);
t_vector			new_start_dir_sphere(t_data *data, t_ray *ray);
t_vector			new_start_dir_cylinder(t_data *data, t_ray *ray);
t_vector			new_start_dir_cone(t_data *data, t_ray *ray);
int					shadow_sphere(t_vector newstart, int i, t_data *data,
		t_vector light_pos);
int					shadow_cone(t_vector newstart, int i, t_data *data,
		t_vector light_pos);
int					shadow_cylinder(t_vector newstart, int i, t_data *data,
		t_vector light_pos);
int					shadow_plane(t_vector newstart, int i, t_data *data,
		t_vector light_pos);
int					shadow(t_data *data, t_vector newstart, int i);
t_vector			vectornew(double x, double y, double z);
double				vector_length(t_vector v);
t_vector			vector_copy(t_vector v);
void				setup(t_data *data);
t_vector			vec_rot_zyx(t_vector v, t_vector r);
t_vector			vec_rot_z(t_vector v, double a);
t_vector			vec_rot_y(t_vector v, double a);
t_vector			vec_rot_x(t_vector v, double a);
void				memory_allocation_fail(void);
void				wrong_argument_nbr(void);
void				data_read_error(void);
t_data				*allocate_memory(t_data *data);
void				free_memory(t_data *data);
void				init_mlx(t_data *data, void *mlx_ptr);
int					keypressed(int keycode);
char				*if_negative(char *line, char *str, int *i, int *y);
int 				min(int num1, int num2);
t_ray  				init_pixel(t_data *data, int x, int y, t_rgb *rgb);
void 				put_color(t_data *data, t_rgb rgb, int x, int y);
void				wrong_scene_name(void);
t_vector 			copy_lightpos(t_data *data, int i);

#endif
