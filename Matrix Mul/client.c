#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX 10

int main()
{
    int sockfd;
    struct sockaddr_in server;

    int r1, c1, r2, c2;
    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    int i, j;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8121);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockfd, (struct sockaddr*)&server, sizeof(server));

    printf("Enter rows and cols of Matrix A: ");
    scanf("%d %d", &r1, &c1);

    printf("Enter rows and cols of Matrix B: ");
    scanf("%d %d", &r2, &c2);

    if (c1 != r2) {
        printf("Matrix multiplication not possible\n");
        return 0;
    }

    printf("Enter Matrix A:\n");
    for (i = 0; i < r1; i++)
        for (j = 0; j < c1; j++)
            scanf("%d", &A[i][j]);

    printf("Enter Matrix B:\n");
    for (i = 0; i < r2; i++)
        for (j = 0; j < c2; j++)
            scanf("%d", &B[i][j]);

    // Send dimensions
    write(sockfd, &r1, sizeof(int));
    write(sockfd, &c1, sizeof(int));
    write(sockfd, &r2, sizeof(int));
    write(sockfd, &c2, sizeof(int));

    // Send matrices
    write(sockfd, A, sizeof(A));
    write(sockfd, B, sizeof(B));

    // Receive result
    read(sockfd, C, sizeof(C));

    printf("\nResult Matrix:\n");
    for (i = 0; i < r1; i++) {
        for (j = 0; j < c2; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    close(sockfd);
    return 0;
}