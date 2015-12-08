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
    init_graphe_n(g,(variables*2)*clauses);
    printf("variables propositionnelles : %d\nclauses : %d\n",variables,clauses);
    for(int i=0;i<clauses;i++){
      fscanf(SAT,"%d %d %d 0\n",&s1,&s2,&s3);
      if(s1<0){
        s1neg=abs(s1);
        s1=s1neg+variables;
        //ajouter_arc_noadd(s1neg,s1,g);
        if(totsommets[s1]!=1)
          totsommets[s1]++;
      }
      if(s2<0){
        s2neg=abs(s2);
        s2=s2neg+variables;
        //ajouter_arc_noadd(s2neg,s2,g);
        if(totsommets[s2]!=1)
          totsommets[s2]++;
      }
      if(s3<0){
        s3neg=abs(s3);
        s3=s3neg+variables; //n°clause
        //ajouter_arc_noadd(s3neg,s3,g);
        if(totsommets[s3]!=1)
          totsommets[s3]++;
      }
      s1+=i*(variables*2);
      s2+=i*(variables*2);
      s3+=i*(variables*2);
      if(s1neg!=0)
        ajouter_arc_noadd(s1neg,s1,g);
      if(s2neg!=0)
        ajouter_arc_noadd(s2neg,s2,g);
      if(s3neg!=0)
        ajouter_arc_noadd(s3neg,s3,g);
      ajouter_arc_noadd(s1,s2,g);
      if(s3!=s1){
        ajouter_arc_noadd(s2,s3,g);
        ajouter_arc_noadd(s3,s1,g);
      }
      s1neg=s2neg=s3neg=0;
    }
  }
  else
    fprintf(stderr,"Erreur lors de la lecture du fichier !");
  return nbnodes(totsommets,variables*2);
}

void copy_fic(const char *input,const char *output,int nbnodes){
  int aretes=0,ch;
  FILE *in=fopen(input,"r");
  FILE *out=fopen(output,"w");
  if(in && out){
    while(!feof(in)){
      ch = fgetc(in);
      if(ch == '\n'){
        aretes++;
      }
    }
    rewind(in);
    fprintf(out,"%d %d\n",nbnodes,aretes);
    while(!feof(in)){
      ch = fgetc(in);
      fputc(ch,out);
    }
  }
  else
    fprintf(stderr,"Erreur lors de l'écriture du fichier STABLE");
  fclose(in);
  fclose(out);
}


int toStable2(char *filename,const char *output){
  FILE *SAT=fopen(filename,"r");
  FILE *STABLE=fopen(output,"w");
  int variables,clauses,s1,s2,s3,s1neg,s2neg,s3neg;
  int **sommets;
  s1neg=s2neg=s3neg=0;
  if(SAT && STABLE){
    while((s1=fgetc(SAT))=='c')
      while((s2=fgetc(SAT))!='\n');
    ungetc(s1,SAT);

    fscanf(SAT, "p cnf %d %d\n",&variables,&clauses);
    sommets=malloc(sizeof(int *)*clauses);
    for(int i=0;i<=clauses;i++)
      sommets[i]=malloc(sizeof(int)*(variables*2));
    for(int i=0;i<=clauses;i++)
      for(int j=0;j<=variables*2;j++)
        sommets[i][j]=0;
    printf("variables propositionnelles : %d\nclauses : %d\n",variables,clauses);
    for(int i=0;i<clauses;i++){
      //fprintf(STABLE,"clause : %d\n",i);
      fscanf(SAT,"%d %d %d 0\n",&s1,&s2,&s3);
      if(s1<0){
        s1neg=abs(s1);
        s1=s1neg+variables;
        sommets[i][s1]=1;
        for(int j=0;j<i;j++)
          if(sommets[j][s1neg])
            fprintf(STABLE,"%d %d\n",(j*variables*2)+s1neg,s1+(i*variables*2));
      }
      else {
        for(int j=0;j<i;j++)
          if(sommets[j][s1+variables])
            fprintf(STABLE,"%d %d\n",(j*variables*2)+(s1+variables),s1+(i*variables*2));
      }
      if(s2<0){
        s2neg=abs(s2);
        s2=s2neg+variables;
        sommets[i][s2]=1;
        for(int j=0;j<i;j++)
          if(sommets[j][s2neg])
            fprintf(STABLE,"%d %d\n",(j*variables*2)+s2neg,s2+(i*variables*2));
      }
      else {
        for(int j=0;j<i;j++)
          if(sommets[j][s2+variables])
            fprintf(STABLE,"%d %d\n",(j*variables*2)+(s2+variables),s2+(i*variables*2));
      }
      if(s3<0){
        s3neg=abs(s3);
        s3=s3neg+variables;
        sommets[i][s3]=1;
        for(int j=0;j<i;j++)
          if(sommets[j][s3neg])
            fprintf(STABLE,"%d %d\n",(j*variables*2)+s3neg,s3+(i*variables*2));
      }
      else {
        for(int j=0;j<i;j++)
          if(sommets[j][s3+variables])
            fprintf(STABLE,"%d %d\n",(j*variables*2)+(s3+variables),s3+(i*variables*2));
      }
      sommets[i][s1]=1;
      sommets[i][s2]=1;
      fprintf(STABLE,"%d %d\n",s1+(i*variables*2),s2+(i*variables*2));
      if(s3!=s1){
        sommets[i][s3]=1;
        fprintf(STABLE,"%d %d\n",s2+(i*variables*2),s3+(i*variables*2));
        fprintf(STABLE,"%d %d\n",s3+(i*variables*2),s1+(i*variables*2));
      }
    }
    fclose(SAT);
    fclose(STABLE);
  }
  else
    fprintf(stderr,"Erreur lors de la lecture du fichier !");
  int som=0;
  for(int i=0;i<=clauses;i++)
    for(int j=0;j<=variables*2;j++)
      if(sommets[i][j])
        som++;
  return som;
}

int main(int argc, char *argv[]){
  if(argc != 2){
    fprintf(stderr,"USAGE : %s fichierSAT\n",argv[0]);
	  return 0;
  }
  char* filename = argv[1];
  int nbnodes;
  //graphe_l *g;
  //g=malloc(sizeof(graphe_l));
  nbnodes=toStable2(filename,"temp");
  copy_fic("temp","STABLE",nbnodes);
  //printgraph_l_SAT_tofile(*g,"STABLE",nbnodes);
  //printgraph_l_SAT(*g,nbnodes);
}
