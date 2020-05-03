#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include <arpa/inet.h>
#include<sys/types.h>
#include<string.h>
#include<netinet/in.h>

#define ip "127.0.0.1"
#define mesaj_max 200

int main(){
	printf("\n istemciyi kapatmak istediginiz zaman yaziniz ! ");
	int soc,uz;
	soc=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in Adres;
	char message1[mesaj_max];
	char message2[mesaj_max];

	Adres.sin_family=AF_INET;
	Adres.sin_port=htons(9999);
	Adres.sin_addr.s_addr=inet_addr(ip);
	
	if(connect(soc,(struct sockaddr *)&Adres,sizeof(Adres))<0){
		printf("\n Baglanti kurulamadi");
		exit(1); }
	else
		printf("\n Baglandi.\n");

	while(1){
		
		printf("\n Gondermek icin metin yaziniz : "); 
		fgets(message1,mesaj_max,stdin);

		if(message1[0]=='!') break;

		uz=strlen(message1)+1;
		send(soc,message1,uz,0);
		recv(soc,message2,mesaj_max,0);

		printf("Serverdan gelen metin  : %s",message2);

	}
	return 0;
}
