#include <string.h>

#include "row.h"


void serialize_row(Row *source, void *destination) {
    memcpy(destination + ID_OFFSET, &source->id, ID_SIZE);
    strncpy(destination + USERNAME_OFFSET, source->username, USERNAME_SIZE);  // by doing strncpy all bytes are initialized (empty to 0)
    strncpy(destination + EMAIL_OFFSET, source->email, EMAIL_SIZE);
}

void deserialize_row(void *source, Row *destination) {
    memcpy(&(destination)->id, source + ID_OFFSET, ID_SIZE);
    memcpy(&(destination)->username, source + USERNAME_OFFSET, USERNAME_SIZE);
    memcpy(&(destination)->email, source + EMAIL_OFFSET, EMAIL_SIZE);
}