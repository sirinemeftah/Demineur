#ifndef CASE_H
#define CASE_H
#include<string>
#include <iostream>
#include<plateau.h>
using namespace std;

class Case
{
    protected:

        bool couverte;     // true si la case est couverte
        bool signale;     // true si la case est marquée
        string contenu_reel; // case contient une mine M ou sans mine X
        string contenu_visuel; // affichage du case découverte (M ou X ou numéro) ou non découverte (# ) ou marquée (D)

    public:


        Case()
        {
            couverte = true;
            signale = false;

            contenu_visuel ="#";
            contenu_reel ="X";

        }

        string get_contenuR() const
        {
            return(contenu_reel);
        }
        void set_contenuR(string ch)
        {
            contenu_reel= ch ;
        }

        string get_contenuV() const
        {
            return(contenu_visuel);
        }
        void set_contenuV(string ch)
        {
            contenu_visuel= ch ;
        }
        bool get_signale() const
        {
            return signale;
        }
        void set_signale(bool a)
        {
            signale=a;
        }
        bool get_couverte() const
        {
            return couverte;
        }
        bool set_couverte(bool a)
        {
            couverte=a;
        }


         ~Case() {}

};

#endif // CASE_H

