#include <assert.h>
#include <iostream>
#include <list>
#include <stdio.h>

using namespace std;

class Observable;

// 观察者接口
class Observer
{
public:
    Observer() {}
    virtual ~Observer() {}
    virtual void update(const Observable &observable, const void *arg) = 0;

private:
    Observer(const Observer &);
    Observer &operator=(const Observer &);
};

// 被观察者类
class Observable
{
public:
    virtual ~Observable()
    {
        observers.clear();
    }
    // 注册观察者
    void registerObserver(Observer *observer)
    {
        assert(observer);
        observers.push_back(observer);
    }
    // 移除观察者
    void removeObservers(Observer *observer)
    {
        observers.remove(observer);
    }
    void setChanged(bool changed)
    {
        this->changed = changed;
    }
    // 通知观察者
    void notifyObservers()
    {
        notifyObservers(NULL);
    }
    // 通知观察者 with argument
    void notifyObservers(const void *arg)
    {
        if (!changed)
            return;
        this->setUnChanged(!this->changed);
        list<Observer *>::const_iterator it;
        for (it = observers.cbegin(); it != observers.cend(); ++it)
        {
            Observer *observer = *it;
            observer->update(*this, arg);
        }
    }

protected:
    void setUnChanged(bool unChanged)
    {
        changed = unChanged;
    }

private:
    list<Observer *> observers;
    bool changed;
};

class AObserver : public Observer
{
public:
    void update(const Observable &observable, const void *arg)
    {
        printf("[%s]:B 观察到 arg = %d \n", __FUNCTION__, *((int *)arg));
    }
};

class BObserver : public Observer
{
public:
    void update(const Observable &observable, const void *arg)
    {
        printf("[%s]:B 观察到 arg = %d \n", __FUNCTION__, *((int *)arg));
    }
};

int main(int argc, char const *argv[])
{
    cout << "-----------------------------\n";
    Observable observable;
    observable.setChanged(true);

    AObserver *a = new AObserver();
    BObserver *b = new BObserver();
    observable.registerObserver(a);
    observable.registerObserver(b);
    int num = 2;
    observable.notifyObservers(&num);

    cout << "-----------------------------\n";
    return 0;
}
