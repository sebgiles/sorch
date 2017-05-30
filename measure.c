#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int TInfo;
#include "tools.h"
#include "indexer.h"

/*========================== MAIN ==================================*/
int main(int argc, char *argv[]) {
  if(argc < 2) {
    printf("Not enough arguments\n");
    return -1;
  }
  int max;
  if(argc == 3)
    max = atoi(argv[2]);
  else
    max = RAND_MAX;
  //srand(time(NULL));
  //srand(0);
	int n = atoi(argv[1]);
  int* v = malloc(n*sizeof(int));
  randomize(v, n, max);
  print(v, n);
	indextree t = newindextree(v,n);
	int x;
	int* f;
	while(1){
    printf("What are you looking for? ");
		scanf("%d", &x);
		if (x==-1) break;
		f = sorch(t, x);
		if(f)
			printf("Found \"%d\" at %x\n",*f, (int)f);
		else
			printf("Not found.\n");
	}
}
