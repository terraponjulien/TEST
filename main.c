#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#define TAILLE_MAX 1000

void afficherMenu();
void AfficherAide();
int Authentification();
int Jouer();
int TableauScores();
int AfficherGrille(char grillej[][10]);
char pseudo[100];

int main()
{
    char retour_utilisateur;
    int Quitter=1;

    printf("asdadad");
    printf("sa marche ou pas");


    //boucle while pour choisir un ‚l‚ment du menu
    while(Quitter){
        afficherMenu();
        scanf("%c", &retour_utilisateur);
        fflush(stdin);
            switch(retour_utilisateur){
                case '1':
                    ecrireEvennements("Commencement d'une partie");
                    Jouer();
                    ecrireEvennements("Partie termin‚e");
                    break;
                case '2':
                    ecrireEvennements("Affichache de l'aide du jeu");
                    AfficherAide();
                    break;
                case '3':
                    ecrireEvennements("Affichage du tableau des scores");
                    TableauScores();
                    break;
                case '4':
                    ecrireEvennements("Fermeture de l'application");
                    Quitter=0;
                    break;
                default:
                    printf("\n\tVeuillez entrer un des 4 choix");
                    fflush(stdin);
                    Sleep(1000); //les diff‚rents sleep pr‚sent dans ce code ont pour but de laisser afficher un message pendant un certain temps avant que le code continu … ˆtre lu et qu'ils disparaissent
                    system("cls");
                    break;
                }
    }
    return EXIT_SUCCESS;
}

/** \brief fonction qui affiche le menu, elle est utilis‚e dans la boucle While ci-dessus(fonction main)

 *
 * \return void
 *
 */
void afficherMenu()
{
    printf("\n\n\n\t1. Jouer\n");
    printf("\t2. Aide de jeu\n");
    printf("\t3. Tableau des scores\n");
    printf("\t4. Quitter le jeu\n\n");
    printf("\tEntrez votre choix: ");
}

/** \brief fonction qui affiche l'aide de jeu, est utilis‚ dans la boucle While ci-dessus(fonction main)
 *
 * \return void
 *
 */
void AfficherAide()
{
    char retour_menu;

    system("cls");
    printf("\n\n\n\n");
    printf("\tRegle de la bataille naval:\n\n");
    printf("\t\tLe but de cette bataille navale est de couler tous les bateaux\n"
           "\t\tde la grille en entrant leurs coordonnees.\n\n\n");
    printf("\tComment jouer?\n\n");
    printf("\t\t1. Entrez les coordonnees de la ligne.\n"
           "\t\t2. Entrez les coordonnees de la colonne.\n"
           "\t\t3. Referez-vous au message qui s'affiche en dessous de la grille et reflechissez a votre prochain coup.\n"
           "\t\t4. Repetez ces operations jusqu'a avoir coule tous les bateaux.");
    printf("\n\n\n\t\tAppuyez sur Enter pour revenir au menu principal ");
    scanf("%c", &retour_menu);
    fflush(stdin);
    system("cls");
}

/** \brief
 *
 * \return int
 *
 */
int TableauScores()
{
    char chaine[TAILLE_MAX]= "";
    char retour;

    system("cls");

    printf("\n\n\n\n");
    printf("\t\t\t\t\t\t\tTableau des scores\n\n\n");
    printf("\t\t\t\t\tPseudo\t\tNombre de coups\t\t\Chrono\n\n");

    FILE *fichier = NULL;
    fichier = fopen("Scores.txt","r");

    if (fichier != NULL)
    {
        while (fgets(chaine, TAILLE_MAX, fichier) != NULL)
        {
            printf("%s", chaine);
        }
        fclose(fichier);
    }
    else{
        ecrireEvennements("Impossible d'ouvrir le fichier scores");
    }

    printf("\n\n\n");
    printf("\t\t\t\t\tAppuyer sur Enter pour revenir au mennu principal");
    scanf("%c", &retour);
    system("cls");

}

/** \brief fonction
 *
 * \return int
 *
 */
