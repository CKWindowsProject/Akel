// This file is a part of AtlasEngine
// CREATED : 03/04/2021
// UPDATED : 11/04/2021

#include <Core/core.h>

void TERMINATE()
{
    std::cout << "EXIT FAILURE: emergency abortion program" << std::endl;
    abort();
}

namespace AE::Core
{
    void log::report(enum LogType type, std::string message, std::string path)
    {
        std::ofstream test(getTime(type, path).c_str());
        if(test)
            test << message;
        if(type == FATAL_ERROR)
        {
            std::set_terminate(TERMINATE);
            std::terminate();
        }
    }

    std::string log::getTime(enum LogType type, std::string path)
    {
        time_t tmm = time(0);
        std::string date = ctime(&tmm);
        switch(type)
        {
            case MESSAGE: path.append("/Messages/"); break;
            case WARNING: path.append("/Warnings/"); break;
            case ERROR:
            case FATAL_ERROR: path.append("/Errors/"); break;
            default: break;
        }
        path.append(date);
        path.append(".log");

        return path;
    }
}