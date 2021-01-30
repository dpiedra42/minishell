/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 13:45:17 by dpiedra           #+#    #+#             */
/*   Updated: 2021/01/30 15:26:23 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int minishell()
{
    ft_putstr_fd("minishell>", 1);
    return (0);
}

int main(int ac, char **av, char **env)
{
    ac = 0;
    av = NULL;
    env = NULL;
    minishell();
    return (0);
}