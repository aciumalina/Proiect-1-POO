#include <iostream>
#include <ctime>
#include <cstring>
using namespace std;

class Serviciu;


class Doctor
{
    char* nume;    //cu const sau fara? cum se lucreaza cu char*?
    string prenume;
    string specializare;
    float rating;

public:
    void setNume(char* nume)     //setter nume, care este char*
    {
        if(this->nume != nullptr)
        {
            delete[] this->nume;
        }
        this->nume = nume;
    }

    void setPrenume(string prenume)                 //setter prenume
    {
        this->prenume = prenume;
    }

    char* getNume()                                //getter nume
    {
        return nume;
    }

    string getPrenume()                             //getter prenume
    {
        return prenume;
    }

    void setSpecializare(string specializare)                   //setter specializare
    {
        this->specializare = specializare;
    }

    string getSpecializare()                                    //getter specializare
    {
        return specializare;
    }

    void setRating(float rating)
    {this->rating = rating;}

    float getRating()
    {return rating;}


    Doctor()                                                                //constructor fara parametri
    {
        nume=new char[strlen("Anonim")+1];
        strcpy( this->nume,"Anonim");
        prenume = "Anonim";
        specializare = "Necunoscut";
        rating = 0;
    }
    Doctor(char* nume, string prenume, string specializare, float rating)    //constructor cu toti parametrii !!!!NU UITA CA O SA MAI NECESITE MODIFICARI daca adaugi variabile
    {
        this->nume = nume;
        this->prenume = prenume;
        this->specializare = specializare;
        this->rating = rating;
    }

    ~Doctor() {                                                            //destructor Doctor, nu uita de eventualele modificari
        if (this->nume != nullptr) {
            delete[] nume;
        }
        prenume = "Anonim";
        specializare = "Necunoscut";
        rating = 0;
    }

    Doctor(const Doctor& d)                                             //copy-constructor pt doctor
    {
        this->nume=new char[strlen(d.nume)+1];
        strcpy( this->nume, d.nume);
        this->prenume = d.prenume;
        this->specializare = d.specializare;
        this->rating = d.rating;
    }

