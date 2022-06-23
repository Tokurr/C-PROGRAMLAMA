// 200202060
// Tayyib Okur, 2. Öğretim
// 2. dönem, quiz 1

#include <stdio.h>
#include <stdlib.h>

void degeryaz(int cift_dizi[],int n1,int tek_dizi[],int n2);

int main()
{
    int boyut;
    printf("Dizi boyutunu giriniz: ");
    scanf("%d",&boyut);

    while(boyut<2)
    {
        printf("Dizinin boyutu ikiden kucuk olamaz\n");
        printf("Dizi boyutunu giriniz:");
       scanf("%d",&boyut);
    }

    int dizi[boyut];
    int i;
    int tek_say=0;
    int cift_say=0;
    printf("\nDizinin elemanlarini giriniz:\n\n");
    for(i=0;i<boyut;i++)
    {
        printf("Dizi %d. eleman : ",i+1);
        scanf("%d",&dizi[i]);
printf("\n");
        if(dizi[i]%2==0)
        {
            cift_say++;
        }

        else if(dizi[i]%2==1 || dizi[i]%2==-1)
        {

            tek_say++;
        }
    }

    int tek_dizi[tek_say];
    int cift_dizi[cift_say];
    int j=0,k=0;
    for(i=0;i<boyut;i++)
    {
        if(dizi[i]%2==0)
        {
            cift_dizi[j] = dizi[i];
            j++;
        }

        else if(dizi[i]%2==1 || dizi[i]%2==-1)
        {
            tek_dizi[k] = dizi[i];
            k++;
        }
    }

    degeryaz(cift_dizi,cift_say,tek_dizi,tek_say);


    return 0;
}


void degeryaz(int cift_dizi[],int n1,int tek_dizi[],int n2)
{
    int i;
    printf("Cift sayilar :\n");
    for(i=0;i<n1;i++)
    {
        printf("%d ",cift_dizi[i]);
    }
printf("\n\n");
    printf("Tek sayilar :\n");
    for(i=0;i<n2;i++)
    {
        printf("%d ",tek_dizi[i]);
    }

}