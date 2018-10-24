#include "../include/PureMessage.hpp"
//#include "../lib/pureparameters/pureparameter.h"
int main(int argc, char *argv[])
{
    auto * root = ParameterGroup::getRoot();
    auto * group = root->addParameterGroup(new ParameterGroup("node"));
    auto * p = group->addParameter("child",5);
    ServerSync sync(root);
    log(sync.getFullState())
    Server server = Server(&sync);

    return server.run();
}
