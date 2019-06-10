# include <stdlib.h> // atoi
# include <stdio.h> // printf
# include <unistd.h> // close
# include <sys/socket.h> // socket
# include <arpa/inet.h> //inet_addr, htons, inet_ntoa, ntohs

#define CHECK_CLIENT 1

int main(int argc, char *argv[]){
    int len;
    char buff[4096];
    // https://sscrisk.hatenablog.com/entries/2006/12/12
    struct sockaddr_in sa = { 0 }; 

    #if CHECK_CLIENT
    struct sockaddr_in sa2 = { 0 };
    int sa_len;
    #endif

    int opt = 1;
    // http://neineigh.hatenablog.com/entry/2013/09/28/185053
    // https://linuxjm.osdn.jp/html/LDP_man-pages/man2/socket.2.html
    int sock = socket(AF_INET, SOCK_DGRAM, 0);


    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // 自分用のソケットアドレスの作成
    sa.sin_family = AF_INET;
    sa.sin_port = htons(atoi(argv[1]));
    sa.sin_addr.s_addr = inet_addr("0.0.0.0");

    //ソケットアドレスをバインド
    bind(sock, (struct sockaddr*)&sa, sizeof(struct sockaddr_in));
    while (1){
#if CHECK_CLIENT // 送信元を特定する場合
        sa_len = sizeof(struct sockaddr_in);
        len = recvfrom(sock, buff, 4096, 0, (struct sockaddr *)&sa2, &sa_len);
        buff[len] = '\0';
        printf("[%s:%d] %s\n", inet_ntoa(sa2.sin_addr), ntohs(sa2.sin_port), buff);
        // sendto(sock, buff, len - 1, 0, (struct sockaddr*)&sa, sizeof(sa)); //add
        buff[0] = '\0';
#else //特定しない場合
        len = recvfrom(sock, buff, 4096, 0, NULL, NULL);
        write(fd, buff, len);
#endif 
    }
    close(sock);
    return 0;


}
