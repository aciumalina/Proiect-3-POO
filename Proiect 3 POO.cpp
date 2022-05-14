#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <exception>
#include <fstream>
#include <sstream>
using namespace std;

class Personal
{
protected:
    string nume;
    string prenume;
    string cnp;
    int cod;

public:
    Personal();                                                                 //constructorul fara parametri
    Personal(string nume, string prenume, string cnp, int cod);                   //constructor cu toti parametri
    Personal(const Personal &p);                                                //copy-constructor
    Personal& operator = (const Personal &p);                                   //supraincarcare atribuire
    virtual ~Personal();                                                                //destructor
    friend istream& operator >> (istream& in, Personal& p);
    friend ostream& operator << (ostream& out, const Personal& p);
    virtual void afisareGen() const;                                              //metoda care face clasa abstracta

    virtual istream& citire(istream& in)                            //citirea
    {
        cout << "Introduceti numele"<<endl;
        in >> this->nume;
        cout << "Introduceti prenumele" << endl;
        in >> this->prenume;
        cout << "Introduceti CNP-ul " << endl;
        in >> this->cnp;
        cout << "Introduceti codul unic " << endl;
        in >> this->cod;

        return in;
    }

    virtual ostream& afisare(ostream& out) const                    //afisarea
    {
        out << "Numele este " << this->nume << endl;
        out << "Prenumele este " << this->prenume << endl;
        out << "CNP-ul este " << this->cnp << endl;

        return out;
    }

    string getNume() const {return this->nume;}                       //getter pt nume
    int getCod() const {return this->cod;}                            //getter pt cod
    void setNume(string nume) {this->nume = nume;}              //setter pt nume

    friend bool operator< (const Personal &left, const Personal &right)
    {
        return left.nume < right.nume;
    }

    virtual bool operator > (const Personal& p)                        //supraincarcare < care compara in functie de tarif
    {
        if (this->nume > p.nume)
            return true;
        return false;
    }
};

Personal::Personal() {
    this->nume = "Anonim";
    this->prenume = "Anonim";
    this->cnp = "Necunoscut";
    this->cod = 0;
}

Personal::Personal(string nume, string prenume, string cnp, int cod) {
    this->nume = nume;
    this->prenume = prenume;
    this->cnp = cnp;
    this->cod = cod;
}

Personal::Personal(const Personal &p) {
    this->nume = p.nume;
    this->prenume = p.prenume;
    this->cnp = p.cnp;
    this->cod = p.cod;
}

Personal& Personal::operator = (const Personal &p)
{
    if(this!= &p)
    {
        this->nume = p.nume;
        this->prenume = p.prenume;
        this->cnp = p.cnp;
        this->cod = p.cod;
    }
    return *this;
}

void Personal::afisareGen() const {
    char cifra = (this->cnp)[0];
    int c = cifra - '0';
    if(c % 2 == 0) cout << "Personalul auxiliar cu numele " << this->nume << " " << this->prenume << " este de gen Feminin" << endl;
    else cout << "Personalul auxiliar cu numele " << this->nume << " " << this->prenume << " este de gen Masculin" << endl;
}

Personal::~Personal() {
    this->nume = "Anonim";
    this->prenume = "Invalid";
    this->cnp = "Invalid";
    this->cod = 0;
}

istream& operator >> (istream& in, Personal& p)
{
    return p.citire(in);
}

ostream& operator << (ostream& out, const Personal& p)
{
    return p.afisare(out);
}

class Pacient: virtual public Personal
{
protected:
    int varsta;
    bool asigurare;

public:
    Pacient();                                                  //constructor fara parametri
    Pacient(string nume, string prenume, string cnp, int cod, int varsta, bool asigurare);             //constructor cu toti parametri
    Pacient(const Pacient& pac);                                                            //copy-constructor
    Pacient& operator = (const Pacient &pac);                                           //supraincarcare =
    virtual ~Pacient();
    void afisareGen() const;                                                              //una dintre functionalitatile clasei
    void filtrareVarsta(int v1, int v2) const;                                                          //a doua functionalitate a clasei care filtreaza pacientii dupa varsta

