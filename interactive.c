#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef int TInfo;
#include "tools.h"
#include "indexer.h"

/*========================== MAIN ==================================*/
int main(int argc, char *argv[]) {
  int n;
  if(argc >= 2)
    n = atoi(argv[1]);
  else
    n = 100001;

  int* v1 = malloc(n*sizeof(int));
  int* v2 = malloc(n*sizeof(int));
  int* v3 = malloc(n*sizeof(int));

  sequence(v1, n);
  int seed = time(NULL);
  srand(seed);
  shuffle(v1, n);
  memcpy(v2, v1, n*sizeof(int));
  memcpy(v3, v1, n*sizeof(int));

  printf("Dataset contains integers 0 - %d.\t", n-1);
  printf("Seed = 0x%x\n", seed);

  printf("TASK\t\tBINARY\t\tLINEAR\t\tSORCH\n");
  printf("preparation\n\t\t");

  tic();
  quicksort(v1, n);
  toc();
  printf("\t\t");

  tic();
  toc();
  printf("\t\t");

  tic();
  indextree t = newindextree(v3,n);
  toc();
  printf("\tus\n");

	int q;
  int k = 1;
  long dt;
	while(1){
    printf("q(%d) = ",k++);
		scanf("%d", &q);
    printf("\t\t");
		if (q < 0) break;

    tic();
    binsearch(v1, n, q);
    dt = toc();
    printf("%ld\t\t",dt);

    tic();
    linsearch(v2, n, q);
    dt = toc();
    printf("%ld\t\t",dt);

    tic();
		sorch(t, q);
    dt=toc();
    printf("%ld\tus\n",dt);
	}
}
