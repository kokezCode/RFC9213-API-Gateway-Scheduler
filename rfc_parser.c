#include "rfc_parser.h"
#include <string.h>
#include <stdlib.h>

ParseResult rfc_parse(const char *header, int *u, bool *i) {
    *u = DEFAULT_URGENCY;
    *i = false;

    if (!header || strlen(header) == 0) return PARSE_OK;

    // Urgency (u=) kontrolü
    const char *u_ptr = strstr(header, "u=");
    if (u_ptr) {
        int val = atoi(u_ptr + 2);
        if (val < 0 || val > 7) {
            *u = DEFAULT_URGENCY; // Graceful degradation
            return PARSE_INVALID_VAL;
        }
        *u = val;
    }

    // Incremental (i) kontrolü: i varsa true, i=?0 varsa false
    if (strstr(header, "i")) {
        if (strstr(header, "i=?0")) *i = false;
        else *i = true;
    }

    return PARSE_OK;
}

const char* rfc_urgency_to_string(int urgency) {
    switch(urgency) {
        case 0: return "CRITICAL";
        case 1: return "HIGH";
        case 3: return "DEFAULT";
        case 7: return "LOW/BACKGROUND";
        default: return "NORMAL";
    }
}