    virtual istream& citire(istream& in)
    {
        Personal::citire(in);
        cout << "Introduceti varsta pacientului " << endl;
        in >> this-> varsta;
        cout << "Precizati daca pacientul este asigurat[1/0] " << endl;
        in >> this->asigurare;

        return in;
    }

    virtual ostream& afisare(ostream& out) const
    {
        Personal::afisare(out);
        out << "Varsta pacientului este " << this->varsta << endl;
        if(!this->asigurare) out << "Pacientul nu are asigurare " << endl;
        else out << "Pacientul are asigurare " << endl;

        return out;
    }

    virtual bool operator > (const Pacient& p)                        //supraincarcare < care compara in functie de varsta
    {
        if (this->varsta > p.varsta)
            return true;
        return false;
    }
};

Pacient::~Pacient()
{
    this->asigurare = false;
    this->varsta = 0;
}

Pacient::Pacient(): Personal() {
    this->varsta = 0;
    this->asigurare = false;
}

Pacient::Pacient(string nume, string prenume, string cnp, int cod, int varsta, bool asigurare): Personal(nume, prenume, cnp, cod)
{
    this->varsta = varsta;
    this->asigurare = asigurare;
}

Pacient::Pacient(const Pacient &pac): Personal(pac) {
    this->varsta = pac.varsta;
    this->asigurare = pac.asigurare;
}

Pacient& Pacient::operator=(const Pacient &pac) {
    if(this != &pac)
    {
        Personal::operator=(pac);
        this->varsta = pac.varsta;
        this->asigurare = pac.asigurare;
    }
    return *this;
}

void Pacient::afisareGen() const {
    char cifra = (this->cnp)[0];
    int c = cifra - '0';
    if(c % 2 == 0) cout << "Pacientul " << this->nume << " " << this->prenume << " este de gen Feminin" << endl;
    else cout << "Pacientul " << this->nume << " " << this->prenume << " este de gen Masculin" << endl;
}

void Pacient::filtrareVarsta(int v1, int v2) const {
    if (this->varsta >= v1 && this->varsta <= v2)
        cout << this->nume << " " <<this->prenume <<endl;
}

class Doctor: virtual public Personal
{
protected:
    float rating;
    string specializare;
    int anulAngajarii;

public:
    Doctor();
    Doctor(string nume, string prenume, string cnp, int cod, float rating, string specializare, int anulAngajarii);
    Doctor(const Doctor& d);
    Doctor& operator = (const Doctor& d);
    void afisareGen() const;                                                                 //prima functionalitate a clasei
    virtual ~Doctor();

    void filtruDoctor(string specializare, float rating) const;                       //ilustrare functionalitate clasa Doctor (cautare doctori dupa specializare, avand peste un anumit rating)


    virtual istream& citire(istream& in)
    {
        Personal::citire(in);
        cout << "Introduceti rating-ul " << endl;
        in >> this->rating;
        cout << "Introduceti specializarea " << endl;
        in >> this->specializare;
        cout << "Introduceti anul angajarii" << endl;
        in >> this->anulAngajarii;

        return in;
    }

    virtual ostream& afisare(ostream& out) const
    {
        Personal::afisare(out);
        out << "Rating-ul este " << this->rating << endl;
        out << "Specializarea este " << this->specializare << endl;
        out << "Anul angajarii este " << this->anulAngajarii << endl;

        return out;
    }

    bool operator > (const Doctor& d)                        //supraincarcare < care compara in functie de rating
    {
        if (this->rating > d.rating)
            return true;
        return false;
    }

};

Doctor::Doctor(): Personal()
{
    this->rating = 0;
    this->specializare = "Necunoscut";
    this->anulAngajarii = 0;
}

Doctor::Doctor(string nume, string prenume, string cnp,int cod, float rating, string specializare, int anulAngajarii): Personal(nume, prenume, cnp, cod)
{
    this->rating = rating;
    this->specializare = specializare;
    this->anulAngajarii = anulAngajarii;
}

Doctor::Doctor(const Doctor& d): Personal(d)
{
    this->rating = d.rating;
    this->specializare = d.specializare;
    this->anulAngajarii = d.anulAngajarii;
}

