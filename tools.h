#ifndef __TOOLS_H__
#define __TOOLS_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int less(int a, int b){
  return a < b;
}

int equal(int a, int b){
  return a == b;
}

char* str(int a){
  char* des = malloc(12);
  sprintf(des, "%d", a);
  return des;
}

void progress(i, n){
  if (n >= 100){
    if (i % (n / 100) == 0){
      printf("%02i%%\b\b\b", i / (n / 100));
      fflush(stdout);
    }
  }
}

void clearline(){
  printf("\r");
  for(int i = 0; i < 40; i ++)
    printf(" ");
  printf("\r");
  fflush(stdout);
}

void print(TInfo* v, int n){
  char* des;
	for (int i = 0; i < n; i++) {
    des = str(v[i]);
		printf("%s ", des);
    free(des);
	}
	printf("\n");
}

// Scambia il contenuto puntato da a con quello puntato da b
void swap(TInfo *a, TInfo *b) {
	TInfo temp=*a;
	*a=*b;
	*b=temp;
}

/* Suddivide l’array a in tre parti:
 * - nella prima ci sono tutti elementi minori del pivot;
 * - nella seconda c’e’ solo il pivot;
 * - nella terza ci sono tutti elementi maggiori o uguali del pivot.
 * Come pivot viene scelto il primo elemento dell’array iniziale.
 * VALORE DI RITORNO
 * L’indice della parte centrale (che contiene il solo pivot)
 * PRE
 * L’array contiene almeno un elemento */
int partition(TInfo a[], int n) {
	int k = 1;
	for(int i = 1; i<n; i++)
		if (less(a[i], a[0]))
			swap(&a[i], &a[k++]);
	swap(&a[0], &a[k-1]);
	return k-1;
}

/* Ordina un array con il Quick Sort */
void quicksort(TInfo a[], int n) {
	int k;
	if (n<2)
		return;
	k = partition(a, n);
	quicksort(a, k);
	quicksort(a+k+1, n-k-1);
}

/* Ricerca lineare.
 * Restituisce l’indirizzo in memoria di un elemento di a che sia equal a x,
 * o NULL se l’elemento non viene trovato. */
int* linsearch(int a[], int n, int el){
	for (int i = 0; i < n; i++) {
		if(equal(a[i] , el)){
			return a + i;
		}
	}
	return NULL;
}

/* Ricerca dicotomica.
 * Restituisce l’indirizzo in memoria di un elemento di a che sia equal a x,
 * o NULL se l’elemento non viene trovato.
 * PRE: l’array a è ordinato rispetto alla relazione less */
int* binsearch (TInfo a[], int n, TInfo x) {
	int first = 0;
	int last = n - 1;
	int cut = (first + last) / 2;
	while (first <= last) {
		if (equal(a[cut], x))
			return &a[cut];
		else if (less(a[cut], x))
			first = cut + 1;
		else
			last = cut - 1;
		cut = (first + last) / 2;
	}
	return NULL;
}

// Assegna valori casuali ai primi n elementi del vettore r
void randomize(int* r, int n, int max){
  printf("Generating numbers ... ");
  for (int i = 0; i < n; i ++){
    r[i]=rand()%max;
    progress(i + 1, n);
  }
  clearline();
}

void shuffle(int* v, int n){
  printf("Generating range ... ");
  fflush(stdout);
  for (int i = 0; i < n; i++) {
    v[i] = i;
    progress(i + 1,n);
  }
  printf("\rShuffling numbers ... ");
  fflush(stdout);
  int temp;
  for (int i = n - 1; i >= 0; --i){
      int j = rand() % (i+1);
      temp = v[i];
      v[i] = v[j];
      v[j] = temp;
      progress(n - i, n);
  }
  clearline();
}

#endif
