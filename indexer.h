typedef struct node node;
typedef node* indextree;

struct node{
	TInfo* pivot;
	TInfo* data;
	int size;
	indextree left;
	indextree right;
};

indextree newindextree(TInfo a[], int n){
  if (n < 1) return NULL;
	node* new;
	new = (node *) malloc(sizeof(node));
	new->pivot = NULL;
	new->data = a;
	new->size = n;
	new->left = NULL;
	new->right = NULL;
	return new;
}

int* sorch (indextree t, TInfo x){
  if (t == NULL) return NULL;

	if (t->pivot == NULL){
		TInfo pivot = t->data[0];
		int smaller = less(x , pivot);
		TInfo* found = NULL;
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

		swap(&t->data[0], &t->data[k-1]);
    t->pivot = &t->data[k-1];
    t->left = newindextree(t->data, k-1);
    t->right = newindextree(&t->data[k], t->size - k);

		if(equal(pivot, x))
			found = t->pivot;
		else if (found == t->pivot)
			found = &t->data[0];
		return found;
	}
  if (equal(x, *(t->pivot)))
  	return t->pivot;
	if (less(x, *(t->pivot)))
    return sorch(t->left, x);
  else
    return sorch(t->right, x);

}
