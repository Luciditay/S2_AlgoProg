#include <QApplication>
#include <time.h>

#include "lib/tp1.h"


MainWindow* w=nullptr;

void merge(Array& first, Array& second, Array& result);

void splitAndMerge(Array& origin)
{
	// stop statement = condition + return (return stop the function even if it does not return anything)
    if (origin.size()==1)
    {
        return;
    }

	Array& first = w->newArray(origin.size()/2);
	Array& second = w->newArray(origin.size()-first.size());
	
	// split
    int i=0, j=0;
    for(int k=0; k<origin.size(); k++)
    {
        if (k<first.size())
        {
            first.set(i, origin.get(k));
            i++;
        }

        if (k>=first.size())
        {
            second.set(j, origin.get(k));
            j++;
        }
    }

	
	// recursiv splitAndMerge of lowerArray and greaterArray
    splitAndMerge(first);
    splitAndMerge(second);
	// merge
    merge(first, second, origin);
}

void merge(Array& first, Array& second, Array& result)
{
	// Sorted merge -> merge by checking for all elements which should be stored first into result

    int ind1=0, ind2=0;
    for(int i=0; i<result.size(); i++)
    {
        if (ind1==first.size())
        {
            result.set(i, second.get(ind2));
            ind2++;
        }

        else if (ind2==second.size())
        {
            result.set(i, first.get(ind1));
            ind1++;
        }
        else if (first.get(ind1)<=second.get(ind2))
        {
            result.set(i, first.get(ind1));
            ind1++;
        }
        else
        {
            result.set(i, second.get(ind2));
            ind2++;
        }
    }
}

void mergeSort(Array& toSort)
{
    splitAndMerge(toSort);
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	uint elementCount=20;
	MainWindow::instruction_duration = 50;
	w = new TestMainWindow(mergeSort, elementCount);
	w->show();

	return a.exec();
}
