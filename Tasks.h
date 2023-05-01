#pragma once

#include <iostream>
#include <string> 
#include <format>
#include "./Container.h"

class Object {
public:
    virtual std::string toString() const = 0;
    static int get_count() { return sm_count; }
protected:
    static int sm_count;
};
int Object::sm_count = 0;

class Task : public Object {
public:
    Task() { Object::sm_count++; }
    virtual ~Task() { Object::sm_count--; }
    std::string toString() const {    
        return std::format("Completed: {}\n", m_completed);
    };
    virtual void execute() {};
protected:
    bool m_completed = false;
};

class Named : public Object {
public:
    Named(std::string m_name = "") : m_name(m_name) {};
    std::string getName() {
        return m_name;
    };
    std::string toString() const {
        return std::format("Name: {}\n", m_name);
    };
protected:
    std::string m_name;
};


class TaskWithResult : public Task {
public:
    int get_result() { return m_result; }
    std::string toString() const {
        return std::format("Result: {}\n", m_result);
    };
protected:
    int m_result = 0;
};

class Ariphmetic : public Named, public TaskWithResult {
public:
    Ariphmetic(int m_arg1, int m_arg2, char m_operation, std::string m_name = "") : 
        Named(m_name), 
        m_arg1(m_arg1), 
        m_arg2(m_arg2), 
        m_operation(m_operation) 
    {};
    void execute() {
        switch (m_operation) {
        case '+':
            m_result = m_arg1 + m_arg2;
            break;
        case '-':
            m_result = m_arg1 - m_arg2;
            break;
        case '*':
            m_result = m_arg1 * m_arg2;
            break;
        case '/':
            if (!m_arg2) {
                m_error = "Division By Zero";
            }
            else {
                m_result = m_arg1 / m_arg2;
            }
            break;
        default:
            break;
        }
        m_completed = true;
    }
    std::string toString() const {
        return std::format("Ariphmetic Task: {} {} {}\n", m_arg1, m_operation, m_arg2) +
            Named::toString() +
            TaskWithResult::toString() +
            Task::toString() + 
            std::format("Error: {}\n", m_error);
    };

private:
    int m_arg1, m_arg2;
    char m_operation;
    std::string m_error = "";
};

class AddTask : public Task, public Named {
public:
    AddTask(Container<Task*> * m_container, Task * m_task, std::string m_name = "") :
        Named(m_name),
        m_container(m_container),
        m_task(m_task)
    {};
    void execute() {
        m_container->push_front(m_task);
        m_completed = true;
    };
    std::string toString() const {
        return "AddTask\n" + Task::toString() + Named::toString();
    };
private:
    Container<Task *> * m_container;
    Task * m_task;
};

class GetObjectsInCont : public TaskWithResult, public Named {
public:
    GetObjectsInCont(Container<Task*> * m_container, std::string m_name = "") :
        Named(m_name),
        m_container(m_container)
    {};
    void execute() {
        m_result = m_container->get_length();
        m_completed = true;
    }
    std::string toString() const {
        return "Get Objects in Container\n" + TaskWithResult::toString() + Named::toString();
    };
private:
    Container<Task *> * m_container;
};

class GetTasksWithResultInCont : public TaskWithResult, public Named {
public:
    GetTasksWithResultInCont(Container<Task*> * m_container, std::string m_name = "") :
        Named(m_name),
        m_container(m_container)
    {};
    void execute() {
        int res = 0;
        for (Container<Task*>::iterator it = m_container->begin(); it != nullptr; ++it) {
            Task* task = (*it);
            TaskWithResult* taskWithRes = dynamic_cast<TaskWithResult*>(task);
            if (taskWithRes) res++;
        }
        m_completed = true;
        m_result = res;
    };
    std::string toString() const {
        return "Get Task With Result in Container\n" + TaskWithResult::toString() + Named::toString();
    };
private:
    Container<Task *> * m_container;
};

template<typename T>
class ClearCont : public Task {
public:
    ClearCont(Container<T> * m_container) :
        m_container(m_container)
    {};
    void execute() {
        m_container->clear();
        m_completed = true;
    }
    std::string toString() const {
        return "Clear Container\n" + Task::toString();
    };
private:
    Container<T> * m_container;

};

class GetAllObjs : public TaskWithResult, public Named {
public:
    GetAllObjs(std::string m_name = "") : Named(m_name) {};
    void execute() {
        m_result = Object::get_count();
        m_completed = true;
    };
    std::string toString() const {
        return "Get All Objects\n" + TaskWithResult::toString() + Named::toString();
    };
};

