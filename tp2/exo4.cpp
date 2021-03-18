#include <QApplication>
#include <time.h>

#include "lib/tp1.h"


MainWindow* w=nullptr;

void recursivQuickSort(Array& toSort, int size)
{
    if(size==0)
    {
        return;
    }
	
	Array& lowerArray = w->newArray(size);
	Array& greaterArray= w->newArray(size);
	int lowerSize = 0, greaterSize = 0; // effectives sizes

    int pivot=toSort.get(0); // Le pivot sera le premier élément du tableau
	
    for(int i=1; i<size; i++)
    {
        if (toSort.get(i)<pivot)
        {
            lowerArray.set(lowerSize, toSort.get(i));
            lowerSize++;
        }
        else
        {
            greaterArray.set(greaterSize, toSort.get(i));
            greaterSize++;
        }
    }
	// recursiv sort of lowerArray and greaterArray
    recursivQuickSort(lowerArray, lowerSize);
    recursivQuickSort(greaterArray, greaterSize);
	// merge
    int i=0;
    for(int l=0; l<size; l++)
    {
        if (l<lowerSize)
        {
            toSort.set(l, lowerArray.get(i));
            i++;
        }
        else if (l==lowerSize) // On arrive au pivot
        {
            toSort.set(l, pivot);
            i=0;
        }
        else // l>lowerSize
        {
            toSort.set(l, greaterArray.get(i));
            i++;
        }
    }


}

void quickSort(Array& toSort){
	recursivQuickSort(toSort, toSort.size());
}


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    uint elementCount=8;
    MainWindow::instruction_duration = 50;
	w = new TestMainWindow(quickSort, elementCount);
	w->show();

	return a.exec();
}
