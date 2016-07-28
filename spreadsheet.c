#include <stdlib.h>

#include "spreadsheet.h"

spreadsheet_t spreadsheet_create(void)
{
    spreadsheet_t sheet = malloc(1);
    return sheet;
}

void spreadsheet_destroy(spreadsheet_t *sheet)
{
    free(*sheet);
    *sheet = NULL;
}
