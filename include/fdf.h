/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:51:26 by kchiang           #+#    #+#             */
/*   Updated: 2025/08/19 12:55:20 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_px;
	int		line_len;
	int		endian;
}			t_data;

#endif
