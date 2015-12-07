#include "my_fnmatch.h"
#include <fnmatch.h>

//la fonction "stats" est appele pour gere les etoiles, elle est semi-recusive
int stars(const char *pattern, const char *string)
{
    if (*pattern != '\0')
    {
        while (*string != '\0')
        {
            if (my_fnmatch(pattern, string) == 0)
                return (0);
            return (stars(pattern, ++string));
        }
        return (1);
    }
    return (0);
}

//la fonction "backslach" est appele pour gere les "/" afin de pouvoir utiliser
//les caracteres speciaux, elle est recursif.
int backslach(const char *pattern, const char *string)
{
    if (*pattern == *string)
        return (my_fnmatch(pattern,string));
    return (1);
}

//la fonction "hook" permet de gere les cas avec crochet mais comme il est dit 
//dans le TODO je n'est pas gere les intervalles...
int hook(const char *p, const char *s)
{
    int x = 0;

    while (*p != ']')
    {
        if (*p == *s)
            x = 1;
        p++;
    }
    if (x == 1)
        return (my_fnmatch(++p,++s));

    return (1);
}

//la fonction my_fnmatch de base totalement recursive
int my_fnmatch(const char *pattern, const char *string)
{
    if (*string == '\0' && *pattern == '\0')
        return (0);

    if (*pattern == '?')
        return (my_fnmatch(++pattern, ++string));

    if (*pattern == *string)
        return (my_fnmatch(++pattern, ++string));

    if (*pattern == '\\')
        return (backslach(++pattern, string));

    if (*pattern == '*')
        return (stars(++pattern,string));

    if (*pattern == '[')
        return (hook(++pattern,string));

    if (*string == '\0' || *pattern == '\0')
        return (1);

    return (1);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
        return (42);
    printf("fnmatch de base : \n");
    printf("%d",fnmatch(argv[1],argv[2],0));
    printf("\n");
    printf("my_fnmatch : \n");
    printf("%d",my_fnmatch(argv[1],argv[2]));

    return (my_fnmatch(argv[1],argv[2]));
}