Doctor& Doctor::operator=(const Doctor &d) {

    if(this != &d)
    {
        Personal::operator=(d);
        this->rating = d.rating;
        this->specializare = d.specializare;
        this->anulAngajarii = d.anulAngajarii;
    }

    return *this;
}

Doctor::~Doctor()
{
    this->specializare = "Invalid";
    this->rating = 0;
    this->anulAngajarii = 0;
}

void Doctor::afisareGen() const {
    char cifra = (this->cnp)[0];
    int c = cifra - '0';
    if(c % 2 == 0) cout << "Doctorul este de gen Feminin" << endl;
    else cout << "Doctorul este de gen Masculin" << endl;
}

void Doctor::filtruDoctor(string specializare, float rating) const
{
    if (this->specializare == specializare && this->rating >= rating)
    {
        cout<<nume<<" "<<prenume<<endl;
    }
}

class PacientSiDoctor: virtual public Doctor, virtual public Pacient
{
private:
    int discount;

public:
    PacientSiDoctor(): Pacient(), Doctor(), Personal()                       //constructor fara parametri
    {
        this->discount = 0;
    }

    //constructor cu toti parametri
    PacientSiDoctor(const string &nume, const string &prenume, const string &cnp, int cod, int varsta, bool asigurare, float rating, const string &specializare, int anulAngajarii, int discount): Personal(nume, prenume, cnp, cod), Pacient(nume, prenume, cnp, cod, varsta, asigurare), Doctor(nume, prenume, cnp, cod, rating, specializare, anulAngajarii)
    {
        this->discount = discount;
    }

    PacientSiDoctor(const PacientSiDoctor& pd): Personal(pd), Pacient(pd), Doctor(pd)                //copy-constructor
    {
        this->discount = pd.discount;
    }

    PacientSiDoctor& operator = (const PacientSiDoctor& pd)                                     //operator =
    {
        if(this != &pd)
        {
            Pacient::operator = (pd);
            this->rating = pd.rating;
            this->specializare = pd.specializare;
            this->anulAngajarii = pd.anulAngajarii;
            this->discount = pd.discount;
        }
        return *this;
    }

    ~PacientSiDoctor()
    {
        this->discount = 0;
    }


    virtual istream& citire(istream& in)
    {
        Pacient::citire(in);
        cout << "Introduceti rating-ul " << endl;
        in >> this->rating;
        cout << "Introduceti specializarea " << endl;
        in >> this->specializare;
        cout << "Introduceti anul angajarii " <<endl;
        in >> this->anulAngajarii;
        cout << "Introduceti discount-ul aditional pentru servicii " <<endl;
        in >> this->discount;

        return in;
    }

    virtual ostream& afisare(ostream& out) const
    {
        Pacient::afisare(out);
        out << "Rating-ul este " << this->rating << endl;
        out << "Specializarea este " << this->specializare << endl;
        out << "Anul angajarii este " << this->anulAngajarii << endl;
        out << "Discount-ul aditional pentru servicii este de " << this->discount << "%" <<endl;

        return out;
    }

    void afisareGen() const{
        char cifra = (this->cnp)[0];
        int c = cifra - '0';
        if(c % 2 == 0) cout << "Personal este de gen Feminin" << endl;
        else cout << "Personal este de gen Masculin" << endl;
    }

    void calculReducereExtra() const                              //functionalitate clasa, calculeaza in functie de anii de vechime daca doctorii pot beneficia de alte reduceri la serviciile spitalului
    {
        time_t t = time(nullptr);
        tm* now = localtime(&t);
        int aniLucru = (now->tm_year + 1900) - this->anulAngajarii;
        if(aniLucru <= 3) cout << "Doctorul nu are suficienti ani de vechime pentru a beneficia de un discount aditional " << endl;
        else if (aniLucru <= 7) cout << "In calitate de pacient, doctorul " << this->nume << " " <<this->prenume <<" va beneficia de un discount extra de 20% la serviciile oferite" << endl;
        else cout << "In calitate de pacient, doctorul " << this->nume << " " <<this->prenume <<" va beneficia de un discount extra de 35% la serviciile oferite" << endl;
    }
};


