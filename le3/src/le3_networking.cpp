#include "le3_networking.h"
using namespace le3;

#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#include <cpr/cpr.h>
#include <fmt/core.h>
using fmt::print;

struct LE3Networking::_NetworkInternal {
    _NetworkInternal() {}
    SDL_mutex* m_pNetworkMutex;
};
LE3Networking::LE3Networking() : 
    m_currentTicket(0xFF),
    m_pInternal(std::make_shared<_NetworkInternal>()),
    m_delay(250) {
}

LE3Networking& LE3Networking::instance() {
    static LE3Networking* instance_ = new LE3Networking();
    return *instance_;
}
int LE3Networking::networkThreadPtr(void* data) {
    return LE3Networking::instance().networkThread(data);
}

int LE3Networking::networkThread(void* data) {
    while (true) {
        LE3NetworkRequest nr;
        {
            _lock();
            if (m_ticketsToHandle.empty()) {
                nr.ticket = -1;
            } else {
                int ticket = m_ticketsToHandle[0];
                m_ticketsToHandle.erase(m_ticketsToHandle.begin());
                nr = m_requests[ticket];
            }
            _unlock();
        }
        nr = _handleRequest(nr);
        {
            _lock();
                m_requests[nr.ticket] = nr;
            _unlock();
        }

        {  
            _lock();
                SDL_Delay(m_delay);
            _unlock();
        }
    }

    return 0;
}

LE3NetworkRequest LE3Networking::sendRequest(LE3NetworkRequestType type, const std::string url) {
    LE3NetworkRequest nr;
    nr.ticket = ++m_currentTicket;
    nr.type = type;
    nr.url = url;
    nr.isDone = false;
    
    {
        _lock();
            m_requests[nr.ticket] = nr;
            m_ticketsToHandle.push_back(nr.ticket);
        _unlock();
    }
    return nr;
}

LE3NetworkRequest LE3Networking::getRequest(int ticket) {
    LE3NetworkRequest nr;
    {
        _lock();
            nr = m_requests[ticket];
        _unlock();
    }
    return nr;
}

LE3NetworkRequest LE3Networking::_handleRequest(LE3NetworkRequest nr) {
    // We assume that mutex is NOT locked here
    if (nr.type == LE3NetworkRequestType::GET) {
        cpr::Response response = cpr::Get(cpr::Url{nr.url});
        nr.responseCode = response.status_code;
        nr.response = response.text;
        nr.isDone = true;
    }
    
    return nr;
}

void LE3Networking::setDelay(int delay) {
    {  
        _lock();
            m_delay = delay;
        _unlock();
    }
}

void LE3Networking::_lock() {
    SDL_LockMutex(m_pInternal->m_pNetworkMutex);
}
void LE3Networking::_unlock() {
    SDL_UnlockMutex(m_pInternal->m_pNetworkMutex);
}