#include <iostream>
#include "sortingcompetition.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    SortingCompetition* obj = new SortingCompetition(argv[1]);
    obj->setFileName(argv[1]);
    obj->readData();
    obj->prepareData();
    //time begin
    obj->sortDataRadixHeap();
    //time end
    obj->outputData(argv[2]);

    delete obj;
    return 0;
}

