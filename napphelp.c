#include <nappgui.h>
#include <osapp/osmain.h>
#include <stdio.h>
#include <string.h>
#include "napp.h"

void i_OnClick_webview_WindowClose(App *app, Event *e)
{

	window_destroy(&app->PopupBrowserCompany);
	app->PopupBrowserCompany = NULL;
	unref(e);
}

static void i_OnClick_CompanyName(App *app, Event *e)
{
	WebView *web = webview_create();
	Panel *panel;
	Layout *layout;
	Window *window;
	S2Df panel_dim;
	char url[255];

#ifndef SKIP // this works
	osapp_open_url("https://www.maxmachinestech.com");
#else	// this does not work - incomplete rendering
	panel = panel_create();
        layout = layout_create(1,1);

	panel_dim.width = 800;
	panel_dim.height = 600;
	panel_size(panel,  panel_dim);

	if (app->PopupBrowserCompany == NULL)
	{
		window = window_create(ekWINDOW_EDGE | ekWINDOW_TITLE | ekWINDOW_MAX | ekWINDOW_MIN | ekWINDOW_CLOSE | ekWINDOW_RESIZE);
		app->PopupBrowserCompany = window;
		window_OnClose(window, listener(app, i_OnClick_webview_WindowClose, App));

		/*window_client_size(window, panel_dim); // not such api */
		window_title(window, "www.MaxMachinesTech.com");
		strcpy(url, "https://www.maxmachinestech.com/");
/*
		strcpy(url, "https://www.google.com/");
*/
		url[strlen(url)] = '\0';
		webview_navigate(web, url);

		/* the order is important */
		layout_webview(layout, web, 0,0);	/* put the webview in the layout */
		panel_layout(panel, layout);	/* put the layout in the panel */
		window_panel(window, panel);	/* put the panel in the window */
		moveToCentre(window, app);
		window_show(window);
	}

#endif

}

