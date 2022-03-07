#ifndef EDIF_ERROR_H
#define EDIF_ERROR_H
#include <functional>
#include "edifparse.h"
namespace edifparse {

    void edif_error_wrap(Callback& callback, const int line_no, const std::string& near_text, const char* fmt, ...);
}
#endif
