/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsellars <jsellars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 11:47:48 by jsellars          #+#    #+#             */
/*   Updated: 2022/01/06 13:42:09 by jsellars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
function:
	get_line

args:
	int fd
	char *buffer
	char **cache

description:
	vars:
		len:
			bytes read from the read() function
		tmp:
			copy of the cache to read from and return
			back
	
	- check that there are bytes to be read from fd
	- if yes, initialise a new cache and copy to tmp
	- join buffer and tmp to the cache
	- read the next buffer size unless a new line is found
*/
char	*get_line(int fd, char *buffer, char **cache)
{
	int		len;
	char	*tmp;

	len = 1;
	while (len != 0)
	{
		len = read(fd, buffer, BUFFER_SIZE);
		if (len == -1)
			return (NULL);
		if (len == 0)
			break ;
		buffer[len] = '\0';
		if (!cache[fd])
			cache[fd] = ft_strdup("");
		tmp = cache[fd];
		cache[fd] = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_strchr (buffer, '\n'))
			break ;
	}
	return (cache[fd]);
}

/*
function:
	extract

args:
	char *line

description:
	vars:
		i:
			index of the string
		tmp_cache:
			the string to return after extracting all characters
			after the first occurrence of a '\n'

	- iterate through the line until null terminator or new line
		is found
	- if no new line found in entire string return null
	- store excess in tmp_cache and if valid, null terminate it and
		return it
*/
char	*extract(char *line)
{
	size_t	i;
	char	*tmp_cache;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0' || line[i + 1] == '\0')
		return (NULL);
	tmp_cache = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (*tmp_cache == '\0')
		free(tmp_cache);
	line[i + 1] = '\0';
	return (tmp_cache);
}

/*
function: 
	get_next_line

args:
	int fd

description: 
	vars:
		cache:
			list of strings to store the left over data if
			any left in the buffer for next gnl call
		buffer:
			dynamically allocated array of characters to
			store the bytes read from file
		result;
			string of characters representing the next line
			in the file including the '\n'
	
	- check valid file descriptor and buffer size
	- allocate memory for buffer and the null terminator then
		check allocation worked.
	- retrieve the next line from file
	- free the buffer as it's not needed
	- check if result is empty
	- store excess in cache
	- return the result
*/
char	*get_next_line(int fd)
{
	static char		*cache[MAX_FD];
	char			*buffer;
	char			*result;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > MAX_FD)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	result = get_line(fd, buffer, cache);
	free(buffer);
	if (!result)
		return (NULL);
	cache[fd] = extract(result);
	return (result);
}
