// ============================================================
//  Lab: Interfejsy i wzorzec Strategy
//  Paradygmaty Programowania Obiektowego
//
// ============================================================

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// ============================================================
//  KLASY PODSTAWOWE
//  Mozesz skopiować tutaj swoje klasy Student i ListaObecnosci,
//  z poprzednich zajec, lub użyć zaproponowanych (uproszczone)
// ============================================================


// ============================================================
// STUDENT
// Bazowa implementacja - tylko podstawowe informacje o studencie
// ustawianie danych przez konstruktor, bez setterów
// ============================================================

class Student {
  private:
    string imie;
    string nazwisko;
    string nrIndeksu;

  public:
    Student(string imie, string nazwisko, string nrIndeksu)
        : imie(imie), nazwisko(nazwisko), nrIndeksu(nrIndeksu) {}

    string getImie()       { return imie; }
    string getNazwisko()   { return nazwisko; }
    string getNrIndeksu() { return nrIndeksu; }
};


// ============================================================
//  ListaObecnosci
//
//  Prosta implementacja oparta o dwie oddzielne tablice polaczone indeksem:
//    studenci[i]  — wskaznik do obiektu Student
//    obecnosc[i]  — licznik obecnosci studenta i
//
//  Indeksy obu tablic sa zsynchronizowane:
//  obecnosc[2] to liczba obecnosci studenta studenci[2].
// ============================================================
class ListaObecnosci {
  private:
    Student** studenci;
    int*      obecnosc;
    int       liczba_zajec;
    int       rozmiar;
    int       pojemnosc;
    string nazwa_przedmiotu;

  public:
    ListaObecnosci(string nazwa, int pojemnosc)
        : liczba_zajec(0), rozmiar(0), pojemnosc(pojemnosc),
          nazwa_przedmiotu(nazwa) {
        studenci = new Student*[pojemnosc];
        obecnosc = new int[pojemnosc];
        for (int i = 0; i < pojemnosc; i++)
            obecnosc[i] = 0;
    }

    ~ListaObecnosci() {
        for (int i = 0; i < rozmiar; i++)
            delete studenci[i];
        delete[] studenci;
        delete[] obecnosc;
    }

    void dodajStudenta(Student* s) {
        if (rozmiar < pojemnosc)
            studenci[rozmiar++] = s;
    }

    // Zaznacza obecnosc dla jednych zajec.
    // obecni[i] == 1 oznacza ze student studenci[i] byl obecny.
    // obecni[i] == 0 oznacza nieobecnosc.
    void zaznaczObecnosc(int* obecni, int rozmiar_tablicy) {
        liczba_zajec++;
        for (int i = 0; i < rozmiar_tablicy && i < rozmiar; i++)
            if (obecni[i])
                obecnosc[i]++;
    }

    int getLiczbaObecnosci(int i) { return obecnosc[i]; }
    int getLiczbaZajec()          { return liczba_zajec; }

    int getProcentObecnosci(int i) {
        if (liczba_zajec == 0) return 0;
        return (obecnosc[i] * 100) / liczba_zajec;
    }

    Student**   getStudenci() { return studenci; }
    int*        getObecnosc() { return obecnosc; }
    int         getRozmiar()  { return rozmiar; }
    string getNazwa()    { return nazwa_przedmiotu; }
};


// ============================================================
//  INTERFEJSY
//  Nie modyfikuj tych klas.
// ============================================================

class IFiltr {
  public:
    // Zwraca nowa tablice wskaznikow do studentow spelniajacych
    // kryterium. Rozmiar wynikowej tablicy zapisywany jest
    // do *wynik_rozmiar. Wywolujacy jest odpowiedzialny za
    // zwolnienie pamieci tablicy wynikowej (nie obiektow Student).
    virtual Student** filtruj(Student** studenci,
                              int*      obecnosc,
                              int       liczba_zajec,
                              int       rozmiar,
                              int*      wynik_rozmiar) = 0;
};

