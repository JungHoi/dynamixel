#include <iostream>
#include <stdio.h>
#include <sstream>
#include <memory>
#include <vector>
#include <string.h>
#include <chrono>
#include <unistd.h>
#include <sys/select.h>

//#include <windows.h>
//#pragma comment (lib, "winmm.lib")

// user input을 받아서 처리하기 위하여 일정 시간마다 timeover 반환 - microsecond
int32_t check_std_in(int32_t a_timeout)
{
    //fd_set rfds;
    //struct timeval timeout;

    //FD_ZERO(&rfds);                         // 0으로 초기화
    //FD_SET(0, &rfds);                       // 파일 디스크립터 0 (stdin) 설정

    //timeout.tv_sec = a_timeout / 1000000;     // timeout 설정
    //timeout.tv_usec = a_timeout % 1000000;    // timeout 설정

    //return select(1, &rfds, nullptr, nullptr, &timeout) > 0;

    return 0;
}

// string을 첫번째 구분자를 기준으로 command, option으로 분리
std::vector<std::string> seperate_cmd(std::string str, char operator_char)
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

int main(void)
{
    bool loop = true;
    char cmd_input[256];

    std::cout << "main start" << std::endl;

    auto time = std::chrono::high_resolution_clock::now();
    auto curTime = time;
    //long time = timeGetTime();
    //long curTime = 0;

    while (loop)
    {
        
        //if (!check_std_in(10000))     continue;

        curTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(curTime-time).count();
        
        if (duration < 50)  continue;
        
        time = curTime;
        //curTime = timeGetTime();
        //if (curTime < time + 50)       continue;

        //time = curTime;


        memset(cmd_input, 0x00, 256);
        fgets(cmd_input, 256, stdin);
        std::string str(cmd_input);
        str.replace(str.find("\n"), 1, "");
        std::vector<std::string> input = seperate_cmd(str, ' ');

        if (input.size() < 1)    continue;


        if (input[0] == "finish")
        {
            loop = false;
        }
        else if (input[0] == "clear")
        {
            system("clear");
        }
        else
        {

        }
    }

    std::cout << "main end" << std::endl;

    return 0;
}