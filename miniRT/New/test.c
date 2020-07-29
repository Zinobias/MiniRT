void	rendering(t_obj_list *list)
{
	t_data	mlx;
	t_img_list *img_l;

	img_l = (t_img_list*)malloc(sizeof(t_img_list));
	if (!img_l)
		error(MALLOC);
	mlx.res = l_get_R(&list);
	mlx.ambient_light = l_get_A(&list);

	mlx.mlx = mlx_init();
	if (!mlx.mlx)
		error(MLX);
	img_l->img = mlx_new_image(mlx.mlx, mlx.res.x, mlx.res.y);
	if (!img_l->img)
		error(MLX);
	mlx.win = mlx_new_window(mlx.mlx, mlx.res.x, mlx.res.y, "hello worlddd");
	if (!mlx.win)
		error(MLX);
	img_l->addr = mlx_get_data_addr(img_l->img, &mlx.bits_p_p, &mlx.line_l, &mlx.endian);

	for (int i = 50; i < 200; i++) {
		for (int j = 50; j < 200; j++) {
			my_mlx_pixel_put(img_l, &mlx, i, j, rgba(0, 55, 55, 255));
		}
	}
	mlx.addr = img_l->addr;
	mlx.img = img_l->img;
	mlx_put_image_to_window(mlx.mlx, mlx.win, img_l->img, 0, 0);
	mlx_key_hook(mlx.win, close_window_esc, &mlx);
	mlx_hook(mlx.win, 17, 0, close_win_x, &mlx);
	mlx_loop(mlx.mlx);
	return ;
}

void            my_mlx_pixel_put(t_img_list *img_l, t_data *mlx, int x, int y, int color)
{
    char    *dst;

    dst = img_l->addr + (y * mlx->line_l + x * (mlx->bits_p_p / 8));
    *(unsigned int*)dst = color;
}