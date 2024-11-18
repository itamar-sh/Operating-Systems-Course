#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <netdb.h>
#include <stdbool.h>

#define MAXHOSTNAME 256
#define BUFF_SIZE 256

#define  FUNC_ERROR "system error: %s\n"
#define STRTOL_ERROR_MSG "strtol fail"
#define SOCKET_ERROR_MSG "find socket fail"
#define WRITE_FAIL "write func fail"
#define READ_FAIL "read func fail"
#define ESTABLISH_ERROR "establish func fail"
#define SERVER "server"
#define CLIENT "client"

/*
 * function declarations
 */
void server(char* argv[]);
int client(int argc, char* argv[]);
int establish(unsigned short portnum);
int get_connection(int s);
int read_data(int s, char *buf, int n);
int write_data(int s, int argc, char* argv[]);
int call_socket(char *hostname, unsigned short portnum);

/**
 * main func will run from it - deal with either server or client input
 * @param argc num of args
 * @param argv array of char* of input
 * @return 0 in success
 */
int main(int argc, char* argv[]) {
    if(strcmp(argv[1], SERVER) == 0){
        server(argv);
    }
    if(strcmp(argv[1], CLIENT) == 0){
        client(argc, argv);
    }
    return 0;
}

/**
 * server mode - 1) we open a port in a server
 * 2) we run and wait for connection of clients
 * @param argv the port number
 * @return never return a value since the server run forever
 */
void server(char* argv[]){
    char *ptr;
    short port_of_client = strtol(argv[2], &ptr, 10);
    if(port_of_client == 0){
        fprintf(stderr, FUNC_ERROR, STRTOL_ERROR_MSG);
        exit(1);
    }
    int server_num = establish(port_of_client);
    if(server_num == -1){
        fprintf(stderr, FUNC_ERROR, ESTABLISH_ERROR);
        exit(1);
    }
    while(true){
        int t = get_connection(server_num);
        char buff[BUFF_SIZE];
        if(t != -1){
            read_data(t, buff, BUFF_SIZE);
            system(buff);
        }
        close(t);
    }
}

/**
 * client mode: try to call a socket that connect to a server and run a command in the server
 * @param argc num of args
 * @param argv array of char* of input
 * @return 0 in success
 */
int client(int argc, char* argv[]){
    char *ptr;
    short port_of_server = strtol(argv[2], &ptr, 10);
    if(port_of_server == 0){
        fprintf(stderr, FUNC_ERROR, STRTOL_ERROR_MSG);
        exit(1);
    }
//    short port_of_server = atoi(argv[2]);
    char myname[MAXHOSTNAME+1];
    gethostname(myname, MAXHOSTNAME);
    int s = call_socket(myname, port_of_server);
    if(s == -1){
        fprintf(stderr, FUNC_ERROR, SOCKET_ERROR_MSG);
        exit(1);
    }
    write_data(s, argc, argv);
    close(s);
    return 0;
}

/**
 *
 * @param s - the file descriptor to write to
 * @param argc num of args
 * @param argv array of char* of input
 * @return 0 in success
 */
int write_data(int s, int argc, char* argv[]){
    char word[BUFF_SIZE] = "";
//    int br_index = 0;
    for (int i = 3; i < argc; i++) { /* loop until full buffer */
        strcat(word, argv[i]);
        if (i != argc - 1){
            strcat(word, " ");
        }
    }
    int n = strlen(word);
    if(write(s, word, n+1) == -1){
        fprintf(stderr, FUNC_ERROR, WRITE_FAIL);
        exit(1);
    }
    return 0;
}

/**
 *
 * @param s - the file descriptor to read from
 * @param buf - buffer to put the data we have read inside him
 * @param n - num of max size of msg to read
 * @return 0 on success
 */
int read_data(int s, char *buf, int n) {
    int bcount;       /* counts bytes read */
    int br;               /* bytes read this pass */
    bcount= 0;

    while (bcount < n) { /* loop until full buffer */
        br = read(s, buf, n-bcount);
        if (br > 0){
            bcount += br;
            buf += br;
        }
        if (br == 0) {
            return(bcount);
        }
        if(br == -1){
            fprintf(stderr, FUNC_ERROR, READ_FAIL);
            exit(1);
        }
    }
    return(bcount);
}

int establish(unsigned short portnum) {
    char myname[MAXHOSTNAME+1];
    int s;
    struct sockaddr_in sa;
    struct hostent *hp;
    //hostnet initialization
    gethostname(myname, MAXHOSTNAME);
    hp = gethostbyname(myname);
    if (hp == NULL)
        return(-1);
    //sockaddrr_in initlization
    memset(&sa, 0, sizeof(struct sockaddr_in));
    sa.sin_family = hp->h_addrtype;
    /* this is our host address */
    memcpy(&sa.sin_addr, hp->h_addr_list[0], hp->h_length);
    /* this is our port number */
    sa.sin_port= htons(portnum);
    /* create socket */
    if ((s= socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return(-1);

    if (bind(s , (struct sockaddr *)&sa , sizeof(struct sockaddr_in)) < 0) {
        close(s);
        return(-1);
    }

    listen(s, 5); /* max # of queued connects */
    return(s);
}

/**
 * @param s number of socket to connect to
 * @return  return file descriptor if succes or -1 if fail
 */
int get_connection(int s) {
    int t; /* socket of connection */
    if ((t = accept(s,NULL,NULL)) < 0)
        return -1;
    return t;
}

int call_socket(char *hostname, unsigned short portnum) {
    struct sockaddr_in sa;
    struct hostent *hp;
    int s;

    if ((hp= gethostbyname(hostname)) == NULL) {
        return(-1);
    }

    memset(&sa,0,sizeof(sa));
    memcpy((char *)&sa.sin_addr , hp->h_addr_list[0] ,hp->h_length);
    sa.sin_family = hp->h_addrtype;
    sa.sin_port = htons(portnum);
    if ((s = socket(hp->h_addrtype,SOCK_STREAM,0)) < 0) {
        return(-1);
    }
    if (connect(s, (struct sockaddr *)&sa , sizeof(sa)) < 0) {
        close(s);
        return(-1);
    }
    return(s);
}
