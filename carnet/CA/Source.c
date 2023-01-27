#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define SIZE 100 
typedef struct _ADRESSE
{
	char rue[30];
	int NUMrue;
	int codePostale;
	char ville[30];
}ADRESSE;
typedef struct _CONTACT
{

	char nom[SIZE];
	char prenom[SIZE];
	char date[SIZE];
	char telephone[SIZE];
	ADRESSE adresse;
	char email[SIZE];


}CONTACT;
typedef struct _NODE
{

	CONTACT contact;
	struct _NODE* next;
	struct _NODE* prev;
} NODE;

typedef struct
{
	NODE* head;
	NODE* tail;
} LIST;

void printFiche(CONTACT contact);
void appendToList(LIST* list, CONTACT contact);
void printList(LIST list);
void saveFiche(FILE* file, CONTACT contact);
void SaveList(LIST list);
void loadFiche(CONTACT* contact, char* str);
LIST loadlist(FILE* file);
CONTACT ficheFromInput(void);
CONTACT searchforcontact(LIST list);
CONTACT modifiedcontact(LIST* list, CONTACT cont);
CONTACT removeFromList(LIST* list, CONTACT contact);

void main(void)
{
	LIST list = { NULL,NULL };
	/*
	CONTACT Contact1 = {"Toto","Bardati","2/7/1999","3364585712",{"impasseBarbier",4,92110,"Clichy"},"Sami1999@outlook.com"};
	appendToList(&list, Contact1);
	CONTACT Contact2 = { "iyad","mobarak","2/5/1996","3364585712",{ "impasseBarbier",10,92110,"Clichy" },"iyad1999@outlook.com" };
	
	appendToList(&list, Contact2);
	CONTACT Contact3 = { "Omar","Omar","2/10/1998","3364585712",{ "impasseBarbier",8,92110,"Clichy" },"omar1999@outlook.com" };
	
	appendToList(&list, Contact3);
	SaveList(list);
	*/
	CONTACT Contactcherche, modified;


	FILE* file;
	file = fopen("Contacts.csv", "r");
    list = loadlist(file);

	printList(list);

	char choix;
	// searchforcontact(list);
	
	do {
		printf("Enter your choice:\n"
			" 1 Rechercher un contact \n"
			" 2 Afficher un contact \n"
			" 3 Supprimer un contact\n"
			" 4 Mise à jour d'un contact\n"
			" 5 Quit program\n");

		scanf("%c", &choix);
		rewind(stdin);
		switch (choix) {
		case '1':
		 Contactcherche = searchforcontact(list);
			

			break;
		case '2':
			
		     printFiche(Contactcherche);
			break;
		case '3':
			//printf("cette fonction n'a pas été fait encore");

			removeFromList(&list,Contactcherche);	
			SaveList(list);
			break;

		case '4':
			
				 modified = modifiedcontact(&list, Contactcherche);
				 SaveList(list);
			break;

		case '5':

			exit(0);
			break;
		}
	} while (choix != '5');



	system("pause");

}



void printFiche(CONTACT contact)
{
	printf("\n");
	printf("Here's the content of the Contact: \n");
	printf("Name      :  %s ", contact.nom); 
	printf("\n");                                                                             //In this function we print the data that we declared 
	printf("Surname   :  %s ", contact.prenom);
	printf("\n");
	printf("Date  :  %s ", contact.date);
	printf("\n");
	printf("Numero de telephone   : %s ", contact.telephone);
	printf("\n");
	printf("Adresse   :  \n");
	//printf("\n");
	printf("-------------------------");
	printf("\n");
	printf("Numero de rue :  %d   ", contact.adresse.NUMrue);
	printf("\n");
	printf("Rue  : %s   ", contact.adresse.rue);
	printf("\n");
	printf("Code postale : %d ", contact.adresse.codePostale);
	printf("\n");
	printf("Ville : %s ", contact.adresse.ville);
	printf("\n");
	printf("EMAIL  : %s ", contact.email);


}


void appendToList(LIST* list, CONTACT contact)
{
	NODE* node = calloc (1, sizeof(NODE));   
	//on alloue un espace mémoire de 1 cases dememe taille que node, initialise à 0
	node->contact = contact;
	
	if (list->tail)
	{
		list->tail->next = node;
		node->prev = list->tail;
		list->tail = node;

	}
	else
	{
		list->head = node;
		list->tail = node;
	}
	

}

void printList(LIST list) { /* affichage en avançant */
	NODE* fleche;
	fleche = list.head; /* point du départ le 1er élément */


	int i = 1;
	while (fleche != NULL)                                                  //En fait on se retrouve au début de la liste, ensuite en utilisant le pointeur suivant de chaque élément la liste 
																			//est parcourue du 1er vers le dernier élément.
	{
		printf(" \n #FICHE %d \n", i);
		printFiche(fleche->contact);
		fleche = fleche->next;
		i++;
	}


}


