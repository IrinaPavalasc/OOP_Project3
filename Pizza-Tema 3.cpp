#include<iostream>
#include<vector>
#include<string>
#include <stdlib.h>

using namespace std;

///...............................................................

class Ingredient {
	string Denumire;
	int Cantitate;
	int PretUnitar;
public:
	Ingredient() {
	    Denumire ="";
		Cantitate = 0;
		PretUnitar = 0;

	}
	Ingredient(string A, int B, int C) {
	    Denumire = A;
        try
        {
            if (B<0)
                throw B;
            if (C<0)
                throw C;
        }
        catch (int x)
        {
            cout<<"Eroare in constructor, cantitatea sau pretul pe unitate nu pot fi negative."<<endl;
            exit(EXIT_FAILURE);
        }
        Cantitate = B;
		PretUnitar = C;
	}

	///supraincarcarea =
	Ingredient& operator=(const Ingredient& A){
	 if (this!=&A)
        {
            Denumire=A.Denumire;
            Cantitate=A.Cantitate;
            PretUnitar=A.PretUnitar;
        }
    return *this;
    }

	///supraincarcarea >>
	friend istream& operator >> (istream& os, Ingredient& A)
	{   cout<<endl;
		cout << "Denumirea ingredientului este: ";
		os >> A.Denumire;
		cout << "Cantitatea ingredientului este: ";
		os >> A.Cantitate;
		cout << "Pretul Unitar al ingredientului este: ";
		os >> A.PretUnitar;
		try
        {
            if (A.Cantitate<0)
                throw A.Cantitate;
            if (A.PretUnitar<0)
                throw A.PretUnitar;
        }
        catch (int x)
        {
            cout<<"Cantitatea sau pretul pe unitate nu pot fi negative."<<endl;
            exit(EXIT_FAILURE);
        }
		cout<<endl;
		return os;
	}
	///supraincarcarea <<
        friend ostream& operator << (ostream& os, Ingredient& A)
        {
            os << A.Denumire;
            cout<<" ("<<A.Cantitate<<"/"<< A.PretUnitar<<") ";
            return os;
        }

	int PretCantitate() {
		return PretUnitar * Cantitate;
	}

	~Ingredient(){}

};
///......................................................................

class Baza {
public:
   virtual int PretProdus()=0;
   virtual void citire (istream &in)=0;
   virtual void afisare(ostream &out)=0;
   friend istream& operator>>(istream& in, Baza&B){ B.citire(in); return in; };
   friend ostream& operator<<(ostream& out, Baza&B){ B.afisare(out);return out; };
   virtual ~Baza(){}
};

///.......................................................................
class Pizza: public Baza {
protected:

     string TipPizza;
     int NumarIngrediente;
	 vector <Ingredient> ListaIngrediente;
	 bool vegetariana;
     const int Manopera;

public:

    bool get_veg()const{
         return vegetariana;
    }

    Pizza(int C=0):Manopera(C){
         NumarIngrediente=0;
         TipPizza="";
         vegetariana=false;
    }

    Pizza(string A,vector <Ingredient> V, int B, int C, bool D):Manopera(C) {
          try
        {
            if (B<0)
                throw B;
        }
        catch (int x)
        {
            cout<<"Eroare in constructor, numarul ingredientelor nu poate fi negativ.\n";
            exit(EXIT_FAILURE);
        }
            NumarIngrediente=B;
            TipPizza=A;
            ListaIngrediente=V;
            vegetariana=D;
    }

    void citire (istream &in);
    void afisare(ostream &out);
    friend istream& operator>>(istream&, Pizza&);
    friend ostream& operator<<(ostream&, Pizza&);

	int PretProdus(){
	     int x=0;
	     for(int i=0;i<NumarIngrediente;i++)
           x= x + ListaIngrediente[i].PretCantitate();
         x=x+Manopera;
         return x;
	}
    Pizza& operator=(const Pizza& A){
	 if (this!=&A)
        {
            TipPizza=A.TipPizza;
            NumarIngrediente=A.NumarIngrediente;
            for (int i = 0; i < A.NumarIngrediente; i++)
                 ListaIngrediente[i]=A.ListaIngrediente[i];
            vegetariana=A.vegetariana;
        }
    return *this;
    }

    ~Pizza(){}
};

