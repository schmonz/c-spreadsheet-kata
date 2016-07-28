#include <check.h>

#include <stdlib.h>

#include "spreadsheet.h"

START_TEST(spreadsheet_create_and_destroy)
{
    spreadsheet_t sheet = spreadsheet_create();

    ck_assert_ptr_ne(NULL, sheet);

    spreadsheet_destroy(sheet);
}
END_TEST

TCase
*spreadsheet_math(void)
{
    TCase *tc = tcase_create("Spreadsheet Math");

    tcase_add_test(tc, spreadsheet_create_and_destroy);

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
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return number_failed;
}
