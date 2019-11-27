#include "leader.h"

#ifdef _LEADER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "util.h"

void addEntry(char const * fname, char const *name, int level, double time) {
    static struct entry newer;
    int i,j;
    FILE * file = fopen(fname, "r");
    len = 0;
    // fill top list
    if (file != NULL) {
        i = 0;
        while (!feof(file)) {
            fscanf(file, "%d | %s | %d | %lf\n", &j, top[i].name, &(top[i].level), &(top[i].time));
            len++;
            i++;

        }
        fclose(file);
    }
    strcpy(newer.name, name);
    newer.level = level;
    newer.time = time;
    i = len;
    while (i > 0 && newer.level > top[i].level)
        i--;
    while (i > 0 && newer.time < top[i].time)
        i--;
    if (i < MAX_LEADER) {
        if (len < MAX_LEADER) len++;
        j = len-1;
        while (j > i) {
            top[j] = top[j-1];
            j--;
        }
        top[i] = newer;
    }
}

void printEntry(char const * fname) {
    FILE * file = fopen(fname, "w");
    int i, max = 0;
    if (file != NULL) {
        for (i = 0; i < len; i++) {
            if (strlen(top[i].name) > max)
                max = strlen(top[i].name);
        }
        for (i = 0; i < len; i++) {
            fprintf(file, "%2d | %*s | %3d | %3.2lf\n", i+1, max, top[i].name, top[i].level, top[i].time);
        }
        fclose(file);
    } else {
        ERROR("error opening file");
    }
}

#endif
