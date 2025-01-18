#include "request.h"
#include "response.h"

class NetworkingController
{
private:
    /* data */
public:
    NetworkingController();

    void start();
    void handlePendingRequests(Response (*callback)(Request));
};

