#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jsiss.h"


int main() {
    char buffer[] =
    "POST /users?notify=true HTTP/1.1\r\n"
    "Host: localhost:8080\r\n"
    "Accept: application/json\r\n"
    "Content-Type: application/json\r\n"
    "Authorization: Bearer example-token\r\n"
    "Content-Length: 23\r\n"
    "\r\n\r\n"
    "{\"name\":\"Max\",\"age\":19}";

    /*size_t bufferLength = sizeof(buffer) - 1;
    struct HttpRequest req = ParseBufferToRequest(buffer, bufferLength);

    printf(req.httpMethod);
    printf(req.path);
    printf(req.httpVersion);*/

    char *s;
    size_t index;

    s=strstr(buffer, " ");

    if (s != NULL)                     // if successful then s now points at "hassasin"
        {
            printf("Found string at index = %d\n", s - buffer);
            index = s - buffer;
        }                                  // index of "hassasin" in buff can be found by pointer subtraction
        else
        {
            printf("String not found\n");  // `strstr` returns NULL if search string not found
        }

    buffer[index] = '\0';

    char *s2;
    s2=strstr(&buffer[index + 1], " ");

    if (s2 != NULL)                     // if successful then s now points at "hassasin"
        {
            printf("Found string at index = %d\n", s2 - buffer);
        }                                  // index of "hassasin" in buff can be found by pointer subtraction
        else
        {
            printf("String not found\n");  // `strstr` returns NULL if search string not found
        }

    printf(s2);


    return 0;
}

/*int main() {
    //create socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSocket < 0) {
        perror("socket");
        return 1;
    }
    printf("THE SOCKET IS OPEN\n");

    //server address
    struct sockaddr_in serveraddr = {0}, clientaddr = {0};
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8080);
    serveraddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    int reuse = 1;

    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        perror("setsockopt");
        close(serverSocket);
        return 1;
    }
    
    //bind server address
    if(bind(serverSocket, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0) {
        perror("bind");
        close(serverSocket);
        return 1;
    }
    printf("THE BIND WORKED\n");
    
    // listen
    if(listen(serverSocket, 10) < 0) {
        perror("listen");
        close(serverSocket);
        return 1;
    }

    printf("LISTENING ON PORT %d...\n", ntohs(serveraddr.sin_port));

    char responseMessage[] =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: 11\r\n"
        "Connection: close\r\n"
        "\r\n"
        "Hello World";

    // accept client
    while(1) {
        socklen_t clientaddr_len = 0;
        int clientSocket = 0;
        ssize_t bytesReceived = 0;
        char buffer[1024] = {0};
        size_t responseLength = 0;
        size_t totalBytesSend = 0;
        ssize_t currentBytesSend = 0;


        printf("WAITING FOR CLIENT...\n");
        clientaddr_len = sizeof(clientaddr);
        clientSocket = accept(serverSocket, (struct sockaddr *) &clientaddr, &clientaddr_len);
        if(clientSocket < 0) {
            perror("accept");
            continue;
        }
        printf("CLIENT CONNECTED\n");

        bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if(bytesReceived < 0) {
            perror("recv");
            close(clientSocket);
            continue;
        }
        if(bytesReceived == 0) {
            printf("CLIENT ENDED CONNECTION\n");
            close(clientSocket);
            continue;
        }
        printf("RECEIVED MESSAGE");
        buffer[bytesReceived] = '\0';
        printf("%s\n", buffer);

        responseLength = sizeof(responseMessage) - 1;
        totalBytesSend = 0;

        while(totalBytesSend < responseLength) {
            currentBytesSend = send(clientSocket, responseMessage + totalBytesSend, responseLength - totalBytesSend, MSG_NOSIGNAL);
            if(currentBytesSend == 0) {
                break;
            }
            if(currentBytesSend < 0) {
                perror("send");
                close(clientSocket);
                break;
            }
            printf("Bytes send: %zd\n", currentBytesSend);
            totalBytesSend += currentBytesSend;
        }
        close(clientSocket);
    }

    close(serverSocket);
    return 0;
}

*/