class Serviciu
{
    string serviciu_oferit;                                 //analize, consultatie, interpretare analize, investigatii, control, ecografie etc
    int tarifTotal;
    float reducere;

public:
    Serviciu()                                                         //constructor fara parametri
    {
        serviciu_oferit = "";
        tarifTotal = 0;
        reducere = 0;
    }

    Serviciu(const string& serviciu_oferit, int tarif, float reducere)          //constructor cu toti parametri
    {
        this->serviciu_oferit = serviciu_oferit;
        if (reducere == 0)
            this->tarifTotal = tarif;
        else this->tarifTotal = reducere * tarif;
        this->reducere = reducere;
    }

    ~Serviciu()                                                             //destructor
    {
        serviciu_oferit = "";
        tarifTotal = 0;
        reducere = 0;
    }

    Serviciu(const Serviciu& s)                                            //copy-constructor
    {
        this->serviciu_oferit = s.serviciu_oferit;
        this->tarifTotal = s.tarifTotal;
        this->reducere = s.reducere;
    }

    Serviciu& operator = (const Serviciu& serv)                                //supraincarcarea operatorului = pentru Serviciu
    {
        if(this != &serv)
        {
            this->serviciu_oferit = serv.serviciu_oferit;
            this->tarifTotal = serv.tarifTotal;
            this->reducere = serv.reducere;

        }
        return *this;
    }

    friend ostream& operator << (ostream& out, const Serviciu& serv)                 //afisare
    {
        out<<"Serviciul oferit este " <<serv.serviciu_oferit<<endl;
        out<<"Tariful serviciului este " <<serv.tarifTotal<<endl;
        out<< "Reducerea serviciul este de " << serv.reducere<<endl;
        return out;
    }

    friend istream& operator >> (istream& in, Serviciu& serv)                        //citire
    {
        cout << "Serviciul oferit este: "<<endl;
        in>>serv.serviciu_oferit;
        cout << "Tariful serviciului este de: "<<endl;
        in >> serv.tarifTotal;
        cout << "Reducerea acordata este de: "<<endl;
        in >>serv.reducere;

        if (serv.reducere == 0) serv.tarifTotal = serv.tarifTotal;
        else serv.tarifTotal = serv.tarifTotal * (1-serv.reducere);
        return in;
    }

    void impartireTarif() const                                                   //functionalitate a clasei, din tariful total calculeaza si afiseaza TVA si pretul brut
    {
        cout<<"TVA-ul serviciului oferit este " << (this->tarifTotal * 9)/100 << " RON"<<endl;
        cout << "Tariful brut al serviciului este " << (this->tarifTotal * 91)/100 << " RON"<< endl;
    }

    string getServiciu_oferit(){return serviciu_oferit;}                //getter pt serviciul oferit
    void setServiciu(string serviciu){this->serviciu_oferit = serviciu;}            //setter serviciu oferit

    bool operator > (const Serviciu& s)                        //supraincarcare < care compara in functie de tarif
    {
        if (this->tarifTotal > s.tarifTotal)
            return true;
        return false;
    }
};

#include <iostream>

template <class T, class U>
class LinkedList
{
    struct Node
    {
        T data;
        U cuvant;
        Node * next;
        Node(T val, U cuv): data(val), cuvant(cuv), next(nullptr){}
    };
    Node *head;

public:
    LinkedList(): head(nullptr){}
    LinkedList(const LinkedList<T,U> & ll) = delete;
    LinkedList& operator=(LinkedList const&) = delete;
    ~LinkedList();
    void insert(T,U);
    void afisare(ostream& out) const
    {
        Node *node = head;
        while(node != nullptr)
        {
            out << node->data << " " << node->cuvant<<endl;
            node = node->next;
        }
    }
    template <class X, class Y>
    friend ostream& operator<<(ostream &out, const LinkedList<T,U> &ll);

    Node* popFront()
    {
        Node *nod = nullptr;
        if(head != nullptr) {
            Node* deSters = head;
            head = head->next;
            nod = deSters;
        }
        return nod;
    }
};

