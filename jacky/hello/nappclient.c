#include <nappgui.h>
#include <osapp/osmain.h>
#include <stdio.h>
#include <string.h>
#include "napp.h"

Layout *MainLayout, *GenLayout, *AuthLayout, *DecisionLayout;
Edit *edit_username, *edit_password;
Edit *edit_certificate, *edit_privatekey;
Button *pushCertificate, *pushPrivateKey;
Button *radio_anonymous, *radio_username_password, *radio_certificate_key;
Button *check_store;

void CertificateOpen(App *app, Window *parent_window)
{
        const char_t *selected_file;
        const char_t *filetypeslist[] = {"pem","der"};
        const uint32_t size=2;

        //selected_file = comwin_open_file(parent_window, filetypeslist, size, NULL);
        selected_file = comwin_open_file(parent_window,
                                        "caption",
                                        filetypeslist,
                                        size, NULL, NULL);
        /* keep the filename in app so that when i click Save, it will update the contents without asking for the filename */
        if (selected_file == NULL) /* user aborted the dialog */
                app->nocertificate = 1;
        else
        {
                app->nocertificate = 0;
                app->certificate = selected_file;
		edit_text(edit_certificate, selected_file);	/* update the editbox with the selected file */

        }
        /* for debugging purposes, show it in the text widget */
        textview_printf(app->text, "Filename is (%s), nofilename = %d \n", app->certificate, app->nocertificate);
        textview_scroll_caret(app->text);

        if (app->certificate != NULL) /* prevents an empty filename */
        {
                app->fp_certificate = fopen(app->certificate, "r");
                if (app->fp_certificate)
                {
                        /* read in the contents */
                        /* fread(.....); */
                        app->nocertificate = 0;
                        fclose(app->fp_certificate);
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

void PrivateKeyOpen(App *app, Window *parent_window)
{
        const char_t *selected_file;
        const char_t *filetypeslist[] = {"pem","der"};
        const uint32_t size=2;

        //selected_file = comwin_open_file(parent_window, filetypeslist, size, NULL);
        selected_file = comwin_open_file(parent_window,
					"caption",
					filetypeslist,
					size, NULL, NULL);
        /* keep the filename in app so that when i click Save, it will update the contents without asking for the filename */
        if (selected_file == NULL) /* user aborted the dialog */
                app->noprivatekey = 1;
        else
        {
                app->noprivatekey = 0;
                app->privatekey = selected_file;
		edit_text(edit_privatekey, selected_file);
        }
        /* for debugging purposes, show it in the text widget */
        textview_printf(app->text, "Filename is (%s), nofilename = %d \n", app->privatekey, app->noprivatekey);
        textview_scroll_caret(app->text);

        if (app->privatekey != NULL) /* prevents an empty filename */
        {
                app->fp_privatekey = fopen(app->privatekey, "r");
                if (app->fp_privatekey)
                {
                        /* read in the contents */
                        /* fread(.....); */
                        app->noprivatekey = 0;
                        fclose(app->fp_privatekey);
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

void i_OnClick_ButtonCancel(App *app, Event *e)
{
    textview_printf(app->text, "Button <Cancel> click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);

    window_stop_modal(app->modalWindow, 300);   /* 300 - value to be returned */
    unref(e);
}

void i_OnClick_ButtonCertificate(App *app, Event *e)
{
    textview_printf(app->text, "Certificate->Load click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    CertificateOpen(app, app->window);
    unref(e);
}

void i_OnClick_ButtonPrivateKey(App *app, Event *e)
{
    textview_printf(app->text, "PrivateKey->Load click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    PrivateKeyOpen(app, app->window);
    unref(e);
}

void i_OnClick_radioAnonymous(App *app, Event *e)
{
    /* disable the edit fields */
    cell_enabled(layout_cell(AuthLayout,2,1), FALSE);
    cell_enabled(layout_cell(AuthLayout,2,3), FALSE);
    cell_enabled(layout_cell(AuthLayout,2,4), FALSE);
    cell_enabled(layout_cell(AuthLayout,2,6), FALSE);
    /* disable the buttons */
    cell_enabled(layout_cell(AuthLayout,3,4), FALSE);
    cell_enabled(layout_cell(AuthLayout,3,6), FALSE);

    textview_printf(app->text, "radiobutton Anonymous->click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    edit_editable(edit_username, FALSE);
    edit_editable(edit_password, FALSE);
    edit_editable(edit_certificate, FALSE);
    edit_editable(edit_privatekey, FALSE);

    edit_color(edit_username, color_gray(1));
    edit_color(edit_password, color_gray(1));
    edit_color(edit_certificate, color_gray(1));
    edit_color(edit_privatekey, color_gray(1));

    button_state(check_store, ekGUI_OFF);
    /*button_state(pushCertificate, ekGUI_OFF); */
    /*button_state(pushPrivateKey, ekGUI_OFF); */

    unref(e);
}

void i_OnClick_radioUsernamePassword(App *app, Event *e)
{
    /* disable the edit fields */
    cell_enabled(layout_cell(AuthLayout,2,1), TRUE);
    cell_enabled(layout_cell(AuthLayout,2,3), TRUE);
    cell_enabled(layout_cell(AuthLayout,2,4), FALSE);
    cell_enabled(layout_cell(AuthLayout,2,6), FALSE);
    /* disable the buttons */
    cell_enabled(layout_cell(AuthLayout,3,4), FALSE);
    cell_enabled(layout_cell(AuthLayout,3,6), FALSE);

    textview_printf(app->text, "radiobutton Username/password->click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    edit_editable(edit_username, TRUE);
    edit_editable(edit_password, TRUE);
    edit_editable(edit_certificate, FALSE);
    edit_editable(edit_privatekey, FALSE);

    edit_color(edit_username, kCOLOR_DEFAULT);
    edit_color(edit_password, kCOLOR_DEFAULT);
    edit_color(edit_certificate, color_gray(1));
    edit_color(edit_privatekey, color_gray(1));

    button_state(check_store, ekGUI_ON);
    /*button_state(pushCertificate, ekGUI_OFF);*/
    /*button_state(pushPrivateKey, ekGUI_OFF);*/

    unref(e);
}

void i_OnClick_radioCertificateKey(App *app, Event *e)
{
    /* disable the edit fields */
    cell_enabled(layout_cell(AuthLayout,2,1), FALSE);
    cell_enabled(layout_cell(AuthLayout,2,3), FALSE);
    cell_enabled(layout_cell(AuthLayout,2,4), TRUE);
    cell_enabled(layout_cell(AuthLayout,2,6), TRUE);
    /* disable the buttons */
    cell_enabled(layout_cell(AuthLayout,3,4), TRUE);
    cell_enabled(layout_cell(AuthLayout,3,6), TRUE);

    textview_printf(app->text, "radiobutton Certificate/key->click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    edit_editable(edit_username, FALSE);
    edit_editable(edit_password, FALSE);
    edit_editable(edit_certificate, TRUE);
    edit_editable(edit_privatekey, TRUE);

    edit_color(edit_username, color_gray(1));
    edit_color(edit_password, color_gray(1));
    edit_color(edit_certificate, kCOLOR_DEFAULT);
    edit_color(edit_privatekey, kCOLOR_DEFAULT);

    button_state(check_store, ekGUI_OFF);
    button_state(pushCertificate, ekGUI_ON);
    button_state(pushPrivateKey, ekGUI_ON);

    unref(e);
}

void i_destroy_modal_data(ModalData** data)
{
   heap_delete(data, ModalData);
}

void moveToCentre(Window *window, App *app)
{
        V2Df origin;

        float window_x, window_y;
        /* handle to target window to align centre to app->window centre */
	/* force the base application window to maximize so as to get the correct coordinates */

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

void ClientAdd(App *app, Window *parent_window)
{
    Window *modalClient;
    uint32_t i, j;
    /*Panel *GenPanel, *AuthPanel, *DecisionPanel;*/
    Panel *panel;
    ModalData *data;
    Label *label_configurationname, *label_pkistore, *label_endpointfilter, *label_anonymous, *label_username, *label_password, *label_certificate, *label_privatekey;
    Edit *edit_configurationname, *edit_pkistore, *edit_endpointfilter;
    /* Edit *edit_username, *edit_password; */

    /* Edit *edit_certificate, *edit_privatekey; */
    Button *pushOK, *pushCancel;
    /* Button *pushCertificate, *pushPrivateKey; */
    /* Button *radio_anonymous, *radio_username_password, *radio_certificate_key; */
    /* Button *check_store; */
    textview_printf(app->text, "Filename is %s, nofilename is %d \n", app->savedFile, app->nofilename);
    textview_scroll_caret(app->text);

    /* creates a modal window */
    modalClient = window_create(ekWINDOW_EDGE | ekWINDOW_TITLE | ekWINDOW_CLOSE);
    window_title(modalClient, "Add a new OPC Client");

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
    AuthLayout = layout_create(4, 7);
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

    radio_anonymous = button_radio(); button_text(radio_anonymous, "Anonymous"); button_state(radio_anonymous, ekGUI_ON); button_OnClick(radio_anonymous, listener(app, i_OnClick_radioAnonymous, App));
    radio_username_password = button_radio();  button_state(radio_username_password, ekGUI_OFF); button_OnClick(radio_username_password, listener(app, i_OnClick_radioUsernamePassword, App)); /*button_text(radio_username, "Username");*/
    radio_certificate_key = button_radio(); button_state(radio_certificate_key, ekGUI_OFF); button_OnClick(radio_certificate_key, listener(app, i_OnClick_radioCertificateKey, App)); /*button_text(radio_certificate, "Certificate");*/

    edit_username = edit_create(); edit_width(edit_username, 300); edit_editable(edit_username, FALSE);
    edit_password = edit_create(); edit_width(edit_password, 300); edit_editable(edit_password, FALSE); edit_passmode(edit_password, TRUE);
    edit_certificate = edit_create(); edit_width(edit_certificate, 300); edit_editable(edit_certificate, FALSE);
    edit_privatekey = edit_create(); edit_width(edit_privatekey, 300); edit_editable(edit_privatekey, FALSE);

    pushCertificate = button_push(); button_text(pushCertificate, "..."); button_state(pushCertificate, ekGUI_OFF); button_OnClick(pushCertificate, listener(app, i_OnClick_ButtonCertificate, App));
    pushPrivateKey = button_push(); button_text(pushPrivateKey, "..."); button_state(pushPrivateKey, ekGUI_OFF); button_OnClick(pushPrivateKey, listener(app, i_OnClick_ButtonPrivateKey, App));
    pushOK = button_push(); button_text(pushOK, "  OK  ");
    pushCancel = button_push(); button_text(pushCancel, "Cancel"); button_OnClick(pushCancel, listener(app, i_OnClick_ButtonCancel, App));

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

    /* Section 2 : col = 4, row = 7 */
    layout_hsize(AuthLayout, 0, 20); /* set a fix width of column 0 (radio buttons)*/
    layout_hsize(AuthLayout, 1, 240); /* sets a fix width of column 1 (labels) */
    layout_hsize(AuthLayout, 2, 400); /* fixed width of column 2 (edit)*/
    layout_hsize(AuthLayout, 3, 100); /* checkbox */
    layout_hmargin(AuthLayout,0,5);
    for (i=0; i<4; i++) {
      for (j=0; j<7; j++) {
        layout_halign(AuthLayout, i,j, ekLEFT);
      }
    }
    layout_vsize(AuthLayout, 2, 1);	/* reduce the height of radio buttons */
    layout_vsize(AuthLayout, 5, 1);     /* reduce the height of radio buttons */
    for (i=0; i<3; i++)
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

    /* Section 2 : col = 4, row = 7 */
    layout_button(AuthLayout, radio_anonymous, 0,0);
    layout_label(AuthLayout, label_username, 1,1);
    layout_button(AuthLayout, radio_username_password, 0,2);
    layout_label(AuthLayout, label_password, 1,3);
    layout_label(AuthLayout, label_certificate, 1,4);
    layout_button(AuthLayout, radio_certificate_key, 0,5);
    layout_label(AuthLayout, label_privatekey, 1,6);

    layout_edit(AuthLayout, edit_username, 2,1);
    layout_edit(AuthLayout, edit_password, 2,3);
    layout_edit(AuthLayout, edit_certificate, 2,4);
    layout_edit(AuthLayout, edit_privatekey, 2,6);

    layout_button(AuthLayout, check_store, 3,1);
    layout_button(AuthLayout, pushCertificate, 3,4);
    layout_button(AuthLayout, pushPrivateKey, 3,6);

    /* Section 3 : col = 10, row = 1 */
    layout_button(DecisionLayout, pushOK, 8,0);
    layout_button(DecisionLayout, pushCancel, 9,0);

    /* assigns GenLayout, AuthLayout and DecisionLayout into MainLayout (2,3) */
    layout_layout(MainLayout, GenLayout, 0, 0);
    layout_layout(MainLayout, AuthLayout, 0,1);
    layout_layout(MainLayout, DecisionLayout, 0,2);

    /* disable the edit fields */
    cell_enabled(layout_cell(AuthLayout,2,1), FALSE);
    cell_enabled(layout_cell(AuthLayout,2,3), FALSE);
    cell_enabled(layout_cell(AuthLayout,2,4), FALSE);
    cell_enabled(layout_cell(AuthLayout,2,6), FALSE);
    /* disable the buttons pushCertificate and pushPrivateKey */
    cell_enabled(layout_cell(AuthLayout,3,4), FALSE);
    cell_enabled(layout_cell(AuthLayout,3,6), FALSE);

    /* assigns the layout to the panel */
    panel_layout(panel, MainLayout);
    /*
    panel_layout(AuthPanel, AuthLayout);
    panel_layout(DecisionPanel, DecisionLayout);*/

    panel_data(panel, &data, i_destroy_modal_data, ModalData);

    /* assigns the panel to the window and saves the handle to app */
    app->modalWindow = modalClient;
    window_panel(modalClient, panel);

    /* sets the default button to Cancel */
    window_defbutton(modalClient, pushCancel);

    /* centres the window */
    moveToCentre(modalClient, app);
    window_modal(modalClient, parent_window);

    if (data != NULL)
    	heap_delete(&data, ModalData);
    window_destroy(&app->modalWindow);
}

void ClientRemove(App *app, Window *parent_window)
{
    Window *modalClient;
    Panel *panel;
    ModalData *data;
    Layout *MainLayout, *TextLayout, *DecisionLayout;
    Label *label_question;
    Button *pushOK, *pushCancel;
    uint32_t i;

    textview_printf(app->text, "Filename is %s, nofilename is %d \n", app->savedFile, app->nofilename);
    textview_scroll_caret(app->text);

    /* creates a modal window */
    modalClient = window_create(ekWINDOW_EDGE | ekWINDOW_TITLE | ekWINDOW_CLOSE);
    window_title(modalClient, "Remove Client");

    /*ModalData *data = i_modal_data(parent_window);*/
    data = heap_new(ModalData);
    data->parent = parent_window;
    data->type = UINT32_MAX;

    panel = panel_create();

    MainLayout = layout_create(5,2); /* col, row */
    TextLayout = layout_create(1,1);
    DecisionLayout = layout_create(5, 1);

    label_question = label_create();
    label_text(label_question, "Do you really want to remove the Client ?");
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

    app->modalWindow = modalClient;
    window_panel(modalClient, panel);

    /* sets the default button to Cancel */
    window_defbutton(modalClient, pushCancel);

    moveToCentre(modalClient, app);
    window_modal(modalClient, parent_window);

    if (data != NULL)
    	heap_delete(&data, ModalData);
    window_destroy(&app->modalWindow);
}

void ClientConnect(App *app, Window *parent_window)
{
    Window *modalClient;
    /*uint32_t i, j;*/
    Panel *panel;
    ModalData *data;

    Layout *MainLayout, *DecisionLayout;
    Button *pushOK, *pushCancel;

    textview_printf(app->text, "Filename is %s, nofilename is %d \n", app->savedFile, app->nofilename);
    textview_scroll_caret(app->text);

    /* creates a modal window */
    modalClient = window_create(ekWINDOW_EDGE | ekWINDOW_TITLE | ekWINDOW_CLOSE);
    window_title(modalClient, "Connect Client");

    /*ModalData *data = i_modal_data(parent_window);*/
    data = heap_new(ModalData);
    data->parent = parent_window;
    data->type = UINT32_MAX;

    panel = panel_create();
    MainLayout = layout_create(1,3);

    DecisionLayout = layout_create(10, 1);
    pushOK = button_push(); button_text(pushOK, "  OK  ");
    pushCancel = button_push(); button_text(pushCancel, "Cancel"); button_OnClick(pushCancel, listener(app, i_OnClick_ButtonCancel, App));

    /* Section 2 : col = 5, row = 1 */
    layout_button(DecisionLayout, pushOK, 1,0);
    layout_button(DecisionLayout, pushCancel, 3,0);

    /* assigns GenLayout, AuthLayout and DecisionLayout into MainLayout (2,3) */
    layout_layout(MainLayout, DecisionLayout, 0,2);

    /* assigns the layout to the panel */
    panel_layout(panel, MainLayout);

    panel_data(panel, &data, i_destroy_modal_data, ModalData);

    app->modalWindow = modalClient;
    window_panel(modalClient, panel);

    /* sets the default button to Cancel */
    window_defbutton(modalClient, pushCancel);

    moveToCentre(modalClient, app);
    window_modal(modalClient, parent_window);

    if (data != NULL)
 	heap_delete(&data, ModalData);
    window_destroy(&app->modalWindow);

}

void ClientDisconnect(App *app, Window *parent_window)
{
    Window *modalClient;
    Panel *panel;
    ModalData *data;
    Layout *MainLayout, *TextLayout, *DecisionLayout;
    Label *label_question;
    Button *pushOK, *pushCancel;
    uint32_t i;

    textview_printf(app->text, "Filename is %s, nofilename is %d \n", app->savedFile, app->nofilename);
    textview_scroll_caret(app->text);

    /* creates a modal window */
    modalClient = window_create(ekWINDOW_EDGE | ekWINDOW_TITLE | ekWINDOW_CLOSE);
    window_title(modalClient, "Disconnet Client");
    /*ModalData *data = i_modal_data(parent_window);*/
    data = heap_new(ModalData);
    data->parent = parent_window;
    data->type = UINT32_MAX;

    panel = panel_create();

    MainLayout = layout_create(5,2); /* col, row */
    TextLayout = layout_create(1,1);
    DecisionLayout = layout_create(5, 1);

    label_question = label_create();
    label_text(label_question, "Do you really want to disconnect from the OPC Server ?");
    pushOK = button_push(); button_text(pushOK, "OK");
    pushCancel = button_push(); button_text(pushCancel, "Cancel"); button_OnClick(pushCancel, listener(app, i_OnClick_ButtonCancel, App));

    /* assigns the layout to the panel */
    panel_layout(panel, MainLayout);
    layout_layout(MainLayout, TextLayout, 0,0);
    layout_layout(MainLayout, DecisionLayout, 0,1);

    /* sets up margins and col width and row height */
    /* Section 1 : col = 1, row = 1 */
    layout_hsize(TextLayout, 0, 500);
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

    app->modalWindow = modalClient;
    window_panel(modalClient, panel);

    /* sets the default button to Cancel */
    window_defbutton(modalClient, pushCancel);

    moveToCentre(modalClient, app);
    window_modal(modalClient, parent_window);

    if (data != NULL)
	heap_delete(&data, ModalData);
    window_destroy(&app->modalWindow);
}

void ClientProperties(App *app, Window *parent_window)
{
    Window *modalClient;
    /*uint32_t i, j;*/
    Panel *panel;
    ModalData *data;

    Layout *MainLayout, *DecisionLayout;
    Button *pushOK, *pushCancel;

    textview_printf(app->text, "Filename is %s, nofilename is %d \n", app->savedFile, app->nofilename);
    textview_scroll_caret(app->text);

    /* creates a modal window */
    modalClient = window_create(ekWINDOW_EDGE | ekWINDOW_TITLE | ekWINDOW_CLOSE);
    window_title(modalClient, "Client Properties");

    /*ModalData *data = i_modal_data(parent_window);*/
    data = heap_new(ModalData);
    data->parent = parent_window;
    data->type = UINT32_MAX;

    panel = panel_create();
    MainLayout = layout_create(1,3);

    DecisionLayout = layout_create(10, 1);
    pushOK = button_push(); button_text(pushOK, "  OK  ");
    pushCancel = button_push(); button_text(pushCancel, "Cancel"); button_OnClick(pushCancel, listener(app, i_OnClick_ButtonCancel, App));

    /* Section 2 : col = 5, row = 1 */
    layout_button(DecisionLayout, pushOK, 1,0);
    layout_button(DecisionLayout, pushCancel, 3,0);

    /* assigns GenLayout, AuthLayout and DecisionLayout into MainLayout (2,3) */
    layout_layout(MainLayout, DecisionLayout, 0,2);

    /* assigns the layout to the panel */
    panel_layout(panel, MainLayout);

    panel_data(panel, &data, i_destroy_modal_data, ModalData);

    app->modalWindow = modalClient;
    window_panel(modalClient, panel);

    /* sets the default button to Cancel */
    window_defbutton(modalClient, pushCancel);

    moveToCentre(modalClient, app);
    window_modal(modalClient, parent_window);

    if (data != NULL)
	heap_delete(&data, ModalData);
    window_destroy(&app->modalWindow);

}

void ClientChangeUser(App *app, Window *parent_window)
{
    Window *modalClient;
    /*uint32_t i, j;*/
    Panel *panel;
    ModalData *data;

    Layout *MainLayout, *DecisionLayout;
    Button *pushOK, *pushCancel;

    textview_printf(app->text, "Filename is %s, nofilename is %d \n", app->savedFile, app->nofilename);
    textview_scroll_caret(app->text);

    /* creates a modal window */
    modalClient = window_create(ekWINDOW_EDGE | ekWINDOW_TITLE | ekWINDOW_CLOSE);
    window_title(modalClient, "Change Username");

    /*ModalData *data = i_modal_data(parent_window);*/
    data = heap_new(ModalData);
    data->parent = parent_window;
    data->type = UINT32_MAX;

    panel = panel_create();
    MainLayout = layout_create(1,3);

    DecisionLayout = layout_create(10, 1);
    pushOK = button_push(); button_text(pushOK, "  OK  ");
    pushCancel = button_push(); button_text(pushCancel, "Cancel"); button_OnClick(pushCancel, listener(app, i_OnClick_ButtonCancel, App));

    /* Section 2 : col = 5, row = 1 */
    layout_button(DecisionLayout, pushOK, 1,0);
    layout_button(DecisionLayout, pushCancel, 3,0);

    /* assigns GenLayout, AuthLayout and DecisionLayout into MainLayout (2,3) */
    layout_layout(MainLayout, DecisionLayout, 0,2);

    /* assigns the layout to the panel */
    panel_layout(panel, MainLayout);

    panel_data(panel, &data, i_destroy_modal_data, ModalData);

    app->modalWindow = modalClient;
    window_panel(modalClient, panel);

    /* sets the default button to Cancel */
    window_defbutton(modalClient, pushCancel);

    moveToCentre(modalClient, app);
    window_modal(modalClient, parent_window);

    if (data != NULL)
	heap_delete(&data, ModalData);
    window_destroy(&app->modalWindow);
}

void ClientChangePassword(App *app, Window *parent_window)
{
    Window *modalClient;
    /*uint32_t i, j;*/
    Panel *panel;
    ModalData *data;

    Layout *MainLayout, *DecisionLayout;
    Button *pushOK, *pushCancel;

    textview_printf(app->text, "Filename is %s, nofilename is %d \n", app->savedFile, app->nofilename);
    textview_scroll_caret(app->text);

    /* creates a modal window */
    modalClient = window_create(ekWINDOW_EDGE | ekWINDOW_TITLE | ekWINDOW_CLOSE);
    window_title(modalClient, "Change Password");

    /*ModalData *data = i_modal_data(parent_window);*/
    data = heap_new(ModalData);
    data->parent = parent_window;
    data->type = UINT32_MAX;

    panel = panel_create();
    MainLayout = layout_create(1,3);

    DecisionLayout = layout_create(10, 1);
    pushOK = button_push(); button_text(pushOK, "  OK  ");
    pushCancel = button_push(); button_text(pushCancel, "Cancel"); button_OnClick(pushCancel, listener(app, i_OnClick_ButtonCancel, App));

    /* Section 2 : col = 5, row = 1 */
    layout_button(DecisionLayout, pushOK, 1,0);
    layout_button(DecisionLayout, pushCancel, 3,0);

    /* assigns GenLayout, AuthLayout and DecisionLayout into MainLayout (2,3) */
    layout_layout(MainLayout, DecisionLayout, 0,2);

    /* assigns the layout to the panel */
    panel_layout(panel, MainLayout);

    panel_data(panel, &data, i_destroy_modal_data, ModalData);

    app->modalWindow = modalClient;
    window_panel(modalClient, panel);

    /* sets the default button to Cancel */
    window_defbutton(modalClient, pushCancel);

    moveToCentre(modalClient, app);
    window_modal(modalClient, parent_window);

    if (data != NULL)
	heap_delete(&data, ModalData);
    window_destroy(&app->modalWindow);
}
