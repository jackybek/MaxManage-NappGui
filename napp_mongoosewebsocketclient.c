#include "mongoose.h"
#include "napp.h"

struct mg_connection *ws_mg_client;
struct mg_str s_ca, s_cert, s_key;
static const char *s_listen_on = "ws://192.168.1.109:7681/websocket";                   // "ws://localhost:8000"
static const char *s_web_root = "/var/www/svr.virtualskies.com.sg";             // "."
static const char *s_ca_path = "ca.pem";                                        // "ca.pem"
static const char *s_cert_path = "/usr/local/ssl/certs/opcCert109.pem";                         // "cert.pem"
static const char *s_key_path = "/usr/local/ssl/private/Opcprivate-key109.pem";

static void wsclient_callback(struct mg_connection *c, int ev, void *ev_data)
{
	int msgtype;
	struct mg_ws_message *wm;
	//TaskData *tData;
	//TextView *textMaxManage, *text1;
	App *app;

	//text1 = textview_create();

	//textMaxManage = (TextView *)ev_data;	// cast to App to get the GUI object tData->app->textManage
	app = (App *)ev_data;	// cast to App to get the GUI object tData->app->textManage

	//app->wsclient_callback_state = ev;

	if (ev == MG_EV_OPEN && c->is_listening)
   	{
  		printf("\x1b[32m in wsclient_callback() : MG_EV_OPEN \x1b[0m \n");
	}
	else if (ev == MG_EV_OPEN)
  	{
	    struct mg_http_message *hm = (struct mg_http_message *) ev_data;

	    #ifdef KIV
	    if (app->textMaxManage != NULL) {
		// shift i_task_mongoose_update() in nappmain.c
		//bmutex_lock(app->mutex);
		//textview_writef(app->textMaxManage, "Websocket Connection opened.. waiting for handshake .. \n");
		//textview_scroll_caret(app->textMaxManage);
		//bmutex_unlock(app->mutex);

		app->wsclient_callback_text = (byte_t *)heap_malloc(256, "app->wsclient_callback_text");
		strcpy(app->wsclient_callback_text, "Websocket Connection opened.. waiting for handshake ..");
		MG_INFO(("ev == MG_EV_OPEN : Connected to server"));
	    }
	    else
		printf("tData->app->text is null \n");
	    #endif

	}
	else if (ev == MG_EV_ACCEPT && c->is_tls)
	{
		printf("\x1b[32m in mg_client_callback() : MG_EV_ACCEPT and c->is_tls \x1b[0m \n");
    		s_ca = mg_file_read(&mg_fs_posix, s_ca_path);
    		s_cert = mg_file_read(&mg_fs_posix, s_cert_path);
    		s_key = mg_file_read(&mg_fs_posix, s_key_path);
    		struct mg_tls_opts opts = {.ca = s_ca, .cert = s_cert, .key = s_key};
    		mg_tls_init(c, &opts);
	}
	else if (ev == MG_EV_ACCEPT)
 	{
		printf("\x1b[32m in wsclient_callback() : MG_EV_ACCEPT \x1b[0m \n");

	}
	else if (ev == MG_EV_HTTP_MSG)
	{
        	printf("\x1b[32m in mg_client_callback(): MG_EV_HTTP_MSG \x1b[0m \n");

      		struct mg_http_message *hm = (struct mg_http_message *) ev_data;
      		if (mg_match(hm->uri, mg_str("/websocket"), NULL))
      		{
        		// Upgrade to websocket. From now on, connection is full-duplex
        		// Websocket connection, which will receive MG_EV_WS_MSG events.
        		printf("\x1b[32m in mg_client_callback() : MS_EV_HTTP_MSG .. calling mg_ws_upgrade \x1b[0m \n");
        		mg_ws_upgrade(c, hm, NULL);
      		}
      		else if (mg_match(hm->uri, mg_str("/rest"), NULL))
      		{
        		// Serve REST response
        		printf("\x1b[32m in mg_client_callback() : MG_EV_HTTP /rest \x1b[0m \n");
        		mg_http_reply(c, 200, "", "{\"result\": %d}\n", 123);
      		}
      		else
      		{
         		// Serve static files
         		struct mg_http_serve_opts opts = {.root_dir = s_web_root};
         		mg_http_serve_dir(c, ev_data, &opts);
      		}
	}
	else if (ev == MG_EV_WS_OPEN)
	{
		//textview_printf(app->text, "Websocket handshake completed upgrade \n");
		//textview_scroll_caret(app->text);
		//app->wsclient_callback_text = "Websocket handshake completed upgrade";
		MG_INFO(("ev == MG_EV_WS_OPEN : Connected to server"));
		// mg_send(c, "Hello\n", 6);	// send data upon successful connection
	}
	else if (ev == MG_EV_WS_MSG)
	{
		printf("ev == MG_EV_WS_MSG : Received incoming messages from ws server \n");
		/* high level protocol event */
		/* triggered when a complete websocket data message is received from a remote peer */
		wm = (struct mg_ws_message *) ev_data;
		msgtype = wm->flags & 0x0F;
		if (msgtype == WEBSOCKET_OP_BINARY)
		{
			// this is a binary data message
		        mg_ws_send(c, wm->data.buf, wm->data.len, WEBSOCKET_OP_BINARY);
        		wm->data.len =0;
        		memset(wm->data.buf, 0, sizeof(wm->data.buf));
		}
		else if (msgtype == WEBSOCKET_OP_TEXT)
		{
			//bmutex_lock(app->mutex);
			//mg_printf(ws_mg_client, wm->data.buf);
			//textview_printf(app->textMaxManage, wm->data.buf);
			//textview_scroll_caret(app->textMaxManage);
			//bmutex_unlock(app->mutex);
		        mg_ws_send(c, wm->data.buf, wm->data.len, WEBSOCKET_OP_TEXT);
        		wm->data.len =0;
        		memset(wm->data.buf, 0, sizeof(wm->data.buf));

			//app->wsclient_callback_text = wm->data.buf;
		}
	}
	else if (ev == MG_EV_CLOSE && c->is_tls)
	{
		MG_INFO(("ev == MG_EV_CLOSE : Connection close : %s", (char *) ev_data));
		//textview_printf(app->textMaxManage, "Connection closed \n");
		//textview_scroll_caret(app->textMaxManage);
		//app->ws_mg_client = NULL;
    		c = NULL;
	}
	else if (ev == MG_EV_CLOSE)
	{
		//app->wsclient_callback_text = "ev == MG_EV_CLOSE : Connection close";
		MG_INFO(("ev == MG_EV_CLOSE : Connection close : %s", (char *) ev_data));
		//textview_printf(app->textMaxManage, "Connection closed \n");
		//textview_scroll_caret(app->textMaxManage);

    		//app->ws_mg_client = NULL;
    		c = NULL;
	}
  	else if (ev == MG_EV_CONNECT)
  	{
    		MG_INFO(("SV_WebApi.c : mg_client_callback() : Connected to mongoose server!"));
    		//mg_send(c, "Hello\n", 6); // Send data upon successful connection
  	}
  	else if (ev == MG_EV_WRITE)
  	{
    		//MG_INFO(("SV_WebApi.c : mg_client_callback() : Caught a MG_EV_WRITE!"));
    		struct mg_ws_message *wm = (struct mg_ws_message *) ev_data;
    		int msgtype = wm->flags & 0x0F;
    		if (msgtype == WEBSOCKET_OP_BINARY)
    		{
      			// This is a binary data message
      			//printf("SV_WebApi.c : in MG_EV_WRITE (WEBSOCKET_OP_BINARY): data is %s, len is %ld \n", wm->data.buf, wm->data.len);
      			mg_send(app->ws_mg_client, wm->data.buf, wm->data.len);
    		}
    		else if (msgtype == WEBSOCKET_OP_TEXT)
    		{
      		// This is a text data message; send it to the websocket server
      		//printf("SV_WebApi.c : in MG_EV_WRITE (WEBSOCKET_OP_TEXT): data is %s, len is %ld \n", wm->data.buf, wm->data.len);
      		mg_send(app->ws_mg_client, wm->data.buf, wm->data.len);
    		}
  	}
	else if (ev == MG_EV_READ)
	{
		/* low level transport layer event : raw socket buffers */
		/* triggered when new data arrives from a remote peer */
		app->wsclient_callback_text = "ev == MG_EV_READ : Received response";
		MG_INFO(("ev == MG_EV_READ : Received response : %.*s", (int)c->recv.len, c->recv.buf));
	}
	else if (ev == MG_EV_ERROR)
	{
		if (app->textMaxManage != NULL) {
		//textview_printf(app->textMaxManage, "Websocket error \n");
		//textview_scroll_caret(app->textMaxManage);
		app->wsclient_callback_text = "ev == MG_EV_ERROR : Connection error";
		MG_ERROR(("ev == MG_EV_ERROR : Connection error : %s", (char *) ev_data));
		}

	}
}

