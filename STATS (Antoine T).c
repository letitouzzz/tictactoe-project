#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STATS_FILE "morpion_stats.txt"

#define P1_INDEX 0
#define P2_INDEX 1
#define AI_INDEX 2

typedef struct {
    char name[20];
    int wins;
    int losses;
    int draws; // Matchs nuls
} PlayerStats;


