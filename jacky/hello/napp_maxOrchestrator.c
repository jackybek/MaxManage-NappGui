#include <nappgui.h>
#include <osapp/osmain.h>
#include <stdio.h>
#include <string.h>
#include "nappgui.h"
#include "napp.h"
#include <ogl3d/ogl3d.h>
#include <GL/gl.h>
//#include "webview.h"
#include <gtk/gtk.h>

void maxOrchestratorStart(App *app, Window *parent_window)
{


}

void maxOrchestratorStop(App *app, Window *parent_window)
{


}

static void _on_window_close(App *app, Window *window)
{
	window_destroy(&window);
	core_finish();

}

static void _on_mouse_move(App *app, Event *event)
{
	const EvMouse *params = event_params(event, EvMouse);
	// kiv - flow_editor_mouse_move(params-X, params->y);
}

static void _on_mouse_click(App *app, Event *event)
{
	const EvMouse *params = event_params(event, EvMouse);
	int button =0; // 0=left, 1=right, 2=middle

	if (params->button == ekGUI_MOUSE_RIGHT) button =1;
	if (params->button == ekGUI_MOUSE_MIDDLE) button =2;

	// check if the event type is a press or release
	bool is_down = (event_type(event) == ekGUI_EVENT_DOWN);
	// kiv - flow_editor_mouse_button(button, is_down);
	bool is_up = (event_type(event) == ekGUI_EVENT_UP);

}

static void _on_draw(App *app, Event *event)
{
	// main drawing callback via OGL3D
	const EvDraw *params = event_params(event, EvDraw);
	int w = (int)params->width;
	int h = (int)params->height;

	// secure the thread context for this layout panel
	// error : ogl3d_make_current(app->gl_context);
	ogl3d_begin_draw(app->gl_context);

	glViewport(0,0,w,h);
	glClearColor(0.06f, 0.06f, 0.07f, 1.0f);// dark background for flow editor
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Call Imnodes backend pipeline loop
	// kiv - flow_editor_render(w, h);

	// swap front and back screen buffers natively
	// error : ogl3d_swap_buffers(app->gl_context);
}

void maxOrchestratorDefineDataflow(App *app, Window *parent_window)
{
	ferror_t error= ekFOK;
#ifdef OLD
	ImageView *imgView;
        ImageView *maxOrchestratorDefineDataflowImageView;
	Image *maxOrchestratorDefineDataflowImage;
	Panel *panelA;
	View *viewA;

	textview_printf(app->text, "napp_maxOrchestrator.c : Entering maxOrchestratorDefineDataflow() \n"); 
        maxOrchestratorDefineDataflowImageView = imageview_create();
        maxOrchestratorDefineDataflowImage = image_from_file("/home/pi/nappgui_src/jacky/img/maxOrchestrator.png", &error);
	if (maxOrchestratorDefineDataflowImage!=NULL && error==ekFOK) {
		textview_printf(app->textMaxOrchestrator, "napp_maxOrchestrator.c : Define Dataflow \n");
		/* hide */
		if (!app->canvasLayout)
		{
			app->canvasLayout = layout_create(1,1);
		}

		layout_show_col(app->canvasLayout, 0, FALSE);	// hide
		layout_show_row(app->canvasLayout, 0, FALSE);	// hide
		/* update the image */
        	imageview_image(maxOrchestratorDefineDataflowImageView, maxOrchestratorDefineDataflowImage);
		imgView = layout_get_imageview(app->canvasLayout, 0,0); // get the handle to the imageView in the layout
		imageview_image(imgView, maxOrchestratorDefineDataflowImage); // update the imgView with the new imageView
        	layout_imageview(app->canvasLayout, imgView, 0,0); // assign the new imageView back to the layout
		/* show */
		layout_show_col(app->canvasLayout, 0, TRUE);	// show
		layout_show_row(app->canvasLayout, 0, TRUE);	// show
	}
	else
		textview_printf(app->text, "napp_maxOrchestrator.c : Error loading /home/pi/nappgui_src/jacky/img/maxOrchestrator.png\n");
#endif
#ifdef coredump
    // Setup required OpenGL attributes
    oglerr_t err;
    void *nView;
    View *flow_view;
	Panel *flow_panel;
	Layout *flow_layout;

    OGLProps props;
    props.api = ekOGL_3_3; // Choose version: ekOGL_1_1, ekOGL_3_3_CORE, etc.
    props.hdaccel = TRUE;
    props.color_bpp = 32;
    props.depth_bpp = 0;
    props.stencil_bpp = 0;
    props.aux_buffers = 0;
    props.transparent = FALSE;
    props.shared = NULL;

	flow_view = app->viewA; //view_create();
	// Map graphics runtime processing hook to drawing thread callbacks
	view_OnDraw(flow_view, listener(app, _on_draw, App));
	view_OnMove(flow_view, listener(app, _on_mouse_move, App));
	view_OnDown(flow_view, listener(app, _on_mouse_click, App));
	view_OnUp(flow_view, listener(app, _on_mouse_click, App));

	//view_size(flow_view, s2df(800.0f, 600.0f));
	nView = view_native(flow_view);

	// Instantiating matching backend context bindings attached over window panel dimensions
	app->gl_context = ogl3d_context(&props, nView, &err);
/*
	if (!app->gl_context)
	{
    		bstd_printf("Error: %s\n", ogl3d_err_str(err));
		exit(0);
	}
*/
	view_update(flow_view);

	//flow_layout = layout_create(1,1);
	//layout_view(app->canvasLayout, flow_view, 0,0);
	//flow_panel = panel_custom(TRUE, TRUE, TRUE);
	//panel_layout(flow_panel, app->canvasLayout);
	//window_panel(app->window, flow_panel);

	//window_client_size(app->window, s2df(800.0f, 600.0f));
	//window_show(app->window);
#endif

#define SHOW_URL
#ifndef SHOW_URL
	osapp_open_url("http://localhost:5678\0");
#else
	//Layout *layout;
	//Panel *panel;
	WebView *webview;
	//char *url = "http://local:5678";
	char *url = "https://www.google.com";

	//Window *window = window_create(ekWINDOW_EDGE | ekWINDOW_TITLE | ekWINDOW_MAX | ekWINDOW_MIN | ekWINDOW_CLOSE | ekWINDOW_RESIZE);
	//window_title(window, "MaxOrchestrator - Define workflow");
	//window_OnClose(window, listener(NULL, _on_window_close, App));

	//window_show(window);

	//panel_size(app->panelABottom, s2df(1080.0f, 450.0f));
	layout_tabstop(app->layoutABottom, 0,0, ekKEY_TAB);

	//GtkWidget *gtk_window = (GtkWidget*)window_native(window);
	//webview_t webView = webview_create(0, (void*)gtk_window);
	webview = webview_create();
	webview_navigate(webview, url);		// once ssh session is started, use localhost
	webview_size(webview, s2df(1024.0f, 768.0f));

	//panel_layout(app->panelABottom, app->layoutABottom);
	//app->layoutABottom = layout_create(1,1);
	//app->panelABottom = panel_scroll(TRUE, TRUE);
	layout_webview(app->layoutABottom, webview, 0,0);
        panel_layout(app->panelABottom, app->layoutABottom);
	panel_update(app->panelABottom);
	//window_panel(window, panel);


#endif
}
