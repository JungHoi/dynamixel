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

void Dynamixel::controlTestRun()
{
    std::cout << "Motor running" << std::endl;
}

void Dynamixel::controlTestStop()
{
    std::cout << "Motor stop!" << std::endl;
}