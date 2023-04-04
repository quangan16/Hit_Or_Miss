#pragma once
#include <vector>
#include <memory>


template <class T>

class ObjectPool {
private:
    std::vector<T> availableObjects;
    std::vector<T> inUseObjects;
    static ObjectPool* instance;
    ObjectPool() {}
public:
    static ObjectPool* getInstance()
    {
        if (instance == 0)
        {
            instance = new ObjectPool;
        }
        return instance;
    }

    void getAvailableObjectsSize()
    {
        std::cout << availableObjects.size();
    }

    void prepareObject(int poolSize, T obj) {
        for (int i = 0; i < poolSize; ++i) {
            availableObjects.push_back(obj);
            std::cout << availableObjects.size();
        }
    }

    virtual ~ObjectPool() {
        for (auto obj : availableObjects) {
            obj.reset();
        }
        for (auto obj : inUseObjects) {
            obj.reset();
        }
        instance = nullptr;
    }


    T acquireObject() {
        if (availableObjects.empty()) {
            return nullptr;
        }
        T obj = availableObjects.back();
        availableObjects.pop_back();
        inUseObjects.push_back(obj);
        return obj;
    }

    void releaseObject(T obj) {
        auto it = std::find(inUseObjects.begin(), inUseObjects.end(), obj);
        if (it != inUseObjects.end()) {
            inUseObjects.erase(it);
            availableObjects.push_back(obj);
        }
    }
};

template <class T>
ObjectPool<T>* ObjectPool<T>::instance = nullptr;