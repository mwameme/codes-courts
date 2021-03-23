#include <iostream>
#include <string>
#include <ctime> // Obligatoire
#include <cstdlib> // Obligatoire

using namespace std;

int main()
{
    bool recommencer(true);
        srand(time(0));

    while(recommencer){
        string mot;
        cout << "choisissez un mot"<<endl;
        cin>> mot;
        string mot0=mot;
        int taille = mot.size();
        string motMelange;
        for(int i(0); i<taille; ++i)
        {
            int j=(int) (rand() % (taille-i));
            motMelange.push_back(mot[j]);
            mot.erase(j,1);
        }
//        motMelange.push_back(mot[0]);

        string essai;

        do
        {

            cout << motMelange << endl;
            cout << "devinez le mot !"<< endl;

            cin >> essai;

            if(essai==mot0) break;
            else cout<< "non. Essaye encore"<<endl<<endl<<endl;
        }
        while(true);

        cout << "trouvé !"<<endl<< "recommencer ? "<<endl;
        cin>> recommencer;

    }
    return 0;
}
