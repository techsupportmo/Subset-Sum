//  Mohammed Ahmed
//  1001655176
//  Lab 3
//  gcc lab3.c


#include <stdio.h>
#include <stdlib.h>

void readInput(int* n,int* m,int** S,int** C)
{
  // Loads all input and allocates space
  int i;

  scanf("%d",n);
  scanf("%d",m);

  *S=(int*) malloc((*n+1)*sizeof(int));

  

  //initializing c as a 2D array
  *C=calloc((*m+1)*(*n+1)*sizeof(int), sizeof(int));

  if (!(*S) || !(*C))
  {
    printf("malloc failed %d\n",__LINE__);
    exit(0);
  }

  (*S)[0]=0;                // Sentinel zero
  for (i=1;i<=*n;i++)
    scanf("%d",*S+i);


  




}

void subsetSum(int n,int m,int* S,int* C)
{
  int i,j,potentialSum,leftover;

  int card = 1;
  

  // Initialize table for DP
  *(C + (0 * (m + 1)) + 0) = 0;  // DP base case

  int fail = n + 1;


  //setting first column to fail (n+1)
  for(i = 1; i <= n; i++)
  {
    *(C + (i * (m+1)) + 0) = fail;

  }


  //setting first row to fail (n+1)
  for(j = 1; j <= m; j++)
  {
    *(C + (0 * (m+1)) + j) = fail;

  }




  for(card = 1; card <= n; card++)
  {
    // For each potential sum, determine the smallest index such
    // that its input value is in a subset to achieve that sum.
    for (potentialSum=1; potentialSum<=m; potentialSum ++)
    {
      for (j=1;j<=n;j++)
      {
        // To be achieved with other values
        leftover=potentialSum-S[j];

        //condition that checks 2d array
        //if (leftover>=0 && *(C + (j * (m + 1)) + potentialSum) < j)
        if(leftover >= 0 && C[ ((card-1) *(m+1)) + leftover] < j)
        {
          break; 
        }                 
                                  
      }
      //C[potentialSum]=j;
      //*(C + (j * (m + 1)) + potentialSum) = j;
      C[((card) *(m+1)) + potentialSum] = j;

    }
  }

  



  
}

void writeOutput(int n,int m,int* S,int* C)
{
  int i;

  //START OF OUTPUT -----------------------
  printf("m is %d\n", m);
  

  // Output the input set
  printf("  i   S\n");
  printf("-------\n");
  for (i=0;i<=n;i++)
    printf("%3d %3d\n",i,S[i]);


  //space
  printf("\n\n");



  //space
  printf("\n\n");

  //print table
  printf("   i   card  C\n");
  printf("-----------------\n");



  i = 0;
  int output = 0;
  int j = 0;

  //Prints C values in the table
  for(i = 0; i < m; i++)
  {
    for(j = 1; j <= n; j++)
    {

      output = *(C + (j * (m + 1)) + i);
      printf("%4d%5d%5d\n", i,j,output);

      
    }
  }

  //space
  printf("\n\n");

  int rowPos; //row position
  int colPos; //column position
  int CValue;  //C value (value inside of 2D Array)
  int SIValue;     //S sub i value (inside of the other array)

  //loop that outputs each solution
  for(i = 1; i <= n; i++)
  {
    // Output the backtrace
    if (*(C + (i * (m+1)) + m) == n + 1)
    {
      printf("No solution with %d elements\n", i);
      
    }
    else
    {
      printf("Solution with %d elements\n", i);
      

      //Starting values for variables
      //set row position to i
      rowPos = i;

      //set column position to last column (m)
      colPos = m;

      //CValue will be element inside of this index
      CValue = *(C + (rowPos * (m+1)) + colPos);



      //BACKTRACE TABLE
      printf("  i   S\n");
      printf("-------\n");

      //loops based on value of cardinality
      for(j = i; j > 0; j--)
      {
        
        //CValue will be element inside of this index
        CValue = *(C + (rowPos * (m+1)) + colPos);

        //extract the SI value from the other array (based on CValue)
        SIValue = S[CValue];

        //Print out our table entry (CValue and SIValue)
        printf("%3d%3d\n",CValue, SIValue);      

        //Subtract column position by the SIValue
        colPos = colPos - SIValue;

        //Move up a row by decrementing the row position
        rowPos = rowPos - 1;

  

      }


    } 
    
  }


  //space
  printf("\n\n");




}

int main()
{

int n;    // Size of input set
int m;    // Target value
int *S;   // Input set
int *C;   // Cost table

readInput(&n,&m,&S,&C);

subsetSum(n,m,S,C);

writeOutput(n,m,S,C);


free(S);
free(C);
}








