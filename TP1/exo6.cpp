#include <iostream>

using namespace std;

struct Noeud{
    int donnee;
    Noeud* suivant;
};

struct Liste{
    Noeud* premier;
    Noeud* dernier; // Simplifiera grandement l'ajout d'une valeur à la fin de la liste
};

void initialise(Liste* liste)
{
    liste->premier=nullptr;
    liste->dernier=nullptr;
}

bool est_vide(const Liste* liste)
{
    if (liste->premier==nullptr)
    {
        return true;
    }
    return false;
}

void ajoute(Liste* liste, int valeur)
{

    Noeud* newNoeud=(Noeud*) malloc(sizeof(Noeud));
    newNoeud->donnee=valeur;
    newNoeud->suivant=nullptr;

    if (est_vide(liste))
    {
        liste->premier=newNoeud;
        liste->dernier=newNoeud;
    }

    else
    {
    liste->dernier->suivant=newNoeud; // On lie le dernier noeud au nouveau noeud crée
    liste->dernier=newNoeud; // Ce nouveau noeud devient le dernier de la liste
    }
}

void affiche(const Liste* liste)
{
    cout <<"Debut liste"<<endl;
    Noeud* noeud=liste->premier;

    while(noeud!=nullptr)
    {
        cout << noeud->donnee <<endl;
        noeud=noeud->suivant;
    }
}

int recupere(const Liste* liste, int n)
{
    Noeud* noeud=liste->premier;

    if (noeud==nullptr)
    {
        return -1;
    }

    for (int i=0;i<n; i++)
    {
        if (noeud==nullptr)
        {
            return -1;
        }
        else
        {
            noeud=noeud->suivant;
        }
    }

    return noeud->donnee;
}

int cherche(const Liste* liste, int valeur)
{
   if (est_vide(liste))
   {
    return -1;
   }

   int cpt=1;
   Noeud* noeud=liste->premier;

   while(noeud!=nullptr)
       if (noeud->donnee==valeur)
       {
           return cpt;
       }
   else
       {
           cpt++;
           noeud=noeud->suivant;
       }

    return -1;
}

void stocke(Liste* liste, int n, int valeur)
{
    if (est_vide(liste))
    {
        return;
    }

    Noeud* noeud=liste->premier;

    for (int i=1;i<n; i++) // Stocke (n, 3) ==> On insère n à la position 3 pr un humain (donc tab[2])
    {
        if (noeud==nullptr)
        {
            return;
        }
        else
        {
            noeud=noeud->suivant;
        }
    }

    noeud->donnee=valeur;

}

struct DynaTableau{
    int* donnees;
    int capacite;
    int nbreEntree;
};

void ajoute(DynaTableau* tableau, int valeur)
{
    if (tableau->nbreEntree == tableau->capacite)
    {
        int* tmpTab = (int*) malloc(tableau->capacite+1*sizeof(int));

        for (int i=0; i<tableau->capacite; i++)
        {
            tmpTab[i]=tableau->donnees[i];
        }
        tmpTab[tableau->capacite]=valeur;
        tableau->donnees=tmpTab;
        (tableau->capacite)++;
    }
    else
    {
        tableau->donnees[tableau->nbreEntree]=valeur;
    }
    tableau->nbreEntree++;
}


void initialise(DynaTableau* tableau, int capacite)
{
    tableau->donnees=(int*) malloc(capacite*sizeof(int));
    tableau->capacite=capacite;
    tableau->nbreEntree=0;
}

bool est_vide(const DynaTableau* tableau)
{
    if (tableau->nbreEntree==0)
    {
        return true;
    }
    return false;
}

void affiche(const DynaTableau* tableau)
{
    cout << "Debut Tab"<<endl;
    for (int i=0; i<tableau->nbreEntree; i++)
    {
        cout << tableau->donnees[i]<<" "<<endl;
    }
}

int recupere(const DynaTableau* tableau, int n)
{
    if (n>=0 && n<tableau->nbreEntree)
    {
        return tableau->donnees[n];
    }
    return 0;
}

