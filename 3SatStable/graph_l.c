#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

/**
 * Initialisation du graphe g.
 * @param g Graphe non-orienté
 * @author Julian HURST
 * @complexite O(n) correspondant au nombre d'arrêtes
 */
void init_graphe(graphe_l *g)
{
	sommet i;
	g->n = 0;
	for(i=0; i<n_max; i++)
	{
		g->a[i] = NULL;
	}
}

/**
 * Initialisation du graphe g.
 * @param g Graphe non-orienté
 * @param n Nombre de sommets
 * @author Julian HURST
 * @complexite O(n) correspondant au nombre d'arrêtes
 */
void init_graphe_n(graphe_l *g,int n){
	sommet i;
	g->n = n;
	for(i=0; i<n; i++)
	{
		g->a[i] = NULL;
	}
}

/**
 * Remplit le graphe g en fonction des données du fichier f.
 * @param f nom du fichier
 * @param g Graphe non-orienté
 * @author Tristan NARI
 * @complexite O(n^2)
 */
int lecture(char * f,graphe_l * g)
{
    FILE* fichier = NULL;
    init_graphe(g);
    int n, m, i, a, b;
    char chemin[100];
    strcpy(chemin, "Benchs/");
    strcat(chemin,f);
    fichier = fopen(chemin, "r");

    if (fichier != NULL)
    {
        fscanf(fichier, "%d %d", &n, &m);
		g->n = n;
		for(i=0; i<m; i++)
		{
			fscanf(fichier, "%d %d", &a, &b);
			ajouter_arc(a, b, g);
		}
		fclose(fichier);
        return 1;
    }
    else return 0;
}

/**
 * Ajoute un arc au graphe
 * @param x sommet (entier)
 * @param y sommet (entier)
 * @param g Graphe non-orienté
 * @author Tristan NARI
 * @complexite O(n)
 */
void ajouter_arc(sommet x,sommet y,graphe_l *g)
{
	liste p = (liste)malloc(sizeof(Couple));
	liste q = (liste)malloc(sizeof(Couple));
	if(x >= g->n) ajouter_sommet(g);
	if(y >= g->n) ajouter_sommet(g);
	p->st = y;
	q->st = x;
	p->suivant = g->a[x];
	q->suivant = g->a[y];
	g->a[x] = p;
	g->a[y] = q;
}

void ajouter_arc_noadd(sommet x,sommet y,graphe_l *g){
	liste p = (liste)malloc(sizeof(Couple));
	liste q = (liste)malloc(sizeof(Couple));
	p->st = y;
	q->st = x;
	p->suivant = g->a[x];
	q->suivant = g->a[y];
	g->a[x] = p;
	g->a[y] = q;
}

/**
 * Ajoute un sommet au graphe
 * @param g Graphe non-orienté
 * @author Tristan NARI
 * @complexite O(1)
 */
void ajouter_sommet(graphe_l * g)
{
	g->n = g->n + 1;
}

/**
 * Affiche le nombre de sommets et les arrêtes
 * @param G Graphe non-orienté
 * @author Julian HURST
 * @complexite O(n) correspondant au nombre d'arrêtes
 */
void printgraph_l(graphe_l G){
	liste p;
	printf("Il y a %d sommets\n",G.n);
	printf("Aretes :\n");
	for(int i=0;i<G.n;i++){
		p=G.a[i];
		while(p!=NULL){
			if(p->st>i)
				printf("%d %d\n",i,p->st);
			p=p->suivant;
		}
	}
}

/**
 * Test d'existence d'une arête pour graphe liste
 * @param G Graphe non-orienté
 * @param x sommet (entier)
 * @param y sommet (entier)
 * @return entier renvoi 1 si est sous-graphe désert sinon 0.
 * @author Julian HURST
 * @complexite O(n)
 */
int arete_l(graphe_l g,sommet x,sommet y){
	liste p;
	p=g.a[x];
	while((p!=NULL) && (p->st!=y))
		p=p->suivant;
	if(p==NULL)
		return 0;
	else
		return 1;
}

/**
 * Vérifie si e est un sous-graphe désert de G version bool
 * @param G Graphe non-orienté
 * @param e ensemble de sommets
 * @return entier echap, renvoi 1 si est sous-graphe désert sinon 0.
 * @author Julian HURST
 * @complexite O(n^2)
 */
int verification_l_bool(graphe_l G,ens_de_sommets e){
	int i,j=0,echap=0;
	for(i=0;i<e.n && !echap;i++)
		for(j=i;j<e.n && !echap;j++)
			if((e.som[i] && e.som[j]) && arete_l(G,i,j))
				echap=1;
	return !echap;
}

/**
 * Maximalité, vérifie si un ensemble est maximal
 * @param G Graphe non-orienté
 * @param e ensemble de sommets
 * @return entier ok, renvoi 1 si est maximal sinon 0.
 * @author Ibrahim OMAR
 * @complexite O(n^3)
 */
int maximal_bool(graphe_l g,ens_de_sommets e)
{
    int x=0;
    int ok=1;
    if(verification_l_bool(g,e))
    {
        do
        {
            if(!e.som[x])
            {
                e.som[x]=1;
                ok=!verification_l_bool(g,e);
                e.som[x]=0;
            }
            x=x+1;
        }while((x<g.n) && ok);
    }
    else
        ok=0;
    return ok;
}

