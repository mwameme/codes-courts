#include "ZFraction.h"

using namespace std;

bool ZFraction::existe() const {
    return m_denom != 0;
}

double ZFraction::valeur() const
{
    if (existe())
        return ((double) m_num)/((double) m_denom);
    else return 0;
}

int ZFraction::getNum() const{
    return m_num;
}

int ZFraction::getDenom() const{
    return m_denom;
}

ZFraction::ZFraction(int num=1, int denom=1): m_num(num), m_denom(denom){
    simplifier();
}

void ZFraction::simplifier(){
    if (m_denom==0) {
            m_num=1;
    }
    else{
        int a=m_num,b=m_denom,c=0;
        while (b != 0){
            c=a%b;
            a=b;
            b=c;
        }
        m_num=m_num/a;
        m_denom=m_denom/a;
    }
    if (m_denom<0){
        m_num=-m_num;
        m_denom=-m_denom;
    }
}

ZFraction ZFraction::operator+(ZFraction const& a) const {
    return ZFraction(m_num*a.m_denom+m_denom*a.m_num,m_denom*a.m_denom);
}

bool ZFraction::operator==(ZFraction const& a) const{
    return (m_denom==a.m_denom) && (m_num==a.m_num);
}

ZFraction ZFraction::operator*(ZFraction const&a) const{
    return ZFraction(m_num*a.m_num,m_denom*a.m_denom);
}

bool ZFraction::operator>(ZFraction const& a) const{
    return (m_num*a.m_denom)>(a.m_num*m_denom);

}
string ZFraction::getString() const{
    return (to_string(m_num)+"/"+to_string(m_denom));
}

ZFraction ZFraction::operator/(ZFraction const&a) const{
    return ZFraction(m_num*a.m_denom,m_denom*a.m_num);
}


ostream& operator<<(ostream &flux, ZFraction const& a ){
    return flux<<a.getString();
}


void ZFraction::recreer(int num=1, int denom=1){
    m_num=num;
    m_denom=denom;
    simplifier();
}
