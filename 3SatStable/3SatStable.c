#include <stdio.h>
#include <stdlib.h>

/**
* copy_fic copie un fichier et rajoute en tête du fichier sortant le nombre de sommets du graphe et le nombre d'arêtes
* @param input : nom du fichier à copier
* @param output : nom du fichier sortant
* @param nbnodes : nombre de sommets du graphe
* @author Julian Hurst
*/
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

/**
* toStable lit les clauses du fichier 3SAT et écrit le graphe résultant dans un fichier temporaire.
* @param filename : nom du fichier à lire
* @param output : nom du fichier de sortie
* @return : nombre de sommets du graphe trouvé
* @author Julian HURST
* @complexite O(n^3)
*/
int toStable(char *filename,const char *output){
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
    sommets=malloc(sizeof(int *)*clauses+1);
    for(int i=0;i<=clauses;i++)
      sommets[i]=malloc(sizeof(int)*(variables*2)+1);
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
  nbnodes=toStable(filename,"temp");
  copy_fic("temp","STABLE",nbnodes);
}
