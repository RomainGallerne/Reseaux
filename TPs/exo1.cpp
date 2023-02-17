#include <string.h>//pour memcpy au moins
#include <stdio.h>//perror
#include <sys/types.h>
#include <sys/socket.h>//constantes, sockaddr generique, socket...
#include <stdlib.h>
#include <netdb.h>
#include "sockdist.h"
#include "sock.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <limits.h>

int main(int argc, char* argv[]){
    struct addrinfo *infosPointeur;
    struct in_addr imp;
    char host[HOST_NAME_MAX];
    char service[HOST_NAME_MAX];

    struct addrinfo infos = {
        AI_CANONNAME,
        PF_UNSPEC,
        SOCK_STREAM,
        0,
        0,
        NULL,
        NULL,
        NULL
    };

    if(getaddrinfo(argv[1], 0, &infos, &infosPointeur)){
        cout << "Erreur de getAddrInfo\n";
        exit(EXIT_FAILURE);
    }
    else {
        if(getnameinfo(infosPointeur->ai_addr,infosPointeur->ai_addrlen,host,sizeof(host),service,sizeof(service),NI_NUMERICHOST)){
            cout << "Erreur de getNameInfo\n";
            exit(EXIT_FAILURE);  
        }
        else {
            cout << "\nNome de la machine : " << infosPointeur->ai_canonname;
            inet_aton(argv[1],&imp);
            cout << "\nAdresse IPv4 de la machine : " << inet_ntoa(imp);
            cout << "\nL'hôte est : " << host;
            cout << "\nLe service est : " << service  << "\n\n";
            return 0;
        }
    }
}