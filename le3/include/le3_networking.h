#pragma once

namespace le3 {
    class LE3Networking {
    public:
        static LE3Networking& instance();
        static int networkThreadPtr(void* data);

    private:
        LE3Networking() {
        }

        int networkThread(void* data);
    };
}