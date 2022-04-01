#include <iostream>
#include <ctime>
#include <cstring>
#include <vector>
using namespace std;

class Serviciu;

class Doctor
{
    char* nume;
    string prenume;
    string specializare;
    float rating;
    const int id_doctor;
    static int contor_doctor;

public:
    void filtruDoctor(string specializare, float rating)                       //ilustrare functionalitate clasa Doctor (cautare doctori dupa specializare, avand peste un anumit rating)
    {
        if (this->specializare == specializare && this->rating >= rating)
        {
            cout<<nume<<" "<<prenume<<endl;
        }
    }
    void setContor_doctor(int contor_doctor)                                //setter pentru contorul curent al doctorului
    {this->contor_doctor = contor_doctor;}

    static int getContor_doctor()                                             //getter pt contor
    {
        return contor_doctor;
    }

    int getId_doctor() const                                                  //getter pt ID-ul doctorului
    {
        return id_doctor;
    }
    void setNume(char* nume)                        //setter nume, care este char*
    {
        if(this->nume!=nullptr)
            delete[] this->nume;
        this->nume=new char[strlen(nume)+1];
        strcpy(this->nume,nume);
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


    Doctor():id_doctor(contor_doctor++)                                                                                //constructor fara parametri
    {
        nume=new char[strlen("Anonim")+1];
        strcpy( this->nume,"Anonim");
        prenume = "Anonim";
        specializare = "Necunoscut";
        rating = 0;
    }

    Doctor(char* nume, const string& prenume):id_doctor(contor_doctor++)                                           //constructor fara specializare si fara rating
    {
        this->nume=new char[strlen(nume)+1];
        strcpy( this->nume, nume);
        this->prenume = prenume;
        this->specializare = "Necunoscut";
        this->rating = 0;
    }

    Doctor(char* nume, const string& prenume, const string& specializare):id_doctor(contor_doctor++)                    //constructor fara rating
    {
        this->nume=new char[strlen(nume)+1];
        strcpy( this->nume, nume);
        this->prenume = prenume;
        this->specializare = specializare;
        this->rating = 0;
    }

    Doctor(char* nume, const string& prenume, const string& specializare, float rating):id_doctor(contor_doctor++)    //constructor cu toti parametrii !!!!NU UITA CA O SA MAI NECESITE MODIFICARI daca adaugi variabile
    {
        this->nume=new char[strlen(nume)+1];
        strcpy( this->nume, nume);
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

    Doctor(const Doctor& d) : id_doctor(d.id_doctor)                                            //copy-constructor pt doctor
    {
        this->nume=new char[strlen(d.nume)+1];
        strcpy( this->nume, d.nume);
        this->prenume = d.prenume;
        this->specializare = d.specializare;
        this->rating = d.rating;
    }

    Doctor& operator = (const Doctor &d)                                           //supraincarcarea operatorului = pentru class Doctor
    {
        if(this != &d)
        {
            if(this->nume != nullptr)
                delete[] this->nume;
            this->nume=new char[strlen(d.nume)+1];
            strcpy( this->nume, d.nume);
            this->nume[strlen(nume)] = '\0';
            this->prenume = d.prenume;
            this->specializare = d.specializare;
            this->rating = d.rating;

        }
        return *this;
    }

    Doctor operator++(){                                        //supraincarcarea ++ pentru clasa doctor, care va incrementa cu 0.1 rating-ul(forma prefix)
        rating = rating + 0.1;
        return *this;
    }

     const Doctor operator++(int) {                                        //supraincarcarea ++ pentru clasa doctor, care va incrementa cu 0.1 rating-ul(forma postifx)
        Doctor aux = *this;
        this->rating = this->rating + 0.1;
        return aux;
    }

    Doctor operator+(Doctor doc)                                //supraincarcare + pentru Doctor. Doctor + Doctor inseamna ca doi doctori vor colabora, li se vor aduna numele, prenumele si specializarea, se face media rating-ului
    {
        Doctor doc1;
        sprintf(doc1.nume,"%s si %s", doc.nume, nume);                  //luat de pe StackOverflow(https://stackoverflow.com/questions/2218290/concatenate-char-array-in-c)
        doc1.prenume = doc.prenume + " si " + prenume;
        doc1.specializare = doc.specializare + " si " + specializare;
        doc1.rating = (doc.rating + rating)/2;                                  //media rating-urilor
        return doc1;
    }

    Doctor operator+(float x)                                   //supraincarcare + pentru float
    {
        Doctor aux(*this);
        aux.rating = aux.rating + x;
        return aux;
    }

    friend Doctor operator+(float x, Doctor doc)                    //float x + doctor aduna valoarea respectiva la rating
    {
        doc.rating = doc.rating + x;
        return doc;
    }

    Doctor operator-(float x)                                   //doctor - x
    {
        Doctor aux(*this);
        aux.rating = aux.rating - x;
        return aux;
    }

    friend Doctor operator-(float x, Doctor doc)                    //x-doctor = doctor - x
    {
        doc.rating = doc.rating - x;
        return doc;
    }

    friend ostream& operator << (ostream& out, const Doctor& d)                 //supraincarcare <<
    {
        out<<"Numele doctorului este " <<d.nume<<endl;
        out<<"Prenumele doctorului este "<<d.prenume<<endl;
        out<<"Specializarea doctorului este "<<d.specializare<<endl;
        out<<"Rating-ul doctorului este "<<d.rating<<endl;
        out<<"Id-ul doctorului este " << d.id_doctor<<endl;                   //ar avea sens sa mai afisez si contorul??
        return out;
    }

    friend istream& operator >> (istream& in, Doctor& d)                        //supraincarcare >>
    {

        cout << "Numele doctorului este: ";
        char aux[100];
        in>>aux;
        if(d.nume!=nullptr)
            delete[] d.nume;
        d.nume=new char[strlen(aux)+1];
        strcpy(d.nume,aux);

        cout << "Prenumele doctorului este: ";
        in >> d.prenume;
        cout << "Specializarea doctorului este: ";
        in >> d.specializare;
        cout << "Rating-ul doctorului este: ";
        in >> d.rating;
        return in;
    }

    bool operator == (const Doctor& doc)                                //supraincarcare == (doi doctori sunt egali daca au acelasi nume si prenume)
    {
        if (strcmp(this->nume,doc.nume) == 0 && this->prenume == doc.prenume)
        {return true;}
        else return false;
    }

    bool operator < (const Doctor& doc)                        //supraincarcare < care compara in functie de rating
    {
        if (this->rating < doc.rating)
            return true;
        return false;
    }

    explicit operator int() {return (int)this->rating;}                 //cast explicit, returneaza rating-ul sub forma de int

};

int Doctor::contor_doctor = 0;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class Pacient
{
    char* nume;
    string prenume;
    string email;
    int varsta;

    bool asigurare;
    int* vizite_doctor_ultimul_an;
    char gen;                       //M, F sau N pt necunoscut

    const int cod_pacient;
    static int contor_pacient;

public:
    friend class Serviciu;
    void calculPachetPromotional()                             //functionalitate pentru clasa Pacient. Pe baza vectorului de frecventa cu vizitele la clinica, persoanele care intrunesc un anumit nr de vizite in ultimul an beneficiaza de pachete promotionale
    {
        int suma = 0;
        for(int i=0;i<12;i++)
            suma += vizite_doctor_ultimul_an[i];
        if (suma <= 5) cout << "Pacientul "<<nume<<" "<<prenume<<" nu se incadreaza pentru niciun pachet promotional";
        else if (suma <= 10) cout << "Pacientul "<<nume<<" "<<prenume<<" se incadreaza pentru pachetul Silver ce ii va conferi o reducere de 20%";
        else if(suma > 10) cout << "Pacientul "<<nume<<" "<<prenume<<" se incadreaza pentru pachetul Gold ce ii va conferi o reducere de 35%";
    }


    void setContor_pacient(int contor_pacient)                                //setter pentru contorul curent al pacientului
    {this->contor_pacient = contor_pacient;}

    static int getContor_pacient()                                             //getter pt contor
    {
        return contor_pacient;
    }

    int getCod_pacient()                                                  //getter pt codul pacientului
    {
        return cod_pacient;
    }
    void setNume(char* nume)                                            //setter nume pacient
    {
        if(this->nume!=nullptr)
            delete[] this->nume;
        this->nume=new char[strlen(nume)+1];
        strcpy(this->nume,nume);
    }
    char* getNume()                                 //getter nume pacient
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

    void setEmail(string email)                 //setter nr telefon
    {
        this->email = email;
    }

    string getEmail()                                      //getter nr telefon
    {
        return this->email;
    }

    void setVarsta(int varsta)                          //setter varsta
    {this->varsta = varsta;}

    int getVarsta()                                     //getter varsta
    {
        return varsta;
    }

    void setNr_vizite_doctor(int* vizite_doctor_ultimul_an)                        //setter vizite doctor
    {
        if(this->vizite_doctor_ultimul_an != nullptr)
        {
            delete[] this->vizite_doctor_ultimul_an;
        }
        this->vizite_doctor_ultimul_an = vizite_doctor_ultimul_an;
    }
    int* getNr_vizite_doctor()                                 //getter nr vizite doctor
    {
        return vizite_doctor_ultimul_an;
    }

    void setGen(char gen)                                       //setter pt gen
    {
        this->gen = gen;
    }

    char getGen()                                               //getter pt gen
    {return gen;}


    void setAsigurare(bool asigurare){
        this->asigurare = asigurare;
    }
    bool getAsigurare()                                      //returneaza 1 daca e asigurat, 0 altfel
    {return this->asigurare;}

    Pacient():cod_pacient(contor_pacient++)                                                //constructor fara parametri
    {
        nume=new char[strlen("Anonim")+1];
        strcpy( this->nume,"Anonim");
        this->prenume = "Anonim";
        this->email = "Necunoscut";
        this->varsta = 0;
        this->asigurare = false;
        this->vizite_doctor_ultimul_an = new int[12];
        for(int i = 0; i<12; i++)
        {this->vizite_doctor_ultimul_an[i] = 0;}
        this->gen = 'N';
    }

    Pacient(char *nume, const string& prenume, const string& email, int varsta):cod_pacient(contor_pacient++)                             //constructor fara asigurare si fara vizite la doctor si gen
    {
        this->nume=new char[strlen(nume)+1];
        strcpy( this->nume, nume);
        this->prenume =prenume;
        this->email = email;
        this->varsta = varsta;
        //this->statut = statut;
        this->asigurare = false;
        this->vizite_doctor_ultimul_an = new int[12];
        for(int i = 0; i<12; i++)
        {this->vizite_doctor_ultimul_an[i] = 0;}
        this->gen = 'N';

    }
    Pacient(char *nume,const string& prenume, const string& email, int varsta, bool asigurare):cod_pacient(contor_pacient++){          //constructor fara vizite la doctor si gen
        this->nume=new char[strlen(nume)+1];
        strcpy( this->nume, nume);
        this->prenume = prenume;
        this->email = email;
        this->varsta = varsta;
        //this->statut = statut;
        this->asigurare = asigurare;
        this->vizite_doctor_ultimul_an = new int[12];
        for(int i = 0; i<12; i++)
        {this->vizite_doctor_ultimul_an[i] = 0;}
        this->gen = 'N';

    }
    Pacient(char *nume, const string& prenume,string email,int varsta, bool asigurare, int* vizite_doctor_ultimul_an):cod_pacient(contor_pacient++){   //constructor fara parametrul de gen
        this->nume=new char[strlen(nume)+1];
        strcpy( this->nume, nume);
        this->prenume = prenume;
        this->email = email;
        this->varsta = varsta;
        //this->statut = statut;
        this->asigurare = asigurare;
        this->vizite_doctor_ultimul_an = new int[12];
        for(int i=0; i<12; i++)
            this->vizite_doctor_ultimul_an[i] = vizite_doctor_ultimul_an[i];
        this-> gen = 'N';
    }

    Pacient(char *nume, const string& prenume,string email,int varsta, bool asigurare, int* vizite_doctor_ultimul_an, char gen):cod_pacient(contor_pacient++){   //constructor cu toti parametri
        this->nume=new char[strlen(nume)+1];
        strcpy( this->nume, nume);
        this->prenume = prenume;
        this->email = email;
        this->varsta = varsta;
        //this->statut = statut;
        this->asigurare = asigurare;
        this->vizite_doctor_ultimul_an = new int[12];
        for(int i=0; i<12; i++)
            this->vizite_doctor_ultimul_an[i] = vizite_doctor_ultimul_an[i];
        this->gen = gen;
    }

    ~Pacient() {                                                             //destructor pacient
        if (this->nume != nullptr)
            delete[] nume;
        this->prenume = "Anonim";
        this->email = "Necunoscut";
        this->varsta = 0;
        //this->statut = Invalid;
        this->asigurare = false;
        if(this->vizite_doctor_ultimul_an != nullptr) {
            delete [] this->vizite_doctor_ultimul_an;
        this->gen = ' ';
        }

    }

    Pacient(const Pacient& p):cod_pacient(p.cod_pacient)                                           //copy-constructor
    {
        this->nume=new char[strlen(p.nume)+1];
        strcpy( this->nume, p.nume);
        this->prenume = p.prenume;
        this->varsta = p.varsta;
        this->email= p.email;
        //this->statut = p.statut;
        this->asigurare = p.asigurare;
        this->vizite_doctor_ultimul_an=new int[12];
        for(int i=0; i<12; i++)
            this->vizite_doctor_ultimul_an[i]=p.vizite_doctor_ultimul_an[i];
        this->gen = p.gen;

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
            this->email = p.email;
            this->asigurare = p.asigurare;
            this->vizite_doctor_ultimul_an=new int[12];
            for(int i=0; i<12; i++)
                this->vizite_doctor_ultimul_an[i]=p.vizite_doctor_ultimul_an[i];
            this->gen = p.gen;
        }
        return *this;
    }
    Pacient operator++(){                                               //supraincarcare ++ pentru Pacient, care adauga 1 la varsta(forma prefix)
        varsta++;
        return *this;}

    const Pacient operator++(int){                                               //supraincarcare ++ pentru Pacient, care adauga 1 la varsta(forma postfix)
        Pacient aux = *this;
        this->varsta++;
        return aux;}

    friend ostream& operator << (ostream& out, const Pacient& p)                 //supraincarcare <<
    {
        out<<"Numele pacientului este " << p.nume<<endl;
        out<<"Prenumele pacientului este "<< p.prenume<<endl;
        out<<"Varsta pacientului este "<< p.varsta<<endl;
        out<<"Email-ul pacientului este "<< p.email<<endl;
        if(p.asigurare == 1) out << "Pacientul este asigurat"<<endl;
        if(p.asigurare == 0) out << "Pacientul nu este asigurat"<<endl;
        out << "Vizitele pacientului la doctor in ultimele 12 luni sunt dupa cum urmeaza: "<<endl;
        for(int i = 0; i < 12; i++)
            out<<p.vizite_doctor_ultimul_an[i]<< " ";
        out<<endl;
        out << "Genul pacientului este " << p.gen <<endl;

        return out;
    }

    friend istream& operator >> (istream& in, Pacient& p)                        //supraincarcare >>
    {
        cout << "Numele pacientului este: "<<endl;
        char aux[100];
        in>>aux;
        if(p.nume!=nullptr)
            delete[] p.nume;
        p.nume=new char[strlen(aux)+1];
        strcpy(p.nume,aux);

        cout << "Prenumele pacientului este: "<<endl;
        in >> p.prenume;
        cout << "Varsta pacientului este: "<<endl;                                 //nu mai trebuie adaugat si id si contor?
        in >> p.varsta;
        cout << "Email-ul pacientului este: "<<endl;
        in >> p.email;
        cout << "Asigurarea pacientului este[1/0]: "<<endl;
        in >> p.asigurare;

        cout << "Vizitele pacientului la doctor in ultimele 12 luni sunt dupa cum urmeaza: "<<endl;
        if(p.vizite_doctor_ultimul_an != nullptr)
            delete[] p.vizite_doctor_ultimul_an;
        p.vizite_doctor_ultimul_an = new int[12];
        for(int i = 0; i <12; i++)
            in >> p.vizite_doctor_ultimul_an[i];

        cout << "Genul pacientului este[F/M/N]: "<<endl;
        in >> p.gen;

        return in;
    }

    bool operator == (const Pacient& p)                                //supraincarcare == (doua ob de tip Persoana vor fi egale daca vor avea acelasi nume,prenume si varsta)
    {
        if (strcmp(this->nume,p.nume) == 0 && this->prenume == p.prenume && this->varsta == p.varsta)
        {return true;}
        else return false;
    }

    bool operator < (const Pacient& p)                        //supraincarcare < care compara in functie de nume
    {
        if (strcmp(this->nume, p.nume) < 0)
            return true;
        return false;
    }

    int operator[](int index)                               //supraincarcare [], intoarce nr de vizite la clinica in luna respectiva
    {
        if (0<index && index <= 12)
            return this->vizite_doctor_ultimul_an[index-1];             //ca sa faca mai naturala introducerea lunilor, numerotarea este 1-12
        cout<< "Index incorect";
        return -1;
    }

    Pacient operator+(int x)                                //supraincarcare + pt intreg, x se aduna sa varsta(forma obiect+int)
    {
        Pacient aux(*this);
        aux.varsta = aux.varsta + x;
        return aux;
    }

    friend Pacient operator+(int x, Pacient p)              //supraincarcare +, aduna x la varsta(forma int+obiect)
    {
        p.varsta = p.varsta + x;
        return p;
    }

    Pacient operator-(int x)                                //supraincarcare - pt intreg, x se scade sa varsta(forma obiect-int)
    {
        Pacient aux(*this);
        aux.varsta = aux.varsta - x;
        return aux;
    }

    friend Pacient operator-(int x, Pacient p)              //supraincarcare -, scade x din varsta(forma int-obiect)
    {
        p.varsta = p.varsta - x;
        return p;
    }

    explicit operator string(){return (string)this->nume;}              //cast intre char* si string pentru nume
};

int Pacient::contor_pacient = 0;                                        //am setat staticul in afara clasei
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Programare
{
    float ora;
    int ziua, luna, an;
    string specializare;

    const int nr_programare;
    static int contor_prog;

public:

    void calculProgramari(int zi, int luna,int an, int& nr)                                //afiseaza programarile dintr-o anumita data si tine evidenta numarului
    {
        if (this->ziua == zi && this-> luna == luna && this->an == an){cout<<"Ora programare: "<<this->ora<<endl; nr++;}
    }


    void setContor_prog(int contor_prog)                                //setter pentru contorul programarii
    {this->contor_prog = contor_prog;}

    static int getContor_prog()                                             //getter pt contor
    {
        return contor_prog;
    }

    int getNr_programare()                                                  //getter pt numar de programare
    {
        return nr_programare;
    }

    void setOra(int ora){this->ora = ora;}                          //setter pt ora
    void setZi(int zi){this->ziua = zi;}                                //setter zi
    void setLuna(int luna){this->luna = luna;}                          //setter luna
    void setAn(int an){this->an = an;}                              //setter an

    int getAn(){return an;}                                     //getter pt an

    int getOra_programare(){return ora;}                                    //getter pt ora programarii

    Programare():nr_programare(contor_prog++)                                        //constructor fara parametri, va lua data curenta (cod luat de pe Stack Overflow - https://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c)
    {
        time_t t = time(nullptr);
        tm* now = localtime(&t);
        this->ora = 0;
        this->an = now->tm_year + 1900;
        this->luna = now->tm_mon + 1;
        this->ziua = now->tm_mday;
        this->specializare = "";
    }

    Programare(float ora, int ziua, int luna, string specializare):nr_programare(contor_prog++)                   //constructor fara parametri de an, va lua implicit anul curent
    {
        time_t t = time(nullptr);
        tm* now = localtime(&t);
        this->ora = 0;
        this->ziua = ziua;
        this->luna = luna;
        this->an = now->tm_year + 1900;
        this->specializare = specializare;
    }

    Programare(int ziua, int luna, int an, string specializare) :nr_programare(contor_prog++)                //constructor fara parametrul de ora
    {
        this->ora = 0;
        this->ziua = ziua;
        this->luna = luna;
        this->an = an;
        this->specializare = specializare;
    }

    Programare(float ora, int ziua, int luna, int an, string specializare):nr_programare(contor_prog++)                  //constructor cu toti parametri
    {
        this->ora = ora;
        this->ziua = ziua;
        this->luna = luna;
        this->an= an;
        this->specializare = specializare;
    }

    ~Programare()                                                   //destructor
    {
        ora = ziua = luna = an = 0;
    }

        Programare(const Programare &prog):nr_programare(prog.nr_programare)                                        //copy-constructor
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

    string getSpecializare() {return this->specializare;}

    void setSpecializare(string specializare)
    {
        this->specializare = specializare;
    }

    Programare operator++()                                 //supraincarcare ++ (forma prefix), adauga o unitate la ora
    {
        ora++;
        return *this;
    }

    const Programare operator++(int)                                 //supraincarcare ++ (forma postfix), adauga o unitate la ora
    {
        Programare aux = *this;
        this->ora++;
        return aux;
    }

    Programare operator+(Programare prog)
    {
        Programare prog1;

    }

    friend ostream& operator << (ostream& out, const Programare& p)                 //supraincarcare <<
    {
        out<<"Ora programarii este " <<p.ora<<endl;
        out<<"Data programarii este " <<p.ziua<<"/"<<p.luna<<"/"<<p.an<<endl;                   //ar avea sens sa mai afisez si contorul??
        return out;
    }

    friend istream& operator >> (istream& in, Programare& p)                        //supraincarcare >>
    {
        cout << "Ora programarii este: "<<endl;
        in>>p.ora;
        cout << "Ziua programarii este: "<<endl;
        in >> p.ziua;
        cout << "Luna progrmarii este: "<<endl;
        in >>p.luna;
        cout << "Anul progrmarii este: "<<endl;
        in >> p.an;
        return in;
    }

    bool operator == (const Programare& p)                                //supraincarcare == (doua ob de tip Programare vor fi egale daca au aceeasi data (nu tine cont de ora))
    {
        if (this->ziua == p.ziua && this->luna == p.luna && this->an == p.an )
        {return true;}
        else return false;
    }

    bool operator < (const Programare& p)                        //supraincarcare < care compara in functie de luna si an.
    {
        if (this->luna < p.luna && this->an < p.an)
            return true;
        return false;
    }

    Programare operator+(int x)                                 //obiect + int, aduna int la ziuaa programarii
    {
        Programare aux(*this);
        aux.ziua = aux.ziua + x;
        return aux;
    }

    friend Programare operator+(int x, Programare p)            //int + obiect, aduna int la zi
    {
        p.ziua = p.ziua + x;
        return p;
    }

    Programare operator-(int x)                                 //supraincarcare - , obiect-int, scade int din zi
    {
        Programare aux(*this);
        aux.ziua = aux.ziua - x;
        return aux;
    }

    friend Programare operator-(int x, Programare p)            // supraincarcare -, int - obiect, scade int din zi
    {
        p.ziua = p.ziua - x;
        return p;
    }

    explicit operator int(){return (int)this->ora;}              //cast explicit de la float ora la int ora
};

int Programare::contor_prog = 0;                            //am initializat staticul contor_prog in afara clasei(DAR DE CE DOAR ASA MA LASA?)


class Serviciu
{
    string serviciu_oferit;                                 //analize, consultatie, interpretare analize, investigatii, control, ecografie
    double tarif;
    float reducere;

