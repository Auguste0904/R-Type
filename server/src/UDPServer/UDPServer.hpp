#ifndef UDPSERVER_HPP
#define UDPSERVER_HPP

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/optional.hpp>
#include <fstream>
#include <iostream>
#include <unordered_map>

/*
    Communication between server and clients
    ----------------------------------------

    CONNECTION client -> server
        observe:
            start a connection, the person will receive all infos of the game
        disobserve:
            stop sending game info
        connect [pseudo]:
            start a connection, for players
            pseudo: pseudo that the player wants to be identified with
        disconn [id]:
            end a connection
            id: id of the player in the game

    END client -> server
        killServer:
            kills the server no matter what is the context

    INFO server -> client
        infoLobby [time] [connected] [max] [difficulty]
            information on the current lobby
            time: time remaining before the start of the game
            connected: number of players in queue
            max: max number of players in the game
            difficulty: difficulty of the game
        startingGame [connected] [difficulty]
            connected: number of players in queue
            difficulty: difficulty of the game

    MOVE client -> server
        move id dir
            move player with id [id] to a direction
            id: id of the player requesting a move
            dir: NN, SS, WW EE, NE, NW, SW, or SE (North South West East,
   North-East, North-West, South-West, South-East)

        stop id
            stop player with id [id]
            id: id of the player requesting a stop

    Bomb client -> server
        bomb id
            Drop a bomb at player with id [id] position
            id: id of the player requesting to drop a bomb

    Victory server -> client
        win
            Send a message to the winner

    End server -> client
        end
            Send an end message to the client

    SUCCESS server -> client
        connected [pseudo] [id]
            response to a connect instruction
            id: id of the player in the game

    ERRORS server -> client
        error 1
            corrupted ID
        error 2
            server is full (already 8 clients connected)
        error 3
            server is already playing
        error 4
            bad instruction
        error 5
            pseudo is too long (16 chars max)
*/
namespace rty {
    namespace server {
        namespace network {

        using UDPEndpoint = boost::asio::ip::udp::endpoint;
        using ServerPlayer = std::vector<std::pair<boost::asio::ip::udp::endpoint, int>>;

        class UdpServer{
        public:
            UdpServer(const int port);
            ~UdpServer();

            /*
             * @brief wait for all clients to join the lobby
             *      stops when 8 players are connected or waiting
             *      time exceeded 60s. It handles connections,
             *      disconnections and also infoLobby instruction
             *
             * @return number of connected players
             */
            int waitForClients();

            /*
             * @brief saves the client in _players and communicates ID to client
             *
             * @param endpoint      endpoint of the remote client
             */
            void connectClient(const boost::asio::ip::udp::endpoint &endpoint);

            /*
             * @brief removes the user with id from the player list
             *
             * @param id        id of the client to delete
             */
            void disconnectClient(char id);

            /*
             * @brief parser and executer for all commands defined in the
             * server-client protocol
             *
             * @param endpoint      endpoint of the remote entity which sent the
             * command
             * @param cmd           the command to execute
             */
            void readCommand(const boost::asio::ip::udp::endpoint &endpoint,
                const std::string &cmd);

            /*
             * @brief send string to one client
             *
             * @param endpoint      remote endpoint of the targeted client
             * @param msg           string containing the message
             */
            void send(const boost::asio::ip::udp::endpoint &endpoint,
                const std::string &msg);
            void send(char id, const std::string &msg);

            /*
             * @brief send data to every player and observers conencted to the
             * lobby
             *
             * @param msg           message to be send to eveyone
             */
            void sendAll(const std::string &msg);

            /*
             * @brief send a message indicating the soon launch off the game,
             * and the start off the sending of game data to every player and
             * observers conencted to the lobby
             */
            void sendStartingGame();

            /*
             * @brief send the information about the actual lobby
             *        to every player and observers conencted to the lobby
             */
            void sendLobbyInfo(int t);

            /*
             * @brief reads all inputs from clients
             *
             * @return received string
             */
            std::string readAll();

            boost::optional<boost::system::error_code> recvUntilTimeout(UDPEndpoint &remoteEndpoint, boost::array<char, 2000> &recvBuf, int seconds);


            bool verifID(
                const boost::asio::ip::udp::endpoint &endpoint, const char id);

            ServerPlayer getPlayers() const noexcept;

            void start();

            std::string readPlayerInput();

        private:
            // used for socket handling
            boost::asio::io_service _ioService;
            // used for communication with clients
            boost::asio::ip::udp::socket _socket;
            // map of all the players id and endpoint
            ServerPlayer _players;

            // port used by the server
            int _port;

            int _currentID;
        };
        } //rty
    } //server
} //network

#endif // UDPSERVER_HPP
