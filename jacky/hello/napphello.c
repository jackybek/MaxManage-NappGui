/* NAppGUI Hello World */
#include <nappgui.h>
#include <osapp/osmain.h>
#include <stdio.h>
#include <string.h>
#define TRANSFER

/* function prototypes */


typedef struct _flyout_t FlyOut;
struct _flyout_t
{
   Window *parent;
   Window *flywin;
   Menu *menu;
   TextView *text;
   GuiControl *edit;
   uint32_t align;
};

typedef struct _modal_data_t ModalData;
struct _modal_data_t
{
    uint32_t type;
    Label *label;
    Window *parent;
};

typedef struct _app_t App;
struct _app_t
{
    V2Df sys_resolution;	/* equivalent to the size of the app window */
    V2Df screen_coordinate;     /* this is the current position of the app window */

    Window *window;
    Menu *top_menu;

    Layout *statusLayout, *buttonLayout, *canvasLayout;

    TextView *text;
    uint32_t clicks;

    /* at initial launch, there is no filename indicated, so nofilename = 1 */
    int nofilename;
    const char *savedFile;
    FILE *fp;

    /* used in ServerAdd() */
    const char *ServerName;

    /* handle to the active modal window */
    Window *modalWindow;

    FlyOut *View_Project;
    int View_Project_IsShown;
    FlyOut *View_AddressSpace;
    int View_AddressSpace_IsShown;
    FlyOut *View_Log;
    int View_Log_IsShown;
    FlyOut *View_Attributes;
    int View_Attributes_IsShown;
    FlyOut *View_References;
    int View_References_IsShown;

    MenuItem *view_project, *view_addressspace, *view_log, *view_attributes, *view_references, *view_filetoolbar, *view_servertoolbar, *view_documenttoolbar;

    Window *imaginaryLeftWindow, *imaginaryTopWindow, *imaginaryRightWindow, *imaginaryBottomWindow;

};


/*---------------------------------------------------------------------------*/
void moveToCentre(Window *window, App *app);
#ifdef REMOVE
{
 	V2Df origin;

        float window_x, window_y;
        /* handle to target window to align centre to app->window centre */
	window_x = window_get_size(window).width;
        window_y = window_get_size(window).height;

	/* finally, move the window to the specific desktop coordinates */
        origin.x = app->sys_resolution.x / 2 - window_x / 2 ;
	origin.y = app->sys_resolution.y / 2 - window_y / 2 ;

	window_origin(window, window_client_to_screen(window, origin));

        textview_printf(app->text, "window_x (%f) window_y (%f) \n", window_x, window_y);
        textview_printf(app->text, "sys_resolution x (%f) sys_resolution y (%f) \n", app->sys_resolution.x, app->sys_resolution.y);
        textview_printf(app->text, "origin.x (%f) origin.y (%f) \n", origin.x, origin.y);

}
#endif

/*
static void i_OnButton(App *app, Event *e)
{
    textview_printf(app->text, "Button click (%d)\n", app->clicks);
    app->clicks += 1;
    unref(e);
}
*/
#ifdef TRANSFER
/* for custom-defined dialog windows, callbacks needs to be declared first */

