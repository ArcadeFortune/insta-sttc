#include "main.h"

static int callback(
    struct lws *wsi,
    enum lws_callback_reasons reason,
    void *user,
    void *in,
    size_t len)
{
  switch (reason)
  {

  case LWS_CALLBACK_CLIENT_ESTABLISHED:
    printf("Connected!\n");
    // todo: send base64 data
    break;

  case LWS_CALLBACK_CLIENT_APPEND_HANDSHAKE_HEADER:
  {
    unsigned char **p = (unsigned char **)in;
    unsigned char *end = (*p) + len;

    lws_add_http_header_by_name(
        wsi,
        (unsigned char *)"authorization:",
        (unsigned char *)OPENAI_API_KEY,
        (int)strlen(OPENAI_API_KEY),
        p,
        end);
    break;
  }

  case LWS_CALLBACK_CLIENT_RECEIVE:
    printf("Received: %.*s\n",
           (int)len,
           (char *)in);
    break;

  case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
    printf("Connection failed\n");
    break;

  default:
    break;
  }

  return 0;
}

struct lws_context *startWebsocketClient()
{
  struct lws_context_creation_info info;

  memset(&info, 0, sizeof(info));

  struct lws_protocols protocols[] =
      {
          {
              "realtime",
              callback,
              0,
              4096,
          },
          {NULL,
           NULL,
           0,
           0}};

  info.protocols = protocols;
  info.options = LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT;

  struct lws_client_connect_info ccinfo = {0};

  struct lws_context * context = lws_create_context(&info);
  ccinfo.context = context;
  ccinfo.address = "api.openai.com";
  ccinfo.port = 443;
  ccinfo.ssl_connection = LCCSCF_USE_SSL;
  ccinfo.path = "/v1/realtime?model=gpt-realtime-2.1";
  ccinfo.host = "api.openai.com";
  ccinfo.origin = "api.openai.com";
  ccinfo.protocol = "realtime";
  struct lws *wsi = lws_client_connect_via_info(&ccinfo);
  return context;
}

int stopWebsocketClient(struct lws_context *context)
{
  lws_context_destroy(context);
  return 0;
}