void SaveList(LIST list)
{
	NODE* fleche;
	fleche = list.head;
	FILE* p;
	p = fopen("Contacts.csv", "w");

	if (p != NULL)
	{

		while (fleche != NULL)                                                  //En fait on se retrouve au début de la liste, ensuite en utilisant le pointeur suivant de chaque élément la liste 
																				//est parcourue du 1er vers le dernier élément.
		{
			printf("\n");
			printf(" Saving data %d ...Please wait ", i);
			saveFiche(p, fleche->contact);
			fleche = fleche->next;
			i++;
		}
		printf(" Data is saved successfully ");
		fclose(p);
	}
	else
	{
		printf("The file doesn't exist");


	}


}
void saveFiche(FILE* file, CONTACT contact)
{

	if (file == NULL)
	{
		fprintf(stderr, "Error : File not found !\n");
		exit(EXIT_FAILURE);
	}
	fprintf(file, "%s;%s;%s;%s;%d;%s;%d;%s;%s\n", contact.nom, contact.prenom, contact.date, contact.telephone,
		contact.adresse.NUMrue, contact.adresse.rue, contact.adresse.codePostale, contact.adresse.ville, contact.email);
}

void loadFiche(CONTACT* contact, char* str)
{
	char* separateur = ";";
	char* seg;

	seg = strtok(str, separateur);
	strcpy(contact->nom, seg);
	seg = strtok(NULL, separateur);
	strcpy(contact->prenom, seg);
	seg = strtok(NULL, separateur);
	strcpy(contact->date, seg);
	seg = strtok(NULL, separateur);
	strcpy(contact->telephone, seg);
	seg = strtok(NULL, separateur);
	contact->adresse.NUMrue = atoi(seg);
	seg = strtok(NULL, separateur);
	strcpy(contact->adresse.rue, seg);
	seg = strtok(NULL, separateur);
	contact->adresse.codePostale = atoi(seg);
	seg = strtok(NULL, separateur);
	strcpy(contact->adresse.ville, seg);
	seg = strtok(NULL, separateur);
	strcpy(contact->email, seg);
	seg = strtok(NULL, separateur);
}

