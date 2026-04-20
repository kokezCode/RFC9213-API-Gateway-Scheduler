#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <stdbool.h>

/**
 * HttpRequest Struct
 * RFC 9213 parametrelerini ve sistem meta verilerini tutar.
 */
typedef struct {
    int id;             /* İstek ID'si */
    int urgency;        /* RFC 9213: 0-7 arası öncelik değeri (0 en yüksek) */
    bool incremental;   /* RFC 9213: Yanıtın parçalı işlenebilirliği (i) */
    char *path;         /* Dinamik olarak ayrılmış URL yolu (malloc ile) */
} HttpRequest;

#endif