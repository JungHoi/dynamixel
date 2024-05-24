#include "dynamixel.h"

Dynamixel::Dynamixel()
{
    std::cout << "생성자" << std::endl;;
}

Dynamixel::~Dynamixel()
{
    std::cout << "소멸자" << std::endl;
}

void Dynamixel::controlTest()
{
    std::cout << "Control OK" << std::endl;
}