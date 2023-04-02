#include "UI.hpp"

void Keyboard::disableRawMode()
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}
void Keyboard::enableRawMode()
{
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
void Keyboard::start()
{
    stopped = false;
    keyboardThread = thread(&Keyboard::waitingInput);
}
void Keyboard::stop()
{
    stopped = true;
    keyboardThread.join();
}

void Keyboard::resetKeyPress()
{
    keyPressed = '\0';
}

void Keyboard::waitingInput()
{
    enableRawMode();

    while (!stopped)
    {
        char c = '\0';
        read(STDIN_FILENO, &c, 1);
        ctrl = false;
        if (c < 27)
        {
            c += 'a' - 1;
            ctrl = true;
        }
        if (c != 96)
        {
            keyPressed = c;
        }
    }

    disableRawMode();
}

string UI::loadingBar(float percent, int size)
{
    string bar = "";
    bar += "[";
    for (int i = 0; i < size; i++)
    {
        if (i * (100 / size) < percent)
            bar += "#";
        else
            bar += " ";
    }
    bar += "]";
    return bar;
}

void UI::eraseLines()
{
    eraseLines(1);
}

void UI::eraseLines(int numberOfLine)
{
    for (int i = 0; i < numberOfLine; i++)
    {
        cout << "\033[A\33[2K\r";
    }
}

void UI::stop()
{
    stopped = true;
}

void UI::realTimeCaptureInterface(string interface, pcap_t *handle)
{
    string url = "https://" + Manager::getSelfIPv4(interface) + ":3000";
    Keyboard::start();
    do
    {
        switch (Keyboard::keyPressed)
        {
        case 'q':
            stopped = true;
            break;
        case 'a':
            activeMode = !activeMode;
            Keyboard::stop();

            Active::startActiveDetection();

            Keyboard::start();
            Keyboard::resetKeyPress();
            break;
        }
        cout << "Started listening on " + interface + "...\r\n";
        cout << "You can go to " + url + " to visualize the network\r\n";
        cout << "Listened to " + to_string(Manager::currentPacketIndex) + " packets and " + to_string(Manager::totalSizeProcessed) + " bytes of data\r\n";
        cout << "There are " + to_string(Manager::numberOfNodes()) + " machines found on the networks\r\n";
        cout << "(a)Active Mode : ";
        cout << (activeMode ? "Enabled" : "Disabled");
        cout << "\r\n";
        cout << "Press (q) to quit\r\n";
        usleep(100000);
        eraseLines(6);
    } while (!stopped);

    pcap_breakloop(handle);
    Keyboard::stop();
    cout << "Listening successfully stopped." << endl;
}

void UI::readPcapFileInterface(string filePath)
{
    std::ifstream in(filePath, std::ifstream::ate | std::ifstream::binary);
    long int fileSize = in.tellg();
    cout << "Currently reading " + filePath << endl;
    do
    {
        float ratio = Manager::totalSizeProcessed / (float)fileSize * 100;
        cout << loadingBar(ratio, 30) + " - " + to_string(ratio) + "% | " + to_string(Manager::totalSizeProcessed) + "/" + to_string(fileSize) << endl;
        usleep(300000);
        eraseLines();
    } while (!stopped);
    cout << loadingBar(100, 30) + " - 100% | " + to_string(fileSize) + "/" + to_string(fileSize) << endl;
}