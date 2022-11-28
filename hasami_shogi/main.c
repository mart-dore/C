#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
---------------------------------------------------
 Afin de ne pas surcharger le programme
 les informations sur les paramètres, données etc.. 
 se trouve dans le rapport
--------------------------------------------------
*/


//la taille du plateau est fixe: 
#define TAILLE 10
#define FALSE 0
#define TRUE 1



void affichage_plateau(char mat[TAILLE][TAILLE]){
	int j;
  int i;
  char lettre='A';
        
    /* Affichage des indices de colonnes */
    printf("    ");
    for (j=1; j<10; j++) printf("%d  ",j);
    printf("\n");
        
    /* Affichage de la matrice */
    for (i=0; i<TAILLE-1; i++) {
        printf("%c   ",lettre);
        lettre++;
        for (j=0; j<TAILLE-1; j++) printf("%c  ", mat[i][j]);
        printf("\n");
    }
	
    printf("\n");
}





//joueur est un entier qui varie entre 1 et 2 et permet de determiner le joueur en cours
void changement_joueur(int *joueur){
  if(*joueur==1){
    *joueur=2;
  }
  else *joueur=1;
}


//affiche le joueur qui doit jouer
void affichage_joueur(int j){
  char pion='B';
  if(j==2)pion='N';
  printf("C'est au tour du joueur %d (%c)\n", j,pion);
}

//renvoie la valeur absolue
int abs(int x){
  return x>0 ? x : -x;
}

//renvoie la distance entre deux nombres
int distance(int a, int b){
  return abs(a-b);
}




//remplit le plateau avec les pions noirs et blancs de chaque côte
void initialisation_plateau(char plateau[TAILLE][TAILLE]){
int i,j;
//remplissage des pions
 for(i=0 ; i<TAILLE-1;i++){
   plateau[0][i]='N';
   plateau[1][i]='N';
   plateau[7][i]='B';
   plateau[8][i]='B';

 }
 //remplissage des cases "vides"
 for(i=2;i<7;i++){
   for(j=0;j<TAILLE-1;j++){
     plateau[i][j]='.';
   }
 }
}


//verifie qu'une coordonnee (abcisse ou ordonnee est sur le plateau)
int estSurPlateau(int a){
  return(a>=0 && a<10);
}


