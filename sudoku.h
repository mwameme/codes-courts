#ifndef SUDOKU_H_INCLUDED
#define SUDOKU_H_INCLUDED

#include <string>
#include <vector>


//on fait setValue depuis la carte :
//on appelle cellule.setValue
//puis on appelle  ligne/colonne/carré.setValue
//quand on a 1 case de trouvée, on appelle setValue depuis la carte !


// on met des bool partout, pour que si cellule.setOff return false, on s'arrête !
//donc les autres fonctions aussi alors retournent false,
//et on livre le message d'erreur !!!

class Carte;

class Cellule{
public :
    int m_x;
    int m_y;
    Carte* m_carte;

    std::vector<bool> m_listeNum; //les 9 possibles
    int m_valeur; //si fixe
    int m_taille; //nombre des possibles

    bool setOff(int num);
    bool setValeur(int num);

    Cellule();
    Cellule(int num);

};

class Ligne{
public:
    int m_y;
    Carte* m_carte;

    std::vector<Cellule*> m_cellules; //la liste des cellules
    std::vector<std::vector<Cellule*>> m_liste_num; //liste, pour chaque numero,
                                            //des cellules qui ont ce possible :
                                            //m_liste_num[num][cellule_i]

    Ligne();
    Ligne(int j,Carte* carte); //prend la ligne (i) depuis la carte;

    bool setOff(int x,int val); //change m_liste_
    bool setValeur(int x,int val);//change m_liste_
};

class Colonne{
public :
    int m_x;
    Carte* m_carte;

    std::vector<Cellule*> m_cellules; //la liste des cellules
    std::vector<std::vector<Cellule*>> m_liste_num; //liste, pour chaque numero,
                                            //des cellules qui ont ce possible :
                                            //m_liste_num[num][cellule_i]
    Colonne();
    Colonne(int i,Carte* carte); //prend la colonne (j) depuis la carte;

    bool setOff(int y,int val); //change m_liste_
    bool setValeur(int y,int val); //change m_liste_
};

class Carre{
public :
    int m_c;
    Carte* m_carte;
//  m_c=(m_x/3)+3*(m_y/3);
//  m_c%3 == i : abscisse
//  m_c/3 == j : ordonnée

    std::vector<Cellule*> m_cellules; //la liste des cellules
    std::vector<std::vector<Cellule*>> m_liste_num; //liste, pour chaque numero,
                                            //des cellules qui ont ce possible :
                                            //m_liste_num[num][cellule_i]
    Carre();
    Carre(int c,Carte* carte); //prend le carre (i,j) depuis la carte;

    bool setOff(int k,int val); //change m_liste_
    bool setValeur(int k,int val); //change m_liste_
};

class Carte{
public :
    bool m_modifie;
    std::vector<std::vector<Cellule>> m_liste_cellules; //les cellules

    std::vector<Ligne> m_liste_lignes; //les lignes
    std::vector<Colonne> m_liste_colonnes; //les colonnes
    std::vector<Carre> m_liste_carres; //les carrés

    bool setOff(int x,int y,int val); //modifie toute la carte ...
    bool setValeur(int x,int y,int val);


    Carte(Carte const& c); //constructeur de copie : recopie les cellules,
                            //et met à jour les pointeurs !!!
    Carte(std::string adresse); //ouvre un fichier, et met la Carte à jour ...
    //~Carte(); //comme les cellules sont détruites, il n'y a rien à y faire ...

    void forcerCalcul(); //fait les non-
    bool calculerSi();

    std::string getString() const;
};

class Test : public Carte{
public:
    int m_x;
    int m_y;
    int m_val;
    //une carte, qui suppose m_val en m_x * m_y. Possible ou non ...
    Test(Carte c);
};

class Essai : public Carte{
public :
    std::vector<Test> m_liste_tests; //les différents essais;
        //this->carte : on modifie si test.possible == false

        //si un essai est faux, modifie la carte ...
    int m_val_x;
    int m_val_y;

    Essai(Carte const& carte); //part d'une carte, et liste les essais à tester
};

class HierarchieTest{
public:
    Carte* m_carte_base;
    std::vector<Essai> m_suite_essais;

    HierarchieTest(Carte const& c);

    iterer(); //fait la suite récurente des essais

};

std::ostream& operator<<( std::ostream &flux, Carte const& carte );




#endif // SUDOKU_H_INCLUDED
