#include <check.h>

#include "s21_matrix.h"

START_TEST(s21_create_matrix_test) {
    int rows = 3;
    int columns = 5;
    matrix_t matrix = s21_create_matrix(rows, columns);

    ck_assert_int_eq(matrix.matrix_type, ZERO_MATRIX);
    s21_remove_matrix(&matrix);

    rows = 0;
    matrix = s21_create_matrix(rows, columns);
    ck_assert_int_eq(matrix.matrix_type, INCORRECT_MATRIX);

    rows = 1;
    columns = -1;
    matrix = s21_create_matrix(rows, columns);
    ck_assert_int_eq(matrix.matrix_type, INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_remove_matrix_test) {
    int rows = 3;
    int columns = 5;
    matrix_t matrix = s21_create_matrix(rows, columns);

    s21_remove_matrix(&matrix);
    ck_assert_int_eq(matrix.matrix_type, INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_eq_matrix_test) {
    int rows = 3;
    int columns = 5;
    matrix_t A = s21_create_matrix(rows, columns);
    matrix_t B = s21_create_matrix(rows, columns);
    ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);

    A.matrix_type = CORRECT_MATRIX;
    A.matrix[0][0] = 1;
    A.matrix[1][1] = 2;
    A.matrix[2][2] = 3;
    ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);

    B.matrix_type = CORRECT_MATRIX;
    B.matrix[0][0] = 1;
    B.matrix[1][1] = 2;
    B.matrix[2][2] = 3;
    ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);

    s21_remove_matrix(&A);
    ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
    s21_remove_matrix(&B);
    ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);

    A = s21_create_matrix(rows, columns);
    A.matrix_type = CORRECT_MATRIX;
    A.matrix[0][0] = 0.045;
    A.matrix[0][1] = 0.0034;
    A.matrix[0][2] = 11;
    A.matrix[0][3] = 54.45;
    A.matrix[0][4] = 45.54;
    A.matrix[1][0] = 1.0045;
    A.matrix[1][1] = 43.4456;
    A.matrix[1][2] = -456.24;
    A.matrix[1][3] = -31.0053;
    A.matrix[1][4] = 11.45;
    A.matrix[2][0] = 0.0002434;
    A.matrix[2][1] = 0.00453;
    A.matrix[2][2] = 1.0000051;
    A.matrix[2][3] = 2.5624567;
    A.matrix[2][4] = 10.34567121;

    B = s21_create_matrix(rows, columns);
    matrix_t C = s21_sum_matrix(&A, &B);

    ck_assert_int_eq(s21_eq_matrix(&A, &C), SUCCESS);
    A.matrix[2][4] = 10.3456712;

    ck_assert_int_eq(s21_eq_matrix(&A, &C), SUCCESS);
    A.matrix[2][4] = 10.345671;
    ck_assert_int_eq(s21_eq_matrix(&A, &C), FAILURE);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_sum_matrix_test) {
    int rows = 3;
    int columns = 5;
    matrix_t A = s21_create_matrix(rows, columns);
    matrix_t B = s21_create_matrix(rows, columns);
    matrix_t result = s21_sum_matrix(&A, &B);
    ck_assert_int_eq(s21_eq_matrix(&A, &result), SUCCESS);
    s21_remove_matrix(&result);

    A.matrix_type = CORRECT_MATRIX;
    A.matrix[0][0] = 1;
    A.matrix[1][1] = 2;
    A.matrix[2][2] = 3;
    result = s21_sum_matrix(&A, &B);
    ck_assert_int_eq(s21_eq_matrix(&A, &result), SUCCESS);
    ck_assert_int_eq(s21_eq_matrix(&B, &result), FAILURE);
    s21_remove_matrix(&result);

    B.matrix_type = CORRECT_MATRIX;
    B.matrix[0][0] = 1;
    B.matrix[1][1] = 2;
    B.matrix[2][2] = 3;
    result = s21_sum_matrix(&A, &B);

    matrix_t sum_matrix = s21_create_matrix(rows, columns);
    sum_matrix.matrix_type = CORRECT_MATRIX;
    sum_matrix.matrix[0][0] = 2;
    sum_matrix.matrix[1][1] = 4;
    sum_matrix.matrix[2][2] = 6;
    ck_assert_int_eq(s21_eq_matrix(&sum_matrix, &result), SUCCESS);

    s21_remove_matrix(&A);

    s21_remove_matrix(&result);
    result = s21_sum_matrix(&A, &B);
    ck_assert_int_eq(result.matrix_type, INCORRECT_MATRIX);

    s21_remove_matrix(&B);
    s21_remove_matrix(&sum_matrix);

    A = s21_create_matrix(rows, columns);
    B = s21_create_matrix(rows, columns - 1);
    result = s21_sum_matrix(&A, &B);
    ck_assert_int_eq(result.matrix_type, INCORRECT_MATRIX);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);

    columns = rows;
    A = s21_create_matrix(rows, columns);
    B = s21_create_matrix(rows, columns);

    A.matrix_type = CORRECT_MATRIX;
    A.matrix[0][0] = 2;
    A.matrix[0][1] = 5;
    A.matrix[0][2] = 7;
    A.matrix[1][0] = 6;
    A.matrix[1][1] = 3;
    A.matrix[1][2] = 4;
    A.matrix[2][0] = 5;
    A.matrix[2][1] = -2;
    A.matrix[2][2] = -3;

    B.matrix_type = CORRECT_MATRIX;
    B.matrix[0][0] = -1;
    B.matrix[0][1] = -5;
    B.matrix[0][2] = -7;
    B.matrix[1][0] = -6;
    B.matrix[1][1] = -2;
    B.matrix[1][2] = -4;
    B.matrix[2][0] = -5;
    B.matrix[2][1] = 2;
    B.matrix[2][2] = 4;

    result = s21_sum_matrix(&A, &B);
    ck_assert_int_eq(result.matrix_type, IDENTITY_MATRIX);
    s21_remove_matrix(&result);
    B.matrix[2][1] = 2.1;
    result = s21_sum_matrix(&A, &B);
    ck_assert_int_eq(result.matrix_type, CORRECT_MATRIX);
    s21_remove_matrix(&result);
    B.matrix[2][1] = 2.00000001;
    result = s21_sum_matrix(&A, &B);
    ck_assert_int_eq(result.matrix_type, IDENTITY_MATRIX);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sub_matrix_test) {
    int rows = 3;
    int columns = 5;
    matrix_t A = s21_create_matrix(rows, columns);
    matrix_t B = s21_create_matrix(rows, columns);
    matrix_t result = s21_sub_matrix(&A, &B);
    ck_assert_int_eq(s21_eq_matrix(&A, &result), SUCCESS);
    s21_remove_matrix(&result);

    A.matrix_type = CORRECT_MATRIX;
    A.matrix[0][0] = 2;
    A.matrix[1][1] = 4;
    A.matrix[2][2] = 6;
    result = s21_sub_matrix(&A, &B);
    ck_assert_int_eq(s21_eq_matrix(&A, &result), SUCCESS);
    ck_assert_int_eq(s21_eq_matrix(&B, &result), FAILURE);
    s21_remove_matrix(&result);

    B.matrix_type = CORRECT_MATRIX;
    B.matrix[0][0] = 1;
    B.matrix[1][1] = 2;
    B.matrix[2][2] = 3;
    result = s21_sub_matrix(&A, &B);

    matrix_t sub_matrix = s21_create_matrix(rows, columns);
    sub_matrix.matrix_type = CORRECT_MATRIX;
    sub_matrix.matrix[0][0] = 1;
    sub_matrix.matrix[1][1] = 2;
    sub_matrix.matrix[2][2] = 3;
    ck_assert_int_eq(s21_eq_matrix(&sub_matrix, &result), SUCCESS);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
    s21_remove_matrix(&sub_matrix);
}
END_TEST

