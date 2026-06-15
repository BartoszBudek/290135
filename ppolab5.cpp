#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class ISerializable {
public:
    virtual string serialize() = 0;
    virtual ~ISerializable() = default; 
};

class osoba {
protected:
    int index;
    string imie;
    string nazwisko;
public:
    osoba() {
        index = 0;
        imie = "";
        nazwisko = "";
    }
    virtual ~osoba() = default;

    bool setindex(int id) {
        if(id < 100000 || id > 999999) {
            cout << "Bledna dlugosc indeksu\n";
            return false;
        }
        index = id;
        return true;
    }
    int getindex() { return index; }
    
    bool setimie(string i) {
        if(i.length() <= 2) {
            cout << "Za krotkie imie\n";
            return false;
        }
        imie = i;
        return true;
    }
    string getimie() { return imie; }
    
    bool setnazwisko(string n) {
        if(n.length() <= 2) {
            cout << "Za krotkie nazwisko\n";
            return false;
        }
        nazwisko = n;
        return true;
    }
    string getnazwisko() { return nazwisko; }

    virtual void drukuj() {
        cout << "OSOBA:\n Imie: " << imie << " Nazwisko: " << nazwisko << endl;
    }
};

class student : public osoba, public ISerializable {
public:
    void drukuj() override {
        cout << "STUDENT:\n Imie: " << imie << " Nazwisko: " << nazwisko << " Indeks: " << index << endl;
    }
    string serialize() override {
        return "STUDENT: Imie: " + imie + " Nazwisko: " + nazwisko + " Indeks: " + to_string(index) + "\n";
    }
};

class student_zaoczny : public student {
public:
    void drukuj() override {
        cout << "STUDENT ZAOCZNY:\n Imie: " << imie << " Nazwisko: " << nazwisko << " Indeks: " << index << endl;
    }
};

class prowadzacy : public osoba {
public:
    void drukuj() override {
        cout << "PROWADZACY:\n Imie: " << imie << " Nazwisko: " << nazwisko << endl;
    }
};

class listy {
private:
    osoba *naliscie[10];
    bool tabobecnosc[10];
public:
    listy() {
        for(int i=0; i<10; i++) {
            naliscie[i] = nullptr;
            tabobecnosc[i] = false;
        }
    }
    
    void przypiszlista(osoba **wszyscy, int rozmiar) {
        int idx;
        cout << "Podaj indeks osoby z bazy danych ktora chcesz wpisac na liste: ";
        cin >> idx;
        for(int i=0; i<rozmiar; i++) {
            if(wszyscy[i] != nullptr && wszyscy[i]->getindex() == idx) {
                for(int j=0; j<10; j++) {
                    if(naliscie[j] == nullptr) {
                        naliscie[j] = wszyscy[i];
                        cout << "Osoba pomyslnie przypisana do listy\n";
                        return;
                    }
                }
                cout << "Brak miejsca na tej liscie\n";
                return;
            }
        }
        cout << "Nie ma takiej osoby w bazie\n";
    }
    
    void usunzlisty() {
        int idx;
        cout << "Podaj indeks osoby ktora chcesz wypisac z tej listy: ";
        cin >> idx;
        for(int i=0; i<10; i++) {
            if(naliscie[i] != nullptr && naliscie[i]->getindex() == idx) {
                naliscie[i] = nullptr;
                tabobecnosc[i] = false;
                cout << "Osoba zostala wypisana z listy\n";
                return;
            }
        }
        cout << "Nie znaleziono takiej osoby na tej liscie\n";
    }

    void wymususun(int idx) {
        for(int i=0; i<10; i++) {
            if(naliscie[i] != nullptr && naliscie[i]->getindex() == idx) {
                naliscie[i] = nullptr;
                tabobecnosc[i] = false;
            }
        }
    }
    
    void pokazlista() {
        cout << "INDEKS/IMIE/NAZWISKO/OBECNOSC\n";
        bool pusta = true;
        for(int i=0; i<10; i++) {
            if(naliscie[i] != nullptr) {
                cout << naliscie[i]->getindex() << " " << naliscie[i]->getimie() << " " 
                     << naliscie[i]->getnazwisko() << " " << tabobecnosc[i] << endl;
                pusta = false;
            }
        }
        if(pusta) cout << "Lista jest pusta\n";
    }
    
