#ifndef _DYNAMIXEL_H_
#define _DYNAMIXEL_H_

#include <iostream>
#include "dynamixel_sdk.h"
#include <sstream>
#include <string>

// Protocol setting
#define PROTOCOL_VERSION 2.0        // Dynamixel protocol version 2.0

// Default setting
#define DXL_ID 1                    // Dynamixel Motor ID
#define BAUDRATE 57600              // Dynamixel Baudrate
#define DEVICENAME "/dev/ttyUSB0"               // Linux COM port
#define DXL_MOVING_STATUS_THRESHOLD 20 // Dynamixel Motor position error set

// Control tavle addresses for Dynamixel MX-64
#define ADDR_TORQUE_ENABLE 64       // Address for torque enable
#define ADDR_ACCELERATION_LIMIT 40  // Address for acc limit
#define ADDR_VELOCITY_LIMIT 44      // Address for velocity limit
#define ADDR_GOAL_VELOCITY 104      // Address for goal velocity
#define ADDR_GOAL_POSITION 116      // Address for goal position
#define ADDR_PRESENT_POSITION 132   // Address for present position
#define ADDR_OPERATING_MODE 11      // Address for operating mode

#define VELOCITY 50

class Dynamixel
{
    public:
        Dynamixel();
        virtual ~Dynamixel();
        void init();
        void set_torque();
        void set_buadrate();
        void open_port();
        void close_port();
        //void control_test();
        void control_run();
        void control_stop();
        void set_rpm();
        void set_operating_mode();
        void torque_on();
        void torque_off();
        int32_t control(std::string command);



    private:
        int32_t _dxl_comm_result = 0;
        uint8_t _dxl_error = 0;
        int32_t _dxl_goal_rpm = 0;
        int32_t _dxl_present_postion;

        dynamixel::PortHandler* portHandler = nullptr;
        dynamixel::PacketHandler* packetHandler = nullptr;   

        std::vector<std::string> seperate_cmd(std::string str, char operator_char);
        std::vector<std::string> seperate_option(std::string str, char operator_char);

};



#endif