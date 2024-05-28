#ifndef _DYNAMIXEL_H_
#define _DYNAMIXEL_H_

#include <iostream>
#include "dynamixel_sdk.h"

// Protocol setting
#define PROTOCOL_VERSION 2.0        // Dynamixel protocol version 2.0

// Default setting
#define DXL_ID 1                    // Dynamixel Motor ID
#define BAUDRATE 57600              // Dynamixel Baudrate
#define DEVICENAME ""               // Linux COM port
#define DXL_MOVING_STATUS_THRESHOLD 20 // Dynamixel Motor position error set

// Control tavle addresses for Dynamixel MX-64
#define ADDR_TORQUE_ENABLE 64       // Address for torque enable
#define ADDR_ACCELERATION_LIMIT 40  // Address for acc limit
#define ADDR_VELOCITY_LIMIT 44      // Address for velocity limit
#define ADDR_GOAL_VELOCITY 104      // Address for goal velocity
#define ADDR_GOAL_POSITION 116      // Address for goal position
#define ADDR_PRESENT_POSITION 132   // Address for present position
#define AADR_OPERATING_MODE 11      // Address for operating mode


class Dynamixel
{
    public:
        Dynamixel();
        virtual ~Dynamixel();
        void controlTest();
        void controlTestRun();
        void controlTestStop();
};


#endif