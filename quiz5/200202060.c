// Tayyib OKUR
// 200202060
// quiz 5 2. donem

#include<stdio.h>
#include<locale.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

void mesaj_id(char *numara,char *mesaj)
{
    char *ilk;
    ilk = strtok(numara,"()");
    char *orta;
    orta = strtok(NULL,"-");
    char *son;
    son = strtok(NULL,"-");

    
    int sayi;



    if(strcmp(ilk,orta)>0)
    {
        sayi = atoi(ilk);
    }

    else if(strcmp(ilk,orta)<0)
    {
        sayi = atoi(orta);
    }


    int toplam = atoi(son) + sayi;

    mesaj[0] = tolower(mesaj[0]);

    int asci = mesaj[0];
    toplam = toplam + asci;

    char yeni_numara[100]= "";
    strcat(yeni_numara,ilk);
    strcat(yeni_numara,orta);
    strcat(yeni_numara,son);


    printf("%s numralai kisiye gonderilen id = %d",yeni_numara,toplam);




}

int main()
{
    setlocale(LC_ALL,"Turkish");
    char numara[25];
    char mesaj[100];
BASLA:
    printf("telefon numarası giriniz: ");
    gets(numara);

    int i;
    for(i=0; numara[i]!='\0'; i++)
    {
        if(isalpha(numara[i]))
        {
            goto BASLA;
        }

    }

    char *ptr1,*ptr2,*ptr3;

    ptr1 = strchr(numara,'(');
    ptr2 = strchr(numara,')');
    ptr3 = strchr(numara,'-');

    while(ptr1== NULL || ptr2 == NULL || ptr3 == NULL)
    {
        printf("telefon numarası giriniz: ");
        gets(numara);

    }

    printf("mesaji giriniz: ");
    gets(mesaj);

    while(islower(mesaj[0]))
    {
        printf("cumlenin ilk harfi buyuk olmalidir");
        gets(mesaj);
    }

    mesaj_id(numara,mesaj);


    return 0;
}