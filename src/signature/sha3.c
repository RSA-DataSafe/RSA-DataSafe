#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../structure/structure.h"
#include "sha3.h"


message *sha3(message *m, int taille) {

    int b_size = 0;
    switch (taille) {
        case 256 :
            b_size = 1088;
            break;
        case 512 :
            b_size = 576;
            break;
        default :
            fprintf (stderr, "Wrong size input for sha3\n");
            exit(107);
    }

    // on ajoute le padding
    message *res = padding_sha3 (m, b_size);

    // on découpe en blocs
    block *r = decoupage_block (res, b_size);

    // on créé la matrice pour keccak (round)
    mpz_t **matrice = malloc (sizeof (*matrice) * 5);
    for (int i=0; i<5; i++) {
        matrice[i] = malloc (sizeof (mpz_t) * 5);
    }
    for (int i=0; i<5; i++) {
        for (int j=0; j<5; j++) {
            mpz_init (matrice[i][j]);
        }
    }

    // Pour chaque bloc, on xor un bloc avec la matrice puis on la traite (round, keccak-f)
    int cnt = 0;
    while (cnt<r->nb_block) {
        for (int i=0; i<9; i++) {
            mpz_t tmp;
            mpz_init (tmp);
            for (int j=0; j<64; j++) {
                mpz_add_ui (tmp, tmp, mpz_tstbit (r->tab[cnt], ((i+1)*(j+1))%b_size) * pow (2, j));
            }
            mpz_xor (matrice[i%5][i%2], matrice[i%5][i%2], tmp);
            mpz_clear (tmp);
        }
        round_sha3 (matrice, 24);
        cnt++;
    }

    // on met le résultat final dans res
    mpz_t output;
    mpz_init (output);
    for (int i=0; i<5; i++) {
        for (int j=0; j<5; j++) {
            mpz_mul_2exp (output, output, 64);
            mpz_add (output, output, matrice[i][j]);
            printf("i = %d, j = %d\n", i, j);
        }
    }
    mpz_set (res->nombre, output);

    // on génère la sortie
    mpz_set_ui (res->taille, taille);                       // on fixe la taille de la sortie
    mpz_t cut, nbr;
    mpz_inits (cut, nbr, NULL);
    mpz_set_ui (nbr, mpz_sizeinbase (res->nombre, 2));
    mpz_sub_ui (cut, nbr, taille);                          // cut = la taille de la partie "en trop"
    int tmp = mpz_get_ui (cut);
    mpz_tdiv_q_2exp (res->nombre, res->nombre, tmp);        // on 'tronque' la sortie
    // on libère la mémoire
    for (int i=0; i<5; i++) {
        for (int j=0; j<5; j++) {
            mpz_clear (matrice[i][j]);
        }
    }

    mpz_clears (cut, nbr, output, NULL);
    free (r);
    for (int i=0; i<5; i++) {
        free (matrice[i]);
    }
    free (matrice);
    
    return res;
};

message *padding_sha3(message *m, int taille) {
    message *res = malloc (sizeof (message));
    mpz_init_set (res->nombre, m->nombre);
    mpz_init_set (res->taille, m->taille);              // res = m
    mpz_t pad, tmp;
    mpz_init_set_ui (tmp, 1);
    mpz_init_set (pad, res->taille);                    // pad = taille du message
    mpz_mod_ui (pad, pad, taille);                      // pad = taille du padding à ajouter
    mpz_mul_2exp (res->nombre, res->nombre, mpz_get_ui (pad));       // message agrandit de pad ( padding : 0*)
    mpz_ui_pow_ui (tmp, 2, mpz_get_ui (pad));           // tmp = un 1 suivi de 0s jusqu'à la bonne taille de padding
    mpz_add_ui (tmp, tmp, 1);                           // on ajoute 1 à tmp (padding : 10*1)
    mpz_add (res->nombre, res->nombre, tmp);            // on ajoute tmp à res

    mpz_clears (pad, tmp);
    return res;
};

