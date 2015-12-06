#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

int nbnodes(int *nbnodes,int size){
  int nb=0;
  for(int i=1;i<=size;i++){
    if(nbnodes[i])
      nb++;
  }
  return nb;
}

int toStable(char *filename,graphe_l *g){
  FILE *SAT=fopen(filename,"r");
  int variables,clauses,s1,s2,s3,s1neg,s2neg,s3neg;
  int *totsommets;
  s1neg=s2neg=s3neg=0;
  if(SAT){
    while((s1=fgetc(SAT))=='c')
      while((s2=fgetc(SAT))!='\n');
    ungetc(s1,SAT);

    fscanf(SAT, "p cnf %d %d\n",&variables,&clauses);
    totsommets=malloc(sizeof(int)*variables*2+1);
    for(int i=1;i<=variables*2;i++){
      if(i<=variables)
        totsommets[i]=1;
      else
        totsommets[i]=0;
    }
    init_graphe_n(g,variables*2);
    printf("variables propositionnelles : %d\nclauses : %d\n",variables,clauses);
    for(int i=0;i<clauses;i++){
      fscanf(SAT,"%d %d %d 0\n",&s1,&s2,&s3);
      if(s1<0){
        s1neg=abs(s1);
        s1=s1neg+variables;
        ajouter_arc_noadd(s1neg,s1,g);
        if(totsommets[s1]!=1)
          totsommets[s1]++;
      }
      if(s2<0){
        s2neg=abs(s2);
        s2=s2neg+variables;
        ajouter_arc_noadd(s2neg,s2,g);
        if(totsommets[s2]!=1)
          totsommets[s2]++;
      }
      if(s3<0){
        s3neg=abs(s3);
        s3=s3neg+variables;
        ajouter_arc_noadd(s3neg,s3,g);
        if(totsommets[s3]!=1)
          totsommets[s3]++;
      }
      ajouter_arc_noadd(s1,s2,g);
      if(s3!=s1){
        ajouter_arc_noadd(s2,s3,g);
        ajouter_arc_noadd(s3,s1,g);
      }
    }
  }
  else
    fprintf(stderr,"Erreur lors de la lecture du fichier !");
  return nbnodes(totsommets,variables*2);
}

int main(int argc, char *argv[]){
  if(argc != 2){
    fprintf(stderr,"USAGE : %s fichierSAT\n",argv[0]);
	  return 0;
  }
  char* filename = argv[1];
  int nbnodes;
  graphe_l *g;
  g=malloc(sizeof(graphe_l));
  nbnodes=toStable(filename,g);
  printgraph_l_SAT_tofile(*g,"STABLE",nbnodes);
  printgraph_l_SAT(*g,nbnodes);
}
