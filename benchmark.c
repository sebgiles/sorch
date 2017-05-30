#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef int TInfo;
#include "tools.h"
#include "indexer.h"

/*========================== MAIN ==================================*/
int main(int argc, char *argv[]) {
  if(argc < 5)
    return -1;
  int n = atoi(argv[1]);  // dimensione del campione
  int qn = atoi(argv[2]); // numero di ricerche
  int qw = atoi(argv[3]); // larghezza intervallo interessato
  int rip = atoi(argv[4]);// ripetizioni
  double *t1, *t2, *t3;
  t1 = calloc(qn+1, sizeof(double));
  t2 = calloc(qn+1, sizeof(double));
  t3 = calloc(qn+1, sizeof(double));

  int qmin = (n-qw)/2;
  int seed = time(NULL);
  srand(seed);

  int* v1 = malloc(n*sizeof(int));
  int* v2 = malloc(n*sizeof(int));
  int* v3 = malloc(n*sizeof(int));

  for (int j = 0; j < rip; j ++){
    sequence(v1, n);
    shuffle(v1, n);
    memcpy(v2, v1, n*sizeof(int));
    memcpy(v3, v1, n*sizeof(int));
    tic();
    t1[0] += toc();

    tic();
    quicksort(v2, n);
    t2[0] += toc();

    tic();
    indextree t = newindextree(v3,n);
    t3[0] += toc();

    int q;
  	for(int i = 1; i <= qn; i ++){
      q = rand() % qw + qmin;

      tic();
      linsearch(v1, n, q);
      t1[i] += toc();

      tic();
      binsearch(v2, n, q);
      t2[i] += toc();

      tic();
  		sorch(t, q);
      t3[i] += toc();
  	}
  }
  t1[0] /= rip;
  t2[0] /= rip;
  t3[0] /= rip;
  for(int j = 1; j <= qn; j ++){
    t1[j] = t1[j]/rip + t1[j-1];
    t2[j] = t2[j]/rip + t2[j-1];
    t3[j] = t3[j]/rip + t3[j-1];
  }
  for(int j = 0; j <= qn; j ++){
    printf("%.1f;%.1f;%.1f\n",t1[j], t2[j], t3[j]);
  }
}
