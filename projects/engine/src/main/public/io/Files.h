#pragma once

#include <string>
#include <libloaderapi.h>

class Files {
public:
    static std::string getCurrentPath() {
        char buffer[255];
        GetModuleFileName(NULL, buffer, 255);
        auto exepath = std::string(buffer);
		return exepath;
    };
};
