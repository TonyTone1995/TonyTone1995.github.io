#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <unistd.h>

void place_queen(int,int,int , int []);
int check_rows(int, int, int[]);
int check_diagonals(int, int, int []);
void initialize_array(int, int []);
void printArray(int,int ,int []);

int Solutions;

#define MASTER  0
#define TAG     0

int main (int argc, char *argv[]) {
  int k = 0;
  if (argc != 2) {
    fprintf (stderr, "need a k for K Queens Problem!!!!\n");
    exit(-1);
  }
  int my_rank, num_nodes, source;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &num_nodes);
  k = atoi (argv[1]);


  int solution[k];
  //int start = 0;



  if (my_rank != MASTER) {

      solution[0] = my_rank;
      place_queen(k, 1, my_rank,solution );

      MPI_Send(&Solutions, 1, MPI_INT, MASTER, 0, MPI_COMM_WORLD);
  }
  else {
 //printf("Hey, I'm the Master and my rank %d, adding all work\n", my_rank);
      //sum = psum


      for (source = 1; source < num_nodes; source++) {
          int response;
          MPI_Recv(&response, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
          printf("Process %d computed %d solutions\n", source, response);
          Solutions += response;

          //printf("PRINTING ARRAY\n")
        //  printArray(k, solution);
          printf("--------------------------------\n");

      }
      // PI = sum of 4 quadrants of unit circle
    printf("Total Number of Solutions %d\n", Solutions);
  }

  MPI_Finalize();
  return 0;

}



void place_queen(int k, int col, int process, int * solution)
{
//  srand(time(NULL));

  if (k == col)
  {

    Solutions++;

  }
  else{
    solution[0] = process;
    for(int row =  1; row <= k; row++)
    {
    //
    // check if queen can be placed safely
      //printf("Row %d\n", row);
      if(check_rows(row, col,solution) == 0 && check_diagonals(row, col, solution) == 0)
      {
      //place queen on this row
        solution[col] = row;

        place_queen (k,col+1, process,solution);

      }//end inner if

    }//end loop
  }
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
void printArray(int k,int process, int * array){
  printf("PROCESS %d [", process);
  for (int i = 0; i < k; i++){
    printf("%d ", array[i]);
  }
  printf("]\n");

}
