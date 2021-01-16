/*
Burak Boz
29.12.2020

Backtracking Yöntemi ile Matris Çözme

Kullanýcýdan bir renkler matrisi girmesi istenir. Kullanýcýnýn girdiði renkler matrisinde her sütunda ayný renk bir kez
bulunabilir. Ayný sütun üzerinde ayný renk birden fazla kez kullanýlýrsa bu satýrlardan biri bir adým saða shift edilir.
Bu þekilde tüm satýrlarda gerekli shift iþlemleri yapýldýktan sonra sonuç ekrana yazdýrýlýr.

Matrisin çözümü olmak zorunda deðildir. Matris çözülürken eðer belli satýrlarda týkanýlýrsa backtracking algoritmasý gereði
en son yol ayrýmýna geri dönülür ve diðer yol denenir.

Kullanýcýdan matrisi girerken renkler yerine, renklere karþýlýk gelen temsili sayý deðerleri girmesi istenmiþtir. Sonuç
bulunduðunda bu sayý deðerleri tekrar renklere dönüþtürülerek ekrana yazdýrýlacaktýr.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void matrisYazdir(int **,int);	//inputlar : (Matris baþlangýç pointeri , N deðeri) -> Matrisin mevcut halini ekrana yazdýrýr.
void matrisAraDegerYazdir(int **,int,int); //inputlar: (Matris baþlangýç pointeri , N deðeri , iþlem yapýlan satýr) -> Ara deðerleri yazdýrmak için kullanýlýr.
void shiftRight(int **,int, int);	//inputlar (Matris baþlangýç deðeri, N deðeri , Saða Kaydýrýlacak satýrýn indexi) -> Ýndeks deðeri gönderilen satýrý saða 1 satýr shift eder.
int recursiveA(int **,int,int); //(Matris baþlangýç pointeri, N deðeri, Ýþlem yapýlan satýr indeksi) -> Çýktý tercihlerinden 1. seçenek seçilirse bu fonksiyon çalýþýr.
int recursiveB(int **,int,int); //(Matris baþlangýç pointeri, N deðeri, Ýþlem yapýlan satýr indeksi) -> Çýktý tercihlerinden 2. seçenek seçilirse bu fonksiyon çalýþýr.
void matrisSonucYazdir(int **,int); //(Matris baþlangýç pointeri, N deðeri) -> Matrisi sayý olarak deðilde renk olarak yazdýrmak için kullanýlýr.

int main()
{
	printf("Burak Boz | 18011706 | Algoritma Analizi Odev 4 | 29.12.2020\n");
	printf("Konu: Backtracking\n\n");
	
	int n=0;	//Matrisin boyutu için kullanýlacaktýr.
	int i=0,j=0;	//Döngüler için kullanýlacaklardýr.
	int sonuc=0;	//Sonucun bulunup bulunamadýðý bu deðiþkende tutulacaktýr.
	int secim=0;	//Çýktýnýn nasýl istendiði bu deðiþkende saklanacaktýr
	do{
		printf("Matrisin boyutlandirilabilmesi icin N sayisini girin (3 <= N <= 8):");
		scanf("%d",&n);
	}while(!(n>=3 && n<=8));
	
	int **matris;	//Renkler matrisi için kullanýlacaktýr. 2 boyutlu integer tutacak þekilde tasarlanmýþtýr.
	matris=(int **)calloc(n,sizeof(int*));
	if(matris!=NULL)
	{
		for(i=0;i<n;i++)
		{
			matris[i]=(int *)calloc(n,sizeof(int));
			if(matris[i]==NULL){
				printf("Bellekte yeterince yer bulunmuyor.");//Bellekte yer ayrýlamadýysa bu hata ekrana yazdýrýlýr ve program kapatýlýr.
				return -1;
			}
		}	
	}
	
	
	printf("Lutfen renkleri (Rakam degerlerini) girin:\n");
	printf("1-sari\n2-lacivert\n3-kirmizi\n4-mor\n5-yesil\n6-pembe\n7-gri\n8-mavi\n");
	printf("!!! Lutfen renklerin rakam karsiliklarini giriniz.\n");
	for(i=0;i<n;i++)//Kullanýcýdan renkler matrisi alýnýyor. Renkler yerine temsil edilen sayýlar kullanýcýdan isteniyor.
	{
		for(j=0;j<n;j++)
		{
			printf("Renk Matrisi[%d][%d]:",i,j);
			scanf("%d",&matris[i][j]);
		}
	}
	
	printf("\nMatrisin ilk hali:\n");
	matrisYazdir(matris,n);
	printf("\n");
	matrisSonucYazdir(matris,n);
	
	printf("\n\nCikti secimi:\n");
	printf("1 - Ara degerleri gormek icin\n");
	printf("2 - Sadece sonucu gormek icin\n");
	printf("Menu harici secim yaparsaniz program kapatilacaktir.\nLutfen seciminizi belirtin:");
	scanf("%d",&secim);
	/*
		Raporda belirtilen çýktýlardan A maddesini görmek için 1 seçimini yapýnýz.
		1 seçimini yaptýðýnýzda matrisin üst satýrlara göre düzgün sýra ile yerleþtiði yere kadar bir iþaretçi ile ekrana yazdýrýlacaktýr.
		2 seçimini yaparsanýz sadece sonucu yazdýracaktýr.
	*/
	if(secim==1)
	{
		sonuc = recursiveA(matris,n,1);
		if(sonuc==1)
		{
			printf("Sonuc bulundu\n");
			printf("Matrisin son hali:\n");
			matrisYazdir(matris,n);
			printf("\n");
			matrisSonucYazdir(matris,n);
		}
		else
		{
			printf("Sonuc bulunamadi...");
		}
	}
	else if(secim==2)
	{
		sonuc = recursiveB(matris,n,1);
		if(sonuc==1)
		{
			printf("Sonuc bulundu\n");
			printf("Matrisin son hali:\n");
			matrisYazdir(matris,n);
			printf("\n");
			matrisSonucYazdir(matris,n);
		}
		else
		{
			printf("Sonuc bulunamadi...");
		}
	}
	else
	{
		printf("Yanlis secim. Program kapatiliyor.");
		for(i=0;i<n;i++)
		{
			free(matris[i]);
		}
		free(matris);
		return -2;
	}
	
		
	
	//Bellekte ayrýlan alanlarýn iþletim sistemine býrakýlmasý
	for(i=0;i<n;i++)
	{
		free(matris[i]);
	}
	free(matris);
	return 0;
}

