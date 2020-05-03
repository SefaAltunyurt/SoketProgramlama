#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include <unistd.h>

#define uzunluk 100
int main(){
	int soc,yeni_soket,c_uz,n,sayac=1;
	struct sockaddr_in Adres;
	struct sockaddr_in clientAdress;
	char message[uzunluk];

	soc=socket(AF_INET,SOCK_STREAM,0);
	
	Adres.sin_family=AF_INET;
	Adres.sin_port=htons(9999);
	Adres.sin_addr.s_addr=INADDR_ANY;

	if(bind(soc,(struct sockaddr *)&Adres,sizeof(Adres))<0){
		printf("Soket bulunamadi");
		exit(1);
	}
	else
		printf("Soket olusturuldu\n");

	listen(soc,10);
	printf("Bekliyorum...\n");

	while (1){
		c_uz=sizeof(Adres);
		yeni_soket=accept(soc,(struct sockaddr *)&Adres,&c_uz);

		if(yeni_soket>0){
				printf("%d.Baglanti basarili.\n",sayac);
				sayac++; }	
				 
		else
				printf("Baglantida hata var\n");

		if(!fork()){
			while(1){
				recv(yeni_soket,message,uzunluk,0);	
				n=strlen(message)+1;
				printf("\n Clinet'taki metin : %s",message);
				printf("Client'a metin yaz : %s",message);
				send(yeni_soket,message,n,0);
				}	
			exit(1);
			}
		else{
		close(yeni_soket);
		}
	}
	return 0;
}
