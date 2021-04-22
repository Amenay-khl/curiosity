#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#ifdef NCURSES
#include <ncurses.h>
#endif
#include "listes.h"
#include "curiosity.h"

// declaration du type element qui va constitué les elements de la pile
typedef struct {
                    int entier;
                    cellule_t *pointeur;
               } element;



//declaration de la pile
typedef struct {
                    int taille;
                    element tab[3];
               }pile;

// fonctions de gestion de pile
void initpile (pile *p)
{
    p->taille=0;
}
void empiler (pile *p,element e)
{
    p->taille++;
    p->tab[p->taille-1]=e;
}
element depiler (pile *p)
{
    element e=p->tab[p->taille-1];
    p->taille--;
    return e;
}

int n=0;
/*
 *  Auteur(s) : HADDAD Yanis
 *  Date :
 *  Suivi des Modifications :
 *
 */

void stop (void)
{
#ifdef NCURSES
    getch();  /* attente appui sur touche */
#else
    char enter = '\0';
    printf ("Appuyer sur entrée pour continuer...\n");
    while (enter != '\r' && enter != '\n') { enter = getchar(); }
#endif
}



int interprete (sequence_t* seq, bool debug)
{
    // Version temporaire a remplacer par 
    //  - une lecture des commandes dans la liste chainee
    // suivie par
    //  - une interpretation des commandes lues (partie fournie)

    char commande = 0;
    int cpt=0;
    pile p;
    //char bv[1000]=""; //var act3
    //char bf[1000]=""; //var act 3
    //debug = true; /* À enlever par la suite et utiliser "-d" sur la ligne de commandes */

    printf ("Programme X:");
    afficher(seq);
    printf ("\n");
    if (debug) stop();
    // À partir d'ici, beaucoup de choses à modifier dans la suite.
    cellule_t *R;
    R=seq->tete;
    //commande = R->command; //à modifier: premiere commande de la sequence
    while (R!=NULL) {
        //commande=R->command;
		commande=R->command;
        if ((commande=='a')||(commande=='A')) {
            switch (avance()) {
                case VICTOIRE:
		seq->tete=NULL;
		 return VICTOIRE;
                case RATE: return RATE;
                case REUSSI: break;
            }
        } else if ((commande=='g')||(commande=='G')) {
            gauche();
        } else if ((commande=='d')||(commande=='D')) {
            droite();
        }else if ((commande=='0')  ||(commande=='1')  || (commande=='2') || (commande=='3') || (commande=='4') || (commande=='5')|| (commande=='6')|| (commande=='7')|| (commande=='8') ) 
		{ 
			
			n=atoi(&commande);
                }
	 else if ((commande=='M') || (commande=='m'))
		{
			n=mesure(n);
		}
         else if ((commande=='P') || (commande=='p'))
		{
			pose(n);
		}
         else if (commande=='{')
		{
			initpile (&p);
			cpt++;
			element res_commande;
			res_commande.entier=n;
			res_commande.pointeur=NULL;
			empiler (&p,res_commande);
			R=R->suivant;
			sequence_t bv;
			bv.tete=NULL;
			while (cpt!=0)
				{
					if (R->command=='{') cpt++;
					if (R->command=='}') cpt--;
					if (cpt !=0) ajout_en_queue(&bv, R->command);
					R=R->suivant;
				}
			element elt_bv;
			elt_bv.entier=-1;
			elt_bv.pointeur=bv.tete;
			empiler (&p,elt_bv);
			
			while (R->command!='{' && R->command <'0' && R->command >'9')
			{
			R=R->suivant;
			}
			sequence_t bf;
			bf.tete=NULL;
			cpt++;
			R=R->suivant;
			while (cpt!=0)
				{
					if (R->command=='{') cpt++;
					if (R->command=='}') cpt--;
					if (cpt !=0) ajout_en_queue(&bf, R->command);
					R=R->suivant;
				}
			element elt_bf;
			elt_bf.entier=-1;
			elt_bf.pointeur=bf.tete;
			empiler (&p,elt_bf);
			
		}
	 else if (commande=='?')
		{
			sequence_t S1,S2;
			S1.tete=NULL;
			S2.tete=NULL;
			element SS1,SS2,SS3;
			SS1=depiler(&p);
			SS2=depiler(&p);
			SS3=depiler(&p);
			S1.tete=SS1.pointeur;
			S2.tete=SS2.pointeur;
			if (SS3.entier==0) interprete (&S1,debug);
			else interprete (&S2,debug);
			
		}
	 //act 3 est passé en commentaire
	 /*else if (commande=='{')
		{
			R=R->suivant;
			commande=R->command;
			int i=0;
			while (commande !='}')
				{
					bv[i]=commande;
					i++;
					R=R->suivant;
					commande=R->command;
				}
			bv[i+1]='\0';
			while (R->command!='{')
			{
			R=R->suivant;
			}
			R=R->suivant;
			commande=R->command; 
			i=0;
			while (commande !='}')
				{
					bf[i]=commande;
					i++;
					R=R->suivant;
					commande=R->command;
				}
			bf[i+1]='\0';
			printf("voilà la chaine bf1:%s\n",bf);
			printf("voilà la chaine bv1:%s\n",bv);
		} //fin act3
	  else if (commande=='?') // deb 2eme fct act 3
		{
			if (n==0) {
					sequence_t S1;
					S1.tete=NULL;
					printf("voilà la chaine bf2:%s\n",bf);
					conversion (bf, &S1);
					interprete (&S1,debug);
					
				  }
			else
			          {
					sequence_t S2;
					S2.tete=NULL;
					printf("voilà la chaine bv2:%s\n",bv);
					conversion (bv, &S2);
					interprete (&S2,debug);

			    	  }
			
		}*/ //fin 2eme partie act3 */
          else {
            printf ("Commande inconnue: %c\n", commande);
        }
	
        // a modifier :
	R=R->suivant;
       //commande suivante dans la sequence

        afficherCarte();
        printf ("Programme X:");

        afficher(seq);
        printf ("\n");
        if (debug) stop();
    }

    /* Si on sort de la boucle sans arriver sur le @
     * c'est raté :-( */
    
    return CIBLERATEE;
}
