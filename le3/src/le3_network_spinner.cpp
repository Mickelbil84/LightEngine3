#include "le3_network_spinner.h"
using namespace le3;

LE3NetworkSpinner::LE3NetworkSpinner() {
    m_request.ticket = -1;
}

void LE3NetworkSpinner::update(float deltaTime) {
    // if (!m_send) return;
    if (m_request.ticket < 0) {
        m_request = m_send();
    }
    m_request = LE3Networking::instance().getRequest(m_request);
    if (m_request.isDone) {
        // if (m_onResponse) 
        m_onResponse(m_request);
        m_request.ticket = -1;
    }
}