void helpAbout(App *app, Window *parent_window)
{
    Window *modalClient;
    V2Df origin;
    float window_x, window_y;
    Panel *panel;
    ferror_t error= ekFOK;
    ModalData *data;
    Layout *MainLayout, *BannerLayout, *TextLayout, *DecisionLayout;
    Label *label_companyName, *label_email, *label_copyright, *label_trademark, *label_trademark2, *label_trademark3, *label_rightsReserved;
    Font *minifont;
    ImageView *CompanyBannerImageView;
    Image *CompanyBannerImage;


    Button *pushOK;
    uint32_t i;

    textview_printf(app->text, "Filename is %s, nofilename is %d \n", app->savedFile, app->nofilename);
    textview_scroll_caret(app->text);

    /* creates a modal window */
    modalClient = window_create(ekWINDOW_EDGE | ekWINDOW_TITLE | ekWINDOW_CLOSE);
    window_title(modalClient, "About us");
    /*ModalData *data = i_modal_data(parent_window);*/
    data = heap_new(ModalData);
    data->parent = parent_window;
    data->type = UINT32_MAX;

    panel = panel_create();

    MainLayout = layout_create(5,3); /* col, row */
    BannerLayout = layout_create(1,1);
    TextLayout = layout_create(1,8);
    DecisionLayout = layout_create(5, 1);

    CompanyBannerImageView = imageview_create();
    CompanyBannerImage = image_from_file("/home/pi/nappgui_src/jacky/img/maxmachines-banner-4.png", &error);
    imageview_image(CompanyBannerImageView, CompanyBannerImage);
    layout_imageview(BannerLayout, CompanyBannerImageView, 0,0);



    label_companyName = label_create();
    label_email = label_create();
    label_copyright = label_create();
    label_trademark = label_create();
    label_trademark2 = label_create();
    label_trademark3 = label_create();
    label_rightsReserved = label_create();
    //minifont = font_create("Times New Roman", 10.0, ekFBOLD);
    minifont = font_system(10.0, ekFBOLD);

    label_text(label_companyName, "MaxMachines Technology Pte Ltd");
    label_text(label_email, "enquiries@maxmachinestech.com");
    label_text(label_copyright, "copyright(c)MaxMachines Technology Pte Ltd"); label_font(label_copyright, minifont);
    label_text(label_trademark, "maxEngine(tm), maxCore(tm), maxAdapter(tm), maxIntegrator(tm), maxScale(tm), maxGate(tm) "); label_font(label_trademark, minifont);
    label_text(label_trademark2, "maxMind(tm), maxLicense(tm), maxManager(tm), maxOrchestrator(tm), maxDiscovery(tm) "); label_font(label_trademark2, minifont);
    label_text(label_trademark3, "maxGenerate(tm), maxNodes(tm) "); label_font(label_trademark2, minifont);label_font(label_trademark3, minifont);
    label_text(label_rightsReserved, "All rights reserved"); label_font(label_rightsReserved, minifont);

    pushOK = button_push(); button_text(pushOK, "OK");button_OnClick(pushOK, listener(app, i_OnClick_ButtonCancel, App));
    //pushCancel = button_push(); button_text(pushCancel, "Cancel"); button_OnClick(pushCancel, listener(app, i_OnClick_ButtonCancel, App));

    /* assigns the layout to the panel */
    panel_layout(panel, MainLayout);
    layout_layout(MainLayout, BannerLayout, 0,0);
    layout_layout(MainLayout, TextLayout, 0,1);
    layout_layout(MainLayout, DecisionLayout, 0,2);

    /* sets up margins and col width and row height */
    /* Section 1 : col = 1, row = 1 */
    layout_hsize(TextLayout, 0, 500);
    layout_hmargin(TextLayout,0,5);
        layout_halign(TextLayout, 0,0, ekLEFT);
        layout_vmargin(TextLayout, 0, 0);
    layout_margin(TextLayout, 10); /* sets a fix margin around the border */

    // launch a web browser and bring user to company website
    label_style_over(label_companyName, ekFUNDERLINE);
    label_OnClick(label_companyName, listener(app, i_OnClick_CompanyName, App));

    /* Section 2 : col = 5, row = 1 */
    for(i=0; i<5; i++)
        layout_hsize(DecisionLayout, i, 10); /* set a fix width of all columns */

    layout_vmargin(DecisionLayout, 0, 2);

    /* assigns the interface objects i.e. label, edit, ... to the layout in X(col),Y(row) coordinate, starts with index 0 */
    /* Section 1 : col = 1, row = 1 */
    layout_label(TextLayout, label_companyName, 0,0);
    layout_label(TextLayout, label_email, 0, 1);
    layout_label(TextLayout, label_copyright, 0, 2);
    layout_label(TextLayout, label_trademark, 0, 3);
    layout_label(TextLayout, label_trademark2, 0, 4);
    layout_label(TextLayout, label_trademark3, 0, 5);
    layout_label(TextLayout, label_rightsReserved, 0, 6);

    /* Section 2 : col = 5, row = 1 */
    layout_button(DecisionLayout, pushOK, 2,0);
    //layout_button(DecisionLayout, pushCancel, 3,0);

    /* assigns the panel to the window and saves the handle to app */
    panel_data(panel, &data, i_destroy_modal_data, ModalData);

    app->modalWindow = modalClient;
    window_panel(modalClient, panel);

    /* sets the default button to Cancel */
    window_defbutton(modalClient, pushOK);


    /* handle to target window to align centre to app->window centre */
    window_x = window_get_size(modalClient).width;
    window_y = window_get_size(modalClient).height;

textview_printf(app->textMaxManage, "Help->About (size_x : %f, size_y : %f)\n", window_x, window_y);
printf("Help->About (window size_x : %f, window size_y : %f)\n", window_x, window_y);



    /* move the dialog window to the centre of the screen */
    origin.x = app->sys_resolution.x / 2 - window_x / 2 ;
    origin.y = app->sys_resolution.y / 2 - window_y / 2 ;
    window_origin(modalClient, origin );

textview_printf(app->text, "Help->About (origin.x = %f, origin.y = %f\n", origin.x, origin.y);
printf("Help->About (origin.x = %f, origin.y = %f\n", origin.x, origin.y);

    //moveToCentre(modalClient, app);
    window_modal(modalClient, parent_window);



    if (data != NULL)
        heap_delete(&data, ModalData);
    window_destroy(&app->modalWindow);
}