    const int cod_serviciu;
    static int contor_serviciu;

public:
    void calculTarif(const Pacient& p)                              //aceasta functie va calcula tariful pentru un pacient, in functie de pachetele promotionale de care poate beneficia sau nu
    {
        int suma = 0;
        for(int i=0;i<12;i++)
            suma += p.vizite_doctor_ultimul_an[i];
        if (suma <= 5) cout << "Pacientul "<<p.nume<<" "<<p.prenume<<" nu se incadreaza pentru niciun pachet promotional, deci tariful serviciului va ramane "<<this->tarif<<endl;
        else if (suma <= 10) cout << "Pacientul "<<p.nume<<" "<<p.prenume<<" se incadreaza pentru pachetul Silver ce ii va conferi o reducere de 20%, deci tariful serviciului va deveni "<<this->tarif*0.8<<endl;
        else if(suma > 10) cout << "Pacientul "<<p.nume<<" "<<p.prenume<<" se incadreaza pentru pachetul Gold ce ii va conferi o reducere de 35%, deci tariful serviciului va deveni "<<this->tarif*0.65<<endl;
    }

    void setContor_serviciu(int contor_serviciu)                                //setter pentru contorul serviciului
    {this->contor_serviciu = contor_serviciu;}

    static int getContor_serviciu()                                             //getter pt contor
    {
        return contor_serviciu;
    }


