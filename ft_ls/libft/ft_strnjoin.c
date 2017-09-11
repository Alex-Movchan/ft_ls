
#include "libft.h"

char	*ft_strnjoin(char const *s1, char const *s2, size_t len)
{
    char *s;

    if (!s1 || !s2 || !(s = ft_strnew(ft_strlen(s1) + len)))
        return (NULL);
    s = ft_strcpy(s, s1);
    s = ft_strncat(s, s2, len);
    return (s);
}
