#pragma once
using namespace std;

class My_own_string {
private:
    size_t size;
public:
    char* my_string = nullptr;
    size_t GetSize() const
    {
        return size;
    }
    void SetSize(int i)
    {
        size = i;
    }
    My_own_string();
    My_own_string(const My_own_string& orig);
    My_own_string(My_own_string&& orig);
    My_own_string(char* val);
    const char& operator[](std::size_t i) const {
        return my_string[i];
    }
    My_own_string& operator=(const My_own_string& right)
    {
        My_own_string tmp = right;
        swap(my_string, tmp.my_string);
        swap(size, tmp.size);
        return *this;
    }
    My_own_string& operator=(My_own_string&& right)
    {
        swap(my_string, right.my_string);
        swap(size, right.size);
        return *this;
    }
};