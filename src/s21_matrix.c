#include "s21_matrix.h"


// MAIN FUNCTIONS
matrix_t s21_create_matrix(int rows, int columns) {
    matrix_t new_matrix = {NULL, 0, 0, CORRECT_MATRIX};
    if ((rows > 0) && (columns > 0)) {
    new_matrix.rows = rows;
    new_matrix.columns = columns;
    new_matrix.matrix_type = ZERO_MATRIX;
    new_matrix.matrix = (double **)calloc(new_matrix.rows, sizeof(double *));
    for (int i = 0; i < new_matrix.rows; i++) {
        new_matrix.matrix[i] = (double *)calloc(new_matrix.columns, sizeof(double));
    }
    } else {
    new_matrix.matrix_type = INCORRECT_MATRIX;
    }
    return new_matrix;
}

void s21_remove_matrix(matrix_t *A) {
    if (A->matrix_type != INCORRECT_MATRIX) {
    for (int i = 0; i < A->rows; i++) {
        free(A->matrix[i]);
    }
    free(A->matrix);
    A->columns = 0;
    A->rows = 0;
    A->matrix_type = INCORRECT_MATRIX;
    }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    int res = 1;
    if ((A->columns == B->columns) && (A->rows == B->rows &&
    (A->matrix_type == B->matrix_type)) && (A->matrix_type != INCORRECT_MATRIX)) {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                if ((fabs(A->matrix[i][j] - B->matrix[i][j]) > EPSILON)) {
                    res = 0;
                } else {
                    res = 1;
                }
            }
        }
    } else {
        res = 0;
    }
    return res;
}

matrix_t s21_sum_matrix(matrix_t *A, matrix_t *B) {
    matrix_t res = {NULL, 0, 0, CORRECT_MATRIX};
    if ((A->columns == B->columns) && (A->rows == B->rows) &&
    (A->matrix_type != INCORRECT_MATRIX || B->matrix_type != INCORRECT_MATRIX)) {
        res = s21_create_matrix(A->rows, A->columns);
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                res.matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
            }
        }
        if (isZeroMatrix(res) == 0) {
            res.matrix_type = ZERO_MATRIX;
        } else if (isIdentityMatrix(res) == 0) {
            res.matrix_type = IDENTITY_MATRIX;
        } else {
            res.matrix_type = CORRECT_MATRIX;
        }
    } else {
        res.matrix_type = INCORRECT_MATRIX;
    }
    return res;
}

matrix_t s21_sub_matrix(matrix_t *A, matrix_t *B) {
    matrix_t res = {NULL, 0, 0, CORRECT_MATRIX};
    if ((A->columns == B->columns) && (A->rows == B->rows) &&
    (A->matrix_type != INCORRECT_MATRIX || B->matrix_type != INCORRECT_MATRIX)) {
        res = s21_create_matrix(A->rows, A->columns);
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                res.matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
            }
        }
        if (isZeroMatrix(res) == 0) {
            res.matrix_type = ZERO_MATRIX;
        } else if (isIdentityMatrix(res) == 0) {
            res.matrix_type = IDENTITY_MATRIX;
        } else {
            res.matrix_type = CORRECT_MATRIX;
        }
    } else {
        res.matrix_type = INCORRECT_MATRIX;
    }
    return res;
}

matrix_t s21_mult_matrix(matrix_t *A, matrix_t *B) {
    matrix_t res = {NULL, 0, 0, CORRECT_MATRIX};
    if (A->columns == B->rows && (A->matrix_type != INCORRECT_MATRIX ||
    B->matrix_type != INCORRECT_MATRIX)) {
        res = s21_create_matrix(A->rows, B->columns);
    for (int i = 0; i < res.rows; i++) {
        for (int j = 0; j < res.columns; j++) {
            for (int c = 0; c < B->rows; c++) {
                res.matrix[i][j] += A->matrix[i][c] * B->matrix[c][j];
            }
        }
    }
    if (isZeroMatrix(res) == 0) {
        res.matrix_type = ZERO_MATRIX;
    } else if (isIdentityMatrix(res) == 0) {
        res.matrix_type = IDENTITY_MATRIX;
    } else {
        res.matrix_type = CORRECT_MATRIX;
    }
    } else {
        res.matrix_type = INCORRECT_MATRIX;
    }
    return res;
}

matrix_t s21_transpose(matrix_t *A) {
    matrix_t res = {NULL, 0, 0, CORRECT_MATRIX};
    if (A->matrix_type == INCORRECT_MATRIX) {
        res.matrix_type = INCORRECT_MATRIX;
    } else {
        res = s21_create_matrix(A->columns, A->rows);
        for (int i = 0; i < res.rows; i++) {
            for (int j = 0; j < res.columns; j++) {
                res.matrix[i][j] = A->matrix[j][i];
            }
        }
        if (isZeroMatrix(res) == 0) {
            res.matrix_type = ZERO_MATRIX;
        } else if (isIdentityMatrix(res) == 0) {
            res.matrix_type = IDENTITY_MATRIX;
        } else {
            res.matrix_type = CORRECT_MATRIX;
        }
    }
    return res;
}

