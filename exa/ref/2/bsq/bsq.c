#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



typedef struct
{
    int y;
    int x;
    int size;
}square;


int min3(int a, int b, int c)
{
    if(a<=b&&a<=c)return a;
    if(b<=a&&b<=c)return b;
    else
        return c;
}


int sstrlen(char *s)
{
    char *p =s;
    while(*p)p++;
    return p - s;
}


int main(int ac, char **av)
{
    FILE *fi = ac > 1 ? fopen(av[1], "r"): stdin;
    if(!fi) return fprintf(stderr, "Error\n"), 1;

    int h = 0;
    char e = 0;
    char o = 0;
    char f = 0;
    if(fscanf(fi, "%d%c%c%c\n", &h,&e,&o,&f) != 4)
        return fprintf(stderr, "map Error\n"), 1;
    if(e == f || e == o || o == f)
        return fprintf(stderr, "map Error\n"), 1;
    char **map = calloc(h, sizeof(char *));
    if(!map)
        return fprintf(stderr, "malloc Error\n"), 1;
    int w = 0;

    for(int i = 0; i < h; i++)
    {
        char *line  = NULL;
        size_t len  = 0;
        if(getline(&line , &len , fi) < 0)
        {
            return fprintf(stderr, "Error\n"), 1;
        }
        int l = sstrlen(line);
        if(l > 0 && line[l-1] == '\n')
        {
            line[--l] = '\0';
        }
        if(!w)
            w = l;
        if(w != l)
            return fprintf(stderr, "map Error\n"), 1;
        map[i] = line;
    }

    if(fi != stdin)
        fclose(fi);
    int **db = calloc(h  + 1, sizeof(int *));
    for(int i = 0; i <= h; i++)
    {
        db[i] = calloc(w + 1, sizeof(int));
    }

    square s = {0,0,0};

    for(int i = 0; i < h ; i++)
    {
        for(int j = 0; j < w ; j++)
        {
            if(map[i][j] == e)
            {
                db[i + 1][j + 1] = 1 + min3(db[i][j + 1], db[i + 1][j],db[i][j]);
                if(s.size < db[i + 1][j + 1])
                {
                    s = (square){i , j , db[i + 1][j + 1]};
                }
            }
            else if(map[i][j] != o)
            {
                return fprintf(stderr, "map Error\n"), 1;
            }
        }
    }
    for(int i = s.y - s.size + 1; i <= s.y; i++)
    {
        for(int j = s.x - s.size + 1; j <= s.x; j++)
        {
            map[i][j] = f;
        }
    }


    for(int i  = 0; i < h; i++)
    {
        fprintf(stdout,"%s\n", map[i]);
        free(map[i]);
    }
    free(map);
    for(int i  = 0; i <= h; i++)
    {
        free(db[i]);
    }
    free(db);
    return 0;
}

