

          /*********************************************************************************
           *    Nom de programme     : JEU DE MORPION                                      *
           *    Date de création     : 05/04/2019                                          *
           *    Auteur               : AIT OUAKRIM Abdessamad                              *
           *********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define L 3
#define C 3

typedef enum {
vide , X , O
}Grille;      //Structure contient les valeurs de la grille ( vide ou X ou O )

Grille grille[L][C];  //j'ai declarer la grille au premier de programme pour ne pas repeter  

typedef enum {FALSE, TRUE} boolean;  //J'ai crée un type "bool" pour l'utilise au programme

typedef struct {
	char nom[20];
	Grille jeton;      //chaque joueur a son jeton (X oubien O)  
}joueur;
  
joueur j1; 
joueur j2;

Grille jeton = X ;

Grille nextTour = X ;   //pour utiliser à l'echange de tour entre les deux joueurs

char initialise_grille()    //la fonction qui initialise la grille
{
   	int i, j; 
   	for(i=0;i<L;i++)
	   for(j=0;j<C;j++)
	      grille[i][j]=vide;
}

void afficheGrille(){      //la fonction qui affiche la grille
  int i, j;
    printf("\t\t\t\t\t    1   2   3  \n");
  for(i=0; i<L; i++){
  	printf("\t\t\t\t\t  -------------\n");
  	printf("\t\t\t\t\t");
  	printf("%d ",i+1);
    for (j=0; j<C; j++) {
      printf("| ");
      switch (grille[i][j]) {
      case vide :
	printf("\40\40");
	break;
      case O :
	printf("O ");
	break;
      case X :
	printf("X ");
	break;
      }
    }
    printf("|\n");
  }
  printf("\t\t\t\t\t  -------------\n\n");
}


void placer_jeton()     //la fonction qui tester la case s'elle est disponible et elle place le jeton dans cette case  
{
	int l, c;
	j1.jeton=X ;
	j2.jeton=O ;
	boolean saisirCorrect=FALSE;
	if(nextTour==X){                        //l'echange des tour entre les deux joueurs
		printf("Le tour de %s :\n",j1.nom);
		nextTour=O;	
	}else{
	   printf("Le tour de %s :\n",j2.nom);
	   nextTour=X;
    }
	   
	do{
		printf("donner le numero de ligne : ");
		scanf("%d",&l);
		printf("donner le numero de colonne: ");
		scanf("%d",&c);
		if((l>0) && (l<=L) && (c>0) && (c<=C)){             //test si le numéro de ligne ou de colonne est correct
			l--;
			c--;
		if(grille[l][c] != vide){         //test si la case est vide
            printf("Cette case est deja remplie. Veuillez ressayez: \n\n");
	                 
                if(nextTour==X)      // pour ne pas perdu le tour de joueur
                    nextTour=O;
                else
                    nextTour=X;
                    
			}else {
			  saisirCorrect = TRUE;
	          grille[l][c] = jeton;
	            if (jeton == O )
	                 jeton = X ;
	            else
	                 jeton = O ;
              }	
		}else{
		  printf("numero de ligne ou de colonne est incorrect. Veuillez ressayez:\n\n");
		  
            if(nextTour==X)        // pour ne pas perdu le tour de joueur
               nextTour=O;
            else
               nextTour=X;
        }
	}while(saisirCorrect=FALSE);
}


boolean testeFinJeu() {            //la fonction qui test si le jeu est fini et elle donne le vainqueur 
  int i,j;
  Grille joueurGagnant=vide;
  boolean jeuFini = FALSE;

  if (grille[1][1] != vide) {   //si grille[1][1] (la case au milieu) est vide on n'a pas besoin de tester (la colonne 2 et la ligne 2 et les deux diagonales)
    if (((grille[0][1] == grille[1][1]) && (grille[1][1] == grille[2][1])) ||
	   ((grille[1][0] == grille[1][1]) && (grille[1][1] == grille[1][2])) ||
	   ((grille[0][0] == grille[1][1]) && (grille[1][1] == grille[2][2])) ||
	   ((grille[0][2] == grille[1][1]) && (grille[1][1] == grille[2][0]))) 
	{ 
      joueurGagnant = grille[1][1];
      jeuFini = TRUE;
    }
  }

  if ((!jeuFini) && (grille[0][0] != vide)) {    //si grille[0][0] (la case premiere) est vide on n'a pas besoin de tester (la colonne 1 et la ligne 1 )
    if (((grille[0][0] == grille[0][1]) && (grille[0][1] == grille[0][2])) ||
	   ((grille[0][0] == grille[1][0]) && (grille[1][0] == grille[2][0]))) {
      joueurGagnant = grille[0][0];
      jeuFini = TRUE;
    }
  }

  if ((!jeuFini) && (grille[2][2] != vide)) {    //si grille[2][2] (la case derniere) est vide on n'a pas besoin de tester (la colonne 3 et la ligne 3 )
    if (((grille[2][0] == grille[2][1]) && (grille[2][1] == grille[2][2])) ||
	   ((grille[0][2] == grille[1][2]) && (grille[1][2] == grille[2][2]))) {
      joueurGagnant = grille[2][2];
      jeuFini = TRUE;
    }
  }

  if (jeuFini) {
    if (joueurGagnant == X )
      printf("Felicitations au joueur %s ayant les croix ( X ) qui a gagne.\n\n",j1.nom);
    else 
	   printf("Felicitations au joueur %s ayant les ronds ( O ) qui a gagne.\n\n",j2.nom); 
    return TRUE;
  }
  
  for (i=0; i<L; i++) {
    for (j=0; j<C; j++) {
      if (grille[i][j] == vide) /*Au moins une case est vide c'est à dire le jeu n'est pas fini donc le programme va continue a derouler */
	return FALSE;                  
    }
  }
  
    for (i=0; i<L; i++) {   //test si la grille est pleine et il n'y a pas de vainqueur
    for (j=0; j<C; j++) {
      if (grille[i][j] != vide) //tout les case sont remplie
	     printf("il n'y a pas de vainqueur. Le jeux est fini par l'egalite.\n\n");
	return TRUE;
    }
  }
  return TRUE;
  
}



                    /*******le programme principal*******/
int main() {
  int reponse;
  int r=1;
  Grille i=X;
     printf("donner le nom de joueur 1 : ");   //remplissage des noms des joueurs
     gets(j1.nom);
     printf("donner le nom de joueur 2 : ");
     gets(j2.nom);
     initialise_grille();
     afficheGrille();
       do {
         placer_jeton();
         afficheGrille();
       }while(!testeFinJeu());

     return 0;
}
