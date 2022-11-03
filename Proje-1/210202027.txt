#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <locale.h>
#include <string.h>

int menu()
{
    int secim;
    while(1)
    {
        printf("\n1-Dosya içeriği göster\n");
        printf("2-Arama\n");
        printf("3-Güncelleme\n");
        printf("4-Dosyaya yaz\n");
        printf("0-Çıkış\n");
        printf("Lütfen [1-4] bir seçim yapın\n");
        scanf("%d",&secim);
        return secim;

    }
}
void ara(char aranan_kelime[],int tekrarsiz_etiket_say,char etiket_tekrarsiz[][100],int dosya_sayisi,char dosya_adlari[][300])
{
    int i;
    int j=0;
    char etiket_isimleri[tekrarsiz_etiket_say][100];
    for(i=0; i<tekrarsiz_etiket_say; i++)
    {
        int boy = strlen(etiket_tekrarsiz[i])-4;
        strncpy(etiket_isimleri[i],etiket_tekrarsiz[i]+2,boy);
        etiket_isimleri[i][boy] = '\0';
    }
    int	 bayrak = 0;
    char yetim_etiketler[50][50];
    int yetim_etiket_say=0;
    // YETİM ETİKET ELDE EDİLİYOR
    for(i=0; i<tekrarsiz_etiket_say; i++)
    {
        for(j=0; j<dosya_sayisi; j++)
        {
            char *ptr = strstr(dosya_adlari[j],etiket_isimleri[i]);
            if(ptr != NULL)
            {
                bayrak = 1;
                break;
            }
        }
        if(bayrak == 0)
        {
            strcpy(yetim_etiketler[yetim_etiket_say],etiket_isimleri[i]);
            yetim_etiket_say++;
            //	printf("%s\n",etiket_isimleri[i]);  // etiket isimleri parantezsiz, eğer parantezli isteerse etiket_tekrarsiz[i] yap.
        }
        bayrak = 0;
    }
    // İSTENEN ETİKET ELDE EDİLİYOR
    bayrak = 0;
    char istenen_etiketler[50][50];
    int istenen_etiket_say=0;
    for(i=0; i<dosya_sayisi; i++)
    {
        for(j=0; j<tekrarsiz_etiket_say; j++)
        {
            char *ptr = strstr(dosya_adlari[i],etiket_isimleri[j]);
            if(ptr!=NULL)
            {
                bayrak = 1;
                break;
            }
        }
        if(bayrak == 0)
        {
            char *ptr = strrchr(dosya_adlari[i],'/');
            char istenen_etiket_adi[50];
            if(ptr!=NULL)
            {
                int k;
                for(k=0; ptr[k+1]!='.'; k++)
                {

                    if(ptr[k+1] == '_')
                    {
                        istenen_etiket_adi[k] = ' ';
                    }
                    else
                    {
                        istenen_etiket_adi[k] = ptr[k+1];
                    }

                }
                istenen_etiket_adi[k] = '\0';
            }
            strcpy(istenen_etiketler[istenen_etiket_say],istenen_etiket_adi);
            istenen_etiket_say++;
        }
        bayrak = 0;
    }
    j=0;
    bayrak = 0;
    for(i=0; i<tekrarsiz_etiket_say || j<istenen_etiket_say; i++,j++)
    {
        if(strcmp(aranan_kelime,etiket_isimleri[i]) == 0)
        {
            bayrak = 1;
            break;
        }
    }
    if(bayrak)
    {
        printf("Aranan kelime etikettir\n");
    }
    else
    {
        printf("Aranan kelime etiket degildir\n");
    }
    for(i=0; i<dosya_sayisi; i++)
    {
        FILE *dosya = fopen(dosya_adlari[i],"r");
        if(dosya == NULL)
        {
            printf("Dosya açılamadı\n");
        }
        while(!feof(dosya))
        {
            char satir[300];
            fgets(satir,299,dosya);
            char *ptr = strstr(satir,aranan_kelime);
            if(ptr!=NULL)
            {
                printf("%s dosyasinda;\n",dosya_adlari[i]);
                printf("kelimenin geçtiği cümle --->>> %s",satir);
                printf("\n\n");
            }
            strcpy(satir,"\0\0");
        }

        fclose(dosya);
    }
    printf("\n*****İSTENEN ETİKETLER***\n\n");
    for(i=0; i<istenen_etiket_say; i++)
    {
        printf("%s\n",istenen_etiketler[i]);
    }
    printf("\n\n*****YETİM ETİKETLER*****");
    printf("\n\n");
    for(i=0; i<yetim_etiket_say; i++)
    {
        printf("%s\n",yetim_etiketler[i]);
    }
    printf("\n\n");
}
void dosya_icerigi_goster(char dosya_adlari[][300],int dosya_adi_say)
{
    printf("Dosya adları:\n");

    int i,bayrak = 0;
    char dosya_adi[dosya_adi_say][100];
    for(i=0; i<dosya_adi_say; i++)
    {

        char *ptr = strrchr(dosya_adlari[i],'/');
        ptr++;
        strcpy(dosya_adi[i],ptr);

        printf("%d-%s\n",i+1,dosya_adi[i]);
    }
    int secim;
    printf("\nLütfen içini gormek istediğiniz dosyayı seçiniz (1-%d):\n",i);
    scanf("%d",&secim);
    while(secim<1 || secim>i)
    {
        printf("Hatalı seçim!!!\n");
        printf("\nLütfen içini gormek istediğiniz dosyayı seçiniz (1-%d):\n",i);
        scanf("%d",&secim);

    }
    printf("Dosya yazılıyor...\n\n");
    FILE *dosya = fopen(dosya_adlari[secim-1],"r");

    if(dosya == NULL)
    {
        printf("Dosya açılamadı\n");
    }

    while(!feof(dosya))
    {
        char satir[300];

        fgets(satir,299,dosya);
        printf("%s",satir);
        strcpy(satir,"\0\0");
    }

    fclose(dosya);
    printf("\n\n");
}

