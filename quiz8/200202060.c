//200202060
//Tayyib Okur
//quiz 8

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct musteri
{
    char ad_soyad[50];
    double telefon;
    int borc;

};



void musteri_listele(struct musteri dizi[])
{

int i,j;

    for(i=0;i<10;i++)
    {
        for(j=0;j<9;j++)
        {
            if(strcmp(dizi[j].ad_soyad,dizi[j+1].ad_soyad)>0)
            {
                struct musteri temp;
                temp = dizi[j];
                dizi[j] = dizi[j+1];
                dizi[j+1] = temp;


            }

        }

    }


}

void bilgi_guncelle(struct musteri musteri1,struct musteri dizi[])
{

   int i;
    for(i=0;i<10;i++)
    {
        if(musteri1.telefon == dizi[i].telefon)
        {
            dizi[i].borc = musteri1.borc;
        }

    }

    musteri_listele(dizi);



}

int main()
{

    struct musteri dizi[15] = { {"MenekseElitok",5052341134,2000}, {"SeyfullahAydinlik",5063457626,3150},{"TekayGunbatti",5027653421,20280},{"simsekerKahveci",5014532365,15425},{"EnderIsikli",5504762387,875},{"ErkutKaracelebi",5356782145,1500},{"sahinTekpinar",5026542113,6550},{"DilaverDuman",5602564421,8000},{"GulnarYegit",5346569009,685},{"EslemOgunc",5057652311,1900} };

    struct musteri musteri1;
    printf("Borcu odenecek musterinin telefon numarasini giriniz: ");
    scanf("%lf",&musteri1.telefon);

   int i;

   int odenecek_borc_miktari;
   for(i=0;i<10;i++)
   {
       if(musteri1.telefon == dizi[i].telefon){
        printf("Musterinin adi soyadi: %s\n",dizi[i].ad_soyad);
        strcpy(musteri1.ad_soyad,dizi[i].ad_soyad);
        break;
       }
   }
printf("odencek borc miktarini giriniz: ");
scanf("%d",&odenecek_borc_miktari);

musteri1.borc = dizi[i].borc - odenecek_borc_miktari;

bilgi_guncelle(musteri1,dizi);

for(i=0;i<10;i++)
{
    printf("%s %.0lf %d\n",dizi[i].ad_soyad,dizi[i].telefon,dizi[i].borc);

}





    return 0;
}