class INotyfikator {
  public:
    virtual void powiadom(Student* student, string komunikat) = 0;
};

class IRaport {
  public:
    virtual void generuj(Student** studenci,
                         int*      obecnosc,
                         int       liczba_zajec,
                         int       rozmiar,
                         string nazwa_pliku) = 0;
};


// ============================================================
//  CZESC 1 — IMPLEMENTACJE IFiltr
//
//  Zaimplementuj jedna z ponizszych klas.
//
//  FiltrProguObecnosci — zwraca studentow ktorych procent
//    obecnosci jest nizszy niz prog podany w konstruktorze
//
//  FiltrNazwiska — zwraca studentow ktorych nazwisko
//    zaczyna sie na litere podana w konstruktorze
//
//  FiltrIndeksu — zwraca studentow ktorych numer indeksu
//    zaczyna sie od ciagu znakow podanego w konstruktorze
// ============================================================


//  PRZYKLAD IMPLEMENTACJI TYPU "STUB"
//  FiltrStub zwraca cala tablice, ktora otrzymal na wejsciu
//

class FiltrStub : public IFiltr {
  public:
    Student** filtruj(Student** studenci, int* obecnosc,
                      int liczba_zajec, int rozmiar,
                      int* wynik_rozmiar) {
        Student** wynik = new Student*[rozmiar];
        for (int i = 0; i < rozmiar; i++)
            wynik[i] = studenci[i];
        *wynik_rozmiar = rozmiar;
        return wynik;
    }

};


// TUTAJ ZAIMPLEMENTUJ FILTRY


// ============================================================
//  CZESC 2 — IMPLEMENTACJE INotyfikator
//
//  Zaimplementuj jedna z ponizszych klas.
//
//  NotyfikatorKonsola — wypisuje imie, nazwisko i komunikat
//    na cout
//
//  NotyfikatorPlik — dopisuje wpis do pliku powiadomienia.txt
//    w formacie: [imie nazwisko]: komunikat
//
//  NotyfikatorEmail — wypisuje na konsole sformatowany
//    naglowek emaila:
//      Do: nrIndeksu@uczelnia.pl
//      Temat: Powiadomienie
//      Tresc: komunikat
// ============================================================

class NotyfikatorStub : public INotyfikator {
public:
    void powiadom(Student* student, string komunikat) {
        cout << "[STUB] " << student->getImie() << ": " << komunikat << endl;
    }
};

// TUTAJ ZAIMPLEMENTUJ
class NotyfikatorKonsola : public INotyfikator {
public:
    void powiadom(Student* student, string komunikat){
        cout<<"Imie i nazwisko: "<<student->getImie()<<" "<<student->getNazwisko()<<" "<<komunikat<<endl;
    } 
};


// ============================================================
//  CZESC 3 — IMPLEMENTACJE IRaport
//
//  Zaimplementuj jedna z ponizszych klas (do wyboru).
//
//  RaportFrekwencji — dla kazdego studenta wypisuje imie,
//    nazwisko i procent obecnosci
//
//  RaportZagrozonych — wypisuje tylko studentow ponizej
//    50% obecnosci z informacja ile zajec musza nadrobi
//    zeby osiagnac prog
//
//  RaportPodsumowania — jedna strona: liczba studentow,
//    srednia obecnosc, najlepszy i najgorszy wynik
// ============================================================

// TUTAJ ZAIMPLEMENTUJ
class RaportStub : public IRaport {
public:
    void generuj(Student** studenci, int* obecnosc,
                 int liczba_zajec, int rozmiar, string nazwa_pliku) {
        cout << "[STUB] Raport dla " << rozmiar << " studentow" << endl;
    }
};

class Raportfrekwencji: public IRaport{
    public:
    void generuj(Student** studenci, int* obecnosc, int liczba_zajec, int rozmiar, string nazwa_pliku){
        for(int i=0; i<rozmiar; i++){
            int procentObecnosci = (obecnosc[i] * 100) / liczba_zajec;
            cout << studenci[i]->getImie() << " " << studenci[i]->getNazwisko() << " - " << procentObecnosci << "%" << endl;
        }
    }
};