template <class T,class U>
ostream & operator<<(ostream & out, const LinkedList<T,U> &ll)
{
    ll.afisare(out);
    return out;
}

template <class T, class U>
void LinkedList<T,U>::insert(T data, U cuv)
{
    Node *t = new Node(data,cuv);
    Node *tmp = head;
    if (tmp == nullptr)
    {
        head = t;
    }
    else
    {
        while (tmp->next != nullptr)
        {
            tmp = tmp->next;
        }
        tmp->next = t;
    }
}

template <class T, class U>
LinkedList<T,U>::~LinkedList()
{
    Node *tmp = nullptr;
    while (head)
    {
        tmp = head;
        head = head->next;
        delete tmp;
    }
    head =nullptr;
}



class Meniu{
    static Meniu* instance;
    Meniu(){}
    Meniu(const Meniu& m) = delete;
//    Meniu(Meniu& m) noexcept = delete;

    vector<Doctor*> doctor;
    list<Pacient> pacienti;
    set<Personal> personal;
    map<int, Serviciu> servicii;

public:
    ~Meniu();
    static Meniu *getInstance()
    {
        if(!instance)
            instance = new Meniu();

        return instance;
    }

    template <class T>
    T maxim(T ob1, T ob2)
    {
        if(ob1 > ob2) return ob1;
        else return ob2;
    }

    void adaugare();
    void stergere();
    void afisare();
    void comparare();
    void filtruDoc();
    void filtruPac();
    void filtruServ();
    void discoutAditional();
    void citireFisier();
    void exportaDate();
    void processFile(ifstream& inFile);
};

Meniu* Meniu::instance = nullptr;

void Meniu::adaugare()
{
    cout << "Alegeti sectiunea in care doriti sa adaugati date: 1-Personal, 2-Pacient, 3-Doctor, 4-Servicii" << endl;
    int opt;
    cin >> opt;
    if (opt == 1) {
        cout << "Introduceti datele personalului auxiliar" << endl;
        Personal p;
        cin >> p;
        personal.insert(p);
    }
    else if (opt == 2) {
        cout << "Introduceti datele pacientului" << endl;
        Pacient p;
        cin >> p;
        pacienti.push_back(p);
    } else if (opt == 3) {
        cout << "Precizati daca doriti sa introduceti un doctor(1) sau un doctor care este si pacient(2)"
             << endl;
        int nr;
        cin >> nr;
        Doctor *d = nullptr;
        if (nr == 1) {
            d = new Doctor();
        } else if (nr == 2) {
            d = new PacientSiDoctor();
        }
        if (d) {
            cin >> *d;
            doctor.push_back(d);
        }

    } else if (opt == 4) {
        cout << "Introduceti datele serviciului dorit" << endl;
        Serviciu s;
        cin >> s;
        cout << "Introduceti o cheie unica de identificare" << endl;
        int cheie;
        cin >> cheie;
        servicii.emplace(pair<int, Serviciu>(cheie, s));

    }
}

void Meniu::stergere()
{
    cout << "Alegeti din ce sectiune doriti sa stergeti date: 1-Personal, 2-Pacient, 3-Doctor, 4-Servicii"<< endl;
    int nr;
    cin >> nr;
    if(nr == 1){
        cout<<"Introduceti codul personalului auxiliar"<<endl;
        int cod;
        cin >> cod;
        set<Personal>::iterator itr;
        for (itr = personal.begin(); itr != personal.end(); itr++) {
            if(itr->getCod() == cod) {
                personal.erase(itr);
                cout<<"Persoana a fost stersa din sistem"<<endl;
            }
        }
        if (itr == personal.end()) cout <<"Nu s-a gasit nicio persoana cu codul introdus"<<endl;
    }
    else if(nr == 2)
    {
        cout << "Introduceti codul pacientului "<<endl;
        int cod;
        cin >> cod;
        list<Pacient>::iterator it;
        for (it = pacienti.begin(); it != pacienti.end(); ++it)
            if(it->getCod() == cod) {
                pacienti.erase(it);
                cout<<"Pacientul a fost sters din sistem"<<endl;
            }
        if(it == pacienti.end()) cout << "Nu s-a gasit niciun pacient cu codul introdus"<<endl;
    }
    else if(nr == 3)
    {
        cout<<"Introduceti codul doctorului"<<endl;
        int cod,it;
        cin >> cod;
        for (it = 0; it != doctor.size(); it++)
            if(doctor[it]->getCod()== cod)
            {
                doctor.erase(doctor.begin() + it);
                cout<<"Doctorul a fost sters"<<endl;
            }
        if (it == doctor.size()) cout <<"Nu a fost gasit niciun doctor cu codul introdus"<<endl;
    }
    else if(nr == 4)
    {
        cout <<"Introduceti cheia serviciului"<<endl;
        int cheie;
        cin >> cheie;
        try {
            if(!servicii.erase(cheie)) throw 0;
            else{
                servicii.erase(cheie);
                cout<<"Serviciul a fost sters"<<endl;
            }
        }
        catch(int x)
        {
            cout<<"Nu s-a gasit niciun serviciu cu cheia introdusa"<<endl;
        }
    }
}

