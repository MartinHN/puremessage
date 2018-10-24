//
// Created by Martin Hermant on 24/10/2018.
//

#ifndef PMCPP_API_H
#define PMCPP_API_H

namespace API {
    typedef enum {
        REGISTER,
        UNREGISTER

    } ConnectionProtocol;

    typedef std::string ServerMsg;

    ServerMsg createServerMessage(std::string cmd, std::string args) {
        return cmd + ":" + args;
    }
    ServerMsg createServerMessage(zmq::message_t & m){
        return toStr(m);
    }

    zmq::message_t createZmqMessage(ServerMsg & msg){
        return zmq::message_t(msg.data(),msg.size());
    }
}
#endif //PMCPP_API_H
