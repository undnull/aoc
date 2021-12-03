#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    int i;
    FILE *fp;
    unsigned int bit, count, gamma, eps;
    unsigned int bits[12] = { 0 };
    char line[16] = { 0 };

    fp = fopen("./input", "r");
    count = gamma = eps = 0;
    memset(bits, 0, sizeof(bits));

    while(fgets(line, sizeof(line), fp)) {
        for(i = 0; i < 12; i++)
            bits[i] += line[i] - '0';
        count++;
    }

    for(i = 0; i < 12; i++)
        *((count - bits[i] < bits[i]) ? &gamma : &eps) |= 1 << (11 - i);
    printf("GAMMA: %u, EPS: %u\n", gamma, eps);
    printf("RES: %u\n", gamma * eps);

    fclose(fp);

    return 0;
}
