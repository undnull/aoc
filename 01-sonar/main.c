#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WINDOW_SIZE 3

int main(void)
{
    FILE *fp;
    char line[16];
    int history[3];
    int ns, cv, id, ws1, ws2;

    fp = fopen("./input", "r");
    history[0] = history[1] = history[2] = -1;
    ns = cv = id = 0;

    while(fgets(line, sizeof(line), fp)) {
        cv = atoi(line);

        if(++id >= 4) {
            ws1 = history[2] + history[1] + history[0];
            ws2 = history[1] + history[0] + cv;
            if(ws2 > ws1)
                ns++;
            printf("WS1: %04d, WS2: %04d\n", ws1, ws2);
        }

        /* H0,H1 -> H1,H2 */
        history[2] = history[1];
        history[1] = history[0];
        history[0] = cv;
    }

    printf("ns: %d\n", ns);

    fclose(fp);

    return 0;
}
