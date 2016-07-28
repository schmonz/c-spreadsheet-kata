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

static char size_t_to_char(size_t n)
{
    return (char)(n % 26 + 'A');
}

static char * index_to_column(size_t index)
{
    const size_t ARTIFICIALLY_LARGE_AMOUNT_OF_MEMORY = 777;
    char *result = malloc(ARTIFICIALLY_LARGE_AMOUNT_OF_MEMORY);
    size_t pos = 0;
    char this_char;

    memset(result, '\0', ARTIFICIALLY_LARGE_AMOUNT_OF_MEMORY);

    if (index > 25) {
        this_char = size_t_to_char(index);
        index = index / 26 - 1;
        result[pos++] = this_char;
    }

    this_char = size_t_to_char(index);
    result[pos++] = this_char;

    reverse(result);
    return result;
}

spreadsheet_t spreadsheet_create(void)
{
    spreadsheet_t sheet = malloc(1);
    sheet->index_to_column = index_to_column;
    return sheet;
}

void spreadsheet_destroy(spreadsheet_t sheet)
{
    free(sheet);
}
