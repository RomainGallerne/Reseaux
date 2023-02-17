#include <stdio.h> //perror
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <iostream>
#include "sock.h"
#include "sockdist.h"
#include <limits>
#include <cstring>
#include <unistd.h>

#define MAXBUF 8192
using namespace std;

int main(int argc, char* argv[]){
    if(argc<2){
        cout << "Entrez le nom de la machine\n";
        exit(-1);
    }
    /* demande de BR locale */
    Sock BrClient(SOCK_STREAM, (short)21346,0) ;
    int descBrClient;
    /* on recupere le descripteur */
    if (BrClient.good()){
        descBrClient=BrClient.getsDesc();
    }
    else {
        cout<<"\nprobleme de BR locale"<<endl;
        exit(1) ;
    }
    SockDist BrPub(argv[1],short(21345));
    struct sockaddr_in * adrBrPub=BrPub.getAdrDist();
    int lgAdrBrPub=sizeof(struct sockaddr_in);
    int erlude = connect(descBrClient,(struct sockaddr *)adrBrPub,lgAdrBrPub);
    if (erlude < 0){
        cout << "Erreur lors de la connection\n";
        close(descBrClient);
        exit(1);
    }

    char tamponReception[MAXBUF];
    int lgReception=sizeof(tamponReception);
    char msg[8192];
    string getMsg;
    string stop = "stop";

    while(msg != stop){
        /* et on reçoit*/
        int retourRecv=recv(descBrClient, tamponReception,lgReception, 0);
        if(retourRecv < 0){
            cout << "Erreur lors de la réception du message\n";
            close(descBrClient);
            exit(1);
        }
        else {
            cout <<  argv[1] << " : " << tamponReception << "\n";

            /* on expédie */
             cout << "Moi : "; 
            //cin >> msg;
            getline(cin, getMsg);
            strcpy(msg, getMsg.c_str());
            int retourSend=send(descBrClient, msg, sizeof(msg),0);
            if(retourSend < 0){
                cout << "Erreur : Message non envoyé\n";
                close(descBrClient);
                exit(1);
            }
            if(retourSend == 0){
                cout << "Serveur déconnecté\n";
                close(descBrClient);
                exit(1);
            }
        }
    }
    close(descBrClient);
    exit(0);
}

    