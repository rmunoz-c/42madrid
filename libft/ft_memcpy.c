/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:44:39 by rmunoz-c          #+#    #+#             */
/*   Updated: 2024/09/30 15:44:41 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				count;
	unsigned char		*ptr;
	const unsigned char	*ptr2;

	if (!dest || !src)
		return (NULL);
	count = 0;
	ptr = (unsigned char *)dest;
	ptr2 = (const unsigned char *)src;
	while (count < n)
	{
		ptr[count] = ptr2[count];
		count++;
	}
	return (dest);
}

/*int	main(void)
{
	char src[] = "EstoEsUnTestDeMemCPY";
	char dest[] = "Hola que tal?";
	
	ft_memcpy(dest, src, 19);
	
	write(1, src, 19);
	return (0);
}*/
