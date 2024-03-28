#include "App.h"
#include <iostream>

struct UserData {
  int something;
};

int main() {
  uWS::App app;
  app.ws<UserData>(
         "/*",
         {

             /* Just a few of the available handlers */
             .open = [](auto *ws) { ws->subscribe("oh_interesting_subject"); },
             .message = [](auto *ws, std::string_view message,
                           uWS::OpCode opCode) { ws->send(message, opCode); }

         })
      .listen(9001,
              [](auto *listenSocket) {
                if (listenSocket) {
                  std::cout << "Listening on port " << 9001 << std::endl;
                } else {
                  std::cout << "Failed to load certs or to bind to port"
                            << std::endl;
                }
              })
      .run();

  return 0;
}
