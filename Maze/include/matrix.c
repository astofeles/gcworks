#include "matrix.h"

#ifdef _MATRIX_H

#include <stdio.h>
#include <stdlib.h>

struct _SSSMatrixNode {
    int value;      /* the cell value */
    int row;        /* the cell row in matrix */
    int column;     /* the cell column in matrix */
    struct _SSSMatrixNode * right;  /* link sparse matrix by row (horizontal ->) */
    struct _SSSMatrixNode * left;   /* link sparse matrix by row (horizontal <-) */
    struct _SSSMatrixNode * below;  /* link sparse matrix by column (vertical v) */
    struct _SSSMatrixNode * above;  /* link sparse matrix by column (vertical ^) */
};

struct _SSSMatrix {
    int order;      /* the matrix order */
    struct _SSSMatrixNode **columns;    /* the columns pointer buffer */
    struct _SSSMatrixNode **rows;       /* the rows pointer buffer */
    struct _SSSMatrixNode *cached;      /* a cached matrix node (for iteration purposes) */
};

/* Initialize the matrix, with given order. */
void sssmatrix_init(sssmatrix * matrix, int order) {
    matrix->order = order;
    matrix->columns = (sssmatrix_node**) malloc (sizeof(sssmatrix_node*) * matrix->order);
    matrix->rows = (sssmatrix_node**) malloc (sizeof(sssmatrix_node*) * matrix->order);
    matrix->cached = (sssmatrix_node*)NULL;
}

/* This function is a helper function for sssmatrix_get, it processes the get itself
 * by using two pointers: one to iterave vertically (vptr) and other to iterate
 * horizontally (hptr). The first one those find the element to get, return that value
 * or, if one of those guaratee that the element node in not in the sparse matrix, return
 * zero.
 *
 * NOTE: matrix is sparse itself, then returnning zero does NOT mean error.
 *
 * NOTE: if requested row or column is outer of the matrix order, a segmentation fault
 *       will be raised
 */
int __sssmatrix_get(sssmatrix * matrix, int row, int column) {
    sssmatrix_node *vptr, *hptr;
    vptr = matrix->columns[column];
    hptr = matrix->rows[row];
    while (vptr && hptr) {
        if (vptr->row > row) break;
        if (hptr->column > column) break;
        if (vptr->row == row) return vptr->value;
        if (hptr->column == column) return hptr->value;
        vptr = vptr->below;
        hptr = hptr->right;
    }
    return 0;
}

int sssmatrix_get(sssmatrix * matrix, int row, int column) {
    int swap;
    /* for implementation detail, it worth to remember that, as the SSSMatrix
     * is symetric, we are going to instanciate just the upper triangle. Therefore
     * if row and column refers to a cell in the lower triangle, we swap then
     * to reach the same symetric cell in the upper triangle */
    if (column < row) {
        swap = column;
        column = row;
        row = swap;
    }
    return __sssmatrix_get(matrix, row, column);
}

/* It is a helper function to set a specific cell as zero in the sparse matrix.
 * As the matrix is sparse, set zero is equivalent to remove the specific node
 * of the matrix. */
void __sssmatrix_set_zero(sssmatrix * matrix, int row, int column) {
    sssmatrix_node *vptr, *hptr, *rem;
    vptr = matrix->columns[column];
    hptr = matrix->rows[row];
    rem = (sssmatrix_node*) NULL ;
    while (vptr1 && hptr1) {
        if (vptr->row > row) break;
        if (hptr->column > column) break;
        if (vptr->row == row) rem = vptr, break;
        if (hptr->column == column) rem = hptr, break;
        vptr = vptr->below;
        hptr = hptr->right;
    }
    if (rem) {
        /* remove in horizontal */
        if (rem->left) rem->left->right = rem->right;
        else matrix->rows[row] = rem->right;
        if (rem->right) rem->right->left = rem->left;
        /* remove in vertical */
        if (rem->above) rem->above->below = rem->below;
        else matrix->columns[column] = rem->below;
        if (rem->below) rem->below->above = rem->above;
    }
}

void __sssmatrix_set(sssmatrix * matrix, int row, int column) {
    sssmatrix_node *vptr, *hptr, *ptr;
    vptr = matrix->columns[column];
    hptr = matrix->rows[row];
    while (vptr && hptr) {
        if (vptr->row > row)
        vptr = vptr->below;
        hptr = hptr->right;
    }
}

void sssmatrix_set(sssmatrix * matrix, int row, int column, int value) {
    int swap;
    /* for implementation detail, it worth to remember that, as the SSSMatrix
     * is symetric, we are going to instanciate just the upper triangle. Therefore
     * if row and column refers to a cell in the lower triangle, we swap then
     * to reach the same symetric cell in the upper triangle */
    if (column < row) {
        swap = column;
        column = row;
        row = swap;
    }
    /* as sparse, if value to be set is zero, then a node needs to be removed.
     * Then it will be trated with a special funcion */
    if (value == 0) {
        __sssmatrix_set_zero(matrix, row, column);
    } else {
        __sssmatrix_set(matrix, row, column, value);
    }
}
    


#endif
