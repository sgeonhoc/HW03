#include <string>
#include <iostream>

class Item {
public:
    Item(const std::string& name = "", int price = 0) : name_(name), price_(price) {}

    const std::string& GetName() const { return name_; }
    int GetPrice() const { return price_; }

    void Clear() {
        name_ = "";
        price_ = 0;
    }

    void PrintInfo() const {
        std::cout << "[이름: " << name_ << ", 가격: " << price_ << "G]" << std::endl;
    }

private:
    std::string name_;
    int price_;
};

template<typename T>
class Inventory {
public:
    Inventory(int capacity = 10) {
        capacity_ = (capacity > 0) ? capacity : 1;
        size_ = 0;
        pItems_ = new T[capacity_];
    }

    ~Inventory() {
        if (pItems_ != nullptr) {
            delete[] pItems_;
            pItems_ = nullptr;
        }
    }

    void AddItem(const T& item) {
        if (size_ < capacity_) {
            pItems_[size_] = item;
            size_++;
        }
        else {
            std::cout << "인벤토리가 꽉 찼습니다!" << std::endl;
        }
    }

    void RemoveLastItem() {
        if (size_ > 0) {
            size_--;
            pItems_[size_].Clear();
        }
        else {
            std::cout << "인벤토리가 비어있습니다." << std::endl;
        }
    }

    int GetSize() const { return size_; }
    int GetCapacity() const { return capacity_; }

    void PrintAllItems() const {
        std::cout << "\n--- 현재 목록 (" << size_ << "/" << capacity_ << ") ---" << std::endl;
        for (int i = 0; i < size_; ++i) {
            pItems_[i].PrintInfo();
        }
        std::cout << "------------------------------------------\n" << std::endl;
    }

private:
    T* pItems_;
    int capacity_;
    int size_;
};

int main() {
    Inventory<Item>* itemInventory = new Inventory<Item>();

    for (int i = 0; i < 11; ++i) {
        itemInventory->AddItem(Item("Item" + std::to_string(i), i * 100));
    }

    itemInventory->PrintAllItems();

    delete itemInventory;

    return 0;
}