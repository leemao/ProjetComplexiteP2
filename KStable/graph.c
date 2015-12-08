#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

int main(int argc, char *argv[]){
	if(argc<=2){
		fprintf(stderr,"Erreur : %s prend un nom de fonction et de fichier de graphe en argument.\n",argv[0]);
		return 1;
	}

	graphe_l gl;
	char * nfichier = argv[2];
	init_graphe(&gl);
    if(!lecture(nfichier,&gl)){
    	fprintf(stderr,"Le fichier n'existe pas ou ne peut pas être ouvert en lecture!\n");
    	return 1;
    }
    ens_de_sommets e;
    init_ens_de_sommets_bool(&e,gl.n);

    if(strcmp(argv[1],"verification")==0){
        lecture_ens(&e,argv[3]);
        if(verification_l_bool(gl,e))
            printf("L'ensemble est sous-graphe desert\n");
        else
            printf("L'ensemble n'est pas sous-graphe desert\n");
    }else if(strcmp(argv[1],"maximalite")==0){
        lecture_ens(&e,argv[3]);
        if(maximal_bool(gl,e))
            printf("Maximal !\n");
        else
            printf("Pas Maximal !\n");
        printf("\n");
    }else if(strcmp(argv[1],"maximal")==0){
        if(argc==3){
            print_ensemble(calcul_maximal_bool(gl));
        }else{
            printf("Nombre d'argument incorrect pour la fonction maximal.\n");
        }
    }else if(strcmp(argv[1],"maximum_exacte")==0){
        if(argc==3){
            print_ensemble(maximum_complete(gl));
        }else{
            printf("Nombre d'argument incorrect pour la fonction maximum exacte.\n");
        }
    }else if(strcmp(argv[1],"maximum_incomplete")==0){
        if(argc==3){
            print_ensemble(maximimum_incomplete_l(gl));
        }else{
            printf("Nombre d'argument incorrect pour la fonction maximum incomplete.\n");
        }
    }else if(strcmp(argv[1],"k_stable")==0){
        if(argc==4){
            if(kStable(gl,atoi(argv[3]))){
                printf("Il existe un ensemble stable de taille %d ou plus.",atoi(argv[3]));
            }else{
                printf("Il n'existe pas un ensemble stable de taille %d ou plus.",atoi(argv[3]));
            }
        }else{
            printf("Nombre d'argument incorrect pour la fonction K stable.\n");
        }
    }else{
        printf("Vous vous etes trompe dans le nom de la fonction.\n");
				printf("Fonctions : \n");
				printf("verification\n");
				printf("maximalite\n");
				printf("maximal\n");
				printf("maximum_exacte\n");
				printf("maximum_incomplete\n");
				printf("k_stable\n");
    }
    return 0;
}