static void i_OnClick_ButtonCancel(App *app, Event *e)
{
    textview_printf(app->text, "Button <Cancel> click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);

    window_stop_modal(app->modalWindow, 300);	/* 300 - value to be returned */
    unref(e);
}
#endif

/*---------------------------------------------------------------------------*/
void FileOpen(App *app, Window *parent_window);
#ifdef REMOVE /* transfer to nappfile.c */
{
	const char_t *selected_file;
        const char_t *filetypeslist = {"uap"};
        const uint32_t size=1;

	selected_file = comwin_open_file(parent_window, &filetypeslist, size, NULL);
	/* keep the filename in app so that when i click Save, it will update the contents without asking for the filename */
	if (selected_file == NULL) /* user aborted the dialog */
		app->nofilename = 1;
	else
	{
		app->nofilename = 0;
		app->savedFile = selected_file;
	}
	/* for debugging purposes, show it in the text widget */
	textview_printf(app->text, "Filename is (%s), nofilename = %d \n", app->savedFile, app->nofilename);
        textview_scroll_caret(app->text);

	if (app->savedFile != NULL) /* prevents an empty filename */
	{
		app->fp = fopen(app->savedFile, "r+w");
		if (app->fp)
		{
			/* read in the contents */
			/* fread(.....); */
			app->nofilename = 0;
			fclose(app->fp);
		}
		else
		{
			/* error reading the file, show a dialog box */

		}
	}
	else
	{
		/* error in the filename, show a dialog box */
	}
}
#endif

void FileExportToXML(App *app, Window *parent_window);
#ifdef REMOVE
{
    Window *modalWindow;
    ModalData *data;

    data = heap_new(ModalData);

    textview_printf(app->text, "Filename is %s, nofilename is %d \n", app->savedFile, app->nofilename);
    textview_scroll_caret(app->text);

    /* creates a modal window */
    modalWindow = window_create(ekWINDOW_EDGE | ekWINDOW_TITLE | ekWINDOW_CLOSE);
    window_title(modalWindow, "Export to XML");

    /* ModalData *data = i_modal_data(parent_window); */
    data = heap_new(ModalData);
    data->parent = parent_window;
    data->type = UINT32_MAX;

    window_modal(modalWindow, data->parent);
    window_destroy(&modalWindow);
    /*window_show(modalWindow);*/
}
#endif

void FileExportToJSON(App *app, Window *parent_window);
#ifdef REMOVE
{
    Window *modalWindow;
    ModalData *data;

    data = heap_new(ModalData);

    textview_printf(app->text, "Filename is %s, nofilename is %d \n", app->savedFile, app->nofilename);
    textview_scroll_caret(app->text);

    /* creates a modal window */
    modalWindow = window_create(ekWINDOW_EDGE | ekWINDOW_TITLE | ekWINDOW_CLOSE);
    window_title(modalWindow, "Export to JSON");

    /* ModalData *data = i_modal_data(parent_window); */
    data = heap_new(ModalData);
    data->parent = parent_window;
    data->type = UINT32_MAX;

    window_modal(modalWindow, parent_window);
    window_show(modalWindow);

}
#endif

void FileSave(App *app, Window *parent_window);
#ifdef REMOVE
{
     	const char_t *saved_file;
	const char_t *filetypeslist[] ={"uap","xml","json"};
	const uint32_t size=3;
        char title[100];

	/* for debugging purposes, show it in the text widget */
        textview_printf(app->text, "Filename is %s, nofilename is %d \n", app->savedFile, app->nofilename);
        textview_scroll_caret(app->text);

        if (app->nofilename == 1) /* this means that this is the first time, then launch comwin_save_file() */
	{
		saved_file = comwin_save_file(parent_window, filetypeslist, size, NULL);
		textview_printf(app->text, "In FileSave IF section : Filename is %s \n", saved_file);
	        textview_scroll_caret(app->text);

		if (saved_file == NULL) /* user aborted */
			app->nofilename = 1;
		else
		{
			/* check the file extension, if it is .uap continue here, else call ExportJSON() or ExportXML() */
			if (strstr(saved_file, ".uap") != NULL)
			{
				textview_printf(app->text, "In FileSave IF strstr section, before fwrite() : saved_file is %s, app->savedFile is %s, nofilename is %d \n",
						saved_file, app->savedFile, app->nofilename);
			        textview_scroll_caret(app->text);
				/* now we have the file name, write the contents of the setup / configuration to this filename */
				app->fp = fopen(saved_file, "w+"); /* somehow this statement failed !!! */
				if (app->fp)
				{
					textview_printf(app->text, "In FileSave IF strstr section, now performing fwrite()");
				        textview_scroll_caret(app->text);

					/* prepare the contents to write - in app object*/
					/* write the contents */
					/* fwrite(.....) */
					fclose(app->fp);
					app->savedFile = saved_file;
					app->nofilename = 0;

                                	/* updates the window title to reflect the file name */
                                	sprintf(title, "open62541 OPC UA demonstration : %s", saved_file);
                                	window_title(app->window, title);
					}
				else
				{
					/* error creating file, show a dialog box */
					textview_printf(app->text, "Error creating file : %s", saved_file);
                                	textview_scroll_caret(app->text);

					app->savedFile = NULL;
					app->nofilename = 1;
				}
			}
			else if(strstr(app->savedFile, ".xml") != NULL)
				FileExportToXML(app, parent_window);
			else if(strstr(app->savedFile, ".json") != NULL)
				FileExportToJSON(app, parent_window);
			else
			{
				/* undefined file extension, show a dialog box */
				textview_printf(app->text, "Error undefined file type : %s", saved_file);
                                textview_scroll_caret(app->text);
				app->savedFile = NULL;
				app->nofilename = 1;


			}
		}
	}
	else
	{
		textview_printf(app->text, "In FileSave() ELSE section : Filename is %s, nofilename is %d \n", app->savedFile, app->nofilename);
                textview_scroll_caret(app->text);
		/* just write the contents to the file */
		/*app->fp = fopen(app->savedFile, "r+w");*/
		/* fwrite(....) */
		/*fclose(app->fp);*/
	}
}
#endif

void FileSaveAs(App *app, Window *parent_window);
#ifdef REMOVE
{
	/* regardless whether there is a previous filename, still launch the saveAs dialog */
	/* for debugging purposes, show it in the text widget */

        const char_t *saved_file;
        const char_t *filetypeslist[] = {"uap", "xml", "json"};
        const uint32_t size=3;
	char title[100];

        textview_printf(app->text, "Filename is %s, nofilename is %d \n", app->savedFile, app->nofilename);
        textview_scroll_caret(app->text);
		saved_file = comwin_save_file(parent_window, filetypeslist, size, NULL);
                if (saved_file == NULL) /* user aborted */
                        app->nofilename = 1;
                else
                {
                        app->savedFile = saved_file;
                        app->nofilename = 0;

                        /* now we have the file name, write the contents of the setup / configuration to this filename */
                        app->fp = fopen(saved_file, "w+");
                        if (app->fp)
                        {
                                textview_printf(app->text, "In FileSaveAs IF(app->fp) section : Filename is %s, nofilename is %d \n", app->savedFile, app->nofilename);
		                textview_scroll_caret(app->text);
                                /* prepare the contents to write - in app object*/
                                /* write the contents */
                                /* fwrite(.....) */
                                fclose(app->fp);
				/* updates the window title to reflect the file name */
				sprintf(title, "open62541 OPC UA demonstration : %s", saved_file);
				window_title(app->window, title);
                        }
                        else
                        {
                                /* error creating file, show a dialog box */

                        }
                }

}
#endif

void FileClose(App *app, Window *parent_window);
#ifdef REMOVE
{
    Window *modalWindow;
    ModalData *data;

    /* creates a modal window */
    modalWindow = window_create(ekWINDOW_EDGE | ekWINDOW_TITLE | ekWINDOW_CLOSE);
    window_title(modalWindow, "Close");

    /*ModalData *data = i_modal_data(parent_window);*/
    data = heap_new(ModalData);
    data->parent = parent_window;
    data->type = UINT32_MAX;

	if (app->fp != NULL)
		fclose(app->fp);

	app->nofilename = 1;
	app->savedFile = NULL;
	/* close all the panels */
    	app->View_Project_IsShown = 0;
    	app->View_AddressSpace_IsShown = 0;
    	app->View_Log_IsShown = 0;
    	app->View_Attributes_IsShown = 0;
    	app->View_References_IsShown = 0;

	/* updates the window title to reflect the file name */
	window_title(app->window, "open62541 OPC UA demonstration");

	textview_printf(app->text, "Filename is %s, nofilename is %d \n", app->savedFile, app->nofilename);
        textview_scroll_caret(app->text);
}
#endif

#ifdef TRANSFER
static Window *i_create_flywin(void)
{
	uint32_t nrows = 4;
	Layout *layout = layout_create(2, nrows);
	Panel *panel = panel_create();
	Window *window = window_create(ekWINDOW_EDGE | ekWINDOW_TITLE | ekWINDOW_CLOSE | ekWINDOW_RESIZE);
	uint32_t i;

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
#endif
#ifdef TRANSFER
static void ev_hide_flyout_ViewProject(App *app, Event *e)
{
    textview_printf(app->text, "Flyout View->Project Hide event click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    window_hide(app->View_Project->flywin);
    app->View_Project_IsShown = 0;
    unref(e);
}
#endif
#ifdef TRANSFER
static void ev_hide_flyout_ViewAddressSpace(App *app, Event *e)
{
    textview_printf(app->text, "Flyout View->Address Space Hide event click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    window_hide(app->View_AddressSpace->flywin);
    app->View_AddressSpace_IsShown = 0;
    unref(e);
}
#endif
#ifdef TRANSFER
static void ev_hide_flyout_ViewLog(App *app, Event *e)
{
    textview_printf(app->text, "Flyout View->Log Hide event click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    window_hide(app->View_Log->flywin);
    app->View_Log_IsShown = 0;
    unref(e);
}
#endif
#ifdef TRANSFER
static void ev_hide_flyout_ViewAttributes(App *app, Event *e)
{
    textview_printf(app->text, "Flyout View->Attributes Hide event click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    window_hide(app->View_Attributes->flywin);
    app->View_Attributes_IsShown = 0;
    unref(e);
}
#endif
#ifdef TRANSFER
static void ev_hide_flyout_ViewReferences(App *app, Event *e)
{
    textview_printf(app->text, "Flyout View->References Hide event click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    window_hide(app->View_References->flywin);
    app->View_References_IsShown = 0;
    unref(e);
}
#endif
#ifdef TRANSFER
static void ev_OnMove_flyout_ViewProject(App *app, Event *e)
{
    V2Df mycoordinate;
    S2Df mysize;
    float x_offset, y_offset;

    #ifdef DEBUG
    textview_printf(app->text, "Flyout View->Project Move event detected \n");
    textview_scroll_caret(app->text);
    #endif
    /* get the screen coordinate of itself */
    //mycoordinate.x = window_get_origin(app->View_Project->flywin).x;
    //mycoordinate.y = window_get_origin(app->View_Project->flywin).y;
    mysize.width = window_get_size(app->View_Project->flywin).width;
    mysize.height = window_get_size(app->View_Project->flywin).height;

    textview_printf(app->text, "app->resolution %f %f \n", app->sys_resolution.x, app->sys_resolution.y);
    //textview_printf(app->text, "imaginaryLeftWindow %f %f \n", window_get_origin(app->imaginaryLeftWindow).x, window_get_origin(app->imaginaryLeftWindow).y);

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
#endif

/*
static void i_OnResize_AppWindow(App *app, Event *e)
{
         updates the size of the window and saved to sys_solution
	app->sys_resolution.x = window_get_size(app->View_Project->flywin).width;
        app->sys_resolution.y = window_get_size(app->View_Project->flywin).height;

    	unref(e);

}
*/
#ifdef TRANSFER
static void i_destroy_flyout(FlyOut **flyout)
{
	cassert_no_null(flyout);
	cassert_no_null(*flyout);
	window_destroy(&(*flyout)->flywin);
	if ((*flyout)->menu != NULL)
		menu_destroy(&(*flyout)->menu);
	heap_delete(flyout, FlyOut);
}
#endif
#ifdef TRANSFER
static void i_OnAlign(FlyOut *flyout, Event *e)
{
	const EvButton *p = event_params(e, EvButton);
	cassert_no_null(flyout);
	flyout->align = p->index;
}
#endif
#ifdef TRANSFER
static Layout *i_align_layout(FlyOut *flyout)
{

	Layout *layout = layout_create(4,1);
	Button *button1 = button_radio();
	button_OnClick(button1, listener(flyout, i_OnAlign, FlyOut));
	return layout;
}
#endif
#ifdef TRANSFER
static Layout *i_layout(FlyOut *flyout)
{
	Layout *layout1 = layout_create(1,5);
        Layout *layout2 = i_align_layout(flyout);
	layout_layout(layout1, layout2, 0, 1);
	return layout1;

}
#endif
#ifdef TRANSFER
static FlyOut *i_flyout(Window *window)
{
	FlyOut *flyout = heap_new(FlyOut);
	flyout->parent = window;
	flyout->flywin = i_create_flywin();	/* returns a handle to a newly created windows */
	flyout->menu = NULL;
	flyout->align = 0;
	return flyout;

}
#endif
#ifdef TRANSFER
static void i_destroy_modal_data(ModalData** data)
{
   heap_delete(data, ModalData);
}
#endif
#ifdef TRANSFER /* transfer to nappserver.c */
void ServerAdd(App *app, Window *parent_window)
{
    Window *modalServer;
    uint32_t i, j;
    /*Panel *GenPanel, *AuthPanel, *DecisionPanel;*/
    Panel *panel;
    ModalData *data;
    Layout *MainLayout, *GenLayout, *AuthLayout, *DecisionLayout;
    Label *label_configurationname, *label_pkistore, *label_endpointfilter, *label_anonymous, *label_username, *label_password, *label_certificate, *label_privatekey;
    Edit *edit_configurationname, *edit_pkistore, *edit_endpointfilter, *edit_username, *edit_password, *edit_certificate, *edit_privatekey;
    Button *pushOK, *pushCancel;
    Button *radio_anonymous, *radio_username, *radio_certificate;
    Button *check_store;
    textview_printf(app->text, "Filename is %s, nofilename is %d \n", app->savedFile, app->nofilename);
    textview_scroll_caret(app->text);

    /* creates a modal window */
    modalServer = window_create(ekWINDOW_EDGE | ekWINDOW_TITLE | ekWINDOW_CLOSE);
    window_title(modalServer, "Add Server");

    /*ModalData *data = i_modal_data(parent_window);*/
    data = heap_new(ModalData);
    data->parent = parent_window;
    data->type = UINT32_MAX;

    panel = panel_create();

    /* Creates panels to hold different layouts */
    /*GenPanel = panel_create();
    AuthPanel = panel_create();
    DecisionPanel = panel_create();*/

    /* Layout *layout = i_modal_layout(data); */
    MainLayout = layout_create(1,3);
    GenLayout = layout_create(2, 3); /* col, row */
    AuthLayout = layout_create(3, 5);
    DecisionLayout = layout_create(10, 1);

    label_configurationname = label_create();
    label_pkistore = label_create();
    label_endpointfilter = label_create();
    label_anonymous = label_create();
    label_username = label_create();
    label_password = label_create();
    label_certificate = label_create();
    label_privatekey = label_create();

    label_text(label_configurationname, "Configuration Name");
    label_text(label_pkistore, "PKI Store");
    label_text(label_endpointfilter, "Endpoint Filter");
    label_text(label_anonymous, "Anonymous");
    label_text(label_username, "Username");
    label_text(label_password, "Password");
    label_text(label_certificate, "Certificate");
    label_text(label_privatekey, "Private Key");

    edit_configurationname = edit_create(); edit_width(edit_configurationname, 300);
    edit_pkistore = edit_create(); edit_width(edit_pkistore, 300);
    edit_endpointfilter = edit_create(); edit_width(edit_endpointfilter, 300);
    edit_username = edit_create(); edit_width(edit_username, 300);
    edit_password = edit_create(); edit_width(edit_password, 300);
    edit_certificate = edit_create(); edit_width(edit_certificate, 300);
    edit_privatekey = edit_create(); edit_width(edit_privatekey, 300);

    pushOK = button_push(); button_text(pushOK, "OK");
    pushCancel = button_push(); button_text(pushCancel, "Cancel"); button_OnClick(pushCancel, listener(app, i_OnClick_ButtonCancel, App));

    radio_anonymous = button_radio(); button_text(radio_anonymous, "Anonymous");
    radio_username = button_radio(); button_text(radio_username, "Username");
    radio_certificate = button_radio(); button_text(radio_certificate, "Certificate");

    check_store = button_check(); button_text(check_store, "Store");

    /* col = 1, row = 3 */
    layout_hsize(MainLayout, 0, 600);

    /* sets up margins and col width and row height */
    /* Section 1 : col = 2, row = 3 */
    layout_hsize(GenLayout, 0, 200);
    layout_hsize(GenLayout, 1, 400);
    layout_hmargin(GenLayout,0,5);
    for (i=0; i<2; i++) {
      for(j=0; j<3; j++) {
        layout_halign(GenLayout, i,j, ekLEFT);
      }
    }
    for (i=0; i<3; i++)
        layout_vmargin(GenLayout, i, 2);
    layout_margin(GenLayout, 10); /* sets a fix margin around the border */

    /* Section 2 : col = 3, row = 5 */
    layout_hsize(AuthLayout, 0, 200); /* set a fix width of column 1 */
    layout_hsize(AuthLayout, 1, 300); /* sets a fix width of column 2 */
    layout_hsize(AuthLayout, 2, 100); /* fixed width of column 3 */
    layout_hmargin(AuthLayout,0,5);
    for (i=0; i<3; i++) {
      for (j=0; j<5; j++) {
        layout_halign(AuthLayout, i,j, ekLEFT);
      }
    }
    for (i=0; i<5; i++)
	layout_vmargin(AuthLayout, i, 2);
    layout_margin(AuthLayout, 10); /* sets a fix margin around the border */

    /* Section 3 : col = 10, row = 1 */
    for(i=0; i<9; i++)
	layout_hsize(DecisionLayout, i, 10); /* set a fix width of all columns */

    layout_vmargin(DecisionLayout, 0, 2);

    /* assigns the interface objects i.e. label, edit, ... to the layout in X(col),Y(row) coordinate, starts with index 0 */
    /* Section 1 : col = 2, row = 3 */
    layout_label(GenLayout, label_configurationname, 0, 0);
    layout_label(GenLayout, label_pkistore, 0,1);
    layout_label(GenLayout, label_endpointfilter, 0,2);

    layout_edit(GenLayout, edit_configurationname, 1,0);
    layout_edit(GenLayout, edit_pkistore, 1,1);
    layout_edit(GenLayout, edit_endpointfilter, 1,2);

    /* Section 2 : col = 2, row = 5 */
    layout_button(AuthLayout, radio_anonymous, 0,0);
    layout_button(AuthLayout, radio_username, 0,1);
    layout_label(AuthLayout, label_password, 0,2);
    layout_button(AuthLayout, radio_certificate, 0,3);
    layout_label(AuthLayout, label_privatekey, 0,4);

    layout_edit(AuthLayout, edit_username, 1,1);
    layout_edit(AuthLayout, edit_password, 1,2);
    layout_edit(AuthLayout, edit_certificate, 1,3);
    layout_edit(AuthLayout, edit_privatekey, 1,4);

    layout_button(AuthLayout, check_store, 2,1);

    /* Section 3 : col = 10, row = 1 */
    layout_button(DecisionLayout, pushOK, 8,0);
    layout_button(DecisionLayout, pushCancel, 9,0);

    /* assigns GenLayout, AuthLayout and DecisionLayout into MainLayout (2,3) */
    layout_layout(MainLayout, GenLayout, 0, 0);
    layout_layout(MainLayout, AuthLayout, 0,1);
    layout_layout(MainLayout, DecisionLayout, 0,2);

    /* assigns the layout to the panel */
    panel_layout(panel, MainLayout);
    /*
    panel_layout(AuthPanel, AuthLayout);
    panel_layout(DecisionPanel, DecisionLayout);*/

    panel_data(panel, &data, i_destroy_modal_data, ModalData);

    /* assigns the panel to the window and saves the handle to app */
    app->modalWindow = modalServer;
    window_panel(modalServer, panel);

    /* sets the default button to Cancel */
    window_defbutton(modalServer, pushCancel);

    /* centres the window */
    moveToCentre(modalServer, app);
    window_modal(modalServer, parent_window);

    if (data != NULL)
    	heap_delete(&data, ModalData);
    window_destroy(&app->modalWindow);
}
#endif

void ServerRemove(App *app, Window *parent_window)
{
    Window *modalServer;
    Panel *panel;
    ModalData *data;
    Layout *MainLayout, *TextLayout, *DecisionLayout;
    Label *label_question;
    Button *pushOK, *pushCancel;
    uint32_t i;

    textview_printf(app->text, "Filename is %s, nofilename is %d \n", app->savedFile, app->nofilename);
    textview_scroll_caret(app->text);

    /* creates a modal window */
    modalServer = window_create(ekWINDOW_EDGE | ekWINDOW_TITLE | ekWINDOW_CLOSE);
    window_title(modalServer, "Remove Server");

    /*ModalData *data = i_modal_data(parent_window);*/
    data = heap_new(ModalData);
    data->parent = parent_window;
    data->type = UINT32_MAX;

    panel = panel_create();

    MainLayout = layout_create(5,2); /* col, row */
    TextLayout = layout_create(1,1);
    DecisionLayout = layout_create(5, 1);

    label_question = label_create();
    label_text(label_question, "Do you really want to remove the server ?");
    pushOK = button_push(); button_text(pushOK, "OK");
    pushCancel = button_push(); button_text(pushCancel, "Cancel"); button_OnClick(pushCancel, listener(app, i_OnClick_ButtonCancel, App));

    /* assigns the layout to the panel */
    panel_layout(panel, MainLayout);
    layout_layout(MainLayout, TextLayout, 0,0);
    layout_layout(MainLayout, DecisionLayout, 0,1);

    /* sets up margins and col width and row height */
    /* Section 1 : col = 1, row = 1 */
    layout_hsize(TextLayout, 0, 300);
    layout_hmargin(TextLayout,0,5);
        layout_halign(TextLayout, 0,0, ekCENTER);
        layout_vmargin(TextLayout, 0, 0);
    layout_margin(TextLayout, 10); /* sets a fix margin around the border */

    /* Section 2 : col = 5, row = 1 */
    for(i=0; i<5; i++)
        layout_hsize(DecisionLayout, i, 10); /* set a fix width of all columns */
 
    layout_vmargin(DecisionLayout, 0, 2);

    /* assigns the interface objects i.e. label, edit, ... to the layout in X(col),Y(row) coordinate, starts with index 0 */
    /* Section 1 : col = 1, row = 1 */
    layout_label(TextLayout, label_question, 0,0);

    /* Section 2 : col = 5, row = 1 */
    layout_button(DecisionLayout, pushOK, 1,0);
    layout_button(DecisionLayout, pushCancel, 3,0);

    /* assigns the panel to the window and saves the handle to app */
    panel_data(panel, &data, i_destroy_modal_data, ModalData);

    app->modalWindow = modalServer;
    window_panel(modalServer, panel);

    /* sets the default button to Cancel */
    window_defbutton(modalServer, pushCancel);

    moveToCentre(modalServer, app);
    window_modal(modalServer, parent_window);

    if (data != NULL)
    	heap_delete(&data, ModalData);
    window_destroy(&app->modalWindow);
}

void ServerConnect(App *app, Window *parent_window)
{
    Window *modalWindow;
    ModalData *data;

    data = heap_new(ModalData);

    textview_printf(app->text, "Filename is %s, nofilename is %d \n", app->savedFile, app->nofilename);
    textview_scroll_caret(app->text);

    /* creates a modal window */
    modalWindow = window_create(ekWINDOW_EDGE | ekWINDOW_TITLE | ekWINDOW_CLOSE);
    window_title(modalWindow, "Remove Server");
    /*ModalData *data = i_modal_data(parent_window);*/
    data = heap_new(ModalData);
    data->parent = parent_window;
    data->type = UINT32_MAX;

    window_modal(modalWindow, parent_window);
    window_show(modalWindow);

    window_destroy(&app->modalWindow);

}

void ServerDisconnect(App *app, Window *parent_window)
{
    Window *modalWindow;
    ModalData *data;

    data = heap_new(ModalData);

    textview_printf(app->text, "Filename is %s, nofilename is %d \n", app->savedFile, app->nofilename);
    textview_scroll_caret(app->text);

    /* creates a modal window */
    modalWindow = window_create(ekWINDOW_EDGE | ekWINDOW_TITLE | ekWINDOW_CLOSE);
    window_title(modalWindow, "Disconnet Server");
    /*ModalData *data = i_modal_data(parent_window);*/
    data = heap_new(ModalData);
    data->parent = parent_window;
    data->type = UINT32_MAX;

    window_modal(modalWindow, parent_window);
    window_show(modalWindow);

    window_destroy(&app->modalWindow);

}

void ServerProperties(App *app, Window *parent_window);
#ifdef REMOVE
{
    Window *modalWindow;
    ModalData *data;

    data = heap_new(ModalData);

    textview_printf(app->text, "Filename is %s, nofilename is %d \n", app->savedFile, app->nofilename);
    textview_scroll_caret(app->text);

    /* creates a modal window */
    modalWindow = window_create(ekWINDOW_EDGE | ekWINDOW_TITLE | ekWINDOW_CLOSE);
    window_title(modalWindow, "Server Properties");
    /*ModalData *data = i_modal_data(parent_window);*/
    data = heap_new(ModalData);
    data->parent = parent_window;
    data->type = UINT32_MAX;

    window_modal(modalWindow, parent_window);
    window_show(modalWindow);

    window_destroy(&app->modalWindow);

}
#endif

void ServerChangeUser(App *app, Window *parent_window)
{
    Window *modalWindow;
    ModalData *data;

    data = heap_new(ModalData);

    textview_printf(app->text, "Filename is %s, nofilename is %d \n", app->savedFile, app->nofilename);
    textview_scroll_caret(app->text);

    /* creates a modal window */
    modalWindow = window_create(ekWINDOW_EDGE | ekWINDOW_TITLE | ekWINDOW_CLOSE);
    window_title(modalWindow, "Change Username");
    /*ModalData *data = i_modal_data(parent_window);*/
    data = heap_new(ModalData);
    data->parent = parent_window;
    data->type = UINT32_MAX;

    window_modal(modalWindow, parent_window);
    window_show(modalWindow);

    window_destroy(&app->modalWindow);
}

void ServerChangePassword(App *app, Window *parent_window)
{
    Window *modalWindow;
    ModalData *data;

    data = heap_new(ModalData);

    textview_printf(app->text, "Filename is %s, nofilename is %d \n", app->savedFile, app->nofilename);
    textview_scroll_caret(app->text);

    /* creates a modal window */
    modalWindow = window_create(ekWINDOW_EDGE | ekWINDOW_TITLE | ekWINDOW_CLOSE);
    window_title(modalWindow, "Change Password");
    /*ModalData *data = i_modal_data(parent_window);*/
    data = heap_new(ModalData);
    data->parent = parent_window;
    data->type = UINT32_MAX;

    window_modal(modalWindow, parent_window);
    window_show(modalWindow);

    window_destroy(&app->modalWindow);

}

void ViewProject(App *app, Window *parent_window);
#ifdef REMOVE /* transfer to napview.c */
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

	menuitem_state(app->view_project, ekGUI_ON);

	window_OnMoved(flyout->flywin, listener(app, ev_OnMove_flyout_ViewProject, App));
        window_OnClose(flyout->flywin, listener(app, ev_hide_flyout_ViewProject, App));
    }
    else
    {
        /* the View->Project flyout window already existed, check what is the current state ? */

        if (app->View_Project_IsShown == 0) /* it is currently hidden */
        {
                window_show(app->View_Project->flywin);     /* show it */
                app->View_Project_IsShown = 1;      /* set the flag to true */

		menuitem_state(app->view_project, ekGUI_ON);
        }
        else    /* it is currently shown */
        {
                window_hide(app->View_Project->flywin); /* hide it */
                app->View_Project_IsShown = 0;       /* set the flag to false */

                /* !!!!!  somehow this cause the view menu to disappear !!!! */
	 	/* menuitem_state(app->view_project, ekGUI_OFF); */
        }
    }

        layout = i_layout(flyout);
        panel = panel_create();
        panel_data(panel, &flyout, i_destroy_flyout, FlyOut);
        panel_layout(panel, layout);
}
#endif

void ViewAddressSpace(App *app, Window *parent_window);
#ifdef REMOVE
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
	menuitem_state(app->view_addressspace, ekGUI_ON);

        window_OnClose(flyout->flywin, listener(app, ev_hide_flyout_ViewAddressSpace, App));
    }
    else
    {
        /* the View->AddressSpace flyout window already existed, check what is the current state ? */
        if (app->View_AddressSpace_IsShown == 0) /* it is currently hidden */
        {
                window_show(app->View_AddressSpace->flywin);     /* show it */
                app->View_AddressSpace_IsShown = 1;      /* set the flag to true */
		menuitem_state(app->view_addressspace, ekGUI_ON);
        }
        else    /* it is currently shown */
        {
                window_hide(app->View_AddressSpace->flywin); /* hide it */
                app->View_AddressSpace_IsShown = 0;       /* set the flag to false */

		/* !!!!!  somehow this cause the menu to disappear !!!! */
		/* menuitem_state(app->view_addressspace, ekGUI_OFF); */
        }
    }

        layout = i_layout(flyout);
        panel = panel_create();
        panel_data(panel, &flyout, i_destroy_flyout, FlyOut);
        panel_layout(panel, layout);
}
#endif

void ViewLog(App *app, Window *parent_window);
#ifdef REMOVE
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
	menuitem_state(app->view_log, ekGUI_ON);

        window_OnClose(flyout->flywin, listener(app, ev_hide_flyout_ViewLog, App));
    }
    else
    {
        /* the View->Log flyout window already existed, check what is the current state ? */

        if (app->View_Log_IsShown == 0) /* it is currently hidden */
        {
                window_show(app->View_Log->flywin);     /* show it */
                app->View_Log_IsShown = 1;      /* set the flag to true */
		menuitem_state(app->view_log, ekGUI_ON);
        }
        else    /* it is currently shown */
        {
                window_hide(app->View_Log->flywin); /* hide it */
                app->View_Log_IsShown = 0;       /* set the flag to false */
		/* !!!!!  somehow this cause the menu to disappear !!!! */
		/* menuitem_state(app->view_log, ekGUI_OFF); */
        }
    }

        layout = i_layout(flyout);
        panel = panel_create();
        panel_data(panel, &flyout, i_destroy_flyout, FlyOut);
        panel_layout(panel, layout);
}
#endif

void ViewAttributes(App *app, Window *parent_window);
#ifdef REMOVE
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
        menuitem_state(app->view_attributes, ekGUI_ON);

        window_OnClose(flyout->flywin, listener(app, ev_hide_flyout_ViewAttributes, App));
    }
    else
    {
        /* the View->Attributes flyout window already existed, check what is the current state ? */

        if (app->View_Attributes_IsShown == 0) /* it is currently hidden */
        {
                window_show(app->View_Attributes->flywin);     /* show it */
                app->View_Attributes_IsShown = 1;      /* set the flag to true */
		menuitem_state(app->view_attributes, ekGUI_ON);
        }
        else    /* it is currently shown */
        {
                window_hide(app->View_Attributes->flywin); /* hide it */
                app->View_Attributes_IsShown = 0;       /* set the flag to false */
		/* !!!!!  somehow this cause the menu to disappear !!!! */
		/*menuitem_state(app->view_attributes, ekGUI_OFF); */
        }
    }

        layout = i_layout(flyout);
        panel = panel_create();
        panel_data(panel, &flyout, i_destroy_flyout, FlyOut);
        panel_layout(panel, layout);
}
#endif

