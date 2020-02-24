#include <stdio.h>
#include <conio.h>
#include <string.h>

typedef char **tKata;
//typedef enum {false=0, true=1} bool;

struct KosaKata {
 char Kata[20];
 KosaKata *Next;
} *KataGanti, *KataKerja, *KataBenda, *tGanti, *tKerja, *tBenda,
  *Head, *Tail, *Baru, *Hapus, *Bantu;

void Pisahkan(char kalimat[], tKata kata, int &jlh)
{
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

 *kata=new (char *)[jlh];
 for(i=0; i<jlh; i++)
  kata[i]=new char[jlh];

 i=j=k=0;
 while (kalimat[i]) {
  huruf=kalimat[i];
  if ( (huruf>='A' && huruf<='Z') || (huruf>='a' && huruf<='z') || (huruf>='0' && huruf<='9') ) {
   kata[k][j]=kalimat[i];
   j++;
  } else {
   if (j>0) {
    kata[k][j]=0;
    j=0;
    k++;
   }
  }
  i++;
 }
 if (j>0) kata[k][j]=0;
}

KosaKata *BacaDaftarKata(char NamaFile[])
{
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
   } else Head=Tail=Baru;
  }
  fclose(f);
  return Head;
 } else return NULL;
}

void CetakDaftarKata(KosaKata *kt)
{
 Bantu=kt;
 while (Bantu) {
  printf("%s\n", Bantu->Kata);
  Bantu=Bantu->Next;
 }
}

void HapusDaftarKata(KosaKata *kt)
{
 while (kt) {
  Hapus=kt;
  kt=kt->Next;
  delete Hapus;
 }
}

bool Terdapat(char kata[], KosaKata *Daftar)
{
 bool ditemukan;

 ditemukan=false;
 Bantu=Daftar;
 while (Bantu && !ditemukan) {
  if ( strcmp(kata, Bantu->Kata)==0 ) ditemukan=true;
  Bantu=Bantu->Next;
 }
 return ditemukan;
}

void main()
{
 char Kalimat[100]="makan udang saya", **Kata, Pola[10];
 int JlhKata, i;

 clrscr();
 KataGanti=KataKerja=KataBenda=NULL;
 KataGanti=BacaDaftarKata("Ganti.txt"); tGanti=Tail;
 KataKerja=BacaDaftarKata("Kerja.txt"); tKerja=Tail;
 KataBenda=BacaDaftarKata("Benda.txt"); tBenda=Tail;
 /*CetakDaftarKata(KataGanti);
 CetakDaftarKata(KataKerja);
 CetakDaftarKata(KataBenda);*/
 //printf("%i\n", JlhKata);

 Pisahkan(Kalimat, Kata, JlhKata);
 for(i=0; i<JlhKata; i++) {
  //printf("%s\n", Kata[i]);
  if ( Terdapat(Kata[i], KataGanti) )
   Pola[i]='S';
  else if ( Terdapat(Kata[i], KataKerja) )
   Pola[i]='P';
  else if ( Terdapat(Kata[i], KataBenda) )
   Pola[i]='O';
 }
 Pola[i]=0;
 printf("Kalimat %s memiliki pola kalimat: %s\n", Kalimat, Pola);
 if ( strcmp(Pola, "SPO")==0 )   //Pola=="SPO"
  printf("Pola kalimat sudah benar\n");
 else
  printf("Pola kalimat salah\n");
 HapusDaftarKata(KataGanti);
 getch();
}