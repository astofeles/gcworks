#ifndef _LEADER_H
#define _LEADER_H

#include <stdio.h>

#define MAX_LEADER 10

struct entry {
    char name[128];
    int level;
    double time;
} top[MAX_LEADER];

int len;

extern void addEntry(char const *, char const *, int, double);

extern void printEntry(char const *);

#endif
