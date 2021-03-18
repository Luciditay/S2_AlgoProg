#include <QApplication>
#include <time.h>

#include "lib/tp1.h"

MainWindow* w=nullptr;

void inserer(Array& toInsert, int ind, int taille, int valeur) // Insere dans l'array toSort l'entier n à l'indice ind
{
    int tmp1=toInsert.get(ind);
    toInsert.set(ind, valeur);

    for (int i=ind+1; i<taille-1; i++)
    {
        toInsert.set(i, tmp1);
        tmp1=toInsert.get(i+1);
    }
    toInsert.set(taille, tmp1);
}

void insertionSort(Array& toSort){
	Array& sorted=w->newArray(toSort.size());
    sorted.set(0, toSort.get(0));
    int nbreElement = 1;
    int ind=1;
    while(ind<toSort.size()) // On se déplace dans le premier tableau
    {
        bool insert=false;
        for (int i=0; i<nbreElement; i++)
        {

            if (sorted.get(i)>toSort.get(ind))
            {
               inserer(sorted, i, nbreElement, toSort.get(ind));
               insert=true;
            }
        }
        if (insert==false) // Le nbre na pas ete insere
        {
            sorted.set(nbreElement, toSort.get(ind));
        }

        nbreElement++;
        ind++;
    }
	
	toSort=sorted; // update the original array
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    uint elementCount=10; // number of elements to sort
    MainWindow::instruction_duration = 100; // delay between each array access (set, get, insert, ...)
    w = new TestMainWindow(insertionSort, elementCount); // window which display the behavior of the sort algorithm
	w->show();

	return a.exec();
}
