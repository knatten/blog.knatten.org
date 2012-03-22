//A basic gloox tutorial by Anders Schau Knatten
//Read more at http://blog.knatten.org/2012/03/22/basic-gloox-tutorial/
//To compile on Linux: g++ -o bot bot.cpp -lgloox -lpthread
#include <iostream>
#include <string>
#include <gloox/client.h>
#include <gloox/message.h>
#include <gloox/messagehandler.h>
#include <gloox/connectionlistener.h>

using namespace std;
using namespace gloox;

ostream& operator<<(ostream& os, Message::MessageType type) {
    switch (type) {
        case Message::Chat:
            os << "Chat";
            break;
        case Message::Error:
            os << "Error";
            break;
        case Message::Groupchat:
            os << "Groupchat";
            break;
        case Message::Headline:
            os << "Headline";
            break;
        case Message::Normal:
            os << "Normal";
            break;
        case Message::Invalid:
            os << "Invalid";
            break;
        default:
            os << "unknown type";
            break;
    }
}

ostream& operator<<(ostream& os, const Message& stanza) {
    os << "type:'" << stanza.subtype() <<  "' from:'" << stanza.from().full() << "' body:'" << stanza.body() << "'";
    return os;
}

class ConnListener : public ConnectionListener {
public:
    ConnListener() {}
    virtual void onConnect() {
        cout << "ConnListener::onConnect()" << endl;
    }
    virtual void onDisconnect(ConnectionError e) {
        cout << "ConnListener::onDisconnect() " << e << endl;
    }
    virtual bool onTLSConnect(const CertInfo& info) {
        cout << "ConnListener::onTLSConnect()" << endl;
        return true;
    }
};

class Bot : public MessageHandler {
public:
    Bot() {
        JID jid( "bot@localhost" );
        client = new Client( jid, "botpwd" );
        connListener = new ConnListener();
        client->registerMessageHandler( this );
        client->registerConnectionListener(connListener);
        client->connect(true);
    }

    ~Bot() {
        delete client;
        delete connListener;
    }
 
    virtual void handleMessage( const Message& stanza, MessageSession* session = 0 ) {
         cout << "Received message: " << stanza << endl;
          Message msg(stanza.subtype(), stanza.from(), "Tell me more about " + stanza.body() );
          client->send( msg );
    }
 
private:
   Client* client;
   ConnListener* connListener;
};

int main() {
    Bot b;
}

