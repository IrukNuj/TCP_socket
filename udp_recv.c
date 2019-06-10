# include <stdlib.h> // atoi
# include <stdio.h> // printf
# include <unistd.h> // close
# include <sys/socket.h> // socket
# include <arpa/inet.h> //inet_addr, htons, inet_ntoa, ntohs

#define CHECK_CLIENT 1

int main(int argc, char *argv[]){
    int len;
    char buff[4096];
    struct sockaddr_in sa = { 0 };

    #if CHECK_CLIENT
    struct sockaddr_in sa2 = { 0 };
    int sa_len;
    #endif

    int opt = 1;
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // 自分用のソケットアドレスの作成
    sa.sin_family = AF_INET;
    sa.sin_port = htons(atoi(argv[1]));
    sa.sin_addr.s_addr = inet_addr("0.0.0.0")


}
