#include <stdlib.h>
#include <string.h>

#include "spreadsheet.h"

static void reverse(char *string)
{
    size_t length = strlen(string);
    size_t last = length - 1;
    char temp;
    for (size_t near_side = 0; near_side < length / 2; near_side++) {
        size_t far_side = last - near_side;
        temp = string[far_side];
        string[far_side] = string[near_side];
        string[near_side] = temp;
    }
}

static int char_to_int(char c)
{
    return c - 'A';
}

static int column_to_index(const char *column)
{
    int result = char_to_int(column[0]);

    for (size_t i = 1; i < strlen(column); i++) {
        result = 26 * (result + 1);
        result += char_to_int(column[1]);
    }

    return result;
}

static char int_to_char(size_t n)
{
    return (char)(n % 26 + 'A');
}

static char * index_to_column(int index)
{
    const size_t ARTIFICIALLY_LARGE_AMOUNT_OF_MEMORY = 777;
    char *result = malloc(ARTIFICIALLY_LARGE_AMOUNT_OF_MEMORY);
    size_t pos = 0;

    memset(result, '\0', ARTIFICIALLY_LARGE_AMOUNT_OF_MEMORY);

    do {
        result[pos++] = int_to_char(index);
        index = index / 26 - 1;
    } while (index >= 0);

    reverse(result);
    return result;
}

spreadsheet_t spreadsheet_create(void)
{
    spreadsheet_t sheet = malloc(1);
    sheet->index_to_column = index_to_column;
    sheet->column_to_index = column_to_index;
    return sheet;
}

void spreadsheet_destroy(spreadsheet_t sheet)
{
    free(sheet);
}
