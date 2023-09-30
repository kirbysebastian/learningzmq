#include <iostream>
#include <zmq.hpp>
#include <zmq_addon.hpp>

int main(int argc, char** argv) {
	std::cout << "Whut?!" << std::endl;

    zmq::context_t ctx;

	if (argc > 1) {
		zmq::socket_t sock2(ctx, zmq::socket_type::pull);
		sock2.connect("tcp://192.168.1.10:1234");

		std::vector<zmq::message_t> recv_msgs;
		const auto ret = zmq::recv_multipart(
			sock2, std::back_inserter(recv_msgs));
		if (!ret)
			return 1;
		std::cout << "Got " << *ret
				  << " messages" << std::endl;

		for (const auto& msg : recv_msgs) {
			std::cout << msg << std::endl;
		}
		return 0;
	}

    zmq::socket_t sock1(ctx, zmq::socket_type::push);
    sock1.bind("tcp://0.0.0.0:1234");
    const std::string last_endpoint =
        sock1.get(zmq::sockopt::last_endpoint);
    std::cout << "Connecting to "
              << last_endpoint << std::endl;

    std::array<zmq::const_buffer, 2> send_msgs = {
        zmq::str_buffer("foo"),
        zmq::str_buffer("bar!")
    };
    if (!zmq::send_multipart(sock1, send_msgs))
        return 1;

    return 0;
}
