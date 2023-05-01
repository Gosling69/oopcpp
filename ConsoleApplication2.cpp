#include <iostream>
#include <string> 
#include <random>
#include "Tasks.h"

using std::cout;
using std::cin;
using std::endl;

char getRandomOperator() {
    char operators[4] = { '+', '-', '/', '*' };
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1, 50);
    return operators[distr(gen) % 4];
}

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(10, 20);

    Container<Task *> tasksCont;
    Container<Task *> toAddCont;
    Container<std::string> results;

    for (int i = 0; i < distr(gen); i++) {
        int rndCase = distr(gen) % 5;
        switch (rndCase) {
        case 0:
            tasksCont.push_front(new Ariphmetic(distr(gen), distr(gen), getRandomOperator()));
            break;
        case 1:
            tasksCont.push_front(new Ariphmetic(distr(gen), distr(gen), getRandomOperator()));
            break;
        case 2:
            tasksCont.push_front(new Ariphmetic(distr(gen), distr(gen), getRandomOperator()));
            break;
        case 3:
            tasksCont.push_front(new AddTask(&toAddCont, new Ariphmetic(distr(gen), distr(gen), getRandomOperator())));
            break;
        case 4:
            tasksCont.push_front(new AddTask(&toAddCont, new Ariphmetic(distr(gen), distr(gen), getRandomOperator())));
            break;
        default:
            tasksCont.push_front(new Ariphmetic(distr(gen), distr(gen), getRandomOperator()));
            break;
        }
    }

    ClearCont<std::string> * clearResults = new ClearCont(&results);
    ClearCont<Task * > * clearTasks = new ClearCont(&tasksCont);
    ClearCont<Task * >* clearToAddCont = new ClearCont(&toAddCont);

    GetObjectsInCont * getObjsInCont = new GetObjectsInCont(&tasksCont, "Get Objects in Tasks Container");
    getObjsInCont->execute();
    cout << getObjsInCont->toString() << endl << endl;

    GetTasksWithResultInCont * getTasksWithRes = new GetTasksWithResultInCont(&tasksCont, "Get Tasks with Result in Tasks Container");
    getTasksWithRes->execute();
    cout << getTasksWithRes->toString() << endl << endl;

    GetAllObjs * getAll = new GetAllObjs("GetAll");
    getAll->execute();
    cout << getAll->toString() << endl << endl;

    int cntLen = tasksCont.get_length();
    for (int i = 0; i < cntLen; i++) {
        Task* task = tasksCont.remove_front();
        task->execute();
        results.push_front(task->toString());
        delete task;
    }

    cout << results << endl << endl;

    int toAddCntLen = toAddCont.get_length();
    for (int i = 0; i < toAddCntLen; i++) {
        Task * task = toAddCont.remove_back();
        delete task;
    }
    
    clearTasks->execute();
    clearResults->execute();
    clearToAddCont->execute();

    delete clearResults;
    delete clearTasks;
    delete getAll;
    delete getTasksWithRes;
    delete getObjsInCont;
    delete clearToAddCont;

    cout << "Total Objects Count: " << Object::get_count() << endl;

}
