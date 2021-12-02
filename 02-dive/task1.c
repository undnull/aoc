#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    FILE *fp;
    long arg, vec[2];
    char cmd[32], line[128];

    fp = fopen("./input", "r");
    arg = vec[0] = vec[1] = 0;

    while(fgets(line, sizeof(line), fp)) {
        sscanf(line, "%31s %ld", cmd, &arg);
        if(!strcmp(cmd, "forward")) vec[0] += arg;
        if(!strcmp(cmd, "down")) vec[1] += arg;
        if(!strcmp(cmd, "up")) vec[1] -= arg;
    }

    printf("VEC: [%ld %ld], %ld\n", vec[0], vec[1], vec[0] * vec[1]);

    fclose(fp);

    return 0;
}
