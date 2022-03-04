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


/*structure for passing data to threads*/
typedef struct  {
    int topRow;
    int bottomRow;
    int leftColumn;
    int rightColumn;
    int iValue;
} run_param;

int main(int argc, char *argv[])
{
  
    FILE *fp;
    int i;
    int j;
    bool valid = TRUE;
    
    pthread_t tid_column[NUM_CHILD_THREADS];
    pthread_t tid_row[NUM_CHILD_THREADS];
    pthread_t tid_subgrid[NUM_CHILD_THREADS];
    pthread_attr_t attr[NUM_CHILD_THREADS];
    run_param col_thrParam[NUM_CHILD_THREADS];
    run_param row_thrParam[NUM_CHILD_THREADS];
    run_param subgrid_thrParam[NUM_CHILD_THREADS];
    
    /* scan and print sudoku file */
    fp = fopen("SudokuPuzzle.txt", "r");
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            fscanf(fp, "%d", &sudokuPuzzle[i][j]);
        }
    }
    
    for(i = 0; i < 9; i++) {
        for(j =0 ; j < 9; j++) {
            printf("%d\t", sudokuPuzzle[i][j]);
         }   
    printf("\n");
    }
    
    /************************************************/
    
    printf("************************Columns************************\n");
    
    /* assign paramters for column validation */
    for (i = 0; i < NUM_CHILD_THREADS; i++) {  
        col_thrParam[i].topRow    = 0;  
        col_thrParam[i].bottomRow = 8;  
        col_thrParam[i].leftColumn = i;
        col_thrParam[i].rightColumn = i;
    }
    
    
    /* get default attributes */
    for (i = 0; i < NUM_CHILD_THREADS; i++) {
        pthread_attr_init(&(attr[i]));
    }
    
    /* create child threads to validate columns */
    for (i = 0; i < NUM_CHILD_THREADS; i++) {
        pthread_create(&(tid_column[i]), &(attr[i]), col_validator, &(col_thrParam[i]));
    }
    
    /* wait for thread to exit */
    for (i = 0; i < NUM_CHILD_THREADS; i++) {
        pthread_join(tid_column[i], NULL);
    }
    
    /************************************************/
    
    printf("**************************Rows**************************\n");

      /* assign paramters for row validation */
    for (i = 0; i < NUM_CHILD_THREADS; i++) {  
        row_thrParam[i].topRow    = i;  
        row_thrParam[i].bottomRow = i;  
        row_thrParam[i].leftColumn = 0;
        row_thrParam[i].rightColumn = 8;
    }
    
    /* create child threads to validate rows */
    for (i = 0; i < NUM_CHILD_THREADS; i++) {
        pthread_create(&(tid_row[i]), &(attr[i]), row_validator, &(row_thrParam[i]));
    }
    
    /* wait for thread to exit */
    for (i = 0; i < NUM_CHILD_THREADS; i++) {
        pthread_join(tid_row[i], NULL);
    }
    
    /************************************************/
    
    printf("************************Subgrids************************\n");

    for (i = 0; i < NUM_CHILD_THREADS; i++) {
        subgrid_thrParam[i].iValue = i;
        if (i < 3){
            subgrid_thrParam[i].topRow     = 0;  
            subgrid_thrParam[i].bottomRow  = 2;  
        }
        else if (i > 2 && i < 6){
            subgrid_thrParam[i].topRow     = 3;  
            subgrid_thrParam[i].bottomRow  = 5;  
        }
        else if (i > 5 && i < 9){
            subgrid_thrParam[i].topRow     = 6;  
            subgrid_thrParam[i].bottomRow  = 8;  
        }
        
        if (i == 0 || i == 3 || i == 6){
            subgrid_thrParam[i].leftColumn = 0;
            subgrid_thrParam[i].rightColumn = 2;
        }
        else if (i == 1 || i == 4 || i == 7){
            subgrid_thrParam[i].leftColumn = 3;
            subgrid_thrParam[i].rightColumn = 5;
        }
        else if (i == 2 || i == 5 || i == 8){
            subgrid_thrParam[i].leftColumn = 6;
            subgrid_thrParam[i].rightColumn = 8;
        }
    }
    
    /* create child threads to validate subgrids */
    for (i = 0; i < NUM_CHILD_THREADS; i++) {
        pthread_create(&(tid_subgrid[i]), &(attr[i]), subgrid_validator, &(subgrid_thrParam[i]));
    }
    
    /* wait for thread to exit */
    for (i = 0; i < NUM_CHILD_THREADS; i++) {
        pthread_join(tid_subgrid[i], NULL);
    }
    
    for (i = 0; i < NUM_CHILD_THREADS; i++) {
        if (!col[i]){
            printf("Column: %lX\tinvalid\n", tid_column[i]);
        }
        else if(col[i]){
            printf("Column: %lX\tvalid\n", tid_column[i]);
        }
    }
    for (i = 0; i < NUM_CHILD_THREADS; i++) {
        if (!row[i]){
            printf("Row: %lX\tinvalid\n", tid_row[i]);
        }
        else if(row[i]){
            printf("Row: %lX\tvalid\n", tid_row[i]);
        }
    }
    for (i = 0; i < NUM_CHILD_THREADS; i++) {
        if (!subGrid[i]){
            printf("Subgrid: %lX\tinvalid\n", tid_subgrid[i]);
        }
        else if(subGrid[i]){
            printf("Subgrid: %lX\tvalid\n", tid_subgrid[i]);
        }
    }
    
    /*Check if puzzle is valid*/
    printf("*****************************\n");
    for (i = 0; i < NUM_CHILD_THREADS; i++) {
        if (!col[i] || !row[i] || !subGrid[i]){
            valid = FALSE;
        }
    }
    if (valid == TRUE){
        printf("Sudoku Puzzle: valid");
    }
    else {
        printf("Sudoku Puzzle: invalid");
    }
    
  /*
     for (int i = 0; i < 9; i++) {
        printf("[%x],", col[i]);
    }
    printf("\n");
    for (int i = 0; i < 9; i++) {
        printf("[%x],", row[i]);
    }
    printf("\n");
    for (int i = 0; i < 9; i++) {
        printf("[%x],", subGrid[i]);
    } */
    
}