    string getServiciu_oferit(){return serviciu_oferit;}                //getter pt serviciul oferit

    void setServiciu(string serviciu){this->serviciu_oferit = serviciu;}            //setter pt serviciu

    int getCod_serviciu()                                                  //getter pt codul serviciului
    {
        return cod_serviciu;
    }

    Serviciu():cod_serviciu(contor_serviciu++)                                                          //constructor fara parametri
    {
        serviciu_oferit = "";
        tarif = 0;
        reducere = 0;
    }

    Serviciu(const string& serviciu_oferit):cod_serviciu(contor_serviciu++)                          //constructor cu un parametru, fara reducere si fara tarif (va lua tariful implicit de 100)
    {
        this->serviciu_oferit = serviciu_oferit;
        this->tarif = 100;
        this->reducere = 0;
    }


    Serviciu(const string& serviciu_oferit, double tarif):cod_serviciu(contor_serviciu++)                          //constructor cu 2 parametri, fara reducere
    {
        this->serviciu_oferit = serviciu_oferit;
        this->tarif = tarif;
        this->reducere = 0;
    }

    Serviciu(const string& serviciu_oferit, double tarif, float reducere):cod_serviciu(contor_serviciu++)          //constructor cu toti parametri
    {
        this->serviciu_oferit = serviciu_oferit;
        if (reducere == 0)
            this->tarif = tarif;
        this->tarif = reducere * tarif;
        this->reducere = reducere;
    }

