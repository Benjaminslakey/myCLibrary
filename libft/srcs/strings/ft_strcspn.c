/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bslakey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 20:17:45 by bslakey           #+#    #+#             */
/*   Updated: 2016/09/22 20:58:53 by bslakey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int 			ft_strcspn(char *str, char *allowed)
{
	int 		inspan;
	int 		i;
	int 		j;

	i = -1;
	j = -1;
	inspan = 0;
	while (str[++i])
	{
		j = -1;
		inspan = 0;
		while (allowed[++j])
		{
			if (str[i] == allowed[j])
			{
				inspan = 1;
				break ;
			}
		}
		if (inspan != 1)
			return (0);
	}
	return (1);
}

/*
* int main(int argc, char **argv)
* {
*	if (argc > 2)
*	{
*		if (ft_strcspn(argv[1], argv[2]))
*			printf("within span\n");
*		else
*			printf("not within character span\n");
*		return (1);
*	}
*	return (0);
* }
*/