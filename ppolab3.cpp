#include <iostream>
#include <string>
using namespace std;

class osoba {
private:
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
};

class listy {
private:
    osoba *naliscie[10];
    bool tabobecnosc[10];
public:
    listy(){
        for(int i=0;i<10;i++){
            naliscie[i]=nullptr;
            tabobecnosc[i]=false;
        }
    }
    void przypiszlista(osoba *wszyscy,int rozmiar){
        int idx;
        cout<<"Podaj indeks osoby z bazy danych ktora chcesz wpisac na liste: ";
        cin>>idx;
        for(int i=0;i<rozmiar;i++){
            if(wszyscy[i].getindex()==idx&&wszyscy[i].getimie()!=""){
                for(int j=0;j<10;j++){
                    if(naliscie[j]==nullptr){
                        naliscie[j]=&wszyscy[i];
                        cout<<"Osoba pomyslnie przypisana do listy\n";
                        return;
                    }
                }
                cout<<"Brak miejsca na tej liscie\n";
                return;
            }
        }
        cout<<"Nie ma takiej osoby w bazie\n";
    }
    void usunzlisty(){
        int idx;
        cout<<"Podaj indeks osoby ktora chcesz wypisac z tej listy: ";
        cin>>idx;
        for(int i=0;i<10;i++){
            if(naliscie[i]!=nullptr&&(*naliscie[i]).getindex()==idx){
                naliscie[i]=nullptr;
                tabobecnosc[i]=false;
                cout<<"Osoba zostala wypisana z listy\n";
                return;
            }
        }
        cout<<"Nie znaleziono takiej osoby na tej liscie\n";
    }
    void pokazlista(){
        cout<<"INDEKS/IMIE/NAZWISKO/OBECNOSC\n";
        bool pusta=true;
        for(int i=0;i<10;i++){
            // Dodany warunek getimie()!="", zeby nie wyswietlac usunietych z bazy
            if(naliscie[i]!=nullptr&&(*naliscie[i]).getimie()!=""){
                cout<<(*naliscie[i]).getindex()<<" "<<(*naliscie[i]).getimie()<<" "<<(*naliscie[i]).getnazwisko()<<" "<<tabobecnosc[i]<<endl;
                pusta=false;
            }
        }
        if(pusta)cout<<"Lista jest pusta\n";
    }
    void sprawdzobecnosc(){
        cout<<"SPRAWDZANIE OBECNOSCI (1-obecnosc 0-nieobecnosc)\n";
        for(int i=0;i<10;i++){
            if(naliscie[i]!=nullptr&&(*naliscie[i]).getimie()!=""){
                cout<<(*naliscie[i]).getimie()<<" "<<(*naliscie[i]).getnazwisko()<<": ";
                cin>>tabobecnosc[i];
            }
        }
    }
};

class interfejs {
private:
    osoba *wszyscy;
    listy *tablist;
    int ileosob,ilelist;
    
    void dodajwszyscy(){
        int tempindex;
        string tempimie,tempnazwisko;
        for(int i=0;i<ileosob;i++){
            if(wszyscy[i].getimie()==""){
                cout<<"Podaj dane nowej osoby \n";
                do{cout<<"Indeks: ";cin>>tempindex;}while(wszyscy[i].setindex(tempindex)==false);
                do{cout<<"Imie: ";cin>>tempimie;}while(wszyscy[i].setimie(tempimie)==false);
                do{cout<<"Nazwisko: ";cin>>tempnazwisko;}while(wszyscy[i].setnazwisko(tempnazwisko)==false);
                break;
            }
        }
    }
    void usunwszyscy(){
        int idx;
        cout<<"Podaj indeks osoby do usuniecia z bazy: ";
        cin>>idx;
        for(int i=0;i<ileosob;i++){
            if(wszyscy[i].getindex()==idx&&wszyscy[i].getimie()!=""){
                wszyscy[i].wyczysc();
                cout<<"Osoba usunieta z bazy\n";
                return;
            }
        }
    }
    void edytujwszyscy(){
        int idx,tempindex;
        string tempimie,tempnazwisko;
        cout<<"Podaj indeks osoby do edycji danych: ";
        cin>>idx;
        for(int i=0;i<ileosob;i++){
            if(wszyscy[i].getindex()==idx&&wszyscy[i].getimie()!=""){
                cout<<"Wpisz nowe dane \n";
                do{cout<<"Indeks: ";cin>>tempindex;}while(wszyscy[i].setindex(tempindex)==false);
                do{cout<<"Imie: ";cin>>tempimie;}while(wszyscy[i].setimie(tempimie)==false);
                do{cout<<"Nazwisko: ";cin>>tempnazwisko;}while(wszyscy[i].setnazwisko(tempnazwisko)==false);
                return;
            }
        }
    }
    void pokazwszystkich(){
        cout<<"INDEKS/IMIE/NAZWISKO\n";
        for(int i=0;i<ileosob;i++){
            if(wszyscy[i].getimie()!=""){
                cout<<wszyscy[i].getindex()<<" "<<wszyscy[i].getimie()<<" "<<wszyscy[i].getnazwisko()<<endl;
            }
        }
    }
    int wybierzliste(){
        int n;
        cout<<"Wybierz numer listy (1 lub 2): ";
        cin>>n;
        if(n>=1&&n<=ilelist)return n-1;
        cout<<"Bledny numer listy\n";
        return -1;
    }
public:
    interfejs(osoba *tabo,int ileo,listy *tabl,int ilel){
        wszyscy=tabo;
        ileosob=ileo;
        tablist=tabl;
        ilelist=ilel;
    }

    void petla(){
        int wybor;
        bool p=true;
        int nrlisty;
        while(p){
            cout<<"\nWYBIERZ CZYNNOSC\n";
            cout<<"1 dodaj osobe do bazy\n2 edytuj osobe\n3 usun osobe z bazy\n4 pokaz baze\n5 dodaj do listy\n6 usun z listy\n7 sprawdz obecnosc\n8 pokaz liste\n";
            cout<<"0 koniec\nwybor: ";
            cin>>wybor;
            switch(wybor){
            case 1:dodajwszyscy();break;
            case 2:edytujwszyscy();break;
            case 3:usunwszyscy();break;
            case 4:pokazwszystkich();break;
            case 5:
                nrlisty=wybierzliste();
                if(nrlisty!=-1)tablist[nrlisty].przypiszlista(wszyscy,ileosob);
                break;
            case 6:
                nrlisty=wybierzliste();
                if(nrlisty!=-1)tablist[nrlisty].usunzlisty();
                break;
            case 7:
                nrlisty=wybierzliste();
                if(nrlisty!=-1)tablist[nrlisty].sprawdzobecnosc();
                break;
            case 8:
                nrlisty=wybierzliste();
                if(nrlisty!=-1)tablist[nrlisty].pokazlista();
                break;
            case 0:p=false;break;
            }
        }
    }
};

int main(){
    osoba wszyscy[10];
    listy tablist[2];
    interfejs ui(wszyscy,10,tablist,2);
    ui.petla();
    return 0;
}