//
// Created by Martin Hermant on 24/10/2018.
//

#ifndef PMCPP_UTILS_H
#define PMCPP_UTILS_H

#include <iostream>

#include <unistd.h>
#include <string>



#define log(l) std::cout << l << std::endl;

std::string toStr(const zmq::message_t & m){ return std::string((char*)m.data(),m.size()); }


#endif //PMCPP_UTILS_H