/**
 * Calcul un ensemble maximal du graphe en partant du premier sommet.
 * @param G Graphe non-orienté
 * @return L'ensemble maximal calculé
 * @author Clément AKRICHE
 * @complexite O(n^3)
 */
ens_de_sommets calcul_maximal_bool(graphe_l G){
    int i=0;
    ens_de_sommets e;
    init_ens_de_sommets_bool(&e,G.n);
    do{
        e.som[i]=1;
        if(!verification_l_bool(G,e))
            e.som[i]=0;
        i++;
    }while(i<G.n);
    return e;
}

/**
 * Lance la fonction récursive du calcul d'un ensemble sous-graphe désert maximum.
 * @param G Graphe non-orienté
 * @return Ensemble maximum calculé
 * @author Kevin GARABEDIAN
 * @complexite O(2^n)
 */
ens_de_sommets maximum_complete(graphe_l G){
	ens_de_sommets e;
	init_ens_de_sommets_bool(&e,G.n);
	return maximum_complete_rec(G,e,0,0);
}

/**
 * Fonction récursive du calcul d'un ensemble sous-graphe désert maximum.
 * @param G Graphe non-orienté
 * @param e ensemble de sommets manipulé
 * @param card cardinalité courante de e
 * @param bestCard meilleure cardinalité trouvé
 * @return Ensemble maximum calculé
 * @author Kevin GARABEDIAN
 * @complexite O(2^n)
 */
ens_de_sommets maximum_complete_rec(graphe_l G,ens_de_sommets e, int card, int bestCard){
	int i=0;
	ens_de_sommets emax;
	init_ens_de_sommets_bool(&emax,G.n);
    ens_de_sommets tmp;
	init_ens_de_sommets_bool(&tmp,G.n);

	for(i=0;i<G.n;i++){
		if(e.som[i]!=1){
			e.som[i]=1;
			if(verification_l_bool(G,e)){
				card++;
				if(card>bestCard){
                    bestCard=card;
                    copie_ens(e,&emax,G.n);
				}
				copie_ens(maximum_complete_rec(G,e,card,bestCard),&tmp,G.n);
				int ctmp=count_ens(tmp);
				if(ctmp>bestCard){
                    bestCard=ctmp;
                    copie_ens(tmp,&emax,G.n);
				}
				card--;
			}
			e.som[i]=0;
		}
	}
	return emax;
}

/**
 * Calcul de manière incomplète un sous graphe desert maximum.
 * @param G Graphe non-orienté
 * @return L'ensemble maximum calculé
 * @author Tristan NARI
 * @complexite O(n^4)
 */
ens_de_sommets maximimum_incomplete_l(graphe_l G){
    int Kmax=0;
    int Ktmp=0;
    ens_de_sommets e;
    init_ens_de_sommets_bool(&e,G.n);
    ens_de_sommets emax;
    init_ens_de_sommets_bool(&emax,G.n);
    int i,j;
    //parcours du nombre de nombre
    for(i=0;i<G.n;i++){
        creation_maximum(G,&e,i);
        //calcul du nombre de sommets
        for(j=0;j<G.n;j++){
            if(e.som[j]==1)
                Ktmp++;
        }
        //enregistre le meilleur ensemble
        if(Ktmp>Kmax){
            Kmax = Ktmp;
            copie_ens(e,&emax,G.n);
        }
        //met à 0 pour le prochain passage dans la boucle
        init_ens_de_sommets_bool(&e,G.n);
        Ktmp=0;
    }
    //printf("%K maximal trouve : d\n",Kmax);
    return emax;
}

/**
 * Calcul d'un sommet maximal à partir du sommet i.
 * @param G Graphe non-orienté
 * @param e ensemble de sommets
 * @param i entier correspondant au sommet sélectionné
 * @author Tristan NARI
 * @complexite O(n^3)
 */
void creation_maximum(graphe_l G,ens_de_sommets *e, int i){
    int j;
    e->som[i]=1;
    for(j = 0;j<G.n;j++){
        if(j!=i){
            e->som[j]=1;
            if(!verification_l_bool(G,*e))
                e->som[j]=0;
        }
    }
}

void printgraph_l_SAT_tofile(graphe_l G,char *filename,int nbnodes){
  FILE *Stable=fopen(filename,"w");
	liste p;
  if(Stable){
	  fprintf(Stable,"Il y a %d sommets\n",nbnodes);
	  fprintf(Stable,"Aretes :\n");
	  for(int i=0;i<G.n;i++){
		  p=G.a[i];
		  while(p!=NULL){
        if(p->st>i)
			     fprintf(Stable,"%d %d\n",i,p->st);
			  p=p->suivant;
		 }
	  }
  }
  else
    fprintf(stderr,"Erreur lors de la lecture du fichier !");
}

void printgraph_l_SAT(graphe_l G,int nbnodes){
	liste p;
	printf("Il y a %d sommets\n",nbnodes);
	printf("Aretes :\n");
	for(int i=0;i<G.n;i++){
	  p=G.a[i];
	  while(p!=NULL){
      if(p->st>i)
		     printf("%d %d\n",i,p->st);
		  p=p->suivant;
	  }
  }
}
