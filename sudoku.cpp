#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "sudoku.h"

using namespace std;

Cellule::Cellule()
{
    this->m_listeNum.resize(9,true);
    this->m_valeur=0;
    this->m_taille=9;
}

Cellule::Cellule(int num)
{
    //vector<bool> vec(9,false);
    this->m_listeNum.resize(9,false);
    this->m_valeur=num;
    this->m_taille=1;
    this->m_listeNum[num-1]=true;
}

bool Cellule::setOff(int num) //enleve num; si taille =1, appeler setValeur. Si possibles =0 return false
{
    if (this->m_listeNum[num-1])
    {
        this->m_listeNum[num-1]=false;
        this->m_carte->m_modifie=true;
        --(this->m_taille);
        if(this->m_taille == 0) return false;
        if (this->m_taille==1)
            for(int i(0); i<9; ++i)
                if(this->m_listeNum[i]==true)
                {
                    this->m_carte->setValeur(this->m_x,this->m_y,i+1); //appelle aussi cellule.setValeur
                    break;
                }
    }
//    cout<<num;
    return true;
}

bool Cellule::setValeur(int num)
{
    //cout<<num;
    if (num==0)
        cout<<this->m_x<<","<<this->m_y<<";"<<num<<endl;
    if ((this->m_valeur!=0) && (this->m_valeur != num))
        return false;//si ça change
    if (this->m_taille > 1){
        this->m_carte->m_modifie = true;
        //cout<<*this->m_carte;
    }
    for(int i(0); i<9; ++i)
        this->m_listeNum[i]=false;
    this->m_listeNum[num-1]=true;
    this->m_taille=1;
    this->m_valeur =num;
    return true;
}


Ligne::Ligne()
{
    ;
}

Colonne::Colonne()
{
    ;
}

Carre::Carre()
{
    ;
}

Ligne::Ligne(int j, Carte* carte)  // cree la ligne
{
    this->m_carte=carte;
    this->m_cellules.resize(9,NULL);

    for(int i(0); i<9; ++i)
        this->m_cellules[i]=& (carte->m_liste_cellules[i][j]);
    this->m_y=j;

//    vector<vector<Cellule*>> vec2(9,vector<Cellule*>(0));
    this->m_liste_num.resize(9,vector<Cellule*>()); //remplit le tableau

   // cout<<"allocation ligne"<<endl;
    for(int i(0); i<9; ++i)
        for(int num(0); num<9; ++num)
            if (this->m_cellules[i]->m_listeNum[num]==true)
                this->m_liste_num[num].push_back(this->m_cellules[i]);
}

bool Ligne::setOff(int x,int val)
{
    for(int i(0); i<this->m_liste_num[val-1].size(); ++i)
        if (this->m_liste_num[val-1][i]->m_x==x)
        {
            this->m_liste_num[val-1].erase(this->m_liste_num[val-1].begin()+i);
            if (m_liste_num[val-1].size()==1)
                if (!(this->m_carte->setValeur(this->m_liste_num[val-1][0]->m_x,this->m_y,val)))
                    return false;
            if (this->m_liste_num[val-1].size()==0)
                return false;
            break;
        }
    return true;
}

bool Ligne::setValeur(int x,int val)
{
    for(int i(0); i<9; ++i)
        if(x!=i)
        {
            if (!(this->m_cellules[i]->setOff(val)))
                return false;
            if (!(this->m_carte->m_liste_colonnes[i].setOff(this->m_y,val)))
                return false;
            if (!(this->m_carte->m_liste_carres[i/3 +3*(this->m_y/3)].setOff(i%3+(this->m_y%3)*3,val)))
                return false;;
        }
    this->m_liste_num[val-1].erase(this->m_liste_num[val-1].begin(),this->m_liste_num[val-1].end());
    this->m_liste_num[val-1].push_back(&(this->m_carte->m_liste_cellules[x][this->m_y]));
    return true;
}


Colonne::Colonne(int i, Carte* carte)
{
    this->m_carte=carte;
    this->m_cellules.resize(9,NULL);

    for(int j(0); j<9; ++j)
        this->m_cellules[j]=& (this->m_carte->m_liste_cellules[i][j]);
    this->m_x=i;

//    vector<vector<Cellule*>> vec2(9,vector<Cellule*>(0));
    this->m_liste_num.resize(9,vector<Cellule*>());

    for(int j(0); j<9; ++j)
        for(int num(0); num<9; ++num)
            if (this->m_cellules[j]->m_listeNum[num]==true)
                this->m_liste_num[num].push_back(this->m_cellules[j]);
}

