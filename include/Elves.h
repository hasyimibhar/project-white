//
//  Elves.h
//  project-white
//
//  Created by Hasyimi Bahrudin on 12/11/12.
//
//

#ifndef project_white_Elves_h
#define project_white_Elves_h

#include <string> 
#include <sstream>

template <typename T>
T from_string(const std::string &s) {

    std::istringstream ss (s);
    T t;
    ss >> t;
    return t;
}

template <typename T>
std::string to_string(const T &t) {
    
    std::ostringstream ss;
    ss << t;
    return ss.str();
}

#endif
