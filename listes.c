#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#ifdef NCURSES
#include <ncurses.h>
#endif
#include "listes.h"

/*
 *  Auteur(s) : HADDAD YANIS
 *  Date :
 *  Suivi des Modifications :
 *
 */
void ajout_en_tete (sequence_t *l,char n)
{
  cellule_t *R;
  R=(cellule_t*) malloc(sizeof(struct cellule));
  R->command=n;
  R->suivant =l->tete;
  l->tete=R;
}
void ajout_en_queue(sequence_t *l, char n) {
  cellule_t *R;
  R=(cellule_t*) malloc(sizeof(struct cellule));
  R->command=n;
  if (l->tete == NULL)
  {
    l->tete=R;
    R->suivant =NULL;
  }
  else
  {
      cellule_t *Q;
      Q=l->tete;
      while (Q->suivant !=NULL)
      {
          Q=Q->suivant;
      }
      Q->suivant=R;
      R->suivant =NULL;
  }
return;
}
void conversion (char *texte, sequence_t *seq)
{
int i;
i=0;
    while (texte[i]!='\0')
	{
	 ajout_en_queue(&(*seq), texte[i]);
         i++;
	}
}





void afficher (sequence_t* seq)
{
    cellule_t *R;
    R=seq->tete;
	while (R!=NULL)
	{
		printf("%c",R->command);
		R=R->suivant;
	}
    
}

cellule_t* nouvelleCellule (void)
{
	cellule_t *nouvelle;
        nouvelle=(cellule_t*)malloc (sizeof(struct cellule));
	return nouvelle;

}


void detruireCellule (cellule_t* cel)
{
    free (cel);
;
}
