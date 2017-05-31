typedef struct node node;
typedef node* indextree;

struct node{
	TInfo* pivot;
	TInfo* data;
	int size;
	indextree left;
	indextree right;
};

// crea un nuovo nodo per l'albero degli indici
// ritorna il puntatore al nodo
indextree newindextree(TInfo a[], int n){
  if (n < 1) return NULL; //indica una foglia senza dati
	node* new;
	new = (node *) malloc(sizeof(node));
	new->pivot = NULL;
	new->data = a;
	new->size = n;
	new->left = NULL;
	new->right = NULL;
	return new;
}

// Ricerca l'elemento x nel vettore indicizzato dall'albero t.
// RITORNA: il puntatore all'elemento sul vettore (NULL se assente).
// POST: - L'albero degli indici ha un nuovo pivot.
//       - Il vettore viene partizionato.
int* sorch (indextree t, TInfo x){

  if (t == NULL) return NULL; // foglia senza dati ferma la ricorsione

  // siamo su una foglia (il blocco deve ancora essere partizionato)
	if (t->pivot == NULL){

		TInfo pivot = t->data[0]; //scegliamo il primo elemento come pivot

    // sapere se l'elemento cercato sia maggiore o minore del pivot ci
    // permette di ridurre i confronti necessari alla ricerca lineare
		int smaller = less(x , pivot);

		TInfo* found = NULL; //puntatore all'eventuale elemento trovato

    // il seguente ciclo è identico a quello per il partizionamento del
    // quicksort, con l'aggiunta di confronti per la ricerca di x
		int k = 1;
		for(int i = 1; i < t->size; i++){
			if (less(t->data[i], pivot)){
				swap(&t->data[i], &t->data[k++]);
			  if(smaller)
				  if(equal(t->data[k-1], x))
					  found = &t->data[k-1];
      }
      if (!smaller)
				if(equal(t->data[i], x))
					found = &t->data[i];
		}
		swap(&t->data[0], &t->data[k-1]); // posiziona il pivot come separatore
    t->pivot = &t->data[k-1]; // memorizza il puntatore al pivot sul nodo

    //assegnazione delle partizioni a due nuove foglie
    t->left = newindextree(t->data, k-1);
    t->right = newindextree(&t->data[k], t->size - k);

    // devono essere aggiunti due controlli aggiuntivi:
    // 1 - in caso l'elemento cercato coincida con il pivot
		if(equal(pivot, x))
			found = t->pivot;
    // 2 - in caso l'elemento cercato fosse stato scambiato col pivot
		else if (found == t->pivot)
			found = &t->data[0];

		return found;
	}

  //ferma la ricorsione se l'elemento cercato coincide col pivot
  if (equal(x, *(t->pivot)))
  	return t->pivot;

  //divide et impera
	if (less(x, *(t->pivot)))
    return sorch(t->left, x);
  else
    return sorch(t->right, x);
}
