#pragma once

#include <map>

namespace le3 {
    enum LE3NetworkRequestType {
        GET,
        POST
    };
    struct LE3NetworkRequest {
        int ticket;
        LE3NetworkRequestType type;
        std::string url;

        bool isDone;
        int responseCode;
        std::string response;
    };

    class LE3Networking {
    public:
        static LE3Networking& instance();
        static int networkThreadPtr(void* data);

        // These methods should be called only from main thread:
        LE3NetworkRequest sendRequest(LE3NetworkRequestType type, const std::string url);
        LE3NetworkRequest getRequest(int ticket);
        LE3NetworkRequest getRequest(LE3NetworkRequest request) { return getRequest(request.ticket); }
        void setDelay(int delay);

    private:
        struct _NetworkInternal;
        std::shared_ptr<_NetworkInternal> m_pInternal;
        void _lock();
        void _unlock();

        LE3Networking();
        int networkThread(void* data);

        LE3NetworkRequest _handleRequest(LE3NetworkRequest nr);

        int m_currentTicket;
        int m_delay;
        std::map<int, LE3NetworkRequest> m_requests;
        std::vector<int> m_ticketsToHandle;
    };

    #define LE3GetNetworking LE3Networking::instance
}