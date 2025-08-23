/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_color_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:44:04 by kchiang           #+#    #+#             */
/*   Updated: 2025/08/23 16:10:57 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	encode_trgb(uint8_t transparency, uint8_t red, uint8_t green, uint8_t blue)
{
	return (transparency << 24 | red << 16 | green << 8 | blue);
}
