//#include <gtk/gtk.h>
#include <nappgui.h>
#include <osapp/osmain.h>
#include <stdio.h>
#include <string.h>
#include "napp.h"

/* global variable to store *app */
extern App *g_app;

static Window *i_create_flywin(void)
{
        uint32_t nrows = 4;
        Layout *layout = layout_create(2, nrows);
        Panel *panel = panel_create();
        Window *window = window_create(ekWINDOW_EDGE | ekWINDOW_TITLE | ekWINDOW_CLOSE);
        uint32_t i;

	#ifdef TEST
	GdkWindow *gdk_window;
	GdkWindowAttr gdkWinAttr;

	gdkWinAttr.title = (gchar*)"Flyout control";
	gdkWinAttr.width = (gint)100;
	gdkWinAttr.height = (gint)100;
	gdkWinAttr.visual = gdk_visual_get_best();
	gdkWinAttr.window_type = GDK_WINDOW_CHILD;
	gdk_window = gdk_window_new(NULL, &gdkWinAttr, GDK_WA_TITLE);
	gdk_window_set_functions(gdk_window, GDK_FUNC_RESIZE | GDK_FUNC_MOVE | GDK_FUNC_CLOSE);
	gdk_window_show(gdk_window);
	#endif

	// disable the minimize button; it will still be visible
        for (i=0; i< nrows; i++)
        {
                char_t text[64];
                Label *label = label_create();
                Slider *slider = slider_create();
                bstd_sprintf(text, sizeof(text), "Flyout control %d", i);
                label_text(label, text);
                layout_label(layout, label, 0, i);
                layout_slider(layout, slider,1, i);

                if (i < nrows -1)
                        layout_vmargin(layout, i, 5);

        }

        layout_hmargin(layout, 0,5);
        layout_margin(layout, 10);
        /*layout_skcolor(layout, kCOLOR_BLACK); */
        panel_layout(panel, layout);
        window_panel(window, panel);
        return window;
}

static FlyOut *i_flyout(Window *window)
{
        FlyOut *flyout = heap_new(FlyOut);
        flyout->parent = window;
        flyout->flywin = i_create_flywin();     /* returns a handle to a newly created windows */
        flyout->menu = NULL;
        flyout->align = 0;
        return flyout;

}

