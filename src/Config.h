#pragma once

namespace Config {
    static const int APP_WINDOW_WIDTH = 1000;
    static const int APP_WINDOW_HEIGHT = 800;
    static const int APP_DESIRED_FRAMERATE = 60;

    //static const std::string ARDUINO_DEVICE_NAME = "COM3";  //if on windows this will be something like like COM3
    static const std::string ARDUINO_DEVICE_NAME = "COM3";  //if on windows this will be something like like COM3
    static const int ARDUINO_BAUD_RATE = 57600;
    static const int MAX_BRIGHTNESS = 230;      //foing full brightness (255) causes issues, so limiting here

    static const int PIN_STRETCH_INPUT = 2;

    static const int PIN_RGB_PWM_BLUE_OUTPUT = 3;
};
    