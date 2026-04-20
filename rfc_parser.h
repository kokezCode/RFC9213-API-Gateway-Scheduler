#ifndef RFC_PARSER_H
#define RFC_PARSER_H

#include "http_request.h"

#define DEFAULT_URGENCY 3

typedef enum {
    PARSE_OK,
    PARSE_INVALID_VAL,
    PARSE_ERR
} ParseResult;

ParseResult rfc_parse(const char *header, int *u, bool *i);
const char* rfc_urgency_to_string(int urgency);

#endif