void Meniu::afisare()
{
    while(1){
        cout<< "Alegeti din ce sectiune doriti sa afisati date: 1-Personal, 2-Pacient, 3-Doctor, 4-Servicii, 5-Revenire Meniu Principal"<< endl;
        try{
            int nr;
            cin >> nr;
            if(nr < 1 || nr > 5) throw nr;
            else {
                if (nr == 1) {
                    set<Personal>::iterator itr;
                    for (itr = personal.begin(); itr != personal.end(); itr++) {
                        cout << *itr << endl;
                    }
                    break;
                } else if (nr == 2) {
                    list<Pacient>::iterator it;
                    for (it = pacienti.begin(); it != pacienti.end(); ++it)
                        cout << *it << endl;
                    break;
                } else if (nr == 3) {
                    for (auto it = doctor.begin(); it != doctor.end(); it++)
                        cout << *it << endl;
                    break;
                } else if (nr == 4) {
                    map<int, Serviciu>::iterator itr;
                    for (itr = servicii.begin(); itr != servicii.end(); ++itr) {
                        cout << itr->second << endl;
                    }
                    break;
                }
                else if (nr == 5) break;
            }
        }
        catch(int x)
        {
            cout<<"Optiunea " << x << " nu este valida"<<endl;
        }
    }
}

