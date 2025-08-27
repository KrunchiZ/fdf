/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:06:19 by kchiang           #+#    #+#             */
/*   Updated: 2025/08/27 16:28:06 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fn_error_exit(char *str)
{
	ft_putstr_fd("fdf: ", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	fn_perror_exit(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	fn_argc_check(int argc)
{
	if (argc != 2)
		fn_error_exit("Input = fdf [FILE]...");
	return ;
}
