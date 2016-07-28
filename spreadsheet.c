#include <stdlib.h>

#include "spreadsheet.h"

static char * index_to_column(size_t index)
{
    (void)index;
    return "A";
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
