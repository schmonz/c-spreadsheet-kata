#include <check.h>

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

START_TEST(index_0_to_column_A)
{
    ck_assert_str_eq("A", sheet->index_to_column(0));
} END_TEST

START_TEST(index_1_to_column_B)
{
    ck_assert_str_eq("B", sheet->index_to_column(1));
} END_TEST

TCase
*spreadsheet_math(void)
{
    TCase *tc = tcase_create("Spreadsheet Math");

    tcase_add_checked_fixture(tc, setup, teardown);
    tcase_add_test(tc, index_0_to_column_A);
    tcase_add_test(tc, index_1_to_column_B);

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
