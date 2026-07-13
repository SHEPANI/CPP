#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct 
{
    int y;
    int x;
    int size;

}square;


int min3(int a , int b  ,int c)
{
    if(a <= b && a <= c)
        return a;
    if(b <= a && b <= c)
        return b;
    return c;
}

int sstrlen(char *s)
{   
    char *p = s;
    while (*p)p++;
    return p  - s;
}

int main(int ac, char **av)
{
    FILE *fi = ac > 1 ? fopen(av[1], "r") : stdin;
    if(!fi)
        return fprintf(stderr, "Error\n"), 1;
    int h;
    char e;
    char o;
    char f;
    if(fscanf(fi, "%d%c%c%c\n", &h, &e, &o, &f)!= 4)
    return fprintf(stderr, "Error\n"), 1;
    if(e == o || e == f || o == f)
    return fprintf(stderr, "Error\n"), 1;
    
    char **map = calloc(h , sizeof(char *));
    if(!map)
    return fprintf(stderr, "Error\n"), 1;
    int w = 0;
    for(int j = 0; j < h; j++)
    {
        size_t len = 0;
        char *line = NULL;
        if(getline(&line, &len, fi) < 0)
        return fprintf(stderr, "Error\n"), 1;
        int l = sstrlen(line);
        if(l > 0 && line[l - 1] == '\n')
        line[--l] = '\0';
        if(!w)
        w = l;
        if(w != l)
            return fprintf(stderr, "Error\n"), 1;
        map[j] = line;
    }
    
    if(fi != stdin)
    fclose(fi);
    int **db = calloc(h + 1, sizeof(int *));
    for(int j = 0; j <= h; j++)
    {
        db[j] = calloc(w + 1, sizeof(int));
    }
    square s = {0, 0, 0};
    for(int j = 0; j < h; j++)
    {
        for(int i = 0; i < w; i++)
        {   
            if(map[j][i] == e)
            {
                db[j + 1][i + 1] = 1 + min3(db[j][i + 1], db[j + 1][i], db[j][i]);
                if(db[j + 1][i + 1] > s.size)
                s = (square){j, i, db[j + 1][i + 1]};
            }
            else if(map[j][i] != o)
                return fprintf(stderr, "Error\n"), 1;
        }
    }

    for(int j = s.y - s.size + 1 ; j <= s.y; j++)
    {
        for(int i = s.x - s.size + 1; i <= s.x; i++)
        {
            map[j][i] = f;
        }
    }

    for(int j = 0; j < h; j++)
    {
        printf("%s\n", map[j]);
        free(map[j]);
    }
    free(map);
    for(int j = 0; j <= h; j++)
    {
        free(db[j]);
    }
    free(db);

    return 0;
}