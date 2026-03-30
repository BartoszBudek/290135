#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;
 
void dodaj(int *tabindex,int index,string *tabimie,string imie,string *tabnazwisko,string nazwisko)
{
    for(int i=0;i<10;i++)
    {
        if (tabnazwisko[i]=="")
        {
            tabindex[i]=index;
            tabimie[i]=imie;
            tabnazwisko[i]=nazwisko;
            break;
        }
    }
}

void usun(int *tabindex,string *tabimie,string *tabnazwisko,bool *tabobecnosc)
{
    int idx;
    cout<<"podaj indeks osoby ktora chcesz usunac: ";
    cin>>idx;
    for(int i=0;i<10;i++)
    {
        if(tabindex[i]==idx)
        {
            if(i==9)
            {
                tabindex[i]=0;
                tabimie[i]="";
                tabnazwisko[i]="";
                tabobecnosc[i]="";
            }
            else
            {
                for(int m=i;m<10;m++)
                {
                    tabindex[m]=tabindex[m+1];
                    tabimie[m]=tabimie[m+1];
                    tabnazwisko[m]=tabnazwisko[m+1];
                    tabobecnosc[m]=tabobecnosc[m+1];
                }
            }
        }
    }
}

void edytuj(int *tabindex,string *tabimie,string *tabnazwisko,bool *tabobecnosc)
{
    int idx;
    cout<<"podaj indeks osoby ktora chcesz edytowac: ";
    cin>>idx;
    for(int i=0;i<10;i++)
    {
        if(tabindex[i]==idx)
        {
            cout<<"podaj nowe dane(indeks/imie/nazwisko/obecnosc): ";
            cin>>tabindex[i]>>tabimie[i]>>tabnazwisko[i]>>tabobecnosc[i];
        }
    }
}

void sprawdzobecnosc(string *tabnazwisko,bool *tabobecnosc,bool obecnosc)
{
    cout<<"1-obecnosc 0-nieobecnosc\n";
    for(int i=0;i<10;i++)
    {
        if(tabnazwisko[i]!="")
        {
            cout<<tabnazwisko[i]<<" ";
            cin>>obecnosc;
            tabobecnosc[i]=obecnosc;
        }
        else break;
    }
}

void lista(int *tabindex,string *tabimie,string *tabnazwisko,bool *tabobecnosc)
{
    cout<<"NR/INDEKS/IMIE/NAZWISKO/OBECNOSC\n";
    for(int i=0;i<10;i++)
    {
        if(tabnazwisko[i]!="")
        {
            cout<<i+1<<". "<<tabindex[i]<<" "<<tabimie[i]<<" "<<tabnazwisko[i]<<" "<<tabobecnosc[i]<<endl;
        }
        else break;
    }
}

int main()
{
    string tabimie[10];
    string imie;
    string tabnazwisko[10];
    string nazwisko;
    int tabindex[10];
    int index;
    bool tabobecnosc[10];
    bool obecnosc;
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
            cout<<"podaj index, imie i nazwisko osoby ktora chcesz dodac: ";
            cin>>index>>imie>>nazwisko;
            dodaj(tabindex,index,tabimie,imie,tabnazwisko,nazwisko);
        }
        if(wybor==2)
        {
            cout<<" \n";
            usun(tabindex,tabimie,tabnazwisko,tabobecnosc);
        }
        if(wybor==3)
        {
            cout<<" \n";
            edytuj(tabindex,tabimie,tabnazwisko,tabobecnosc);
        }
        if(wybor==4)
        {
            cout<<" \n";
            sprawdzobecnosc(tabnazwisko,tabobecnosc,obecnosc);
        }
        if(wybor==5)
        {
            cout<<" \n";
            lista(tabindex,tabimie,tabnazwisko,tabobecnosc);
        }
        if(wybor==0)
        {
            p=0;
        }
    }
}