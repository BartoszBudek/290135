#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

class osoba
{    
    private:    
        int index;
        string imie;
        string nazwisko;
    public:
        int setindex(int index);
        int getindex(int index);
        string setimie(string imie);
        string getimie(string imie);
        string setnazwisko(string nazwisko);
        string getnazwisko(string nazwisko);

};
 
void menu()
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
            sprawdzobecnosc(tabosoba,tabobecnosc,obecnosc);
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

void dodaj(osoba *tabosoba)
{
    for(int i=0;i<10;i++)
    {
        if (tabosoba[i].imie=="");
        {
            cout<<"podaj indeks, imie i nazwisko osoby ktora chcesz dodac: ";
            cin>>tabosoba[i].index>>tabosoba[i].imie>>tabosoba[i].nazwisko;
            break;
        }
    }
}

void usun(osoba *tabosoba,bool *tabobecnosc)
{
    int idx;
    cout<<"podaj indeks osoby ktora chcesz usunac: ";
    cin>>idx;
    for(int i=0;i<10;i++)
    {
        if(tabosoba[i].index==idx)
        {
            if(i==9)
            {
                tabosoba[i].index=0;
                tabosoba[i].imie="";
                tabosoba[i].nazwisko="";
                tabobecnosc[i]="";
            }
            else
            {
                for(int m=i;m<10;m++)
                {
                    tabosoba[m].index=tabosoba[m+1].index;
                    tabosoba[m].imie=tabosoba[m+1].imie;
                    tabosoba[m].nazwisko=tabosoba[m+1].nazwisko;
                    tabobecnosc[m]=tabobecnosc[m+1];
                }
            }
        }
    }
}

void edytuj(osoba *tabosoba,bool *tabobecnosc)
{
    int idx;
    cout<<"podaj indeks osoby ktora chcesz edytowac: ";
    cin>>idx;
    for(int i=0;i<10;i++)
    {
        if(tabosoba[i].index==idx)
        {
            cout<<"podaj nowe dane(indeks/imie/nazwisko/obecnosc): ";
            cin>>tabosoba[i].index>>tabosoba[i].imie>>tabosoba[i].nazwisko>>tabobecnosc[i];
        }
    }
}

void sprawdzobecnosc(osoba *tabosoba,bool *tabobecnosc,bool obecnosc)
{
    cout<<"1-obecnosc 0-nieobecnosc\n";
    for(int i=0;i<10;i++)
    {
        if(tabosoba[i].imie!="")
        {
            cout<<tabosoba[i].imie<<" "<<tabosoba[i].nazwisko<<" ";
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
        if(tabosoba[i].imie!="")
        {
            cout<<i+1<<". "<<tabosoba[i].index<<" "<<tabosoba[i].imie<<" "<<tabosoba[i].nazwisko<<" "<<tabobecnosc[i]<<endl;
        }
        else break;
    }
}

int main()
{
    osoba tabosoba[10];
    bool tabobecnosc[10];
    bool obecnosc;
    menu();
}
