#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>

int main(int argc, char *argv[]) {
    int len;
    char buff[4096];
    struct sockaddr_in sa = {0}; //ソケットアドレス格納用 sockaddr_in の実装を見ろ
    int opt = 1;
    int lsock, csock;
    getchar();
    signal(SIGCHLD, SIG_IGN); //ここで「chldシグナルを無視」の意図がわからない... ゾンビプロセス　#とは 
    lsock = socket(AF_INET, SOCK_STREAM, 0); //ソケット生成らしい。 lsockがソケット所持
    setsockopt(lsock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)); //ソケットのオプション...?要調査

    sa.sin_family = AF_INET; //構造体に入れてるだけ。 sockaddr_inを見る
    sa.sin_port = htons(atoi(argv[1]));
    sa.sin_addr.s_addr = inet_addr("0.0.0.0");

    // ソケットアドレスをバインド
    bind(lsock, (struct sockaddr *)&sa, sizeof(struct sockaddr_in));
    
    //リスニングソケットにする。
    listen(lsock, SOMAXCONN)// /proc/sys/net/core/somaxconn
    while(1) {
        csock = accept(lsock, NULL, NULL);
        if (fork() == 0) {
            close(lsock);
            printf("...Start Child Proc:%d\n", getpid());
            while (0 < (len = recv(csock, buff, 4096, MSG_NOSIGNAL)))
        }
    }

}