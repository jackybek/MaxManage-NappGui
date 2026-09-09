#include <nappgui.h>
#include <osapp/osmain.h>
#include <stdio.h>
#include <string.h>
#include "napp.h"


static uint32_t i_task_maxAdapter_StopViewLiveLogs(App *app)
{
        bool pipe = TRUE;
        const char *maxAdapterHost = "192.168.1.109";
        const char *user = "pi";
        char* password = "molekhaven24";
        char cmd[255];
        int status;

        textview_printf(app->textMaxAdapter, "napp_maxAdapter.c : Entering maxAdapter_StopViewLiveLogs() \n");

        // stop the journalctl process
        // kill -s 9 journalctl

	//sprintf(cmd, "echo %s | /usr/bin/sudo -S /bin/bash -c '/usr/bin/kill -s 9 systemd-journald'", password);
#ifdef switch
	sprintf(cmd,
		"echo %s | /usr/bin/sudo -S /bin/bash -c '/usr/bin/systemctl stop system-journald-audit.socket -f && sleep 2'", password);
	status = run_remote_command(maxAdapterHost, user, password, cmd, pipe, app->textMaxAdapter);
        sprintf(cmd,
                "echo %s | /usr/bin/sudo -S /bin/bash -c '/usr/bin/systemctl stop systemd-journald-dev-log.socket -f && sleep 2'", password);
        status = run_remote_command(maxAdapterHost, user, password, cmd, pipe, app->textMaxAdapter);
        sprintf(cmd,
                "echo %s | /usr/bin/sudo -S /bin/bash -c '/usr/bin/systemctl stop system-journald.socket -f && sleep 2 '", password);
        status = run_remote_command(maxAdapterHost, user, password, cmd, pipe, app->textMaxAdapter);
#else
	sprintf(cmd,
		"echo %s | /usr/bin/sudo -S /bin/bash -c '/usr/bin/systemctl stop system-journal.socket-audit.socket systemd-journald-dev-log.socket systemd-journald.socket'", password);
	status = run_remote_command(maxAdapterHost, user, password, cmd, pipe, app->textMaxAdapter);
	if (status == 1) {
		textview_printf(app->textMaxAdapter, "Successfully stop live logs\n");
	}
	else if (status == 0) {
		// not a journal command - do nothing
	}
	else if (status == -1) {
		textview_printf(app->textMaxAdapter, "failed to stop live logs\n");
	}
#endif
        /* hide all the flat buttons */
}

// Runs in GUI thread
static void i_task_maxAdapter_StopViewLiveLogsupdate(App *app)
{
        // update the gui here
        //progress_undefined(app->bar, TRUE);

}

