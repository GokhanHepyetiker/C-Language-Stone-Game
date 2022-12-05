#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//Oyuncu bilgilerini tutacak olan struct
struct oyuncu{
	int no;
	int mavi[20];
	int kirmizi[20];
};
//Parametre olarak alinan tas degerinin, 0 ve 20 arasinda ve tahtada o konumda tas olup olmadigini kontrol eden metot
//1 donerse gecerli, 0 donerse gecersizdir
int Gecerlimi(int tas,int tahta[20]){
	if(tas<0)return 0;
	else if(tas>20)return 0;
	else{
	    if(tahta[tas]>0)
		return 1;
		else return 0;
	}
}
//Bir oyuncunun elindeki taslara gore, gecerlimi komutunu cagirarak yapilaca hamleyi belirleyen metot
int HamleSec(int renk,int tas,struct oyuncu o){
	int kosullar[2];
	//kosullar dizisi yapilacak komutlari belirler
	if(renk==0){
		//Renk mavi ise, tasin 2 katinin gecerlilik durumu ve rengin tam tersinin 4 eksiginin gecerlilik durumu sorgulanir
		kosullar[0]=Gecerlimi(tas*2,o.mavi);
		kosullar[1]=Gecerlimi(tas-4,o.kirmizi);
	}
	else{
		//Yukaridaki islemin kirmizi tas icin olan kontrolleri
	    kosullar[0]=Gecerlimi(tas*2,o.kirmizi);
		kosullar[1]=Gecerlimi(tas-4,o.mavi);
	}
	//Eger iki kosuldan biri saglanirsa o 1 veya 2 degeri dondurulur
	if(kosullar[0]==1&&kosullar[1]==0)return 1;
	else if(kosullar[0]==0&&kosullar[1]==1)return 2;
	//Kosullardan hic biri saglanmazsa 0(oyun biter)
	else if(kosullar[0]==0&&kosullar[1]==0)return 0;
	else{
		//Iki kosul da saglanirsa rastgele biri secilir
		if(rand()%2==0){
			return 1;
		}
		else return 2;
	}
}
void OyuncuYazdir(struct oyuncu o){
	//Oyuncu bilgilerini yazdiran metot
	printf("Oyuncu %d\n",o.no);
	printf("Mavi: ");
	int i;
	for(i=0;i<20;i++){
		printf("%d ",o.mavi[i]);
	}
	printf("\nKirmizi: ");
	for(i=0;i<20;i++){
		printf("%d ",o.kirmizi[i]);
	}
	printf("\n\n");
}
int main(){
	//Degisken tanimlari ve ilk tas,renk ve siranin rastgele secilmesi
	srand(time(NULL));
	int tas = rand()%11;
	int renk = rand()%2;
	int sira = rand()%2;
	int hamle,hamlesayisi=0;
	//Oyuncu yapilari tanimlanir
	struct oyuncu oyuncu1={
		1,
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, //mavi
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} //kirmizi
	};
	struct oyuncu oyuncu2={
		2,
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},//mavi
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}//kirmizi
	};
	while(1){
		//Surekli bir dongu acilir ve oyuncu bilgileri her seferinde yazdirilir
		hamlesayisi++;
		OyuncuYazdir(oyuncu1);
		OyuncuYazdir(oyuncu2);
		//oyuncu 1'in sirasi
		if(sira==0){
			hamle=HamleSec(renk,tas,oyuncu1);
			if(hamle!=0){
				//Hamle 0 ise oyun biter, degilse;
				if(hamle==1){
					tas=tas*2;
				}
				else{
					//Secilen hamleye gore tas ve renk degistirilir
					tas-=4;
					renk=(renk+1)%2;
				}
				//Ardindan renge ve oyuncu sirasina gore tas alisverisi saglanir
				printf("Oyuncu 1 Hamle Yapiyor\nVerilen Tas:");
				if(renk==0)printf("Mavi %d\n",tas);
				else printf("Kirmizi %d\n",tas);
				if(renk==0){
					oyuncu1.mavi[tas]--;
					oyuncu2.mavi[tas]++;
				}
				else{
					oyuncu1.kirmizi[tas]--;
					oyuncu2.kirmizi[tas]++;
				}
			}
			else break;
		}
		//Oyuncu 2'nin sirasi
		else{
			//Ayni islemler oyuncu 2 icin gerceklestirilir
			hamle=HamleSec(renk,tas,oyuncu2);
			if(hamle!=0){
				if(hamle==1){
					tas=tas*2;
				}
				else{
					tas-=4;
					renk=(renk+1)%2;
				}
				printf("Oyuncu 2 Hamle Yapiyor\nVerilen Tas:");
				if(renk==0)printf("Mavi %d\n",tas);
				else printf("Kirmizi %d\n",tas);
				if(renk==0){
					oyuncu2.mavi[tas]--;
					oyuncu1.mavi[tas]++;
				}
				else{
					oyuncu2.kirmizi[tas]--;
					oyuncu1.kirmizi[tas]++;
				}
			}
			else break;
		}
		//Sira 0 ise 1, 1 ise 0 olur
		sira = (sira+1)%2;
		//Tas 0 oldu ise, carpim yapilabilmesi icin 1 yapilir ve oyunun bozulmamasi saglanir
		if(tas==0)tas++;
	}
	printf("Kazanana Oyuncu %d\nToplam Hamle Sayisi: %d\n",sira+1,hamlesayisi);
}
