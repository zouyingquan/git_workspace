#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<mysql.h>
#include<time.h>
#define MAXLINE 80
#define SERV_PORT 8000
#define SIZE 100

char str_time[SIZE];

char* get_ctime()
{
	time_t t;
	time(&t);
	strftime(str_time,SIZE,"%Y%m%d%H%M%S",localtime(&t));
	return str_time;
}

void Insert(MYSQL *p,char *getbuf ,int flag)
{
    int res;
    char sql[SIZE];
    char *endp;
    int xl;
    float tw;
    char *s = get_ctime();
    if(flag){
    	xl = atoi(getbuf);
        sprintf(sql,"insert into xl values(null,%d,%s)",xl,s);
    }
    else{
     	tw = strtof(getbuf,&endp);
        sprintf(sql,"insert into tw values(null,%.2f,%s)",tw,s);
    }
    res = mysql_query(p,sql);
    if(!res) printf("Inserted %lu rows\n",(unsigned long)mysql_affected_rows(p));
    else fprintf(stderr,"Insert error %d:%s\n",mysql_errno(p),mysql_error(p));
}




int main()
{
    struct sockaddr_in servaddr,cliaddr;
    socklen_t cliaddr_len;
    int listenfd,connfd;
    char buf[MAXLINE];
    int i,n,x,flag = 0;
    float t;
    char* pend;
    MYSQL *conn_ptr;
    conn_ptr = mysql_init(NULL);
    if(!conn_ptr){
    	printf("mysql init failed\n");
    }
    conn_ptr = mysql_real_connect(conn_ptr,"localhost","root","062411","zyq",0,NULL,0);
    if(!conn_ptr) printf("COnnection failed..\n");


    listenfd = socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
    listen(listenfd,20);
    printf("Accepting connections..\n");
    while(1){
    	cliaddr_len = sizeof(cliaddr);
	connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&cliaddr_len);
	n = read(connfd,buf,MAXLINE);
		while(1){ 
		   if(n!=0){
		   	 if(n<4){
		  		/* for(i = 0;i<n;i++)printf("%c",buf[i]);
		    		 printf("\n") ;
				 x = atoi(buf);*/
				 Insert(conn_ptr,buf,1);
			 }
			 else{
		  		/* for(i = 0;i<n;i++)printf("%c",buf[i]);
		    		 printf("\n") ;
				 t = strtof(buf,&pend);*/
				 Insert(conn_ptr,buf,0);
			  }
		   }
		   else{
		   	printf("Client say close the connection..\n");
			break;
		   }
			n = read(connfd,buf,MAXLINE);
		}
	close(connfd);
    }
    mysql_close(conn_ptr);
}
