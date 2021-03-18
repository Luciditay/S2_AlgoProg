#include "lib/tp3.h"
#include <QApplication>
#include <time.h>

MainWindow* w = nullptr;
using std::size_t;

int binarySearch(Array& array, int toSearch)
{
    int start=0, mid, end=array.size();
    while(start<end)
    {
        mid=(start+end)/2;
        if (toSearch>array.get(mid))
        {
            start=mid;
        }
        else if(toSearch<array.get(mid))
        {
            end=mid;
        }
        else
            return mid;
    }

        return -1;
	return -1;
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow::instruction_duration = 500;
	w = new BinarySearchWindow(binarySearch);
	w->show();

	return a.exec();
}
