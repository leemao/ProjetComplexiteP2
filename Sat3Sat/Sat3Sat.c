#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_MAX 1000 // Tableau de taille 1000

/**
 * Traitement d'une clause
 * @param fichierSAT fichier SAT
 * @param chaine servant à la lecture
 * @param litteraux est le nombre de litteraux
 * @param clauses est le nombre de clauses
 * @author Tristan NARI
 * @complexite O(n) n correspondant au nombre de fois que la chaine a été décomposé
 */
void traite_clause(FILE* fichierSAT,char * chaine,int * litteraux,int * clauses){
    FILE* fichierTemp = NULL;
    fichierTemp = fopen("temp", "a");

    fgets(chaine,TAILLE_MAX,fichierSAT);
    int lit=0;
    int tab_tmp[TAILLE_MAX] = {0};

    if(fichierTemp != NULL){
        for (char *p = strtok(chaine," "); p != NULL; p = strtok(NULL, " ")){
            if(atoi(p)!=0){
                tab_tmp[lit]=atoi(p);
                lit=lit+1;
            }else{
                //printf("lit=%d\n",lit);
                /* Cas 1: Clause de taille 1 */
                if(lit==1){
                    fprintf(fichierTemp,"%d %d %d 0\n",tab_tmp[0],*litteraux+1,*litteraux+2);
                    fprintf(fichierTemp,"%d %d %d 0\n",tab_tmp[0],*litteraux+1,-(*litteraux+2));
                    fprintf(fichierTemp,"%d %d %d 0\n",tab_tmp[0],-(*litteraux+1),*litteraux+2);
                    fprintf(fichierTemp,"%d %d %d 0\n",tab_tmp[0],-(*litteraux+1),-(*litteraux+2));
                    *litteraux=(*litteraux)+2;
                    *clauses=(*clauses)+4;
                }
                /* Cas 2: Clause de taille 2 */
                if(lit==2){
                    fprintf(fichierTemp,"%d %d %d 0\n",tab_tmp[0],tab_tmp[1],*litteraux+1);
                    fprintf(fichierTemp,"%d %d %d 0\n",tab_tmp[0],tab_tmp[1],-(*litteraux+1));
                    *litteraux=(*litteraux)+1;
                    *clauses=(*clauses)+2;
                }
                /* Cas 3: Clause de taille 3 */
                if(lit==3){
                    fprintf(fichierTemp,"%d %d %d 0\n",tab_tmp[0],tab_tmp[1],tab_tmp[2]);
                    *clauses=(*clauses)+1;
                }
                /* Cas 4: Clause de taille 4 et plus */
                if(lit>=4){
                    int i=1;
                    fprintf(fichierTemp,"%d %d %d 0\n",tab_tmp[0],tab_tmp[1],*litteraux+i);
                    lit=lit-2;

                    while(lit != 2){
                        fprintf (fichierTemp, "%d %d %d 0\n", -(*litteraux+i), tab_tmp[i+1], (*litteraux+i+1));
                        i = i + 1;
                        lit = lit - 1;
                    }
                    fprintf (fichierTemp, "%d %d %d 0\n", -(*litteraux+i), tab_tmp[i+1], tab_tmp[i+2]);

                    *clauses = *clauses + i + 1;
                    *litteraux = *litteraux + i;
                }
                lit=0;
            }
        }
    }

    fclose(fichierTemp);
}

/**
 * transformation sat en 3SAT(sans la ligne p cnf)
 * @param filename
 * @param litteraux est le nombre de litteraux
 * @param clauses est le nombre de clauses
 * @author Tristan NARI
 * @complexite O(c*n)
 *  c est le nombre de clauses dans le fichier SAT de départ
 *  n correspondant au nombre de fois que la chaine a été décomposé
 */
void sat_3sat(char* filename,int * litteraux, int * clauses){
    FILE* fichierSAT = NULL;
    FILE* fichier3SAT = NULL;

    fichierSAT = fopen(filename, "r");

    if(fichierSAT != NULL){
        char chaine[TAILLE_MAX] = "";

        /* Recherche de la ligne contenant "p cnf" afin de commencer la lecture des clauses. */
        while(!feof(fichierSAT)){
            fgets(chaine,TAILLE_MAX,fichierSAT);
            /* NB: strncmp donne 0 si str1 = str2 */
            if(strncmp(chaine,"c",1)){
                if(!(strncmp(chaine,"p cnf ",6))){
                    /* Ligne correspondant "p cnf" */
                    char * str=strtok(chaine," ");
                    int i = 0;
                    while( str != NULL ){
                        if(i == 2){
                            *litteraux=atoi(str);
                        }
                        str=strtok(NULL," ");
                        i++;
                    }
                }else{
                    traite_clause(fichierSAT,chaine,litteraux,clauses);
                }
            }
        }
    }else{
        printf("Erreur fichier de lecture !\n");
    }

    fclose(fichierSAT);
}

int main(int argc, char *argv[])
{
    if(argc != 2){
        printf("Il faut le nom du fichier graphe.\n");
        return 0;
    }
    char* filename = argv[1];
    int litteraux = 0;
    int clauses = 0;
    int caractereActuel = 0;


    sat_3sat(filename,&litteraux,&clauses);

    FILE* fichierTemp = NULL;
    FILE* fichier3SATFin = NULL;
    fichierTemp = fopen("temp", "r");
    fichier3SATFin = fopen("3SAT.cnf", "w");

    fprintf(fichier3SATFin,"p cnf %d %d\n",litteraux,clauses);
    fseek(fichierTemp,0,SEEK_SET);
    // O(n) n représentant le nombre de caractère dans le fichier temporaire "temp"
    if(fichierTemp != NULL && fichier3SATFin != NULL){
        while((caractereActuel = fgetc(fichierTemp)) != EOF)
        {
            fprintf(fichier3SATFin, "%c",caractereActuel);
        }
    }

    fclose(fichierTemp);
    fclose(fichier3SATFin);
    remove("temp");
    return 1;
}