//un deplacement est possible si :
//le joueur bouge un pion qui lui appartient
//-la case est libre 
//-la case se situe dans la meme ligne/colonne
//-le pion ne rencontre pas de pion
//-le pion saute un pion adjacent ---> il ne peut parcourir que deux cases
int deplacement_possible(char plateau[][TAILLE],int player, char caseDep[2], char caseArr[2]) {
  //conversion des donnees Lettres/Chiffres en indice de la matrice
  int lArr=(int)caseArr[0]-65;
  int cArr=(int)caseArr[1]-49;
  int lDep=(int)caseDep[0]-65;
  int cDep=(int)caseDep[1]-49;

 
  int indParcours; //indice de parcours
  int bloque= FALSE; //indique si un pion bloque le chemin

//test des coordonnées dans le plateau
if(!estSurPlateau(lArr) || !estSurPlateau(cArr) || !estSurPlateau(lDep) || !estSurPlateau(cDep)){
  printf("Une des coordonnees n'est pas sur le plateau\n");
  return FALSE;
}  

//test que la case de depart n'est pas vide
if(plateau[lDep][cDep]=='.'){
  printf("Case de depart vide\n");
  return FALSE;
}

//test que le joueur bouge un de SES pions
  if((player==1 && plateau[lDep][cDep]=='N') || (player==2 && plateau[lDep][cDep]=='B')){
    printf("Vous ne pouvez bouger que vos propres pions\n");
    return FALSE;
  }

 //test si la case d'arrivee est vide
 if(plateau[lArr][cArr]!='.'){
   printf("Case d'arrivee occupee\n");
   return FALSE;
 }
 //test si le deplacement s'effectue en ligne droite
 else if(cArr!=cDep && lArr!=lDep){
   printf("Deplacement en ligne droite uniquement\n");
   return FALSE;
 }
 
 //le deplacement est valide -> verifier qu'aucun pion ne bloque
 else{
   //deplacement horizontal (même colonne)
   if(cArr==cDep){
   //deplacement vers le bas
   if(lArr>lDep){
     indParcours=lDep+1;
    while(indParcours<=lArr && !bloque){
      if(plateau[indParcours][cArr]!='.'){
        bloque=TRUE;
      }
      indParcours++;
    }
    //si le pion est bloque -> peut-on le sauter
      if(bloque && distance(lArr,lDep)==2){
          printf("Saut de pion\n");
          return TRUE;
      }
    //si le pion est bloque et ne peut sauter -> deplacement impossible
     if(bloque){
      printf("Un pion bloque le deplacement  \n");
      return FALSE;
     }
     //si le pion n'est pas bloque -> deplacement possible
     else return TRUE;
    }
  

   //deplacement vers le haut
   if(lArr<lDep){
     indParcours=lDep-1;
    while(indParcours>=lArr && !bloque){
      if(plateau[indParcours][cArr]!='.'){
        bloque=TRUE;
        
      }
      indParcours--;
    }
    //si le pion est bloque -> peut-on le sauter
      if(bloque && distance(lArr,lDep)==2){
          printf("Saut de pion\n");
          return TRUE;
      }
    //si le pion est bloque et ne peut sauter -> deplacement impossible
     if(bloque){
      printf("Un pion bloque le deplacement \n");
      return FALSE;
     }
     //si le pion n'est pas bloque -> deplacement possible
     else return TRUE;
    }
  }

  else{//deplacement horizontal
    if(cArr>cDep){//deplacement vers la droite
     indParcours=cDep+1;
     while(indParcours<=cArr && !bloque){
       if(plateau[lDep][indParcours]!='.'){
        bloque=TRUE;
        
      }
      indParcours++;
    }
    //si le pion est bloque -> peut-on le sauter
      if(bloque && distance(cArr,cDep)==2){
          printf("Saut de pion\n");
          return TRUE;
      }
    //si le pion est bloque et ne peut sauter -> deplacement impossible
     if(bloque){
      printf("Un pion bloque le deplacement \n");
      return FALSE;
     }
     //si le pion n'est pas bloque -> deplacement possible
     else return TRUE;
    }
    else{//deplacement vers la gauche
     indParcours=cDep-2;
     while(indParcours>=cArr && !bloque){
       if(plateau[lDep][indParcours]!='.'){
        bloque=TRUE;
        
      }
      indParcours--;
    }
    //si le pion est bloque -> peut-on le sauter
      if(bloque && distance(cArr,cDep)==2){
          printf("Saut de pion\n");
          return TRUE;
      }
    //si le pion est bloque et ne peut sauter -> deplacement impossible
     if(bloque){
      printf("Un pion bloque le deplacement \n");
      return FALSE;
     }
     //si le pion n'est pas bloque -> deplacement possible
     else return TRUE;

    }
  }
 }
printf("Deplacement impossible");
 return FALSE;
}



//deplace le pion de la case de depart vers la case d'arrivee 
void deplacement_pion(char plateau[][TAILLE], char caseDep[2], char caseArr[2]){
  //int lArr=(int)caseArr[0]-65;
  //int cArr=(int)caseArr[1]-49;
  //int lDep=(int)caseDep[0]-65;
  //int cDep=(int)caseDep[1]-49;

//deplaçage du pion vers la case d'arrivee
  plateau[(int)caseArr[0]-65][(int)caseArr[1]-49]=plateau[(int)caseDep[0]-65][(int)caseDep[1]-49];

//case initiale desormais vide
  plateau[(int)caseDep[0]-65][(int)caseDep[1]-49]='.';
}





//demande au joueur son déplacement
//stock les coordonnées dans des vecteurs
void demande_coord(char caseDep[], char caseArr[]){
  printf("Entrez les coordonnees de la case sous la forme caseDepart,caseArrivee\n");

  scanf(" %c%c,%c%c", &caseDep[0], &caseDep[1],&caseArr[0],&caseArr[1]);
  }


//vide les buffers pour eviter les problèmes
//liés au scanf
void viderBuffer(void)
{
  int c;
  while((c=getchar()) != EOF && c != '\n');
 
}


