/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_libft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:56:47 by aschenk           #+#    #+#             */
/*   Updated: 2024/09/20 18:50:33 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
Includes general-purpose functions usually included within the libft library.
*/

#include "philo.h"

// IN FILE:

int		ft_atoi(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_putstr_fd(char *s, int fd);
void	*ft_calloc(size_t nmemb, size_t size);

/**
Converts a string to its corresponding integer representation.

Processes the input string `str`, skipping over any leading whitespace
characters. After the whitespace, it checks for an optional sign ('+' or '-')
that determines the sign of the resulting integer. The conversion then
processes digit characters (0-9) until a non-digit character is encountered,
ignoring anything beyond the digits.

Only base 10 numbers (decimal) are handled by this function.

 @param str 	Pointer to the string representing the number.

 @return		The integer representation of the number found in the string,
				including the appropriate sign. If no valid digits are found,
				the function returns 0.

 @param str 	Pointer to the string representing a number.

 @return		The integer representation of the number.
*/
int	ft_atoi(const char *str)
{
	int	sign;
	int	res;

	sign = 1;
	res = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = sign * -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		str++;
	}
	return (res * sign);
}

/**
Compares two null-terminated strings.

This function compares the two strings `s1` and `s2` character by character.
The comparison is done lexicographically (based on ASCII values). The
comparison stops when a difference is found, or when a null terminator
('\0') is reached in either string.
 -	If the two strings are identical, the function returns 0, indicating
	no difference.
 -	If a difference is found and the first differing character in `s2` is
 	greater than the corresponding character in `s1`, the result is negative.
 -	If the first differing character in `s2` is less than the corresponding
	character in `s1`, the result is positive.

 @param s1 	The first string to compare
 @param s2 	The second string to compare

 @return	An integer indicating the result of the comparison:
			`0` if the strings are identical,
			a negative value if `s1` is lexicographically greater than `s2`,
			a positive value if `s2` is lexicographically greater than `s1`.
*/
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/**
Writes a string to the given file descriptor.

 @param s	The string to output. If the string is NULL, nothing is written.
 @param fd 	The file descriptor on which to write.
*/
void	ft_putstr_fd(char *s, int fd)
{
	char	*ptr;

	ptr = s;
	while (*ptr)
	{
		write(fd, ptr, 1);
		ptr++;
	}
}

/**
Allocates memory for an array of `nmemb` elements of `size` bytes each,
and initializes all bytes to zero. If allocation fails, it returns NULL.

 @param nmemb 	The number of elements to allocate memory for.
 @param size 	The size, in bytes, of each element.

 @return 		A pointer to the allocated and zero-initialized memory,
				or `NULL` if the allocation fails or if the multiplication
				of `nmemb` and `size` overflows.
*/
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	total_bytes;

	if (nmemb > 0 && ((size_t)-1) / nmemb < size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	total_bytes = nmemb * size;
	memset(ptr, 0, total_bytes);
	return (ptr);
}
