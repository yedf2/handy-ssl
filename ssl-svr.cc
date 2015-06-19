#include "ssl-conn.h"

using namespace handy;
using namespace std;

int main(int argc, const char* argv[]) {
    Logger::getLogger().setLogLevel(Logger::LTRACE);
    EventBase ebase;
    Signal::signal(SIGINT, [&]{ ebase.exit(); });
    SSLConn::setSSLCertKey("server.pem", "server.pem");
    TcpServer ss(&ebase);
    int r = ss.bind("0.0.0.0", 1002);
    exitif(r, "bind failed %d %s", errno, strerror(errno));
    ss.onConnCreate([]{ return TcpConnPtr(new SSLConn); });
    ss.onConnRead([](const TcpConnPtr& con) {
        con->send(con->getInput());
        con->getInput().clear();
    });

    TcpServer ts(&ebase);
    r = ts.bind("0.0.0.0", 1003);
    exitif(r, "bind failed %d %s", errno, strerror(errno));
    ts.onConnRead([](const TcpConnPtr& con) {
        con->send(con->getInput());
        con->getInput().clear();
    });
    ebase.loop();
    return 0;
}
