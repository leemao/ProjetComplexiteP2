#define n_max 1024

typedef int sommet;

//Liste d'adjacence
typedef struct chainon{
	sommet st;
	struct chainon *suivant;
}Couple;

typedef Couple *liste;

typedef struct {
	liste a[n_max];
	int n;  // nombre de sommets
}graphe_l;

//typedef liste ens_de_sommets;
typedef struct {
	int n;
	sommet som[n_max];
}	ens_de_sommets;