static void ev_hide_flyout_ViewInterconnectivity(App *app, Event *e)
{
    textview_printf(app->text, "Flyout View->Interconnectivity Hide event click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    window_hide(app->View_Interconnectivity->flywin);
    app->View_Interconnectivity_IsShown = 0;

    /* !!!!!  somehow this cause the view menu to disappear !!!! */
    /*
    menuitem_state(app->view_interconnectivity,ekGUI_OFF);
    */
    unref(e);
}

static void ev_hide_flyout_ViewProject(App *app, Event *e)
{
    textview_printf(app->text, "Flyout View->Project Hide event click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    window_hide(app->View_Project->flywin);
    app->View_Project_IsShown = 0;

    /* !!!!!  somehow this cause the view menu to disappear !!!! */
    /*
    menuitem_state(app->view_project,ekGUI_OFF);
    */
    unref(e);
}

static void ev_hide_flyout_ViewAttributes(App *app, Event *e)
{
    textview_printf(app->text, "Flyout View->Attributes Hide event click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    window_hide(app->View_Attributes->flywin);
    app->View_Attributes_IsShown = 0;

    /* !!!!!  somehow this cause the view menu to disappear !!!! */
    /*
    menuitem_state(app->view_attributes,ekGUI_OFF);
    */
    unref(e);
}

static void ev_hide_flyout_ViewReferences(App *app, Event *e)
{
    textview_printf(app->text, "Flyout View->References Hide event click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    window_hide(app->View_References->flywin);
    app->View_References_IsShown = 0;

    /* !!!!!  somehow this cause the view menu to disappear !!!! */
    /*
    menuitem_state(app->view_references,ekGUI_OFF);
    */
    unref(e);
}

static void ev_hide_flyout_ViewAddressSpace(App *app, Event *e)
{
    textview_printf(app->text, "Flyout View->Address Space Hide event click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    window_hide(app->View_AddressSpace->flywin);
    app->View_AddressSpace_IsShown = 0;

    /* !!!!!  somehow this cause the view menu to disappear !!!! */
    /*
    menuitem_state(app->view_addressspace,ekGUI_OFF);
    */
    unref(e);
}


static void ev_hide_flyout_ViewmaxAdapter(App *app, Event *e)
{
    textview_printf(app->text, "Flyout View->maxAdapter Hide event click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    window_hide(app->View_maxAdapter->flywin);
    app->View_maxAdapter_IsShown = 0;

    /* !!!!!  somehow this cause the view menu to disappear !!!! */
    /*
    menuitem_state(app->view_maxAdapter,ekGUI_OFF);
    */
    unref(e);
}


static void ev_hide_flyout_ViewmaxGate(App *app, Event *e)
{
    textview_printf(app->text, "Flyout View->maxGate Hide event click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    window_hide(app->View_maxGate->flywin);
    app->View_maxGate_IsShown = 0;

    /* !!!!!  somehow this cause the view menu to disappear !!!! */
    /*
    menuitem_state(app->view_maxGate,ekGUI_OFF);
    */
    unref(e);
}

static void ev_hide_flyout_ViewmaxIntegrator(App *app, Event *e)
{
    textview_printf(app->text, "Flyout View->maxIntegrator Hide event click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    window_hide(app->View_maxIntegrator->flywin);
    app->View_maxIntegrator_IsShown = 0;

    /* !!!!!  somehow this cause the view menu to disappear !!!! */
    /*
    menuitem_state(app->view_maxIntegrator,ekGUI_OFF);
    */
    unref(e);
}

static void ev_hide_flyout_ViewLog(App *app, Event *e)
{
    textview_printf(app->text, "Flyout View->Log Hide event click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    window_hide(app->View_Log->flywin);
    app->View_Log_IsShown = 0;

    /* !!!!!  somehow this cause the view menu to disappear !!!! */
    /*
    menuitem_state(app->view_log,ekGUI_OFF);
    */
    unref(e);
}

static void ev_OnMove_flyout_ViewInterconnectivity(App *app, Event *e)
{
    textview_printf(app->text, "Flyout View->interconnectivity Move event \n", app->clicks);
    unref(e);
}

static void ev_OnMove_flyout_ViewProject(App *app, Event *e)
{
    V2Df mycoordinate;
    S2Df mysize;
    float x_offset, y_offset;

    #ifdef DEBUG
    textview_printf(app->text, "Flyout View->Project Move event detected \n");
    textview_scroll_caret(app->text);
    #endif

#ifdef TEST
    /* get the screen coordinate of itself */
    //mycoordinate.x = window_get_origin(app->View_Project->flywin).x;
    //mycoordinate.y = window_get_origin(app->View_Project->flywin).y;
    mysize.width = window_get_size(app->View_Project->flywin).width;
    mysize.height = window_get_size(app->View_Project->flywin).height;

    //textview_printf(app->text, "app->resolution %f %f \n", app->sys_resolution.x, app->sys_resolution.y);
    //textview_printf(app->text, "imaginaryLeftWindow %f %f \n", window_get_origin(app->imaginaryLeftWindow).x, window_get_origin(app->imaginaryLeftWindow).y);
#endif

    /* now check if there ia overlapping of the app->window */
    /* compare the flywin left coordinate against the screen coordinate*/
    /* if it move beyond 25%-50% of iteself, then it is considered breached */

    /* original - if (mycoordinate.x < app->screen_coordinate.x) */
    if (mycoordinate.x + mysize.width * 0.50 > app->screen_coordinate.x) {
        /* ok */
        if ( (mycoordinate.x + mysize.width * 0.25) < app->screen_coordinate.x) {
                textview_printf(app->text,
                        "Flyout View->Project Move event Left border (X) breach detected : mycoordinate.x (%f) mysize.width*0.25 (%f) app->screen_coordinate.x (%f) \n",
                        mycoordinate.x,  mysize.width * 0.25, app->screen_coordinate.x);
                textview_scroll_caret(app->text);
                /* show an imaginary panel */
                window_show(app->imaginaryLeftWindow);
        }
        else {
                window_hide(app->imaginaryLeftWindow);
        }
    }
    else {
        window_hide(app->imaginaryLeftWindow);
    }

    if (mycoordinate.y + mysize.height *0.50 > app->screen_coordinate.y) {
        /* ok */
        if (mycoordinate.y + mysize.height * 0.25 < app->screen_coordinate.y) {
                textview_printf(app->text, "Flyout View->Project Move event detected : Top border (Y) breached \n");
                textview_scroll_caret(app->text);
                /* show an imaginary panel */
                window_show(app->imaginaryTopWindow);
        }
        else {
                window_hide(app->imaginaryTopWindow);
        }
    }
    else {
        window_hide(app->imaginaryTopWindow);
    }
    /* original - if (mycoordinate.x + mysize.width * 0.50 > app->screen_coordinate.x + app->sys_resolution.x) */
    /* compare the flywin right coordinate (flywin.x + width) against the screen right coordinate */
    x_offset = app->screen_coordinate.x + app->sys_resolution.x - mysize.width;
    if (mycoordinate.x  > x_offset + mysize.width * 0.25) {
         /* ok */
        /* original - if (mycoordinate.x + mysize.width * 0.25 > app->screen_coordinate.x + app->sys_resolution.x) */
        if (mycoordinate.x < x_offset + mysize.width * 0.5) {
                textview_printf(app->text, "Flyout View->Project Move event detected : Right border (X) breached \n");
                textview_scroll_caret(app->text);
                /* show an imaginary panel */
                window_show(app->imaginaryRightWindow);
        }
        else {
                window_hide(app->imaginaryRightWindow);
        }
    }
    else {
        window_hide(app->imaginaryRightWindow);
    }

    y_offset = app->screen_coordinate.y + app->sys_resolution.y;
    textview_printf(app->text, "Here : y_offset %f, mycoordinate.y %f, mysize.height %f \n", y_offset, mycoordinate.y, mysize.height);
    textview_scroll_caret(app->text);
    /*there is a 212 difference between app->window and view->project due to the height of the flyout window (view->project) */
    /* must take this in account when computing the maths */
    /* y_offset (Y) = mycoordinate.y (C) + mysize.height (H)
     * Y = C + H is when both windows Y position are the same */
    /*
    C = Y-1.25H
    C = Y-1.50H
    */
    if ( mycoordinate.y > (y_offset - 1.25*mysize.height) )
    {
        textview_printf(app->text, "Flyout View->Project Move event detected : Bottom border (Y) breached \n");
        textview_scroll_caret(app->text);
    }

    unref(e);
}

static void i_destroy_flyout(FlyOut **flyout)
{
        cassert_no_null(flyout);
        cassert_no_null(*flyout);
        window_destroy(&(*flyout)->flywin);
        if ((*flyout)->menu != NULL)
                menu_destroy(&(*flyout)->menu);
        heap_delete(flyout, FlyOut);
}

static void i_OnAlign(FlyOut *flyout, Event *e)
{
        const EvButton *p = event_params(e, EvButton);
        cassert_no_null(flyout);
        flyout->align = p->index;
}

static Layout *i_align_layout(FlyOut *flyout)
{

        Layout *layout = layout_create(4,1);
        Button *button1 = button_radio();
        button_OnClick(button1, listener(flyout, i_OnAlign, FlyOut));
        return layout;
}

static Layout *i_layout(FlyOut *flyout)
{
        Layout *layout1 = layout_create(1,5);
        Layout *layout2 = i_align_layout(flyout);
        layout_layout(layout1, layout2, 0, 1);
        return layout1;

}

#ifdef in_nappmain_c
void ws_ev_handler(struct mg_connection *c, int ev, void *ev_data)
{
        if (ev == MG_EV_OPEN)
        {
                mg_ws_send(c, "hello", 5, WEBSOCKET_OP_TEXT);
        }
        else if (ev == MG_EV_WS_MSG)
        {
                struct mg_ws_message *wm = (struct mg_ws_message *) ev_data;
                textview_printf(g_app->text, "%s \n", wm->data.buf);
        }

}
#endif

#ifdef NOT_USED
void i_OnIdle_Interconnectivity_state(App *app, Event *e)
{

	struct mg_mgr *mgr = &app->ws_mgr;
	if (mgr != NULL)
	{
        	mg_mgr_poll(&app->ws_mgr, 0);    /* non-blocking poll */
		// update the textview with the message from websocket
		textview_printf(g_app->text, "nappview.c : message from websocket \n");
	}

	textview_printf(app->text, "nappview.c : Entering i_OnIdle_Interconnectivity_state() : %d \n", app->View_Interconnectivity_IsShown);
/*
	menuitem_state(app->view_interconnectivity, app->View_Interconnectivity_IsShown ? ekGUI_ON : ekGUI_OFF);
*/
	unref(e);
}
#endif

void ViewInterconnectivity(App *app, Window *parent_window)
{
    FlyOut *flyout;
    Layout *layout;
    Panel *panel;

        ferror_t error= ekFOK;
	ImageView *imgView;
	ImageView *InterconnectivityImageView;
	Image *InterconnectivityImage;

	textview_printf(app->text, "nappview.c : Entering ViewInterconnectivity() \n");
	InterconnectivityImageView = imageview_create();
	InterconnectivityImage = image_from_file("/home/pi/nappgui_src/jacky/img/interconnectivity.jpg", &error);
	if (InterconnectivityImage!=NULL && error==ekFOK) {
		textview_printf(app->text, "nappview.c : Here \n");
		/* hide */
                layout_show_col(app->canvasLayout, 0, FALSE);
                layout_show_row(app->canvasLayout, 0, FALSE);
		/* update the image */
		imageview_image(InterconnectivityImageView, InterconnectivityImage);
		imgView = layout_get_imageview(app->canvasLayout, 0,0); // get the handle to the imageView in the layout
		imageview_image(imgView, InterconnectivityImage); // update the imgView with the new imageView
		layout_imageview(app->canvasLayout, imgView, 0,0); // assign the new imageView back to the layout
		/* show */
		layout_show_col(app->canvasLayout, 0, TRUE);
                layout_show_row(app->canvasLayout, 0, TRUE);
	}
	else
        {
		textview_printf(app->text, "nappview.c : Error loading /home/pi/nappgui_src/jacky/img/interconnectivity.jpg\n");
        }

    if (app->View_Interconnectivity == NULL)
    {
        /* create the View->Interconnectivity flyout window */
        flyout = i_flyout(app->window); //(parent_window);

        window_title(flyout->flywin, "Interconnectivity");
        app->View_Interconnectivity = flyout; /* save the handle of the View->Reference flyout window in the main App */

        /* show the View->Interconnectivity flyout window */

	//window_hide(app->View_Interconnectivity->flywin); /* hide it first*/
        //window_overlay(flyout->flywin, app->window);
        window_show(app->View_Interconnectivity->flywin);

        app->View_Interconnectivity_IsShown = 1; /* set the flag to true */
	/* !!!!!  somehow this cause the menu to disappear !!!! */
/*
        menuitem_state(app->view_interconnectivity, ekGUI_ON);
*/
	window_OnMoved(flyout->flywin, listener(app, ev_OnMove_flyout_ViewInterconnectivity, App));
	window_OnClose(flyout->flywin, listener(app, ev_hide_flyout_ViewInterconnectivity, App));
    }
    else
    {
        /* the View->Interconnectivity flyout window already existed, check what is the current state ? */
        textview_printf(app->text, "View->Interconnectivity flyout window already exist");
        if (app->View_Interconnectivity_IsShown == 0) /* it is currently hidden */
        {
		textview_printf(app->text, "View_Interconnectivity_IsShown == 0, showing it now");
                app->View_Interconnectivity_IsShown = 1;      /* set the flag to true */

		//window_hide(app->View_Interconnectivity->flywin); /* hide it first*/
                //window_overlay(app->View_Interconnectivity->flywin, app->window);     /* now show it */
                window_show(app->View_Interconnectivity->flywin);     /* show it */

                // defer until the callback is completed
		// menuitem_state(app->view_interconnectivity, ekGUI_ON);
        }
        else    /* it is currently shown */
        {
		textview_printf(app->text, "View_Interconnectivity_IsShown == 1, hiding it now");
                app->View_Interconnectivity_IsShown = 0;       /* set the flag to false */
                window_hide(app->View_Interconnectivity->flywin); /* hide it */
                /* !!!!!  somehow this cause the menu to disappear !!!! */
		// defer until the callback is completed
                // menuitem_state(app->view_interconnectivity, ekGUI_OFF); => this caused the menu to disappear

        }
    }


        textview_printf(app->text, "menuitem_state(view->Interconnectivity is %d \n", menuitem_get_state(app->view_interconnectivity)); /* 0=ekGUI_OFF, 1=ekGUI_ON, 2= ekGUI_MIXED */
        textview_scroll_caret(app->text);

        layout = i_layout(flyout);
        panel = panel_create();
        panel_data(panel, &flyout, i_destroy_flyout, FlyOut);
        panel_layout(panel, layout);
	#ifdef NOT_USED
	gui_OnIdle(listener(app, i_OnIdle_Interconnectivity_state, App));
	#endif
}

void ViewProject(App *app, Window *parent_window)
{
    FlyOut *flyout;
    Layout *layout;
    Panel *panel;

    if (app->View_Project == NULL)   /* the View->Project flyout window is not yet created */
    {
        /* create the View->Project flyout window */
        flyout = i_flyout(parent_window);

        window_title(flyout->flywin, "Project");
        app->View_Project = flyout; /* save the handle of the View->Project flyout window in the main App */

 /*       window_overlay(flyout->flywin, flyout->parent); */
        window_show(flyout->flywin); /* show the View->Project flyout window */
        app->View_Project_IsShown = 1; /* set the flag to true */

        /* !!!!!  somehow this cause the view menu to disappear !!!! */
        /*
	menuitem_state(app->view_project, ekGUI_ON);
	*/

	window_OnMoved(flyout->flywin, listener(app, ev_OnMove_flyout_ViewProject, App));
        window_OnClose(flyout->flywin, listener(app, ev_hide_flyout_ViewProject, App));
    }
    else
    {
        /* the View->Project flyout window already existed, check what is the current state ? */
	textview_printf(app->text, "View->Project flyout window already exist");
        if (app->View_Project_IsShown == 0) /* it is currently hidden */
        {
		textview_printf(app->text, "View_Project_IsShown == 0, showing it now");
                window_show(app->View_Project->flywin);     /* show it */
                app->View_Project_IsShown = 1;      /* set the flag to true */
		menuitem_state(app->view_project, ekGUI_ON);
        }
        else    /* it is currently shown */
        {
		textview_printf(app->text, "View_Project_IsShown == 1, hiding it now");
                window_hide(app->View_Project->flywin); /* hide it */
                app->View_Project_IsShown = 0;       /* set the flag to false */

                /* !!!!!  somehow this cause the view menu to disappear !!!! */
		/*
	 	menuitem_state(app->view_project, ekGUI_OFF);
		*/
        }
    }

        textview_printf(app->text, "menuitem_state(view->Project is %d \n", menuitem_get_state(app->view_project)); /* 0=ekGUI_OFF, 1=ekGUI_ON, 2= ekGUI_MIXED */
        textview_scroll_caret(app->text);

        layout = i_layout(flyout);
        panel = panel_create();
        panel_data(panel, &flyout, i_destroy_flyout, FlyOut);
        panel_layout(panel, layout);
}

void ViewAttributes(App *app, Window *parent_window)
{

    FlyOut *flyout;
    Layout *layout;
    Panel *panel;

    if (app->View_Attributes == NULL)   /* the View->Attributes flyout window is not yet created */
    {
        /* create the View->Attributes flyout window */
        flyout = i_flyout(parent_window);

        window_title(flyout->flywin, "Attributes");
        app->View_Attributes = flyout; /* save the handle of the View->Attributes flyout window in the main App */

  /*      window_overlay(flyout->flywin, flyout->parent); */
        window_show(flyout->flywin); /* show the View->Reference flyout window */
        app->View_Attributes_IsShown = 1; /* set the flag to true */
/* !!!!!  somehow this cause the menu to disappear !!!! */
/*
        menuitem_state(app->view_attributes, ekGUI_ON);
*/
        window_OnClose(flyout->flywin, listener(app, ev_hide_flyout_ViewAttributes, App));
    }
    else
    {
        /* the View->Attributes flyout window already existed, check what is the current state ? */
        textview_printf(app->text, "View->Attributes flyout window already exist");
        if (app->View_Attributes_IsShown == 0) /* it is currently hidden */
        {
		textview_printf(app->text, "View_Attributes_IsShown == 0, showing it now");
                window_show(app->View_Attributes->flywin);     /* show it */
                app->View_Attributes_IsShown = 1;      /* set the flag to true */
		menuitem_state(app->view_attributes, ekGUI_ON);
        }
        else    /* it is currently shown */
        {
		textview_printf(app->text, "View_Attributes_IsShown == 1, hiding it now");
                window_hide(app->View_Attributes->flywin); /* hide it */
                app->View_Attributes_IsShown = 0;       /* set the flag to false */
		/* !!!!!  somehow this cause the menu to disappear !!!! */
/*
		menuitem_state(app->view_attributes, ekGUI_OFF);
*/
        }
    }

        textview_printf(app->text, "menuitem_state(view->Attributes is %d \n", menuitem_get_state(app->view_attributes)); /* 0=ekGUI_OFF, 1=ekGUI_ON, 2= ekGUI_MIXED */
        textview_scroll_caret(app->text);

        layout = i_layout(flyout);
        panel = panel_create();
        panel_data(panel, &flyout, i_destroy_flyout, FlyOut);
        panel_layout(panel, layout);
}

void ViewReferences(App *app, Window *parent_window)
{
    FlyOut *flyout;
    Layout *layout;
    Panel *panel;

    if (app->View_References == NULL)	/* the View->Reference flyout window is not yet created */
    {
	/* create the View->Reference flyout window */
	flyout = i_flyout(parent_window);

        window_title(flyout->flywin, "References");
        app->View_References = flyout; /* save the handle of the View->Reference flyout window in the main App */

  /*      window_overlay(flyout->flywin, flyout->parent); */
	window_show(flyout->flywin); /* show the View->Reference flyout window */
        app->View_References_IsShown = 1; /* set the flag to true */
/* !!!!!  somehow this cause the menu to disappear !!!! */
/*
      menuitem_state(app->view_references, ekGUI_ON);
*/
	window_OnClose(flyout->flywin, listener(app, ev_hide_flyout_ViewReferences, App));
    }
    else
    {
	/* the View->Reference flyout window already existed, check what is the current state ? */
	textview_printf(app->text, "View->Reference flyout window already exist");
	if (app->View_References_IsShown == 0) /* it is currently hidden */
	{
		textview_printf(app->text, "View_References_IsShown == 0, showing it now");
		window_show(app->View_References->flywin);     /* show it */
        	app->View_References_IsShown = 1;      /* set the flag to true */
                menuitem_state(app->view_references, ekGUI_ON);
	}
	else	/* it is currently shown */
	{
		textview_printf(app->text, "View_References_IsShown == 1, hiding it now");
		window_hide(app->View_References->flywin); /* hide it */
		app->View_References_IsShown = 0;	/* set the flag to false */
		/* !!!!!  somehow this cause the menu to disappear !!!! */
/*
                menuitem_state(app->view_references, ekGUI_OFF);
*/
	}
    }

   	textview_printf(app->text, "menuitem_state(view->References is %d \n", menuitem_get_state(app->view_references)); /* 0=ekGUI_OFF, 1=ekGUI_ON, 2= ekGUI_MIXED */
        textview_scroll_caret(app->text);

	layout = i_layout(flyout);
	panel = panel_create();
	panel_data(panel, &flyout, i_destroy_flyout, FlyOut);
	panel_layout(panel, layout);

}

void ViewAddressSpace(App *app, Window *parent_window)
{

    FlyOut *flyout;
    Layout *layout;
    Panel *panel;

    if (app->View_AddressSpace == NULL)   /* the View->AddressSpace flyout window is not yet created */
    {
        /* create the View->AddressSpace flyout window */
        flyout = i_flyout(parent_window);

        window_title(flyout->flywin, "Address Space");
        app->View_AddressSpace = flyout; /* save the handle of the View->AddressSpace flyout window in the main App */

  /*      window_overlay(flyout->flywin, flyout->parent); */
        window_show(flyout->flywin); /* show the View->AddressSpace flyout window */
        app->View_AddressSpace_IsShown = 1; /* set the flag to true */
        /* !!!!!  somehow this cause the view menu to disappear !!!! */
        /*
	menuitem_state(app->view_addressspace, ekGUI_ON);
	*/
        window_OnClose(flyout->flywin, listener(app, ev_hide_flyout_ViewAddressSpace, App));
    }
    else
    {
        /* the View->AddressSpace flyout window already existed, check what is the current state ? */
	textview_printf(app->text, "View->Address Space flyout window already exist");
        if (app->View_AddressSpace_IsShown == 0) /* it is currently hidden */
        {
		textview_printf(app->text, "View_AddressSpace_IsShown == 0, showing it now");
                window_show(app->View_AddressSpace->flywin);     /* show it */
                app->View_AddressSpace_IsShown = 1;      /* set the flag to true */
		menuitem_state(app->view_addressspace, ekGUI_ON);
        }
        else    /* it is currently shown */
        {
		textview_printf(app->text, "View_Attributes_IsShown == 1, hiding it now");
                window_hide(app->View_AddressSpace->flywin); /* hide it */
                app->View_AddressSpace_IsShown = 0;       /* set the flag to false */

		/* !!!!!  somehow this cause the menu to disappear !!!! */
		/*
		menuitem_state(app->view_addressspace, ekGUI_OFF);
		*/
        }
    }

        textview_printf(app->text, "menuitem_state(view->Address Space is %d \n", menuitem_get_state(app->view_addressspace)); /* 0=ekGUI_OFF, 1=ekGUI_ON, 2= ekGUI_MIXED */
        textview_scroll_caret(app->text);

        layout = i_layout(flyout);
        panel = panel_create();
        panel_data(panel, &flyout, i_destroy_flyout, FlyOut);
        panel_layout(panel, layout);
}

void ViewmaxAdapter(App *app, Window *parent_window)
{
    FlyOut *flyout;
    Layout *layout;
    Panel *panel;

    if (app->View_maxAdapter == NULL)   /* the View->AddressSpace flyout window is not yet created */
    {
        /* create the View->maxAdapter flyout window */
        flyout = i_flyout(parent_window);

        window_title(flyout->flywin, "maxAdapter");
        app->View_maxAdapter = flyout; /* save the handle of the View->maxAdapter flyout window in the main App */

  /*      window_overlay(flyout->flywin, flyout->parent); */
        window_show(flyout->flywin); /* show the View->AddressSpace flyout window */
        app->View_maxAdapter_IsShown = 1; /* set the flag to true */
        /* !!!!!  somehow this cause the view menu to disappear !!!! */
        /*
        menuitem_state(app->view_maxadapter, ekGUI_ON);
        */
        window_OnClose(flyout->flywin, listener(app, ev_hide_flyout_ViewmaxAdapter, App));
    }
    else
    {
        /* the View->AddressSpace flyout window already existed, check what is the current state ? */
	textview_printf(app->text, "View->Adapter flyout window already exist");
        if (app->View_maxAdapter_IsShown == 0) /* it is currently hidden */
        {
		textview_printf(app->text, "View_maxAdapter_IsShown == 0, showing it now");
                window_show(app->View_maxAdapter->flywin);     /* show it */
                app->View_maxAdapter_IsShown = 1;      /* set the flag to true */
                menuitem_state(app->view_maxAdapter, ekGUI_ON);
        }
        else    /* it is currently shown */
        {
		textview_printf(app->text, "View_maxAdapter_IsShown == 1, hiding it now");
                window_hide(app->View_maxAdapter->flywin); /* hide it */
                app->View_maxAdapter_IsShown = 0;       /* set the flag to false */

                /* !!!!!  somehow this cause the menu to disappear !!!! */
                /*
                menuitem_state(app->view_maxadapter, ekGUI_OFF);
                */
        }
    }

        textview_printf(app->text, "menuitem_state(view->maxAdapter is %d \n", menuitem_get_state(app->view_maxAdapter)); /* 0=ekGUI_OFF, 1=ekGUI_ON, 2= ekGUI_MIXED */
        textview_scroll_caret(app->text);

        layout = i_layout(flyout);
        panel = panel_create();
        panel_data(panel, &flyout, i_destroy_flyout, FlyOut);
        panel_layout(panel, layout);

}

void ViewmaxGate(App *app, Window *parent_window)
{
    FlyOut *flyout;
    Layout *layout;
    Panel *panel;

    if (app->View_maxGate == NULL)   /* the View->AddressSpace flyout window is not yet created */
    {
        /* create the View->maxGate flyout window */
        flyout = i_flyout(parent_window);

        window_title(flyout->flywin, "maxGate");
        app->View_maxGate = flyout; /* save the handle of the View->maxGate flyout window in the main App */

  /*      window_overlay(flyout->flywin, flyout->parent); */
        window_show(flyout->flywin); /* show the View->AddressSpace flyout window */
        app->View_maxGate_IsShown = 1; /* set the flag to true */
        /* !!!!!  somehow this cause the view menu to disappear !!!! */
        /*
        menuitem_state(app->view_maxGate, ekGUI_ON);
        */
        window_OnClose(flyout->flywin, listener(app, ev_hide_flyout_ViewmaxGate, App));
    }
    else
    {
        /* the View->AddressSpace flyout window already existed, check what is the current state ? */
	textview_printf(app->text, "View->maxGate flyout window already exist");
        if (app->View_maxGate_IsShown == 0) /* it is currently hidden */
        {
		textview_printf(app->text, "View_maxGate_IsShown == 0, showing it now");
                window_show(app->View_maxGate->flywin);     /* show it */
                app->View_maxGate_IsShown = 1;      /* set the flag to true */
                menuitem_state(app->view_maxGate, ekGUI_ON);
        }
        else    /* it is currently shown */
        {
		textview_printf(app->text, "View_maxGate_IsShown == 1, hiding it now");
                window_hide(app->View_maxGate->flywin); /* hide it */
                app->View_maxGate_IsShown = 0;       /* set the flag to false */

                /* !!!!!  somehow this cause the menu to disappear !!!! */
                /*
                menuitem_state(app->view_maxGate, ekGUI_OFF);
                */
        }
    }

        textview_printf(app->text, "menuitem_state(view->maxGate is %d \n", menuitem_get_state(app->view_maxGate)); /* 0=ekGUI_OFF, 1=ekGUI_ON, 2= ekGUI_MIXED */
        textview_scroll_caret(app->text);

        layout = i_layout(flyout);
        panel = panel_create();
        panel_data(panel, &flyout, i_destroy_flyout, FlyOut);
        panel_layout(panel, layout);


}

void ViewmaxIntegrator(App *app, Window *parent_window)
{

    FlyOut *flyout;
    Layout *layout;
    Panel *panel;

    if (app->View_maxIntegrator == NULL)   /* the View->AddressSpace flyout window is not yet created */
    {
        /* create the View->maxIntegrator flyout window */
        flyout = i_flyout(parent_window);

        window_title(flyout->flywin, "maxIntegrator");
        app->View_maxIntegrator = flyout; /* save the handle of the View->maxIntegrator flyout window in the main App */

  /*      window_overlay(flyout->flywin, flyout->parent); */
        window_show(flyout->flywin); /* show the View->AddressSpace flyout window */
        app->View_maxIntegrator_IsShown = 1; /* set the flag to true */
        /* !!!!!  somehow this cause the view menu to disappear !!!! */
        /*
        menuitem_state(app->view_maxIntegrator, ekGUI_ON);
        */
        window_OnClose(flyout->flywin, listener(app, ev_hide_flyout_ViewmaxIntegrator, App));
    }
    else
    {
        /* the View->AddressSpace flyout window already existed, check what is the current state ? */
	textview_printf(app->text, "View->maxIntegrator flyout window already exist");
        if (app->View_maxIntegrator_IsShown == 0) /* it is currently hidden */
        {
		textview_printf(app->text, "View_maxIntegrator_IsShown == 0, showing it now");
                window_show(app->View_maxIntegrator->flywin);     /* show it */
                app->View_maxIntegrator_IsShown = 1;      /* set the flag to true */
                menuitem_state(app->view_maxIntegrator, ekGUI_ON);
        }
        else    /* it is currently shown */
        {
		textview_printf(app->text, "View_maxIntegrator_IsShown == 1, hiding it now");
                window_hide(app->View_maxIntegrator->flywin); /* hide it */
                app->View_maxIntegrator_IsShown = 0;       /* set the flag to false */

                /* !!!!!  somehow this cause the menu to disappear !!!! */
                /*
                menuitem_state(app->view_maxIntegrator, ekGUI_OFF);
                */
        }
    }

        textview_printf(app->text, "menuitem_state(view->maxIntegrator is %d \n", menuitem_get_state(app->view_maxIntegrator)); /* 0=ekGUI_OFF, 1=ekGUI_ON, 2= ekGUI_MIXED */
        textview_scroll_caret(app->text);

        layout = i_layout(flyout);
        panel = panel_create();
        panel_data(panel, &flyout, i_destroy_flyout, FlyOut);
        panel_layout(panel, layout);

}


void ViewLog(App *app, Window *parent_window)
{

    FlyOut *flyout;
    Layout *layout;
    Panel *panel;

    if (app->View_Log == NULL)   /* the View->Log flyout window is not yet created */
    {
        /* create the View->Log flyout window */
        flyout = i_flyout(parent_window);

        window_title(flyout->flywin, "Log");
        app->View_Log = flyout; /* save the handle of the View->Log flyout window in the main App */

/*       window_overlay(flyout->flywin, flyout->parent); */
        window_show(flyout->flywin); /* show the View->Log flyout window */
        app->View_Log_IsShown = 1; /* set the flag to true */

/* !!!!!  somehow this cause the menu to disappear !!!! */
/*
	menuitem_state(app->view_log, ekGUI_ON);
*/
        window_OnClose(flyout->flywin, listener(app, ev_hide_flyout_ViewLog, App));
    }
    else
    {
        /* the View->Log flyout window already existed, check what is the current state ? */
	textview_printf(app->text, "View->Log flyout window already exist");
        if (app->View_Log_IsShown == 0) /* it is currently hidden */
        {
		textview_printf(app->text, "View_Log_IsShown == 0, showing it now");
                window_show(app->View_Log->flywin);     /* show it */
                app->View_Log_IsShown = 1;      /* set the flag to true */
		menuitem_state(app->view_log, ekGUI_ON);
        }
        else    /* it is currently shown */
        {
		textview_printf(app->text, "View_Log_IsShown == 1, hiding it now");
                window_hide(app->View_Log->flywin); /* hide it */
                app->View_Log_IsShown = 0;       /* set the flag to false */
		/* !!!!!  somehow this cause the menu to disappear !!!! */
		/*
		menuitem_state(app->view_log, ekGUI_OFF);
		*/
        }
    }

        textview_printf(app->text, "menuitem_state(view->Log is %d \n", menuitem_get_state(app->view_log)); /* 0=ekGUI_OFF, 1=ekGUI_ON, 2= ekGUI_MIXED */
        textview_scroll_caret(app->text);

        layout = i_layout(flyout);
        panel = panel_create();
        panel_data(panel, &flyout, i_destroy_flyout, FlyOut);
        panel_layout(panel, layout);
}
