#include "lib/tp4.h"

#include "lib/mainwindow.h"
#include <QApplication>
#include <time.h>
#include <stdio.h>

MainWindow* w = nullptr;
using std::size_t;
using std::string;

int Heap::leftChild(int nodeIndex)
{
    return nodeIndex*2+1;
}

int Heap::rightChild(int nodeIndex)
{
    return nodeIndex*2+2;
}

void Heap::insertHeapNode(int heapSize, int value)
{
    int i = heapSize;

    this->set(i, value);

    while(i>0 && this->get(i)>this->get(i/2))
    {
        swap(i, (i-1)/2);
        i=(i-1)/2;
    }
}

void Heap::heapify(int heapSize, int nodeIndex)
{
    int largest = nodeIndex;

    if (rightChild((nodeIndex))< heapSize && this->get(leftChild(nodeIndex)) > this->get(largest))
        largest=leftChild(nodeIndex);

    if (leftChild(nodeIndex) < heapSize && this->get(rightChild(nodeIndex)) > this->get(largest))
        largest = rightChild(nodeIndex);

    if(largest != nodeIndex)
    {
        swap(nodeIndex, largest);
        this->heapify(heapSize, largest);
    }
}

void Heap::buildHeap(Array& numbers)
{
    for (int i=0; i<numbers.size(); i++)
    {
        this->insertHeapNode(i, numbers.get(i));
    }
}

void Heap::heapSort()
{
    for (int i=this->size()-1; i!=-1; i--)
    {
        this->swap(0, i);
        this->heapify(i, 0);
    }
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    MainWindow::instruction_duration = 50;
    w = new HeapWindow();
	w->show();

	return a.exec();
}
