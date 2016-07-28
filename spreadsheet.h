typedef struct spreadsheet {
    char * (*index_to_column)(size_t);
} *spreadsheet_t;

spreadsheet_t spreadsheet_create(void);
void spreadsheet_destroy(spreadsheet_t);
