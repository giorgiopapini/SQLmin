#ifndef row_h
#define row_h

#include "common.h"

#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255

#define SIZE_OF_ATTRIBUTE(struct, attribute) sizeof(((struct *)0)->attribute)


typedef struct Row {
    uint32_t id;
    char username[COLUMN_USERNAME_SIZE + 1];  // +1 because of the '\0' char at the end of any Cstring
    char email[COLUMN_EMAIL_SIZE + 1];
} Row;

// This thing should be later done "just in time" for every single statement?  (by doing so, one can have dynamic rows)
static const uint32_t ID_SIZE = SIZE_OF_ATTRIBUTE(Row, id);
static const uint32_t USERNAME_SIZE = SIZE_OF_ATTRIBUTE(Row, username);
static const uint32_t EMAIL_SIZE = SIZE_OF_ATTRIBUTE(Row, email);
static const uint32_t ID_OFFSET = 0;
static const uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
static const uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;
static const uint32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;

void serialize_row(Row *, void *);
void deserialize_row(void *, Row *);

#endif