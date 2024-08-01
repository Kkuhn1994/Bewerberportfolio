/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuhn <kkuhn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:28:10 by kkuhn             #+#    #+#             */
/*   Updated: 2024/07/30 16:12:31 by kkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error3(char **cmd)
{
	char *errormessage;

	errormessage = ft_strjoin(cmd[0], ": command not found\n");
	free_paths(cmd);
	error2(errormessage, 127);
}


