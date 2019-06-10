#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
int main(int argc, char *argv[]){
    struct sockaddr_in sa = { 0 };
    int len;
    char buff[4096];
    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    // 通信相手のソケットアドレスを作成
    sa.sin_family = AF_INET;
    sa.sin_port = htons(atoi(argv[2])); //host 2 network short
    sa.sin_addr.s_addr = inet_addr(argv[1]);

    while (0 < (len = read(0, buff, 256))){
        sendto(sock, buff, len - 1, 0, (struct sockaddr*)&sa, sizeof(sa));
    }
    close(sock);
    return 0;
    
}