int Jouer()
{
    int BateauTouche;
    char grillej[10][10];
    int grille[10][10]= {{0,0,0,0,0,0,0,0,0,0},  //grille de position des bateaux cod‚ en dur
                         {0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0}};

    int i, j;
    int choix_x= 0, choix_y= 0;
    int comptouche=0; //compteur qui va compter le nombre de tirs qui touchent, sa valeur d‚ternime si on sort de la boucle do while ci-dessous
    int comptcoup= 0; //compteur qui compte le nombre de coups tir‚s pour l'afficher … l'utilisateur en fin de partie
    char retour_menu;

    lireFichierGrille(grille);

    Authentification();//Rappel de la fonction Authentification afin que le joueur s'authentifie avant le d‚but de la partie

    //boucle for qui va dire … grillej d'afficher une grille de O au d‚but de la partie
    for(i=0; i<10; i++){
        for(j=0; j<10; j++){
                grillej[i][j]='O';
        }
    }
    clock_t start, end;
    double ChronoParti;
    //boucle do while o— le d‚roulement de la partie est cod‚, le partie est termin‚ lorsqu'on sort de cette boucle
    start=clock();//d‚marage du chronomŠtre
    do{

        AfficherGrille(grillej);

        do{
            printf("Entrer coordonn‚e ligne: ");
            scanf("%i", &choix_x);
        }while(choix_x>9 || choix_x<0);
        do{
            printf("Entrer coordonn‚e colonne: ");
            scanf("%i", &choix_y);
        }while(choix_y>9 || choix_y<0);
        comptcoup++;

        //if qui permet d'afficher le message ci-dessous si le joueur tir sur un bateau qui est d‚j… touch‚
        if(grillej[choix_x][choix_y]== 'X')
        {
            printf("\t\t\t\t\t\t Vous avez deja touche ce bateau !");
            Sleep(1500);
        }

        //if qui va v‚rifier si le joueur a toucher un bateau
        if(grille[choix_x][choix_y]!=0 & grillej[choix_x][choix_y] != 'X')
            {
            grillej[choix_x][choix_y]= 'X'; // Va remplacer le O … l'endroit touch‚ par un X dans grillej
            BateauTouche = grille[choix_x][choix_y];
            grille[choix_x][choix_y]= -1;
            comptouche++;
            printf("\t\t\t\t\t\tTouch‚ !");
            if(BateauCoule(grille,BateauTouche)==1) //If qui v‚rifie si le bateau touch‚ est coul‚
                {
                printf("\n\n\t\t\t\t\t\t-------\n");
                printf("\t\t\t\t\t\tCoul‚ !\n");
                printf("\t\t\t\t\t\t-------");
                }
            Sleep(1500);
            }
        if(grille[choix_x][choix_y] == 0)  //if qui v‚rifie si le tir est rat‚
            {
            printf("\t\t\t\t\t\tRat‚ !");
            Sleep(1500);
            }
    }while(comptouche<18);
    end = clock();
    ChronoParti = ((double)end - start) / CLOCKS_PER_SEC;

    AfficherGrille(grillej); //Rappel de la fonction AfficherGrille(grillej) pour qu'elle affiche la grille mise a jour aprŠs le dernier coup de la partie (sans elle la grille ne s'affiche pas car nous sommes sorti de la boucle do while ci dessus)

    fflush(stdin);
    printf("----------------------------------------\n");
    printf("Bravo ! Vous avez coul‚ tous les bateaux !\n");
    printf("Nombre de coups utilis‚s: %d\n", comptcoup);
    printf("Duree de la partie: %.2f secondes\n", ChronoParti);
    printf("----------------------------------------");
    printf("\nAppuyer sur Enter pour revenir au menu principal ");

    //Inscription du pseudo, nombre de coups et du chrono dans le fichier
    FILE *fichier = NULL;
    fichier = fopen("Scores.txt","a");
    fprintf(fichier, "\t\t\t\t\t%s", pseudo);
    fprintf(fichier, "\t\t%i", comptcoup);
    fprintf(fichier, "\t\t\t%.2fsec\n", ChronoParti);
    fclose(fichier);

    scanf("%c", &retour_menu);
    fflush(stdin);
    system("cls");
}

/** \brief fonction qui va afficher la grille visible pour le joueur en la mofifiant au fil de la partie,
            on fait appel … elle au d‚but de la boucle while ci-dessus (fonction Jouer)
 *
 * \param grillej[][10] char
 * \return int
 *
 */
int AfficherGrille(char grillej[][10]){

    int i, j;

    system("cls");
        printf("  0 1 2 3 4 5 6 7 8 9\n");
        //boucle for qui va mofifier grillej si un bateau a ‚t‚ touch‚
        for(i=0; i<10; i++){
                printf("%d ", i);
            for(j=0; j<10; j++){
                    printf("%c ", grillej[i][j]);
            }
            printf("\n");
        }
}

