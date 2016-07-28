typedef struct spreadsheet {
    char * (*index_to_column)(int);
    int (*column_to_index)(const char *);
} *spreadsheet_t;

spreadsheet_t spreadsheet_create(void);
void spreadsheet_destroy(spreadsheet_t);
