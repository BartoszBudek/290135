#include <iostream>
#include <string>
using namespace std;

class osoba
{    
    private:    
        int index;
        string imie;
        string nazwisko;
    public:
        bool setIndex(int id) {
            if(id <= 100000 || id >= 999999)
            {
                cout<<"Bledna dlugosc indeksu\n";
                return false;
            }
            index=id;
            return true;
        }
        int getIndex(){
            return index;
        }
        bool setImie(string i){
            if(i.length()<=2)
            {
                cout<<"Za krotkie imie\n";
                return false;
            }
            imie=i;
            return true;
        }
        string getImie(){
            return imie;
        }
        bool setNazwisko(string n){
            if(n.length()<=2)
            {
                cout<<"Za krotkie nazwisko\n";
                return false;
            }
            nazwisko=n;
            return true;
        }
        string getNazwisko(){
            return nazwisko;
        }
        void wyczysc(){
            index=0;
            imie="";
            nazwisko="";
        }
    };

void dodaj(osoba *tabosoba)
{
    int tempindex;
    string tempimie,tempnazwisko;
    for(int i=0;i<10;i++)
    {
        if (tabosoba[i].getImie()=="")
        {
            cout<<"Podaj indeks, imie i nazwisko osoby, ktora chcesz dodac: \n";
            do{
                cout<<"Indeks: ";
                cin>>tempindex;
            } while (tabosoba[i].setIndex(tempindex)==false);
            do{
                cout<<"Imie: ";
                cin>>tempimie;
            } while (tabosoba[i].setImie(tempimie)==false);
            do{
                cout<<"Nazwisko: ";
                cin>>tempnazwisko;
            } while (tabosoba[i].setNazwisko(tempnazwisko)==false);
            break;
        }
    }
}

void usun(osoba *tabosoba,bool *tabobecnosc)
{
    int idx;
    cout<<"Podaj indeks osoby ktora chcesz usunac: ";
    cin>>idx;
    for(int i=0;i<10;i++)
    {
        if(tabosoba[i].getIndex()==idx)
        {
            if(i==9)
            {
                tabosoba[i].wyczysc();
            }
            else
            {
                for(int m=i;m<9;m++)
                {
                    tabosoba[m].setIndex(tabosoba[m+1].getIndex());
                    tabosoba[m].setImie(tabosoba[m+1].getImie());
                    tabosoba[m].setNazwisko(tabosoba[m+1].getNazwisko());
                    tabobecnosc[m]=tabobecnosc[m+1];
                }
                tabosoba[9].wyczysc();
                tabobecnosc[9]=0;
            }
        }
    }
}

void edytuj(osoba *tabosoba,bool *tabobecnosc)
{
    int tempindex;
    string tempimie,tempnazwisko;
    int idx;
    cout<<"Podaj indeks osoby, ktora chcesz edytowac: ";
    cin>>idx;
    for(int i=0;i<10;i++)
    {
        if(tabosoba[i].getIndex()==idx)
        {
            cout<<"Podaj nowe dane: ";
            do{
                cout<<"Indeks: ";
                cin>>tempindex;
            } while (tabosoba[i].setIndex(tempindex)==false);
            do{
                cout<<"Imie: ";
                cin>>tempimie;
            } while (tabosoba[i].setImie(tempimie)==false);
            do{
                cout<<"Nazwisko: ";
                cin>>tempnazwisko;
            } while (tabosoba[i].setNazwisko(tempnazwisko)==false);
        }
    }
}

void sprawdzobecnosc(osoba *tabosoba,bool *tabobecnosc)
{
    bool obecnosc;
    cout<<"SPRAWDZANIE OBECNOSCI(1-obecnosc 0-nieobecnosc)\n";
    for(int i=0;i<10;i++)
    {
        if(tabosoba[i].getImie()!="")
        {
            cout<<tabosoba[i].getImie()<<" "<<tabosoba[i].getNazwisko()<<" ";
            cin>>obecnosc;
            tabobecnosc[i]=obecnosc;
        }
        else break;
    }
}

void lista(osoba *tabosoba,bool *tabobecnosc)
{
    cout<<"NR/INDEKS/IMIE/NAZWISKO/OBECNOSC\n";
    for(int i=0;i<10;i++)
    {
        if(tabosoba[i].getImie()!="")
        {
            cout<<i+1<<". "<<tabosoba[i].getIndex()<<" "<<tabosoba[i].getImie()<<" "<<tabosoba[i].getNazwisko()<<" "<<tabobecnosc[i]<<endl;
        }
        else break;
    }
}

void menu(osoba *tabosoba,bool *tabobecnosc)
{
    int p = 1;
    int wybor;
    while(p)
    {
        cout<<"\n";
        cout<<"Wybierz czynnosc: \n";
        cout<<"1-dodaj osobe\n";
        cout<<"2-usun osobe\n";
        cout<<"3-edytuj osobe\n";
        cout<<"4-sprawdz obecnosc\n";
        cout<<"5-pokaz liste\n";
        cout<<"0-koniec\n";
        cout<<"wybor: ";
        cin>>wybor;
        if(wybor==1)
        {
            cout<<" \n";
            dodaj(tabosoba);
        }
        if(wybor==2)
        {
            cout<<" \n";
            usun(tabosoba,tabobecnosc);
        }
        if(wybor==3)
        {
            cout<<" \n";
            edytuj(tabosoba,tabobecnosc);
        }
        if(wybor==4)
        {
            cout<<" \n";
            sprawdzobecnosc(tabosoba,tabobecnosc);
        }
        if(wybor==5)
        {
            cout<<" \n";
            lista(tabosoba,tabobecnosc);
        }
        if(wybor==0)
        {
            p=0;
        }
    }
}

int main()
{
    osoba tabosoba[10];
    bool tabobecnosc[10]={false};
    menu(tabosoba,tabobecnosc);
}