/** \brief fonction utilis‚ avant chaque d‚but de partie afin que le joueur s'authentifie
 *
 * \return int
 *
 */
int Authentification()
{
    char retour_menu;


    system("cls");
    do{
        printf("\n\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t\t7 caracteres maximum");
        printf("\n\t\t\t\t\tPas de caracteres speciaux");
        printf("\n\t\t\t\t\tEntrez votre pseudo: ");
        scanf("%s", &pseudo);
        system("cls");
    }while(strlen(pseudo)>7);
    ecrireEvennements("Authentification du joueur");
    fflush(stdin);
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t\t7 caracteres maximum");
    printf("\n\t\t\t\t\tPas de caracteres speciaux");
    printf("\n\t\t\t\t\tEntrez votre pseudo: %s", pseudo);
    printf("\n\n\t\t\t\t\tAppuyez sur Enter pour commencer la partie ");
    scanf("%c", &retour_menu);
    fflush(stdin);
    system("cls");
}

/** \brief fonction qui v‚rifie si le bateau touch‚ est coul‚, est utilis‚ dans la boucle do while ci-dessus (int Jouer)
 *
 * \param grille[][10] char
 * \param BateauTouche int
 * \return int
 *
 */
int BateauCoule(int grille[][10],int BateauTouche)
{
    int i, j;
    for(i=0; i<10; i++){
        for(j=0; j<10; j++){
            if(grille[i][j] == BateauTouche){
                return 0; //Retourne 0 si le bateau n'est pas coul‚
            }
        }
    }
    return 1; //Retourne 1 si le bateau est coul‚

}

/** \brief Fonction qui va s‚lectionner et lire les fichier ou se trouvent les grilles
 *
 * \param exemple[10][10] int
 * \return int
 *
 */
int lireFichierGrille(int exemple[10][10])
{
    FILE* fichier = NULL;
    int fX, fY, fNumBateau, EndOfFile;
    int rdm = 0;

    rdm = random(1,3);

    switch(rdm){
    case 1:
        fichier = fopen("Grille1.txt", "r");
        ecrireEvennements("Ouverture grille 1");
        break;
    case 2:
        fichier = fopen("Grille2.txt", "r");
        ecrireEvennements("Ouverture grille 2");
        break;
    case 3:
        fichier = fopen("Grille3.txt", "r");
        ecrireEvennements("Ouverture grille 3");
        break;
        }

    if (fichier != NULL)
    {
        while(EndOfFile!=EOF){
            EndOfFile = fscanf(fichier, "%i %i %i", &fX, &fY, &fNumBateau);
            exemple[fX][fY] = fNumBateau;
        }
        fclose(fichier);
        return 0;
    }
    else{
        ecrireEvennements("Impossible d'ouvrir le fichier grille s‚lectionn‚");
        return -1;
    }
}

/** \brief Fonction qui va ‚crire les diff‚rentes donn‚es importantes dans le fichier Evennements
*
* \param log[100]
* \return void
*
*/
void ecrireEvennements(char log[100]){
    FILE* fichier = NULL;
    time_t s;
    struct tm* current_time;

    fichier = fopen("Evennements", "a");
    s = time(NULL);
    current_time = localtime(&s);

    if (fichier != NULL)
    {
        fseek(fichier, 0, SEEK_END);
        fprintf(fichier,"[%02d/%02d/%d %02d:%02d:%02d] %s\n",current_time->tm_mday,current_time->tm_mon+1,current_time->tm_year+1900,current_time->tm_hour,current_time->tm_min,current_time->tm_sec,log);
        fclose(fichier);
    }else{
        printf("Impossible de lire le fichier");

    }
}
/** \brief Permet de cr‚e plusieurs nombre al‚atoire diff‚rent sans attendre 1 sec … chaque appel source: https://openclassrooms.com/forum/sujet/generateur-de-nombre-aleatoire-entre-1-et-9
*
* \param a int Borne Min
* \param b int Borne Max
* \return int
*
*/
int random(int a, int b){
    static int rand_is_seeded = 0;
    if(!rand_is_seeded)
    {
        srand(time(NULL));
        rand_is_seeded = 1;
    }

    return rand() % (b-a+1)+a;
}