    void sprawdzobecnosc() {
        cout << "SPRAWDZANIE OBECNOSCI (1-obecnosc 0-nieobecnosc)\n";
        for(int i=0; i<10; i++) {
            if(naliscie[i] != nullptr) {
                cout << naliscie[i]->getimie() << " " << naliscie[i]->getnazwisko() << ": ";
                cin >> tabobecnosc[i];
            }
        }
    }

    void zapiszliste(ofstream& plik) {
        for(int i=0; i<10; i++) {
            if(naliscie[i] != nullptr) {
                ISerializable* ser = dynamic_cast<ISerializable*>(naliscie[i]);
                if(ser) {
                    plik << ser->serialize();
                } else {
                    plik << "INNA OSOBA: " << naliscie[i]->getimie() << " " << naliscie[i]->getnazwisko() << "\n";
                }
            }
        }
    }
};

class interfejs {
protected:
    osoba **wszyscy;
    listy *tablist;
    int ileosob, ilelist;
    
    void dodajwszyscy() {
        for(int i=0; i<ileosob; i++) {
            if(wszyscy[i] == nullptr) { 
                int typ;
                cout << "Kogo chcesz dodac?\n 1. Student\n 2. Student zaoczny\n 3. Prowadzacy\nWybor: ";
                cin >> typ;

                osoba* nowaosoba = nullptr;
                if(typ == 1) nowaosoba = new student();
                else if(typ == 2) nowaosoba = new student_zaoczny();
                else if(typ == 3) nowaosoba = new prowadzacy();
                else { cout << "Bledny wybor.\n"; return; }

                int tempindex; string tempimie, tempnazwisko;
                cout << "Podaj dane nowej osoby \n";
                do { cout << "Indeks: "; cin >> tempindex; } while(!nowaosoba->setindex(tempindex));
                do { cout << "Imie: "; cin >> tempimie; } while(!nowaosoba->setimie(tempimie));
                do { cout << "Nazwisko: "; cin >> tempnazwisko; } while(!nowaosoba->setnazwisko(tempnazwisko));
                
                wszyscy[i] = nowaosoba; 
                cout << "Dodano do bazy!\n";
                return;
            }
        }
        cout << "Baza jest pelna!\n";
    }
    
    void usunwszyscy() {
        int idx;
        cout << "Podaj indeks osoby do usuniecia z bazy: ";
        cin >> idx;
        for(int i=0; i<ileosob; i++) {
            if(wszyscy[i] != nullptr && wszyscy[i]->getindex() == idx) {
                for(int j=0; j<ilelist; j++) tablist[j].wymususun(idx);
                
                delete wszyscy[i]; 
                wszyscy[i] = nullptr;
                cout << "Osoba usunieta z bazy.\n";
                return;
            }
        }
        cout << "Nie znaleziono osoby w bazie.\n";
    }
    
    void edytujwszyscy() {
        int idx, tempindex;
        string tempimie, tempnazwisko;
        cout << "Podaj indeks osoby do edycji danych: ";
        cin >> idx;
        for(int i=0; i<ileosob; i++) {
            if(wszyscy[i] != nullptr && wszyscy[i]->getindex() == idx) {
                cout << "Wpisz nowe dane \n";
                do { cout << "Indeks: "; cin >> tempindex; } while(!wszyscy[i]->setindex(tempindex));
                do { cout << "Imie: "; cin >> tempimie; } while(!wszyscy[i]->setimie(tempimie));
                do { cout << "Nazwisko: "; cin >> tempnazwisko; } while(!wszyscy[i]->setnazwisko(tempnazwisko));
                cout << "Dane zaktualizowane.\n";
                return;
            }
        }
        cout << "Nie znaleziono osoby w bazie.\n";
    }
    