//Matrisin o anki durumunu sayý olarak ekrana yazdýrmak için kullanýlýr.
void matrisYazdir(int **matris,int n)
{
	int i=0,j=0;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d ",matris[i][j]);
		}
		printf("\n");
	}
}

//Matrisin o anki durumundaki sayýlarý renklere çevirerek yazdýrýr.
void matrisSonucYazdir(int **matris,int n)
{
	int i=0,j=0;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			switch(matris[i][j])
			{
				case 1:
					printf("Sari ");
					break;
				case 2:
					printf("Lacivert ");
					break;
				case 3:
					printf("Kirmizi ");
					break;
				case 4:
					printf("Mor ");
					break;
				case 5:
					printf("Yesil ");
					break;
				case 6:
					printf("Pembe ");
					break;
				case 7:
					printf("Gri ");
					break;
				case 8:
					printf("Mavi ");
					break;
				default:
					
					printf("-1 ");
					
			}
		}
		printf("\n");
	}
}

/*Matris satýrlarý saða shift edilir ve eðer üst kýsýmla uyumlu hale gelirse kullanýcýdan alýnan seçime göre 
ekrana yazdýrýlabilir. Bu fonksiyon düzenlenmiþ halin hangi satýra kadar uyum içerisinde bulunduðunu, reqursiveA 
fonksiyonundan aldýðý satýrIndex deðerine göre bir iþaretçiyle iþaretler ve ekrana yazdýrýr.*/
void matrisAraDegerYazdir(int **matris,int n,int satirIndex)
{
	int i=0,j=0;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d ",matris[i][j]);
		}
		if(i==satirIndex)
		{
			printf(" <- ");
		}
		printf("\n");
	}
}

//index deðiþkenine gelen sayýya göre matrisin ilgili satýrýný bir saða shift eder. En saðdaki deðer satýrýn baþýna alýnýr.
void shiftRight(int **matris,int n, int index)
{
	int dizi[n];
	int i=0;
	for(i=1;i<n;i++)
	{
		dizi[i]=matris[index][i-1];
	}
	dizi[0]=matris[index][n-1];
	
	for(i=0;i<n;i++)
	{
		matris[index][i]=dizi[i];
	}
	
}

//Matrisi çözmeye çalýþan reqursive fonksiyondur. Eðer ara adýmlar kullanýcý tarafýndan görüntülenmek istenirse bu fonksiyon çalýþýr.
//Sonuç bulunduysa 1, bulunamadýysa 0 döndürür.
int recursiveA(int **matris,int n,int satir)
{
	int step=0;
	int result=0;
	while(step<n && result ==0)
	{
		bool cik=false;
		int j=0;
		while(j<n && cik==false)
		{
			int k=satir-1;
			while(k>0 && matris[k][j] != matris[satir][j])
			{
				k--;
			}
			if(matris[k][j] == matris[satir][j])
			{
				cik=true;
			}
			j++;
		}
		if(cik==true)
		{
			shiftRight(matris,n,satir);
		}
		else
		{
			printf("Cozulen satira kadar olan kisim isaretlenmistir:\n");
			matrisAraDegerYazdir(matris,n,satir);//Ara adýmýn ekrana yazdýrýlmasýný saðlayan fonksiyon
			printf("\n");
			if(satir==n-1)
			{
				result = 1;
			}
			else{
				result = recursiveA(matris,n,satir+1);
			}
		}
		step++;
	}
	if(step == n && result == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

//Matrisi çözmeye çalýþan recursive fonksiyondur. Kullanýcý ara adýmlarý görmeden sadece sonucu görmek isterse bu fonksiyon çalýþtýrýlýr.
//Sonuç bulunduysa 1, bulunamadýysa 0 döndürür.
int recursiveB(int **matris,int n,int satir)
{
	int step=0;
	int result=0;
	while(step<n && result ==0)
	{
		bool cik=false;
		int j=0;
		while(j<n && cik==false)
		{
			int k=satir-1;
			while(k>0 && matris[k][j] != matris[satir][j])
			{
				k--;
			}
			if(matris[k][j] == matris[satir][j])
			{
				cik=true;
			}
			j++;
		}
		if(cik==true)
		{
			shiftRight(matris,n,satir);
		}
		else
		{
			if(satir==n-1)
			{
				result = 1;
			}
			else{
				result = recursiveB(matris,n,satir+1);
			}
		}
		step++;
	}
	if(step == n && result == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

