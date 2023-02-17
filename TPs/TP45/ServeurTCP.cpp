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
#include <cstring>
#include <unistd.h>
  using namespace std;

#include "sock.h"
#include "sockdist.h"

#define MAXBUF 256

int main(int argc, char*argv[]){

    /* On ne tient pas compte du nombre de param�tres. Il ne devrait
     pas y en avoir mais au c�s ou */

    /* Une BR locale cf Cours*/
    Sock BrPub (SOCK_STREAM, (short)21345, 0);
    int descBrPub;
    if (BrPub.good()) 
        descBrPub=BrPub.getsDesc();//on recupere le descripteur
    else 
    {
      cout<<"pb BR locale"<<endl;
      exit(1);
    }

    cout<<"Serveur en attente de connexion..."<<endl;

    int estin = listen(descBrPub,5);
    struct sockaddr_in brCv;
    socklen_t lgbrCv = sizeof(struct sockaddr_in);
    int descBrCv = accept(descBrPub,(struct sockaddr *)&brCv, &lgbrCv);
    if(descBrCv < 0){
        cout << "Erreur lors de la connection" << endl;
        close(descBrPub);
        exit(1);
    } 

    char tamponReception[MAXBUF];

    string message;
    char messageChar[MAXBUF];
    string stop = "stop";
    char msg[8192];
    string getMsg;
   
    cout<<"Connexion établie"<<endl;

    while (tamponReception != stop && getMsg != stop){
        cout << "Moi : ";
        getline(cin, getMsg);
        strcpy(messageChar, getMsg.c_str());
        int retourSend=send(descBrCv, messageChar, MAXBUF+1, 0);
        if (retourSend < 0){
	        cout <<"problème lors de l'envoi"<<endl;
            close(descBrPub);
	        exit(1);
        }
        if(retourSend == 0){
            cout << "Client déconnecté\n";
            close(descBrPub);
            exit(1);
        }

        int retourRecv=recv(descBrCv, tamponReception, MAXBUF+1, 0);
        if (retourRecv < 0){
	        cout <<"problème à la réception"<<endl;
            close(descBrPub);
	        exit(1);
        }
        else{
            cout <<  "Client : " << tamponReception << "\n";
            if(tamponReception == stop || getMsg == stop){
                message = "Signal stop -> fermeture du serveur";
            }
            strcpy(tamponReception, "\0");
        }
    }
    close(descBrPub);
    exit(0);
}