void Pizza::citire (istream &in){
        cout << "Tipul de Pizza este: ";
		in >> TipPizza;
		cout<<endl;
		cout<<"Este Pizza Vegetariana?  ";
		string x;
		in>>x;
		if(x=="da" || x=="Da")
            vegetariana=1;
		else
            if(x=="nu" || x=="Nu")
                vegetariana=0;
        try
        {
            if (x!= "da" && x!= "Da" && x!="nu" && x!="Nu")
                throw 'a';
        }
        catch (char x)
        {
            cout<<"Raspunsul trebuie sa fie Da sau Nu."<<endl;
            exit(EXIT_FAILURE);
        }
		cout<<endl;
		cout << "Numarul Ingredientelor este: ";
		in >> NumarIngrediente;
		 try
        {
            if (NumarIngrediente<0)
                throw NumarIngrediente;
        }
        catch (int x)
        {
            cout<<"Numarul ingredientelor nu poate fi negativ."<<endl;
            exit(EXIT_FAILURE);
        }
		cout<<endl;
		cout << "Lista Ingredientelor este: "<<endl;

        Ingredient X;
        ListaIngrediente.clear();
        for(int i=0;i<NumarIngrediente;i++)
           { in>>X;
             ListaIngrediente.push_back(X);
           }
        };

istream& operator>>(istream& in, Pizza& A)
        {
            A.citire(in);
            return in;
        }

void Pizza::afisare(ostream &out){

        out << "Pizza: ";
		out << TipPizza<<"   ";
        out<<"Pret: "<< PretProdus();
        out<<endl;
		out << "Ingrediente: "<<endl;
        for(int i=0;i<NumarIngrediente;i++)
            out<<ListaIngrediente[i];
        out<<endl;
	    out<<"Este Vegetariana? ";
	    if(vegetariana==1)
            out<<" Da.";
        else out<<"Nu.";
        out<<endl;

        };

ostream& operator<<(ostream& out, Pizza& A)
        {
            A.afisare(out);
            return out;
        }

///.............................................................................

class PizzaOnline: public Pizza{
    int Distanta;

public:

    PizzaOnline():Pizza(){}
    PizzaOnline(string A,vector <Ingredient> V, int B,int C, bool D) :Pizza(A,V,B,C,D){}

    void citire (istream &in);
    void afisare(ostream &out);
    friend istream& operator>>(istream&, PizzaOnline&);
    friend ostream& operator<<(ostream&, PizzaOnline&);

    int PretProdus(){
        float x=0;
        for(int i=0;i<NumarIngrediente;i++)
           x= x + ListaIngrediente[i].PretCantitate();
         x=x+Manopera;
         int y=Distanta;///y=20
         float z=5*x/100;///
         while(y>=10){
             x=x+z;
             y=y-10;
         }

    return x;
    }

    PizzaOnline& operator=(const PizzaOnline &A){
        if(this!=&A)
            { Pizza::operator=(A);
              Distanta=A.Distanta;
            }
        return *this;
    }

    ~PizzaOnline(){}

};

void PizzaOnline::citire (istream &in){
        Pizza::citire(in);

        cout << "Distanta pana la domiciliu: ";
                in >> Distanta;
        };
istream& operator>>(istream& in, PizzaOnline& A)
        {
                    A.citire(in);
                    return in;
        }

void PizzaOnline::afisare(ostream &out){
        Pizza::afisare(out);

        out << "Distanta pana la domiciliu: ";
                out<< Distanta;
        out<<endl;
        };
ostream& operator<<(ostream& out, PizzaOnline& A)
        {
            A.afisare(out);
            return out;
        }
void tipComanda(Baza *&p, int &i) {
    string comanda;
    cout<<endl;
    cout<<"Tipul comenzii este "<<i+1<<": ";
    cin>>comanda;

    if(comanda=="Pizza"){
        p=new Pizza;
        cin>>*p;
        i++;
    }
    else
        if(comanda=="PizzaOnline"){
            p=new PizzaOnline;
            cin>>*p;
            i++;
        }
}
void Citire_Memorare_Afisare(Baza **V){
    int n;
    cout<<"Numarul de obiecte citite este: ";
    cin>>n;
    V=new Baza*[n];

    if (n>0){
        for(int i=0;i<n;)
            tipComanda(V[i],i);
        cout<<endl;
        cout<<"Comenzile efectuate anterior: ";
        cout<<endl;

        for(int i=0;i<n;i++)
            {cout<<endl<<*V[i];

             cout<<endl<<"*****************************"<<endl;
            }
    }
    else cout<<"Numarul de obiecte nu poate fi negativ!";
}

