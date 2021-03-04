#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <functional>
#include <stdexcept>
#include <math.h>

#include <qglobal.h>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsView>
#include <QPushButton>
#include <QFormLayout>
#include <QLinkedList>
#include <QStack>
#include <QVector2D>
#include <QTimer>

#include "thread.h"

class AbstractArray;
class Array;

using std::size_t;


struct Point {
    float x;
    float y;

    Point(float x=0, float y=0) : x(x), y(y) {}
    float length() {
        return std::sqrt(x*x+y*y);
    }
    float squaredLength() {
        return x*x+y*y;
    }
};


class NumberGraphicsItem : public QGraphicsEllipseItem
{
public:
	explicit NumberGraphicsItem(const int _number, QGraphicsItem* parent=nullptr);
	void setNumber(const int _number);

	void paint(QPainter* painter, const QStyleOptionGraphicsItem *option,
			   QWidget *widget=nullptr) override;

	void displayDefault();
	void displayReadenState();
	void displayWrittenState();
	int number() const;

	static QColor baseColor;

private:
	enum State
	{
		DEFAULT=0,
		READEN,
		WRITEN,
		STATE_COUNT
	};
	void displayDefault(bool force);

	QString text;
	int _number;
	State state;
};

class MainWindow : public QMainWindow
{

	Q_OBJECT

public:
    static MainWindow* _instance;
    static MainWindow* instance();

	explicit MainWindow(QWidget* parent=nullptr);

	Array& mainArray() {return *arrays[0];}
	Array& newRandomArray(uint size);
	Array& newSortedRandomArray(uint size);
	Array& newArray(uint size);

	void resizeEvent(QResizeEvent*);
	void closeEvent(QCloseEvent*);

	void setBackground(QImage* image);

	virtual void updateLayout();
	void updateStatusItem(int itemWidth);
	void updateBackground();
	int updateNumberItems(int itemWidth, int &maxY, int &maxX);


    void pushFunctionCall(QString functionName, int parameter);
    void pushFunctionCall(QString functionName, int parameter1, int parameter2);
    void pushFunctionCall(QString functionName, Point parameter1, int parameter2, Point parameter3);
    void pushFunctionCall(QString functionName, const Array& parameter1, int parameter2);
    void pushFunctionCall(QString functionName, const Array& parameter1, const Array& parameter2, int parameter3, int parameter4);
    int popFunctionCall(int result);
    void popFunctionCall(QVariant result);

    void clearFunctionsCall();
    void clearArrays();

    QVariant& addIntParam(QString param_name, int defaultValue=0, int min=0, int max=100);
    QVariant& addFloatParam(QString param_name, float defaultValue=0, float min=0, float max=100);
    const QVariant& getParam(QString param_name);

    int updateFunctionCalls(int itemWidth, int &maxY, int &maxX);

	static unsigned long instruction_duration;

	bool eventFilter(QObject* object, QEvent* event);

    ~MainWindow();
public slots:
    virtual void updateScene();
    virtual void startWorkerThread();
    virtual void stopWorkerThread();
    virtual void handleResult();
    virtual void handleParamChanged();
    void updateInstructionDuration(int);

private:

	void initialize();

	QGraphicsView view;
    QWidget parametersView;
    QFormLayout parametersLayout;

	QVector<QVector<NumberGraphicsItem*> > numberItems;
	QVector<QGraphicsTextItem *> accessInfoItem;
	QGraphicsTextItem statusItem;
	QVector<Array*> arrays;

	QTimer timer;

	QGraphicsPixmapItem* background;

    QStack<QString> functionCalls;
    QLinkedList<QGraphicsTextItem *> functionCallItems;

	bool zoom;
	float scale;
	QPointF targetPos;

    int maxNumbersY;

protected:
	QGraphicsScene scene;
    QVBoxLayout* workerLayout;

    QPushButton startButton;
    QPushButton stopButton;

	QVector<QGraphicsItem*> toAdd;
	QVector<QPair<QGraphicsTextItem*, QString> > toUpdate;
	QVector<QGraphicsItem*> toRemove;

    QMap<QString, QVariant> parameters;

	Thread* workerThread;
	bool dirty;
};


#endif // MAINWINDOW_H
