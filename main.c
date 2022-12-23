/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayet <apayet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 15:32:13 by apayet            #+#    #+#             */
/*   Updated: 2022/12/23 17:09:07 by apayet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./lcg.h"

typedef enum e_random
{
	A = 1103515245,	// multiplicator
	C = 12345,		// incrementor
	M = 2147483647	// modulo
}		t_random;



static long long	seed_rand(long long p_seed)
{
	static long long	seed = -1;

	if (p_seed == -1)
		return (seed);
	seed = p_seed;
	return (seed);
}

static long long	generate_entropy(void)
{
	int		fd;
	char	buff[1024];
	int		nbr_of_read;
	int		i;
	int		result;

	result = 0;
	i = 0;
	nbr_of_read = 0;
	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
		return (101010);
	read(fd, buff, 1024);
	while (i < 1024)
	{
		nbr_of_read += buff[i];
		i++;
	}
	i = 0;
	if (nbr_of_read < 0)
		nbr_of_read *= -1;
	while (i < nbr_of_read)
	{
		read(fd, buff, 1);
		if (buff[0] < 0)
			continue ;
		result += buff[0];
		i++;
	}
	printf("nbr of read is : %d \n", nbr_of_read);
	printf("new seed is %d\n", result);
	close(fd);
	return (result);
}

static long long	ft_random()
{
	long long	seed_current;

	seed_current = seed_rand(-1);
	if (seed_current == -1)
		seed_current = seed_rand(generate_entropy());
	return (seed_rand((A * seed_current + C) % M));
}

int	main(void)
{
	int	seed;

	seed = 12345;
	seed_rand(seed); // can ommit entropy will be generated
	printf("Start LCG test\n");
	for (int i = 0; i < 10; i++)
		printf("LCG value is %lld\n", ft_random());
	return (0);
}