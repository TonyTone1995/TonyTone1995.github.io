#include <stdio.h>
#include <math.h>
#include <stdlib.h>


void place_queen(int,int, int []);
int check_rows(int, int, int[]);
int check_diagonals(int, int, int []);
void initialize_array(int, int []);
void printArray(int ,int []);

int Solutions;

int main (int argc, char *argv[]) {


  int k = 0;
  if (argc != 2) {
    fprintf (stderr, "need a k for K Queens Problem!!!!\n");
    exit(-1);
  }

  k = atoi (argv[1]);

  int solution[k];
  //int start = 0;


  initialize_array(k, solution);
  //solution[0] = 8;

  place_queen(k, 0, solution);
  printf("Found %d\n", Solutions);
}



void place_queen(int k, int col, int * solution)
{

  if (k == col)
  {
    printArray(k,solution);
    Solutions++;

  }

    for(int row=1; row <= k; row++)
    {
    // check if queen can be placed safely
      //solution[0] = 8;
      if(check_rows(row, col,solution) == 0 && check_diagonals(row, col, solution) == 0)
      {
      //place queen on this row
        solution[col] = row;
      // try rest of problem
        place_queen (k,col+1, solution);

      }//end inner if

    }//end loop
}//end method

//will take a row and column and see if a queen is in danger
int check_rows(int row, int col, int * solution){
  //queens cant exist on the same row
  for(int i = 0; i < col; i ++){
    if(solution[i] == row ){
      return -1;
    }
  }
  return 0;
}


int check_diagonals(int row, int col, int * solution){
  //values we will be examining
  int danger1;
  int danger2;


  for(int i = 0; i < col; i ++){
    danger1 = solution[i]+i; // diagonals from left side
    danger2 = i - solution[i]; //diagonals from rights side

    if(row + col  == danger1){ //left hand diagonals
      return -1;
    }
    if( col - row ==  danger2){ //right hand diagonals
      return -1;
    }
  }
  return 0;

}

//fill array with zeros
void initialize_array(int k, int * array){
  for (int i = 0; i < k; i++){
    array[i] = 0;
  }
}

//print array
void printArray(int k, int * array){
  printf("[");
  for (int i = 0; i < k; i++){
    printf("%d ", array[i]);
  }
  printf("]\n");

}
