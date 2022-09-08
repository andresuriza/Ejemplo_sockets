#include <iostream>
#include <boost/asio.hpp> // Incluir libreria de Boost Asio

using namespace std;

/**
 *
 * Funcion que lee mensaje enviado por cliente
 *
 * @param socket
 * @return
 */
string ReadMessage(boost::asio::ip::tcp::socket & socket) {
    boost::asio::streambuf buf; // Buffer de entrada de mensajes
    boost::asio::read_until( socket, buf, "\n" ); //  Indica que lea mensaje del socket desde el buffer hasta el delimitador \n
    string data = boost::asio::buffer_cast<const char*>(buf.data()); // Hace cast del buffer de entrada a un char pointer (caracteres legibles)
    return data; // Retorna el mensaje recibido
}

/**
 *
 * Funcion que envia mensaje al cliente
 *
 * @param socket
 * @param message
 */
void SendMessage(boost::asio::ip::tcp::socket & socket, const string& message) {
    const string msg = message + "\n"; // Declara variable string con un delimitador linea siguiente
    boost::asio::write( socket, boost::asio::buffer(message)); // Envia mensaje a cliente mediante buffer
}

int main() {
    boost::asio::io_service io_service; // Servicio de input/output
    boost::asio::ip::tcp::acceptor acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 1234));
                                            // Acepta de manera asincrona conexiones en puerto 1234
    boost::asio::ip::tcp::socket socket_(io_service); // Declaracion de socket para conexiones

    cout << "Servidor iniciado" << endl;

    acceptor_.accept(socket_); // Acepta al socket del cliente que pida conectarse

    cout << "Cliente conectado" << endl;

    string message = ReadMessage(socket_); // Lee y declara mensaje del cliente
    cout << "Cliente dice: " + message << endl;

    SendMessage(socket_, "Hola, soy el servidor"); // Envia mensaje al cliente
    cout << "Mensaje enviado" << endl;
    return 0;
}