void Meniu::comparare()
{
    cout << "Alegeti sectiunea din care doriti sa comparati date: 1-Personal, 2-Pacient, 3-Doctor, 4-Servicii "<<endl;
    int nr;
    cin >> nr;
    if(nr == 1){
        cout<<"Introduceti codul primei persoane"<<endl;
        int cod1, cod2;
        cin >> cod1;
        cout<<"Introduceti codul celei de-a doua persoane"<<endl;
        cin >> cod2;
        set<Personal>::iterator itr1;
        set<Personal>::iterator itr2;
        for (itr1 = personal.begin(); itr1 != personal.end(); itr1++) {
            if(itr1->getCod() == cod1) break;
        }
        for (itr2 = personal.begin(); itr2 != personal.end(); itr2++) {
            if(itr2->getCod() == cod2) break;
        }
        try {
            if(itr1 == personal.end() || itr2 == personal.end())
                throw string("Coduri introduse incorect");
            else
            {
                cout<<"In ordonarea alfabetica "<<maxim(*itr1, *itr2).getNume() << " este in fata"<<endl;
            }
        }
        catch(string s){cout << s << endl;}
    }
    else if(nr==2){
        cout<<"Introduceti codul primului pacient"<<endl;
        int cod1, cod2;
        cin >> cod1;
        cout<<"Introduceti codul celei de-al doilea pacient"<<endl;
        cin >> cod2;
        list<Pacient>::iterator itr1;
        list<Pacient>::iterator itr2;
        for (itr1 = pacienti.begin(); itr1 != pacienti.end(); itr1++) {
            if(itr1->getCod() == cod1) break;
        }
        for (itr2 = pacienti.begin(); itr2 != pacienti.end(); itr2++) {
            if(itr2->getCod() == cod2) break;
        }
        try {
            if(itr1 == pacienti.end() || itr2 == pacienti.end())
                throw string("Coduri introduse incorect");
            else
            {
                cout<<maxim(*itr1, *itr2).getNume() << " este mai in varsta"<<endl;
            }
        }
        catch(string s){cout << s << endl;}
    }
    else if(nr == 3){
        cout<<"Introduceti codul primului doctor"<<endl;
        int cod1, cod2, i,j;
        cin >> cod1;
        cout<<"Introduceti codul celui de-al doilea doctor"<<endl;
        cin >> cod2;
        for (i = 0; i != doctor.size(); i++) {
            if(doctor[i]->getCod() == cod1) break;
        }
        for (j = 0; j != doctor.size(); j++) {
            if(doctor[j]->getCod() == cod2) break;
        }
        try {
            if(i == doctor.size() || j == doctor.size())
                throw string("Coduri introduse incorect");
            else
            {
                cout<<"Doctorul " << maxim(doctor[i], doctor[j])->getNume() << " are rating-ul mai mare"<<endl;
            }
        }
        catch(string s){cout << s << endl;}
    }
    else if (nr == 4){
        while(1){
            cout << "Introduceti cheia primului serviciu" << endl;
            int ch1;
            cin >> ch1;
            try {
                servicii.at(ch1);
            }
            catch (exception &) {
                cout << "Cheie introdusa gresit" << endl;
                break;
            }
            cout << "Introduceti cheia celui de-al doilea serviciu" << endl;
            int ch2;
            cin >> ch2;
            try {
                servicii.at(ch2);
            }
            catch(exception&)
            {
                cout<<"Cheie introdusa gresit"<<endl;
                break;
            }
            cout << "Tariful mai mare il are serviciul "
                 << maxim(servicii.at(ch1), servicii.at(ch2)).getServiciu_oferit() << endl;
            break;
        }
    }
}

void Meniu::filtruDoc() {
    cout<<"Introduceti specializarea pe care o cautati "<<endl;
    string specializare;
    cin >> specializare;
    cout << "Introduceti rating-ul minim al doctorului "<<endl;
    float rating;
    cin >>rating;
    for(int i = 0; i<doctor.size();i++)                         //pentru fiecare doctor voi trece prin functia de filtru pentru a vedea daca se incadreaza
    {
        doctor[i]->filtruDoctor(specializare,rating);
    }
}

void Meniu::filtruPac()
{
    int minim, maxim;
    cout << "Introduceti varsta minima"<<endl;
    cin >> minim;
    cout << "Introduceti varsta maxima" << endl;
    cin >> maxim;
    list<Pacient>::iterator it;
    for (it = pacienti.begin(); it != pacienti.end(); ++it)
    {
        it->filtrareVarsta(minim,maxim);
    }
}

void Meniu::filtruServ()
{
    int cod;
    cout << "Introduceti cheia serviciului pe care il cautati" << endl;
    cin >> cod;
    try
    {
        servicii.at(cod).impartireTarif();
    }
    catch(exception&)
    {
        cout<<"Cheia introdusa nu este valida"<<endl;
    }
}

void Meniu::discoutAditional()
{
    int cod,i;
    cout << "Introduceti codul doctorului pe care il cautati" << endl;
    cin >> cod;
    for(i = 0; i < doctor.size(); i++)
    {
        if(doctor[i]->getCod() == cod)
        {
            try{
                dynamic_cast<PacientSiDoctor&>(*doctor[i]).calculReducereExtra();
                break;
            }
            catch(bad_cast& e)
            {
                cout<<"Doctorul ales nu urmeaza tratament la acest spital"<<endl;
                break;
            }
        }
    }
    if(i == doctor.size()) cout <<"Nu s-a gasit niciun doctor cu codul introdus"<<endl;
}

void Meniu::processFile(ifstream& inFile)
{
    LinkedList<int, string> lista;
    int contor = 0;
    string line;
    string word;
    while(!inFile.eof())
    {
        getline(inFile, line);
        if(inFile.good())
        {
            int data;
            string cuvant;
            istringstream ss(line);
            while(ss >> word)
            {
                if(word.length() == 1) data = stoi(word);
                else cuvant = word;

            }
            contor++;
            lista.insert(data, cuvant);
        }
    }

    cout<<"In sistem se afla: "<<endl;
    cout << lista << endl;
}

