#include <iostream>
#include <string>
using namespace std;

class osoba {
protected:
    int index;
    string imie;
    string nazwisko;
public:
    osoba(){
        index=0;
        imie="";
        nazwisko="";
    }
    bool setindex(int id){
        if(id<100000||id>999999){
            cout<<"Bledna dlugosc indeksu\n";
            return false;
        }
        index=id;
        return true;
    }
    int getindex(){return index;}
    bool setimie(string i){
        if(i.length()<=2){
            cout<<"Za krotkie imie\n";
            return false;
        }
        imie=i;
        return true;
    }
    string getimie(){return imie;}
    bool setnazwisko(string n){
        if(n.length()<=2){
            cout<<"Za krotkie nazwisko\n";
            return false;
        }
        nazwisko=n;
        return true;
    }
    string getnazwisko(){return nazwisko;}
    void wyczysc(){
        index=0;
        imie="";
        nazwisko="";
    }
    virtual void drukuj(){
        cout<<"OSOBA:\n Imie: "<<imie<<" Nazwisko: "<<nazwisko<<endl;
    }
};

class student:public osoba{
    virtual void drukuj(){
        cout<<"STUDENT:\n Imie: "<<imie<<" Nazwisko: "<<nazwisko<<endl;
    }
};

class prowadzacy:public osoba{
    virtual void drukuj(){
        cout<<"PROWADZACY:\n Imie: "<<imie<<" Nazwisko: "<<nazwisko<<endl;
    }
};

int main(){
    osoba *tab[3];

    osoba os1;
    student st1;
    prowadzacy pr1;

    tab[0]=&os1;
    tab[1]=&st1;
    tab[2]=&pr1;

    tab[0]->drukuj();
    tab[1]->drukuj();
    tab[2]->drukuj();
}