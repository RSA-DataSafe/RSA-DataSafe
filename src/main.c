#include <gmp.h>
#include <stdio.h>
#include "structure/structure.h"
#include "gestion_fichier/lecture.h"

int main(void) {
    int a = chercher_utilisateur("user2@email.com", "mdp2");
		printf("%d",a);    
		return 0;
}
