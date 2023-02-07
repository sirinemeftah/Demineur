#include <iostream>
#include<plateau.h>
#include<Case.h>
#include <fstream>
#include<string>
#include<vector>
#include<stdio.h>
using namespace std;

int main()
{

    string rep1, rep2;
    int taille_c, taille_l, nb_mines,x,y,x1,y1;
    int compteur_cout ;
    int compteur_mines;
    string ch;


    //accueil
    string rep3 ="Y";
    while (rep3=="Y")
            {
                cout <<"Voulez vous consulter les meilleurs scores ? Y/N"<<endl;
                cin>>rep1;
    //ouvrir le fichier du score
                if (rep1=="Y")
                {
                    string filename("score.txt");
                    vector<string> lines;
                    string line;

                    ifstream input_file(filename);
                    if (!input_file.is_open())
                    {
                        cout << "impossible d'ouvrir le fichier  '"<< filename << "'" << endl;

                    }
                    else
                        {
                            while (getline(input_file, line))
                            {
                                lines.push_back(line);
                            }
                            vector <string>::iterator itr ;
                            for (itr = lines.begin(); itr != lines.end();++itr)
                                { cout<<(*itr)<<endl;}
                        }
                        input_file.close();


                }
    //Passer à la nouvelle partie

                cout<< "*******************************  Bienvenue dans une nouvelle partie  ******************************"<<endl;
                cout<<"Veuillez saisir successivement le nombre des colonnes, le nombre des lignes et le nombre des mines"<<endl;
                cin>>taille_c;
                cin>>taille_l;
                cin>>nb_mines;
                compteur_mines = nb_mines;
                compteur_cout = 0;



    // création du matrice intitiale
                plateau P1(taille_l,taille_c,nb_mines);

                //affichage
                cout<<"Le compteur des mines :"<<compteur_mines<<endl;
                cout<<"Le compteur des coups :"<<compteur_cout<<endl;
                P1.afficher();


              while (!((compteur_mines == 0 ) &&(P1.decouverte()== true)))
                {

                    // decouvrir une case
                    cout<<"Decouvrez une case de votre choix en precisant successivement son numero de ligne et son numero de colonne "<<endl;
                    cin>>x1; // ligne
                    cin>>y1; // colonne
                    (x1)--;
                    (y1)--;
                    P1.Decouvrir(x1, y1);
                    ch= P1.type_case(x1, y1);
                    compteur_cout++;

                    cout<<"Le compteur des mines :"<<compteur_mines<<endl;
                    cout<<"Le compteur des coups :"<<compteur_cout<<endl;
                    P1.afficher();


                    if (ch=="M")
                    {
                        cout<<" Vous avez perdu !!! "<<endl;
                        break;

                    }
                    if (P1.decouverte()== true)
                    {
                        break;
                    }
                    cout<<"Voulez vous Marquer une case de votre choix ? Y/N "<<endl;
                    cin>>rep2;
                    if (rep2=="Y")
                    {
                        cout<<"Marquez une case de votre choix en precisant successivement son numero de ligne et son numero de colonne "<<endl;
                        cin>>x; // ligne
                        cin>>y; // colonne
                        P1.Marquer(x-1,y-1,&compteur_mines);
                        compteur_cout++;
                        cout<<"Le compteur des mines :"<<compteur_mines<<endl;
                        cout<<"Le compteur des coups :"<<compteur_cout<<endl;
                        P1.afficher();

                    }
                }
    // Si vous avez gangé
                if (ch != "M")
                {
                    string nom;
                    cout<<" Vous avez gagné !!! "<<endl;
                    // insert fichier
                    cout<<"Veuillez saisir votre Nom"<<endl;
                    cin>>nom;

                    string filename("score.txt");
                    fstream f;

                    f.open(filename, std::ios_base::app | std::ios_base::in);

                    if (!f.is_open())
                    {
                       cout << "impossible d'ouvrir le fichier  '"<< filename << "'" << endl;
                    }
                    else

                    {
                        f <<"\n"<<nom<<","<<compteur_cout;

                    }
                    f.close();

                }

                cout << "Voulez vous lancer une nouvelle partie"<< endl;
                cin>>rep3;
            }

    return 0;
}
