#include <stdio.h>//perror
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


using namespace std;

int main(int argc, char* argv[]){
    if(argc<2){
        cout << "Entrez le nom de la machine\n";
        exit(-1);
    }
    /* demande de BR locale */
    Sock BRLoc(SOCK_DGRAM, (short)31470,0) ;
    int descbreLoc ;
    /* on recupere le descripteur */
    if (BRLoc.good()){
        descbreLoc=BRLoc.getsDesc();
    }
    else {
        cout<<"\nprobleme de BR locale"<<endl;
        exit(1) ;
    }
    /* désignation BR distante */
    SockDist saBr(argv[1],(short)31469);
    socklen_t lgEnvoi= saBr.getsLen();
    sockaddr_in *adrsaBr= saBr.getAdrDist();

    char msg[8192];
    string getMsg;
    string stop = "stop";

    char tamponReception[8192];
    int lgReception=sizeof(tamponReception);

    while(msg != stop){
        cout << "Moi : "; 
    
        //cin >> msg;
        getline(cin, getMsg);
        strcpy(msg, getMsg.c_str());

        /* on expédie */
        int retourSend=sendto(descbreLoc, msg, sizeof(msg),0,(sockaddr*)adrsaBr, lgEnvoi);
        if(retourSend < 0){
            cout << "Erreur : Message non envoyé\n";
        }
        /* et on reçoit*/
        int retourRecv=recvfrom(descbreLoc, tamponReception,lgReception, 0,NULL,NULL);
        if(retourRecv < 0){
            cout << "Erreur lors de la réception du message\n";
        }
        tamponReception[retourRecv] = '\0';
        cout <<  argv[1] << " : " << tamponReception << "\n";
    }
}