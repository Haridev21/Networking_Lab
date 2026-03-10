#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX 10


void multiply(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX],
              int r1, int c1, int r2, int c2)
{
    int i, j, k;

    for (i = 0; i < r1; i++) {
        for (j = 0; j < c2; j++) {
            C[i][j] = 0;
            for (k = 0; k < c1; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main()
{
    int sockfd, newsockfd;
    struct sockaddr_in server, client;
    socklen_t len;

    int r1, c1, r2, c2;
    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8121);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr*)&server, sizeof(server));
    listen(sockfd, 5);

    printf("Server waiting...\n");

    len = sizeof(client);
    newsockfd = accept(sockfd, (struct sockaddr*)&client, &len);

    // Receive dimensions
    read(newsockfd, &r1, sizeof(int));
    read(newsockfd, &c1, sizeof(int));
    read(newsockfd, &r2, sizeof(int));
    read(newsockfd, &c2, sizeof(int));

    // Receive matrices
    read(newsockfd, A, sizeof(A));
    read(newsockfd, B, sizeof(B));

    // Multiply
    multiply(A, B, C, r1, c1, r2, c2);

    // Send result
    write(newsockfd, C, sizeof(C));

    close(newsockfd);
    close(sockfd);

    return 0;
}