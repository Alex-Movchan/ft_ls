
#include "libft.h"

char    *ft_strndup(char *str, size_t len)
{
    char	*src;

    if (!(src = ft_strnew(len)))
        return (NULL);
    src = ft_strncpy(src, str, len);
    return (src);
}