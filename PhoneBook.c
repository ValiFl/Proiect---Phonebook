#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

int numar_contacte;

struct AGENDA{
	char nume[20];
	char numar[10];
};

//functie introducere contacte

/*Functie de creeare a fisierului initial
In aceasta functie vom introduce datele initiale ale
agendei de la tastatura in scopul prelucrarii acestora
*/

int creareFisier(char *fnume){
	FILE *f;
	int i;
    struct AGENDA persoana[numar_contacte];
	f=fopen("test.bin","wb");
	if(!f){
		printf("Fisierul nu s-a putut deschide!\n");
		return -1;
	}
	printf("Dati info despre persoana:\n");
	for(i=0;i<numar_contacte;i++)
		{	printf("Nume:\n");
			scanf("%s",&persoana[i].nume);
			printf("Numar:\n");
			scanf("%s",&persoana[i].numar);
	}fwrite(&persoana,sizeof(persoana),1,f);

	fclose(f);
	return 0;
}
/*Functie de citire a agendei
Dupa creearea agendei in urma functiei initiale,
folosim aceasta functie pentru citirea tuturor datelor
introduse anterior
*/
int citesteFisier(char *fnume)
{
	FILE *f;
	struct AGENDA persoana[numar_contacte];
	int i=0;
	f=fopen(fnume,"rb");
	if (!f) {
		printf("Unable to open file!");
		return -1;
	}

	printf("Datele urmatoare se afla in fisierul binar %s:\n", fnume);
    while(fread(&persoana,sizeof(struct AGENDA),1,f) != NULL)
    {
        if(strcmp(persoana[i].nume,"")==0){
            break;}
        else{
        printf("Nume:%s\n",persoana[i].nume);
        printf("Numar:%s\n",persoana[i].numar);}
    }

	fclose(f);
	return 0;
}

/*Functie de adaugare contact nou
Aceasta functie are ca scop adaugarea unui nou contact in agenda
Astfel putem introduce de la tastatura numele si numarul unui contact
nou
*/
int adaugaContact(char *fnume)
{
    FILE *f;
	int i=0;
	numar_contacte++;
	struct AGENDA persoana[numar_contacte];
	char numeNou[20], numarNou[10];
	f=fopen(fnume,"r+b");
	if(!f){
		printf("Fisierul nu s-a putut deschide!\n");
		return -1;
	}
	printf("Dati info despre persoana:\n");
	printf("Nume:\n");
	scanf("%s",&numeNou);
	printf("Numar:\n");
	scanf("%s",&numarNou);
	while(fread(&persoana,sizeof(struct AGENDA),1,f) != NULL)
    {
        if(strcmp(persoana[i].nume,"")==0)
            if(strcmp(persoana[i-1].nume,"")==0)
            {
            strcpy(persoana[i].nume,numeNou);
            strcpy(persoana[i].numar,numarNou);
            break;
            }
    i++;
    }

	fclose(f);
	return 0;
}

/*Functie de stergere
Aceasta functie are ca scop stergerea unui contact din agenda
Functia are ca criteriu un nume introdus de la tastatura,
urmand stergerea acestuia
*/

int deleteContact(char *fnume)
{
    FILE *f;
	FILE *f_nou;
	struct AGENDA persoana[numar_contacte];
	char numeCautat[20];
	int found=0,i=0,skip=0;
	f=fopen(fnume,"rb");
	if(!f){
		printf("Nu se poate deschide fisierul %s",fnume);
		return -1;
	}
	f_nou=fopen("tmp.bin","wb");
    if(!f_nou){
        printf("Nu se poate deschide fisierul temporar ");
        return -1;
    }
	printf("\n Alege numele contactului pe care vrei sa il stergi\n");
    scanf("%s",&numeCautat);

	while(fread(&persoana,sizeof(struct AGENDA),1,f) != NULL)
    {
        printf("Name:%s\n",persoana[i].nume);
        printf("Numar%s\n",persoana[i].numar);
        if(strcmp(numeCautat ,persoana[i].nume)==0)
        {
                found=1;
                printf("Studentul cu numele %s exista in agenda.\n",persoana[i].nume);
                skip=1;
                printf("Name:%s\n",persoana[i].nume);
                printf("Numar%s\n",persoana[i].numar);
                i++;
                i++;
        }
        else
        {
            fwrite(&persoana,sizeof(struct AGENDA),1,f_nou);
        }
    }


    if(found==0)
        printf("Numele cautat nu se afla in agenda.\n");
	fclose(f);
    fclose(f_nou);

    numar_contacte--;

    remove(fnume);
    rename("tmp.bin",fnume);
	return 0;
}
/*Functie de cautat un anumit contact in agenda
Scopul acestei functii este de a cauta un anumit contact
din agenda pe baza numelui,introdus de la tastatura.
Dupa gasirea contactului,functia afiseaza numele si numarul
contactului respectiv
*/
int cautaContact(char *fnume)
{
    int found = 0;
    int i = 0,k;
    char numeCautat[20];
	struct AGENDA persoana[numar_contacte];
    FILE *f;

    f=fopen(fnume,"rb");
    if(!f){
            printf("Nu se poate deschide fisierul %s",fnume);
            return -1;
			}

    printf("\n Alege numele contactului de cautat\n");
    scanf("%s",&numeCautat);

    while(fread(&persoana,sizeof(struct AGENDA),1,f) != NULL)
		{
		    if(strcmp(numeCautat ,persoana[i].nume)==0)
            {
					found=1;
					printf("Studentul cu numele %s exista in agenda.\n",persoana[i].nume);

					printf("Name:%s\n",persoana[i].nume);
					printf("Numar%s\n",persoana[i].numar);
					break;
			 }
        }
    if(found==0)
        printf("\nNumele cautat nu se afla in agenda\n");

	fclose(f);
    return 0;
    }
