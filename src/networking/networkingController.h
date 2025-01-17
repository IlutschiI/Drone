#include "request.h"

class NetworkingController
{
private:
    /* data */
public:
    NetworkingController();

    void start();
    void handlePendingRequests(void (*callback)(Request));
};