START_TEST(s21_mult_number_test) {
    int rows = 3;
    int columns = 5;
    matrix_t A = s21_create_matrix(rows, columns);
    double number = 5;
    matrix_t result = s21_mult_number(&A, number);
    ck_assert_int_eq(s21_eq_matrix(&A, &result), SUCCESS);
    s21_remove_matrix(&A);
    s21_remove_matrix(&result);

    result = s21_mult_number(&A, number);
    ck_assert_int_eq(result.matrix_type, INCORRECT_MATRIX);

    A = s21_create_matrix(rows, columns);
    A.matrix_type = CORRECT_MATRIX;
    A.matrix[0][0] = 0.045;
    A.matrix[0][1] = 0.0034;
    A.matrix[0][2] = 11;
    A.matrix[0][3] = 54.45;
    A.matrix[0][4] = 45.54;
    A.matrix[1][0] = 1.0045;
    A.matrix[1][1] = 43.4456;
    A.matrix[1][2] = -456.24;
    A.matrix[1][3] = -31.0053;
    A.matrix[1][4] = 11.45;
    A.matrix[2][0] = 0.0002434;
    A.matrix[2][1] = 0.00453;
    A.matrix[2][2] = 1.0000051;
    A.matrix[2][3] = 2.5624567;
    A.matrix[2][4] = 10.34567121;

    matrix_t matrix_to_compare = s21_create_matrix(rows, columns);
    matrix_to_compare.matrix_type = CORRECT_MATRIX;
    matrix_to_compare.matrix[0][0] = 0.02025;
    matrix_to_compare.matrix[0][1] = 0.00153;
    matrix_to_compare.matrix[0][2] = 4.95;
    matrix_to_compare.matrix[0][3] = 24.5025;
    matrix_to_compare.matrix[0][4] = 20.493;
    matrix_to_compare.matrix[1][0] = 0.452025;
    matrix_to_compare.matrix[1][1] = 19.55052;
    matrix_to_compare.matrix[1][2] = -205.308;
    matrix_to_compare.matrix[1][3] = -13.952385;
    matrix_to_compare.matrix[1][4] = 5.1525;
    matrix_to_compare.matrix[2][0] = 0.00010953;
    matrix_to_compare.matrix[2][1] = 0.0020385;
    matrix_to_compare.matrix[2][2] = 0.450002295;
    matrix_to_compare.matrix[2][3] = 1.153105515;
    matrix_to_compare.matrix[2][4] = 4.6555520445;

    number = 0.45;
    result = s21_mult_number(&A, number);
    ck_assert_int_eq(s21_eq_matrix(&matrix_to_compare, &result), SUCCESS);
    s21_remove_matrix(&A);
    s21_remove_matrix(&matrix_to_compare);
    s21_remove_matrix(&result);

    rows = 2;
    columns = 2;
    A = s21_create_matrix(rows, columns);
    A.matrix_type = CORRECT_MATRIX;
    A.matrix[0][0] = 10;
    A.matrix[1][1] = 10;

    number = 0.1;
    result = s21_mult_number(&A, number);
    ck_assert_int_eq(result.matrix_type, IDENTITY_MATRIX);
    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_matrix_test) {
    int rows_a = 3;
    int columns_a = 2;
    int rows_b = 2;
    int columns_b = 3;
    matrix_t A = s21_create_matrix(rows_a, columns_a);
    A.matrix_type = CORRECT_MATRIX;
    A.matrix[0][0] = 1;
    A.matrix[1][0] = 2;
    A.matrix[2][0] = 3;
    A.matrix[0][1] = 4;
    A.matrix[1][1] = 5;
    A.matrix[2][1] = 6;

    matrix_t B = s21_create_matrix(rows_b, columns_b);
    B.matrix_type = CORRECT_MATRIX;
    B.matrix[0][0] = 1;
    B.matrix[1][0] = 2;
    B.matrix[0][1] = -1;
    B.matrix[1][1] = 3;
    B.matrix[0][2] = 1;
    B.matrix[1][2] = 4;

    matrix_t matrix_to_compare = s21_create_matrix(rows_a, columns_b);
    matrix_to_compare.matrix_type = CORRECT_MATRIX;
    matrix_to_compare.matrix[0][0] = 9;
    matrix_to_compare.matrix[1][0] = 12;
    matrix_to_compare.matrix[2][0] = 15;
    matrix_to_compare.matrix[0][1] = 11;
    matrix_to_compare.matrix[1][1] = 13;
    matrix_to_compare.matrix[2][1] = 15;
    matrix_to_compare.matrix[0][2] = 17;
    matrix_to_compare.matrix[1][2] = 22;
    matrix_to_compare.matrix[2][2] = 27;

    matrix_t result = s21_mult_matrix(&A, &B);
    ck_assert_int_eq(s21_eq_matrix(&matrix_to_compare, &result), SUCCESS);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
    s21_remove_matrix(&matrix_to_compare);

    A = s21_create_matrix(rows_a, columns_a);
    result = s21_mult_matrix(&A, &A);
    ck_assert_int_eq(result.matrix_type, INCORRECT_MATRIX);
    s21_remove_matrix(&A);

    rows_a = 3;
    columns_a = 5;
    A = s21_create_matrix(rows_a, columns_a);
    A.matrix_type = CORRECT_MATRIX;
    A.matrix[0][0] = 0.045;
    A.matrix[0][1] = 0.0034;
    A.matrix[0][2] = 11;
    A.matrix[0][3] = 54.45;
    A.matrix[0][4] = 45.54;
    A.matrix[1][0] = 1.0045;
    A.matrix[1][1] = 43.4456;
    A.matrix[1][2] = -456.24;
    A.matrix[1][3] = -31.0053;
    A.matrix[1][4] = 11.45;
    A.matrix[2][0] = 0.0002434;
    A.matrix[2][1] = 0.00453;
    A.matrix[2][2] = 1.0000051;
    A.matrix[2][3] = 2.5624567;
    A.matrix[2][4] = 10.34567121;

    rows_b = columns_a;
    columns_b = columns_a;
    B = s21_create_matrix(rows_b, columns_b);
    result = s21_mult_matrix(&A, &B);
    ck_assert_int_eq(result.matrix_type, ZERO_MATRIX);
    s21_remove_matrix(&result);
    B.matrix_type = IDENTITY_MATRIX;
    B.matrix[0][0] = 1;
    B.matrix[1][1] = 1;
    B.matrix[2][2] = 1;
    B.matrix[3][3] = 1;
    B.matrix[4][4] = 1;
    result = s21_mult_matrix(&A, &B);
    ck_assert_int_eq(s21_eq_matrix(&A, &result), SUCCESS);
    s21_remove_matrix(&result);
    B.matrix_type = CORRECT_MATRIX;
    B.matrix[0][1] = 1.003;
    B.matrix[0][3] = 3.44;
    B.matrix[2][3] = 1.002;
    B.matrix[3][0] = 4.411;
    B.matrix[4][2] = 0.05;

    matrix_to_compare = s21_create_matrix(rows_a, columns_b);
    matrix_to_compare.matrix_type = CORRECT_MATRIX;
    matrix_to_compare.matrix[0][0] = 240.22395;
    matrix_to_compare.matrix[0][1] = 0.048535;
    matrix_to_compare.matrix[0][2] = 13.277;
    matrix_to_compare.matrix[0][3] = 65.6268;
    matrix_to_compare.matrix[0][4] = 45.54;
    matrix_to_compare.matrix[1][0] = -135.7598783;
    matrix_to_compare.matrix[1][1] = 44.4531135;
    matrix_to_compare.matrix[1][2] = -455.6675;
    matrix_to_compare.matrix[1][3] = -484.7023;
    matrix_to_compare.matrix[1][4] = 11.45;
    matrix_to_compare.matrix[2][0] = 11.3032399037;
    matrix_to_compare.matrix[2][1] = 0.0047741302;
    matrix_to_compare.matrix[2][2] = 1.5172886605;
    matrix_to_compare.matrix[2][3] = 3.5652991062;
    matrix_to_compare.matrix[2][4] = 10.34567121;

    result = s21_mult_matrix(&A, &B);
    ck_assert_int_eq(s21_eq_matrix(&matrix_to_compare, &result), SUCCESS);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
    s21_remove_matrix(&matrix_to_compare);
}
END_TEST