matrix_t s21_calc_complements(matrix_t *A) {
    matrix_t res = {NULL, 0, 0, CORRECT_MATRIX};
    if ((A->rows != A->columns) || (A->matrix_type == INCORRECT_MATRIX)) {
        res.matrix_type = INCORRECT_MATRIX;
    } else {
        res = s21_minor_matrix(A);
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                res.matrix[i][j] *= pow(-1, (i + j));
            }
        }
        res.matrix_type = CORRECT_MATRIX;
        if (isIdentityMatrix(res) == 0) {
            res.matrix_type = IDENTITY_MATRIX;
        }
    }
    return res;
}

matrix_t s21_mult_number(matrix_t *A, double number) {
    matrix_t res = {NULL, 0, 0, CORRECT_MATRIX};
    if (A->matrix_type == INCORRECT_MATRIX) {
        res.matrix_type = INCORRECT_MATRIX;
    } else {
        res = s21_create_matrix(A->rows, A->columns);
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                res.matrix[i][j] = A->matrix[i][j] * number;
            }
        }
        if (isZeroMatrix(res) == 0) {
            res.matrix_type = ZERO_MATRIX;
        } else if (isIdentityMatrix(res) == 0) {
            res.matrix_type = IDENTITY_MATRIX;
        } else {
            res.matrix_type = CORRECT_MATRIX;
        }
    }
    return res;
}

double s21_determinant(matrix_t *A) {
    double res = 0.00;
    if ((A->rows != A->columns) || (A->matrix_type == INCORRECT_MATRIX)) {
        res = NAN;
    } else {
        int degree = 1;
        if (A->rows == 1) {
            res = A->matrix[0][0];
        } else if (A->rows == 2) {
            res = duo_det(A);
        } else {
            matrix_t tmp_matrix;
            for (int i = 0; i < A->rows; i++) {
                tmp_matrix = s21_cropp_matrix(A, 0, i);
                res += degree * A->matrix[0][i] * s21_determinant(&tmp_matrix);
                s21_remove_matrix(&tmp_matrix);
                degree = -degree;
            }
        }
    }
    return res;
}

matrix_t s21_inverse_matrix(matrix_t *A) {
    matrix_t res = {NULL, 0, 0, CORRECT_MATRIX};
    if ((A->rows != A->columns) || (A->matrix_type == INCORRECT_MATRIX)) {
        res.matrix_type = INCORRECT_MATRIX;
    } else {
        float det = s21_determinant(A);
        if (det == 0) {
            res.matrix_type = INCORRECT_MATRIX;
        } else {
            matrix_t comp = s21_calc_complements(A);
            matrix_t transp = s21_transpose(&comp);
            s21_remove_matrix(&comp);
            res = s21_mult_number(&transp, 1 / det);
            s21_remove_matrix(&transp);
            if (isIdentityMatrix(res) == 0) {
                res.matrix_type = IDENTITY_MATRIX;
            }
        }
    }
    return res;
}


// SUBFUNCTIONS
double duo_det(matrix_t *A) {
    double res = 0;
    res = A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    return res;
}

matrix_t s21_minor_matrix(matrix_t *A) {
    matrix_t res;
    res = s21_create_matrix(A->rows, A->columns);
    matrix_t temp;
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            temp = s21_cropp_matrix(A, i, j);
            res.matrix[i][j] = s21_determinant(&temp);
            s21_remove_matrix(&temp);
        }
    }
    return res;
}

matrix_t s21_cropp_matrix(matrix_t *A, int row, int col) {
    matrix_t res;
    res = s21_create_matrix(A->rows - 1, A->columns - 1);
    int x_row = 0;
    int y_col = 0;
    for (int i = 0; i < A->rows - 1; i++) {
        if (i == row) {
            x_row = 1;
        }
        y_col = 0;
        for (int j = 0; j < A->columns - 1; j++) {
        if (j == col) {
            y_col = 1;
        }
        res.matrix[i][j] = A->matrix[i + x_row][j + y_col];
        }
    }
    return res;
}

int isZeroMatrix(matrix_t A) {
    int res = 0;
    for (int i = 0; (i != A.rows); i++) {
        for (int j = 0; (j != A.columns); j++) {
            if (A.matrix[i][j] != 0) {
                res = 1;
            }
        }
    }
    return res;
}

int isIdentityMatrix(matrix_t A) {
    // 0 - identity matrix
    // 1 - not identity matrix
    int res = 0;
    if (A.rows == A.columns) {
    int flag_one = 0;
    int flag_zero = 0;
    int flag_final = 0;
    for (int i = 0; (i != A.rows); i++) {
        for (int j = 0; (j != A.columns); j++) {
            if ((fabs(A.matrix[i][j]) > EPSILON) && (i != j)) {
                flag_zero += 1;
            }
            if ((flag_zero == 0) && (i == j)) {
                if (!(fabs(A.matrix[i][j] - 1) > EPSILON)) {
                    flag_one += 1;
                }
            }
        }
    }
    if ((flag_zero == 0) && (flag_one == A.columns)) {
        flag_final = 1;
    }
    if (flag_final != 1) {
        res = 1;
    }
    } else {
        res = 1;
    }
    return res;
}
