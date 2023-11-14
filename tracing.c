#include "fdf.h"

void	tracing(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < tab->height)
	{
		j = 0;
		while (j < tab->width)
		{
			if (j < tab->width - 1)
			{
				tab->x1 = j + 1;
				tab->y1 = i;
				trace_line(j, i, tab);
			}
			if (i < tab->height - 1)
			{
				tab->x1 = j;
				tab->y1 = i + 1;
				trace_line(j, i, tab);
			}
			j++;
		}
		i++;
	}
}