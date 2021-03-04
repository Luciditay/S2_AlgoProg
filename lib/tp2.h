#ifndef TP2_H
#define TP2_H

#include "mainwindow.h"
#include "array.h"
#include "thread.h"

class SorterThread : public TestThread<std::function<void(Array&)> >
{
public:
	explicit SorterThread(MainWindow* mainWindow,
						  std::function<void(Array&)> sortFunction, QObject *parent = nullptr)
		: TestThread(mainWindow, sortFunction, parent)
    {
        srand(time(NULL));
        mainWindow->addIntParam("n", 7+rand()%10);
    }
	void run() override;
	void assertSort(const Array& array) const;
	const QString& errorMessage() const;
};

class TestMainWindow : public MainWindow
{
	Q_OBJECT

public:
    explicit TestMainWindow(std::function<void(Array&)> sortFunction,
                            QWidget *parent=nullptr);

	~TestMainWindow() {}
};
#endif // TP1_H
