#include <nappgui.h>
#include <osapp/osmain.h>
#include <stdio.h>
#include <string.h>
#include "napp.h"
#include "mongoose.h"

/* global variable to store *app */
extern App *g_app;


void maxServicesUsersAccount(App *app, Window *parent_window)
{

        ferror_t error= ekFOK;
        ImageView *imgView;
        ImageView *maxEngineUsersAccountView;
        Image *maxEngineUsersAccountImage;

        textview_printf(app->text, "napp_maxEngine.c : Entering maxEngineUsersAccount() \n");
        maxEngineUsersAccountView = imageview_create();
        maxEngineUsersAccountImage = image_from_file("/home/pi/nappgui_src/jacky/img/maxEngineUsersLogin.png", &error);
        if (maxEngineUsersAccountImage!=NULL && error==ekFOK) {
                textview_printf(app->text, "napp_maxEngine.c : Here \n");
                /* hide */
                layout_show_col(app->canvasLayout, 0, FALSE);
                layout_show_row(app->canvasLayout, 0, FALSE);
                /* update the image */
                imageview_image(maxEngineUsersAccountView, maxEngineUsersAccountImage);
                imgView = layout_get_imageview(app->canvasLayout, 0,0); // get the handle to the imageView in the layout
                imageview_image(imgView, maxEngineUsersAccountImage); // update the imgView with the new imageView
                layout_imageview(app->canvasLayout, imgView, 0,0); // assign the new imageView back to the layout
                /* show */
                layout_show_col(app->canvasLayout, 0, TRUE);
                layout_show_row(app->canvasLayout, 0, TRUE);
        }
        else
                textview_printf(app->text, "napp_maxEngine.c : Error loading /home/pi/nappgui_src/jacky/img/maxEngineUsersLogin.png\n");


}

void maxServicesSystemsAccount(App *app, Window *parent_window)
{

        ferror_t error= ekFOK;
        ImageView *imgView;
        ImageView *maxEngineSystemsAccountView;
        Image *maxEngineSystemsAccountImage;

        textview_printf(app->text, "napp_maxEngine.c : Entering maxEngineSystemsAccount() \n");
        maxEngineSystemsAccountView = imageview_create();
        maxEngineSystemsAccountImage = image_from_file("/home/pi/nappgui_src/jacky/img/maxEngineSystemsLogin.png", &error);
        if (maxEngineSystemsAccountImage!=NULL && error==ekFOK) {
                textview_printf(app->text, "napp_maxEngine.c : Here \n");
                /* hide */
                layout_show_col(app->canvasLayout, 0, FALSE);
                layout_show_row(app->canvasLayout, 0, FALSE);
                /* update the image */
                imageview_image(maxEngineSystemsAccountView, maxEngineSystemsAccountImage);
                imgView = layout_get_imageview(app->canvasLayout, 0,0); // get the handle to the imageView in the layout
                imageview_image(imgView, maxEngineSystemsAccountImage); // update the imgView with the new imageView
                layout_imageview(app->canvasLayout, imgView, 0,0); // assign the new imageView back to the layout
                /* show */
                layout_show_col(app->canvasLayout, 0, TRUE);
                layout_show_row(app->canvasLayout, 0, TRUE);
        }
        else
                textview_printf(app->text, "napp_maxEngine.c : Error loading /home/pi/nappgui_src/jacky/img/maxEngineSystemsLogin.png\n");
}


