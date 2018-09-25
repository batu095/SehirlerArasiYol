#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>
#include<process.h>
#include<conio.h>
#include<locale.h>

#define N 22
#define IN 5000

struct  sehir
{
    char sehir_adi[15];
    int sehir_kod;

};


char path[100];




int dijsktra(int distances[N][N],int source,int target)
{
    int dist[N],prev[N],selected[N]={0},i,m,min,start,d,j;

    for(i=0;i< N;i++)
    {
        dist[i] = IN;
        prev[i] = -1;
    }
    start = source;
    selected[start]=1;
    dist[start] = 0;
    while(selected[target] ==0)
    {
        min = IN;
        m = 0;
      for(i=0;i< N;i++)
        {
            d = dist[start] +distances[start][i];
            if(d< dist[i]&&selected[i]==0)
            {
                dist[i] = d;
                prev[i] = start;
            }
            if(min>dist[i] && selected[i]==0)
            {
                min = dist[i];
                m = i;
            }
        }
        start = m;
        selected[start] = 1;
    }
    start = target;
    j = 0;
    while(start != -1)
    {
        path[j++] = start+65;
        start = prev[start];
    }
    path[j]='\0';
    strrev(path);
    //printf("%s", path);
    return dist[target];
}




main(){

    setlocale(LC_ALL, "Turkish");
    int sehir_sayisi=1,i,tut,tut2,bayrak=1,sayi=0,sayi_tut,z;
    char tmp,tmp2;
    char gecici_sehir[12];

    FILE *dosya;
    dosya = fopen("sehirkod.txt","r");

    while(feof(dosya)==NULL){
        tmp=getc(dosya);
        if(tmp=='\n')
            sehir_sayisi++;
    }

    struct sehir sehirler[sehir_sayisi];

    int mesafeler[sehir_sayisi][sehir_sayisi];

    fclose(dosya);


    for(i=0;i<sehir_sayisi;i++){
        for(z=0;z<sehir_sayisi;z++){
            mesafeler[i][z]=20000;
        }
    }


    dosya = fopen("sehirkod.txt","r");

    for(i=0;i<sehir_sayisi;i++){
        int k=0;
        tmp=getc(dosya);
        while(tmp!='-'){
        sehirler[i].sehir_adi[k] = tmp;
        tmp=getc(dosya);
        k++;
        }
        sehirler[i].sehir_adi[k] = '\0';
        tmp=getc(dosya);
        sehirler[i].sehir_kod=tmp-48;
        tmp=getc(dosya);
        tut=tmp-48;
        if(tut<10 && tut >-1){
            sehirler[i].sehir_kod = 10*sehirler[i].sehir_kod + tut;
            tmp=getc(dosya);
        }
    }

    fclose(dosya);


    dosya=fopen("sehirmesafe.txt","r");

    while(!feof(dosya)){
        int k=0;
        tmp=getc(dosya);
        while(tmp!='-' && !feof(dosya)){
            gecici_sehir[k] = tmp;
            tmp=getc(dosya);
            k++;
        }
        gecici_sehir[k]='\0';
        for(i=0;i<sehir_sayisi;i++){
            if(!strcmp(gecici_sehir,sehirler[i].sehir_adi)){
                tut=sehirler[i].sehir_kod-1;
                break;
            }
        }
        k=0;
        tmp=getc(dosya);
        while(tmp!='-' && !feof(dosya)){
            gecici_sehir[k] = tmp;
            tmp=getc(dosya);
            k++;
        }
        gecici_sehir[k]='\0';
        for(i=0;i<sehir_sayisi;i++){
            if(!strcmp(gecici_sehir,sehirler[i].sehir_adi)){
                tut2=sehirler[i].sehir_kod-1;
                break;
            }
        }

        tmp=getc(dosya);
        sayi=0;
        while(tmp!='\n' && !feof(dosya)){
            sayi_tut=tmp-48;
            sayi=sayi*10+sayi_tut;
            tmp=getc(dosya);

        }



        mesafeler[tut][tut2] = sayi;
        mesafeler[tut2][tut] = sayi;
      //  printf("%d %d %d  ",tut,tut2,mesafeler[tut][tut2] = sayi);

    }
    int k;
    char basla[12],bitis[12];
    int gonder1,gonder2;
    printf("baslangic sehri: ");
    scanf("%s",&basla);
    printf("bitis sehri: ");
    scanf("%s",&bitis);

    for(i=0;i<sehir_sayisi;i++){
        if(!strcmp(basla,sehirler[i].sehir_adi)){
            gonder1=sehirler[i].sehir_kod;
            break;
        }
    }
    for(i=0;i<sehir_sayisi;i++){
        if(!strcmp(bitis,sehirler[i].sehir_adi)){
            gonder2=sehirler[i].sehir_kod;
            break;
        }
    }

    z=dijsktra(mesafeler,gonder1-1,gonder2-1);
    printf("Mesafe: %d Gecilen Sehirler: ",z);
    i=strlen(path);
    for(k=0;k<i;k++){
        printf("%s ", sehirler[path[k]-65].sehir_adi);
    }


}


