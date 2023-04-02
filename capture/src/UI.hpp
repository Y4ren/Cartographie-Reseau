#pragma once

#include <iomanip>
#include <termios.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <thread>
#include <pcap.h>
#include <string.h>

#include "manager.hpp"
#include "active.hpp"

class Keyboard{
private:
    inline static bool stopped = false;
    inline static struct termios orig_termios;
    inline static thread keyboardThread;
    

    static void waitingInput();
    static void enableRawMode();
    static void disableRawMode();

public:
    inline static char keyPressed;
    inline static bool ctrl;
    
    static void start();
    static void stop();
    static void resetKeyPress();

};

class UI{
private:
    inline static bool stopped = false;
    inline static bool activeMode = false;

    static string loadingBar(float percent, int size);

    static void eraseLines();

    static void eraseLines(int numberOfLine);


public:
    static void stop();

    static void realTimeCaptureInterface(string interface, pcap_t *handle);

    static void readPcapFileInterface(string filePath);
};