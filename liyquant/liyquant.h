#ifndef LIYQUANT_H
#define LIYQUANT_H

struct liyqResults {
	float *uniqueelements;
	int uniquecount;
	int *quantidx;
};

struct liyqResults liyq_Quantfloatarr(float *infloats, int numfloats) {
	struct liyqResults out;
	float *fullsizeuniqueelements = malloc(numfloats * sizeof(float));
	out.uniquecount = 0;
	for(int i = 0; i < numfloats; i++) { fullsizeuniqueelements[i] = INFINITY; }
	for(int i = 0; i < numfloats; i++) { //Create array with unique values
		int matches = 0;
		for(int j = 0; j < numfloats; j++) {
			if(infloats[i] == fullsizeuniqueelements[j]) {
				matches++;
			}
		}
		if(matches == 0) {
			fullsizeuniqueelements[out.uniquecount] = infloats[i];
			out.uniquecount++; 
		}
	}
	
	out.quantidx = malloc(numfloats * sizeof(float));
		
	for(int i = 0; i < numfloats; i++) {
		for(int j = 0; j < out.uniquecount; j++) {
			if(infloats[i] == fullsizeuniqueelements[j]) {
				out.quantidx[i] = j;
				break;
			}
		}
	}
	out.uniqueelements = malloc(out.uniquecount * sizeof(float));
	for(int i = 0; i < out.uniquecount; i++) {
		out.uniqueelements[i] = fullsizeuniqueelements[i];
	}
	return out;
}

void freeLiyqResults(struct liyqResults *in) {
	free(in->uniqueelements);
	free(in->quantidx);
}

#endif