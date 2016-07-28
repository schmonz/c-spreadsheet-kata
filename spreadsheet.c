#include <stdlib.h>
#include <string.h>

#include "spreadsheet.h"

static char size_t_to_char(size_t n)
{
    return (char)(n + 'A');
}

static char * index_to_column(size_t index)
{
    const size_t ARTIFICIALLY_LARGE_AMOUNT_OF_MEMORY = 777;
    char *result = malloc(ARTIFICIALLY_LARGE_AMOUNT_OF_MEMORY);
    size_t pos = 0;
    char this_char;

    memset(result, '\0', ARTIFICIALLY_LARGE_AMOUNT_OF_MEMORY);

    if (index > 25) {
        index = index / 26 - 1;
        this_char = size_t_to_char(index);
        result[pos++] = this_char;
    }

    this_char = size_t_to_char(index);
    result[pos++] = this_char;

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
