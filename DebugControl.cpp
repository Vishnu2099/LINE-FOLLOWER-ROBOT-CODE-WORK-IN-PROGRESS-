#include "DebugControl.h"
void DebugControl::broadcastStatus(String type, String message) {
        String jsonPayload = R"({"type":")" + type + R"(","message":")" + message + R"("})";
        ws.textAll(jsonPayload);
}
void DebugControl::broadcastStatus(String count) {
        String jsonPayload = R"({"count":")"+ count + R"("})";
        ws.textAll(jsonPayload);
}
DebugControl DebugStatus{};