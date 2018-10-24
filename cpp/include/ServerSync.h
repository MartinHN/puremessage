//
// Created by Martin Hermant on 24/10/2018.
//

#ifndef PMCPP_SERVERSYNC_H
#define PMCPP_SERVERSYNC_H


typedef std::string(*toStrVisitor)(AbstractParameter*) ;

class ServerSync{
public :
    ServerSync(ParameterGroup * _root):root(_root),isAnnounced(false) {

    };

    void setServer(AbstractServer * s){ server = s;isAnnounced = false; }

    int processRequest(API::ServerMsg & msg){
        if(!isAnnounced) {
            sendFullState();
            isAnnounced = true;
            return 0;
        }
        return 1;
    }

    void sendFullState(){
//        ParamIterators::Trav_Node i(root);
//        auto * p = i.next();
//        while(p){
//            p = i.next();
//        }


        send(API::createServerMessage("fullstate",getFullState()));
    }

    std::string getFullState(){
        return "{"+buildJSONFromTree(root,&ServerSync::getParameterDesc)+"}";
    }

    static std::string getParameterDesc(AbstractParameter * p ){
        return p->getNameStr()+":"+p->getValueAsString()+"("+p->getTypeNameStr()+")";
    }
    std::string buildJSONFromTree(ParameterGroup * pg , toStrVisitor f){
        std::string res = "";
        int idx = pg->params.size()-1;
        for(auto * p: pg->params){
            res+=f(p);
            if(idx!=0){ res+=","; }
            idx--;
        }
        for(ParameterGroup * p: pg->paramGroups){
            res+=p->name+":{"+buildJSONFromTree(p,f)+"}";
        }

        return res;

    }
    int send(API::ServerMsg && msg){
        if(server){
            return server->send(msg);
        }
        return 0;
    }

    ParameterGroup * root;
    AbstractServer * server;
    bool isAnnounced;
};
#endif //PMCPP_SERVERSYNC_H