    Doctor& operator = (const Doctor &d)                                            //supraincarcarea operatorului = pentru class Doctor
    {
        if(this != &d)
        {
            if(this->nume != nullptr)
                delete[] this->nume;
            this->nume=new char[strlen(d.nume)+1];
            strcpy( this->nume, d.nume);
            this->prenume = d.prenume;
            this->specializare = d.specializare;
            this->rating = d.rating;
        }
        return *this;
    }
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class Pacient
{
    char* nume;
    string prenume;
    long long int nr_telefon;
    int varsta;
    char statut;             //va fi E pt elev, S pt student, P pensionar, X pentru persoana care nu se incadreaza in nicio categorie.
                             //Aceasta informatie Va folosi ulterior pentru Asigurare
    bool asigurare;          //asigurare pt studenti si elevi, care va oferi o reducere de 50% din tariful serviciilor

public:
    //friend void calcul_tarif(Pacient, Serviciu);
    void setNume(char* nume)           //setter nume pacient
    {
        if(this->nume != nullptr)
        {
            delete[] this->nume;
        }
        this->nume = nume;
    }
    char* getNume()                 //getter nume pacient
    {
        return nume;
    }

    void setPrenume(string prenume)               //setter prenume pacient
    {
        this->prenume = prenume;
    }

    string getPrenume()                             //getter prenume pacient
    {
        return prenume;
    }

    void setNumar(long long int nr_tel)                 //setter nr telefon
    {
        this->nr_telefon = nr_tel;
    }

    int getNumar()                                      //getter nr telefon
    {
        return this->nr_telefon;
    }

    void setVarsta(int varsta)                          //setter varsta
    {this->varsta = varsta;}

    int getVarsta()                                     //getter varsta
    {
        return varsta;
    }

    void setStatut(char statut)                         //setter statut
    {this->statut = statut;}

    void getStatut()                                    //getter statut
    {if (statut == 'E')
        cout<< "Elev";
        if (statut == 'S')
            cout << "Student";
        if (statut == 'P')
            cout << "Pensionar";
        if (statut == 'X')
            cout << "Persoana";
    }

    void setare_asigurare()                                  //functie pt a seta asigurarea(doar elevii si studentii au reducere 50%)
    {
        if (this->statut == 'E' || this->statut == 'S')
            this->asigurare = true;
        else { this->asigurare = false; }
    }

    bool getAsigurare()                                      //returneaza 1 daca e asigurat, 0 altfel
    {return this->asigurare;}

    Pacient()                                                //constructor fara parametri
    {
        nume=new char[strlen("Anonim")+1];
        strcpy( this->nume,"Anonim");
        this->prenume = "Anonim";
        this->nr_telefon = 0;
        this->varsta = 0;
        this->statut = ' ';
        this->asigurare = false;
    }

    Pacient(char *nume, string prenume,long long int nr_telefon,int varsta, char statut){   //constructor fara parametrul de asigurare
        this->nume=new char[strlen(nume)+1];
        strcpy( this->nume, nume);
        this->prenume = prenume;
        this->nr_telefon = nr_telefon;
        this->varsta = varsta;
        this->statut = statut;
    }
    Pacient(char *nume, string prenume,long long int nr_telefon,int varsta, char statut, bool asigurare){   //constructor cu toti parametrii
        this->nume=new char[strlen(nume)+1];
        strcpy( this->nume, nume);
        this->prenume = prenume;
        this->nr_telefon = nr_telefon;
        this->varsta = varsta;
        this->statut = statut;
        this->asigurare = asigurare;
    }

    ~Pacient() {                                                             //destructor pacient
        if (this->nume != nullptr)
            delete[] nume;
        this->prenume = "Anonim";
        this->nr_telefon = 0;
        this->varsta = 0;
        this->statut = ' ';
        this->asigurare = false;
    }

    Pacient(const Pacient& p)                                           //copy-constructor
    {
        this->nume=new char[strlen(p.nume)+1];
        strcpy( this->nume, p.nume);
        this->prenume = p.prenume;
        this->varsta = p.varsta;
        this->nr_telefon = p.nr_telefon;
        this->statut = p.statut;
        this->asigurare = p.asigurare;
    }

    Pacient& operator = (const Pacient& p)                              //supraincarcare operator = pentru Pacient
    {
        if(this != &p)
        {
            if(this->nume != nullptr)
                delete[] this->nume;
            this->nume=new char[strlen(p.nume)+1];
            strcpy( this->nume, p.nume);
            this->prenume = p.prenume;
            this->varsta = p.varsta;
            this->nr_telefon = p.nr_telefon;
            this->statut = p.statut;
            this->asigurare = p.asigurare;
        }
        return *this;
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Programare
{
    int ora, ziua, luna, an;
public:
    friend class Doctor;
    friend class Pacient;

    Programare()                                        //constructor fara parametri, va lua data curenta (cod luat de pe Stack Overflow - https://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c)
    {
        time_t t = time(nullptr);   // get time now
        tm* now = localtime(&t);
        this->ora = 0;
        this->an = now->tm_year + 1900;
        this->luna = now->tm_mon + 1;
        this->ziua = now->tm_mday;
    }
    Programare(int ora, int ziua, int luna, int an)    //constructor cu toti parametri
    {
        this->ora = ora;
        this->ziua = ziua;
        this->luna = luna;
        this->an= an;
    }
    ~Programare()                                       //destructor
    {
        ora = ziua = luna = an = 0;
    }
        void citire_programare()                                     //functie pentru introducerea unei date in sistem pentru a face o programare
        {
            cout<<"Introduceti ora dorita(24-hour format): "<<endl;
            cin>>this->ora;
            cout<< "Introduceti ziua dorita: "<<endl;
            cin>>this->ziua;
            cout<<"Introduceti luna dorita: "<<endl;
            cin>>this->luna;
            cout<<"Introduceti anul: "<<endl;
            cin>>this->an;
            cout<<"Ati selectat data de "<<ziua<< "/"<<luna<<"/"<<an<< " ora " << ora;
        }

        Programare(const Programare &prog)                                        //copy-constructor
        {
        this->ora = prog.ora;
        this->ziua = prog.ziua;
        this->luna = prog.luna;
        this->an = prog.an;
        }

        Programare& operator = (const Programare& prog)                         //supraincarcarea = pentru clasa Programare
        {
            if(this != &prog)
            {
                this->ora = prog.ora;
                this->ziua = prog.ziua;
                this->luna = prog.luna;
                this->an = prog.an;
            }
            return *this;
        }

    int getZiua()
    {return this->ziua;}
};


class Serviciu
{
    string serviciu_oferit;                        //analize, consultatie, interpretare analize, investigatii, control, ecografie
    double tarif;
    float reducere;

public:
    friend class Doctor;
    friend void calcul_tarif(Pacient, Serviciu);            //declarata in afara claselor

    Serviciu()                                                          //constructor fara parametri
    {
        serviciu_oferit = "";
        tarif = 0;
        reducere = 0;
    }

    Serviciu(string serviciu_oferit, double tarif)                          //constructor cu 2 parametri, fara reducere
    {
        this->serviciu_oferit = serviciu_oferit;
        this->tarif = tarif;
    }

    Serviciu(string serviciu_oferit, double tarif, float reducere)          //constructor cu toti parametri
    {
        this->serviciu_oferit = serviciu_oferit;
        this->tarif = tarif;
        this->reducere = reducere;
    }

    ~Serviciu()                                                             //destructor
    {
        serviciu_oferit = "";
        tarif = 0;
        reducere = 0;
    }

    Serviciu(const Serviciu& s)                                             //copy-constructor
    {
        this->serviciu_oferit = s.serviciu_oferit;
        this->tarif = s.tarif;
        this->reducere = s.reducere;
    }

    double getTarif()                                                   //functie de getter pt tarif, calculat in functie de reducere (reducere obtinuta in fuctie de statutul pacientului)
    {
        if (reducere == 0.5)
        {this ->tarif = this->tarif * 0.5; return this->tarif;}
        else return this->tarif;
    }

    Serviciu& operator = (const Serviciu& serv)                                //supraincarcarea operatorului = pentru Serviciu
    {
        if(this != &serv)
        {
            this->serviciu_oferit = serv.serviciu_oferit;
            this->tarif = serv.tarif;
            this->reducere = serv.reducere;
        }
        return *this;
    }
};
//void calcul_tarif(Pacient p1, Serviciu s1)                            //functia care reduce cu 50% tariful unui serviciu pentru studenti si elevi, nu stiu daca are sens
//{
//    if (!p1.asigurare)
//        s1.tarif = s1.tarif;
//    else s1.tarif = s1.tarif * 0.5;
//}

int main()
{
    Pacient p("Pop", "Ion", 333, 18, 'E');
    //p.getStatut();
    //Doctor d("Popescu", "gigel", "alal", 4.7);
    //p.setare_asigurare();
    Programare pr;
    Serviciu serv("consultatie", 120), serv1;
    //calcul_tarif(p, serv);
    serv1 = serv;
    cout<<serv1.getTarif();

    return 0;
}