    ~Serviciu()                                                             //destructor
    {
        serviciu_oferit = "";
        tarif = 0;
        reducere = 0;
    }

    Serviciu(const Serviciu& s):cod_serviciu(s.cod_serviciu)                                             //copy-constructor
    {
        this->serviciu_oferit = s.serviciu_oferit;
        this->tarif = s.tarif;
        this->reducere = s.reducere;
    }

    double getTarif()                                                           //functie de getter pt tarif, calculat in functie de reducere (reducere obtinuta in fuctie de statutul pacientului)
    {
        return this->tarif;
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

    Serviciu operator++()                                               //supraincarcare ++ pentru tarif, care va adauga o unitate (forma prefix)
    {
        this->tarif++;
        return *this;
    }

    const Serviciu operator++(int)                                               //supraincarcare ++ pentru tarif, care va adauga o unitate (forma postincrement)
    {
        Serviciu aux = *this;
        this->tarif++;
        return aux;
    }

    Serviciu operator+(Serviciu const &serv)                                       //supraincarcare + pentru Servicii. Tarifele se aduna, reducerea nu se cumuleaza(ramane aceeasi, elevii si studentii oricum au reducere de 50% pentru tot, restul persoanelor nu au), si serviciile oferite se concateneaza
    {
        Serviciu serv1;
        serv1.tarif = serv.tarif + tarif;
        serv1.reducere = serv.reducere;
        serv1.serviciu_oferit = serv.serviciu_oferit + " si " + serviciu_oferit;
        return serv1;
    }

    Serviciu operator+(int x)                                           //supraincarcare +
    {
        Serviciu aux(*this);
        aux.tarif = aux.tarif + x;
        return aux;
    }

    friend Serviciu operator+(int x, Serviciu s)                        //supraincarcare +
    {
        s.tarif = s.tarif + x;
        return s;
    }

    Serviciu operator-(int x)                                           //ob - x, supraincarcare -
    {
        Serviciu aux(*this);
        aux.tarif = aux.tarif - x;
        return aux;
    }

    friend Serviciu operator-(int x, Serviciu s)                         // x - ob, supraincarcare -
    {
        s.tarif = s.tarif - x;
        return s;
    }

    friend ostream& operator << (ostream& out, const Serviciu& serv)                 //supraincarcare <<
    {
        out<<"Serviciul oferit este " <<serv.serviciu_oferit<<endl;
        out<<"Tariful serviciului este " <<serv.tarif<<endl;                   //ar avea sens sa mai afisez si contorul??
        out<< "Reducerea serviciul a fost de " << serv.reducere<<endl;
        return out;
    }

    friend istream& operator >> (istream& in, Serviciu& serv)                        //supraincarcare >>
    {
        cout << "Serviciul oferit este: "<<endl;
        in>>serv.serviciu_oferit;
        cout << "Tariful serviciului este de: "<<endl;
        in >> serv.tarif;
        cout << "Reducerea acordata este de: "<<endl;
        in >>serv.reducere;
        return in;
    }

    bool operator == (const Serviciu& s)                                //supraincarcare == (doua ob de tip Serviciu sunt egale daca au acelasi tarif)
    {
        if (this->tarif == s.tarif)
        {return true;}
        else return false;
    }

    bool operator < (const Serviciu& s)                        //supraincarcare < care compara in functie de tarif
    {
        if (this->tarif < s.tarif)
            return true;
        return false;
    }

    explicit operator int(){return int(this->tarif);}               //transforma double tarif in int tarif

};

int Serviciu::contor_serviciu = 0;

void optiuniMeniu(){                                                //functie pentru afisarea optiunilor
    cout<<endl;
    cout<<"Daca doriti sa introduceti informatii noi, alegeti optiunea 1"<<endl;                    //create
    cout<<"Pentru a modifica anumite informatii, alegeti optiunea 2 "<<endl;                         //update
    cout<<"Pentru stergerea de date din sistem, alegeti optiunea 3 "<<endl;                     //delete
    cout<<"Pentru a afisa informatii, alegeti optiunea 4 "<<endl;                               //read
    cout<<"Pentru a filtra doctorii, alegeti optiunea 5 "<<endl;                            //functionalitate doctor
    cout<<"Pentru a calcula eligibilitatea unui pacient pentru un pachet promotional, alegeti optiunea 6 "<<endl;               //functionalitate pacient
    cout<<"Pentru a afisa/verifica numarul de programari intr-o anumita data, alegeti optiunea 7 "<<endl;                       //functionalitate programare
    cout<<"Pentru a calcula tariful unui serviciu pentru un pacient, alegeti optiunea 8 "<<endl;                //functionalitate serviciu
    cout<<"Oricare alta optiune inchide meniul."<<endl;
}

void optiuneaUnu(Doctor vec[], Pacient pac[], Programare prog[], Serviciu serv[], int &sizeVec,int &nrVec, int &sizePac,int &nrPac, int &sizeServ, int &nrServ, int &sizeProg, int &nrProg) {
    while (1)
    {
        cout << "Alegeti in ce sectiune doriti sa introduceti informatii(1-Doctor, 2-Pacient, 3-Programare, 4-Servicii)"<<endl;
        int opt;
        cin >> opt;
        if (opt == 1) {
            if(nrVec + 1 > sizeVec)                             //daca nr de doctori ajunge la limita maxima alocata de sizeVec, voi suplimenta
            {
                //cout<<"aici";
                auto *tmp = new Doctor[nrVec + 10];
                for(int i =0; i<nrVec; i++)
                {
                    tmp[i] = vec[i];
                    cout<<tmp[i];
                }
                delete [] vec;
                vec = tmp;
                sizeVec += 10;
                cin>>vec[nrVec++];
                break;
            }

            else{
                int i;
                for(i = 0; i < nrVec; i++)                        //mai intai parcurg pana la nrVec si unde am prima pozitie libera, introduc noul doctor si voi schimba nrVec
                {
                    if (vec[i].getPrenume() == "Anonim")
                    {
                        cin >> vec[i];
                        break;
                    }
                }
                if(i == nrVec) {cin>>vec[nrVec++]; break;}
            }


        }
        else if (opt == 2)
        {
            //cod
        }
        else break;
    }
}

void optiuneaDoi(Doctor vec[], Pacient pac[], Programare prog[], Serviciu serv[], int sizePac,int sizeServ, int sizeProg){
    cout<<"Alegeti in ce sectiune doriti sa modificati informatii(1-Doctor, 2-Pacient, 3-Programare, 4-Servicii)"<<endl;
    int opt;
    cin >> opt;
    if (opt == 1){
        int id,i;
        cout<<"Introduceti id-ul doctorului ale carui informatii doriti sa le modificati "<<endl;
        cin >> id;
        for(i = 0; i<30; i++)
        {
            if(vec[i].getId_doctor() == id){cin >> vec[i]; break;}
        }
        //if (i == 30) cout<<"Nu s-a gasit niciun doctor cu id-ul specificat"<<endl;
    }

    if(opt == 2){
        int cod, i;
        cout<<"Introduceti codul pacientului ale carui informatii doriti sa le modificati "<<endl;
        cin >> cod;
        for(i = 0; i < sizePac; i++)
        {
            if(pac[i].getCod_pacient() == cod){cin >> pac[i];}
        }
        
        //if (i == sizePac) cout<<"Nu s-a gasit niciun pacient cu codul introdus"<<endl;
    }
    if(opt == 3)
    {
        int nr, i;
        cout<<"Introduceti numarul programarii ale carei informatii doriti sa le modificati "<<endl;
        cin>>nr;
        for(i=0; i<sizeProg; i++)
        {
            if (prog[i].getNr_programare() == nr){cin>>prog[i];}
        }
        //if (i ==sizeProg) cout<<"Nu s-a gasit nicio programare cu numarul specificat "<<endl;
    }
    if(opt == 4)
    {
        int cod, i;
        cout<<"Introduceti codul serviciului ale carui informatii doriti sa le modificati "<<endl;
        cin >> cod;
        for(i = 0; i<sizeServ; i++)
        {
            if (serv[i].getCod_serviciu() == cod) {cin >> serv[i];}
            
        }
        //if (i==sizeProg) cout <<"Nu s-a gasit niciun serviciu cu codul introdus "<<endl;         
    }
}

void optiuneaTrei(Doctor vec[], Pacient pac[], Programare prog[], Serviciu serv[], int sizePac,int sizeServ,int sizeProg){
    cout<<"Alegeti din ce sectiune doriti sa stergeti date(1-Doctor, 2-Pacient, 3-Programare, 4-Servicii)"<<endl;
    int opt;
    cin >> opt;
    if (opt == 1)
    {
        int id,i;
        cout<<"Introduceti id-ul doctorului pe care doriti sa il stergeti "<<endl;
        cin >> id;
        for(i = 0; i < 30; i++)
        {
            if(vec[i].getId_doctor() == id){
                cout<<"Doctorul cu id-ul "<<id<<" a fost sters"<<endl;
                vec[i].setPrenume("Anonim");              //prin prenumele setat la "" voi verifica in caz ca vreau sa fac introducere de informatii daca pozitia respectiva este libera
                break;
            }
        }
    }
    if (opt == 2)
    {
        int cod,i;
        cout<<"Introduceti codul pacientului pe care doriti sa il stergeti "<<endl;
        cin >> cod;
        for(i = 0; i < sizePac; i++)
        {
            if(pac[i].getCod_pacient() == cod){
                cout<<"Pacientul cu codul "<<cod<<" a fost sters"<<endl;
                pac[i].setPrenume("Anonim");          //acelasi lucru ca la doctor
            }
        }
    }
    if (opt == 3)
    {
        int nr,i;
        cout<<"Introduceti numarul programarii pe care doriti sa o stergeti "<<endl;
        cin >> nr;
        for(i = 0; i < sizeProg; i++)
        {
            if(prog[i].getNr_programare() == nr){
                cout<<"Programarea cu numarul "<<nr<<" a fost stearsa"<<endl;
                prog[i].setSpecializare("");                           //voi seta doar specializarea la ""
            }
        }
    }
    if (opt == 4)
    {
        int cod,i;
        cout<<"Introduceti codul serviciului pe care doriti sa il stergeti "<<endl;
        cin >> cod;
        for(i = 0; i < sizeServ; i++)
        {
            if(serv[i].getCod_serviciu() == cod){
                cout<<"Serviciul cu codul "<<cod<<" a fost sters"<<endl;
                serv[i].setServiciu("");                        //voi seta doar serviciul la "" si cand voi gasi primul obiect cu "" pe post de serviciu, voi sti ca este inactiv
            }
        }
    }
}

void optiuneaPatru(Doctor vec[], Pacient pac[], Programare prog[], Serviciu serv[], int nrVec, int nrPac,int nrServ, int nrProg){
    cout<<"Alegeti din ce sectiune doriti sa afisati date(1-Doctor, 2-Pacient, 3-Programare, 4-Servicii)"<<endl;
    int opt;
    cin >> opt;
    while (1){    if (opt == 1) {
            cout<<"Daca doriti afisarea tuturor doctorilor, alegeti optiunea 1"<<endl;
            cout<<"Pentru afisarea unui singur doctor cunoscut dupa ID, alegeti optiunea 2"<<endl;
            int optiune;
            cin>>optiune;
            if (optiune == 1){
                for(int i = 0; i < nrVec; i++)
                {
                    if(vec[i].getPrenume() != "Anonim")
                    {
                        cout<<"INFORMATII DOCTOR"<<endl;
                        cout<<vec[i]<<endl;
                    }
                }
            }
            if (optiune == 2){
                cout<<"Introduceti ID-ul doctorului cautat"<<endl;
                int ID;
                cin>>ID;
                int i;
                for(i=0; i < nrVec; i++)
                {
                    if (vec[i].getId_doctor() == ID)
                    {
                        cout<<vec[i]<<endl;
                        break;}
                }
                if (i == 30) cout<<"Nu s-a gasit niciun doctor cu ID-ul introdus";
            }
            else{break;}
        }
        if (opt == 2) {
            cout<<"Daca doriti afisarea tuturor pacientilor, alegeti optiunea 1"<<endl;
            cout<<"Pentru afisarea unui singur pacient cunoscut dupa cod, alegeti optiunea 2"<<endl;
            cout<<"Pentru a iesi, alegeti orice alta optiune "<<endl;
            int optiune;
            cin>>optiune;
            if (optiune == 1){
                for(int i = 0; i<nrPac; i++)
                {
                    if(pac[i].getPrenume() != "Anonim")
                    {
                        cout<<"INFORMATII PACIENT"<<endl;
                        cout<<pac[i]<<endl;
                    }
                }
            }
            if (optiune == 2){
                cout<<"Introduceti codul pacientului cautat"<<endl;
                int ID;
                cin>>ID;
                for(int i=0; i<nrPac; i++)
                {
                    if (pac[i].getCod_pacient() == ID)
                    {cout<<pac[i]<<endl;
                        break;}
                }
            }
            else{break;}
        }
        if (opt == 3)
        {
            cout<<"Daca doriti afisarea tuturor programarilor, alegeti optiunea 1"<<endl;
            cout<<"Pentru afisarea unei singure progrmari cunoscute dupa numar, alegeti optiunea 2"<<endl;
            int optiune;
            cin>>optiune;
            if (optiune == 1){
                for(int i = 0; i<nrProg; i++)
                {
                    if(prog[i].getSpecializare() != "")
                    {
                        cout<<"INFORMATII PROGRAMARE"<<endl;
                        cout<<prog[i]<<endl;
                    }
                }
            }
            if (optiune == 2){
                cout<<"Introduceti numarul programarii cautate"<<endl;
                int nr;
                cin>>nr;
                for(int i=0; i<nrProg; i++)
                {
                    if (prog[i].getNr_programare() == nr)
                    {cout<<prog[i]<<endl;
                        break;}
                }
            }
            else{break;}
        }
        if (opt == 4) {
            cout<<"Daca doriti afisarea tuturor serviciilor, alegeti optiunea 1"<<endl;
            cout<<"Pentru afisarea unui singur serviciu cunoscut dupa cod, alegeti optiunea 2"<<endl;
            int optiune;
            cin>>optiune;
            if (optiune == 1){
                for(int i = 0; i<nrServ; i++)
                {
                    if(serv[i].getServiciu_oferit() != "")
                    {
                        cout<<"INFORMATII SERVICIU OFERIT"<<endl;
                        cout<<serv[i]<<endl;
                    }
                }
            }
            if (optiune == 2){
                cout<<"Introduceti codul serviciului cautat"<<endl;
                int nr;
                cin>>nr;
                for(int i=0; i<nrServ; i++)
                {
                    if (serv[i].getCod_serviciu() == nr)
                        cout<<serv[i]<<endl;
                }
            }
            else{break;}
        }
    }
}


int main()
{
int v[12] = {2, 3,1,0, 0, 0, 0, 0, 0, 0, 0,7};
//Pacient p("Pop", "Ion", "ceva", 18);
//Pacient p2("aaa", "ion", "emailaaaa", 19, false, v,'F');
    int sizePac = 100;
    int sizeServ = 40;
    int sizeProg = 100;
    int sizeVec = 2;

    auto *vec = new Doctor[sizeVec];
    auto *pac = new Pacient[sizePac];
    auto *serv = new Serviciu[sizeServ];
    auto *prog = new Programare[sizeProg];

//    Programare pr(14.50,10,6,2022), pr2(10, 10,6,2022), pr3(10,10,6,2022);
//    Programare prg[3] = {pr,pr2,pr3};
//    int sizePrg = sizeof(prg)/sizeof(prg[0]);
//    int sizePac = sizeof(pac)/sizeof(pac[0]);
    int nrVec, nrPac, nrServ, nrProg;
    cout<<"Specificati cati doctori doriti sa introduceti in sistem: "<<endl;
    cin >> nrVec;
    cout<<"Specificati cati pacienti doriti sa introduceti in sistem: "<<endl;
    cin >> nrPac;
    cout<<"Specificati cate programari doriti sa introduceti in sistem: "<<endl;
    cin >> nrProg;
    cout<<"Specificati cate servicii doriti sa introduceti in sistem: "<<endl;
    cin >> nrServ;
    if (nrVec != 0)
    {cout<<"INTRODUCETI DOCTORII PE RAND "<<endl;
        for(int i = 0; i<nrVec; i++)
        {
            cout<<"Informatii doctor"<<endl;
            cin>>vec[i];
        }
    }

    if (nrPac != 0)
    {cout<<"INTRODUCETI PACIENTII PE RAND "<<endl;
        for(int i = 0; i<nrPac; i++)
        {
            cout<<"Informatii pacient"<<endl;
            cin>>pac[i];
        }
    }

    if (nrProg != 0)
    {cout<<"INTRODUCETI PROGRAMARILE PE RAND "<<endl;
        for(int i = 0; i<nrProg; i++)
        {
            cout<<"Informatii programare"<<endl;
            cin>>prog[i];
        }
    }

    if (nrServ != 0)
    {cout<<"INTRODUCETI SERVICIILE PE RAND "<<endl;
        for(int i = 0; i<nrServ; i++)
        {
            cout<<"Informatii serviciu"<<endl;
            cin>>serv[i];
        }
    }

    while (1)
    {

        optiuniMeniu();
        int nrOpt;
        cin >> nrOpt;
        if (nrOpt == 1) {optiuneaUnu(vec,pac,prog,serv, sizeVec, nrVec, sizePac, nrPac,sizeServ, nrServ,sizeProg,nrProg);}
        else if (nrOpt == 2) {optiuneaDoi(vec,pac,prog,serv,sizePac,sizeServ, sizeProg);}
        else if (nrOpt == 3) {optiuneaTrei(vec,pac,prog,serv,sizePac,sizeServ, sizeProg);}
        else if (nrOpt == 4) {optiuneaPatru(vec,pac,prog,serv,nrVec, nrPac,nrServ, nrProg);}
        else if (nrOpt == 5) {
            cout<<"Introduceti specializarea pe care o cautati "<<endl;
            string specializare;
            cin >> specializare;
            cout << "Introduceti rating-ul minim al doctorului "<<endl;
            float rating;
            cin >>rating;
            for(int i =0; i<30;i++)
            {
                vec[i].filtruDoctor(specializare,rating);
            }
        }
        else if (nrOpt == 6){
            cout<<"Introduceti codul pacientului: "<<endl;
            int cod;
            cin>>cod;
            int i;
            for(i = 0; i < nrPac; i++)
            {
                if (pac[i].getCod_pacient() == cod)
                {
                    {pac[i].calculPachetPromotional(); break;}
                }
                else
                {
                    if( i == nrPac-1 && pac[i].getCod_pacient() != cod) cout<< "Codul nu a fost gasit in sistem";
                }
            }

        }
        else if (nrOpt == 7){
            int zi, luna,an;
            cout << "Introduceti ziua: ";
            cin >>zi;
            cout << "Introduceti luna: ";
            cin >> luna;
            cout << "Introduceti anul: ";
            cin >>an;
            int nr = 0;
            for(int i = 0; i < sizeProg; i++)
                {
                    prog[i].calculProgramari(zi,luna,an,nr);
                }
            cout<<"In data de "<<zi<<"/"<<luna<<"/"<<an<<" sunt "<<nr<<" programari "<<endl;
        }

        else if (nrOpt == 8)
        {
            int cod_p, cod_s;
            cout<<"Introduceti codul pacientului "<<endl;
            cin >> cod_p;
            cout<<"Introduceti codul serviciului "<<endl;
            cin >> cod_s;
            Pacient p; Serviciu s;
            int i, j;
            for(i =0; i<sizePac;i++){
                if (pac[i].getCod_pacient() == cod_p && pac[i].getPrenume() != "Anonim" )
                {p = pac[i]; break;}
            }
            if(i == sizePac) {cout << "Cod pacient invalid" <<endl;}
            for(j =0; j<sizeServ;i++){
                if (serv[j].getCod_serviciu() == cod_s)
                {s = serv[j]; break;}
            }
            if(j == sizeServ){cout << "Cod serviciu invalid"<<endl;}

            s.calculTarif(p);
        }
        else break;
    }

    delete[] vec;
    delete[] pac;
    delete[] serv;
    delete[] prog;
    return 0;
}

