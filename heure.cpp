#include <string>
#include <iostream>
#include "heure.h"


using namespace std;



Temps::Temps() : m_heure(0), m_minute(0),m_seconde(0),m_total_seconde(0)
{

}

Temps::Temps(int heure, int minute,int seconde){
    int secondes=heure*3600+minute*60+seconde;

    m_total_seconde=secondes;

    m_seconde=secondes%60;
    secondes=(secondes-m_seconde)/60;
    m_minute=secondes%60;
    secondes=(secondes-m_minute)/60;
    m_heure=secondes;
}

Temps::Temps(int seconde){
    m_total_seconde=seconde;
    m_seconde=seconde%60;
    seconde=(seconde-m_seconde)/60;
    m_minute=seconde%60;
    seconde=(seconde-m_minute)/60;
    m_heure=seconde;

}

string Temps::getString() const {
    string s;
    //s=(string m_heure)+"h "+(string m_minute)+"m "+(string m_seconde)+" s";
    //s<<m_heure << "h "<< m_minute << "m " << m_seconde << "s";

    s=to_string(m_heure)+"h "+to_string(m_minute)+"m "+to_string(m_seconde)+"s";
    return s;
}

int Temps::getTotalSecondes()const {
    return m_total_seconde;
}

Temps Temps::operator+(Temps const& a) const {
    return Temps(this->m_total_seconde+a.m_total_seconde);

}

int Temps::getHeure() const{
    return m_heure;
}

int Temps::getMinute() const{
    return m_minute;
}

int Temps::getSeconde() const{
    return m_seconde;
}

bool Temps::operator==(Temps const& a) const{
    return (m_total_seconde == a.m_total_seconde);
}

ostream& operator<<( ostream &flux, Temps const& a ){

    return (flux << a.getString()) ;
}