template <class t> class Meniu{
   static int index;
   vector <t> Comenzi;
   vector <int> NrOrdine;
public:

    Meniu(){
        Comenzi={};
        NrOrdine={};
    }
    Meniu(vector <t> A) {
	    for(int i=0;i<A.size();i++)
           {Comenzi.push_back(A[i]); index++; NrOrdine.push_back(index);}

    }

    Meniu& operator=(const Meniu& A){
        if (this!=&A)
        {
            Comenzi=A.Comenzi;
            NrOrdine=A.NrOrdine;
        }
        return *this;
    }

    Meniu& operator+=(const t& A){
        Comenzi.push_back(A); index++; NrOrdine.push_back(index);
        return *this;

    }

    friend istream& operator >> (istream& os, Meniu& A)
    {

        cout<< "Numarul de comenzi: ";

        int a;

        os >> a;
         try
        {
            if (a<0)
                throw a;
        }
        catch (int x)
        {
            cout<<"Numarul de comenzi nu poate fi negativ"<<endl;
            exit(EXIT_FAILURE);
        }
        t Ob;
        for(int i=0;i<a;i++)
            {os>>Ob; A+=Ob;}
        return os;
    }


        friend ostream& operator << (ostream& os, Meniu& A)

        {   os<<"                  Meniu                 "<<endl;
            os<<"****************************************"<<endl;

            for(int i=0;i<A.Comenzi.size();i++)
                os<<A.NrOrdine[i]<<".  "<<A.Comenzi[i]<<endl;


            return os;
        }

    ~Meniu(){}

};
template <class t> int Meniu <t>::index=0;

template <> class Meniu <PizzaOnline>{
   static int index;
   vector <PizzaOnline> Comenzi;
   vector <int> NrOrdine;
   vector <PizzaOnline> PizzaVegetariana;
public:

    Meniu(){
        Comenzi={};
        NrOrdine={};
    }
    Meniu(vector <PizzaOnline> A) {
	    for(int i=0;i<A.size();i++)
           {Comenzi.push_back(A[i]); index++; NrOrdine.push_back(index);
            if(A[i].get_veg()==true)
                PizzaVegetariana.push_back(A[i]);
           }

    }
     Meniu(const Meniu& A)
        {
            Comenzi=A.Comenzi;
            PizzaVegetariana=A.PizzaVegetariana;
            NrOrdine=A.NrOrdine;

        }
    Meniu& operator=(const Meniu& A){
        if (this!=&A)
        {
            Comenzi=A.Comenzi;
            PizzaVegetariana=A.PizzaVegetariana;
            NrOrdine=A.NrOrdine;
        }
        return *this;
    }

    Meniu& operator+=(const PizzaOnline& A){

        Comenzi.push_back(A); index++; NrOrdine.push_back(index);
         if(A.get_veg()==true)
                PizzaVegetariana.push_back(A);

        return *this;

    }

    friend istream& operator >> (istream& os, Meniu& A)
    {
        cout << "Numarul de comenzi: ";
        int a;

        os >> a;
        try
        {
            if (a<0)
                throw a;
        }
        catch (int x)
        {
            cout<<"Numarul de comenzi nu poate fi negativ"<<endl;
            exit(EXIT_FAILURE);
        }
        PizzaOnline Ob;
        for(int i=0;i<a;i++)
            {os>>Ob; A.Comenzi.push_back(Ob); A.index++; A.NrOrdine.push_back(index);
             if(Ob.get_veg()==true)
                A.PizzaVegetariana.push_back(Ob);
            }
        return os;
    }
    int ValoareVegetariana(){
        int Suma=0;
        for(int i=0;i<PizzaVegetariana.size();i++)
            Suma=Suma+PizzaVegetariana[i].PretProdus();
        return Suma;
    }
    friend ostream& operator << (ostream& os, Meniu& A)
    {   os<<"                  Meniu                 "<<endl;
        os<<"****************************************"<<endl;


        for(int i=0;i<A.Comenzi.size();i++)
           os<<A.NrOrdine[i]<<"  "<<A.Comenzi[i]<<endl;


        os<<endl;
        os<<"Total suma incasata din vanzarea de pizza vegetariana: "<< A.ValoareVegetariana();
        return os;
    }

    ~Meniu(){}

};
template <> int Meniu <PizzaOnline>::index=0;

int main()
{
Meniu<Pizza> M;
cin>>M;
cout<<M;


}