void *col_validator(void *param){
    run_param *inP;
    int top, bottom, left, right, i;
    int digit;
    bool contains[10] = {FALSE};
    pthread_t self;
    
    self = pthread_self();
    inP = (run_param *)param;
    top = inP -> topRow;
    bottom = inP -> bottomRow;
    left = inP -> leftColumn;
    right = inP -> rightColumn;
    
    contains[0] = TRUE;
    
    for (i = 0; i < bottom + 1 ; i++) { /* this comment has text before it */
        digit = sudokuPuzzle[i][right];
        if (!contains[digit]){
            contains[digit] = TRUE;
        }
        else if (contains[digit] == TRUE){
            printf("%lX\tTRow:%d\tBRow:%d\tLCol:%d\tRcol:%d\tinvalid!\n",(unsigned long)self , top, bottom, left, right);
            col[right] = FALSE;
            pthread_exit(0);
        }
    }
    
    for (i = 0; i < 10 ; i++) {
        if (!contains[i]){
            col[right] = FALSE;
        }
        else {
            col[right] = TRUE;
        }
    }
    
    printf("%lX\tTRow:%d\tBRow:%d\tLCol:%d\tRcol:%d\tvalid!\n",(unsigned long)self , top, bottom, left, right);
}

void *row_validator(void *param){
    run_param *inP;
    int top, bottom, left, right, i;
    int digit;
    bool contains[10] = {FALSE};
    pthread_t self;
    
    self = pthread_self();
    inP = (run_param *)param;
    top = inP -> topRow;
    bottom = inP -> bottomRow;
    left = inP -> leftColumn;
    right = inP -> rightColumn;
    
    contains[0] = TRUE;
    
    for (i = 0; i < right + 1 ; i++) {
        digit = sudokuPuzzle[top][i];
        if (!contains[digit]){
            contains[digit] = TRUE;
        }
        else if (contains[digit] == TRUE){
            printf("%lX\tTRow:%d\tBRow:%d\tLCol:%d\tRcol:%d\tinvalid!\n",(unsigned long)self , top, bottom, left, right);
            row[top] = FALSE;
            pthread_exit(0);
        }
    }
    
    for (i = 0; i < 10 ; i++) {
        if (!contains[i]){
            row[top] = FALSE;
        }
        else {
            row[top] = TRUE;
        }
    }
    
    printf("%lX\tTRow:%d\tBRow:%d\tLCol:%d\tRcol:%d\tvalid!\n",(unsigned long)self , top, bottom, left, right);
}

void *subgrid_validator(void *param){
    run_param *inP;
    int top, bottom, left, right, i, j;
    int digit, iv;
    bool contains[10] = {FALSE};
    pthread_t self;
    
    self = pthread_self();
    inP = (run_param *)param;
    top = inP -> topRow;
    bottom = inP -> bottomRow;
    left = inP -> leftColumn;
    right = inP -> rightColumn;
    iv = inP -> iValue;
    
    contains[0] = TRUE;
    
    for (i = top; i < bottom + 1 ; i++) {
        for (j = left; j < right + 1; j++) {
            digit = sudokuPuzzle[i][j];
            if (!contains[digit]){
             contains[digit] = TRUE;
            }
            else if (contains[digit] == TRUE){
                printf("%lX\tTRow:%d\tBRow:%d\tLCol:%d\tRcol:%d\tinvalid!\n",
                    (unsigned long)self , top, bottom, left, right);
                if (bottom < 3 && right == 2)
                subGrid[iv] = FALSE;
                pthread_exit(0);
            }
        }
         
    }
    
    for (i = 0; i < 10 ; i++) {
        if (!contains[i]){
            subGrid[iv] = FALSE;
        }
        else {
            subGrid[iv] = TRUE;
        }
    }
    
    printf("%lX\tTRow:%d\tBRow:%d\tLCol:%d\tRcol:%d\tvalid!\n",(unsigned long)self , top, bottom, left, right);
}







