#include "lib/tp3.h"
#include <QApplication>
#include <time.h>

MainWindow* w = nullptr;
using std::size_t;


void binarySearchAll(Array& array, int toSearch, int& indexMin, int& indexMax)
{
    int start=0, mid, end=array.size(), index=-1;

    while(start<end)
    {
        mid=(start+end)/2;
        if (toSearch>array.get(mid))
        {
            start=mid+1;
        }
        else if (toSearch<array.get(mid))
        {
            end=mid;
        }
        else
        {
            index=mid;
            break;
        }
    }

    if (index==-1)
    {
       indexMin=-1;
       indexMax=-1;
       return;
    }

    indexMin=index, indexMax=index;

    while(indexMin>=0 && array.get(indexMin-1)==toSearch)
    {
        indexMin--;
    }

    while(indexMax<array.size()-1 &&  (array.get(indexMax+1)==toSearch))
    {
        indexMax++;
    }

}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow::instruction_duration = 500;
	w = new BinarySearchAllWindow(binarySearchAll);
	w->show();

	return a.exec();
}
