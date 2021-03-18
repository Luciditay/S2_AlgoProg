#include <QApplication>
#include <time.h>

#include "lib/tp1.h"

MainWindow* w = nullptr;

void selectionSort(Array& toSort){
    int indMin, tmp;
    for (int i=0; i<toSort.size(); i++)
    {
        indMin=i;
        for (int j=i+1; j<toSort.size(); j++)
        {
            if (toSort.get(j)<toSort.get(indMin))
            {
                indMin=j;
            }
        }
        tmp=toSort.get(indMin);
        toSort.swap(i, indMin);
    }
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    uint elementCount=15; // number of elements to sort
    MainWindow::instruction_duration = 100; // delay between each array access (set, get, insert, ...)
    w = new TestMainWindow(selectionSort, elementCount); // window which display the behavior of the sort algorithm
    w->show();

	return a.exec();
}
