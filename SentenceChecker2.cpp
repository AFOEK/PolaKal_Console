#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>

typedef char **tKata;
//typedef enum {false=0, true=1} bool;

struct KosaKata {
	char Kata[20];
	KosaKata *Next;
} *SubjectPronoun, *PossesiveAdjective, *Verb, *Noun, *Adjective, *Adverb, *Preposition,
 *tSP, *tPA, *tV, *tN, *tAdj, *tAdv, *tPrep, *Head, *Tail, *Baru, *Hapus, *Bantu;

tKata Pisahkan(char kalimat[], tKata kata, int &jlh) {
	int i, j, k;
	char huruf;

	i=0;
	jlh=1;
	while (kalimat[i]) {
		huruf=kalimat[i];
		if (! ( (huruf>='A' && huruf<='Z') || (huruf>='a' && huruf<='z') || (huruf>='0' && huruf<='9') ) )
			jlh++;
		i++;
	}

	kata=(char **)malloc(jlh*sizeof(char *));
	for(i=0; i<jlh; i++)
		kata[i]=new char[jlh];

	i=j=k=0;
	while (kalimat[i]) {
		huruf=kalimat[i];
		if ( (huruf>='A' && huruf<='Z') || (huruf>='a' && huruf<='z') || (huruf>='0' && huruf<='9') ) {
			if (huruf>='A' && huruf<='Z')
				huruf+=32;
			kata[k][j]=huruf;
			j++;
		}
		else {
			if (j>0) {
				kata[k][j]=0;
				j=0;
				k++;
			}
		}
		i++;
	}
	if (j>0) kata[k][j]=0;

	return kata;
}

KosaKata *BacaDaftarKata(char NamaFile[]) {
	FILE *f;
	static char kata[20];
	int p;

	Head=Tail=NULL;
	f=fopen(NamaFile, "rt");
	if (f) {
		while (!feof(f)) {
			fgets(kata, 20, f);
			p=strlen(kata)-1;
			if (kata[p]=='\n')
				kata[p]=0;

			strlwr(kata);
			Baru=new KosaKata;
			strcpy(Baru->Kata, kata);
			Baru->Next=NULL;
			if (Head) {
				Tail->Next=Baru;
				Tail=Baru;
			}
			else
				Head=Tail=Baru;
		}
		fclose(f);
		return Head;
	}
	else
		return NULL;
}

void CetakDaftarKata(KosaKata *kt) {
	Bantu=kt;
	while (Bantu) {
		printf("%s\n", Bantu->Kata);
		Bantu=Bantu->Next;
	}
}

void HapusDaftarKata(KosaKata *kt) {
	while (kt) {
		Hapus=kt;
		kt=kt->Next;
		delete Hapus;
	}
}

bool Terdapat(char kata[], KosaKata *Daftar) {
	bool ditemukan;

	ditemukan=false;
	Bantu=Daftar;
	while (Bantu && !ditemukan) {
		if ( strcmp(kata, Bantu->Kata)==0 ) ditemukan=true;
		Bantu=Bantu->Next;
	}
	return ditemukan;
}

main() {
	char Kalimat[100]="My pet eats unhealthy food", **Kata, Pola[20][5];
	int JlhKata, i, j;
	bool VerbFound;

	system("cls");
	//for (int i=0; i<100; i++)
	//printf("%c", Kalimat[i] );
	//printf("Masukkan kalimat: ");
	//scanf("%c", &Kalimat);
	//printf("%c", Kalimat);

	SubjectPronoun=PossesiveAdjective=Verb=Noun=Adjective=Adverb=NULL;
	
	SubjectPronoun		=BacaDaftarKata("SubjectPronouns.txt");			tSP=Tail;
	PossesiveAdjective	=BacaDaftarKata("PossesiveAdjectives.txt");		tPA=Tail;
	Verb				=BacaDaftarKata("Wordlist-Verbs-All.txt");		tV=Tail;
	Noun				=BacaDaftarKata("Wordlist-Nouns-All.txt");		tN=Tail;
	Adjective			=BacaDaftarKata("Wordlist-Adjectives-All.txt");	tAdj=Tail;
	Adverb				=BacaDaftarKata("Wordlist-Adverbs-All.txt");	tAdv=Tail;
	Preposition			=BacaDaftarKata("Prepositions.txt"); 			tPrep=Tail;
	/*CetakDaftarKata(SubjectPronoun);
	CetakDaftarKata(Verb);
	CetakDaftarKata(Noun);*/
	
	printf("Kalimat: '%s'\n", Kalimat);
 
	Kata=Pisahkan(Kalimat, Kata, JlhKata);
	printf("Jumlah Kata: %i\n\n", JlhKata);
	j=0;
	
	/*****************************************************
	VerbFound=false;
	for(i=0; i<JlhKata; i++) {
		//printf("%s\n", Kata[i]);
		if ( Terdapat(Kata[i], SubjectPronoun) ) {
			if (VerbFound) Pola[j]='O'; else Pola[j]='S';
		}
		else if ( Terdapat(Kata[i], Verb) ) {
			VerbFound=true;
			Pola[j]='P';
		}
		else if ( Terdapat(Kata[i], Noun) )
			if (VerbFound) Pola[j]='O'; else Pola[j]='S';
		else Pola[j]='X';
		j++; 
	}
	*******************************************************/
	
	/*First Parsing - Identifying Words*/	
	for(i=0; i<JlhKata; i++) {
		//printf("%s\n", Kata[i]);
		if ( Terdapat(Kata[i], SubjectPronoun) ) 
			strcpy(Pola[j], "SP");
		else if ( Terdapat(Kata[i], PossesiveAdjective) ) 
			strcpy(Pola[j], "PA");
		else if ( Terdapat(Kata[i], Verb) ) 
			strcpy(Pola[j], "V");
		else if ( Terdapat(Kata[i], Noun) )
			strcpy(Pola[j], "N");
		else if ( Terdapat(Kata[i], Adjective) ) 
			strcpy(Pola[j], "Adj");
		else if ( Terdapat(Kata[i], Adverb) )
			strcpy(Pola[j], "Adv");		
		else
			strcpy(Pola[j], "X");
		j++; 
	}
	
	/*Second Parsing - Identifying phrases
	for(i=0; i<j; i++){
		if( Pola[i]=='PA' && Pola[i+1]=='N' ){
			Pola2[i]='S';
			Pola2[i+1]=" ";
		}
		else
			Pola2[i]=Pola[i];
	}
	*/
	
	printf("Pola  Kalimat: ");
	//printf("%i\n", j);
	/*printf("Pola  Kalimat: %s\n", Pola);
	printf("Pola2 Kalimat: %s\n", Pola2);*/
	for(i=0; i<j; i++)
		printf("%s ", Pola[i]);
		
	/*
	if ( strcmp(Pola, "SPO")==0 )   //Pola=="SPO"
		printf("Pola kalimat sudah benar\n");
	else
		printf("Pola kalimat salah\n");
	*/

	HapusDaftarKata(SubjectPronoun);
	HapusDaftarKata(PossesiveAdjective);
	HapusDaftarKata(Noun);
	HapusDaftarKata(Verb);
	HapusDaftarKata(Adjective);
	HapusDaftarKata(Adverb);
	HapusDaftarKata(Preposition);
	//getch();
	return 0;
}