START_TEST(s21_transpose_test) {
    int rows = 3;
    int columns = 2;
    matrix_t A = s21_create_matrix(rows, columns);
    A.matrix_type = CORRECT_MATRIX;
    A.matrix[0][0] = 1;
    A.matrix[1][0] = 2;
    A.matrix[2][0] = 3;
    A.matrix[0][1] = 4;
    A.matrix[1][1] = 5;
    A.matrix[2][1] = 6;

    matrix_t matrix_to_compare = s21_create_matrix(columns, rows);
    matrix_to_compare.matrix_type = CORRECT_MATRIX;
    matrix_to_compare.matrix[0][0] = 1;
    matrix_to_compare.matrix[0][1] = 2;
    matrix_to_compare.matrix[0][2] = 3;
    matrix_to_compare.matrix[1][0] = 4;
    matrix_to_compare.matrix[1][1] = 5;
    matrix_to_compare.matrix[1][2] = 6;

    matrix_t result = s21_transpose(&A);
    ck_assert_int_eq(s21_eq_matrix(&matrix_to_compare, &result), SUCCESS);
    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
    s21_remove_matrix(&matrix_to_compare);

    result = s21_transpose(&A);
    ck_assert_int_eq(result.matrix_type, INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_calc_complements_test) {
    int rows = 3;
    int columns = 3;
    matrix_t A = s21_create_matrix(rows, columns);
    A.matrix_type = CORRECT_MATRIX;
    A.matrix[0][0] = 1;
    A.matrix[0][1] = 2;
    A.matrix[0][2] = 3;
    A.matrix[1][0] = 0;
    A.matrix[1][1] = 4;
    A.matrix[1][2] = 2;
    A.matrix[2][0] = 5;
    A.matrix[2][1] = 2;
    A.matrix[2][2] = 1;

    matrix_t matrix_to_compare = s21_create_matrix(rows, columns);
    matrix_to_compare.matrix_type = CORRECT_MATRIX;
    matrix_to_compare.matrix[0][0] = 0;
    matrix_to_compare.matrix[0][1] = 10;
    matrix_to_compare.matrix[0][2] = -20;
    matrix_to_compare.matrix[1][0] = 4;
    matrix_to_compare.matrix[1][1] = -14;
    matrix_to_compare.matrix[1][2] = 8;
    matrix_to_compare.matrix[2][0] = -8;
    matrix_to_compare.matrix[2][1] = -2;
    matrix_to_compare.matrix[2][2] = 4;

    matrix_t result = s21_calc_complements(&A);
    ck_assert_int_eq(s21_eq_matrix(&matrix_to_compare, &result), SUCCESS);
    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
    s21_remove_matrix(&matrix_to_compare);

    columns = 4;
    A = s21_create_matrix(rows, columns);
    result = s21_calc_complements(&A);
    ck_assert_int_eq(result.matrix_type, INCORRECT_MATRIX);
    s21_remove_matrix(&A);

    rows = 5;
    columns = rows;
    A = s21_create_matrix(rows, columns);
    A.matrix_type = CORRECT_MATRIX;
    A.matrix[0][0] = 1.004;
    A.matrix[0][1] = 2;
    A.matrix[0][2] = 2.2;
    A.matrix[0][3] = 4.5;
    A.matrix[0][4] = 4.002;

    A.matrix[1][0] = 0.00012;
    A.matrix[1][1] = 0.6;
    A.matrix[1][2] = 10;
    A.matrix[1][3] = -4.4;
    A.matrix[1][4] = -5.5;

    A.matrix[2][0] = -0.4;
    A.matrix[2][1] = 1.5;
    A.matrix[2][2] = 0.004;
    A.matrix[2][3] = 4.4;
    A.matrix[2][4] = 5.5;

    A.matrix[3][0] = 7.335;
    A.matrix[3][1] = 5.334;
    A.matrix[3][2] = -9.45;
    A.matrix[3][3] = 1.1;
    A.matrix[3][4] = 2.01;

    A.matrix[4][0] = 4.11;
    A.matrix[4][1] = -6.1;
    A.matrix[4][2] = 8;
    A.matrix[4][3] = 2;
    A.matrix[4][4] = 0;

    matrix_to_compare = s21_create_matrix(rows, columns);
    matrix_to_compare.matrix_type = CORRECT_MATRIX;
    matrix_to_compare.matrix[0][0] = -527.53797;
    matrix_to_compare.matrix[0][1] = 905.5026670496;
    matrix_to_compare.matrix[0][2] = -211.166281928;
    matrix_to_compare.matrix[0][3] = 4690.53879138528;
    matrix_to_compare.matrix[0][4] = -4037.59912830944;

    matrix_to_compare.matrix[1][0] = 290.674078576;
    matrix_to_compare.matrix[1][1] = 393.070774072;
    matrix_to_compare.matrix[1][2] = 505.450856288;
    matrix_to_compare.matrix[1][3] = -1420.27279570608;
    matrix_to_compare.matrix[1][4] = 1049.789448728;

    matrix_to_compare.matrix[2][0] = 453.4347076;
    matrix_to_compare.matrix[2][1] = -325.845847328;
    matrix_to_compare.matrix[2][2] = 662.86885161728;
    matrix_to_compare.matrix[2][3] = -4577.11356493752;
    matrix_to_compare.matrix[2][4] = 4831.370019212;

    matrix_to_compare.matrix[3][0] = 604.98681488;
    matrix_to_compare.matrix[3][1] = 164.28842993408;
    matrix_to_compare.matrix[3][2] = -10.3042358384;
    matrix_to_compare.matrix[3][3] = -700.951249925856;
    matrix_to_compare.matrix[3][4] = 559.961599576;

    matrix_to_compare.matrix[4][0] = 496.1443013632;
    matrix_to_compare.matrix[4][1] = -546.123070245344;
    matrix_to_compare.matrix[4][2] = 134.471874324704;
    matrix_to_compare.matrix[4][3] = -340.26728019080064;
    matrix_to_compare.matrix[4][4] = 457.14190386464;

    result = s21_calc_complements(&A);
    for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
        char s21[128];
        char orig[128];
        snprintf(s21, sizeof(s21), "%lf", result.matrix[i][j]);
        snprintf(orig, sizeof(orig), "%lf", matrix_to_compare.matrix[i][j]);
        ck_assert_str_eq(s21, orig);
    }
    }
    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
    s21_remove_matrix(&matrix_to_compare);
}
END_TEST

