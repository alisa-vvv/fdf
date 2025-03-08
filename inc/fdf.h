/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   fdf.h                                             :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/03/07 18:05:14 by avaliull     #+#    #+#                  */
/*   Updated: 2025/03/07 18:38:52 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include "ft_printf.h"

# define MALLOC_ERR "malloc()"
# define DUP2_ERR "dup2()"
# define FORK_ERR "fork()"
# define PIPE_ERR "pipe()"
# define FD_ERR "invalid fd"
# define CLOSE_ERR "close()"


typedef	struct	s_coord
{
	int	x;
	int	z;
}	t_coord;

#endif
