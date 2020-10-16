#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main()
{
    /* variables */
    long int u;
    float tab [20];
    int i;
    int j;
    int prof;
    int total;
    float ratio;
    float alea;
    float xtemp;
    float fx;
    float ysup;
    float xrand;
    float yrand;
    float res;


    /* instructions */
    time(&u);
    srand(u);

    total = 0;
    ysup=0;

    /* on génère un tableau pour stocker les coefficients du polynome, sa taille est prédéfinie par l'énoncée */
    for (i=0; i<20; i=i+1){
        printf("Entrez le coefficient du x puissance %d : ", i);
        scanf("%f",& tab[i]);
        /* on profite de la boucle if pour calculer la somme des coefficients (en valeur absolue) du polynome, qui sera un majorant du maximum */
        if (tab[i]>=0){
            ysup=ysup+tab[i];
        }
        else{
            ysup=ysup-tab[i];
        }
    }

    /* La somme des coefficients en valeur absolue nous permet de majorer facilement le polynome, étant donné qu'on le considère entre -1 et 1.
    De même, cette valeur prise négativement nous permet une minoration à faible complexité.*/


    printf("Entrez le nombre de points souhaité à générer : ");
    scanf("%d",& prof);

    /* La profondeur correspond simplement au nombre de point à générer.
    Une plus grande profondeur permettra une approximation plus correcte, mais demandera une plus grande puissance de calcul */


    for (i=0; i<prof; i=i+1){

        /* On génère un x aléatoirement. Sachant que le nombre aléatoire est compris entre 0 et 1,
        on le multiplie par 2 (la longueur de l'intervalle) et on soustraie 1 pour le recentrer en 0 */
        alea=(float) rand()/RAND_MAX;
        xrand=(2*alea)-1;

        /* même principe pour générer y, sauf qu'on  multiplie notre nombre aléatoirement pris entre -1 et 1 par ysup,
        le majorant/minorant de notre  polynome */
        alea=(float) rand()/RAND_MAX;
        yrand=((2*alea)-1)*ysup;

        /* On va maintenant calculer f(x) pour le x trouvé aléatoirement, on va donc utiliser une boucle "pour" pour
        parcourir notre tableau de coefficient, tout en augementant la puissance de x */
        fx=tab[0];
        xtemp=xrand;
        for (j=1; j<20; j=j+1){
            fx=fx+(tab[j]*xtemp);
            xtemp=xtemp*xrand;
        }

        /* On regarde maintenant si le point obtenu est au dessus ou en dessous de la courbe. Selon les cas, il participera positivement,
        négativement ou pas du tout au calcul de l'intégrale. */
        if (fx>0 && yrand>0 && yrand<fx){
            total=total+1;
        }

        else if (fx<0 && yrand<0 && yrand>fx){
            total=total-1;
        }
    }

    /* En divisant la somme des valeurs des points par le nombre total de points, on obtient le ratio de l'aire sous la courbe par rapport
    au rectangle repésenté par x=-1, x=1 et les droites constantes valant respectivement le minorant et le majorant. */
    ratio= (float) total/prof;

    /* L'aire du rectangle est 2ysup*2, que l'on multiplie par le ratio pour obtenir le résultat. */
    res=4*ysup*ratio;
    printf("L'intégrale du polynome entre -1 et 1 vaut %f", res);


    return 0;
}
