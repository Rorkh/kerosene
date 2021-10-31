#include <iostream>
#include <sstream>
#include <fstream>

#include <chrono>
#include <thread>

#include "misc/consts.h"
#include "misc/utils.h"

#include "thirdparty/picojson.h"

int main()
{
    using namespace std::chrono_literals;
    std::cout << "Written for Lord of Panckaes by Solaire :)\nPress C to make mouse click (or configured keys).\n";

    int first_key = constant::PRIMARY_KEY;
    int second_key = 0x00;

    if (utils::IsFileExists("config.json")) 
    {
        std::ifstream file;
        std::stringstream ss;

        file.open("config.json", std::ifstream::binary);
        ss << file.rdbuf();
        file.close();

        picojson::value v;
        ss >> v;

        std::string err = picojson::get_last_error();
        if (!err.empty()) {
            std::cerr << err << std::endl;
            return -1;
        }

        picojson::object config = v.get<picojson::object>();

        if (!config["firstKey"].is<picojson::null>()) first_key = config["firstKey"].get<double>();
        if (!config["secondKey"].is<picojson::null>()) second_key = config["secondKey"].get<double>();
    }

    bool first_pressed = false;
    bool second_pressed = false;

    while (true)
    {
        if (utils::IsKeyPressed(first_key)) {
            utils::LeftMouseDown();
            std::this_thread::sleep_for(5ms);

            first_pressed = true;
        }
        else
        {
            if (first_pressed)
            {
                utils::LeftMouseUp();
                first_pressed = false;
            }
        }

        if (second_key != 0x00) {
            if (utils::IsKeyPressed(second_key)) {
                std::cout << "1\n";
                utils::RightMouseDown();
                std::this_thread::sleep_for(5ms);

                second_pressed = true;
            }
            else
            {
                if (second_pressed)
                {
                    utils::RightMouseUp();
                    second_pressed = false;
                }
            }
        }
    }
}