void maxServicesGenerateSSLCertificates(App *app, Window *parent_window)
{
Layout *MainLayout, *GenLayout, *AuthLayout, *DecisionLayout;
Button *radio_anonymous, *radio_username_password, *radio_certificate_key;
Button *check_store;

    Window *modalClient;
    uint32_t i, j;
    /*Panel *GenPanel, *AuthPanel, *DecisionPanel;*/
    Panel *panel;
    ModalData *data;
    Label *label_applicationuri, *label_privatekey, *label_certificate, *label_username, *label_password, *label_ipaddress, *label_port;
    Edit *edit_applicationuri, *edit_privatekey, *edit_certificate, *edit_username, *edit_password, *edit_ipaddress, *edit_port;
    PopUp *popup_method;
    /* Edit *edit_username, *edit_password; */

    /* Edit *edit_certificate, *edit_privatekey; */
    Button *pushSave, *pushSaveAndDeploy, *pushCancel;
    /* Button *pushCertificate, *pushPrivateKey; */
    /* Button *radio_anonymous, *radio_username_password, *radio_certificate_key; */
    /* Button *check_store; */
    textview_printf(app->text, "Filename is %s, nofilename is %d \n", app->savedFile, app->nofilename);
    textview_scroll_caret(app->text);

    /* creates a modal window */
    modalClient = window_create(ekWINDOW_EDGE | ekWINDOW_TITLE | ekWINDOW_CLOSE);
    window_title(modalClient, "maxEngine - Generate SSL Certificate");

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
    MainLayout = layout_create(1,4);
    GenLayout = layout_create(2, 8); /* col, row */
    AuthLayout = layout_create(4, 7);
    DecisionLayout = layout_create(3, 1);

    label_applicationuri = label_create();
    label_privatekey = label_create();
    label_certificate = label_create();
    label_username = label_create();
    label_password = label_create();
    label_ipaddress = label_create();
    label_port = label_create();

    label_text(label_applicationuri, "Application URI");
    label_text(label_privatekey, "Private Key");
    label_text(label_certificate, "Certificate");
    label_text(label_username, "TrustList location");
    label_text(label_password, "Revocation List location");
    label_text(label_ipaddress, "Receipient Email Address");
    label_text(label_port, "SSL Config File");

    edit_applicationuri = edit_create(); edit_width(edit_applicationuri, 400); edit_text(edit_applicationuri, "urn:opc109.virtualskies.com.sg");
    edit_privatekey = edit_create(); edit_width(edit_privatekey, 400); edit_text(edit_privatekey, "/usr/local/ssl/private/Opcprivate-key109.pem");
    edit_certificate = edit_create(); edit_width(edit_certificate, 400); edit_text(edit_certificate, "/usr/local/ssl/certs/Opccert109.pem");
    edit_username = edit_create(); edit_width(edit_username, 400); edit_text(edit_username, "/usr/local/ssl/certs/trustlist/");
    edit_password = edit_create(); edit_width(edit_password, 400); edit_text(edit_password, "/usr/local/ssl/revocationlist/");
    edit_ipaddress = edit_create(); edit_width(edit_ipaddress, 400); edit_text(edit_ipaddress, "jackybek@maxmachinestech.com");
    edit_port = edit_create(); edit_width(edit_port, 400); edit_text(edit_port, "/usr/local/ssl/openssl-109.cnf");

#ifdef NO_NEED
    popup_method = popup_create();
    popup_add_elem(popup_method, "Poll", NULL);
    popup_add_elem(popup_method, "Value Set", NULL);
    popup_add_elem(popup_method, "User Defined", NULL);

    radio_anonymous = button_radio(); button_text(radio_anonymous, "Anonymous"); button_state(radio_anonymous, ekGUI_ON); button_OnClick(radio_anonymous, liste>
    radio_username_password = button_radio();  button_state(radio_username_password, ekGUI_OFF); button_OnClick(radio_username_password, listener(app, i_OnClic>
    radio_certificate_key = button_radio(); button_state(radio_certificate_key, ekGUI_OFF); button_OnClick(radio_certificate_key, listener(app, i_OnClick_radio>

    edit_username = edit_create(); edit_min_width(edit_username, 300); edit_editable(edit_username, FALSE);
    edit_password = edit_create(); edit_min_width(edit_password, 300); edit_editable(edit_password, FALSE); edit_passmode(edit_password, TRUE);
    edit_certificate = edit_create(); edit_min_width(edit_certificate, 300); edit_editable(edit_certificate, FALSE);
    edit_privatekey = edit_create(); edit_min_width(edit_privatekey, 300); edit_editable(edit_privatekey, FALSE);

    pushCertificate = button_push(); button_text(pushCertificate, "..."); button_state(pushCertificate, ekGUI_OFF); button_OnClick(pushCertificate, listener(ap>
    pushPrivateKey = button_push(); button_text(pushPrivateKey, "..."); button_state(pushPrivateKey, ekGUI_OFF); button_OnClick(pushPrivateKey, listener(app, i>
#endif

    pushSave = button_push(); button_text(pushSave, "  Save  ");
    pushSaveAndDeploy = button_push(); button_text(pushSaveAndDeploy, "Save And Generate");
    pushCancel = button_push(); button_text(pushCancel, "Cancel"); button_OnClick(pushCancel, listener(app, i_OnClick_ButtonCancel, App));

#ifdef NO_NEED
    check_store = button_check(); button_text(check_store, "Store");
#endif
    /* col = 1, row = 3 */
    layout_hsize(MainLayout, 0, 600);

    /* sets up margins and col width and row height */
    /* Section 1 : col = 2, row = 4 */
    layout_hsize(GenLayout, 0, 200);
    layout_hsize(GenLayout, 1, 400);
    layout_hmargin(GenLayout,0,5);
    for (i=0; i<2; i++) {
      for(j=0; j<8; j++) {
        layout_halign(GenLayout, i,j, ekLEFT);
      }
    }
    for (i=0; i<3; i++)
        layout_vmargin(GenLayout, i, 2);
    layout_margin(GenLayout, 10); /* sets a fix margin around the border */

#ifdef NO_NEED
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

    layout_vsize(AuthLayout, 2, 1);     /* reduce the height of radio buttons */
    layout_vsize(AuthLayout, 5, 1);     /* reduce the height of radio buttons */
    for (i=0; i<3; i++)
        layout_vmargin(AuthLayout, i, 2);
    layout_margin(AuthLayout, 10); /* sets a fix margin around the border */
#endif

    /* Section 3 : col = 10, row = 1 */
    for(i=0; i<9; i++)
        layout_hsize(DecisionLayout, i, 10); /* set a fix width of all columns */

    layout_vmargin(DecisionLayout, 0, 2);

    /* assigns the interface objects i.e. label, edit, ... to the layout in X(col),Y(row) coordinate, starts with index 0 */
    /* Section 1 : col = 2, row = 3 */
    layout_label(GenLayout, label_applicationuri, 0,0);
    layout_label(GenLayout, label_privatekey, 0,1);
    layout_label(GenLayout, label_certificate, 0,2);
    layout_label(GenLayout, label_username, 0,3);
    layout_label(GenLayout, label_password, 0,4);
    layout_label(GenLayout, label_ipaddress, 0,5);
    layout_label(GenLayout, label_port, 0,6);

    layout_edit(GenLayout, edit_applicationuri, 1,0);
    layout_edit(GenLayout, edit_privatekey, 1,1);
    layout_edit(GenLayout, edit_certificate, 1,2);
    layout_edit(GenLayout, edit_username, 1,3);
    layout_edit(GenLayout, edit_password, 1,4);
    layout_edit(GenLayout, edit_ipaddress, 1,5);
    layout_edit(GenLayout, edit_port, 1,6);

    /* Section 2 : col = 4, row = 7 */
#ifdef NO_NEED
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
#endif

    /* Section 3 : col = 10, row = 1 */
    layout_button(DecisionLayout, pushSave, 0, 0);
    layout_button(DecisionLayout, pushSaveAndDeploy, 1, 0);
    layout_button(DecisionLayout, pushCancel, 2, 0);

    /* assigns GenLayout, AuthLayout and DecisionLayout into MainLayout (2,3) */
    layout_layout(MainLayout, GenLayout, 0, 0);
//    layout_layout(MainLayout, AuthLayout, 0,1);
    layout_layout(MainLayout, DecisionLayout, 0,2);

    /* disable the edit fields */
#ifdef NO_NEED
    cell_enabled(layout_cell(AuthLayout,2,1), FALSE);
    cell_enabled(layout_cell(AuthLayout,2,3), FALSE);
    cell_enabled(layout_cell(AuthLayout,2,4), FALSE);
    cell_enabled(layout_cell(AuthLayout,2,6), FALSE);
    /* disable the buttons pushCertificate and pushPrivateKey */
    cell_enabled(layout_cell(AuthLayout,3,4), FALSE);
    cell_enabled(layout_cell(AuthLayout,3,6), FALSE);
#endif

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
    //moveToCentre(modalClient, app);
    window_modal(modalClient, parent_window);
/*
    if (data != NULL)
        heap_delete(&data, ModalData);
    window_destroy(&app->modalWindow);
*/


}
