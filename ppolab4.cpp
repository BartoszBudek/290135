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

class student : public osoba {
public:
    // Użycie virtual zgodnie z konwencją prowadzącego
    virtual void drukuj(){
        cout<<"STUDENT:\n Imie: "<<imie<<" Nazwisko: "<<nazwisko<<" Indeks: "<<index<<endl;
    }
};

// Nowa klasa dziedzicząca po studencie, również z virtual
class student_zaoczny : public student {
public:
    virtual void drukuj(){
        cout<<"STUDENT ZAOCZNY:\n Imie: "<<imie<<" Nazwisko: "<<nazwisko<<" Indeks: "<<index<<endl;
    }
};

class prowadzacy : public osoba {
public:
    virtual void drukuj(){
        cout<<"PROWADZACY:\n Imie: "<<imie<<" Nazwisko: "<<nazwisko<<endl;
    }
};

int main(){
    osoba *tab[4];

    osoba os1;
    student st1;
    student_zaoczny stz1;
    prowadzacy pr1;

    os1.setimie("Jan"); os1.setnazwisko("Kowalski"); os1.setindex(100001);
    st1.setimie("Anna"); st1.setnazwisko("Nowak"); st1.setindex(222333);
    stz1.setimie("Piotr"); stz1.setnazwisko("Zielinski"); stz1.setindex(555666);
    pr1.setimie("Tomasz"); pr1.setnazwisko("Wisniewski");

    tab[0]=&os1;
    tab[1]=&st1;
    tab[2]=&stz1;
    tab[3]=&pr1;

    for(int i = 0; i < 4; i++) {
        tab[i]->drukuj();
        cout << "--------------------" << endl;
    }

    return 0;
}
