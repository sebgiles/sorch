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
// forza l'inizializzazione dei campi "data" e "n" per permettere la futura
// indicizzazione
// ritorna il puntatore al nodo
indextree newindextree(TInfo a[], int n){
  if (n < 1) return NULL; //impedisce la creazione di foglie senza dati
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
// Ritorna il puntatore all'elemento sul vettore (NULL se assente).
// La ricerca procede ricorsivamente facendo uso dei pivot dell'albero fino ad
// arrivarne ad una foglia, a questo punto la ricerca diventa lineare e
// il blocco interessato viene partizionato simultaneamente usando il primo
// elemento come pivot.
// POST: - L'albero degli indici ha un nuovo pivot.
//       - Il vettore viene parzialmente riordinato.
int* sorch (indextree t, TInfo x){

  // ferma la ricorsione alle foglie
  if (t == NULL) return NULL;

  // pivot non ancora assegnato indica che siamo su una foglia
	if (t->pivot == NULL){

    //scegliamo il primo elemento come pivot
		TInfo pivot = t->data[0];

    // sapere se l'elemento cercato è maggiore o minore del pivot ci permette
    // di ridurre i confronti necessari alla ricerca lineare
		int smaller = less(x , pivot);

    // per conservare un puntatore all'eventuale elemento trovato
		TInfo* found = NULL;

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
    // posiziona il pivot come separatore
		swap(&t->data[0], &t->data[k-1]);

    // assegna i valori sul nuovo nodo dell'albero degli indici
    t->pivot = &t->data[k-1];
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

  //ricorsione
	if (less(x, *(t->pivot)))
    return sorch(t->left, x);
  else
    return sorch(t->right, x);

}
