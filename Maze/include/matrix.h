#include <stdio.h>
#include <stdlib.h>

#ifndef _MATRIX_H
#define _MATRIX_H

/* In this file SS stand for 'Squared Simetric Sparse'
 * The SSSMatrix defined here is a squared simetric sparse
 * matrix that will be used in maze to process the
 * matrix operations.
 */

/* One single node, that is, non-zero cell, of the matrix */
struct _SSSMatrixNode;

/* The matrix structure itself */
struct _SSSMatrix;

typedef struct _SSSMatrixNode sssmatrix_node;
typedef struct _SSSMatrix sssmatrix;

/* Inializes matrix with given size */
extern void sssmatrix_init(sssmatrix *, int);

/* Sets m[i,j] = val */
extern void sssmatrix_set(sssmatrix*, int, int, int);

/* Gets the value of m[i,j] */
extern int sssmatrix_get(sssmatrix*, int, int);

#endif
