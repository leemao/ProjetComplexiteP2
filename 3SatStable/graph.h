#include "struct.h"

//Fonctions pour le graphe par listes d'adjacence
void init_graphe(graphe_l *g);
void init_graphe_n(graphe_l *g,int n);
int lecture(char * f,graphe_l * g);
void ajouter_arc(sommet x,sommet y, graphe_l *g);
void ajouter_arc_noadd(sommet x,sommet y, graphe_l *g);
void ajouter_sommet(graphe_l * g);
void printgraph_l(graphe_l G);
int arete_l(graphe_l g,sommet x,sommet y);
int verification_l_bool(graphe_l G,ens_de_sommets e);
int maximal_bool(graphe_l g,ens_de_sommets e);
ens_de_sommets calcul_maximal_bool(graphe_l G);
ens_de_sommets maximum_complete(graphe_l G);
ens_de_sommets maximum_complete_rec(graphe_l G,ens_de_sommets e, int card, int bestCard);
ens_de_sommets maximimum_incomplete_l(graphe_l G);
void creation_maximum(graphe_l G,ens_de_sommets * e, int i);
void printgraph_l_SAT_tofile(graphe_l G,char *filename,int nbnodes);
void printgraph_l_SAT(graphe_l G,int nbnodes);

//Fonctions utiles
void init_ens_de_sommets_bool(ens_de_sommets *e,int n);
int contains(ens_de_sommets e,int x);
void print_ensemble(ens_de_sommets e);
void copie_ens(ens_de_sommets e_src,ens_de_sommets *e_dest,int n);
void lecture_ens(ens_de_sommets *e,char liste_e[]);
int count_ens(ens_de_sommets e);
