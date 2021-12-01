#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    FILE *fp;
    char line[16];
    int ns, pv, cv;

    fp = fopen("./input", "r");
    ns = 0;
    pv = cv = -1;

    while(fgets(line, sizeof(line), fp)) {
        cv = atoi(line);

        if(pv != -1) {
            if(cv > pv)
                ns++;
            printf("PV: %04d, CV: %04d\n", pv, cv);
        }

        pv = cv;
    }

    printf("NS: %d\n", ns);

    fclose(fp);

    return 0;
}