START_TEST(s21_determinant_test) {
    int rows = 3;
    int columns = 3;
    matrix_t A = s21_create_matrix(rows, columns);
    A.matrix_type = CORRECT_MATRIX;
    A.matrix[0][0] = 1;
    A.matrix[0][1] = 2;
    A.matrix[0][2] = 3;
    A.matrix[1][0] = 4;
    A.matrix[1][1] = 5;
    A.matrix[1][2] = 6;
    A.matrix[2][0] = 7;
    A.matrix[2][1] = 8;
    A.matrix[2][2] = 9;

    double det = s21_determinant(&A);
    // ck_assert_double_eq(det, 0);
    s21_remove_matrix(&A);

    rows = 5;
    columns = rows;
    A = s21_create_matrix(rows, columns);
    A.matrix_type = CORRECT_MATRIX;
    A.matrix[0][0] = 1.004;
    A.matrix[0][1] = 2;
    A.matrix[0][2] = 2.2;
    A.matrix[0][3] = 4.5;
    A.matrix[0][4] = 4.002;

    A.matrix[1][0] = 0.00012;
    A.matrix[1][1] = 0.6;
    A.matrix[1][2] = 10;
    A.matrix[1][3] = -4.4;
    A.matrix[1][4] = -5.5;

    A.matrix[2][0] = -0.4;
    A.matrix[2][1] = 1.5;
    A.matrix[2][2] = 0.004;
    A.matrix[2][3] = 4.4;
    A.matrix[2][4] = 5.5;

    A.matrix[3][0] = 7.335;
    A.matrix[3][1] = 5.334;
    A.matrix[3][2] = -9.45;
    A.matrix[3][3] = 1.1;
    A.matrix[3][4] = 2.01;

    A.matrix[4][0] = 4.11;
    A.matrix[4][1] = -6.1;
    A.matrix[4][2] = 8;
    A.matrix[4][3] = 2;
    A.matrix[4][4] = 0;

    det = s21_determinant(&A);
    double answer = 5765.7442413153;
    char s21[128];
    char orig[128];
    snprintf(s21, sizeof(s21), "%lf", det);
    snprintf(orig, sizeof(orig), "%lf", answer);
    ck_assert_str_eq(s21, orig);
    s21_remove_matrix(&A);

    rows = 4;
    columns = 3;
    A = s21_create_matrix(rows, columns);
    det = s21_determinant(&A);
    // ck_assert_double_nan(det);
    s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_inverse_matrix_test) {
    int rows = 3;
    int columns = 3;
    matrix_t A = s21_create_matrix(rows, columns);
    A.matrix_type = CORRECT_MATRIX;
    A.matrix[0][0] = 2;
    A.matrix[0][1] = 5;
    A.matrix[0][2] = 7;
    A.matrix[1][0] = 6;
    A.matrix[1][1] = 3;
    A.matrix[1][2] = 4;
    A.matrix[2][0] = 5;
    A.matrix[2][1] = -2;
    A.matrix[2][2] = -3;

    matrix_t matrix_to_compare = s21_create_matrix(rows, columns);
    matrix_to_compare.matrix_type = CORRECT_MATRIX;
    matrix_to_compare.matrix[0][0] = 1;
    matrix_to_compare.matrix[0][1] = -1;
    matrix_to_compare.matrix[0][2] = 1;
    matrix_to_compare.matrix[1][0] = -38;
    matrix_to_compare.matrix[1][1] = 41;
    matrix_to_compare.matrix[1][2] = -34;
    matrix_to_compare.matrix[2][0] = 27;
    matrix_to_compare.matrix[2][1] = -29;
    matrix_to_compare.matrix[2][2] = 24;

    matrix_t result_matrix = s21_inverse_matrix(&A);
    ck_assert_int_eq(s21_eq_matrix(&matrix_to_compare, &result_matrix), SUCCESS);
    matrix_t identity = s21_mult_matrix(&result_matrix, &A);
    ck_assert_int_eq(identity.matrix_type, IDENTITY_MATRIX);
    s21_remove_matrix(&A);
    s21_remove_matrix(&matrix_to_compare);
    s21_remove_matrix(&result_matrix);
    s21_remove_matrix(&identity);

    rows = 5;
    columns = rows;
    A = s21_create_matrix(rows, columns);
    A.matrix_type = CORRECT_MATRIX;
    A.matrix[0][0] = 1.004;
    A.matrix[0][1] = 2;
    A.matrix[0][2] = 2.2;
    A.matrix[0][3] = 4.5;
    A.matrix[0][4] = 4.002;

    A.matrix[1][0] = 0.00012;
    A.matrix[1][1] = 0.6;
    A.matrix[1][2] = 10;
    A.matrix[1][3] = -4.4;
    A.matrix[1][4] = -5.5;

    A.matrix[2][0] = -0.4;
    A.matrix[2][1] = 1.5;
    A.matrix[2][2] = 0.004;
    A.matrix[2][3] = 4.4;
    A.matrix[2][4] = 5.5;

    A.matrix[3][0] = 7.335;
    A.matrix[3][1] = 5.334;
    A.matrix[3][2] = -9.45;
    A.matrix[3][3] = 1.1;
    A.matrix[3][4] = 2.01;

    A.matrix[4][0] = 4.11;
    A.matrix[4][1] = -6.1;
    A.matrix[4][2] = 8;
    A.matrix[4][3] = 2;
    A.matrix[4][4] = 0;

    matrix_to_compare = s21_create_matrix(rows, columns);
    matrix_to_compare.matrix_type = CORRECT_MATRIX;
    matrix_to_compare.matrix[0][0] = -0.0914952083;
    matrix_to_compare.matrix[0][1] = 0.0504139737;
    matrix_to_compare.matrix[0][2] = 0.0786428756847;
    matrix_to_compare.matrix[0][3] = 0.1049277924166;
    matrix_to_compare.matrix[0][4] = 0.086050348506;

    matrix_to_compare.matrix[1][0] = 0.15704870510229;
    matrix_to_compare.matrix[1][1] = 0.06817346687967658;
    matrix_to_compare.matrix[1][2] = -0.056514100121385635;
    matrix_to_compare.matrix[1][3] = 0.028493880938534266599;
    matrix_to_compare.matrix[1][4] = -0.0947185735940228175;

    matrix_to_compare.matrix[2][0] = -0.036624288745736;
    matrix_to_compare.matrix[2][1] = 0.08766446015175;
    matrix_to_compare.matrix[2][2] = 0.11496674564;
    matrix_to_compare.matrix[2][3] = -0.00178714757490686;
    matrix_to_compare.matrix[2][4] = 0.0233225527697;

    matrix_to_compare.matrix[3][0] = 0.81351835861439;
    matrix_to_compare.matrix[3][1] = -0.246329482589;
    matrix_to_compare.matrix[3][2] = -0.7938460974629;
    matrix_to_compare.matrix[3][3] = -0.12157168625397;
    matrix_to_compare.matrix[3][4] = -0.0590153267;

    matrix_to_compare.matrix[4][0] = -0.70027371304;
    matrix_to_compare.matrix[4][1] = 0.18207353722;
    matrix_to_compare.matrix[4][2] = 0.83794386587;
    matrix_to_compare.matrix[4][3] = 0.09711870248;
    matrix_to_compare.matrix[4][4] = 0.079285844937;

    result_matrix = s21_inverse_matrix(&A);

    ck_assert_int_eq(s21_eq_matrix(&matrix_to_compare, &result_matrix), SUCCESS);

    identity = s21_mult_matrix(&result_matrix, &A);
    ck_assert_int_eq(identity.matrix_type, IDENTITY_MATRIX);
    s21_remove_matrix(&A);
    s21_remove_matrix(&matrix_to_compare);
    s21_remove_matrix(&result_matrix);
    s21_remove_matrix(&identity);

    rows = 3;
    columns = 3;
    A = s21_create_matrix(rows, columns);
    A.matrix_type = CORRECT_MATRIX;
    A.matrix[0][0] = 1;
    A.matrix[0][1] = 2;
    A.matrix[0][2] = 3;
    A.matrix[1][0] = 4;
    A.matrix[1][1] = 5;
    A.matrix[1][2] = 6;
    A.matrix[2][0] = 7;
    A.matrix[2][1] = 8;
    A.matrix[2][2] = 9;

    result_matrix = s21_inverse_matrix(&A);
    ck_assert_int_eq(result_matrix.matrix_type, INCORRECT_MATRIX);
    s21_remove_matrix(&A);
}
END_TEST

