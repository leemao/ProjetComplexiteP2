#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if(argc != 3){
		printf("Il faut le nom du fichier graphe ainsi qu'une valeur k!\n");
		return 0;
	}

    char* filename = argv[1];
    int k = atoi(argv[2]);
    int sommets = 0, arretes = 0;
    int i, j, l, x, y, clauses = 0, lit=1;
    int caractereActuel = 0;

    FILE* fichierStable = NULL;
    FILE* fichierSAT = NULL;
    FILE* fichierTemp = NULL;
    /* fichierStable est le graphe desert(stable) qui est lue. */
    fichierStable = fopen(filename, "r");

    char* filenameSAT=filename;
    strcat(filenameSAT,".cnf");
    /* fichierSAT est le fichier de sortie, celui que l'on va écrire, qui représente le SAT */
    fichierSAT = fopen(filenameSAT, "w");
    fichierTemp = fopen("temp", "w");

    if(fichierStable != NULL){
        fscanf(fichierStable,"%d %d",&sommets,&arretes);
    }else{
        printf("Erreur fichier de lecture !\n");
    }

    if (fichierSAT != NULL && fichierStable != NULL && fichierTemp != NULL)
    {
        /* Ecriture de la première ligne du document*/
        fprintf(fichierSAT, "p cnf %d ", k*sommets);

        /* Ecriture des clauses identifiant tout les littéraux */
        /* De complexité k*sommets est donc du type O(n*m) */
        for(j = 0; j<k; j++){
            for(i = 0; i<sommets; i++){
                if(i==0){
                    fprintf(fichierTemp, "%d", lit);
                }else{
                    fprintf(fichierTemp, " %d", lit);
                }
                lit++;
            }
            fprintf(fichierTemp, " 0\n");
            clauses++;
        }

        /* Ecriture de l'ensemble des clauses possible entre sommets du même ensemble k */
        /* De complexité k*sommets² est donc du type O(k*sommets²) */
        for(l=0; l<k; l++){
            for(j = 1+(l*sommets); j<=sommets+(l*sommets); j++){
                for(i = j+1; i<=sommets+(l*sommets); i++){
                    fprintf(fichierTemp, "-%d -%d 0\n", j, i);
                    clauses++;
                }
            }
        }

        /* Ecriture de l'ensemble des clauses possible entre k de même sommet */
        /* De complexité sommets*k² est donc du type O(sommets*k²) */
        for(l=0; l<sommets; l++){
            for(j = 1+l; j<=sommets*k; j=j+sommets){
                for(i = j+sommets; i<=sommets*k; i=i+sommets){
                    fprintf(fichierTemp, "-%d -%d 0\n", j, i);
                    clauses++;
                }
            }
        }

        /* Ecriture de l'ensemble des clauses des arretes */
        /* De complexité arretes*k² est donc du type O(arretes*k²) */
        for(i=0; i<arretes; i++){
            fscanf(fichierStable,"%d %d",&x,&y);
            for(j=x+1; j<(k*sommets)+1; j=j+sommets){
                for(l=y+1; l<(k*sommets)+1; l=l+sommets){
                    if((j-1)/sommets != (l-1)/sommets){
                        fprintf(fichierTemp, "-%d -%d 0\n", j, l);
                        clauses++;
                    }
                }
            }
        }

        fprintf(fichierSAT, "%d\n", clauses);
        fclose(fichierTemp);
        fichierTemp = fopen("temp", "r");

        /* Copie du fichierTemp dans fichierSAT */
        while((caractereActuel = fgetc(fichierTemp)) != EOF)
        {
            fprintf(fichierSAT, "%c",caractereActuel);
        }
    }else{
        printf("Erreur fichier d'écriture !\n");
    }
    fclose(fichierTemp);
    fclose(fichierStable);
    fclose(fichierSAT);
    remove("temp");
    return 1;
}
