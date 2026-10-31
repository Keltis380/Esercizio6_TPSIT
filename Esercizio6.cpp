#include <iostream>
#include <string>
using namespace std;

class Materiale {
protected:
    string codice, titolo;
    int anno;

    virtual string dettaglio() const = 0;
    virtual int durataPrestito() const = 0;
    virtual double moraGiornaliera() const = 0;

public:
    Materiale(string c, string t, int a)
        : codice(c), titolo(t), anno(a) {}

    virtual ~Materiale() {}

    void descrizione() const {
        cout << "[" << codice << "] " << titolo << " (" << anno << "), " << dettaglio() << " - prestito " << durataPrestito() << " giorni" << endl;
    }

    double calcolaMora(int giorni) const {
        if (giorni <= 0) return 0;
        return giorni * moraGiornaliera();
    }
};

class Libro : public Materiale { int pagine;

protected:
    string dettaglio() const override { return to_string(pagine) + " pagine"; }

    int durataPrestito() const override { return 30; }

    double moraGiornaliera() const override { return 0.10; }

public:
    Libro(string c, string t, int a, int p) : Materiale(c, t, a), pagine(p) {}
};

class DVD : public Materiale { int minuti;

protected:
    string dettaglio() const override { return to_string(minuti) + " minuti"; }

    int durataPrestito() const override { return 7; }

    double moraGiornaliera() const override { return 0.50; }

public: DVD(string c, string t, int a, int m) : Materiale(c, t, a), minuti(m) {}
};

class Rivista : public Materiale {
    int numero;

protected: string dettaglio() const override { return "n. " + to_string(numero); }
    int durataPrestito() const override { return 14; }
    double moraGiornaliera() const override { return 0.20; }

public: Rivista(string c, string t, int a, int n) : Materiale(c, t, a), numero(n) {}
};

int main() {
    Materiale* materiali[4];
    materiali[0] = new Libro("L01", "I promessi sposi", 1827, 720);
    materiali[1] = new DVD("D01", "Il sorpasso", 1962, 105);
    materiali[2] = new Rivista("R01", "Informatica Oggi", 2026, 12);
    materiali[3] = new Libro("L02", "Il nome della rosa", 1980, 512);
    double totale = 0;

    for (int i = 0; i < 4; i++) {
        materiali[i]->descrizione();
        double mora = materiali[i]->calcolaMora(10);
        cout << "Mora: " << mora << " euro" << endl;
        totale += mora;
    }

    cout << "Mora totale: " << totale << " euro" << endl;
    for (int i = 0; i < 4; i++) {
        delete materiali[i];
    }

    return 0;
}