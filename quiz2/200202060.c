// Tayyib okur
// 200202060
// quiz2

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
void ortalama_bul(int matris_boyu,int a[][matris_boyu])
{
    float ortalama=0.0;

    int k=0;
    float b[matris_boyu];


    for(int satir=0; satir<matris_boyu; satir++)

    {
        for(int sutun = 0; sutun<matris_boyu; sutun++)
        {
            ortalama+=a[satir][sutun];

        }
        ortalama /=matris_boyu;

        b[k++]=ortalama;

        ortalama = 0.000;
    }
    ortalama = 0.000;
    for(int satir = 0; satir<matris_boyu; satir++)
    {
        ortalama += b[satir];

    }
    ortalama /= matris_boyu;
    float ortmatris=ortalama;
    ortalama = 0;
    printf("Matrisin ortalamasi = %f ",ortmatris);
    printf("\n");
    for(int satir = 0; satir<matris_boyu; satir++)

        printf("%d. satirin ortalamasi %f\n",satir,b[satir]);

    En_yakin(matris_boyu,b);
}

void    En_yakin(int matris_boyu,float dizi[matris_boyu])
{
    float en_kucuk,ortalama=0.0;
    for(int satir = 0; satir<matris_boyu; satir++)
    {
        ortalama += dizi[satir];


    }
    ortalama /= matris_boyu;
    float ortmatris=ortalama;
    int satir=0,sutun=0;
    en_kucuk = fabs(ortmatris - dizi[satir]);
    for(satir = 1; satir<matris_boyu; satir++)
    {
        if(en_kucuk > fabs(ortmatris - dizi[satir]))
        {
            en_kucuk=fabs(ortmatris - dizi[satir]);
            sutun=satir;
        }
    }
    printf("Matris ortalamasina(%f) en yakin sayi : %f\n%d. satir ",ortmatris,dizi[sutun],sutun);


}

int main()
{
    srand(time(NULL));
    int boyut;

    printf("Matrisin boyunu giriniz :");

    scanf("%d",&boyut);

    int matris[boyut][boyut];

    for(int i = 0; i < boyut; i++)

    {
        for(int j = 0; j < boyut; j++)
        {
            matris[i][j] = rand() % 100;
            printf("%d ",matris[i][j]);

        }
        printf("\n");
    }
    printf("\n");
    ortalama_bul(boyut,matris);
    return 0;
}