void Meniu::citireFisier()
{
    ifstream inFile;
    inFile.open("C:\\Users\\Malina\\CLionProjects\\untitled\\input.txt");
    processFile(inFile);
    inFile.close();
}

void Meniu::exportaDate()
{
    ofstream MyFile("C:\\Users\\Malina\\CLionProjects\\untitled\\input.txt");
    MyFile << doctor.size() << " Doctori"<<endl;
    MyFile << pacienti.size() << " Pacienti"<<endl;
    MyFile << servicii.size() << " Servicii"<<endl;
    MyFile << personal.size() << " Personal"<<endl;
    MyFile.close();
    cout<<"Datele au fost transferate cu succes"<<endl;
}

Meniu::~Meniu()
{
    for(int i = 0; i < doctor.size(); i++)
        delete doctor[i];
    doctor.clear();

    list<Pacient>::iterator it;
    for (it = pacienti.begin(); it != pacienti.end(); ++it)
        pacienti.erase(it);
    pacienti.clear();

    map<int, Serviciu>::iterator itr;
    for(itr = servicii.begin(); itr != servicii.end(); ++itr)
    {
        servicii.erase(itr->first);
    }
    servicii.clear();

    for (auto itrt = personal.begin(); itrt != personal.end(); ++it)
        personal.erase(itrt);
    personal.clear();

}
//template<typename C, typename T = typename C::value_type>
//void ceva(C const& container)
//{
//    for (auto v : container) {
//        cout << v <<endl;
//    }
//}
//

//template<template<typename...> typename C>
//void foo(const C<string> &cont)
//{
//    for(string val: cont) {
//        cout << val << std::endl;
//    }
//}

//template<typename Iter>
//void foo(Iter begin, Iter end) {
//    using T = decltype(*begin);
//    std::for_each(begin, end, [] (const T & t)) {
//        std::cout << t << '\n';
//    }
//}


void optiuniMeniu()
{
    cout<<endl;
    cout<<"1. Pentru a introduce date noi in sistem"<<endl;                    //create
    cout<<"2. Pentru stergerea de date din sistem "<<endl;                     //delete
    cout<<"3. Pentru a afisa informatii "<<endl;                               //read
    cout <<"4. Pentru a compara datele din sistem"<<endl;
    cout << "5. Pentru a filtra doctorii dupa specializare si rating "<<endl;
    cout << "6. Pentru a filtra pacientii in functie de varsta" << endl;
    cout << "7. Pentru a afisa pretul brut si TVA-ul serviciilor oferite" <<endl;
    cout << "8. Pentru a calcula discount-ul aditional pentru un doctor care urmeaza tratament " << endl;
    cout << "9. Pentru a exporta date in fisier"<<endl;
    cout << "10. Pentru a importa date din fisier"<<endl;
    cout << "11. Pentru a inchide meniul" << endl;
}

int main()
{
    Meniu *m = m->getInstance();

    while(1)
    {
        try{
            optiuniMeniu();
            int nrOpt;
            cin >> nrOpt;
            if(nrOpt < 1 || nrOpt > 11)
                throw string("Optiune introdusa gresit");
            else {
                if (nrOpt == 1) {m->adaugare(); }
                else if (nrOpt == 2) { m->stergere(); }
                else if (nrOpt == 3) { m->afisare(); }
                else if (nrOpt == 4) {m->comparare(); }
                else if (nrOpt == 5) {m->filtruDoc();}
                else if (nrOpt == 6) {m->filtruPac();}
                else if (nrOpt == 7){m->filtruServ();}
                else if(nrOpt == 8){m->discoutAditional();}

                else if (nrOpt == 9) {m->exportaDate();}
                else if (nrOpt == 10) {m->citireFisier();}
                else if (nrOpt == 11) break;
            }
        }
        catch(string s){cout << s << endl;}

    }
    return 0;
}

