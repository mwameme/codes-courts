#ifndef HEURE_H_INCLUDED
#define HEURE_H_INCLUDED
#include <string>

class Temps{
    public :
        Temps();
        Temps(int heure, int minute,int seconde);
        Temps(int seconde);
        std::string getString() const;
        int getTotalSecondes() const;
        Temps operator+(Temps const& a) const;
        int getHeure() const;
        int getMinute() const;
        int getSeconde() const;

        bool operator==(Temps const& a) const;

    private :
        int m_heure;
        int m_minute;
        int m_seconde;

        int m_total_seconde;

};

std::ostream& operator<<( std::ostream &flux, Temps const& a );


#endif // HEURE_H_INCLUDED