//gere la capture des pions lors des déplacement
//une capture ne s'effectue uniquement après un déplacement
//donc seul la case d'arrivee est une donnee necessaire
void capture_pion(char plateau[][TAILLE], char caseArr[2], int *nbBlancs, int* nbNoirs){
  int lArr=(int)caseArr[0]-65;
  int cArr=(int)caseArr[1]-49;
  char pion = plateau[lArr][cArr];
 
  int indParcours;
  int pionCaptures=0;

  //captures horizontales
    //à droite
  indParcours=cArr+1;
  while(plateau[lArr][indParcours]!=pion && plateau[lArr][indParcours]!='.' && indParcours<8){
    indParcours++;
  }
  //verification que le pions est encadre
  if(plateau[lArr][indParcours]==pion){
    
    //modification du nombres de pions restants et mettre les cases vides
    while(indParcours>cArr+1){
      plateau[lArr][indParcours-1]='.';
      indParcours--;
      pionCaptures++;
    }
  }

    //à gauche
  indParcours=cArr-1;
  while(plateau[lArr][indParcours]!=pion && plateau[lArr][indParcours]!='.' && indParcours>0){
    indParcours--;
  }
  //verification que le pions est encadre
  if(plateau[lArr][indParcours]==pion){
    
    //modification du nombres de pions restants et mettre les cases vides
    while(indParcours<cArr-1){
      plateau[lArr][indParcours+1]='.';
      indParcours++;
      pionCaptures++;
    }
  }

  //captures verticales
    //en bas
  indParcours=lArr+1;
  while(plateau[indParcours][cArr]!=pion && plateau[indParcours][cArr]!='.' && indParcours<8){
    indParcours++;
  }
  //verification que le pions est encadre
  if(plateau[indParcours][cArr]==pion){
    
    //modification du nombres de pions restants et mettre les cases vides
    while(indParcours>lArr+1){
      plateau[indParcours-1][cArr]='.';
      indParcours--;
      pionCaptures++;
    }
  }

    //en haut
  indParcours=lArr-1;
  while(plateau[indParcours][cArr]!=pion && plateau[indParcours][cArr]!='.' && indParcours>0){
    indParcours--;
  }
  //verification que le pions est encadre
  if(plateau[indParcours][cArr]==pion){
    
    //modification du nombres de pions restants et mettre les cases vides
    while(indParcours<lArr-1){
      plateau[indParcours+1][cArr]='.';
      indParcours++;
      pionCaptures++;
    }
  }
  if(pion=='B'){
    *nbNoirs=*nbNoirs-pionCaptures;
  }
  else{
    *nbBlancs=*nbBlancs-pionCaptures;
  }

}


/*---------------main--------------------*/

int main(){
 //creation du plateau de jeu
 char plateau[TAILLE][TAILLE];

 //initialisation des pièces sur le plateau:
 initialisation_plateau(plateau);

 //initialisation du nombre de pièces de chaque joueur :
 int nbBlancs=18;
 int nbNoirs=18;

 //debut de la partie
 int player=1;
 
affichage_plateau(plateau);

//creation des coordonnees
char caseDep[2];
char caseArr[2];


//la partie s'arrete quand un des joueurs n'a plus que 5pièces (ou moins)
while(nbBlancs >5 && nbNoirs>5){
  affichage_joueur(player);

  //demande du déplacement tant que celui ci n'est pas valide
  demande_coord(caseDep, caseArr);
  viderBuffer();
  while(!deplacement_possible(plateau,player,caseDep,caseArr)){
    demande_coord(caseDep,caseArr);
    viderBuffer();
  }
  
  //deplacement et capture
  deplacement_pion(plateau,caseDep,caseArr);
  capture_pion(plateau,caseArr,&nbBlancs,&nbNoirs);
 //affichage du plateau apres deplacement
  affichage_plateau(plateau);
  //affichage des scores
  printf("Le nombe de pions noirs restants est %d \n", nbNoirs);
  printf("Le nombe de pions blancs restants est %d \n", nbBlancs);
  
  
  changement_joueur(&player);
}

  //affichage du gagnant
if(nbNoirs<=5){
  printf("Les blancs gagnent la partie\n");
}
else{
  printf("Les noirs gagnent la partie \n");
}

  return 0;
}
