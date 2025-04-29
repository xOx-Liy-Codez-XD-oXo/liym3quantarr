#ifndef LIY3QUANT_H
#define LIY3QUANT_H

#include <math.h>

struct liy3qResults {
	float *uniqueverts;
	int uniquecount;
	int vertcount;
	int *vertidx;
};

int l3q_close(float a, float b) {
	return fabs(a - b) < 0.0001f;
}

struct liy3qResults liy3q_QuantTripleFloatArr(float *fullArray, int vertcount) { 
	struct liy3qResults out;

	float *fullsizeuniquetriples = malloc(vertcount * 3 * sizeof(float));
	out.uniquecount = 0;
	for(int i = 0; i < vertcount * 3; i++) { fullsizeuniquetriples[i] = INFINITY; }
	for(int i = 0; i < vertcount; i++) { //Create array with uniques
		int matches = 0;
		for(int j = 0; j < vertcount; j++) {
			if(l3q_close(fullArray[i*3], fullsizeuniquetriples[j*3]) && l3q_close(fullArray[(i*3)+1], fullsizeuniquetriples[(j*3)+1]) && l3q_close(fullArray[(i*3)+2], fullsizeuniquetriples[(j*3)+2])) {
				matches++;
			}
		}
		if(matches == 0) {
			fullsizeuniquetriples[(out.uniquecount*3)  ] = fullArray[(i*3)  ];
			fullsizeuniquetriples[(out.uniquecount*3)+1] = fullArray[(i*3)+1];
			fullsizeuniquetriples[(out.uniquecount*3)+2] = fullArray[(i*3)+2];
			out.uniquecount++;
		}
	}

	out.vertidx = malloc(vertcount * sizeof(int) * 3); //to reiterate each index goes to 3 vert f32s

	for(int i = 0; i < vertcount; i++) {
		for(int j = 0; j < out.uniquecount; j++) {
			if(l3q_close(fullArray[i*3], fullsizeuniquetriples[j*3]) && l3q_close(fullArray[(i*3)+1], fullsizeuniquetriples[(j*3)+1]) && l3q_close(fullArray[(i*3)+2], fullsizeuniquetriples[(j*3)+2])) {
				out.vertidx[i] = j;
				break;
			}
		}
	}
	out.uniqueverts = malloc(out.uniquecount * sizeof(float) * 3);
	for(int i = 0; i < out.uniquecount * 3; i++) {
		out.uniqueverts[i] = fullsizeuniquetriples[i];
	}
	
	out.vertcount = vertcount;

	return out;
}

void freeliy3qResults(struct liy3qResults *a) {
	free(a->uniqueverts);
	free(a->vertidx);
}

#endif