#include "server.h"

Server::Server(QObject *parent) : QObject(parent)
{

}

RemoteReplica *Server::remote() const
{
    return m_remote;
}

void Server::setRemote(RemoteReplica *remote)
{
    m_remote = remote;
}