void ViewReferences(App *app, Window *parent_window);
#ifdef REMOVE
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
        menuitem_state(app->view_references, ekGUI_ON);

	window_OnClose(flyout->flywin, listener(app, ev_hide_flyout_ViewReferences, App));
    }
    else
    {
	/* the View->Reference flyout window already existed, check what is the current state ? */

	if (app->View_References_IsShown == 0) /* it is currently hidden */
	{
		window_show(app->View_References->flywin);     /* show it */
        	app->View_References_IsShown = 1;      /* set the flag to true */
                menuitem_state(app->view_references, ekGUI_ON);
	}
	else	/* it is currently shown */
	{
		window_hide(app->View_References->flywin); /* hide it */
		app->View_References_IsShown = 0;	/* set the flag to false */
		/* !!!!!  somehow this cause the menu to disappear !!!! */
                /* menuitem_state(app->view_references, ekGUI_OFF); */
	}
    }

   	textview_printf(app->text, "menuitem_state(view->References is %d \n", menuitem_get_state(app->view_references)); /* 0=ekGUI_OFF, 1=ekGUI_ON, 2= ekGUI_MIXED */
        textview_scroll_caret(app->text);

	layout = i_layout(flyout);
	panel = panel_create();
	panel_data(panel, &flyout, i_destroy_flyout, FlyOut);
	panel_layout(panel, layout);

}
#endif