bool Colonne::setOff(int y,int val)
{
    for(int j(0); j<this->m_liste_num[val-1].size(); ++j)
        if (this->m_liste_num[val-1][j]->m_y==y)
        {
            this->m_liste_num[val-1].erase(this->m_liste_num[val-1].begin()+j);
            if (this->m_liste_num[val-1].size()==1)
                if (!(this->m_carte->setValeur(this->m_x,this->m_liste_num[val-1][0]->m_y,val)))
                    return false;
            if (this->m_liste_num[val-1].size()==0)
                return false;
            break;
        }
    return true;
}

bool Colonne::setValeur(int y,int val)
{
    for(int j(0); j<9; ++j)
        if(y!=j)
        {
            if (!(this->m_cellules[j]->setOff(val)))
                return false;
            if (!(this->m_carte->m_liste_lignes[j].setOff(this->m_x,val)))
                return false;
            if (!(this->m_carte->m_liste_carres[this->m_x/3+3*(j/3)].setOff((this->m_x%3)+(j%3)*3,val)))
                return false;
        }
    this->m_liste_num[val-1].erase(this->m_liste_num[val-1].begin(),this->m_liste_num[val-1].end());
    this->m_liste_num[val-1].push_back(&(this->m_carte->m_liste_cellules[this->m_x][y]));
    return true;
}


//  m_c=(m_x/3)+3*(m_y/3);
//  m_c%3 == i : abscisse
//  m_c/3 == j : ordonnée

Carre::Carre(int c,Carte* carte)
{
    this->m_carte= carte;
    this->m_c =c;
    int m_i=this->m_c%3;
    int m_j=this->m_c/3;

//    vector<Cellule*> vec(9,NULL);
    this->m_cellules.resize(9,NULL);

    for(int i(0); i<3; ++i)
        for(int j(0); j<3; ++j)
            this->m_cellules[i+3*j] = & (this->m_carte->m_liste_cellules[3*m_i+i][3*m_j+j]);

    this->m_liste_num.resize(9,vector<Cellule*>(0));

    for(int i(0); i<3; ++i)
        for(int j(0); j<3; ++j)
            for(int num(0); num<9; ++num)
                if (this->m_cellules[i+3*j]->m_listeNum[num]==true)
                    this->m_liste_num[num].push_back(this->m_cellules[i+3*j]);

}

bool Carre::setOff(int k,int val)
{
    for(int j(0); j<this->m_liste_num[val-1].size(); ++j)
        if (((this->m_liste_num[val-1][j]->m_x % 3) + 3 * (this->m_liste_num[val-1][j]->m_y%3))==k)
        {
            this->m_liste_num[val-1].erase(this->m_liste_num[val-1].begin()+j);
            if (this->m_liste_num[val-1].size()==1)//
                if (!(m_carte->setValeur(this->m_liste_num[val-1][0]->m_x,this->m_liste_num[val-1][0]->m_y,val)))
                    return false;
            if (this->m_liste_num[val-1].size()==0)
                return false;
            break;
        }

    return true;
}

bool Carre::setValeur(int k,int val)
{
    for(int j(0); j<9; ++j)
        if(k!=j)
        {
            if (!(this->m_cellules[j]->setOff(val)))
                return false;
            if (!(this->m_carte->m_liste_lignes[(j/3) + 3* (this->m_c/3)].setOff(j%3+(this->m_c%3) *3,val)))
                return false;
            if (!(this->m_carte->m_liste_colonnes[j%3+(this->m_c%3) *3].setOff((j/3) + 3* (this->m_c/3),val)))
                return false;
        }
    this->m_liste_num[val-1].erase(this->m_liste_num[val-1].begin(),this->m_liste_num[val-1].end());
    this->m_liste_num[val-1].push_back(&(this->m_carte->m_liste_cellules[(k%3) + 3*(this->m_c % 3)][(k/3) + 3*(this->m_c/3)]));
    return true;
}