int cherche(const DynaTableau* tableau, int valeur)
{
    int cpt = 1, index=-1;

    while(cpt<tableau->nbreEntree){
           if(tableau->donnees[cpt] == valeur)
           {
               index = cpt;
               break;
           }
           cpt++;
       }

       return index+1; // Si nb est à position n dans tab, il est à la n+1ème place pr un humain

    return -1;
}

void stocke(DynaTableau* tableau, int n, int valeur)
{
    if(n>=0 && n<tableau->nbreEntree)
    {
        tableau->donnees[n-1]=valeur;
    }
    return;
}

//void pousse_file(DynaTableau* liste, int valeur)
void pousse_file(Liste* liste, int valeur)
{
    Noeud* newNoeud= (Noeud*) malloc(sizeof(Noeud));
    newNoeud->donnee=valeur;
    newNoeud->suivant= liste->premier;
    liste->premier=newNoeud;
}

//int retire_file(Liste* liste)
int retire_file(Liste* liste)
{
    Noeud* tmp = liste->premier;
    int valeur = tmp->donnee;

    liste->premier=liste->premier->suivant;
    free(tmp);

    return valeur;
}

//void pousse_pile(DynaTableau* liste, int valeur)
void pousse_pile(Liste* liste, int valeur)
{
   ajoute(liste, valeur); //pile ==> Fin, File -> Debut
}

//int retire_pile(DynaTableau* liste)
int retire_pile(Liste* liste)
{

   if (liste->premier->suivant==nullptr) // Liste ne contient qu'un élément
   {
       int value=liste->premier->donnee;
       liste->premier=nullptr;
       return value;
   }

   else
   {
     Noeud* noeud = liste->premier;

     while(noeud->suivant->suivant!=nullptr) // On se place à l'avant dernier noeud
     {
       noeud=noeud->suivant;
     }
     int value=noeud->suivant->donnee;
     liste->dernier=noeud;
     liste->dernier->suivant=nullptr;
     return value;
   }
}


int main()
{
    Liste liste;
    initialise(&liste);
    DynaTableau tableau;
    initialise(&tableau, 5);

    if (!est_vide(&liste))
    {
        std::cout << "Oups y a une anguille dans ma liste" << std::endl;
    }

    if (!est_vide(&tableau))
    {
        std::cout << "Oups y a une anguille dans mon tableau" << std::endl;
    }

    for (int i=1; i<=7; i++) {
        ajoute(&liste, i*7);
        ajoute(&tableau, i*5);
    }

    if (est_vide(&liste))
    {
        std::cout << "Oups y a une anguille dans ma liste" << std::endl;
    }

    if (est_vide(&tableau))
    {
        std::cout << "Oups y a une anguille dans mon tableau" << std::endl;
    }

    std::cout << "Elements initiaux:" << std::endl;
    affiche(&liste);
    affiche(&tableau);
    std::cout << std::endl;

    std::cout << "5e valeur de la liste " << recupere(&liste, 4) << std::endl;
    std::cout << "5e valeur du tableau " << recupere(&tableau, 4) << std::endl;

    std::cout << "21 se trouve dans la liste à " << cherche(&liste, 21) << std::endl;
    std::cout << "15 se trouve dans la liste à " << cherche(&tableau, 15) << std::endl;

    stocke(&liste, 4, 7);
    stocke(&tableau, 4, 7);

    std::cout << "Elements après stockage de 7:" << std::endl;
    affiche(&liste);
    affiche(&tableau);
    std::cout << std::endl;

    Liste pile; // DynaTableau pile;
    Liste file; // DynaTableau file;

    initialise(&pile);
    initialise(&file);

    for (int i=1; i<=7; i++) {
        pousse_file(&file, i);
        pousse_pile(&pile, i);
    }

    int compteur = 10;

    while(!est_vide(&file) && compteur > 0)
    {
        std::cout << retire_file(&file) << std::endl;
        compteur--;
    }

    if (compteur == 0)
    {
        std::cout << "Ah y a un soucis là..." << std::endl;
    }

    compteur = 10;
    while(!est_vide(&pile) && compteur > 0)
    {
        std::cout << retire_pile(&pile) << std::endl;
        compteur--;
    }

    if (compteur == 0)
    {
        std::cout << "Ah y a un soucis là..." << std::endl;
    }

    return 0;
}
