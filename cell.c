/*
  @file cell.c
  @brief Implements cell information structure and methods
*/
#include <stdlib.h>
#include <assert.h>
#include "cell.h"
#include "ansicolors.h"

//static const int AMOUNT_OF_ITEMS = 3 ;

#define ANSI_SHOT ANSI_RED_BG
#define ANSI_NORMAL ANSI_WHITE

cell_t cell_from_file(FILE* file)
{
    cell_t cell;
    char symbol;
    int k_status;
    unsigned int round;

    int res = fscanf(file, " [%c %d %u]", &symbol, &k_status, &round);
    if (res != 3) {
        fprintf(stderr, "Error reading cell data.\n");
        exit(EXIT_FAILURE);
    }
    /* COMPLETARDO: Lectura de datos de la celda */
    if (symbol == 'w') {
        cell.content = water;
    } else if (symbol=='s') {
        cell.content = ship;
    } else {
    /* COMPLETARDO*/
        fprintf(stderr, "Invalid cell content: %c\n", symbol);
        exit(EXIT_FAILURE);
    }
    if (k_status == 0) {
    /* COMPLETARDO*/
        cell.status = untouched;
    /* COMPLETARDO*/
    } else if (k_status == 1) {
        cell.status = hit;
    } else {
        fprintf(stderr, "Invalid cell status: %d\n", k_status);
        exit(EXIT_FAILURE);
    }
    cell.round = round;
    return cell;
}

void cell_dump(cell_t cell) {
    printf("%-5s [%-9s] (round %2d)", cell.content==water? "water":
                                      cell.content==ship ? "ship":
                                                           "?????", 
                                      cell.status==untouched ? "untouched":
                                      cell.status==hit       ? "hit!":
                                                               "?????????", 
                                      cell.round);
    printf(" | raw content: (%d,%d,%u) ", cell.content, cell.status, cell.round);
}

void cell_draw(cell_t cell, unsigned int round) {
    assert((cell.content==water || cell.content==ship) &&
           (cell.status==untouched || cell.status==hit));
    if (cell.status==untouched || cell.round > round) {
        printf(ANSI_NORMAL "%c", cell.content==water?' ':'#');
    } else {
        printf(ANSI_SHOT "%c", cell.content==water?' ':'#');
    }
}

