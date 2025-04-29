#ifndef LIY2QUANT_H
#define LIY2QUANT_H

#include <math.h>

struct liy2qResults {
	float *uniqueverts;
	int uniquecount;
	int vertcount;
	int *vertidx;
};

int l2q_close(float a, float b) {
	return fabs(a - b) < 0.0001f;
}

struct liy2qResults liy2q_QuantTripleFloatArr(float *fullArray, int vertcount) {
	struct liy2qResults out;

	float *fullsizeuniquetriples = malloc(vertcount * 2 * sizeof(float));
	out.uniquecount = 0;
	for(int i = 0; i < vertcount * 2; i++) { fullsizeuniquetriples[i] = INFINITY; }
	for(int i = 0; i < vertcount; i++) { //Create array with uniques
		int matches = 0;
		for(int j = 0; j < vertcount; j++) {
			if(l2q_close(fullArray[i*2], fullsizeuniquetriples[j*2]) && l2q_close(fullArray[(i*2)+1], fullsizeuniquetriples[(j*2)+1])) {
				matches++;
			}
		}
		if(matches == 0) {
			fullsizeuniquetriples[(out.uniquecount*2)  ] = fullArray[(i*2)  ];
			fullsizeuniquetriples[(out.uniquecount*2)+1] = fullArray[(i*2)+1];
			out.uniquecount++;
		}
	}

	out.vertidx = malloc(vertcount * sizeof(float) * 3); //to reiterate each index goes to 2 vert f22s

	for(int i = 0; i < vertcount; i++) {
		for(int j = 0; j < out.uniquecount; j++) {
			if(l2q_close(fullArray[i*2], fullsizeuniquetriples[j*2]) && l2q_close(fullArray[(i*2)+1], fullsizeuniquetriples[(j*2)+1])) {
				out.vertidx[i] = j;
				break;
			}
		}
	}
	out.uniqueverts = malloc(out.uniquecount * sizeof(float) * 2);
	for(int i = 0; i < out.uniquecount * 2; i++) {
		out.uniqueverts[i] = fullsizeuniquetriples[i];
	}
	
	out.vertcount = vertcount;

	return out;
}

void freeliy2qResults(struct liy2qResults *a) {
	free(a->uniqueverts);
	free(a->vertidx);
}

#endif