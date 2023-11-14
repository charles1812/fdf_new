#include "fdf.h"

int     process_keypress(int keysym, void *mlx)
{
    if(keysym == XK_Escape)
        mlx_loop_end(mlx);
    else if (keysym == XK_k)
        printf("salut\n");
    return (0);
}

int     ft_max_zoom(int one, int two)
{
    if(one > two)
        return(one);
    return(two);

}

void	draw_background(t_data *data, int color)
{
	int	x;
	int	y;

	y = 0;
	while (++y < 800)
	{
		x = 0;
		while (++x < 1000)
			put_pxl(data, x, y, color);
	}
}

void	show_map(t_data *data)
{
	mlx_clear_window(data->mlx, data->mlx_win);
	data->img = mlx_new_image(data->mlx, 1000, 800);
	data->data.img = mlx_get_data_addr(data->img, &data->data.pixel,
			&data->data.line, &data->data.endian);
	draw_background(data, 0x181C26);
	tracing(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	pannel(data);
}

void     get_map(t_data *data)
{
	int		i;
	char	*row;

    i = 0;
    data->height = 0;
    row = get_next_line(data->fd);
	data->width = ft_countword(row);
    while(row)
    {
        free(row);
        row = get_next_line(data->fd);
        data->height += 1;
    }
    free(row);
    data->map = malloc(sizeof(int *) * data->height);
	while (i < data->height)
	{
		data->map[i] = malloc(sizeof(int) * data->width);
		if (!data->map[i])
			exit(-1);
		i++;
	}
}


void	readfile(t_data *data)
{
	char	*str;
	char	**s_str;
	int		j;
	int		i;

	data->gnl = get_next_line(data->fd);
	get_map(data);
    if (!data->map)
		exit(-1);
	j = 0;
	while (str)
	{
		s_str = ft_split(str, ' ');
		i = 0;
		while (i < data->width)
		{
			data->map[j][i] = ft_atoi(s_str[i]);
			i++;
		}
		free(str);
		ft_free_tab(s_str);
		str = get_next_line(data->fd);
		j++;
	}
}

int     process_structure(void *mlx)
{
    mlx_loop_end(mlx);
    return (0);
}

int     process_mouse(int keysym, void *mlx)
{
    if (keysym == Button1)
        printf("left click\n");
    else if (keysym == Button2)
        printf("scroll click\n");
    else if (keysym == Button3)
        printf("right click\n");
    else if (keysym == Button4)
        printf("up scroll\n");
    else if (keysym == Button5)
        printf("down scroll\n");
    return (0);
}


int     main_loop(t_data *data)
{
    static float     x = 200;
    static float     y = 100;

    mlx_clear_window(data->mlx, data->mlx_win);
    ft_rettangolo(data->mlx, data->mlx_win, x, y);
    if(x >= 900)
        x = 100;
    if(y >= 450)
        y = 50;
    x += 0.1;
    y += 0.1;

    return (0);
}


int     main(int argc, char **argv)
{
    t_data *data;

    data = ft_calloc(1, sizeof(*data));
    data->mlx = mlx_init();
	data->fd = open(data->ag[1], O_RDONLY, 0777);
    if (data->fd == -1)
		exit(-1);
    readfile(data);
	close(data->fd);

    data->mlx_win = mlx_new_window(data->mlx, 1000, 500, "Hello world!");
    data->zoom = ft_max_zoom(100 / data->width, 2);
    show_map(data);

    mlx_hook(data->mlx_win, KeyPress, KeyPressMask, process_keypress, data->mlx);
    mlx_hook(data->mlx_win, DestroyNotify, StructureNotifyMask, process_structure, data->mlx);
    mlx_hook(data->mlx_win, ButtonPress, ButtonPressMask, process_mouse, data->mlx);

    mlx_loop_hook(data->mlx, main_loop, data);

    mlx_loop(data->mlx);

    mlx_destroy_window(data->mlx, data->mlx_win);
    mlx_destroy_display(data->mlx);
    free(data->mlx);
    return(0);
}
