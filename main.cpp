#include "MyWindow.h"
#include <QtWidgets/QApplication>
#include "SongColection.h"
#include "Controller.h"
#include <fstream>
int main(int argc, char *argv[])
{

    //std::ifstream inputFile();

    QApplication a(argc, argv);
   
       /* TestController test;
        test.testAll();*/
        FileRepository colection{ "Songs.txt" };
        Controller control{ colection };
        MyWindow w{ control };
        w.show();
        return a.exec();
  
    
   
		return 0;

}
