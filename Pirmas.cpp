#include <iostream>
#include <iomanip>
#include <string>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstdlib>

using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::left;
using std::setw;
using std::fixed;
using std::setprecision;
using std::sort;


struct duom{
  string vardas;
  string pavarde;
  double pazymiai[30];
  int egzaminas;
};


duom ivedimas(int &n){
    duom stud;
    int egzaminoPazymys;
    cout<<"Iveskite studento varda: "; cin>>stud.vardas;
    cout<<"Iveskite studento pavarde: "; cin>>stud.pavarde;
    cout<<"Iveskite egzamino bala(Random egzamino balas - iveskite 0) : "; cin>>egzaminoPazymys;
    while(egzaminoPazymys>10){
    cout<<"Veskite pazymius tik nuo 1 iki 10"<<endl;
    cin>>egzaminoPazymys;
    }
    stud.egzaminas=egzaminoPazymys;
    if(stud.egzaminas==0)stud.egzaminas=1+(rand()%10);

  //---- Dinaminis C masyvas

    /*int *p = new int[20];
    if(!p) cout << "allocation of memory failed\n";

    else {

        n=0;
        for(int kint=0;kint<20;kint++){
            cout<<"Iveskite "<<kint+1<<" semestro pazymi(Jei suvedete visus pazymius, iveskite 0,jei random - -1): ";
            cin>>p[kint];
            while (p[kint]>10){
                cout<<"veskite pazymius tik nuo 1 iki 10"<<endl;
                cin>>p[kint];}
            if(p[kint]==0)break;
            else if (p[kint]==-1){
                stud.pazymiai[kint]=1+(rand()%10);
            }
            else{
                stud.pazymiai[kint]=p[kint];

    }
    n++;
  }
  } */

    vector<int> v;
    v.reserve(50);
    n=0;
    int paz;
    for(int kint=0;kint<20;kint++){
        cout<<"Iveskite semestro pazymi(Norite nutraukti - iveskite skaiciu 0,jei norite random pazymio - iveskite -1): ";
        cin>>paz;
        while(paz>10){
            cout<<"Iveskite skaiciu tik nuo 1 iki 10!"<<endl;
            cin>>paz;
        }
        v[kint]=paz;
;
        if(v[kint]==0)break;
        else if(v[kint]==-1){
            stud.pazymiai[kint]=1+(rand()%10);
        }
        else{
            stud.pazymiai[kint] = v[kint];
        }
        n++;
        v.push_back(kint);
    }
    v.shrink_to_fit();
    //delete [] p;
    return stud;
}


void isvedimas(duom as, int n){

    cout<<setw(20)<<left<<"Vardas"<<setw(20)<<left<<"Pavarde"<<setw(43)<<left<<"Galutinis (Vid.) / Galutinis (Med.)"<<endl;
    cout<<"--------------------------------------------------------------------------"<<endl;
    cout<<setw(20)<<left<<as.vardas<<setw(20)<<left<<as.pavarde;
    double suma = 0;
    for(int i=0;i<n;i++) suma = suma + as.pazymiai[i];
    cout<<fixed<<setprecision(2)<<setw(20)<<left<<0.4*suma/n+0.6*as.egzaminas;
    sort(as.pazymiai,as.pazymiai+n);
    if(n%2!=0)cout<<fixed<<setprecision(2)<<setw(23)<<left<<as.pazymiai[(n-1)/2]<<endl;
    else cout<<fixed<<setprecision(2)<<setw(23)<<left<<(as.pazymiai[n/2-1]+as.pazymiai[n/2])/2<<endl;
}
int main(){
  duom asmuo1, masyvas[25];
  int n, m;
  cout<<"Iveskite studentu kieki: "; cin>>n;
  for (int i=0;i<n;i++){
       masyvas[i]=ivedimas(m);
       isvedimas (masyvas[i], m);
    }
}