// Runs in GUI thread
static void i_task_maxAdapter_StopViewLiveLogsend(App *app)
{
        // finish the task code here
        progress_undefined(app->bar, FALSE);

}
static uint32_t i_task_maxAdapter_StartViewLiveLogs(App *app)
{
	bool pipe = TRUE;
        const char *maxAdapterHost = "192.168.1.109";
        const char *user = "pi";
	char* password = "molekhaven24";
	char cmd[255];
	int status;

        textview_printf(app->text, "napp_maxAdapter.c : Entering maxAdapter_StartViewLiveLogs() \n");

	// grep the journal output and pipe into a widget
	// show using 'View Live Logs menu item if it is selected in the menu
                // run the journalctl command and pipe to app->textMaxAdapter (widget)

	sprintf(cmd,
		"echo %s | /usr/bin/sudo -S /bin/bash -c '/usr/bin/systemctl restart systemd-journald.socket -f && sleep 2'", password);
	status = run_remote_command(maxAdapterHost, user, password, cmd, pipe, app->textMaxAdapter);
	if (status == 1) {
		textview_printf(app->textMaxAdapter, "Successfully started systemd-journal.socket \n");
	}
	else if (status == -1) {
		textview_printf(app->textMaxAdapter, "failed to start systemd-journal.socket \n");
	}

        sprintf(cmd,
                "echo %s | /usr/bin/sudo -S /bin/bash -c '/usr/bin/systemctl restart systemd-journald-dev-log.socket -f && sleep 2'", password);
        status = run_remote_command(maxAdapterHost, user, password, cmd, pipe, app->textMaxAdapter);
	if (status == 1) {
		textview_printf(app->textMaxAdapter, "Successfully started systemd-journald-dev-log.socket \n");
	}
	else if (status == -1) {
		textview_printf(app->textMaxAdapter, "failed to start systemd-journald-dev-log.socket \n");
	}

        sprintf(cmd,
                "echo %s | /usr/bin/sudo -S /bin/bash -c '/usr/bin/systemctl restart systemd-journald-audit.socket -f && sleep 2'", password);
        status = run_remote_command(maxAdapterHost, user, password, cmd, pipe, app->textMaxAdapter);
	if (status == 1) {
		textview_printf(app->textMaxAdapter, "Successfully started systemd-journald-audit.socket \n");
	}
	else if (status == -1) {
		textview_printf(app->textMaxAdapter, "failed to start systemd-journald-audit.socket \n");
	}
	//execlp("journalctl", "journalctl", "-u", "maxadapter.service", "-f", NULL);


	return 0;
}

// Runs in GUI thread
static void i_task_maxAdapter_StartViewLiveLogsupdate(App *app)
{
        // update the gui here
        //progress_undefined(app->bar, TRUE);

}

// Runs in GUI thread
static void i_task_maxAdapter_StartViewLiveLogsend(App *app)
{
        // finish the task code here
        progress_undefined(app->bar, FALSE);
}

// Runs in a new thread
static uint32_t i_task_maxAdapter_Start(App *app)
{
        int status;
        const char *maxAdapterHost = "192.168.1.109";
        const char *user = "pi";
        const char *password = "molekhaven24";
        char cmd[255];
	bool pipe;
        //const char *cmd = "/usr/bin/sudo -S /bin/bash -c -n /usr/bin/systemctl restart maxintegrator --wait";
//const char *cmd = "echo molekhaven24 | /usr/bin/sudo -S /bin/bash -c '/usr/bin/systemctl restart maxintegrator && sleep 2 && systemctl status maxintegrator > /tmp/ssh_test.log'";


        sprintf(cmd,
                "echo %s | /usr/bin/sudo -S /bin/bash -c '/usr/bin/systemctl restart maxadapter && sleep 2 && systemctl status maxadapter > /tmp/ssh_test.log'", password);

	pipe = FALSE;
        status = run_remote_command(maxAdapterHost, user, password, cmd, pipe, app->textMaxAdapter);
        if (status == 0)
                printf("maxadapter.service started successfully\n");
        else
                printf("error starting maxadapter.service : %d \n", status);


        // grep the journal output and pipe into a widget
        // show using 'View Live Logs menu item if it is selected in the menu
        if (app->maxAdapter_viewLiveLogs_IsShown)
        {
                // run the journalctl command and pipe to app->textMaxAdapter (widget)
        sprintf(cmd,
                "echo %s | /usr/bin/sudo -S /bin/bash -c 'journalctl -u maxadapter.service -f'", password);
        pipe = TRUE;
        status = run_remote_command(maxAdapterHost, user, password, cmd, pipe, app->textMaxAdapter);

        //execlp("journalctl", "journalctl", "-u", "maxadapter.service", "-f", NULL);

        }

        return 0;
}

// Runs in GUI thread
static void i_task_maxAdapter_Startupdate(App *app)
{
        // update the gui here
        //progress_undefined(app->bar, TRUE);

}

// Runs in GUI thread
static void i_task_maxAdapter_Startend(App *app)
{
        // finish the task code here
        progress_undefined(app->bar, FALSE);
}

