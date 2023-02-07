#ifndef PLATEAU_H
#define PLATEAU_H
#include<Case.h>
#include <iostream>
#include <time.h>
#include<string>
using namespace std;


class plateau
{
    protected:
    Case ** matrice;
    int lignes;         //nombre des lignes
    int colonnes;       //nombre des colonnes
    int n_m;           // nombre des mines

    public:
        plateau(int a=0, int b=0, int n=0):lignes(a),colonnes(b),n_m(n)
        {

            //definition du matrice
            matrice = new Case*[lignes];
            for (int i=0; i < lignes; i++)
            {
                matrice[i] = new Case[colonnes];
            }

            //remplissage du matrice
            for (int i=0; i < lignes; i++)
                for (int j=0; j < colonnes; j++)
                {
                    {
                        Case c;
                        matrice[i][j]=c;
                    }
                }

                //choix aléatoire des cases contenants des mines
                int i=0;
                while(i<n_m)
                    {
                        srand( time( 0 ) );
                        int x= (rand() % lignes) ;
                        int y= (rand() % colonnes) ;
                        if (matrice[x][y].get_contenuR() != "M")
                        {
                            matrice[x][y].set_contenuR("M");
                            i++;
                        }

                    }
            }


         ~plateau()
        {
            delete [] matrice;
        }

        // affichage du plateau
        void afficher() const
        {
            for(int i=0; i<=(5* colonnes );i++)
            {
                cout<<'*';
            }
            cout<<"\n"<<"*";
            for(int k=0; k<(5* colonnes -1);k++)
            {
                cout<<" ";
            }
            cout<<"*";

            for (int j=0;j<=lignes;j++)
            {
                cout<<"\n";
                cout<<"*";

                for(int i=0;i<(colonnes );i++)
                {
                    cout<<" ";

                }
                if (j==0)                {
                    cout<<"   ";

                }
                else
                {
                    cout<<j<<"  ";
                }
                for(int i=0;i<colonnes;i++)
                {
                    if (j==0)
                    {
                        cout<<i+1<<" ";

                    }
                    else
                    {
                        cout<<matrice[j-1][i].get_contenuV()<<" ";

                    }
                }
                for(int k=0; k<(2* colonnes -4);k++)
                {

                    cout<<" ";
                }
                cout<<"*";
            }
            cout<<"\n"<<"*";
            for(int k=0; k<(5* colonnes -1);k++)
            {
                cout<<" ";
            }
            cout<<"*";
            cout<<"\n"<<"*";
            for(int k=0; k<(5* colonnes -1);k++)
            {
                cout<<" ";
            }
            cout<<"*";
            cout<<"\n";


            for(int i=0; i<=(5* colonnes );i++)
            {
                cout<<'*';
            }
            cout<<"\n";
        }

        //decouvrir une case choisie
        void Decouvrir(int x1, int y1)
        {

            if (( matrice[x1][y1].get_signale()== false)&&(matrice[x1][y1].get_couverte() == true)) // la matrice marquee ne peut pas etre signale ou deja decouverte

            {

                matrice[x1][y1].set_couverte(false);
                if (matrice[x1][y1].get_contenuR()=="M")
                {

                    matrice[x1][y1].set_contenuV(matrice[x1][y1].get_contenuR());

                }
                else // Matrice[x1][y1].get_contenuR()=="x"
                {

                    if (nb_vm(x1,y1)==0)
                    {
                        string ch=matrice[x1][y1].get_contenuR();

                        matrice[x1][y1].set_contenuV(ch);
                        int a= x1-1;
                        int b=y1-1;
                        int c=x1+1;
                        int d=y1+1;
                        if(x1>0) {Decouvrir(a, y1); }
                        if((x1>0) && (y1>0)) {Decouvrir(a, b);}
                        if(y1>0) {Decouvrir( x1, b);}
                        if(y1>0 && x1<(lignes-1)) {Decouvrir(c, b);}
                        if(c<lignes) {Decouvrir(c, y1);}
                        if((x1<(lignes-1)) && (y1<(colonnes-1))) {Decouvrir(c, d);}
                        if(y1<(colonnes-1)) {Decouvrir(x1, d);}

                        if((x1>0) && (y1<(colonnes-1))) {Decouvrir(a, d);}
                    }
                    else
                    {

                        matrice[x1][y1].set_contenuV(to_string(nb_vm(x1,y1)));

                    }
                }
            }
        }

        // calculer le nombre des voisins contenats une mine
        int nb_vm(int x , int y) const
        {
            int a,b;
            int n=0;
            for (int i=0; i <= 2;i++)
                    {
                        for (int j=0;j<=2;j++)
                        {
                            if (!((i== 1) &&(j==1)))
                            {
                                a= x+i-1;
                                b= y+j-1;

                                 if ((a>=0)&&(b>=0))
                                     if((a<lignes)&&(b<colonnes))

                                         {
                                             if(matrice[a][b].get_contenuR()=="M")
                                                n++;
                                         }

                            }

                        }
                    }

            return(n);
        }


        //Marquer une case choisie
        void Marquer(int x,int y, int* n)
        {

            if (matrice[x][y].get_couverte()==true)
            {
                if (matrice[x][y].get_signale())
                {
                    matrice[x][y].set_contenuV("#");
                    matrice[x][y].set_signale(false);
                    (*n)++;

                }
                else
                    if (*n>=1)
                {
                    matrice[x][y].set_contenuV("D");
                    matrice[x][y].set_signale(true);
                    (*n)--;

                }
            }

        }
        //verifier si toute les cases sont découvertes
        bool decouverte()
        {
            for (int i=0; i< lignes;i++)
                {
                    for(int j=0; j<colonnes;j++)
                    {
                        if (matrice[i][j].get_contenuV() =="#")
                            return(false);

                    }
                }
            return(true);


        }
        // contenu virtuelle de la case
        string type_case(int x,int y)
            {
                return(matrice[x][y].get_contenuV());
            }



};
#endif



