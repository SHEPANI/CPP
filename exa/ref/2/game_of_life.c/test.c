#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int ac , char **av)
{
    if(ac != 4)
        return 0;
    int w  =  atoi(av[1]);
    int h  =  atoi(av[2]);
    int iter = atoi(av[3]);

    if(w <= 0 || h <= 0)
        return 0;
    char board[h][w];
    char tmp[h][w];

    for(int j = 0 ;j < h ; j++)
    {
        for(int i = 0 ;i < w ; i++)
        {
            board[j][i] = 0;
        }
    }
    
    int x = 0;
    int y = 0;
    char c;
    int pen = 0;

    while (read(0, &c, 1) > 0)
    {
        if(c == 'w' && y > 0) y--;
        else if(c == 's' && y < h - 1) y++;
        else if(c == 'a' && x > 0) x--;
        else if(c == 'd' && x < w - 1) x++;
        if(c == 'x') pen = !pen;
        if(pen)
            board[y][x] = 1;
    }
    
    while (iter)
    {
        for(int j = 0 ;j < h ; j++)
        {
            for(int i = 0 ;i < w ; i++)
            {
                int compt = 0;
                for(int dx = -1 ;dx <= 1 ; dx++)
                {
                    for(int dy = -1 ;dy <= 1 ; dy++)
                    {
                        if(dx == 0 && dy == 0) continue;
                        int ny = dy + j;
                        int nx = dx + i;
                        if(ny >= 0 && ny < h && nx >= 0 && nx < w)
                        {                        
                            if(board[ny][nx] == 1)
                                compt++;
                        }
                    }

                }
                if(board[j][i])
                    tmp[j][i] = (compt == 2 || compt == 3);
                else 
                    tmp[j][i] = (compt == 3);
            }
        }

        for(int j = 0 ;j < h ; j++)
        {
            for(int i = 0 ;i < w ; i++)
            {
                board[j][i] = tmp[j][i];
            }
        }
        iter--;
    }
    

        for(int j = 0 ;j < h ; j++)
        {
            for(int i = 0 ;i < w ; i++)
            {
                if(board[j][i])
                    putchar('0');
                else 
                    putchar(' ');

            }
            putchar('\n');
        }
        return 0;
}