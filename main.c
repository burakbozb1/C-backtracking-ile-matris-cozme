/*
Burak Boz
29.12.2020

Backtracking Y�ntemi ile Matris ��zme

Kullan�c�dan bir renkler matrisi girmesi istenir. Kullan�c�n�n girdi�i renkler matrisinde her s�tunda ayn� renk bir kez
bulunabilir. Ayn� s�tun �zerinde ayn� renk birden fazla kez kullan�l�rsa bu sat�rlardan biri bir ad�m sa�a shift edilir.
Bu �ekilde t�m sat�rlarda gerekli shift i�lemleri yap�ld�ktan sonra sonu� ekrana yazd�r�l�r.

Matrisin ��z�m� olmak zorunda de�ildir. Matris ��z�l�rken e�er belli sat�rlarda t�kan�l�rsa backtracking algoritmas� gere�i
en son yol ayr�m�na geri d�n�l�r ve di�er yol denenir.

Kullan�c�dan matrisi girerken renkler yerine, renklere kar��l�k gelen temsili say� de�erleri girmesi istenmi�tir. Sonu�
bulundu�unda bu say� de�erleri tekrar renklere d�n��t�r�lerek ekrana yazd�r�lacakt�r.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void matrisYazdir(int **,int);	//inputlar : (Matris ba�lang�� pointeri , N de�eri) -> Matrisin mevcut halini ekrana yazd�r�r.
void matrisAraDegerYazdir(int **,int,int); //inputlar: (Matris ba�lang�� pointeri , N de�eri , i�lem yap�lan sat�r) -> Ara de�erleri yazd�rmak i�in kullan�l�r.
void shiftRight(int **,int, int);	//inputlar (Matris ba�lang�� de�eri, N de�eri , Sa�a Kayd�r�lacak sat�r�n indexi) -> �ndeks de�eri g�nderilen sat�r� sa�a 1 sat�r shift eder.
int recursiveA(int **,int,int); //(Matris ba�lang�� pointeri, N de�eri, ��lem yap�lan sat�r indeksi) -> ��kt� tercihlerinden 1. se�enek se�ilirse bu fonksiyon �al���r.
int recursiveB(int **,int,int); //(Matris ba�lang�� pointeri, N de�eri, ��lem yap�lan sat�r indeksi) -> ��kt� tercihlerinden 2. se�enek se�ilirse bu fonksiyon �al���r.
void matrisSonucYazdir(int **,int); //(Matris ba�lang�� pointeri, N de�eri) -> Matrisi say� olarak de�ilde renk olarak yazd�rmak i�in kullan�l�r.

int main()
{
	printf("Burak Boz | 18011706 | Algoritma Analizi Odev 4 | 29.12.2020\n");
	printf("Konu: Backtracking\n\n");
	
	int n=0;	//Matrisin boyutu i�in kullan�lacakt�r.
	int i=0,j=0;	//D�ng�ler i�in kullan�lacaklard�r.
	int sonuc=0;	//Sonucun bulunup bulunamad��� bu de�i�kende tutulacakt�r.
	int secim=0;	//��kt�n�n nas�l istendi�i bu de�i�kende saklanacakt�r
	do{
		printf("Matrisin boyutlandirilabilmesi icin N sayisini girin (3 <= N <= 8):");
		scanf("%d",&n);
	}while(!(n>=3 && n<=8));
	
	int **matris;	//Renkler matrisi i�in kullan�lacakt�r. 2 boyutlu integer tutacak �ekilde tasarlanm��t�r.
	matris=(int **)calloc(n,sizeof(int*));
	if(matris!=NULL)
	{
		for(i=0;i<n;i++)
		{
			matris[i]=(int *)calloc(n,sizeof(int));
			if(matris[i]==NULL){
				printf("Bellekte yeterince yer bulunmuyor.");//Bellekte yer ayr�lamad�ysa bu hata ekrana yazd�r�l�r ve program kapat�l�r.
				return -1;
			}
		}	
	}
	
	
	printf("Lutfen renkleri (Rakam degerlerini) girin:\n");
	printf("1-sari\n2-lacivert\n3-kirmizi\n4-mor\n5-yesil\n6-pembe\n7-gri\n8-mavi\n");
	printf("!!! Lutfen renklerin rakam karsiliklarini giriniz.\n");
	for(i=0;i<n;i++)//Kullan�c�dan renkler matrisi al�n�yor. Renkler yerine temsil edilen say�lar kullan�c�dan isteniyor.
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
		Raporda belirtilen ��kt�lardan A maddesini g�rmek i�in 1 se�imini yap�n�z.
		1 se�imini yapt���n�zda matrisin �st sat�rlara g�re d�zg�n s�ra ile yerle�ti�i yere kadar bir i�aret�i ile ekrana yazd�r�lacakt�r.
		2 se�imini yaparsan�z sadece sonucu yazd�racakt�r.
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
	
		
	
	//Bellekte ayr�lan alanlar�n i�letim sistemine b�rak�lmas�
	for(i=0;i<n;i++)
	{
		free(matris[i]);
	}
	free(matris);
	return 0;
}

//Matrisin o anki durumunu say� olarak ekrana yazd�rmak i�in kullan�l�r.
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

//Matrisin o anki durumundaki say�lar� renklere �evirerek yazd�r�r.
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

/*Matris sat�rlar� sa�a shift edilir ve e�er �st k�s�mla uyumlu hale gelirse kullan�c�dan al�nan se�ime g�re 
ekrana yazd�r�labilir. Bu fonksiyon d�zenlenmi� halin hangi sat�ra kadar uyum i�erisinde bulundu�unu, reqursiveA 
fonksiyonundan ald��� sat�rIndex de�erine g�re bir i�aret�iyle i�aretler ve ekrana yazd�r�r.*/
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

//index de�i�kenine gelen say�ya g�re matrisin ilgili sat�r�n� bir sa�a shift eder. En sa�daki de�er sat�r�n ba��na al�n�r.
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

//Matrisi ��zmeye �al��an reqursive fonksiyondur. E�er ara ad�mlar kullan�c� taraf�ndan g�r�nt�lenmek istenirse bu fonksiyon �al���r.
//Sonu� bulunduysa 1, bulunamad�ysa 0 d�nd�r�r.
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
			matrisAraDegerYazdir(matris,n,satir);//Ara ad�m�n ekrana yazd�r�lmas�n� sa�layan fonksiyon
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

//Matrisi ��zmeye �al��an recursive fonksiyondur. Kullan�c� ara ad�mlar� g�rmeden sadece sonucu g�rmek isterse bu fonksiyon �al��t�r�l�r.
//Sonu� bulunduysa 1, bulunamad�ysa 0 d�nd�r�r.
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