LIST loadlist(FILE* file)
{
	LIST list = { NULL,NULL };
	CONTACT contact;

	char loadedstr[100];

	file = fopen("Contacts.csv", "r");
	if (file != NULL)
	{
		while (!feof(file))
		{

			char* test = fgets(loadedstr, 100, file);
			loadedstr[strlen(loadedstr) - 1] = '\0';
			if (test == NULL)
			{
				break;

			}



			loadFiche(&contact, loadedstr);

			appendToList(&list, contact);`


		}


	}

	return list;
	fclose(file);


}


CONTACT ficheFromInput(void)
{
	CONTACT contactajoute;
	int number;
	int postalcode;

	char str[SIZE];


	printf("What is your name?\n\t");
	fgets(str, SIZE, stdin); //lis au clavier le nom de la fiche, taille max 80
	str[strlen(str) - 1] = '\0';
	strcpy(contactajoute.nom, str);


	printf("What is your firstname?\n\t");
	fgets(str, SIZE, stdin); //lis au clavier le prenom de la fiche, taille max 80
	str[strlen(str) - 1] = '\0';
	strcpy(contactajoute.prenom, str);

	printf("What is your birthdate ?\n\t");
	fgets(str, SIZE, stdin); //lis au clavier le prenom de la fiche, taille max 80
	str[strlen(str) - 1] = '\0';
	strcpy(contactajoute.date, str);



	printf("What is your phone number?\n\t");
	fgets(str, SIZE, stdin);
	str[strlen(str) - 1] = '\0';
	strcpy(contactajoute.telephone, str);



	printf("What is your street number ?\n\t");
	fgets(str, SIZE, stdin); //lis au clavier le prenom de la fiche, taille max 80
	str[strlen(str) - 1] = '\0';
	number = sscanf(str, "%d %*s", &contactajoute.adresse.NUMrue);


	printf("What is your street name ?\n\t");
	fgets(str, SIZE, stdin); //lis au clavier le prenom de la fiche, taille max 80
	str[strlen(str) - 1] = '\0';
	strcpy(contactajoute.adresse.rue, str);


	printf("What is your postal code ?\n\t");
	fgets(str, SIZE, stdin); //lis au clavier le prenom de la fiche, taille max 80
	str[strlen(str) - 1] = '\0';
	postalcode = sscanf(str, "%d %*s", &contactajoute.adresse.codePostale);


	printf("What is your city ?\n\t");
	fgets(str, SIZE, stdin);
	str[strlen(str) - 1] = '\0';
	strcpy(contactajoute.adresse.ville, str);


	printf("What is your email?");
	fgets(str, SIZE, stdin);
	str[strlen(str) - 1] = '\0';
	strcpy(contactajoute.email, str);

	return contactajoute;
}

CONTACT searchforcontact(LIST list)
{
	CONTACT searched = { NULL };
	NODE* fleche;
	
	fleche = list.head; /* point du départ le 1er élément */

	printf(" \n Veuillez saisir le nom du contact que vous cherchez :");
	char chaine1[SIZE];
	fgets(chaine1, SIZE, stdin);
	chaine1[strlen(chaine1) - 1] = '\0';


	while (fleche != NULL)                                                  //En fait on se retrouve au début de la liste, ensuite en utilisant le pointeur suivant de chaque élément la liste 
																			//est parcourue du 1er vers le dernier élément.
	{


		if (strcmp(chaine1, fleche->contact.nom) == 0)
		{

			searched=fleche->contact;
			return searched;

		}

		else {
			fleche = fleche->next;
			
			
			}
		} 
return searched;
	}

	
	









CONTACT modifiedcontact(LIST* list, CONTACT cont)
{	CONTACT empty = { NULL,NULL };
	int number;
	int postalcode;
	char str[SIZE];
	NODE* fleche;
	
	
	char str1[SIZE];
	strcpy(str1,cont.nom );
	
	
	char str2[SIZE];
	strcpy(str2, empty.nom );

	




	if (strcmp(str1,str2) == 0)
	{
		printf("The contact doesn't exist");
		return empty;
	}

	else
	{

		fleche = list->head;
		while (fleche != NULL)                                                  //En fait on se retrouve au début de la liste, ensuite en utilisant le pointeur suivant de chaque élément la liste 
																				//est parcourue du 1er vers le dernier élément.
		{


			if (strcmp(str1, fleche->contact.nom) == 0)
			{

				
				break;

			}

			else {
				fleche = fleche->next;


			}
		}

		printf(" \n What is the new name ?\n\t");
		fgets(str, SIZE, stdin); //lis au clavier le nom de la fiche, taille max 80
		str[strlen(str) - 1] = '\0';
		strcpy(fleche->contact.nom, str);


		printf("What is the new surname ?\n\t");
		fgets(str, SIZE, stdin); //lis au clavier le prenom de la fiche, taille max 80
		str[strlen(str) - 1] = '\0';
		strcpy(fleche->contact.prenom, str);

		printf("What is the new birthday ??\n\t");
		fgets(str, SIZE, stdin); //lis au clavier le prenom de la fiche, taille max 80
		str[strlen(str) - 1] = '\0';
		strcpy(fleche->contact.date, str);



		printf("What is the new phone number ?\n\t");
		fgets(str, SIZE, stdin);
		str[strlen(str) - 1] = '\0';
		strcpy(fleche->contact.telephone, str);



		printf("What is the new street number ?\n\t");
		fgets(str, SIZE, stdin); //lis au clavier le prenom de la fiche, taille max 80
		str[strlen(str) - 1] = '\0';
		number = sscanf(str, "%d %*s", &fleche->contact.adresse.NUMrue);


		printf("What is your street name ?\n\t");
		fgets(str, SIZE, stdin); //lis au clavier le prenom de la fiche, taille max 80
		str[strlen(str) - 1] = '\0';
		strcpy(fleche->contact.adresse.rue, str);


		printf("What is the new postal code ?\n\t");
		fgets(str, SIZE, stdin); //lis au clavier le prenom de la fiche, taille max 80
		str[strlen(str) - 1] = '\0';
		postalcode = sscanf(str, "%d %*s", &fleche->contact.adresse.codePostale);


		printf("What is your city ?\n\t");
		fgets(str, SIZE, stdin);
		str[strlen(str) - 1] = '\0';
		strcpy(fleche->contact.adresse.ville, str);


		printf("What is your email?");
		fgets(str, SIZE, stdin);
		str[strlen(str) - 1] = '\0';
		strcpy(fleche->contact.email, str);
		return fleche->contact;
	}

	
}

CONTACT removeFromList(LIST* list, CONTACT contact)
{

	char str4[SIZE];
	strcpy(str4, contact.nom);

	NODE* fleche= list->head;
	int i;
	CONTACT vide = {NULL,NULL };
	if(fleche == NULL)
	{
		//printf("La liste est vide");
		return vide;
	}

	else
	{
		/*On se positionne sur l'élément à supprimer*/
		for (i = 0; fleche != NULL; i++)
		{
			strcpy(str4, contact.nom);
			if (strcmp(str4,fleche->contact.nom) == 0)
				break;
			fleche = fleche->next;
		}
		/* Si on l'a pas trouvé on retourne vide*/
		if (fleche == NULL)
		{
			return vide;
		}
		
		/*Sinon s'il est la queue de liste*/
		else if (fleche== list->tail)
		{
			list->tail = fleche->prev;
			fleche->prev->next = NULL;
			//temp->prev == NULL;
			//free(temp);
			return fleche->contact;
		}
		/*Sinon s'il n'est ni la tete ni la queue*/
		else
		{
			fleche->next->prev = fleche->prev;
			fleche->prev->next= fleche->next;
			return fleche->contact;
		}
	}
}

