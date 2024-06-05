#include "dynamixel.h"

Dynamixel::Dynamixel()
{
    portHandler = dynamixel::PortHandler::getPortHandler(DEVICENAME);
    packetHandler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);
    
    init();
}

Dynamixel::~Dynamixel()
{
    torque_off();
    close_port();
}

void Dynamixel::control_run()
{
    
    if (_dxl_goal_rpm != 0)
    {
        _dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, DXL_ID, ADDR_GOAL_VELOCITY, _dxl_goal_rpm, &_dxl_error);
        std::cout << "Now RPM is " <<_dxl_goal_rpm << std::endl;
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
		    std::cout << "Motor running to " << _dxl_goal_rpm << "RPM!" << std::endl;
	    }
    }
    else
    {
        std::cout << "Please to set RPM~" << std::endl;
    }

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
		std::cout << "Motor stop" << std::endl;
	}
    
}

void Dynamixel::init()
{
    _dxl_comm_result = 0;
    _dxl_error = 0;
    set_buadrate();
    open_port();
    set_operating_mode();
}


void Dynamixel::set_rpm()
{
    //_dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, DXL_ID, ADDR_GOAL_VELOCITY, _dxl_goal_rpm, &_dxl_error);
    //if (_dxl_comm_result != COMM_SUCCESS)
	//{
	//	std::cerr << "Failed to set goal_velocity! Error: " << _dxl_comm_result << std::endl;
	//}
	//else if (_dxl_error != 0)
	//{
	//	std::cerr << "Error in setting goal_velocity! Error: " << _dxl_error << std::endl;
	//}
	//else
	//{
	//	std::cout << "Goal velocity set to " << _dxl_goal_rpm << " RPM!" << std::endl;
	//}
    std::cout << "Goal velocity set to " << _dxl_goal_rpm << " RPM!" << std::endl;
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

// string을 첫번째 구분자를 기준으로 command, option으로 분리
std::vector<std::string> Dynamixel::seperate_cmd(std::string str, char operator_char)
{
    std::string cmd = str;
    std::string option = "";
    size_t pos = std::string::npos;
    std::vector<std::string> rets;
    rets.clear();

    if (cmd.find("\n") != std::string::npos)   cmd.replace(cmd.find("\n"), 1, "");

    if (str.size() > 0)
    {
        pos = str.find(operator_char);
        if (pos != std::string::npos)
        {
            cmd = str.substr(0, pos);
            option = str.substr(pos + 1, str.size() - pos);
        }
    }

    rets.push_back(cmd);
    rets.push_back(option);

    return rets;
}

// string을 구분자를 기준으로 각각의 option으로 분리
std::vector<std::string> Dynamixel::seperate_option(std::string str, char operator_char)
{
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string string_buffer;

    if (str.find("\n") != std::string::npos) str.replace(str.find("\n"), 1, "");

    tokens.clear();
    while (getline(ss, string_buffer, operator_char))
    {
        if (string_buffer.size() > 0)
        {
            tokens.push_back(string_buffer);
        }
    }
    return tokens;
}

int32_t Dynamixel::control(std::string command)
{
    std::vector<std::string> input = seperate_cmd(command, ' ');

    if (input.size() < 1)   return 0;

    std::map<std::string, int32_t> _command_map;

    if (input.size() > 1)
    {
        _command_map.clear();
        std::vector<std::string> option = seperate_option(input[1], ' ');
        if (option.size() == 1)
        {
            _command_map.insert(make_pair(option[0], 0));
        }
        else
        {
            _command_map.insert(make_pair(option[0], atoi(option[1].c_str())));
        }
    }

    if (input[0] == "torque")
    {
        if (_command_map.find("on") != _command_map.end())
        {
            torque_on();
        }
        else if (_command_map.find("off") != _command_map.end())
        {
            torque_off();
        }
    }
    else if (input[0] == "rpm")
    {
        if (input.size() >1)
        {
            _dxl_goal_rpm = std::stoi(input[1]);
            set_rpm();
        }
    }
    else if (input[0] == "motor")
    {
        if (_command_map.find("run") != _command_map.end())
        {
            control_run();
        }
        else if (_command_map.find("stop") != _command_map.end())
        {
            control_stop();
        }
    }

    _command_map.clear();

    return 0;
}