// Tayyib OKUR
// 200202060
// quiz 7 2. donem

// Tayyib OKUR
// 200202060
// quiz 7 2. donem

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
struct kapasite
{
    char cins[3];
    float miktar;


};

struct birimler
{
    char birim[3];


};

struct kapasite yukari_donustur(struct birimler b[], struct kapasite k)
{

int i;
for(i=0;i<5;i++)
{
    if(strcmp(k.cins,b[i].birim) == 0 && strcmp(k.cins,"tb")!=0)
    {
        k.miktar = k.miktar / 1024;
        strcpy(k.cins,b[i+1].birim);
        return k;
    }


}

return k;

};

int main()
{

   struct birimler b[6];
   strcpy(b[0].birim,"b");
   strcpy(b[1].birim,"bt");
   strcpy(b[2].birim,"kb");
   strcpy(b[3].birim,"mb");
   strcpy(b[4].birim,"gb");
   strcpy(b[5].birim,"tb");

char string[100];
 printf("kapasite miktarini ve cinsini giriniz: ");
 gets(string);
 struct kapasite k1;
struct kapasite yedek;

 sscanf(string,"%f %s",&k1.miktar,k1.cins);
 struct kapasite sonuc = yukari_donustur(b,k1);


if(strcmp(k1.cins,sonuc.cins)!=0)
printf("bir uste donusmus hali %.2f %s",sonuc.miktar,sonuc.cins);


else
printf("herhangi bir degisiklik yapilmamistir %.2f %s",sonuc.miktar,sonuc.cins);


    return 0;
}