block *decoupage_block(message* m, int taille) {
    block *res = malloc (sizeof (res));                 // on réserve de l'espace mémoire pour res
    res->tab = malloc (sizeof (mpz_t));                 // on réserve de l'espace mémoire pour res
    int j,cnt = 0;                                      // cnt comptera le nombre de blocs, j sert d'indice au parcours du bloc en cours
    int m_size = mpz_get_ui (m->taille);                // on récupère la taille de m
    for (int i=0; i+j<m_size; cnt++) {                  // tant que la lecture de m n'est pas terminée, i sert à marquer l'endroit du début d'un bloc sur m
        res->tab = realloc (res->tab, sizeof (res) * cnt+1); // on réserve une nouvelle "case mémoire" pour le nouveau bloc à ajouter
        mpz_init (res->tab[cnt]);                       // on initialise ce nouveau bloc à 0
        for (j=0; j<taille; j++) {                      // on parcours sur m le bloc en cours
            int tmp = mpz_tstbit (m->nombre, i+j);      // on récupère la valeur du bit à l'endroit où on se trouve
            mpz_add_ui (res->tab[cnt], res->tab[cnt], pow (2*tmp, j));       // on ajoute le bit lu dans le bloc courant
        }
        i+=j;                                           // on met le "curseur" sur m à l'endroit qui correspond à la fin du bloc qu'on vient d'ajouter
    }
    res->nb_block = cnt;                                // on stocke le nombre de blocs
    return res;
};

void round_sha3(mpz_t **matrice,int nb_tour) {

    // set RC constants
    mpz_t RC[24];
    mpz_init_set_str (RC[0], "0x0000000000000001", 0);
    mpz_init_set_str (RC[1], "0x0000000000008082", 0);
    mpz_init_set_str (RC[2], "0x800000000000808A", 0);
    mpz_init_set_str (RC[3], "0x8000000080008000", 0);
    mpz_init_set_str (RC[4], "0x000000000000808B", 0);
    mpz_init_set_str (RC[5], "0x0000000080000001", 0);
    mpz_init_set_str (RC[6], "0x8000000080008081", 0);
    mpz_init_set_str (RC[7], "0x8000000000008009", 0);
    mpz_init_set_str (RC[8], "0x000000000000008A", 0);
    mpz_init_set_str (RC[9], "0x0000000000000088", 0);
    mpz_init_set_str (RC[10],"0x0000000080008009", 0);
    mpz_init_set_str (RC[11],"0x000000008000000A", 0);
    mpz_init_set_str (RC[12],"0x000000008000808B", 0);
    mpz_init_set_str (RC[13],"0x800000000000008B", 0);
    mpz_init_set_str (RC[14],"0x8000000000008089", 0);
    mpz_init_set_str (RC[15],"0x8000000000008003", 0);
    mpz_init_set_str (RC[16],"0x8000000000008002", 0);
    mpz_init_set_str (RC[17],"0x8000000000000080", 0);
    mpz_init_set_str (RC[18],"0x000000000000800A", 0);
    mpz_init_set_str (RC[19],"0x800000008000000A", 0);
    mpz_init_set_str (RC[20],"0x8000000080008081", 0);
    mpz_init_set_str (RC[21],"0x8000000000008080", 0);
    mpz_init_set_str (RC[22],"0x0000000080000001", 0);
    mpz_init_set_str (RC[23],"0x8000000080008008", 0);

    // round
    for (int i=0; i<nb_tour; i++) {
        keccak_f (matrice, RC[i]);
    }
};

