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

static void check_index_becomes_column(size_t index, const char *expected)
{
    char *actual = sheet->index_to_column(index);
    ck_assert_str_eq(expected, actual);
    free(actual);
}

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

TCase
*spreadsheet_math(void)
{
    TCase *tc = tcase_create("Spreadsheet Math");

    tcase_add_checked_fixture(tc, setup, teardown);
    tcase_add_test(tc, index_0_to_column_A);
    tcase_add_test(tc, index_1_to_column_B);
    tcase_add_test(tc, index_25_to_column_Z);
    tcase_add_test(tc, index_26_to_column_AA);

    return tc;
}

Suite
*spreadsheet_suite(void)
{
    Suite *s = suite_create("Spreadsheet Suite");

    suite_add_tcase(s, spreadsheet_math());

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
