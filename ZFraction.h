#ifndef ZFRACTION_H_INCLUDED
#define ZFRACTION_H_INCLUDED
#include <iostream>
#include <string>


class ZFraction{
    public :
        bool existe() const;
        double valeur() const;
        int getNum() const;
        int getDenom() const;
        ZFraction(int num, int denom);
        void simplifier();
        ZFraction operator+(ZFraction const& a) const;
        bool operator==(ZFraction const& a) const;
        ZFraction operator*(ZFraction const&a) const;
        ZFraction operator/(ZFraction const&a) const;
        bool operator>(ZFraction const& a) const;
        std::string getString() const;
        void recreer(int num,int denom);
    private:
        int m_num;
        int m_denom;
};

std::ostream& operator<<( std::ostream &flux, ZFraction const& a );


#endif // ZFRACTION_H_INCLUDED