/*Functie modificare contact
Aceasta functie are ca scop gasirea unui contact
pe baza de nume,si modificarea informatiilor acestuia
(nume,numar)
*/
int modificaContact(char *fnume){
	FILE *f;
	FILE *f_nou;
	char numeCautat[20];
	int found=0,i=0;
	char numeNou[20],numarNou[10];
	struct AGENDA persoana[numar_contacte];
	f=fopen(fnume,"r+b");
	if(!f){
		printf("Nu se poate deschide fisierul %s",fnume);
		return -1;
	}
	f_nou=fopen("tmp.bin","wb");
    if(!f_nou){
        printf("Nu se poate deschide fisierul temporar ");
        return -1;
    }
	printf("\n Alege numele contactului pe care vrei sa il modifici\n");
    scanf("%s",&numeCautat);
	while(fread(&persoana,sizeof(struct AGENDA),1,f) != NULL)
	{
			if(strcmp(numeCautat,persoana[i].nume)==0)
			{
			found=1;
			printf("Introduceti noul nume:\n");
			scanf("%s",&numeNou);
			printf("si noul numar\n");
			scanf("%s",&numarNou);
			strcpy(persoana[i].nume,numeNou);
			strcpy(persoana[i].numar,numarNou);
			fwrite(&persoana,sizeof(struct AGENDA),1,f_nou);
			}
			else if(found==1)
				fwrite(&persoana,sizeof(struct AGENDA),1,f_nou);
	i++;
	}

		if(found==0)
			printf("Numele cautat nu se afla in agenda.\n");
	fclose(f);
    fclose(f_nou);

    remove(fnume);
    rename("tmp.bin",fnume);
	return 0;
}

int main() {
	int rezultat,optiune,n;
	printf("Introduceti numarul de contacte\n");
	scanf("%d",&n);
	numar_contacte=n;
	struct AGENDA persoana[numar_contacte];



	rezultat = creareFisier("test.bin");
	if(rezultat ==-1){
		printf("Nu s-a putut crea fisierul!");
	}
	printf("Alegeti optiunea dorita: \n");
    printf("Optiunea 1: Afisare contacte\n");
    printf("Optiunea 2: Adaugare contact nou \n");
    printf("Optiunea 3: Stergere contact\n");
    printf("Optiunea 4: Cautare contact\n");
    printf("Optiunea 5: Modifica un contact\n");
    scanf("%d",&optiune);
    printf("\nAti ales optiunea: %d \n",optiune);
    while(optiune){
    switch(optiune){

        case 1:	rezultat=citesteFisier("test.bin");
				if(rezultat ==-1)
				{	printf("Nu s-a putut deschide fisierul!");
					}
				break;

        case 2: rezultat=adaugaContact("test.bin");
				if(rezultat ==-1)
				{	printf("Nu s-a putut deschide fisierul!");
					}

				break;
        case 3: rezultat = deleteContact("test.bin");
				if(rezultat == -1)
				{	printf("Error deleting record!");
					}
			/*	rezultat=citesteFisier("test.bin",n);
				if(rezultat ==-1)
				{	printf("nope");
				}*/
				break;

        case 4: rezultat = cautaContact("test.bin");
				if(rezultat ==-1)
				{	printf("nope");
				}
				break;

		case 5: rezultat = modificaContact("test.bin");
				if(rezultat ==-1)
				{	printf("nope");
				}
				break;

        case 6:	rezultat=citesteFisier("tmp.bin");
				if(rezultat ==-1)
				{	printf("Nu s-a putut deschide fisierul!");
					}
				break;

        default:printf("Optiunea introdusa nu exista\n");
	}
	printf("Alegeti alta optiune.\nDaca doriti sa iesiti din program apasati tasta 0.\n");
	scanf("%d",&optiune);
	}

	printf("O zi buna! :)");

	getch();
	return 0;
	}
