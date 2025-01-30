#include "request.h"
#include "response.h"

class NetworkingController
{
private:
    long lastTimestamp=0;
    /* data */
public:
    NetworkingController();

    void start();
    void handlePendingRequests(Response (*callback)(Request));
};

