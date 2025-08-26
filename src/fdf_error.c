/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:06:19 by kchiang           #+#    #+#             */
/*   Updated: 2025/08/26 16:09:41 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fn_error_exit(int exit_code)
{
	ft_putendl_fd("fdf: Error", STDERR_FILENO);
	exit(exit_code);
}