static uint32_t i_task_maxAdapter_Stop(App *app)
{
        int status;
        const char *maxAdapterHost = "192.168.1.109";
        const char *user = "pi";
        const char *password = "molekhaven24";
        char cmd[255];
	bool pipe;


        sprintf(cmd,
                "echo %s | /usr/bin/sudo -S /bin/bash -c '/usr/bin/systemctl stop maxadapter && sleep 2 && systemctl status maxadapter > /tmp/ssh_test.log'", password);

	pipe = FALSE;
        status = run_remote_command(maxAdapterHost, user, password, cmd, pipe, app->textMaxAdapter);
        if (status == 0)
                printf("maxadapter.service stopped successfully\n");
        else
                printf("error stopping maxadapter.service : %d \n", status);

        return 0;
}


// Runs in GUI thread
static void i_task_maxAdapter_Stopupdate(App *app)
{
        // update the gui here
        //progress_undefined(app->bar, TRUE);
}

// Runs in GUI thread
static void i_task_maxAdapter_Stopend(App *app)
{
        // finish the task code here
        progress_undefined(app->bar, FALSE);
}

void maxAdapterStart(App *app, Window *parent_window)
{

        // create a parallel thread
        osapp_task(app, .04, i_task_maxAdapter_Start, i_task_maxAdapter_Startupdate, i_task_maxAdapter_Startend, App);

}

void maxAdapterStop(App *app, Window *parent_window)
{
        // create a parallel thread
        osapp_task(app, .04, i_task_maxAdapter_Stop, i_task_maxAdapter_Stopupdate, i_task_maxAdapter_Stopend, App);
}


