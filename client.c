#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#define SIZE 50

int main(){
    struct sockaddr_in serv_addr;
    int client_sock=0;
    int matrix[SIZE][SIZE]={{0},{0}};
    int order=0;
    int determinant=0;
    if ((client_sock=socket(AF_INET,SOCK_STREAM,0))< 0){
        printf("Failed to create socket\n");
    }
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_port=htons(8080);
  
    if ((connect(client_sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr)))<0){
        printf("Connection Failed.\n");
    }else{
        printf("Enter the order of the matrix:\n");
        scanf("%d",&order);
        printf("Enter the values into the matrix:\n");
        for (int i = 1; i <= order; ++i){            
            for (int j = 1; j <= order; ++j){
                printf("matrix[%d][%d]:\t",i,j);
                scanf("%d",&matrix[i][j]);           
            }
        }
        printf("The matrix entered is:\n");
        for (int i =1 ; i <= order ; ++i){
            for (int j = 1 ; j <= order; ++j){+
                printf("%d\t",matrix[i][j]);            
            }
            printf("\n");
        }
        send(client_sock ,&matrix ,sizeof(matrix),0 );
        send(client_sock,&order,sizeof(order),0);
        printf("Matrix & order have been sent\n");
        recv(client_sock ,&determinant, sizeof(determinant),0);
        printf("The determinant of the matrix is : %d\n",determinant);       
    }
    close(client_sock);    
    return 0;
}