/*----------------Section on Callbacks --------------------------------------------------------*/
#ifdef TRANSFER
static void i_OnMoved_AppWindow(App *app, Event *e)
{
	/* update the screen coordinates */
	//app->screen_coordinate.x = window_get_origin(app->window).x;
	//app->screen_coordinate.y = window_get_origin(app->window).y;

        textview_printf(app->text, "App->screen coordinate :  %f, %f\n", app->screen_coordinate.x, app->screen_coordinate.y);
        textview_scroll_caret(app->text);
	unref(e);
}
#endif
#ifdef TRANSFER
static void i_OnResize_AppWindow(App *app, Event *e)
{
        /* update the screen resolution */
        app->sys_resolution.x = window_get_size(app->window).width;
        app->sys_resolution.y = window_get_size(app->window).height;

        textview_printf(app->text, "App->screen size :  %f, %f\n", app->sys_resolution.x, app->sys_resolution.y);
        textview_scroll_caret(app->text);

	/* readjust the layout HERE*/
        /* set a minimum height of the status section */
        layout_vsize(app->canvasLayout, 0, 600);
        layout_vsize(app->statusLayout, 0, 400);


        unref(e);
}
#endif
#ifdef TRANSFER
static void i_OnClose(App *app, Event *e)
{
    osapp_finish();
    unref(app);
    unref(e);
}
#endif
#ifdef TRANSFER
static void i_OnClick_file_new(App *app, Event *e)
{
    textview_printf(app->text, "File->New Menu click (%d)\n", app->clicks);
        textview_scroll_caret(app->text);

    app->clicks += 1;

    unref(e);
    /*createAttributesWindow(app->window);*/
}
#endif