void maxAdapterHistorianServer(App *app, Window *parent_window)
{
Layout *MainLayout, *GenLayout, *AuthLayout, *DecisionLayout;
Button *radio_anonymous, *radio_username_password, *radio_certificate_key;
Button *check_store;

    Window *modalClient;
    V2Df origin;
    float window_x, window_y;
    uint32_t i, j;
    /*Panel *GenPanel, *AuthPanel, *DecisionPanel;*/
    Panel *panel;
    ModalData *data;
    Label *label_connectionip, *label_port, *label_username, *label_password, *label_database, *label_method;
    Edit *edit_connectionip, *edit_port, *edit_username, *edit_password, *edit_database, *edit_method;
    PopUp *popup_method;
    /* Edit *edit_username, *edit_password; */

    /* Edit *edit_certificate, *edit_privatekey; */
    Button *pushSave, *pushTestConnection, *pushCancel;
    /* Button *pushCertificate, *pushPrivateKey; */
    /* Button *radio_anonymous, *radio_username_password, *radio_certificate_key; */
    /* Button *check_store; */
    textview_printf(app->text, "Filename is %s, nofilename is %d \n", app->savedFile, app->nofilename);
    textview_scroll_caret(app->text);

    /* creates a modal window */
    modalClient = window_create(ekWINDOW_EDGE | ekWINDOW_TITLE | ekWINDOW_CLOSE);
    window_title(modalClient, "MaxAdapter - Historian Server");

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
    GenLayout = layout_create(2, 6); /* col, row */
    AuthLayout = layout_create(4, 7);
    DecisionLayout = layout_create(3, 1);


    label_connectionip = label_create();
    label_port = label_create();
    label_username = label_create();
    label_password = label_create();
    label_database = label_create();
    label_method = label_create();

    label_text(label_connectionip, "Connection IP");
    label_text(label_port, "Port");
    label_text(label_username, "Username");
    label_text(label_password, "Password");
    label_text(label_database, "Database");
    label_text(label_method, "Method");

    edit_connectionip = edit_create(); edit_width(edit_connectionip, 300); edit_text(edit_connectionip, "192.168.1.71");
    edit_port = edit_create(); edit_width(edit_port, 300); edit_text(edit_port, "3306");
    edit_username = edit_create(); edit_width(edit_username, 300); edit_text(edit_username, "debian");
    edit_password = edit_create(); edit_width(edit_password, 300); edit_text(edit_password, "molekhaven"); edit_passmode(edit_password, TRUE);
    edit_database = edit_create(); edit_width(edit_database, 300); edit_text(edit_database, "HistoryAirgard");

    popup_method = popup_create();
    popup_add_elem(popup_method, "Poll", NULL);
    popup_add_elem(popup_method, "Value Set", NULL);
    popup_add_elem(popup_method, "User Defined", NULL);

#ifdef NO_NEED
    radio_anonymous = button_radio(); button_text(radio_anonymous, "Anonymous"); button_state(radio_anonymous, ekGUI_ON); button_OnClick(radio_anonymous, listener(app, i_OnClick_radioAnonymous, App));
    radio_username_password = button_radio();  button_state(radio_username_password, ekGUI_OFF); button_OnClick(radio_username_password, listener(app, i_OnClick_radioUsernamePassword, App)); /*button_text(radio_username, "Username");*/
    radio_certificate_key = button_radio(); button_state(radio_certificate_key, ekGUI_OFF); button_OnClick(radio_certificate_key, listener(app, i_OnClick_radioCertificateKey, App)); /*button_text(radio_certificate, "Certificate");*/

    edit_username = edit_create(); edit_width(edit_username, 300); edit_editable(edit_username, FALSE);
    edit_password = edit_create(); edit_width(edit_password, 300); edit_editable(edit_password, FALSE); edit_passmode(edit_password, TRUE);
    edit_certificate = edit_create(); edit_width(edit_certificate, 300); edit_editable(edit_certificate, FALSE);
    edit_privatekey = edit_create(); edit_width(edit_privatekey, 300); edit_editable(edit_privatekey, FALSE);

    pushCertificate = button_push(); button_text(pushCertificate, "..."); button_state(pushCertificate, ekGUI_OFF); button_OnClick(pushCertificate, listener(app, i_OnClick_ButtonCertificate, App));
    pushPrivateKey = button_push(); button_text(pushPrivateKey, "..."); button_state(pushPrivateKey, ekGUI_OFF); button_OnClick(pushPrivateKey, listener(app, i_OnClick_ButtonPrivateKey, App));
#endif

    pushSave = button_push(); button_text(pushSave, "  Save  ");
    pushTestConnection = button_push(); button_text(pushTestConnection, "Test Connection");
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
      for(j=0; j<6; j++) {
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
    layout_label(GenLayout, label_connectionip, 0, 0);
    layout_label(GenLayout, label_port, 0,1);
    layout_label(GenLayout, label_username, 0,2);
    layout_label(GenLayout, label_password, 0,3);
    layout_label(GenLayout, label_database, 0,4);
    layout_label(GenLayout, label_method, 0,5);

    layout_edit(GenLayout, edit_connectionip, 1,0);
    layout_edit(GenLayout, edit_port, 1,1);
    layout_edit(GenLayout, edit_username, 1,2);
    layout_edit(GenLayout, edit_password, 1,3);
    layout_edit(GenLayout, edit_database, 1,4);
    layout_popup(GenLayout, popup_method, 1,5);

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
    layout_button(DecisionLayout, pushTestConnection, 1, 0);
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

   /* handle to target window to align centre to app->window centre */
    window_x = window_get_size(modalClient).width;
    window_y = window_get_size(modalClient).height;

textview_printf(app->text, "MaxAdapter->Historian (size_x : %f, size_y : %f)\n", window_x, window_y);
printf("MaxAdapter->Historian (window size_x : %f, window size_y : %f)\n", window_x, window_y);

    /* move the dialog window to the centre of the screen */
    origin.x = app->sys_resolution.x / 2 - window_x / 2 ;
    origin.y = app->sys_resolution.y / 2 - window_y / 2 ;
    window_origin(modalClient, origin );

textview_printf(app->text, "MaxAdapter->Historian (origin.x = %f, origin.y = %f\n", origin.x, origin.y);
printf("MaxAdapter->Historian (origin.x = %f, origin.y = %f\n", origin.x, origin.y);



    /* centres the window */
    //moveToCentre(modalClient, app);
    window_modal(modalClient, parent_window);
/*
    if (data != NULL)
        heap_delete(&data, ModalData);
    window_destroy(&app->modalWindow);
*/


}

void maxAdapterAlarmsAndConditions(App *app, Window *parent_window)
{

}

void maxAdapterEvents(App *app, Window *parent_window)
{

}

void maxAdapterLogsManagement(App *app, Window *parent_window)
{

}

void maxAdapterReverseConnect(App *app, Window *parent_window)
{
Layout *MainLayout, *GenLayout, *AuthLayout, *DecisionLayout;

    Window *modalClient;
    V2Df origin;
    float window_x, window_y;
    uint32_t i, j;
    /*Panel *GenPanel, *AuthPanel, *DecisionPanel;*/
    Panel *panel;
    ModalData *data;
    Label *label_port, *label_clientip;
    Edit *edit_port, *edit_clientip;

    Button *pushSave, *pushCancel;
    textview_printf(app->text, "Filename is %s, nofilename is %d \n", app->savedFile, app->nofilename);
    textview_scroll_caret(app->text);

    /* creates a modal window */
    modalClient = window_create(ekWINDOW_EDGE | ekWINDOW_TITLE | ekWINDOW_CLOSE);
    window_title(modalClient, "maxAdapter - Reverse Connect");

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
    GenLayout = layout_create(2, 4); /* col, row */
    AuthLayout = layout_create(4, 7);
    DecisionLayout = layout_create(5, 1);

    label_port = label_create();
    label_clientip = label_create();

    label_text(label_port, "Reverse Connect Port");
    label_text(label_clientip, "Client IP Address");

    edit_port = edit_create(); edit_width(edit_port, 300); edit_text(edit_port, "4839");
    edit_clientip = edit_create(); edit_width(edit_clientip, 300); edit_text(edit_clientip, "192.168.1.158");

    pushSave = button_push(); button_text(pushSave, "  Save  ");
    pushCancel = button_push(); button_text(pushCancel, "Cancel"); button_OnClick(pushCancel, listener(app, i_OnClick_ButtonCancel, App));

    /* col = 1, row = 3 */
    layout_hsize(MainLayout, 0, 600);

    /* sets up margins and col width and row height */
    /* Section 1 : col = 2, row = 4 */
    layout_hsize(GenLayout, 0, 200);
    layout_hsize(GenLayout, 1, 400);
    layout_hmargin(GenLayout,0,5);
    for (i=0; i<2; i++) {
      for(j=0; j<4; j++) {
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
    layout_label(GenLayout, label_port, 0, 0);
    layout_label(GenLayout, label_clientip, 0,1);

    layout_edit(GenLayout, edit_port, 1,0);
    layout_edit(GenLayout, edit_clientip, 1,1);

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
    layout_button(DecisionLayout, pushSave, 1,0);
    layout_button(DecisionLayout, pushCancel, 3,0);

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



    /* handle to target window to align centre to app->window centre */
    window_x = window_get_size(modalClient).width;
    window_y = window_get_size(modalClient).height;

textview_printf(app->text, "MaxAdapter->reverseConnect (size_x : %f, size_y : %f)\n", window_x, window_y);
printf("MaxAdapter->reverseConnect (window size_x : %f, window size_y : %f)\n", window_x, window_y);

    /* move the dialog window to the centre of the screen */
    origin.x = app->sys_resolution.x / 2 - window_x / 2 ;
    origin.y = app->sys_resolution.y / 2 - window_y / 2 ;
    window_origin(modalClient, origin );

textview_printf(app->text, "MaxAdapter->reverseConnect (origin.x = %f, origin.y = %f\n", origin.x, origin.y);
printf("MaxAdapter->reverseConnect (origin.x = %f, origin.y = %f\n", origin.x, origin.y);


    /* centres the window */
    //moveToCentre(modalClient, app);
    window_modal(modalClient, parent_window);
/*
    if (data != NULL)
        heap_delete(&data, ModalData);
    window_destroy(&app->modalWindow);
*/

}


void maxAdapterStartupParameters(App *app, Window *parent_window)
{
        ferror_t error= ekFOK;
        ImageView *imgView;
        ImageView *maxAdapterStartupParametersView;
        Image *maxAdapterStartupParametersImage;

        textview_printf(app->text, "napp_maxAdapter.c : Entering maxAdapterStartupParameters() \n");
        maxAdapterStartupParametersView = imageview_create();
        maxAdapterStartupParametersImage = image_from_file("/home/pi/nappgui_src/jacky/img/startupParameters.jpg", &error);
printf("Error  = %d \n", error);

        if (maxAdapterStartupParametersImage!=NULL && error==ekFOK) {
                textview_printf(app->text, "napp_maxAdapter.c : Here \n");
                /* hide */
                layout_show_col(app->canvasLayout, 0, FALSE);
                layout_show_row(app->canvasLayout, 0, FALSE);
                /* update the image */
                imageview_image(maxAdapterStartupParametersView, maxAdapterStartupParametersImage);
                imgView = layout_get_imageview(app->canvasLayout, 0,0); // get the handle to the imageView in the layout
                imageview_image(imgView, maxAdapterStartupParametersImage); // update the imgView with the new imageView
                layout_imageview(app->canvasLayout, imgView, 0,0); // assign the new imageView back to the layout
                /* show */
                layout_show_col(app->canvasLayout, 0, TRUE);
                layout_show_row(app->canvasLayout, 0, TRUE);
        }
        else
                textview_printf(app->text, "maxAdapter.c : Error loading /home/pi/nappgui_src/jacky/img/startupParameters.jpg\n");

}


void maxAdapterCommunicationsProtocol(App *app, Window *parent_window)
{

}

void maxAdapterViewStatistics(App *app, Window *parent_window)
{
        ferror_t error= ekFOK;
        ImageView *imgView;
        ImageView *maxAdapterViewStatisticsView;
        Image *maxAdapterViewStatisticsImage;

        textview_printf(app->text, "napp_maxAdapter.c : Entering maxAdapterViewStatistics() \n");
        maxAdapterViewStatisticsView = imageview_create();
        maxAdapterViewStatisticsImage = image_from_file("/home/pi/nappgui_src/jacky/img/maxAdapterViewStatistics.png", &error);
        if (maxAdapterViewStatisticsImage!=NULL && error==ekFOK) {
                textview_printf(app->text, "napp_maxAdapter.c : Here \n");
                /* hide */
                layout_show_col(app->canvasLayout, 0, FALSE);
                layout_show_row(app->canvasLayout, 0, FALSE);
                /* update the image */
                imageview_image(maxAdapterViewStatisticsView, maxAdapterViewStatisticsImage);
                imgView = layout_get_imageview(app->canvasLayout, 0,0); // get the handle to the imageView in the layout
                imageview_image(imgView, maxAdapterViewStatisticsImage); // update the imgView with the new imageView
                layout_imageview(app->canvasLayout, imgView, 0,0); // assign the new imageView back to the layout
                /* show */
                layout_show_col(app->canvasLayout, 0, TRUE);
                layout_show_row(app->canvasLayout, 0, TRUE);
        }
        else
                textview_printf(app->text, "napp_maxAdapter.c : Error loading /home/pi/nappgui_src/jacky/img/maxAdapterViewStatistics.png\n");

}


void maxAdapterViewLiveLogs(App *app, Window *parent_window, bool StartOrStop)
{

        // create a parallel thread
	if (StartOrStop == TRUE) // start
	        osapp_task(app, .04, i_task_maxAdapter_StartViewLiveLogs, i_task_maxAdapter_StartViewLiveLogsupdate, i_task_maxAdapter_StartViewLiveLogsend, App);
	else // StartOrStop == FALSE // stop
		osapp_task(app, .04, i_task_maxAdapter_StopViewLiveLogs, i_task_maxAdapter_StopViewLiveLogsupdate, i_task_maxAdapter_StopViewLiveLogsend, App);
}

void maxAdapterDiscoverDevices(App *app, Window *parentWindow)
{





}

void maxAdapterAutoGenerate(App *app, Window *parentWindow)
{

}

void maxAdapterSimRun(App *app, Window *parentWindow)
{

}

void maxAdapterNodesetEditor(App *app, Window *parentWindow)
{
        ferror_t error= ekFOK;
        ImageView *imgView;
        ImageView *maxAdapterNodesetEditorImageView;
        Image *maxAdapterNodesetEditorImage;

        textview_printf(app->text, "napp_maxAdapter.c : Entering maxAdapterNodesetEditor() \n");
        maxAdapterNodesetEditorImageView = imageview_create();
        maxAdapterNodesetEditorImage = image_from_file("/home/pi/nappgui_src/jacky/img/editDeviceNodeset.jpg", &error);
        if (maxAdapterNodesetEditorImage!=NULL && error==ekFOK) {
                textview_printf(app->text, "napp_maxAdapter.c : Here \n");
                /* hide */
                layout_show_col(app->canvasLayout, 0, FALSE);
                layout_show_row(app->canvasLayout, 0, FALSE);
                /* update the image */
                imageview_image(maxAdapterNodesetEditorImageView, maxAdapterNodesetEditorImage);
                imgView = layout_get_imageview(app->canvasLayout, 0,0); // get the handle to the imageView in the layout
                imageview_image(imgView, maxAdapterNodesetEditorImage); // update the imgView with the new imageView
                layout_imageview(app->canvasLayout, imgView, 0,0); // assign the new imageView back to the layout
                /* show */
                layout_show_col(app->canvasLayout, 0, TRUE);
                layout_show_row(app->canvasLayout, 0, TRUE);
        }
        else
                textview_printf(app->text, "napp_maxAdapter.c : Error loading /home/pi/nappgui_src/jacky/img/editDeviceNodeset.jpg\n");

}

void maxAdapterManualConfiguration(App *app, Window *parentWindow)
{
        ferror_t error= ekFOK;
        ImageView *imgView;
        ImageView *maxAdapterManualConfigurationImageView;
        Image *maxAdapterManualConfigurationImage;

        textview_printf(app->text, "napp_maxAdapter.c : Entering maxAdapterManualConfiguration() \n");
        maxAdapterManualConfigurationImageView = imageview_create();
        maxAdapterManualConfigurationImage = image_from_file("/home/pi/nappgui_src/jacky/img/maxAdapter.jpg", &error);
        if (maxAdapterManualConfigurationImage!=NULL && error==ekFOK) {
                textview_printf(app->text, "napp_maxAdapter.c : Here \n");
                /* hide */
                layout_show_col(app->canvasLayout, 0, FALSE);
                layout_show_row(app->canvasLayout, 0, FALSE);
                /* update the image */
                imageview_image(maxAdapterManualConfigurationImageView, maxAdapterManualConfigurationImage);
                imgView = layout_get_imageview(app->canvasLayout, 0,0); // get the handle to the imageView in the layout
                imageview_image(imgView, maxAdapterManualConfigurationImage); // update the imgView with the new imageView
                layout_imageview(app->canvasLayout, imgView, 0,0); // assign the new imageView back to the layout
                /* show */
                layout_show_col(app->canvasLayout, 0, TRUE);
                layout_show_row(app->canvasLayout, 0, TRUE);
        }
        else
                textview_printf(app->text, "napp_maxAdapter.c : Error loading /home/pi/nappgui_src/jacky/img/maxAdapter.jpg\n");
}
