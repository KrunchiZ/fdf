/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_color_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:44:04 by kchiang           #+#    #+#             */
/*   Updated: 2025/08/30 14:42:18 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	fn_encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
	return (red << 16 | green << 8 | blue);
}

uint8_t	fn_get_red(int rgb)
{
	return (rgb >> 16 & 0xFF);
}

uint8_t	fn_get_green(int rgb)
{
	return (rgb >> 8 & 0xFF);
}

uint8_t	fn_get_blue(int rgb)
{
	return (rgb & 0xFF);
}
