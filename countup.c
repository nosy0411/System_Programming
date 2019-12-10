void countup(links* x, char w[20]) {
	node* n = x->head;
	if (n == NULL) {
		insrt(x, w);
		return;
	}
	while (n != NULL) {
		if (strcmp(n->word, w) == 0) {
			n->count++;
			int i = n->count;
			node* n2 = n;
		ii:
			if (n->prv != NULL && i > n->prv->count) {
				n = n->prv;
				goto ii;
			}
			else {
				if (n == n2)return;
				strswap(n->word, n2->word);
				n->count++;
				n2->count--;
				return;
			}
		}
		else n = n->nxt;
	}
	insrt(x, w);
}


char *Strcat(char *d, char *s){

	while(*d!='\0'){
		d++;
	}
	while(*s!='\0') { 
		*d++ = *s++; 
	}
	*d='\0';
	return d;
}