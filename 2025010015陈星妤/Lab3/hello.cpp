#include <iostream>

bool getDoubled(int value, int & result)
{
    result = value * 2;
    return true;
}

int main()
{
    std::cout << "name:chenxingyu" << std::endl;
    std::cout << "id:2025010015" << std::endl;

    bool isStudent = true;
    std::cout << "Is student: " << isStudent << std::endl;

    int num = 15;
    int res;
    getDoubled(num, res);
    std::cout << num << " the double of is " << res << std::endl;

    return 0;
}