void dosyaya_yaz(char etiketler[][100],int etiket_say,char etiket_tekrarsiz[][100],int tekrarsiz_etiket_say,char dosya_adlari[][300],int dosya_adi_say)
{

    FILE *dosya = fopen("/home/kali/Desktop/Üniversite/output.txt","r");
    int i,j,bayrak = 0;
    if(dosya == NULL)
    {
        dosya = fopen("/home/kali/Desktop/Üniversite/output.txt","w+");
        char etiket_isimleri[tekrarsiz_etiket_say][100];
        for(i=0; i<tekrarsiz_etiket_say; i++)
        {
            int boy = strlen(etiket_tekrarsiz[i])-4;
            strncpy(etiket_isimleri[i],etiket_tekrarsiz[i]+2,boy);
            etiket_isimleri[i][boy] = '\0';

        }
        char yetim_etiketler[50][50];
        int yetim_etiket_say=0;
        char etiket_dosya_isimleri[dosya_adi_say][100];
        for(i=0; i<dosya_adi_say; i++)
        {
            char *ptr=	strrchr(dosya_adlari[i],'/');
            ptr++;

            int boy = strlen(ptr)-4;
            strncpy(etiket_dosya_isimleri[i],ptr,boy);
            etiket_dosya_isimleri[i][boy] = '\0';

            for(j=0; etiket_dosya_isimleri[i][j]!='\0'; j++)
            {
                if(etiket_dosya_isimleri[i][j] == '_')
                {
                    etiket_dosya_isimleri[i][j] = ' ';
                }
            }
        }

        // YETİM ETİKET ELDE EDİLİYOR
        for(i=0; i<tekrarsiz_etiket_say; i++)
        {
            for(j=0; j<dosya_adi_say; j++)
            {

                if(strcmp(etiket_dosya_isimleri[j],etiket_isimleri[i]) == 0)
                {
                    bayrak = 1;
                    break;
                }
            }
            if(bayrak == 0)
            {
                strcpy(yetim_etiketler[yetim_etiket_say],etiket_isimleri[i]);
                yetim_etiket_say++;
                //	printf("%s\n",etiket_isimleri[i]);  // etiket isimleri parantezsiz, eğer parantezli isteerse etiket_tekrarsiz[i] yap.
            }
            bayrak = 0;
        }
        printf("\n\n\n");
        int sayac=0;
        bayrak = 0;
        int k= 0;
        fprintf(dosya,"Etiket listesi   -    Tekrar Sayisi\n\n");
        for(i=0; i<etiket_say; i++)
        {
            for(k=0; k<etiket_say; k++)
            {
                if(strcmp(etiket_tekrarsiz[i],etiketler[k]) == 0)
                {
                    sayac++;
                }
            }
            if(sayac!=0)
            {
                fprintf(dosya,"%-35s %d\n",etiket_isimleri[i],sayac);
            }
            sayac=0;
        }
        sayac = 0;
        bayrak=0;
        fprintf(dosya,"\n\nYetim Etiketler\n\n");
        for(i=0; i<yetim_etiket_say; i++)
        {
            for(j=0; j<yetim_etiket_say; j++)
            {
                if(strcmp(yetim_etiketler[i],yetim_etiketler[j]) == 0)
                {
                    bayrak = 1;
                    sayac++;
                }
            }
            if(bayrak ==1 )
            {
                fprintf(dosya,"%s\n",yetim_etiketler[i]); // last substitution
            }
            sayac = 0;
        }
        printf("yazma işlemi başarılı bir şekilde yapılmıştır...\n");
        fclose(dosya);
    }
    else
    {
        FILE *dosya = fopen("/home/kali/Desktop/Üniversite/output.txt","a");
	if (dosya == NULL)
		printf("Dosya açılamadı\n");
        fprintf(dosya,"\nGüncel Liste\n");
        char etiket_isimleri[tekrarsiz_etiket_say][100];
        for(i=0; i<tekrarsiz_etiket_say; i++)
        {
            int boy = strlen(etiket_tekrarsiz[i])-4;
            strncpy(etiket_isimleri[i],etiket_tekrarsiz[i]+2,boy);
            etiket_isimleri[i][boy] = '\0';

        }
        char yetim_etiketler[50][50];
        int yetim_etiket_say=0;
        char etiket_dosya_isimleri[dosya_adi_say][100];
        for(i=0; i<dosya_adi_say; i++)
        {
            char *ptr=	strrchr(dosya_adlari[i],'/');
            ptr++;

            int boy = strlen(ptr)-4;
            strncpy(etiket_dosya_isimleri[i],ptr,boy);
            etiket_dosya_isimleri[i][boy] = '\0';

            for(j=0; etiket_dosya_isimleri[i][j]!='\0'; j++)
            {
                if(etiket_dosya_isimleri[i][j] == '_')
                {
                    etiket_dosya_isimleri[i][j] = ' ';
                }
            }
        }

        // YETİM ETİKET ELDE EDİLİYOR
        for(i=0; i<tekrarsiz_etiket_say; i++)
        {
            for(j=0; j<dosya_adi_say; j++)
            {

                if(strcmp(etiket_dosya_isimleri[j],etiket_isimleri[i]) == 0)
                {
                    bayrak = 1;
                    break;
                }
            }
            if(bayrak == 0)
            {
                strcpy(yetim_etiketler[yetim_etiket_say],etiket_isimleri[i]);
                yetim_etiket_say++;
                //	printf("%s\n",etiket_isimleri[i]);  // etiket isimleri parantezsiz, eğer parantezli isteerse etiket_tekrarsiz[i] yap.
            }
            bayrak = 0;
        }
        printf("\n\n\n");
        int sayac=0;
        bayrak = 0;
        int k= 0;
        fprintf(dosya,"Etiket listesi   -    Tekrar Sayisi\n\n");
        for(i=0; i<etiket_say; i++)
        {
            for(k=0; k<etiket_say; k++)
            {
                if(strcmp(etiket_tekrarsiz[i],etiketler[k]) == 0)
                {
                    sayac++;
                }
            }
            if(sayac!=0)
            {
                fprintf(dosya,"%-35s %d\n",etiket_isimleri[i],sayac);
            }
            sayac=0;
        }
        sayac = 0;
        bayrak=0;
        fprintf(dosya,"\n\nYetim Etiketler\n\n");
        for(i=0; i<yetim_etiket_say; i++)
        {
            for(j=0; j<yetim_etiket_say; j++)
            {
                if(strcmp(yetim_etiketler[i],yetim_etiketler[j]) == 0)
                {
                    bayrak = 1;
                    sayac++;
                }
            }
            if(bayrak ==1 )
            {
                fprintf(dosya,"%s\n",yetim_etiketler[i]); // last substitution
            }
            sayac = 0;
        }
        printf("Yazma işlemi başarılı bir şekilde yapılmıştır...\n");
        fclose(dosya);
    }

}
int guncelle(char etiketler[][100],int etiket_say,int tekrarsiz_etiket_say,char etiket_tekrarsiz[][100],int dosya_adi_say,char dosya_adlari[][300],char klasor_adlari[][100],int *etiketler_sayisi)
{
    int i,j;
    int	 bayrak = 0;
    char etiket_isimleri[tekrarsiz_etiket_say][100];
    for(i=0; i<tekrarsiz_etiket_say; i++)
    {
        int boy = strlen(etiket_tekrarsiz[i])-4;
        strncpy(etiket_isimleri[i],etiket_tekrarsiz[i]+2,boy);
        etiket_isimleri[i][boy] = '\0';
    }
    char yetim_etiketler[50][50];
    int yetim_etiket_say=0;
    // YETİM ETİKET ELDE EDİLİYOR
    for(i=0; i<tekrarsiz_etiket_say; i++)
    {
        for(j=0; j<dosya_adi_say; j++)
        {
            char *ptr = strstr(dosya_adlari[j],etiket_isimleri[i]);

            if(ptr != NULL)
            {
                bayrak = 1;
                break;
            }
        }
        if(bayrak == 0)
        {
            strcpy(yetim_etiketler[yetim_etiket_say],etiket_isimleri[i]);
            yetim_etiket_say++;
            //	printf("%s\n",etiket_isimleri[i]);  // etiket isimleri parantezsiz, eğer parantezli isteerse etiket_tekrarsiz[i] yap.
        }
        bayrak = 0;
    }
    int secim=0;
    char degistirilecek_etiket_adi[100];
    char yeni_etiket_adi[100];
    while(secim!= 1 && secim!=2)
    {
        printf("1 - Etiket degiştir: \n");
        printf("2 - Yetim etiket dosyası oluştur: \n\n");
        printf("[1-2] Seçim: ");
        scanf("%d",&secim);
    }
    if(secim == 1)
    {
        printf("Değiştirilecek etiketi giriniz:");
   	getchar();
        gets(degistirilecek_etiket_adi);


        printf("Yeni etiket adını giriniz: ");
        gets(yeni_etiket_adi);
        int i;
        int j=0;
        j=0;
        bayrak = 0;
        for(i=0; i<tekrarsiz_etiket_say; i++)
        {
            if(strcmp(degistirilecek_etiket_adi,etiket_isimleri[i]) == 0)
            {
                bayrak = 1;
                break;
            }
        }
        if(bayrak)
        {
            printf("Girilen kelime etikettir değişiklik yapılıyor...\n");
        }
        else
        {
            printf("Girilen kelime etiket değildir. Menüye yönlendiriliyorsunuz\n");
            return dosya_adi_say;
        }
        char degistirilecek_etiket_formati[100] = "[[";
        strcat(degistirilecek_etiket_formati,degistirilecek_etiket_adi);
        strcat(degistirilecek_etiket_formati,"]]");

        char yeni_etiket_formati[100] = "[[";
        strcat(yeni_etiket_formati,yeni_etiket_adi);
        strcat(yeni_etiket_formati,"]]");
        i = 0;
        while(i<tekrarsiz_etiket_say)
        {
            if (!strcmp(etiket_tekrarsiz[i],degistirilecek_etiket_formati))
                strcpy(etiket_tekrarsiz[i],yeni_etiket_formati);
            i++;
        }
        for(i=0; i<dosya_adi_say; i++)
        {
            FILE *dosya = fopen(dosya_adlari[i],"r+");
            int flag = 0;
            if(dosya == NULL)
            {
                printf("dosya açılmadı\n");
                break;
            }
            FILE *ndosya = fopen("tmp.txt","w+");
            char satir[400];
            while(!feof(dosya))
            {
                if (flag == 0)
                {
                    fgets(satir,399,dosya);

                    char *ptr = strstr(satir,degistirilecek_etiket_formati);
                    if(ptr!=NULL)
                    {
                        if (flag == 0)
                        {
                            rewind(dosya);
                            flag = 1;
                        }
                    }
                }
                strcpy(satir,"\0\0");
                if (flag == 1)
                {
                    fgets(satir,399,dosya);

                    char *ptr = strstr(satir,degistirilecek_etiket_formati);
                    if (ptr == NULL)
                        fputs(satir,ndosya);
                    else
                    {
                        int a = 0;
                        int etiketuz = strlen(degistirilecek_etiket_formati);
                        int fark = ptr - satir;
                        while(fark != 0)
                        {
                            char c = satir[a];
                            fputc(c,ndosya);
                            a++;
                            fark -= 1;
                        }

                        a = a + etiketuz;
                        fputs(yeni_etiket_formati,ndosya);
                        while(satir[a] != '\0')
                        {
                            char c = satir[a];
                            fputc(c,ndosya);
                            a++;
                        }
                    }
                }
            }

            fclose(dosya);
            if (flag == 1)
            {
                rewind(ndosya);
                dosya = fopen(dosya_adlari[i],"w+");
                while(!feof(ndosya))
                {
                    strcpy(satir,"\0\0");
                    fgets(satir,399,ndosya);
                    fputs(satir,dosya);
                }
		fclose(dosya);
            }

            fclose(ndosya);
            flag = 0;
        }
        for(i=0; i<dosya_adi_say; i++)
        {
            int k =0;
            char degistirilecek_dosya_adi[100];

            strcpy(degistirilecek_dosya_adi,degistirilecek_etiket_adi);
            strcat(degistirilecek_dosya_adi,".txt");
            char *ptr = strstr(dosya_adlari[i],degistirilecek_dosya_adi);
            char yeni_dosya_adi[200];
            if(ptr!=NULL)
            {
                strcpy(yeni_dosya_adi,dosya_adlari[i]);
                char *p = strrchr(yeni_dosya_adi,'/');

                for(k=0; p != &yeni_dosya_adi[k]; k++)
                {
                }
                strcat(yeni_dosya_adi,"/");
                strcpy(yeni_dosya_adi+k+1,yeni_etiket_adi);
                strcat(yeni_dosya_adi,".txt");

                int m=0;
                for(m=0; yeni_dosya_adi[m]!='\0'; m++)
                {
                    if(yeni_dosya_adi[m] == ' ')
                    {
                        yeni_dosya_adi[m] = '_';
                    }
                }

                rename(dosya_adlari[i],yeni_dosya_adi);
                strcpy(dosya_adlari[i],yeni_dosya_adi);
            }
        }
        for(i=0; i<etiket_say; i++)
        {

            if(strcmp(etiketler[i],degistirilecek_etiket_formati) == 0)
            {
                strcpy(etiketler[i],yeni_etiket_formati);
            }
        }
    }

    FILE *ders_kodu_txt = fopen("ders_kodu_tut.txt","a+");
	if (ders_kodu_txt == NULL)
		printf("Dosya açılamadı\n");
    char ders_kod[20];
    static int ders_kodu=200;

    while(1)
    {
        fscanf(ders_kodu_txt,"%s",ders_kod);
        if(feof(ders_kodu_txt))
        {
            break;
        }
        ders_kodu = atoi(ders_kod);
    }

    if(secim == 2)
    {
        char yetim_etiket_adi[100];
        int bayrak = 0;
        printf("Yetim etiketler\n");

        for(i=0; i<yetim_etiket_say; i++)
        {
            printf("%s\n",yetim_etiketler[i]);

        }
        printf("Dosyası oluşturulacak yetim etiketin ismini giriniz: ");
        getchar();
        gets(yetim_etiket_adi);
        for(i=0; i<yetim_etiket_say; i++)
        {
            if(strcmp(yetim_etiket_adi,yetim_etiketler[i]) == 0)
            {
                bayrak = 1;
            }
        }
        char yetimderskodu[100];
        if(bayrak == 1)
        {


            char olusturulan_dosya_adi[100] = "/home/kali/Desktop/Üniversite/Dersler/";
            strcat(olusturulan_dosya_adi,yetim_etiket_adi);
            strcat(olusturulan_dosya_adi,".txt");
            FILE *dosya = fopen(olusturulan_dosya_adi,"w");
            fputs("Dersin Kodu : ",dosya);
            fprintf(dosya, "BLM%d\n\n",ders_kodu);
            ders_kodu++;
            fputs("Dersin Adı : ",dosya);
            fprintf(dosya,"[[%s]]\n\nDersin içeriği : ",yetim_etiket_adi);
            strcpy(dosya_adlari[dosya_adi_say],olusturulan_dosya_adi);
            dosya_adi_say++;
            fprintf(ders_kodu_txt,"%d ",ders_kodu);
            fclose(ders_kodu_txt);
            fclose(dosya);

            char yeni_yetim_etiket_adi[50] = "[[";
            strcat(yeni_yetim_etiket_adi,yetim_etiket_adi);
            strcat(yeni_yetim_etiket_adi,"]]");
            strcpy(etiketler[etiket_say], yeni_yetim_etiket_adi);
            (*etiketler_sayisi)++;

        }

        else
        {
            printf("\n%s isminde yetim etiket yoktur\n",yetim_etiket_adi);
        }
    }
    return dosya_adi_say;
}
int main()
{
    setlocale(LC_ALL, "Turkish");
    int i=0;
    DIR *dizin_adi;
    struct dirent * dizin_oku;
    int sayac=0;
    dizin_adi = opendir("/home/kali/Desktop/Üniversite");
    if(dizin_adi==NULL)
    {
        printf("Dosya açılamadı");
    }
    if(dizin_adi != NULL)
    {
        while((dizin_oku = readdir(dizin_adi)) != NULL)
        {
            char *ptr = strchr(dizin_oku->d_name,'.');
            if(ptr == NULL )
            {
                sayac++;
            }
        }
        closedir(dizin_adi);
    }
    char klasor_adlari[sayac][100];
    sayac =0;
    dizin_adi = opendir("/home/kali/Desktop/Üniversite");
    if(dizin_adi==NULL)
    {
        printf("Dosya açılamadı!");
    }
    if(dizin_adi != NULL)
    {
        while((dizin_oku = readdir(dizin_adi)) != NULL)
        {
            char *ptr = strchr(dizin_oku->d_name,'.');
            if(ptr == NULL )
            {
                strcpy(klasor_adlari[sayac],"/home/kali/Desktop/Üniversite/");
                strcat(klasor_adlari[sayac],dizin_oku->d_name);
                strcat(klasor_adlari[sayac],"/");
                sayac++;
            }
        }
        closedir(dizin_adi);
    }
    char etiketler[100][100];
    int etiket_say=0;
    int j=0,k=0,space_counter=0;
    int dosya_adi_say = 0;
    char dosya_adlari[100][300];
    for(i=0; i<sayac; i++)
    {
        dizin_adi = opendir(klasor_adlari[i]);
        if(dizin_adi==NULL)
        {
            printf("Dosya açılamadı");
        }
        if(dizin_adi != NULL)
        {
            while((dizin_oku = readdir(dizin_adi)) != NULL)
            {
                char *ptr =  strstr(dizin_oku->d_name,".txt");
                if(ptr != NULL)
                {
                    char dosya_adi[100];
                    strcpy(dosya_adi,klasor_adlari[i]);
                    strcat(dosya_adi,dizin_oku->d_name);
                    strcpy(dosya_adlari[dosya_adi_say],dosya_adi);
                    dosya_adi_say++;
                    FILE *dosya = fopen(dosya_adi,"r");
                    char satir[300];
                    while(!feof(dosya))
                    {
                        fgets(satir,299,dosya);
                        char *p1 = strchr(satir,'[');
                        char *p2 = strchr(satir,']');
                        while(p1!=NULL && p2!=NULL)
                        {
                            char etiket[50];
                            memcpy(etiket,p1,p2-p1+2);

                            etiket[p2-p1+2] = '\0';

                            while (etiket[k])
                            {
                                if (etiket[k] == ' ')
                                    space_counter++;
                                k++;
                            }
                            if(etiket[p2-p1] == ']' && etiket[p2-p1+1] == ']' && (space_counter < 2))
                            {
                                strcpy(etiketler[j],etiket);
                                etiket_say++;
                                j++;
                            }
                            p1 = p1+2;
                            p2 = p2+2;
                            p1 = strchr(p1,'[');
                            p2 = strchr(p2,']');
                            strcpy(satir,"\0\0");
                            k = 0;
                            space_counter = 0;
                        }
                    }
                    fclose(dosya);
                    rewind(dosya);
                }
            }
        }
        closedir(dizin_adi);
    }
    char etiket_tekrarsiz[50][100];
    int tekrarsiz_etiket_say = 0;
    int bayrak=0;
    for(i=0; i<etiket_say; i++)
    {
        for(j=0; j<etiket_say; j++)
        {
            if(strcmp(etiket_tekrarsiz[j],etiketler[i]) == 0)
            {
                bayrak = 1;
                break;
            }
        }
        if(bayrak== 0)
        {
            strcpy(etiket_tekrarsiz[tekrarsiz_etiket_say],etiketler[i]);
            tekrarsiz_etiket_say++;
        }
        bayrak = 0;
    }
    int secim;
    char bolum_adi[50];
    char aranan_kelime[100];
    char degistirlecek_etiket_adi[100];
    char yeni_etiket_adi[100];
    printf("Tüm Etiketler\n");
    for(i=0; i<tekrarsiz_etiket_say; i++)
    {
        printf("%d. Etiket %s\n",i+1,etiket_tekrarsiz[i]);
    }

    while( (secim = menu()) )
    {
        switch(secim)
        {
        case 1:
            dosya_icerigi_goster(dosya_adlari,dosya_adi_say);
            printf("Tüm Etiketler\n");
            for(i=0; i<tekrarsiz_etiket_say; i++)
            {
                printf("%d. Etiket %s\n",i+1,etiket_tekrarsiz[i]);
            }
            break;
        case 2:
            printf("Aranan kelimeyi girin: ");
            getchar();
            gets(aranan_kelime);

            ara(aranan_kelime,tekrarsiz_etiket_say,etiket_tekrarsiz,dosya_adi_say,dosya_adlari);
            printf("Tüm Etiketler\n");
            for(i=0; i<tekrarsiz_etiket_say; i++)
            {
                printf("%d. Etiket %s\n",i+1,etiket_tekrarsiz[i]);
            }
            break;
        case 3:
            dosya_adi_say =	guncelle(etiketler,etiket_say,tekrarsiz_etiket_say,etiket_tekrarsiz,dosya_adi_say,dosya_adlari,klasor_adlari,&etiket_say);
            printf("Tüm Etiketler\n");
            for(i=0; i<tekrarsiz_etiket_say; i++)
            {
                printf("%d. Etiket %s\n",i+1,etiket_tekrarsiz[i]);
            }
            break;
        case 4:
            dosyaya_yaz(etiketler,etiket_say,etiket_tekrarsiz,tekrarsiz_etiket_say,dosya_adlari,dosya_adi_say);
            break;

        default:
            printf("HATALI SEÇİM!!! \n");

        }
    }
    return 0;
}