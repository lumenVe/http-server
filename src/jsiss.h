#pragma once

struct HttpHeaderEntry {
    char *name;
    char *value;
};
struct QueryEntry {
    char *name;
    char *value;
};

struct HttpRequest ParseBufferToRequest(char *buffer, size_t bufferSize);

struct HttpRequest {
    char *httpMethod;
    char *path;
    struct QueryEntry *query;
    char *httpVersion;
    struct HttpHeaderEntry header[32];
    size_t headerEntries;
    char *body;
    size_t bodyLength;
};