class RaportZagrozonych : public IRaport {
public:
    void generuj(Student** studenci, int* obecnosc, int liczba_zajec, int rozmiar, string nazwa_pliku){
        for(int i=0; i<rozmiar; i++){
            if((obecnosc[i]*1.0/liczba_zajec)<0.5) {
                cout<<studenci[i]->getImie()<<" "<<studenci[i]->getNazwisko()<<" brakuje "<<liczba_zajec-obecnosc[i]<<" aby zdac"<<endl;
            }
        }
    }
};

// ============================================================
//  MAIN i przyklad filtra
// ============================================================


void testFiltrowania(IFiltr *filtr, ListaObecnosci *lista){
    int wynik_rozmiar_stub = 0;
    Student **wynikStub = filtr->filtruj(lista->getStudenci(),
                                            lista->getObecnosc(),
                                            lista->getLiczbaZajec(),
                                            lista->getRozmiar(),
                                            &wynik_rozmiar_stub);

    for(int i=0; i<wynik_rozmiar_stub; i++){
      cout << wynikStub[i]->getImie() << endl;
    }

    delete[] wynikStub;
}

void testNotyfikatora(INotyfikator* notyfikator, ListaObecnosci* lista) {
    // do uzupelnienia przez studentow
    notyfikator->powiadom(lista->getStudenci()[0],"test");
}

void testRaportu(IRaport* raport, ListaObecnosci* lista ) {
    int procentObecnosci=0;
    raport->generuj(lista->getStudenci(),
                    lista->getObecnosc(),
                    lista->getLiczbaZajec(),
                    lista->getRozmiar(),
                    "raport.txt");

}

int main() {
    ListaObecnosci lista("Paradygmaty Programowania Obiektowego", 10);

    lista.dodajStudenta(new Student("Anna",    "Kowalska",   "123456"));
    lista.dodajStudenta(new Student("Bartosz", "Nowak",      "654321"));
    lista.dodajStudenta(new Student("Celina",  "Kwiatkowska","111111"));
    lista.dodajStudenta(new Student("Damian",  "Krawczyk",   "222222"));

    // symulacja trzech zajec
    // zajecia 1: Anna, Celina i Damian obecni
    int zajecia1[] = {1, 0, 1, 1};
    lista.zaznaczObecnosc(zajecia1, lista.getRozmiar());

    // zajecia 2: tylko Damian obecny
    int zajecia2[] = {0, 0, 0, 1};
    lista.zaznaczObecnosc(zajecia2, lista.getRozmiar());

    // zajecia 3: Anna i Celina obecne
    int zajecia3[] = {1, 0, 1, 0};
    lista.zaznaczObecnosc(zajecia3, lista.getRozmiar());

    // PRZYKLADY UZYCIA FILTRA, RAPORTU i NOTYFIKATORA na podstawie interfejsów
    FiltrStub filtrStub;
    testFiltrowania(&filtrStub, &lista);

    RaportStub raportStub;
    testRaportu(&raportStub, &lista);

    NotyfikatorStub notyfikatorStub;
    testNotyfikatora(&notyfikatorStub, &lista);

    // --- Test IFiltr ---
    // WYKORZYSTAJ FILTR ZAIMPLEMENTOWANY PRZEZ INNA GRUPE

    // --- Test INotyfikator ---
    // WYKORZYSTAJ NOTYFIKATOR ZAIMPLEMENTOWANY PRZEZ INNA GRUPE
    
    NotyfikatorKonsola notyfikatorKonsola;
    testNotyfikatora(&notyfikatorKonsola, &lista);

    // --- Test IRaport ---
       // WYKORZYSTAJ RAPORT ZAIMPLEMENTOWANY PRZEZ INNA GRUPE

    RaportZagrozonych raportZagrozonych;
    testRaportu(&raportZagrozonych, &lista);
    
    return 0;
}
