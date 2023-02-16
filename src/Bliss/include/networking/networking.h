#ifndef NETWORKING_H
#define NETWORKING_H

#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif

#define ASIO_STANDALONE
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

#include <iostream>
#include <vector>

#include "packet.h"

#define DEFAULT_NETWORK_PORT 80//3776
#define MAX_CLIENTS 10

class Networker {
public:
    asio::error_code ec;
    asio::io_context context;
    //asio::ip::tcp::socket socket;

    enum {
        Host,
        Client
    } Type;

    struct {
        std::string address = "93.184.216.34";
        int port = DEFAULT_NETWORK_PORT;
    } connection;

    Networker() {}
    ~Networker() {}

    void BeginConnection() {
        asio::ip::tcp::endpoint endpoint(asio::ip::make_address(connection.address, ec),connection.port);
        asio::ip::tcp::socket socket(context);

        socket.connect(endpoint, ec);

        if (!ec) {
            std::cout << "connected" << std::endl;
        } else {
            std::cout << "no connecy" << std::endl;
        }

        
    }

    void SendPacket(Packet packet) {
        /*if (socket.is_open()) {
            std::string sRequest =
                "GET /index.html HTTP/1.1\r\n"
                "Host: example.com\r\n"
                "Connection: close\r\n\r\n";

            socket.write_some(asio::buffer(sRequest.data(), sRequest.size()), ec);

            size_t bytes = socket.available();
            std::cout << "Bytes Available: " << bytes << std::endl;

            if (bytes > 0) {
                std::vector<char> vBuffer(bytes);
                socket.read_some(asio::buffer(vBuffer.data(), vBuffer.size()), ec);

                for (auto c : vBuffer)
                    std::cout << c;
            }*/
        //}
    }
};

#endif