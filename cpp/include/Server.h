//
// Created by Martin Hermant on 24/10/2018.
//

#ifndef PMCPP_SERVER_H
#define PMCPP_SERVER_H

class Server:public AbstractServer {
public:
    Server(ServerSync * _sync=nullptr){
        setServerSync(_sync);
    }
    void setServerSync(ServerSync * _sync){
        sync = _sync;
        if(sync) { sync->setServer(this); }
    }
    int run() {

        //  Prepare our context and socket
        zmq::context_t context(1);
        zmq::socket_t socket(context, ZMQ_REP);
        publisher = &socket;
        log("starting");
        auto addr = "tcp://*:3000";

        try { socket.bind(addr); }
        catch (zmq::error_t err) { return catchErr(err); }

        while (true) {
            zmq::message_t request;
            //  Wait for next request from client
            try {
                //log("recieving on : " << addr)
                socket.recv(&request);
            }
            catch (zmq::error_t err) { return catchErr(err); }

            //log("Received " << toStr(request));
            //  Do some 'work'
            //sleep(1);
            if(sync){
                auto m =API::createServerMessage(request);
                if(auto err = sync->processRequest(m)){
                    //  Send error
                    zmq::message_t reply(5);
                    memcpy(reply.data(), "Error", 5);
                    socket.send(reply);
                }
            }


        }

    }
    void freeLoop(){
        publisher = nullptr;
    }

    int catchErr(zmq::error_t & err){
        log(err.what());
        freeLoop();
        return err.num();
    }

    int send(API::ServerMsg & msg) override{
        if(publisher){
            return publisher->send(API::createZmqMessage(msg));
        }
    return 0;
    };
    int send(API::ServerMsg && msg) override{
        if(publisher){
            return publisher->send(API::createZmqMessage(msg));
        }
        return 0;
    };
    ServerSync * sync;
    zmq::socket_t* publisher;
};

#endif //PMCPP_SERVER_H
