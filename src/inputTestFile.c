/*this comment is the first line of the file */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


#define NUM_CHILD_THREADS 9

typedef int bool;

#define TRUE 1
#define FALSE 0

int sudokuPuzzle[9][9];
bool col[9];
bool row[9];
bool subGrid[9];

void *col_validator(void *param);
void *row_validator(void *param);
void *subgrid_validator(void *param);


/*This is a single line comment*/
typedef struct  {
    int topRow;
    int bottomRow;
    int leftColumn;
    int rightColumn;
    int iValue;
} run_param;

/* this comment appears on the same line before code */ int main(int argc, char *argv[])
{

    FILE *fp;
    int i;
    int j;
    bool valid = TRUE; /* this comment appears on the same line after code */

    pthread_t tid_column[NUM_CHILD_THREADS];
    pthread_t tid_row[NUM_CHILD_THREADS];
    pthread_t tid_subgrid[NUM_CHILD_THREADS];
    pthread_attr_t attr[NUM_CHILD_THREADS];
    run_param col_thrParam[NUM_CHILD_THREADS];
    run_param row_thrParam[NUM_CHILD_THREADS];
    run_param subgrid_thrParam[NUM_CHILD_THREADS];

    /* This is
    a multiline comment
    made up of three lines*/
    fp = fopen("SudokuPuzzle.txt", "r");
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            fscanf(fp, "%d", &sudokuPuzzle[i][j]);
        }
    }
    /*
    this is a multiline comment that comments out a block of code
    for(i = 0; i < 9; i++) {
        for(j =0 ; j < 9; j++) {
            printf("%d\t", sudokuPuzzle[i][j]);
         }
    printf("\n");
  }
  */
}
/* this comment is the last line of the file, in all there are 7 comments in this file */
