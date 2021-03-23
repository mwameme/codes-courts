#include <iostream>
#include <string>
#include <ctime> // Obligatoire
#include <cstdlib> // Obligatoire

using namespace std;

int main()
{
    srand(time(0));
    string motMystere,motVisible;
    int nombreEssai(8);
    cin >> motMystere;

    motVisible=motMystere;
    for(int i(1); i < motMystere.size()-1; ++i)
        motVisible[i]=' ';

    bool gagne=false;
    while (nombreEssai>0 && !gagne)
    {
        char essai;
        cin>> essai;
        bool trouve(false);
        for(int i(0); i<motMystere.size(); i++)
        {

            if (motMystere[i]==essai)
            {
                motVisible[i]=motMystere[i];
                trouve=true;
            }
        }
        if (!trouve) --nombreEssai;
        cout <<motVisible<<endl;
        if (motVisible==motMystere) gagne=true;

    }
    if (gagne) cout << "VICTOIRE !!! "<<nombreEssai<<endl;
    return nombreEssai;
}