int main(void) {
    Suite *s_s21_matrix = suite_create("s21_matrix");

    TCase *tc_s21_create_matrix = tcase_create("s21_create_matrix_test");
    TCase *tc_s21_remove_matrix = tcase_create("s21_remove_matrix_test");
    TCase *tc_s21_eq_matrix = tcase_create("s21_eq_matrix_test");
    TCase *tc_s21_sum_matrix = tcase_create("s21_sum_matrix_test");
    TCase *tc_s21_sub_matrix = tcase_create("s21_sub_matrix_test");
    TCase *tc_s21_mult_number = tcase_create("s21_mult_number_test");
    TCase *tc_s21_mult_matrix = tcase_create("s21_mult_matrix_test");
    TCase *tc_s21_transpose = tcase_create("s21_transpose_test");
    TCase *tc_s21_calc_complements = tcase_create("s21_calc_complements_test");
    TCase *tc_s21_determinant = tcase_create("s21_determinant_test");
    TCase *tc_s21_inverse_matrix = tcase_create("s21_inverse_matrix_test");

    SRunner *sr = srunner_create(s_s21_matrix);

    suite_add_tcase(s_s21_matrix, tc_s21_create_matrix);
    tcase_add_test(tc_s21_create_matrix, s21_create_matrix_test);
    suite_add_tcase(s_s21_matrix, tc_s21_remove_matrix);
    tcase_add_test(tc_s21_remove_matrix, s21_remove_matrix_test);
    suite_add_tcase(s_s21_matrix, tc_s21_eq_matrix);
    tcase_add_test(tc_s21_eq_matrix, s21_eq_matrix_test);
    suite_add_tcase(s_s21_matrix, tc_s21_sum_matrix);
    tcase_add_test(tc_s21_sum_matrix, s21_sum_matrix_test);
    suite_add_tcase(s_s21_matrix, tc_s21_sub_matrix);
    tcase_add_test(tc_s21_sub_matrix, s21_sub_matrix_test);
    suite_add_tcase(s_s21_matrix, tc_s21_mult_number);
    tcase_add_test(tc_s21_mult_number, s21_mult_number_test);
    suite_add_tcase(s_s21_matrix, tc_s21_mult_matrix);
    tcase_add_test(tc_s21_mult_matrix, s21_mult_matrix_test);
    suite_add_tcase(s_s21_matrix, tc_s21_transpose);
    tcase_add_test(tc_s21_transpose, s21_transpose_test);
    suite_add_tcase(s_s21_matrix, tc_s21_calc_complements);
    tcase_add_test(tc_s21_calc_complements, s21_calc_complements_test);
    suite_add_tcase(s_s21_matrix, tc_s21_determinant);
    tcase_add_test(tc_s21_determinant, s21_determinant_test);
    suite_add_tcase(s_s21_matrix, tc_s21_inverse_matrix);
    tcase_add_test(tc_s21_inverse_matrix, s21_inverse_matrix_test);

    srunner_run_all(sr, CK_ENV);
    srunner_ntests_failed(sr);
    srunner_free(sr);
}
