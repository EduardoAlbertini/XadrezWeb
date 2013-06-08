#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <libwebsockets.h>

#include "xadrez_logica.c"

static int callback_http(struct libwebsocket_context *this,
                         struct libwebsocket *wsi,
                         enum libwebsocket_callback_reasons reason, void *user,
                         void *in, size_t len)
{
    return 0;
}

static int callback_dumb_increment(struct libwebsocket_context * this,
                                   struct libwebsocket *wsi,
                                   enum libwebsocket_callback_reasons reason,
                                   void *user, void *in, size_t len)
{
    int n, m;
	unsigned char buf[LWS_SEND_BUFFER_PRE_PADDING + 1024 + LWS_SEND_BUFFER_POST_PADDING];
	unsigned char *p = &buf[LWS_SEND_BUFFER_PRE_PADDING];
    
    switch (reason) {
        case LWS_CALLBACK_ESTABLISHED:
            printf(";)\n");
            break;
            
        case LWS_CALLBACK_RECEIVE:
            printf("%s", (const char *)in);
            //char *str = (char *) in;
            char *str;
            
            str = (char *) malloc(5*sizeof(char));
            
            sprintf(str, "%s", (const char *)in);
            
            if(vm( (int)str[0]-48, (int)str[1]-48, (int)str[2]-48, (int)str[3]-48))
                n = sprintf((char *)p, "%s%s", "V", str);
            else
                n = sprintf((char *)p, "%s%s", "F", str);

            m = libwebsocket_write(wsi, p, n, LWS_WRITE_TEXT);
            break;
        default:
            break;
    }
   
   
    return 0;
}

static struct libwebsocket_protocols protocols[] = {
    /* first protocol must always be HTTP handler */
    {
        "http-only",   // name
        callback_http, // callback
        0              // per_session_data_size
    },
    {
        "dumb-increment-protocol", // protocol name - very important!
        callback_dumb_increment,   // callback
        0                          // we don't use any per session data

    }
};

int main(int argc, char *argv[]) 
{
    inicia_tabuleiro();
    
    struct libwebsocket_context *context;
    struct lws_context_creation_info info;
    const char *iface = NULL;
   
   info.port = 7681;
   info.ssl_cert_filepath = NULL;
   info.ssl_private_key_filepath = NULL;
   info.iface = iface;
   info.protocols = protocols;
   info.extensions = libwebsocket_get_internal_extensions();
   
    // create libwebsocket context representing this server
    context = libwebsocket_create_context(&info);
   
    if (context == NULL) {
        fprintf(stderr, "libwebsocket init failed\n");
        return -1;
    }
   
    printf("starting server...\n");
   
    // infinite loop, to end this server send SIGTERM. (CTRL+C)
    while (1) {
        libwebsocket_service(context, 50);
        // libwebsocket_service will process all waiting events with their
        // callback functions and then wait 50 ms.
        // (this is a single threaded webserver and this will keep our server
        // from generating load while there are not requests to process)
    }
   
    libwebsocket_context_destroy(context);
   
    return 0;
}