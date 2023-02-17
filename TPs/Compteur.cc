/* Serveur qui ne fait que r�pondre le m�me texte �tout message, quel que
   soit son contenu.  On pourrait pr�voir par la suite une r�ponse en
   fonction du texte exp�di�. */

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

#define MAXBUF 8192

int main(int argc, char*argv[]){

  /* On ne tient pas compte du nombre de param�tres. Il ne devrait
     pas y en avoir mais au c�s ou */

  /* Une BR locale cf Cours*/
  Sock maBR (SOCK_DGRAM, (short)31469, 0);
  int descmaBR;
  if (maBR.good()) 
    descmaBR=maBR.getsDesc();//on recupere le descripteur
  else 
    {
      cout<<"pb BR locale"<<endl;
      exit(1);
    }

  //On pr�pare le n�cessaire pour reconna�tre l'expediteur
  // et r�cup�rer son message.
  SockDist sexpInconnu;
  socklen_t lgInconnuInit = sexpInconnu.getsLen();
  sockaddr_in *adrexpInconnu = sexpInconnu.getAdrDist();
    
    
  
  char tamponReception[MAXBUF];
  int lgReception=sizeof(tamponReception);

  int nombreReception = 0;
  string message;
  char messageChar[MAXBUF];
  string stop = "stop";
   
  cout<<"Serveur en route"<<endl;
  
  while (tamponReception != stop){

    socklen_t lgInconnu = lgInconnuInit;
    
    int retourRecv=recvfrom(descmaBR, tamponReception, lgReception, 0,(sockaddr *)adrexpInconnu, &lgInconnu);
    if (retourRecv < 0){
	    cout <<"probl�me � la r�ception"<<endl;
	    exit(1);
    }
    else{
      nombreReception+=1;
      message = "Vous avez envoyé " + to_string(nombreReception);
      if(nombreReception == 1){
        message += " message sur notre serveur";
      }
      else {
        message += " messages sur notre serveur";
      }
      if(tamponReception == stop){
        message = "Signal stop -> fermeture du serveur";
      }
      strcpy(messageChar, message.c_str());
      int retourSend=sendto(descmaBR, messageChar, retourRecv, 0,(sockaddr *)adrexpInconnu, lgInconnu);
    }
  }
  close(descmaBR);
  exit(0);
}
