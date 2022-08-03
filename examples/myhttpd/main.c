// Copyright (c) 2020 Cesanta Software Limited
// All rights reserved

#include "mongoose.h"

static const char *s_lsnaddr = "http://0.0.0.0:8080";

// Implemented in web.c
extern void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data);

int main(void) {
  struct mg_mgr mgr;
  mg_mgr_init(&mgr);                          // Init event manager
  mg_http_listen(&mgr, s_lsnaddr, fn, NULL);  // Start listener
  MG_INFO(("Listening on %s", s_lsnaddr));    // Show log message
  for (;;) mg_mgr_poll(&mgr, 50);             // Event loop
  mg_mgr_free(&mgr);
  return 0;
}
