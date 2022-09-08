#include <iostream>
#include <boost/asio.hpp>

using namespace std;
int main() {
    boost::asio::io_service io_service; // Servicio de input/output
    boost::asio::ip::tcp::socket socket(io_service); // Declaracion de socket para conexiones
    boost::system::error_code error; // Variable para codigo de error especifico de Boost
    boost::asio::streambuf receive_buffer; // Buffer para recibir mensajes
    const string outMessage = "Hola, soy el cliente\n"; // Mensaje a enviar

    socket.connect(boost::asio::ip::tcp::endpoint( boost::asio::ip::address::from_string("127.0.0.1"), 1234));
                                                                       // Conecta socket a IP local con puerto del servidor
    cout << "Conectado al servidor" << endl;

    boost::asio::write(socket, boost::asio::buffer(outMessage), error ); // Escribe mensaje al servidor

    if(!error) {
        cout << "Mensaje enviado" << endl;
    }
    else {
        cout << "error" << error.message() << endl;
    }

    boost::asio::read(socket, receive_buffer, boost::asio::transfer_all(), error); // Guarda mensaje recibido en el buffer

    if (error && error != boost::asio::error::eof) {
        cout << "error" << error.message() << endl;
    } else {
        const char* inMessage = boost::asio::buffer_cast<const char*>(receive_buffer.data()); // Interpreta mensaje recibido
        cout << "Servidor dice: " + (string) inMessage << endl; // Se hace cast a string al inMessage ya que es un const char pointer,
                                                                  // para poder concatenarlo basicamente
    }
    return 0;
}