void keccak_f(mpz_t **matrice, mpz_t RC) {

    //init tmp variables
    mpz_t tmp[5][5], tmp2[5][5], A[5], B[5], C[5];
    for (int i = 0; i<5; i++) {
        mpz_init (A[i]);
        mpz_init (B[i]);
        mpz_init (C[i]);
        for (int j = 0; j<5; j++) {
            mpz_init (tmp[i][j]);
            mpz_init (tmp2[i][j]);
        }
    }

    //init r constant
    int r[5][5] = {
        {0,36,3,41,18},     //r[0]
        {1,44,10,45,2},     //r[1]
        {62,6,43,15,61},    //r[2]
        {28,55,25,21,56},   //r[3]
        {27,20,39,8,14}     //r[4]
    };
	
    //teta step
    for (int i = 0; i<5; i++) {
        for (int j = 0; j<5; j++) {
            mpz_xor (A[i], A[i], matrice[i][j]);
        }
    }
    for (int i = 0; i<5; i++) {
        mpz_set (C[i], A[i]);
        rot (C[i], 1);
        mpz_xor (B[i], A[(i+1)%5], C[(i+1)%5]);
    }
    for (int i = 0; i<5; i++) {
        for (int j = 0; j<5; j++) {
            mpz_xor (matrice[i][j], matrice[i][j], B[i]);
        }
    }

    //rho step
    for (int i = 0; i<5; i++) {
        for (int j = 0; j<5; j++) {
            mpz_set (tmp[i][j], matrice[i][j]);
            rot (tmp[i][j], r[i][j]);
        }
    }

    //pi step
    for (int i = 0; i<5; i++) {
        for (int j = 0; j<5; j++) {
            mpz_set (matrice[j][(2*i+3*j)%5], tmp[i][j]);
        }
    }

    //chi step
    for (int i = 0; i<5; i++) {
        for (int j = 0; j<5; j++) {
            mpz_set (tmp[i][j], matrice[i][j]);
            invert (tmp[i][j]);
        }
    }
    for (int i = 0; i<5; i++) {
        for (int j = 0; j<5; j++) {
            mpz_and (tmp2[i][j], tmp[(i+1)%5][j], matrice[(i+2)%5][j]);
        }
    }
    for (int i = 0; i<5; i++) {
        for (int j = 0; j<5; j++) {
            mpz_xor (matrice[i][j], matrice[i][j], tmp2[i][j]);
        }
    }


    //iota step
    mpz_add (matrice[0][0], matrice[0][0], RC);

    //free tmp variables
    for (int i = 0; i<5; i++) {
        mpz_clear (A[i]);
        mpz_clear (B[i]);
        mpz_clear (C[i]);
        for (int j = 0; j<5; j++) {
            mpz_clear (tmp[i][j]);
            mpz_clear (tmp2[i][j]);
        }
    }
};

void rot (mpz_t x, int n) {
    int size = mpz_sizeinbase (x, 2);                   // size = taille de x
    int tmp[64];                                        // tmp permet de stocker chaque bit à l'indice correspondant
    for (int i=0; i<64; i++) tmp[i] = 0;                // init tmp à 0
    for (int i=0; i<size; i++)                          // on remplit tmp avec x, au bon endroit
        tmp[64-i-1] = mpz_tstbit (x, i);
    char *str = malloc (sizeof (char) * 64);
    for (int i=0; i<64; i++) {                          // on transforme tmp en chaîne de caractères, en effectuant la rotation
        str[i] =  tmp[(i+n)%64] + '0';                  
    }
    mpz_set_str (x, str, 2);                            // on remplace x par sa nouvelle valeur
    free (str);
};

void invert (mpz_t x) {
    int size = mpz_sizeinbase (x, 2);                   // size = taille de x
    int tmp[64];                                        // tmp permet de stocker chaque bit à l'indice correspondant
    for (int i=0; i<64; i++) tmp[i] = 1;                // init tmp à 1
    for (int i=0; i<size; i++)                          // on remplit tmp avec l'inverse de x
        tmp[64-i-1] = (mpz_tstbit (x, i)+1)%2;
    char *str = malloc (sizeof (char) * 64);
    for (int i=0; i<64; i++) {                          // on transforme tmp en chaîne de caractères
        str[i] =  tmp[i] + '0';                  
    }
    mpz_set_str (x, str, 2);                            // on remplace x par sa nouvelle valeur
    free (str);
};