    void pokazwszystkich() {
        cout << "BAZA OSOB:\n";
        bool pusto = true;
        for(int i=0; i<ileosob; i++) {
            if(wszyscy[i] != nullptr) {
                wszyscy[i]->drukuj(); 
                pusto = false;
            }
        }
        if(pusto) cout << "Baza jest pusta.\n";
    }
    
    int wybierzliste() {
        int n;
        cout << "Wybierz numer listy (1 lub 2): ";
        cin >> n;
        if(n >= 1 && n <= ilelist) return n - 1;
        cout << "Bledny numer listy\n";
        return -1;
    }

    void zapiszdopliku() {
        int wybor;
        cout << "Co chcesz zapisac: \n 1. Zapisac cala liste\n 2. Zapisac 1 studenta\nWybor: ";
        cin >> wybor;
        
        if (wybor == 1) {
            int nrl = wybierzliste();
            if (nrl != -1) {
                string nazwa = "lista_" + to_string(nrl+1) + ".txt";
                ofstream plik(nazwa);
                tablist[nrl].zapiszliste(plik);
                plik.close();
                cout << "Zapisano do pliku " << nazwa << "\n";
            }
        } 
        else if (wybor == 2) {
            int idx;
            cout << "Podaj indeks studenta, ktorego chcesz zapisac: ";
            cin >> idx;
            
            bool znaleziono = false;
            for(int i=0; i<ileosob; i++) {
                if(wszyscy[i] != nullptr && wszyscy[i]->getindex() == idx) {
                    znaleziono = true;
                    ISerializable* ser = dynamic_cast<ISerializable*>(wszyscy[i]);
                    if(ser) {
                        string nazwa = "student_" + to_string(idx) + ".txt";
                        ofstream plik(nazwa);
                        plik << ser->serialize();
                        plik.close();
                        cout << "Zapisano studenta do pliku " << nazwa << "\n";
                    } else {
                        cout << "Ta osoba nie implementuje zapisu (np. to prowadzacy).\n";
                    }
                    break;
                }
            }
            if(!znaleziono) cout << "Nie ma takiego studenta w bazie.\n";
        }
    }

public:
    interfejs(osoba **tabo, int ileo, listy *tabl, int ilel) {
        wszyscy = tabo;
        ileosob = ileo;
        tablist = tabl;
        ilelist = ilel;
    }

    void petla() {
        int wybor;
        bool p = true;
        int nrlisty;
        while(p) {
            cout << "\nWYBIERZ CZYNNOSC\n";
            cout << "1 dodaj osobe do bazy\n2 edytuj osobe\n3 usun osobe z bazy\n4 pokaz baze\n";
            cout << "5 dodaj do listy\n6 usun z listy\n7 sprawdz obecnosc\n8 pokaz liste\n9 zapisz do pliku\n";
            cout << "0 koniec\nWybor: ";
            cin >> wybor;
            cout << "\n";
            
            switch(wybor) {
                case 1: dodajwszyscy(); break;
                case 2: edytujwszyscy(); break;
                case 3: usunwszyscy(); break;
                case 4: pokazwszystkich(); break;
                case 5:
                    nrlisty = wybierzliste();
                    if(nrlisty != -1) tablist[nrlisty].przypiszlista(wszyscy, ileosob);
                    break;
                case 6:
                    nrlisty = wybierzliste();
                    if(nrlisty != -1) tablist[nrlisty].usunzlisty();
                    break;
                case 7:
                    nrlisty = wybierzliste();
                    if(nrlisty != -1) tablist[nrlisty].sprawdzobecnosc();
                    break;
                case 8:
                    nrlisty = wybierzliste();
                    if(nrlisty != -1) tablist[nrlisty].pokazlista();
                    break;
                case 9:
                    zapiszdopliku(); 
                    break;
                case 0: 
                    p = false; 
                    break;
                default: 
                    cout << "Bledny wybor.\n";
            }
        }
    }
};

int main(){
    osoba* wszyscy[10] = {nullptr}; 
    listy tablist[2];
    
    interfejs ui(wszyscy, 10, tablist, 2);
    ui.petla();
    
    for(int i=0; i<10; i++){
        if(wszyscy[i] != nullptr){
            delete wszyscy[i];
        }
    }
    
    return 0;
}
