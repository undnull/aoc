#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct table {
    unsigned int values[5][5];
    int status[5][5];
};

static int read_table(FILE *fp, struct table *t)
{
    int i;
    unsigned int *p;
    char line[64];

    /* skip the empty line */
    fgets(line, sizeof(line), fp);

    for(i = 0; i < 5; i++) {
        if(!fgets(line, sizeof(line), fp))
            return 0;
        p = t->values[i];
        sscanf(line, "%u%u%u%u%u", &p[0], &p[1], &p[2], &p[3], &p[4]);
        memset(t->status[i], 0, sizeof(t->status[i]));
    }

    return 1;
}

static unsigned int draw_number(unsigned int n, struct table *t)
{
    unsigned int i, j, bingo;

    for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            if(t->values[i][j] != n)
                continue;
            t->status[i][j] = 1;
        }
    }

    /* go vertically */
    for(i = 0; i < 5; i++) {
        bingo = 1;
        for(j = 0; j < 5; j++)
            bingo = bingo && t->status[i][j];
        if(!bingo)
            continue;
        goto table_won;
    }

    /* go horizontally */
    for(j = 0; j < 5; j++) {
        bingo = 1;
        for(i = 0; i < 5; i++)
            bingo = bingo && t->status[i][j];
        if(!bingo)
            continue;
        goto table_won;
    }

    return 0;

table_won:
    for(i = bingo = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            if(t->status[i][j])
                continue;
            bingo += t->values[i][j];
        }
    }

    return bingo * n;
}

int main(void)
{
    FILE *fp;
    char numbers[512], tmp[32];
    const char *np;
    struct table dummy;
    struct table *tables;
    unsigned int n, i, v, bingo;
    int nc;

    fp = fopen("./input", "r");

    fgets(numbers, sizeof(numbers), fp);
    for(n = 0; read_table(fp, &dummy); n++);
    fseek(fp, 0, SEEK_SET);

    tables = calloc(n, sizeof(struct table));
    fgets(numbers, sizeof(numbers), fp);
    for(i = 0; read_table(fp, tables + i); i++);
    fclose(fp);

    np = numbers;
    while(sscanf(np, "%31[^, \t\n],%n", tmp, &nc) >= 1) {
        np += nc;
        v = (unsigned int)strtoul(tmp, NULL, 10);
        for(i = 0; i < n; i++) {
            if((bingo = draw_number(v, tables + i))) {
                printf("Table %u won\n", i);
                printf("RES: %u\n", bingo);
                goto done;
            }
        }
    }
    
done:
    free(tables);

    return 0;
}