Carte::Carte(string adresse)
{
    this->m_liste_cellules.resize(9,vector<Cellule>(9));
    //cout<<"ok"<<endl;
    for(int i(0); i<9; ++i)
        for(int j(0); j<9; ++j)
        {
            //this->m_cellules[i][j];
            this->m_liste_cellules[i][j]=Cellule();
            this->m_liste_cellules[i][j].m_x=i;
            this->m_liste_cellules[i][j].m_y=j;
            this->m_liste_cellules[i][j].m_carte=this;
        }
    //cout<<"allocation tab"<<endl;
    this->m_liste_lignes.resize(9);
    for(int i(0); i<9;++i)
        this->m_liste_lignes[i]=Ligne(i,this);
    cout<<"allocation ligne"<<endl;

    this->m_liste_colonnes.resize(9);
    for(int i(0); i<9;++i)
        this->m_liste_colonnes[i]=Colonne(i,this);

    cout<<"allocation colonne"<<endl;



    this->m_liste_carres.resize(9);
    for(int i(0); i<9;++i)
        this->m_liste_carres[i]=Carre(i,this);

    cout<<"allocation carrés"<<endl;

    /*string s("");
    for (int j(0); j<9; ++j)
    {
        for(int i(0); i<9; ++i)
            s+=std::to_string(m_liste_cellules[i][j].m_listeNum[4]) + ", ";
        s+="\n";
    }
    s+="\n";
    cout<<s<<endl;*/

    ifstream fichier(adresse);
    if (fichier)
        cout<<"fichier ok"<<endl;
    int i(0),j(0);
    char a;
    bool erreur=false;
    do
    {
        fichier.get(a);
        //cout<<a;
        int numero= ((int) a)- 48;
        //cout<<numero<<endl;
        if (numero ==0)
            ++i;
        if ((1<=numero) && (numero<=9))
        {
            if((i>8)||(j>8)){
                cout<<"mauvais fichier"<<endl;
                erreur=true;
                break;
            }
            if (! (this->setValeur(i,j,numero))){
                erreur=true;
                cout<<"erreur"<<endl;
                break;
            }
            ++i;
        }
        if (a=='\n')
        {
            i=0;
            ++j;
            //cout<<"saut"<<endl;
        }
    } while((j<=8));

    fichier.close();

    if (erreur)
    {
        cout<<"erreur !"<<endl;
        cout<<*this;
        return;
    }

    this->m_modifie=true;

    while (this->m_modifie)
    {
        this->m_modifie=false;
        this->calculerSi();
        //this->forcerCalcul();
    }


    cout<<*this;

    return;

}

bool Carte::setOff(int x,int y,int val)
{
    if (!(this->m_liste_cellules[x][y].setOff(val)))
        return false;
    if (!(this->m_liste_lignes[y].setOff(x,val)))
        return false;
    if (!(this->m_liste_colonnes[x].setOff(y,val)))
        return false;
    if (!(this->m_liste_carres[(x/3) + 3* (y/3)].setOff((x%3) + 3*(y%3),val)))
        return false;

    //cout<<val;
    return true;
}

bool Carte::setValeur(int x,int y,int val)
{
    //cout<<x<<","<<y<<endl;
    if (!(this->m_liste_cellules[x][y].setValeur(val)))
        return false;
    if (!(this->m_liste_lignes[y].setValeur(x,val)))
        return false;
    if (!(this->m_liste_colonnes[x].setValeur(y,val)))
        return false;
    if (!(this->m_liste_carres[(x/3) + 3* (y/3)].setValeur((x%3) + 3*(y%3),val)))
        return false;

    //cout<<val;
    //cout<<x<<","<<y<<endl;
    return true;
}

