#include "ssl-conn.h"

using namespace handy;
using namespace std;

int main(int argc, const char* argv[]) {
    Logger::getLogger().setLogLevel(Logger::LTRACE);
    EventBase ebase;
    Signal::signal(SIGINT, [&]{ ebase.exit(); });
    SSLConn::setSSLCertKey("server.pem", "server.pem");
    HttpServer ss(&ebase);
    int r = ss.bind("0.0.0.0", 1002);
    exitif(r, "bind failed %d %s", errno, strerror(errno));
    ss.setConnType<SSLConn>();
    ss.onGet("/hello", [](const HttpConnPtr& con) {
        HttpResponse resp;
        resp.body = Slice("hello world");
        con.sendResponse(resp);
    });
    ebase.loop();
    return 0;
}
