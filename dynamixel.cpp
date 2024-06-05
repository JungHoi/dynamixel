#include "dynamixel.h"

Dynamixel::Dynamixel()
{
    //std::cout << "생성자" << std::endl;;
    portHandler = dynamixel::PortHandler::getPortHandler(DEVICENAME);
    packetHandler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);
    init();
}

Dynamixel::~Dynamixel()
{
    //std::cout << "소멸자" << std::endl;
    torque_off();
    close_port();
}

void Dynamixel::control_test()
{
    std::cout << "Control OK" << std::endl;
}

void Dynamixel::control_run()
{
    _dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, DXL_ID, ADDR_GOAL_VELOCITY, VELOCITY, &_dxl_error);
    if (_dxl_comm_result != COMM_SUCCESS)
	{
		std::cerr << "Failed to set goal_velocity! Error: " << _dxl_comm_result << std::endl;
	}
	else if (_dxl_error != 0)
	{
		std::cerr << "Error in setting goal_velocity! Error: " << _dxl_error << std::endl;
	}
	else
	{
		std::cout << "Goal velocity set to " << VELOCITY << " RPM!" << std::endl;
	}
    std::cout << "Motor running" << std::endl;
}


void Dynamixel::control_stop()
{
    _dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, DXL_ID, ADDR_GOAL_VELOCITY, 0, &_dxl_error);
    if (_dxl_comm_result != COMM_SUCCESS)
	{
		std::cerr << "Failed to set goal_velocity! Error: " << _dxl_comm_result << std::endl;
	}
	else if (_dxl_error != 0)
	{
		std::cerr << "Error in setting goal_velocity! Error: " << _dxl_error << std::endl;
	}
	else
	{
		std::cout << "Goal velocity set to 0 RPM!" << std::endl;
	}
    std::cout << "Motor stop" << std::endl;
}

void Dynamixel::init()
{
    _dxl_comm_result = 0;
    _dxl_error = 0;
    set_buadrate();
    open_port();
    set_operating_mode();
    torque_on();
}


void Dynamixel::set_vel()
{
    // Set veloicyty

}

void Dynamixel::set_operating_mode()
{
    _dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, DXL_ID, ADDR_OPERATING_MODE, 1, &_dxl_error);
    if (_dxl_comm_result == 0)
    {
        std::cerr << "Success to set operating mode!" << std::endl;
    }
    else
    {
        std::cerr << "Failed to set operating mode!" << std::endl;
    }
}

void Dynamixel::torque_on()
{
    _dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, DXL_ID, ADDR_TORQUE_ENABLE, 1, &_dxl_error);
    if (_dxl_comm_result != COMM_SUCCESS)
    {
        std::cerr << "Failed to enable torque!" << std::endl;
    }
    else if (_dxl_error != 0)
    {
        std::cerr << "Error in enable torque!" << std::endl;
    }
    else
    {
        std::cerr << "Torque on!" << std::endl;
    }
}

void Dynamixel::torque_off()
{
    //std::cout << "Motor stop!" << std::endl;
    _dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, DXL_ID, ADDR_TORQUE_ENABLE, 0, &_dxl_error);
    if (_dxl_comm_result != COMM_SUCCESS)
    {
        std::cerr << "Failed to disable torque!" << std::endl;
    }
    else if (_dxl_error != 0)
    {
        std::cerr << "Error in disable torque!" << std::endl;
    }
    else
    {
        std::cerr << "Torque off!" << std::endl;
    }
}

void Dynamixel::open_port()
{
    portHandler->openPort();
    std::cerr << "Open port!" << std::endl;
}

void Dynamixel::close_port()
{
   portHandler->closePort();
   std::cerr << "Close port!" << std::endl;
}

void Dynamixel::set_buadrate()
{
    portHandler->setBaudRate(BAUDRATE);
    std::cerr << "Set to Buadrate is " << BAUDRATE << std::endl;
}