#ifdef TRANSFER
static void i_OnClick_file_open(App *app, Event *e)
{
    textview_printf(app->text, "File->Open Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    FileOpen(app, app->window);
    unref(e);
}
#endif

#ifdef TRANSFER
static void i_OnClick_file_save(App *app, Event *e)
{
    textview_printf(app->text, "File->Save Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);

    app->clicks += 1;
    FileSave(app, app->window);

    unref(e);
}
#endif

#ifdef TRANSFER
static void i_OnClick_file_saveAs(App *app, Event *e)
{
    textview_printf(app->text, "View->Save As Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    FileSaveAs(app, app->window);
    unref(e);
}
#endif

#ifdef TRANSFER
static void i_OnClick_file_close(App *app, Event *e)
{
    textview_printf(app->text, "View->Close Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    FileClose(app, app->window);
    unref(e);
}
#endif

#ifdef TRANSFER
static void i_OnClick_view_project(App *app, Event *e)
{
    textview_printf(app->text, "View->Project Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    ViewProject(app, app->window);
    unref(e);
}
#endif

#ifdef TRANSFER
static void i_OnClick_view_addressspace(App *app, Event *e)
{
    textview_printf(app->text, "View->Address Space Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    ViewAddressSpace(app, app->window);
    unref(e);
}
#endif

#ifdef TRANSFER
static void i_OnClick_view_log(App *app, Event *e)
{
    textview_printf(app->text, "View->Log Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    ViewLog(app, app->window);
    unref(e);
}
#endif

#ifdef TRANSFER
static void i_OnClick_view_attributes(App *app, Event *e)
{
    textview_printf(app->text, "View->Attributes Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    ViewAttributes(app, app->window);
    unref(e);
}
#endif

#ifdef TRANSFER
static void i_OnClick_view_references(App *app, Event *e)
{
    textview_printf(app->text, "View->References Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    ViewReferences(app, app->window);
    unref(e);

}
#endif

#ifdef TRANSFER
static void i_OnClick_view_filetoolbar(App *app, Event *e)
{
    textview_printf(app->text, "View->File Toolbar Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    unref(e);

}
#endif

#ifdef TRANSFER
static void i_OnClick_view_servertoolbar(App *app, Event *e)
{
    textview_printf(app->text, "View->Server Toolbar  Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    unref(e);

}
#endif

#ifdef TRANSFER
static void i_OnClick_view_documenttoolbar(App *app, Event *e)
{
    textview_printf(app->text, "View->Document Toolbar  Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    unref(e);

}
#endif

#ifdef TRANSFER
static void i_OnClick_server_add(App *app, Event *e)
{
    textview_printf(app->text, "Server->Add Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    ServerAdd(app, app->window);

    unref(e);
}
#endif

#ifdef TRANSFER
static void i_OnClick_server_remove(App *app, Event *e)
{
    textview_printf(app->text, "Server->Remove Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    ServerRemove(app, app->window);

    unref(e);
}
#endif

#ifdef TRANSFER
static void i_OnClick_server_connect(App *app, Event *e)
{
    textview_printf(app->text, "Server->Connect Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    ServerConnect(app, app->window);

    unref(e);
}
#endif
#ifdef TRANSFER
static void i_OnClick_server_disconnect(App *app, Event *e)
{
    textview_printf(app->text, "Server->Disconnect Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    ServerDisconnect(app, app->window);

    unref(e);
}
#endif
#ifdef TRANSFER
static void i_OnClick_server_properties(App *app, Event *e)
{
    textview_printf(app->text, "Server->Properties Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    ServerProperties(app, app->window);

    unref(e);
}
#endif
#ifdef TRANSFER
static void i_OnClick_server_changeuser(App *app, Event *e)
{
    textview_printf(app->text, "Server->Change User Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    ServerChangeUser(app, app->window);

    unref(e);
}
#endif
#ifdef TRANSFER
static void i_OnClick_server_changepassword(App *app, Event *e)
{
    textview_printf(app->text, "Server->Change Password Menu click (%d)\n", app->clicks);
    app->clicks += 1;
    textview_scroll_caret(app->text);
    ServerChangePassword(app, app->window);

    unref(e);
}
#endif
#ifdef TRANSFER
static void i_OnClick_document_add(App *app, Event *e)
{
    textview_printf(app->text, "Document->Add Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    unref(e);

}
#endif
#ifdef TRANSFER
static void i_OnClick_document_remove(App *app, Event *e)
{
    textview_printf(app->text, "Document->Remove Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    unref(e);

}
#endif
#ifdef TRANSFER
static void i_OnClick_document_hide_unhide(App *app, Event *e)
{
    textview_printf(app->text, "Document->Hide/ Unhide all dock widgets Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    unref(e);

}
#endif
#ifdef TRANSFER
static void i_OnClick_settings_plugins(App *app, Event *e)
{
    textview_printf(app->text, "Settings->Plugins Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    unref(e);

}
#endif
#ifdef TRANSFER
static void i_OnClick_settings_configure_OPCSvr(App *app, Event *e)
{
    textview_printf(app->text, "Settings->Configure->OPCSvr Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    unref(e);

}
#endif
#ifdef TRANSFER
static void i_OnClick_settings_configure_LDS(App *app, Event *e)
{
    textview_printf(app->text, "Settings->Configure->LDS Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    unref(e);
}
#endif
#ifdef TRANSFER
static void i_OnClick_settings_configure_GDS(App *app, Event *e)
{
    textview_printf(app->text, "Settings->Configure->GDS Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    unref(e);


}
#endif
#ifdef TRANSFER
static void i_OnClick_settings_configure_message_broker(App *app, Event *e)
{
    textview_printf(app->text, "Settings->Configure->MSB Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    unref(e);


}
#endif
#ifdef TRANSFER
static void i_OnClick_settings_managecertificates(App *app, Event *e)
{
    textview_printf(app->text, "Settings->Manage Certificates Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    unref(e);

}
#endif
#ifdef TRANSFER
static void i_OnClick_help_manual(App *app, Event *e)
{
    textview_printf(app->text, "Help->Manual Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    unref(e);

}
#endif
#ifdef TRANSFER
static void i_OnClick_help_whatsthis(App *app, Event *e)
{
    textview_printf(app->text, "Help->What's This? Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    unref(e);

}
#endif
#ifdef TRANSFER
static void i_OnClick_help_licensestatus(App *app, Event *e)
{
    textview_printf(app->text, "Help->License Status Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    unref(e);

}
#endif
#ifdef TRANSFER
static void i_OnClick_help_checkforupdates(App *app, Event *e)
{
    textview_printf(app->text, "Help->Check for UpdatesMenu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    unref(e);

}
#endif
#ifdef TRANSFER
static void i_OnClick_help_about(App *app, Event *e)
{
    textview_printf(app->text, "Help->About Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    unref(e);

}
#endif

/*----------------end Section on Callbacks-------------------------*/




/*
void createDocumentWindow(App *app)
{


}

void createProjectWindow(App *app)
{

}

void createAddressSpaceWindow(App *app)
{

}

void createLogWindow(App *app)
{

}

void createAttributesWindow(App *app)
{

}
*/

/*---------------------------------------------------------------------------*/
/* not required to be called upfront, but the individual createXXXWindow() will be invoked when a callback is invoked via the menu */
/*void createSubWindows(Window *window)*/
/*{*/
	/* This Window holds the different tabs that can be turned on/off in Topmenu->Document->Add or Topmenu->Document->Remove */
/*	createDocumentWindow(window); */

	/* These are dockable windows that can be turned on/off in Topmenu->View */
/*	createProjectWindow(window); */
/*	createAddressSpaceWindow(window); */
/*	createLogWindow(window);	*/
/*	createAttributesWindow(window); */
/*	createReferencesWindow(window); */
/*}*/

/*---------------------------------------------------------------------------*/
void createMenus(App *app);
#ifdef REMOVE /* transfer to nappmenu.c */
{
    Menu *topmenu;
    MenuItem *file, *view, *server, *document, *settings, *help;
    Menu *submenu_file, *submenu_view, *submenu_server, *submenu_document, *submenu_settings, *submenu_help;
    Menu *submenu_settings_configure;

    MenuItem *file_new, *file_open, *file_save, *file_saveAs, *file_recentprojects, *file_separator, *file_close, *file_quit;
    /* the following menuitems view->XXX  are declared in app */
    MenuItem *view_separator; /* *view_project, *view_addressspace, *view_log, *view_attributes, *view_references, *view_filetoolbar, *view_servertoolbar, *view_documenttoolbar;*/
    MenuItem *server_add, *server_remove, *server_connect, *server_disconnect, *server_properties, *server_separator, *server_changeuser, *server_changepassword;
    MenuItem *document_add, *document_remove, *document_hide_unhide;
    MenuItem *settings_plugins, *settings_configure, *settings_separator, *settings_managecertificates;
    MenuItem *help_manual, *help_whatsthis, *help_licensestatus, *help_checkforupdates, *help_separator, *help_about;

    MenuItem *configure_OPCSvr, *configure_LDS, *configure_GDS, *configure_MSB;

    /*Image *image_file_new, *image_file_open, *image_file_save, *image_file_saveAs, *image_file_quit;*/
    Image *image_view_project, *image_view_addressspace, *image_view_log, *image_view_attributes, *image_view_references, *image_view_filetoolbar, *image_view_servertoolbar, *image_view_documenttoolbar;

/* step 1 */
    /* create top level menu */
    app->top_menu = menu_create();
    topmenu = app->top_menu;

    osapp_menubar(topmenu, app->window);

    file = menuitem_create();
    view = menuitem_create();
    server = menuitem_create();
    document = menuitem_create();
    settings = menuitem_create();
    help = menuitem_create();

    /* label the menu items */
    menuitem_text(file, "Project");
    menuitem_text(view, "View");
    menuitem_text(server, "Server");
    menuitem_text(document, "Document");
    menuitem_text(settings, "Settings");
    menuitem_text(help, "Help");

    /* add the menu items to the top level menu */
    menu_add_item(topmenu, file);
    menu_add_item(topmenu, view);
    menu_add_item(topmenu, server);
    menu_add_item(topmenu, document);
    menu_add_item(topmenu, settings);
    menu_add_item(topmenu, help);


/* step 2 */
    /* create drop-down menus (submenus) */

    /* drop down menu items for 'File' */
    submenu_file = menu_create();
    osapp_menubar(submenu_file, app->window);
      file_new = menuitem_create(); menuitem_enabled(file_new, 1); menuitem_visible(file_new, 1);
      file_open = menuitem_create(); menuitem_enabled(file_open, 1); menuitem_visible(file_open, 1);
      file_save = menuitem_create(); menuitem_enabled(file_save, 1); menuitem_visible(file_save, 1);
      file_saveAs = menuitem_create(); menuitem_enabled(file_saveAs, 1); menuitem_visible(file_saveAs, 1);
      file_recentprojects = menuitem_create();
      file_separator = menuitem_separator();
      file_close = menuitem_create(); menuitem_enabled(file_close, 1), menuitem_visible(file_close, 1);
      file_quit = menuitem_create(); menuitem_enabled(file_quit, 1); menuitem_visible(file_quit, 1);

      menuitem_text(file_new,            "New       Ctrl+N");
      menuitem_text(file_open,           "Open      Ctrl+O");
      menuitem_text(file_save,           "Save      Ctrl+S");
      menuitem_text(file_saveAs,         "Save As ..      ");
      menuitem_text(file_recentprojects, "Recents Projects");
      menuitem_text(file_close,          "Close           ");
      menuitem_text(file_quit,           "Quit            ");

      /* KIV first until suitable size icons/ images can be found */
      /*image_file_new = image_from_file("/home/pi/nappgui_arc/jacky/resources/file-new-icon-png-31179.png", NULL);*/
      /*image_file_open = image_from_file("/home/pi/nappgui_src/jacky/resources/open.jpg", NULL);*/
      /*image_file_save = image_from_file("/home/pi/nappgui_src/jacky/resources/file-save-icon-19.jpg", NULL);*/
      /*image_file_saveAs = image_from_file("/home/pi/nappgui_src/jacky/resources/filesaveas.jpg", NULL);*/
      /*image_file_quit = image_from_file("home/pi/nappgui_src/jacky/resources/Quit-Button-846x604.png", NULL);*/

      menu_add_item(submenu_file, file_new); /* menuitem_image(file_new, image_file_new); */
      menu_add_item(submenu_file, file_open); /* menuitem_image(file_open, image_file_open);*/
      menu_add_item(submenu_file, file_save); /* menuitem_image(file_save, image_file_save); */
      menu_add_item(submenu_file, file_saveAs); /* menuitem_image(file_saveAs, image_file_saveAs); */
      menu_add_item(submenu_file, file_recentprojects);
      menu_add_item(submenu_file, file_separator);
      menu_add_item(submenu_file, file_close);
      menu_add_item(submenu_file, file_quit); /* menuitem_image(file_quit, image_file_quit); */

      menuitem_submenu(file, &submenu_file);

      menuitem_OnClick(file_new, listener(app, i_OnClick_file_new, App));
      menuitem_OnClick(file_open, listener(app, i_OnClick_file_open, App));
      menuitem_OnClick(file_save, listener(app, i_OnClick_file_save, App));
      menuitem_OnClick(file_saveAs, listener(app, i_OnClick_file_saveAs, App));
      menuitem_OnClick(file_close, listener(app, i_OnClick_file_close, App));
      menuitem_OnClick(file_quit, listener(app, i_OnClose, App));

    /* drop down menu items for View */
    submenu_view = menu_create();
    osapp_menubar(submenu_view, app->window);
      app->view_project = menuitem_create(); menuitem_enabled(app->view_project, 1); menuitem_visible(app->view_project, 1);
      app->view_addressspace =  menuitem_create(); menuitem_enabled(app->view_addressspace, 1); menuitem_visible(app->view_addressspace, 1);
      app->view_log = menuitem_create(); menuitem_enabled(app->view_log, 1); menuitem_visible(app->view_log, 1);
      app->view_attributes = menuitem_create(); menuitem_enabled(app->view_attributes, 1); menuitem_visible(app->view_attributes, 1);
      app->view_references = menuitem_create(); menuitem_enabled(app->view_references, 1); menuitem_visible(app->view_references, 1);
      view_separator = menuitem_separator();
      app->view_filetoolbar = menuitem_create(); menuitem_enabled(app->view_filetoolbar, 1); menuitem_visible(app->view_filetoolbar, 1);
      app->view_servertoolbar = menuitem_create(); menuitem_enabled(app->view_servertoolbar, 1); menuitem_visible(app->view_servertoolbar, 1);
      app->view_documenttoolbar = menuitem_create(); menuitem_enabled(app->view_documenttoolbar, 1); menuitem_visible(app->view_documenttoolbar, 1);


      image_view_project = image_from_file("/home/pi/nappgui_arc/jacky/resources/icons8-checkmark-32.jpg", NULL);   /* to replace with a new icon file */
      image_view_addressspace = image_from_file("/home/pi/nappgui_arc/jacky/resources/icons8-checkmark-32.jpg", NULL);  /* to replace with a new icon file */
      image_view_log = image_from_file("/home/pi/nappgui_arc/jacky/resources/icons8-checkmark-32.jpg", NULL);  /* to replace with a new icon file */
      image_view_attributes = image_from_file("/home/pi/nappgui_arc/jacky/resources/icons8-checkmark-32.jpg", NULL);  /* to replace with a new icon file */
      image_view_references = image_from_file("/home/pi/nappgui_arc/jacky/resources/icons8-checkmark-32.jpg", NULL);  /* to replace with a new icon file */
      image_view_filetoolbar = image_from_file("/home/pi/nappgui_arc/jacky/resources/icons8-checkmark-32.jpg", NULL); /*  to replace with a new icon file */
      image_view_servertoolbar = image_from_file("/home/pi/nappgui_arc/jacky/resources/icons8-checkmark-32.jpg", NULL);  /* to replace with a new icon file */
      image_view_documenttoolbar = image_from_file("/home/pi/nappgui_arc/jacky/resources/icons8-checkmark-32.jpg", NULL); /* to replace with a new icon file */

      /* displays a tick next to the menuitem if it is selected, tracked in app */
      menuitem_text(app->view_project,         "Project           ");  menuitem_state(app->view_project, ekGUI_ON);
      menuitem_text(app->view_addressspace,    "Address Space     ");  menuitem_state(app->view_addressspace, ekGUI_ON);
      menuitem_text(app->view_log,             "Log               ");  menuitem_state(app->view_log, ekGUI_ON);
      menuitem_text(app->view_attributes,      "Attributes        ");  menuitem_state(app->view_attributes, ekGUI_ON);
      menuitem_text(app->view_references,      "References        ");  menuitem_state(app->view_references, ekGUI_ON);
      menuitem_text(app->view_filetoolbar,     "File Toolbar      ");  menuitem_state(app->view_filetoolbar, ekGUI_ON);
      menuitem_text(app->view_servertoolbar,   "Server Toolbar    ");  menuitem_state(app->view_servertoolbar, ekGUI_ON);
      menuitem_text(app->view_documenttoolbar, "Document Toolbar  ");  menuitem_state(app->view_documenttoolbar, ekGUI_ON);

      /* adds the image icon to the menu item */
      menu_add_item(submenu_view, app->view_project);  menuitem_image(app->view_project, image_view_project);
      menu_add_item(submenu_view, app->view_addressspace); menuitem_image(app->view_addressspace, image_view_addressspace);
      menu_add_item(submenu_view, app->view_log); menuitem_image(app->view_log, image_view_log);
      menu_add_item(submenu_view, app->view_attributes); menuitem_image(app->view_attributes, image_view_attributes);
      menu_add_item(submenu_view, app->view_references); menuitem_image(app->view_references, image_view_references);
      menu_add_item(submenu_view, view_separator);
      menu_add_item(submenu_view, app->view_filetoolbar); menuitem_image(app->view_filetoolbar, image_view_filetoolbar);
      menu_add_item(submenu_view, app->view_servertoolbar); menuitem_image(app->view_servertoolbar, image_view_servertoolbar);
      menu_add_item(submenu_view, app->view_documenttoolbar); menuitem_image(app->view_documenttoolbar, image_view_documenttoolbar);

      menuitem_submenu(view, &submenu_view);

      menuitem_OnClick(app->view_project, listener(app, i_OnClick_view_project, App));
      menuitem_OnClick(app->view_addressspace, listener(app, i_OnClick_view_addressspace, App));
      menuitem_OnClick(app->view_log, listener(app, i_OnClick_view_log, App));
      menuitem_OnClick(app->view_attributes, listener(app, i_OnClick_view_attributes, App));
      menuitem_OnClick(app->view_references, listener(app, i_OnClick_view_references, App));
      menuitem_OnClick(app->view_filetoolbar, listener(app, i_OnClick_view_filetoolbar, App));
      menuitem_OnClick(app->view_servertoolbar, listener(app, i_OnClick_view_servertoolbar, App));
      menuitem_OnClick(app->view_documenttoolbar, listener(app, i_OnClick_view_documenttoolbar, App));

    /* drop down menu items for Server */
    submenu_server = menu_create();
    osapp_menubar(submenu_server, app->window);
      server_add = menuitem_create(); menuitem_enabled(server_add, 1); menuitem_visible(server_add, 1);
      server_remove = menuitem_create(); menuitem_enabled(server_remove, 1); menuitem_visible(server_remove, 1);
      server_connect = menuitem_create(); menuitem_enabled(server_connect, 1); menuitem_visible(server_connect, 1);
      server_disconnect = menuitem_create(); menuitem_enabled(server_disconnect, 1); menuitem_visible(server_disconnect, 1);
      server_properties = menuitem_create(); menuitem_enabled(server_properties, 1); menuitem_visible(server_properties, 1);
      server_separator = menuitem_separator();
      server_changeuser = menuitem_create(); menuitem_enabled(server_changeuser, 1); menuitem_visible(server_changeuser, 1);
      server_changepassword = menuitem_create(); menuitem_enabled(server_changepassword, 1); menuitem_visible(server_changepassword, 1);

      menuitem_text(server_add,            "Add ...             ");
      menuitem_text(server_remove,         "Remove              ");
      menuitem_text(server_connect,        "Connect             ");
      menuitem_text(server_disconnect,     "Disconnect          ");
      menuitem_text(server_properties,     "Properties          ");
      menuitem_text(server_changeuser,     "Change user...      ");
      menuitem_text(server_changepassword, "Change password...  ");

      menu_add_item(submenu_server, server_add);
      menu_add_item(submenu_server, server_remove);
      menu_add_item(submenu_server, server_connect);
      menu_add_item(submenu_server, server_disconnect);
      menu_add_item(submenu_server, server_properties);
      menu_add_item(submenu_server, server_separator);
      menu_add_item(submenu_server, server_changeuser);
      menu_add_item(submenu_server, server_changepassword);

      menuitem_submenu(server, &submenu_server);

      menuitem_OnClick(server_add, listener(app, i_OnClick_server_add, App));
      menuitem_OnClick(server_remove, listener(app, i_OnClick_server_remove, App));
      menuitem_OnClick(server_connect, listener(app, i_OnClick_server_connect, App));
      menuitem_OnClick(server_disconnect, listener(app, i_OnClick_server_disconnect, App));
      menuitem_OnClick(server_properties, listener(app, i_OnClick_server_properties, App));
      menuitem_OnClick(server_changeuser, listener(app, i_OnClick_server_changeuser, App));
      menuitem_OnClick(server_changepassword, listener(app, i_OnClick_server_changepassword, App));

    /* drop down menu items for Document */
    submenu_document = menu_create();
    osapp_menubar(submenu_document, app->window);
      document_add = menuitem_create(); menuitem_enabled(document_add, 1); menuitem_visible(document_add, 1);
      document_remove = menuitem_create(); menuitem_enabled(document_remove, 1); menuitem_visible(document_remove, 1);
      document_hide_unhide = menuitem_create(); menuitem_enabled(document_hide_unhide, 1); menuitem_visible(document_hide_unhide, 1);

      menuitem_text(document_add,         "Add ...                         ");
      menuitem_text(document_remove,      "Remove                          ");
      menuitem_text(document_hide_unhide, "Hide/ Unhide all dock widgets   ");

      menu_add_item(submenu_document, document_add);
      menu_add_item(submenu_document, document_remove);
      menu_add_item(submenu_document, document_hide_unhide);

      menuitem_submenu(document, &submenu_document);

      menuitem_OnClick(document_add, listener(app, i_OnClick_document_add, App));
      menuitem_OnClick(document_remove, listener(app, i_OnClick_document_remove, App));
      menuitem_OnClick(document_hide_unhide, listener(app, i_OnClick_document_hide_unhide, App));

    /* drop down menu items for Settings */
    submenu_settings = menu_create();
    osapp_menubar(submenu_settings, app->window);
      settings_plugins = menuitem_create(); menuitem_enabled(settings_plugins, 1); menuitem_visible(settings_plugins, 1);
      settings_configure = menuitem_create(); menuitem_enabled(settings_configure, 1); menuitem_visible(settings_configure, 1);
      settings_separator = menuitem_separator();
      settings_managecertificates = menuitem_create(); menuitem_enabled(settings_managecertificates, 1); menuitem_visible(settings_managecertificates, 1);

      menuitem_text(settings_plugins,   "Plugins...                ");
      menuitem_text(settings_configure, "Configure ...     ");
      menuitem_text(settings_managecertificates, "Manage Certificates    ");

      menu_add_item(submenu_settings, settings_plugins);
      menu_add_item(submenu_settings, settings_configure);
      menu_add_item(submenu_settings, settings_separator);
      menu_add_item(submenu_settings, settings_managecertificates);

      menuitem_submenu(settings, &submenu_settings);

      /* ----------submenu for Settings->Configure */
      /* here we create a submenu consists of 4 menu items */
      submenu_settings_configure = menu_create();
      osapp_menubar(submenu_settings_configure, app->window);
      configure_OPCSvr = menuitem_create(); menuitem_enabled(configure_OPCSvr, 1); menuitem_visible(configure_OPCSvr, 1);
      configure_LDS = menuitem_create(); menuitem_enabled(configure_LDS, 1); menuitem_visible(configure_LDS, 1);
      configure_GDS = menuitem_create(); menuitem_enabled(configure_GDS, 1); menuitem_visible(configure_GDS, 1);
      configure_MSB = menuitem_create(); menuitem_enabled(configure_MSB, 1); menuitem_visible(configure_MSB, 1);

      menuitem_text(configure_OPCSvr, "OPC UA Server");
      menuitem_text(configure_LDS, "Local Directory Server");
      menuitem_text(configure_GDS, "Global Directory Server");
      menuitem_text(configure_MSB, "Message Broker");

      menu_add_item(submenu_settings_configure, configure_OPCSvr);
      menu_add_item(submenu_settings_configure, configure_LDS);
      menu_add_item(submenu_settings_configure, configure_GDS);
      menu_add_item(submenu_settings_configure, configure_MSB);

      menuitem_submenu(settings_configure, &submenu_settings_configure);

      menuitem_OnClick(settings_plugins, listener(app, i_OnClick_settings_plugins, App));
      menuitem_OnClick(configure_OPCSvr, listener(app, i_OnClick_settings_configure_OPCSvr, App));
      menuitem_OnClick(configure_LDS, listener(app, i_OnClick_settings_configure_LDS, App));
      menuitem_OnClick(configure_GDS, listener(app, i_OnClick_settings_configure_GDS, App));
      menuitem_OnClick(configure_MSB, listener(app, i_OnClick_settings_configure_message_broker, App));
      menuitem_OnClick(settings_managecertificates, listener(app, i_OnClick_settings_managecertificates, App));


    /* drop down menu items for Help */
    submenu_help = menu_create();
    osapp_menubar(submenu_help, app->window);
      help_manual = menuitem_create(); menuitem_enabled(help_manual, 1); menuitem_visible(help_manual, 1);
      help_whatsthis = menuitem_create(); menuitem_enabled(help_whatsthis, 1); menuitem_visible(help_whatsthis, 1);
      help_licensestatus = menuitem_create(); menuitem_enabled(help_licensestatus, 1); menuitem_visible(help_licensestatus, 1);
      help_checkforupdates = menuitem_create(); menuitem_enabled(help_checkforupdates, 1); menuitem_visible(help_checkforupdates, 1);
      help_separator = menuitem_separator();
      help_about = menuitem_create(); menuitem_enabled(help_about, 1); menuitem_visible(help_about, 1);

      menuitem_text(help_manual,          "Manual                ");
      menuitem_text(help_whatsthis,       "What's This?          ");
      menuitem_text(help_licensestatus,   "License Status...     ");
      menuitem_text(help_checkforupdates, "Check for Updates...  ");
      menuitem_text(help_about,           "About                 ");

      menu_add_item(submenu_help, help_manual);
      menu_add_item(submenu_help, help_whatsthis);
      menu_add_item(submenu_help, help_licensestatus);
      menu_add_item(submenu_help, help_checkforupdates);
      menu_add_item(submenu_help, help_separator);
      menu_add_item(submenu_help, help_about);

      menuitem_submenu(help, &submenu_help);

      menuitem_OnClick(help_manual, listener(app, i_OnClick_help_manual, App));
      menuitem_OnClick(help_whatsthis, listener(app, i_OnClick_help_whatsthis, App));
      menuitem_OnClick(help_licensestatus, listener(app, i_OnClick_help_licensestatus, App));
      menuitem_OnClick(help_checkforupdates, listener(app, i_OnClick_help_checkforupdates, App));
      menuitem_OnClick(help_about, listener(app, i_OnClick_help_about, App));

}
#endif

/*---------------------------------------------------------------------------------------------------------------------*/
/* static Panel *i_panel() - instantiates the components of the window */
/*---------------------------------------------------------------------------------------------------------------------*/

static Panel *i_panel(App *app)			/* just change the name to i_panel_new to switch to original panel */
{
    Layout *baseLayout = layout_create(1,2); 	/* 1 col 2 rows */
    Layout *topLayout = layout_create(1,1);     /* topLayout consists of buttons */
    Layout *bottomLayout = layout_create(1,1);	/* bottomLayout consists of SpitView */
    Layout *buttonLayout = layout_create(30,1); /* buttonLayout consists of buttons */
   Button *buttonOpen, *buttonSave, *buttonSaveAs, *buttonClose;

    SplitView *mySplitView = splitview_horizontal();		/* Topside of SplitView consists of canvasLayout */
						/* Bottomside of SplitView consists of statusLayout */
    TextView *text = textview_create();
    Panel *panel = panel_create();		/* base level panel i.e. app->window -> panel */
    Panel *panel_split = panel_create();

     layout_layout(baseLayout,topLayout, 0,0);		/* put topLayout into baseLayout */
	layout_layout(topLayout, buttonLayout, 0,0);	/* put buttonLayout in topLayout */

     layout_layout(baseLayout,bottomLayout, 0,1);	/* put bottomLayout into baseLayout */
	layout_splitview(bottomLayout, mySplitView, 0,0); /* put splitview into bottomLayout */
	splitview_panel(mySplitView, panel_split);	/* put a panel_split into splitview */
     	//splitview_text(mySplitView, text, 0);		/* put a textview into splitview */


    /* ----------------initialise the objects */
    buttonOpen = button_push(); button_OnClick(buttonOpen, listener(app, i_OnClick_file_open, App));
    buttonSave = button_push(); button_OnClick(buttonSave, listener(app, i_OnClick_file_save, App));
    buttonSaveAs = button_push(); button_OnClick(buttonSaveAs, listener(app, i_OnClick_file_saveAs, App));
    buttonClose = button_push(); button_OnClick(buttonClose, listener(app, i_OnClick_file_close, App));

      /*-------button section */
        /* update the label on the button */
        button_text(buttonOpen, "Open");
        button_text(buttonSave, "Save");
        button_text(buttonSaveAs, "SaveAs");
        button_text(buttonClose, "Close");
        /* attach buttons to buttonLayout */
        layout_button(buttonLayout, buttonOpen, 0, 0);
        layout_button(buttonLayout, buttonSave, 1,0);
        layout_button(buttonLayout, buttonSaveAs, 2,0);
        layout_button(buttonLayout, buttonClose, 3,0);


    return panel;
}

static Panel *i_panel_original(App *app)
{
    Panel *imaginaryLeftPanel, *imaginaryTopPanel, *imaginaryRightPanel, *imaginaryBottomPanel;
    Panel *panel = panel_create();
    Layout *baseLayout = layout_create(1, 3); /* col, row */
    Layout *buttonLayout = layout_create(30,1);

    Layout *canvasLayout = layout_create(1,1);
    Layout *statusLayout = layout_create(1,1);
    Button *buttonOpen, *buttonSave, *buttonSaveAs, *buttonClose;
    TextView *text = textview_create();
    Layout *imaginaryLayoutLeftRight, *imaginaryLayoutTopBottom;
    color_t imaginaryColorLeftRight = color_rgb(88,4,47);
    color_t imaginaryColorTopBottom = color_rgb(50,130,246);
    S2Df imaginary_leftright_struct, imaginary_topbottom_struct;
    S2Df canvasSize;

/*TODO*/
    View *canvasView = view_custom(0,1);	/* scroll, border */

    /* ----------------initialise the objects */
    buttonOpen = button_push(); button_OnClick(buttonOpen, listener(app, i_OnClick_file_open, App));
    buttonSave = button_push(); button_OnClick(buttonSave, listener(app, i_OnClick_file_save, App));
    buttonSaveAs = button_push(); button_OnClick(buttonSaveAs, listener(app, i_OnClick_file_saveAs, App));
    buttonClose = button_push(); button_OnClick(buttonClose, listener(app, i_OnClick_file_close, App));

    /* ----- set the size of the baseLayout */
    layout_hsize(baseLayout, 0, 1680); /* set the width of row 0 */
    layout_vsize(baseLayout, 1, 900); /* set the height of row 1 */
    layout_vsize(baseLayout, 2, 400); /* set the height of row 2 */
    layout_margin(baseLayout, 5);
    layout_vmargin(baseLayout, 0, 5);
    layout_vmargin(baseLayout, 1, 5);

    /* ----- create 3 sublayouts within the base layout */
    layout_layout(baseLayout, buttonLayout, 0,0);
    layout_layout(baseLayout, canvasLayout, 0,1);
    layout_layout(baseLayout, statusLayout, 0,2);

      /*-------button section */
        /* update the label on the button */
        button_text(buttonOpen, "Open");
        button_text(buttonSave, "Save");
        button_text(buttonSaveAs, "SaveAs");
        button_text(buttonClose, "Close");
        /* attach buttons to buttonLayout */
        layout_button(buttonLayout, buttonOpen, 0, 0);
        layout_button(buttonLayout, buttonSave, 1,0);
        layout_button(buttonLayout, buttonSaveAs, 2,0);
        layout_button(buttonLayout, buttonClose, 3,0);

    /* ----- canvas section */
    /* attach a secondary view object to canvasLayout */
    layout_view(canvasLayout, canvasView, 0,0);
    layout_vsize(canvasLayout, 0, 600);
    view_get_size(canvasView, &canvasSize);

    /* ------ status section */
    /* attach textview control to baseLayout */
    layout_textview(statusLayout, text, 0, 0);
    layout_vsize(statusLayout, 0, 400);

    /* ---- keep a copy in app */
    app->buttonLayout = buttonLayout;
    app->canvasLayout = canvasLayout;
    app->statusLayout = statusLayout;

  /*      layout_vsize(statusLayout, 0, 200);  caused the menu text to disappear */

    /* create 4 imaginery windows */
    /* this is used when view_project windows crosses the boundaries of app->window */
#ifdef wrong /* cause the program to crash */
    imaginary_leftright_struct.width = app->sys_resolution.x / 4 ; /*canvasSize.width / 4; /* app->sys_resolution.x / 4; */
    imaginary_leftright_struct.height = app->sys_resolution.y; /* app->sys_resolution.y; /* canvasSize.height; 	/* app->sys_resolution.y; */
    imaginary_topbottom_struct.width =  app->sys_resolution.x; /*app->sys_resolution.x; /*canvasSize.width; /* app->sys_resolution.x; */
    imaginary_topbottom_struct.height = app->sys_resolution.y / 2; /* app->sys_resolution.y / 4; /*canvasSize.height / 4; */

    /*textview_printf(app->text, "imaginary sizes = AAA\n");*/ /* app->sys_resolution.x /4,
								   app->sys_resolution.y,
								   app->sys_resolution.x,
								   app->sys_resolution.y /4);*/
    textview_scroll_caret(app->text);

#endif

    imaginaryLayoutLeftRight = layout_create(1,1);	/* col, row */
    layout_bgcolor(imaginaryLayoutLeftRight, imaginaryColorLeftRight);
    imaginaryLayoutTopBottom = layout_create(1,1);      /* col, row */
    layout_bgcolor(imaginaryLayoutTopBottom, imaginaryColorTopBottom);


#ifdef WRONG /* this cause core dump */
    textview_printf(app->text, "I am here \n");
    textview_scroll_caret(app->text);

/*
	textview_printf(app->text, "leftright : width, height, topbottom : width, height %f %f %f %f \n",
		imaginary_leftright_struct.width, imaginary_leftright_struct.height, imaginary_topbottom_struct.width, imaginary_topbottom_struct.height);
*/
#endif

#ifndef WRONG
    /* create imaginary panels and associate with the common imaginaryLayout */
    imaginaryLeftPanel = panel_create();
    panel_size(imaginaryLeftPanel, imaginary_leftright_struct);
    panel_layout(imaginaryLeftPanel, imaginaryLayoutLeftRight);

    imaginaryTopPanel = panel_create();
    panel_size(imaginaryTopPanel, imaginary_topbottom_struct);
    panel_layout(imaginaryTopPanel, imaginaryLayoutTopBottom);

    imaginaryRightPanel = panel_create();
    panel_size(imaginaryRightPanel, imaginary_leftright_struct);
    panel_layout(imaginaryRightPanel, imaginaryLayoutLeftRight);

    imaginaryBottomPanel = panel_create();
    panel_size(imaginaryBottomPanel, imaginary_topbottom_struct);
    panel_layout(imaginaryBottomPanel, imaginaryLayoutTopBottom);

    /* create the imaginary windows with the panel attached */
    app->imaginaryLeftWindow = window_create(ekWINDOW_EDGE);
    window_panel(app->imaginaryLeftWindow, imaginaryLeftPanel);

    app->imaginaryTopWindow = window_create(ekWINDOW_EDGE);
    window_panel(app->imaginaryTopWindow, imaginaryTopPanel);

    app->imaginaryRightWindow = window_create(ekWINDOW_EDGE);
    window_panel(app->imaginaryRightWindow, imaginaryRightPanel);

    app->imaginaryBottomWindow = window_create(ekWINDOW_EDGE);
    window_panel(app->imaginaryBottomWindow, imaginaryBottomPanel);


    /* set the size of the imaginary windows */
    imaginary_leftright_struct.width = window_get_size(app->window).width / 4;
    imaginary_leftright_struct.height = window_get_size(app->window).height; /* to review the formulae */
    imaginary_topbottom_struct.width =  window_get_size(app->window).width;
    imaginary_topbottom_struct.height = window_get_size(app->window).height / 2; /* to review the formulae */

    window_client_size(app->imaginaryLeftWindow, imaginary_leftright_struct );
    window_client_size(app->imaginaryTopWindow, imaginary_topbottom_struct );
    window_client_size(app->imaginaryRightWindow, imaginary_leftright_struct );
    window_client_size(app->imaginaryBottomWindow, imaginary_topbottom_struct );

    /* moves the imaginery window into position */
    window_origin(app->imaginaryLeftWindow, app->screen_coordinate);
#endif


    panel_layout(panel, baseLayout);
    app->text = text;
    return panel;
}

static App *i_create(void)
{
    App *app = heap_new0(App);
    Panel *panel;

    app->nofilename = 1;	/* at initial launch, there is no filename indicated */
    app->window = window_create(ekWINDOW_EDGE | ekWINDOW_TITLE | ekWINDOW_MAX | ekWINDOW_MIN | ekWINDOW_CLOSE | ekWINDOW_RESIZE);
    window_title(app->window, "open62541 OPC UA demonstration");
    window_origin(app->window, v2df(500, 200)); 	/* move window to position */


#ifndef WRONG
    panel = i_panel(app);	/* function to create a panel */
    window_panel(app->window, panel); /* create a panel and attach to app->window */
#endif

    /* get the size of the main window i.e. resolution */
#ifndef WRONG
/*ok*/
    app->sys_resolution.x = window_get_size(app->window).width;
    app->sys_resolution.y = window_get_size(app->window).height;
    //app->screen_coordinate.x = window_get_origin(app->window).x;
    //app->screen_coordinate.y = window_get_origin(app->window).y;
    textview_printf(app->text, "app->window size : width %f height %f \n", app->sys_resolution.x, app->sys_resolution.y);
    textview_scroll_caret(app->text);
#endif

    window_show(app->window);

#ifndef WRONG
/*ok*/
    createMenus(app);
#endif
    /*not required to be called upfront, but the individual createXXXWindow() will be invoked when a callback is invoked via the menu */
    /*createSubWindows(app->window); */

    /* on startup, launch all the View windows, then enable the ticks on the menuitem using createmenus()  Reason see below */
#ifndef WRONG
    ViewProject(app, app->window);
    ViewAddressSpace(app, app->window);
    ViewLog(app, app->window);
    ViewAttributes(app, app->window);
    ViewReferences(app, app->window);
#endif

    window_OnClose(app->window, listener(app, i_OnClose, App));
    window_OnMoved(app->window, listener(app, i_OnMoved_AppWindow, App));
    window_OnResize(app->window, listener(app, i_OnResize_AppWindow, App));

    #ifndef WRONG
    window_show(app->imaginaryLeftWindow);
    window_show(app->imaginaryTopWindow);
    window_show(app->imaginaryRightWindow);
    window_show(app->imaginaryBottomWindow);
    #endif

/* if the following are activated, the menu bar text all gone missing, so have to do it in createmenus() */
/*
menuitem_state(app->view_project, ekGUI_ON);
menuitem_state(app->view_addressspace, ekGUI_ON);
menuitem_state(app->view_log, ekGUI_ON);
menuitem_state(app->view_attributes, ekGUI_ON);
menuitem_state(app->view_references, ekGUI_ON);
*/


    return app;
}


/*---------------------------------------------------------------------------*/

static void i_destroy(App **app)
{
    /* destroy the menu */
    if ((*app)->top_menu != NULL)
    {
	/* the following caused segmentation fault */
    	/* menu_destroy(&(*app)->top_menu); */
	/* do nothing it will have memory leak */
    }

    if ((*app)->window != NULL)
	    window_destroy(&(*app)->window);
    heap_delete(app, App);
}

/*---------------------------------------------------------------------------*/
#ifdef REMOVE
osmain(i_create, i_destroy, "", App)
#endif

