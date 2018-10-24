//
// Created by Martin Hermant on 24/10/2018.
//

#ifndef PMCPP_ABSTRACTSERVER_H
#define PMCPP_ABSTRACTSERVER_H




class AbstractServer{
public:
    virtual int send(API::ServerMsg & msg) = 0;
    virtual int send(API::ServerMsg && msg) = 0;
};
#endif //PMCPP_ABSTRACTSERVER_H
