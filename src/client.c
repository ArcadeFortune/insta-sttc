#include "main.h"

struct lws *clientWsi = NULL;

static int callback(struct lws *wsi, enum lws_callback_reasons reason,
                    void *user, void *in, size_t len) {
  switch (reason) {

  // case LWS_CALLBACK_CLIENT_ESTABLISHED:
  //   printf("Connected!\n");
  //   websocketState = CONNECTED;
  //   break;
  // case LWS_CALLBACK_CLIENT_WRITEABLE: {
  //   unsigned char buffer[LWS_PRE + 4096];

  //   int len = strlen(base64ToSend);

  //   memcpy(&buffer[LWS_PRE], base64ToSend, len);

  //   lws_write(wsi, &buffer[LWS_PRE], len, LWS_WRITE_TEXT);

  //   break;
  // }

  case LWS_CALLBACK_CLIENT_APPEND_HANDSHAKE_HEADER: {
    unsigned char **p = (unsigned char **)in;
    unsigned char *end = (*p) + len;

    lws_add_http_header_by_name(
        wsi, (unsigned char *)"authorization:", (unsigned char *)OPENAI_API_KEY,
        (int)strlen(OPENAI_API_KEY), p, end);
    break;
  }

  case LWS_CALLBACK_CLIENT_RECEIVE:
    printf("Received: %.*s\n", (int)len, (char *)in);
    break;

  case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
    websocketState = UNUSABLE;
    printf("Connection failed\n");
    break;

  case LWS_CALLBACK_CLIENT_CLOSED:
    websocketState = UNUSABLE;
    printf("Connection closed.\n");
    break;

  default:
    break;
  }

  return 0;
}

struct lws_context *startWebsocketClient() {
  struct lws_context_creation_info info;

  memset(&info, 0, sizeof(info));

  static struct lws_protocols protocols[] = {{
                                          "realtime",
                                          callback,
                                          0,
                                          4096,
                                      },
                                      {NULL, NULL, 0, 0}};

  info.protocols = protocols;
  info.options = LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT;

  struct lws_context *context = lws_create_context(&info);
  return context;
}

void connectWebsocketClient(struct lws_context *context) {
  struct lws_client_connect_info ccinfo = {0};
  ccinfo.context = context;
  ccinfo.address = "api.openai.com";
  ccinfo.port = 443;
  ccinfo.ssl_connection = LCCSCF_USE_SSL;
  ccinfo.path = "/v1/realtime?model=gpt-realtime-2.1";
  ccinfo.host = "api.openai.com";
  ccinfo.origin = "api.openai.com";
  ccinfo.protocol = "realtime";
  clientWsi = lws_client_connect_via_info(&ccinfo);
}

void sendToWebsocket(char *buf) {}

int stopWebsocketClient(struct lws_context *context) {
  websocketState = UNUSABLE;
  lws_context_destroy(context);
  return 0;
}
