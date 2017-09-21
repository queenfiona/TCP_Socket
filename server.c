#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#define SIZE 50

int determinant(int matrix[SIZE][SIZE],int t);
int main(){
	struct sockaddr_in address;
	struct sockaddr_storage server_storage;
	socklen_t addrlen;
	int server_sock,new_connection;
	
	if ((server_sock=socket(AF_INET,SOCK_STREAM,0))==0)
	{
		printf("Failed to create socket\n");
	}
	memset(&address, '0', sizeof(address));
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=htonl(INADDR_ANY);
	address.sin_port=htons(8080);

	bind(server_sock,(struct sockaddr *)&address,sizeof(address));
	if(listen(server_sock,5)>=0){
		printf("Listening for connection...\n");
	}
	addrlen= sizeof(server_storage);
	new_connection=accept(server_sock,(struct sockaddr *)&server_storage,&addrlen);
	if(new_connection<0){
		printf("Failed to connect.\n");
	}else{
		int matrix[SIZE][SIZE]={{0},{0}},order=0,d=0;
		recv(new_connection,&matrix,sizeof(matrix),0);
		recv(new_connection,&order,sizeof(order),0);
		printf("The order of the matrix is %d\n",order);
		printf("The matrix from the client is :\n");
		for (int i = 1; i <= order; ++i){
			for (int j = 1; j<= order; ++j){
				printf("%d\t",matrix[i][j] );
			}	
			printf("\n");	
		}
		d=determinant(matrix,order);
		printf("The determinant of the matrix is:%d\n",d);
		send(new_connection,&d,sizeof(d),0);
	}
	
	close(new_connection);
	close(server_sock);
	return 0;
}

int determinant(int matrix[SIZE][SIZE],int x){
	int pr,c[SIZE],d=0,tempMatrix[SIZE][SIZE],j,p,q,t;
  if(x==2){
  	d=0;
    d=(matrix[1][1]*matrix[2][2])-(matrix[1][2]*matrix[2][1]);
    return(d);
  }else{
    for(j=1;j<=x;j++){  
    	int r=1,s=1;
    	for(p=1;p<=x;p++){
    		for(q=1;q<=x;q++){
    			if(p!=1&&q!=j){
    				tempMatrix[r][s]=matrix[p][q];
    				s++;
    				if(s>x-1){
    					r++;
    					s=1;
    				}
    			}
    		}
    	}
    	for(t=1,pr=1;t<=(1+j);t++)
    	pr=(-1)*pr;
    	c[j]=pr*determinant(tempMatrix,x-1);
    }
    for(j=1,d=0;j<=x;j++){
    	d=d+(matrix[1][j]*c[j]);
    }
    return(d);
   }
}