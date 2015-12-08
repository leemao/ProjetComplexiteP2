# Graph
Projet de Calculabilité du Master 1 Informatique de St Jerôme

Consigne:
-Premier argument correspond à la fonction utilisé
	verification <nomFichier> <ensemble_E>
	maximalite <nomFichier> <ensemble_E>
	maximal <nomFichier>
	maximum_exacte <nomFichier>
	maximum_incomplete <nomFichier>
	k_stable <nomFichier> <K>
	
-Deuxième argument correspond au nom du fichier du graphe non-orienté.
Les fichiers des graphes doivent se situer dans le dossier "Benchs" qui est à la racine.
	
-Troisième argument 
Pour verification et maximalite
	sous le format x,x,x...
	x correspond au numéro du sommet à 1.
	Chaqu'un séparé par une virgule.

Pour k_stable le 3ème argument correspond à la taille min du stable

Exemple d'utilisation:
	verification test2 2,4,5
	maximalite test2 0,2,4
	maximum_incomplete test2
	k_stable test 3