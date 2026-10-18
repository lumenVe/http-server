#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h> 

#include "jsiss.h"

static int g_server_fd = 0;

int jssis_GetSocket() {
    return g_server_fd;
}

void ParseQuery(char *buffer, struct HttpRequest *req, size_t startPos, size_t endPos) {
    size_t currentQueryPos = startPos;
    size_t queryCounter = 1;

    //search query amount
    while(buffer[currentQueryPos] != ' ' && currentQueryPos < endPos) {
        if(buffer[currentQueryPos] == '&') { queryCounter++; }
        currentQueryPos++;
    }
    //TODO: not closed
    struct QueryEntry *queryArray = malloc(sizeof(struct QueryEntry[queryCounter])); 
    req->query = queryArray;
    currentQueryPos = startPos;

    for(size_t i = 0; i < queryCounter; i++) {
        queryArray[i].name = &buffer[currentQueryPos];
        while(buffer[currentQueryPos] != '=' && currentQueryPos < endPos) { currentQueryPos++; }
        buffer[currentQueryPos] = '\0';
        currentQueryPos++;
        queryArray[i].value = &buffer[currentQueryPos];
        while(buffer[currentQueryPos] != '&' && currentQueryPos < endPos) { currentQueryPos++; }
        buffer[currentQueryPos] = '\0';
        currentQueryPos++;
    } 
}

// expects null terminated request line
size_t ParseRequestLine(char *buffer, struct HttpRequest *req) {
    char *endWordPosPointer = NULL;
    size_t endWordPosIndex = 0;
    // search buffer for httpMethod
    req->httpMethod = &buffer[0];
    endWordPosPointer = strstr(buffer, " ");
    if(endWordPosPointer != NULL) {
        endWordPosIndex = endWordPosPointer - buffer;
    } else {
        return -1;
    }

    buffer[endWordPosIndex] = '\0';
    
    // search path

    req->path = &buffer[endWordPosIndex + 1];
    endWordPosPointer = strstr(&buffer[endWordPosIndex + 1], " ");

    if(endWordPosPointer != NULL) {
        endWordPosIndex = endWordPosPointer - buffer;
        buffer[endWordPosIndex] = '\0';
        size_t startPos = endWordPosIndex + 1;
        endWordPosPointer = strstr(&buffer[endWordPosIndex + 1], " ");
    } else {
        return -1;
    }



    

    // parse query if existing
    //if(buffer[currentReqLinePos] == '?') {
    //    buffer[currentReqLinePos] = '\0';
     //   currentReqLinePos++;
     //   size_t startPos = currentReqLinePos;
    //    while(buffer[currentReqLinePos] != ' ' && currentReqLinePos < endPos) { currentReqLinePos++; }
     //   ParseQuery(buffer, req, startPos, currentReqLinePos);
    //}

    //buffer[currentReqLinePos] = '\0';
    // currentReqLinePos++;

    //req->httpVersion = &buffer[currentReqLinePos];
    //while(buffer[currentReqLinePos] != '\r' && buffer[currentReqLinePos] != '\n' && currentReqLinePos < endPos) {currentReqLinePos++;}
    //buffer[currentReqLinePos] = '\0';
}

void ParseHeader(char *buffer, size_t bufferSize, size_t startPos, size_t endPos) {

}

// expects a buffer > 0 that is already terminated
struct HttpRequest ParseBufferToRequest(char *buffer, size_t bufferSize) {
    struct HttpRequest req = {0};

    size_t requestLineEndPos = ParseRequestLine(buffer, &req);
    
    return req;
}

bool jsiss_Init(int domain, int type, int protocol, in_port_t host, in_addr_t address) {
    g_server_fd = socket(domain, type, protocol);
    if(g_server_fd < 0) {
        perror("socket");
        return 0;
    }

    struct sockaddr_in serverAddress = {0};
    serverAddress.sin_family = type;
    serverAddress.sin_port = host;
    serverAddress.sin_addr.s_addr = address;

    if(bind(g_server_fd, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
        perror("bind");
        close(g_server_fd);
        return 0;
    }
}

bool jsiss_Run() {
    if(listen(g_server_fd, 10) < 0) {
        perror("listen");
        close(g_server_fd);
        return 0;
    }
    
}

bool jsiss_Stop() {
    close(g_server_fd);
}