void initialiseMongooseWebSocketClient(App *app)
{

	const char *c_url;
	//struct mg_mgr mg_client_mgr; // create an instance
	struct mg_connection *ws_mg_client;
	//TaskData *tData = (TaskData *)t;
	//App *app = (App *)arg;

 	printf("app->wsclient_callback_state=%d \n", app->wsclient_callback_state);
      	c_url = "ws://192.168.1.109:7681/websocket";

	//printf("inspecting the contents of tData \n");
	//printf("tData->progress = %d \n", tData->progress);
	//printf("tData->finished = %d \n", tData->finished);
	//printf("app->text = %s \n", textview_get_text(app->text));

	//app->ws_mgr = &mg_client_mgr; // assign to app object

	//bmutex_lock(app->mutex);
	mg_mgr_init(&app->ws_mgr);        // initalise event manager
	//bmutex_unlock(app->mutex);

	// mutex_lock will be called in wsclient_callback()
	ws_mg_client = mg_ws_connect(&app->ws_mgr, c_url, wsclient_callback, NULL, NULL);       // create a client connection

        if (ws_mg_client == NULL)
        {
		//bmutex_lock(app->mutex);
                textview_printf(app->textMaxEngine, "nappmain.c : %s : cannot create ws client object \n", __func__);
		printf("napp_mongoosewebsocketclient.c : %s : cannot create ws client object \n", __func__);
		//bmutex_unlock(app->mutex);
     	}
        else
	{
                //textview_printf(app->text, "nappmain.c : %s : successfully created ws client object \n", __func__);
		//bmutex_lock(app->mutex);
		app->ws_mg_client = ws_mg_client;	// save the handle for use in wsclient_callback()
		//bmutex_unlock(app->mutex);
	}

	//bmutex_lock(app->mutex);
//        textview_scroll_caret(app->textMaxEngine);
	//bmutex_unlock(app->mutex);

	//bmutex_lock(app->mutex);
        strcpy(app->serverLogs, "Test message");
	//bmutex_unlock(app->mutex);

	//bmutex_lock(app->mutex);
	while (true)
		mg_mgr_poll(&app->ws_mgr, 1000);

       	mg_mgr_free(&app->ws_mgr);
	//bmutex_unlock(app->mutex);

}
