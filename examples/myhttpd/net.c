#include "mongoose.h"

void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
  if (ev == MG_EV_HTTP_MSG) {
    struct mg_http_message *hm = (struct mg_http_message *) ev_data;
    MG_INFO(("%.*s %.*s %.*s", (int) hm->method.len, hm->method.ptr,
                               (int) hm->uri.len, hm->uri.ptr,
                               (int) hm->body.len, hm->body.ptr));

    // Health check
    if (mg_http_match_uri(hm, "/api/status") &&
        mg_vcasecmp(&hm->method, "GET") == 0) {
      mg_http_reply(c, 200, NULL, "{\"status\": \"ok\"}");
      return;
    }

    // Reboot device
    if (mg_http_match_uri(hm, "/api/reboot") &&
        mg_vcasecmp(&hm->method, "GET") == 0) {
      mg_http_reply(c, 200, NULL, "");
      return;
    }

    // Get configuration
    if (mg_http_match_uri(hm, "/api/config/get") &&
        mg_vcasecmp(&hm->method, "GET") == 0) {
      mg_http_reply(c, 200, NULL, "{\"val1\": \"hi\", \"val2\": 34, \"val3\": true}");
      return;
    }

    // Set configuration
    if (mg_http_match_uri(hm, "/api/config/set") &&
        mg_vcasecmp(&hm->method, "POST") == 0) {
      mg_http_reply(c, 200, NULL, "{\"phone-number\": \"10086\"}");
      return;
    }

    struct mg_http_serve_opts opts = {.root_dir = "web_root"};
    mg_http_serve_dir(c, ev_data, &opts);
  }
}