bool Carte::calculerSi()
{
    for(int valeur=1; valeur<10; ++valeur)    //pour chacune des valeurs ...
    {
        for(int c(0); c<9; ++c)                   //on rentre dans le carre,
        {
            int l[3]= {0,0,0}; //    on regarde les trois lignes, si c'est sur une seule...
            for(int i(0); i<3; ++i)
                for(int j(0); j<3; j++)
                    if(this->m_liste_cellules[3*(c%3)+i][3*(c/3)+j].m_listeNum[valeur-1])
                        l[j]=1;
            int nligne;
            if((l[0]+l[1]+l[2] )!= 1)
                goto colonne;
            nligne = l[1]+l[2]*2;
            for(int i(0); i<9; ++i) //on enleve les valeur hors du carré
            {
                if (i/3 == c%3)
                    continue;
                if (this->m_liste_cellules[i][3*(c/3)+nligne].m_listeNum[valeur-1])
                    this->setOff(i,3*(c/3)+nligne,valeur);
            }

colonne:
            int l2[3]= {0,0,0}; //    on regarde les trois colonnes ...
            for(int i(0); i<3; ++i)
                for(int j(0); j<3; j++)
                    if(this->m_liste_cellules[3*(c%3)+i][3*(c/3)+j].m_listeNum[valeur-1])
                        l2[i]=1;
            if((l2[0]+l2[1]+l2[2]) != 1)
                continue;
            int ncolonne = 0 + l2[1] + l2[2]*2;
            for(int j(0); j<9; ++j)
            {
                if (j/3 == c/3)
                    continue;
                if (this->m_liste_cellules[3*(c%3)+ncolonne][j].m_listeNum[valeur-1])
                    this->setOff(3*(c%3)+ncolonne,j,valeur);
            }
        }

        //on rentre dans les lignes ...
        for(int ligne(0); ligne<9; ++ligne) //dans la ligne
        {
            int l[3]= {0,0,0}; //on regarde le carré
            for(int i(0); i<9; ++i)
                if (this->m_liste_cellules[i][ligne].m_listeNum[valeur-1])
                    l[i/3]=1;
            if ((l[0]+l[1]+l[2]) !=1)
                continue;
            int ncarre=0+ l[1]+2*l[2]; //x du carré (0,1,2)
            for(int i(0); i<9; ++i)
            {
                if ( i/3 + (ligne/3)*3 == ligne)
                    continue;
                if (this->m_liste_cellules[ncarre*3 + i%3][i/3 + (ligne/3)*3].m_listeNum[valeur-1])
                    this->setOff(ncarre*3 + i%3,i/3 + (ligne/3)*3,valeur);
            }
        }


        //on rentre dans les colonnes ...
        for(int colonne(0); colonne<9; ++colonne) //la xieme colonne
        {
            int l[3]= {0,0,0};
            for(int j(0); j<9; ++j) //dans la colonne
                if (this->m_liste_cellules[colonne][j].m_listeNum[valeur-1])
                    l[j/3]=1;
            if (l[0]+l[1]+l[2] !=1)
                continue;
            int ncarre=0+ l[1]+2*l[2];
            for(int i(0); i<9; ++i) //on regarde dans le carré, dont x=colonne/3, y=ncarre
            {
                if ( i%3 + (colonne/3)*3 == colonne)
                    continue;
                if (this->m_liste_cellules[i%3 + (colonne/3)*3][ncarre*3 + i/3].m_listeNum[valeur-1])
                    this->setOff(i%3 + (colonne/3)*3,ncarre*3 + i/3,valeur);
            }//fin du carré
        }//fin des colonnes
    }//fin des valeurs
} //fin fonction

/*
void Carte::forcerCalcul()
{

        for(int i(0); i<9; ++i)
            for(int j(0); j<9; ++j)
                if (this->m_liste_cellules[i][j].m_valeur>0)
                    this->setValeur(i,j,this->m_liste_cellules[i][j].m_valeur);
        for(int i(0); i<9; ++i)
            for(int val=1; val<=9; ++val)
                if (this->m_liste_colonnes[i].m_liste_num[val-1].size()==1)
                    this->setValeur(i,this->m_liste_colonnes[i].m_liste_num[val-1][0]->m_y,val);
        for(int j(0); j<9; ++j)
            for(int val=1; val<=9; ++val)
                if (this->m_liste_lignes[j].m_liste_num[val-1].size()==1)
                    this->setValeur(this->m_liste_lignes[j].m_liste_num[val-1][0]->m_x,j,val);
        for(int c(0); c<9; ++c)
            for(int val=1; val<=9; ++val)
                if (this->m_liste_carres[c].m_liste_num[val-1].size()==1)
                    this->setValeur(this->m_liste_carres[c].m_liste_num[val-1][0]->m_x,this->m_liste_carres[c].m_liste_num[val-1][0]->m_y,val);
}*/

string Carte::getString() const
{
    string s("");
    for (int j(0); j<9; ++j)
    {
        for(int i(0); i<9; ++i)
            s+=std::to_string(m_liste_cellules[i][j].m_valeur) + ", ";
        s+="\n";
    }
    s+="\n";
    return s;
}



std::ostream& operator<<( std::ostream &flux, Carte const& carte )
{
    return flux<<carte.getString();
}



