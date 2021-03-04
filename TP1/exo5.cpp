#include "tp1.h"
#include <QApplication>
#include <time.h>

int isMandelbrot(Point z, int n, Point point){

    if (n==0)
    {
        return 1;
    }

    else
    {
        z.x = (z.x)*(z.x) - (z.y)*(z.y) + point.x;
        z.y = 2*z.x*z.y + point.y;
        int module = sqrt((z.x*z.x) + (z.y*z.y));

        if (module>2)
        {
            return 0;
        }
        return isMandelbrot(z, n-1, point);
    }


    return 0;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* w = new MandelbrotWindow(isMandelbrot);
    w->show();

    a.exec();
}



