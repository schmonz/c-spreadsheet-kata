#include <check.h>

#include <stdlib.h>

#include "spreadsheet.h"

spreadsheet_t sheet;

void setup(void)
{
    sheet = spreadsheet_create();
}

void teardown(void)
{
    spreadsheet_destroy(sheet);
}

static void check_column_becomes_index(const char *column, size_t expected)
{
    ck_assert_int_eq(expected, sheet->column_to_index(column));
}

static void check_index_becomes_column(size_t index, const char *expected)
{
    char *actual = sheet->index_to_column(index);
    ck_assert_str_eq(expected, actual);
    free(actual);
}

START_TEST(column_A_to_index_0) {
    check_column_becomes_index("A", 0);
} END_TEST

START_TEST(column_B_to_index_1) {
    check_column_becomes_index("B", 1);
} END_TEST

START_TEST(column_Z_to_index_25) {
    check_column_becomes_index("Z", 25);
} END_TEST

START_TEST(column_AA_to_index_26) {
    check_column_becomes_index("AA", 26);
} END_TEST

START_TEST(column_ZY_to_index_700) {
    check_column_becomes_index("ZY", 700);
} END_TEST

START_TEST(column_AAA_to_index_702) {
    check_column_becomes_index("AAA", 702);
} END_TEST

START_TEST(column_AAB_to_index_703) {
    check_column_becomes_index("AAB", 703);
} END_TEST

START_TEST(index_0_to_column_A) {
    check_index_becomes_column(0, "A");
} END_TEST

START_TEST(index_1_to_column_B) {
    check_index_becomes_column(1, "B");
} END_TEST

START_TEST(index_25_to_column_Z) {
    check_index_becomes_column(25, "Z");
} END_TEST

START_TEST(index_26_to_column_AA) {
    check_index_becomes_column(26, "AA");
} END_TEST

START_TEST(index_27_to_column_AB) {
    check_index_becomes_column(27, "AB");
} END_TEST

START_TEST(index_700_to_column_ZY) {
    check_index_becomes_column(25 + 26*26 - 1, "ZY");
} END_TEST

START_TEST(index_702_to_column_AAA) {
    check_index_becomes_column(25 + 26*26 + 1, "AAA");
} END_TEST

TCase
*spreadsheet_columns_to_indices(void)
{
    TCase *tc = tcase_create("Columns to Indices");

    tcase_add_checked_fixture(tc, setup, teardown);
    tcase_add_test(tc, column_A_to_index_0);
    tcase_add_test(tc, column_B_to_index_1);
    tcase_add_test(tc, column_Z_to_index_25);
    tcase_add_test(tc, column_AA_to_index_26);
    tcase_add_test(tc, column_ZY_to_index_700);
    tcase_add_test(tc, column_AAA_to_index_702);
    tcase_add_test(tc, column_AAB_to_index_703);

    return tc;
}

TCase
*spreadsheet_indices_to_columns(void)
{
    TCase *tc = tcase_create("Indices to Columns");

    tcase_add_checked_fixture(tc, setup, teardown);
    tcase_add_test(tc, index_0_to_column_A);
    tcase_add_test(tc, index_1_to_column_B);
    tcase_add_test(tc, index_25_to_column_Z);
    tcase_add_test(tc, index_26_to_column_AA);
    tcase_add_test(tc, index_27_to_column_AB);
    tcase_add_test(tc, index_700_to_column_ZY);
    tcase_add_test(tc, index_702_to_column_AAA);

    return tc;
}

Suite
*spreadsheet_suite(void)
{
    Suite *s = suite_create("Spreadsheet Suite");

    suite_add_tcase(s, spreadsheet_columns_to_indices());
    suite_add_tcase(s, spreadsheet_indices_to_columns());

    return s;
}

int
main(void)
{
    int number_failed;

    SRunner *sr = srunner_create(spreadsheet_suite());
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return number_failed;
}
