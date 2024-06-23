/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuhn <kkuhn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:46:29 by kkuhn             #+#    #+#             */
/*   Updated: 2024/05/28 20:48:23 by kkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	handle_no_event(t_data *data)
{
	double	*null_punkt;

	null_punkt = malloc (2 * sizeof(double));
	set_coordinate(data->nullx, data->nully, &null_punkt);
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	visualize(data, null_punkt);
	free(null_punkt);
	return (0);
}

int	handle_input(int keysym, t_data *data)
{
	shift_colors(data, keysym);
	if (keysym == 53)
		close_win(data);
	if (keysym == 126)
		data->nully -= 10;
	if (keysym == 125)
		data->nully += 10;
	if (keysym == 124)
		data->nullx += 10;
	if (keysym == 123)
		data->nullx -= 10;
	if (keysym == 13)
		data->creal = data->creal + 0.1;
	if (keysym == 1)
		data->creal = data->creal - 0.1;
	if (keysym == 2)
		data->cimag = data->cimag + 0.1;
	if (keysym == 0)
		data->cimag = data->cimag - 0.1;
	if (keysym == 12)
		data->i = data->i - 50;
	if (keysym == 14)
		data->i = data->i + 50;
	return (0);
}

int	handle_scroll(int button, int x, int y, t_data *data)
{
	double	zoom_old;

	mlx_mouse_get_pos(data->win_ptr, &data->mouse_x, &data->mouse_y);
	x = 0;
	y = 0;
	if (button == 4)
	{
		zoom_old = data->zoom;
		data->zoom = 1.5 * data->zoom;
		data->zoom_old = zoom_old;
		data = calc_nullpunkt(data);
	}
	else if (button == 5)
	{
		zoom_old = data->zoom;
		data->zoom = data->zoom / 1.5;
		data->zoom_old = zoom_old;
		data = calc_nullpunkt(data);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (print_fractal_options(argv, argc) == 0)
		return (0);
	data.name_set = argv[1];
	set_data(&data, argv, argc);
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, 1000, 1000, "My Window");
	if (data.win_ptr == NULL)
		return (1);
	mlx_loop_hook(data.mlx_ptr, &handle_no_event, &data);
	mlx_hook(data.win_ptr, 4, 0, (int (*)())handle_scroll, &data);
	mlx_key_hook(data.win_ptr, &handle_input, &data);
	mlx_loop(data.mlx_ptr);
}
