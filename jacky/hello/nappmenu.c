#include <nappgui.h>
#include <osapp/osmain.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "napp.h"

void i_OnClick_menu_project_new(App *app, Event *e)
{
    textview_printf(app->text, "Project->New Menu click (%d)\n", app->clicks);
        textview_scroll_caret(app->text);

    app->clicks += 1;

    unref(e);
    /*createAttributesWindow(app->window);*/
}

void i_OnClick_menu_project_open(App *app, Event *e)
{
    textview_printf(app->text, "Project->Open Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    FileOpen(app, app->window);
    unref(e);
}

void i_OnClick_menu_project_save(App *app, Event *e)
{
    textview_printf(app->text, "Project->Save Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);

    app->clicks += 1;
    FileSave(app, app->window);

    unref(e);
}

void i_OnClick_menu_project_saveAs(App *app, Event *e)
{
    textview_printf(app->text, "Project->Save As Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    FileSaveAs(app, app->window);
    unref(e);
}

void i_OnClick_menu_project_close(App *app, Event *e)
{
    textview_printf(app->text, "Project->Close Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    FileClose(app, app->window);
    unref(e);
}

void i_OnClick_menu_project_quit(App *app, Event *e)
{
    osapp_finish();
    unref(app);
    unref(e);

}

void i_OnClick_menu_view_interconnectivity(App *app, Event *e)
{
    textview_printf(app->text, "View->Interconnectivity Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    ViewInterconnectivity(app, app->window);
    unref(e);
}

void i_OnClick_menu_view_project(App *app, Event *e)
{
    textview_printf(app->text, "View->Project Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    ViewProject(app, app->window);
    unref(e);
}

void i_OnClick_menu_view_attributes(App *app, Event *e)
{
    textview_printf(app->text, "View->Attributes Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    ViewAttributes(app, app->window);
    unref(e);
}

void i_OnClick_menu_view_references(App *app, Event *e)
{
    textview_printf(app->text, "View->References Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    ViewReferences(app, app->window);
    unref(e);

}

void i_OnClick_menu_view_addressspace(App *app, Event *e)
{
    textview_printf(app->text, "View->Address Space Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    ViewAddressSpace(app, app->window);
    unref(e);
}

void i_OnClick_menu_view_maxAdapter(App *app, Event *e)
{
    textview_printf(app->text, "View->maxAdapter Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    ViewmaxAdapter(app, app->window);
    unref(e);

}

void i_OnClick_menu_view_maxGate(App *app, Event *e)
{
    textview_printf(app->text, "View->maxGate Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    ViewmaxGate(app, app->window);
    unref(e);

}

void i_OnClick_menu_view_maxIntegrator(App *app, Event *e)
{
    textview_printf(app->text, "View->maxIntegrator Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    ViewmaxIntegrator(app, app->window);
    unref(e);

}

void i_OnClick_menu_view_log(App *app, Event *e)
{
    textview_printf(app->text, "View->Log Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    ViewLog(app, app->window);
    unref(e);
}

void i_OnClick_menu_view_filetoolbar(App *app, Event *e)
{
    textview_printf(app->text, "View->File Toolbar Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    /* alternate the status of the button */
    app->view_fileToolbar_IsShown = !app->view_fileToolbar_IsShown;
    if (app->view_fileToolbar_IsShown) {
	/* show the tick */
	menuitem_state(app->view_fileToolbar, ekGUI_ON);

	/* show all the flat buttons */
	textview_printf(app->text, "View->File Toolbar : showing flat buttons \n", app->clicks);
	layout_show_col(app->buttonLayout, 0, TRUE);
        layout_show_col(app->buttonLayout, 1, TRUE);
	layout_show_col(app->buttonLayout, 2, TRUE);
	layout_show_col(app->buttonLayout, 3, TRUE);
	layout_show_col(app->buttonLayout, 4, TRUE);
	layout_show_col(app->buttonLayout, 5, TRUE);

    } else {
	/* hide the tick */
	menuitem_state(app->view_fileToolbar, ekGUI_OFF);

	/* hide all the flat buttons */
	textview_printf(app->text, "View->File Toolbar : hiding flat buttons \n", app->clicks);
	layout_show_col(app->buttonLayout, 0, FALSE);
	layout_show_col(app->buttonLayout, 1, FALSE);
	layout_show_col(app->buttonLayout, 2, FALSE);
	layout_show_col(app->buttonLayout, 3, FALSE);
	layout_show_col(app->buttonLayout, 4, FALSE);
	layout_show_col(app->buttonLayout, 5, FALSE);

    }
    layout_update(app->buttonLayout);
    unref(e);

}

void i_OnClick_menu_view_viewtoolbar(App *app, Event *e)
{
    textview_printf(app->text, "View->View Toolbar Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    /* alternate the status of the button */
    app->view_viewToolbar_IsShown = !app->view_viewToolbar_IsShown;
    if (app->view_viewToolbar_IsShown) {
        /* show the tick */
        menuitem_state(app->view_viewToolbar, ekGUI_ON);

        /* show all the flat buttons */
        textview_printf(app->text, "Toolbars->View Toolbar : showing flat buttons \n", app->clicks);
        layout_show_col(app->buttonLayout, 6, TRUE);
        layout_show_col(app->buttonLayout, 7, TRUE);
        layout_show_col(app->buttonLayout, 8, TRUE);
        layout_show_col(app->buttonLayout, 9, TRUE);
        layout_show_col(app->buttonLayout, 10, TRUE);
        layout_show_col(app->buttonLayout, 11, TRUE);

    } else {
        /* hide the tick */
        menuitem_state(app->view_viewToolbar, ekGUI_OFF);

        /* hide all the flat buttons */
        textview_printf(app->text, "Toolbars->View Toolbar : hiding flat buttons \n", app->clicks);
        layout_show_col(app->buttonLayout, 6, FALSE);
        layout_show_col(app->buttonLayout, 7, FALSE);
        layout_show_col(app->buttonLayout, 8, FALSE);
        layout_show_col(app->buttonLayout, 9, FALSE);
        layout_show_col(app->buttonLayout, 10, FALSE);
        layout_show_col(app->buttonLayout, 11, FALSE);

    }
    layout_update(app->buttonLayout);
    unref(e);
}

void i_OnClick_menu_view_maxEnginetoolbar(App *app, Event *e)
{
    textview_printf(app->text, "View->maxEngine Toolbar Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    /* alternate the status of the button */
    app->view_maxEngineToolbar_IsShown = !app->view_maxEngineToolbar_IsShown;
    if (app->view_maxEngineToolbar_IsShown) {
        /* show the tick */
        menuitem_state(app->view_maxEngineToolbar, ekGUI_ON);

        /* show all the flat buttons */
        textview_printf(app->text, "Toolbars->maxEngine Toolbar : showing flat buttons \n", app->clicks);
        layout_show_col(app->buttonLayout, 12, TRUE);
        layout_show_col(app->buttonLayout, 13, TRUE);
        layout_show_col(app->buttonLayout, 14, TRUE);
        layout_show_col(app->buttonLayout, 15, TRUE);
        layout_show_col(app->buttonLayout, 16, TRUE);
        layout_show_col(app->buttonLayout, 17, TRUE);
        layout_show_col(app->buttonLayout, 18, TRUE);
        layout_show_col(app->buttonLayout, 19, TRUE);
        layout_show_col(app->buttonLayout, 20, TRUE);
        layout_show_col(app->buttonLayout, 21, TRUE);
        layout_show_col(app->buttonLayout, 22, TRUE);
        layout_show_col(app->buttonLayout, 23, TRUE);
        layout_show_col(app->buttonLayout, 24, TRUE);
	layout_show_col(app->buttonLayout, 25, TRUE);

    } else {
        /* hide the tick */
        menuitem_state(app->view_maxEngineToolbar, ekGUI_OFF);

        /* hide all the flat buttons */
        textview_printf(app->text, "Toolbars->maxEngine Toolbar : hiding flat buttons \n", app->clicks);
        layout_show_col(app->buttonLayout, 12, FALSE);
        layout_show_col(app->buttonLayout, 13, FALSE);
        layout_show_col(app->buttonLayout, 14, FALSE);
        layout_show_col(app->buttonLayout, 15, FALSE);
        layout_show_col(app->buttonLayout, 16, FALSE);
        layout_show_col(app->buttonLayout, 17, FALSE);
        layout_show_col(app->buttonLayout, 18, FALSE);
        layout_show_col(app->buttonLayout, 19, FALSE);
        layout_show_col(app->buttonLayout, 20, FALSE);
        layout_show_col(app->buttonLayout, 21, FALSE);
        layout_show_col(app->buttonLayout, 22, FALSE);
        layout_show_col(app->buttonLayout, 23, FALSE);
        layout_show_col(app->buttonLayout, 24, FALSE);
        layout_show_col(app->buttonLayout, 25, FALSE);

    }
    layout_update(app->buttonLayout);

    unref(e);

}

void i_OnClick_menu_view_maxCoretoolbar(App *app, Event *e)
{
    textview_printf(app->text, "View->maxCore Toolbar Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    /* alternate the status of the button */
    app->view_maxCoreToolbar_IsShown = !app->view_maxCoreToolbar_IsShown;
    if (app->view_maxCoreToolbar_IsShown) {
        /* show the tick */
        menuitem_state(app->view_maxCoreToolbar, ekGUI_ON);

	/* show all the flat buttons */


    } else {
	/* hide the tick */
	menuitem_state(app->view_maxCoreToolbar, ekGUI_OFF);

	/* hide all the flat buttons */
    }

    layout_update(app->buttonLayout);
    unref(e);

}

void i_OnClick_menu_view_maxIntegratortoolbar(App *app, Event *e)
{
    textview_printf(app->text, "View->maxIntegrator Toolbar Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    /* alternate the status of the button */
    app->view_maxIntegratorToolbar_IsShown = !app->view_maxIntegratorToolbar_IsShown;
    if (app->view_maxIntegratorToolbar_IsShown) {
        /* show the tick */
        menuitem_state(app->view_maxIntegratorToolbar, ekGUI_ON);

        /* show all the flat buttons */


    } else {
        /* hide the tick */
        menuitem_state(app->view_maxIntegratorToolbar, ekGUI_OFF);

        /* hide all the flat buttons */
    }

    layout_update(app->buttonLayout);
    unref(e);

}
void i_OnClick_menu_view_maxAdaptertoolbar(App *app, Event *e)
{
    textview_printf(app->text, "View->maxAdapter Toolbar Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    /* alternate the status of the button */
    app->view_maxAdapterToolbar_IsShown = !app->view_maxAdapterToolbar_IsShown;
    if (app->view_maxAdapterToolbar_IsShown) {
        /* show the tick */
        menuitem_state(app->view_maxAdapterToolbar, ekGUI_ON);

        /* show all the flat buttons */


    } else {
        /* hide the tick */
        menuitem_state(app->view_maxAdapterToolbar, ekGUI_OFF);

        /* hide all the flat buttons */
    }

    layout_update(app->buttonLayout);
    unref(e);

}
void i_OnClick_menu_view_maxGatetoolbar(App *app, Event *e)
{
    textview_printf(app->text, "View->maxGate Toolbar Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    /* alternate the status of the button */
    app->view_maxGateToolbar_IsShown = !app->view_maxGateToolbar_IsShown;
    if (app->view_maxGateToolbar_IsShown) {
        /* show the tick */
        menuitem_state(app->view_maxGateToolbar, ekGUI_ON);

        /* show all the flat buttons */


    } else {
        /* hide the tick */
        menuitem_state(app->view_maxGateToolbar, ekGUI_OFF);

        /* hide all the flat buttons */
    }

    layout_update(app->buttonLayout);
    unref(e);

}

void i_OnClick_menu_view_maxScaletoolbar(App *app, Event *e)
{
    textview_printf(app->text, "View->maxScale Toolbar Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    /* alternate the status of the button */
    app->view_maxScaleToolbar_IsShown = !app->view_maxScaleToolbar_IsShown;
    if (app->view_maxScaleToolbar_IsShown) {
        /* show the tick */
        menuitem_state(app->view_maxScaleToolbar, ekGUI_ON);

        /* show all the flat buttons */


    } else {
        /* hide the tick */
        menuitem_state(app->view_maxScaleToolbar, ekGUI_OFF);

        /* hide all the flat buttons */
    }

    layout_update(app->buttonLayout);
    unref(e);

}
void i_OnClick_menu_view_maxOrchestratortoolbar(App *app, Event *e)
{
    textview_printf(app->text, "View->maxOrchestrator Toolbar Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    /* alternate the status of the button */
    app->view_maxOrchestratorToolbar_IsShown = !app->view_maxOrchestratorToolbar_IsShown;
    if (app->view_maxOrchestratorToolbar_IsShown) {
        /* show the tick */
        menuitem_state(app->view_maxOrchestratorToolbar, ekGUI_ON);

        /* show all the flat buttons */


    } else {
        /* hide the tick */
        menuitem_state(app->view_maxOrchestratorToolbar, ekGUI_OFF);

        /* hide all the flat buttons */
    }

    layout_update(app->buttonLayout);
    unref(e);

}
void i_OnClick_menu_view_maxMindtoolbar(App *app, Event *e)
{
    textview_printf(app->text, "View->maxMind Toolbar Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    /* alternate the status of the button */
    app->view_maxMindToolbar_IsShown = !app->view_maxMindToolbar_IsShown;
    if (app->view_maxMindToolbar_IsShown) {
        /* show the tick */
        menuitem_state(app->view_maxMindToolbar, ekGUI_ON);

        /* show all the flat buttons */


    } else {
        /* hide the tick */
        menuitem_state(app->view_maxMindToolbar, ekGUI_OFF);

        /* hide all the flat buttons */
    }

    layout_update(app->buttonLayout);
    unref(e);

}
void i_OnClick_menu_view_maxLicensetoolbar(App *app, Event *e)
{
    textview_printf(app->text, "View->maxLicense Toolbar Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    /* alternate the status of the button */
    app->view_maxLicenseToolbar_IsShown = !app->view_maxLicenseToolbar_IsShown;
    if (app->view_maxLicenseToolbar_IsShown) {
        /* show the tick */
        menuitem_state(app->view_maxLicenseToolbar, ekGUI_ON);

        /* show all the flat buttons */


    } else {
        /* hide the tick */
        menuitem_state(app->view_maxLicenseToolbar, ekGUI_OFF);

        /* hide all the flat buttons */
    }

    layout_update(app->buttonLayout);
    unref(e);

}

void i_OnClick_menu_view_maxServicestoolbar(App *app, Event *e)
{
    textview_printf(app->text, "View->maxServices Toolbar Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    /* alternate the status of the button */
    app->view_maxServicesToolbar_IsShown = !app->view_maxServicesToolbar_IsShown;
    if (app->view_maxServicesToolbar_IsShown) {
        /* show the tick */
        menuitem_state(app->view_maxServicesToolbar, ekGUI_ON);

        /* show all the flat buttons */


    } else {
        /* hide the tick */
        menuitem_state(app->view_maxServicesToolbar, ekGUI_OFF);

        /* hide all the flat buttons */
    }

    layout_update(app->buttonLayout);
    unref(e);

}


void i_OnClick_menu_view_documenttoolbar(App *app, Event *e)
{
    textview_printf(app->text, "View->Document Toolbar  Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    /* alternate the status of the button */
    app->view_documentToolbar_IsShown = !app->view_documentToolbar_IsShown;
    if (app->view_documentToolbar_IsShown) {
        /* show the tick */
        menuitem_state(app->view_documentToolbar, ekGUI_ON);

        /* show all the flat buttons */


    } else {
        /* hide the tick */
        menuitem_state(app->view_documentToolbar, ekGUI_OFF);

        /* hide all the flat buttons */
    }

    layout_update(app->buttonLayout);
    unref(e);

}

void i_OnClick_menu_maxengine_oneclickstart(App *app, Event *e)
{
    textview_printf(app->text, "maxEngine->Start Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    maxEngineOneClickStart(app, app->window);

    unref(e);
}

void i_OnClick_menu_maxengine_oneclickstop(App *app, Event *e)
{
    textview_printf(app->text, "maxEngine->Stop Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    maxEngineOneClickStop(app, app->window);

    unref(e);
}

void i_OnClick_menu_maxengine_viewstatistics(App *app, Event *e)
{
    textview_printf(app->text, "maxEngine->View Statistics Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    unref(e);
}

void i_OnClick_menu_maxengine_viewlivelogs(App *app, Event *e)
{
    textview_printf(app->text, "maxEngine->View Live Logs Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    /* alternate the status of the button */
    app->maxEngine_viewLiveLogs_IsShown = !app->maxEngine_viewLiveLogs_IsShown;
    if (app->maxEngine_viewLiveLogs_IsShown) {
        /* show the tick */
        menuitem_state(app->maxEngine_ViewLiveLogs, ekGUI_ON);

        /* show all the flat buttons */


    } else {
        /* hide the tick */
        menuitem_state(app->maxEngine_ViewLiveLogs, ekGUI_OFF);

        /* hide all the flat buttons */
    }

    unref(e);

}

/**/

void i_OnClick_menu_maxadapter_start(App *app, Event *e)
{
    textview_printf(app->text, "maxAdapter->Start Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    if (menuitem_get_state(app->maxAdapter_Start) == ekGUI_OFF) {
    	maxAdapterStart(app, app->window);
    	progress_undefined(app->bar, TRUE);
    }

    menuitem_state(app->maxAdapter_Start, ekGUI_ON);
    menuitem_state(app->maxAdapter_Stop, ekGUI_OFF);


}

void i_OnClick_menu_maxadapter_stop(App *app, Event *e)
{
    textview_printf(app->text, "maxAdapter->Stop Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    if (menuitem_get_state(app->maxAdapter_Stop) == ekGUI_OFF) {
    	maxAdapterStop(app, app->window);
    	progress_undefined(app->bar, FALSE);
    }

    menuitem_state(app->maxAdapter_Start, ekGUI_OFF);
    menuitem_state(app->maxAdapter_Stop, ekGUI_ON);

}

void i_OnClick_menu_maxadapter_alarmsandconditions(App *app, Event *e)
{
    textview_printf(app->text, "maxAdapter->Alarms&Conditions Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    maxAdapterAlarmsAndConditions(app, app->window);

    unref(e);
}

void i_OnClick_menu_maxadapter_events(App *app, Event *e)
{
    textview_printf(app->text, "maxAdapter->Events Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    maxAdapterEvents(app, app->window);

    unref(e);
}

void i_OnClick_menu_maxadapter_logsmanagement(App *app, Event *e)
{
    textview_printf(app->text, "maxAdapter->Logs Management Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    maxAdapterLogsManagement(app, app->window);

    unref(e);
}

void i_OnClick_menu_maxadapter_reverseconnect(App *app, Event *e)
{
    textview_printf(app->text, "maxAdapter->Reverse Connect Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    maxAdapterReverseConnect(app, app->window);

    unref(e);
}

void i_OnClick_menu_maxadapter_startupparameters(App *app, Event *e)
{
    textview_printf(app->text, "maxAdapter->Startup Parameters Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    maxAdapterStartupParameters(app, app->window);

    unref(e);
}

void i_OnClick_menu_maxadapter_communications(App *app, Event *e)
{
    textview_printf(app->text, "maxAdapter->Communications Protocol Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    maxAdapterCommunicationsProtocol(app, app->window);

    unref(e);

}

void i_OnClick_menu_maxadapter_viewstatistics(App *app, Event *e)
{
    textview_printf(app->text, "maxAdapter->View Statistics Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    maxAdapterViewStatistics(app, app->window);

    unref(e);
}

void i_OnClick_menu_maxadapter_viewlivelogs(App *app, Event *e)
{
    textview_printf(app->text, "maxAdapter->View Live Logs Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

     /* alternate the status of the button */
    app->maxAdapter_viewLiveLogs_IsShown = !app->maxAdapter_viewLiveLogs_IsShown;
    if (app->maxAdapter_viewLiveLogs_IsShown) {
        /* show the tick */
        menuitem_state(app->maxAdapter_ViewLiveLogs, ekGUI_ON);

        /* show all the flat buttons */


	// start the journal
    	maxAdapterViewLiveLogs(app, app->window, TRUE);

    } else {
        /* hide the tick */
        menuitem_state(app->maxAdapter_ViewLiveLogs, ekGUI_OFF);


	// stop the journal
	maxAdapterViewLiveLogs(app, app->window, FALSE);
    }


    unref(e);
}

void i_OnClick_menu_maxadapter_discoverdevices(App *app, Event *e)
{
    textview_printf(app->text, "maxAdapter->Discover Devices Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    maxAdapterDiscoverDevices(app, app->window);

    unref(e);

}


void i_OnClick_menu_maxadapter_autogenerate(App *app, Event *e)
{
    textview_printf(app->text, "maxAdapter->Auto generate Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    maxAdapterAutoGenerate(app, app->window);

    unref(e);

}

void i_OnClick_menu_maxadapter_nodeseteditor(App *app, Event *e)
{
    textview_printf(app->text, "maxAdapter->Edit device nodeset Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    maxAdapterNodesetEditor(app, app->window);

    unref(e);

}

void i_OnClick_menu_maxadapter_simrun(App *app, Event *e)
{
    textview_printf(app->text, "maxAdapter->Simulate and connect Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    maxAdapterSimRun(app, app->window);

    unref(e);

}


void i_OnClick_menu_maxadapter_manualconfiguration(App *app, Event *e)
{
    textview_printf(app->text, "maxAdapter->Manual Configuration Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    maxAdapterManualConfiguration(app, app->window);

    unref(e);
}

/**/

void i_OnClick_menu_maxcore_viewlivelogs(App *app, Event *e)
{
    textview_printf(app->text, "maxCore->View Live Logs Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    maxCoreViewLiveLogs(app, app->window);

     /* alternate the status of the button */
    app->maxCore_viewLiveLogs_IsShown = !app->maxCore_viewLiveLogs_IsShown;
    if (app->maxCore_viewLiveLogs_IsShown) {
        /* show the tick */
        menuitem_state(app->maxCore_ViewLiveLogs, ekGUI_ON);

        /* show all the flat buttons */


    } else {
        /* hide the tick */
        menuitem_state(app->maxCore_ViewLiveLogs, ekGUI_OFF);

        /* hide all the flat buttons */
    }

    unref(e);

}

/**/
void i_OnClick_menu_maxServices_usersaccount(App *app, Event *e)
{
    textview_printf(app->text, "maxService->Users Account Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    maxServicesUsersAccount(app, app->window);

    unref(e);
}

void i_OnClick_menu_maxServices_systemsaccount(App *app, Event *e)
{
    textview_printf(app->text, "maxServices->Systems Account Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    maxServicesSystemsAccount(app, app->window);

    unref(e);
}

void i_OnClick_menu_maxServices_generatesslcertificates(App *app, Event *e)
{
    textview_printf(app->text, "maxServices->Generate SSL Cetificates Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    maxServicesGenerateSSLCertificates(app, app->window);

    unref(e);
}

void i_OnClick_menu_maxCore_registermaxadapters(App *app, Event *e)
{
    textview_printf(app->text, "maxCore->Register maxAdapters Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    maxCoreRegisterAdapters(app, app->window);

    unref(e);

}



/**/

void i_OnClick_menu_maxIntegrator_start(App *app, Event *e)
{
    textview_printf(app->textMaxIntegrator, "maxIntegrator->Start Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->textMaxIntegrator);
    app->clicks += 1;
    maxIntegratorStart(app, app->window);
    progress_undefined(app->bar, TRUE);
}

void i_OnClick_menu_maxIntegrator_stop(App *app, Event *e)
{
    textview_printf(app->textMaxIntegrator, "maxIntegrator->Stop Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->textMaxIntegrator);
    app->clicks += 1;
    maxIntegratorStop(app, app->window);
    progress_undefined(app->bar, FALSE);
    progress_value(app->bar, 0.0);
}

void i_OnClick_menu_maxIntegrator_radiusservice(App *app, Event *e)
{
    textview_printf(app->textMaxIntegrator, "maxIntegrator->Radius Server Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->textMaxIntegrator);
    app->clicks += 1;
    maxIntegratorRadiusServer(app, app->window);

    unref(e);

}

void i_OnClick_menu_maxIntegrator_ldapservice(App *app, Event *e)
{
    textview_printf(app->textMaxIntegrator, "maxIntegrator->Ldap Server Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->textMaxIntegrator);
    app->clicks += 1;
    maxIntegratorLdapServer(app, app->window);

    unref(e);

}

void i_OnClick_menu_maxIntegrator_iamservice(App *app, Event *e)
{
    textview_printf(app->textMaxIntegrator, "maxIntegrator->Identity & Access Server Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->textMaxIntegrator);
    app->clicks += 1;
    maxIntegratorIAMServer(app, app->window);

    unref(e);

}

void i_OnClick_menu_maxIntegrator_syslogservice(App *app, Event *e)
{
    textview_printf(app->textMaxIntegrator, "maxIntegrator->Syslog Server Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->textMaxIntegrator);
    app->clicks += 1;
    maxIntegratorSyslogServer(app, app->window);

    unref(e);

}


void i_OnClick_menu_maxAdapter_historianservice(App *app, Event *e)
{
    textview_printf(app->textMaxAdapter, "maxAdapter->Historian Server Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->textMaxAdapter);
    app->clicks += 1;
    maxAdapterHistorianServer(app, app->window);

    unref(e);
}

void i_OnClick_menu_maxIntegrator_viewstatistics(App *app, Event *e)
{
    textview_printf(app->textMaxIntegrator, "maxIntegrator->View Statistics Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->textMaxIntegrator);
    app->clicks += 1;
    maxIntegratorViewStatistics(app, app->window);

    unref(e);
}

void i_OnClick_menu_maxIntegrator_viewlivelogs(App *app, Event *e)
{
    textview_printf(app->textMaxIntegrator, "maxIntegrator->View Live Logs Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->textMaxIntegrator);
    app->clicks += 1;
    maxIntegratorViewLiveLogs(app, app->window);

     /* alternate the status of the button */
    app->maxIntegrator_viewLiveLogs_IsShown = !app->maxIntegrator_viewLiveLogs_IsShown;
    if (app->maxIntegrator_viewLiveLogs_IsShown) {
        /* show the tick */
        menuitem_state(app->maxIntegrator_ViewLiveLogs, ekGUI_ON);

        /* show all the flat buttons */


    } else {
        /* hide the tick */
        menuitem_state(app->maxIntegrator_ViewLiveLogs, ekGUI_OFF);

        /* hide all the flat buttons */
    }

    unref(e);

}

void i_OnClick_menu_maxIntegrator_amqpservice(App *app, Event *e)
{
    textview_printf(app->textMaxIntegrator, "maxIntegrator->Rabbit AMQP Server Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->textMaxIntegrator);
    app->clicks += 1;
    maxIntegratorRabbitAqmpServer(app, app->window);

    unref(e);

}

void i_OnClick_menu_maxIntegrator_mqttservice(App *app, Event *e)
{
    textview_printf(app->textMaxIntegrator, "maxIntegrator->Message Broker Server Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->textMaxIntegrator);
    app->clicks += 1;
    maxIntegratorMqttServer(app, app->window);

    unref(e);

}


void i_OnClick_menu_maxIntegrator_webapiservice(App *app, Event *e)
{
    textview_printf(app->textMaxIntegrator, "maxIntegrator->WebAPI Server Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->textMaxIntegrator);
    app->clicks += 1;
    maxIntegratorWebAPIServer(app, app->window);

    unref(e);

}

void i_OnClick_menu_maxIntegrator_websocketservice(App *app, Event *e)
{
    textview_printf(app->textMaxIntegrator, "maxIntegrator->WebSocket Server Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->textMaxIntegrator);
    app->clicks += 1;
    maxIntegratorWebSocketServer(app, app->window);

    unref(e);

}

void i_OnClick_menu_maxIntegrator_proxyservice(App *app, Event *e)
{
    textview_printf(app->textMaxIntegrator, "maxIntegrator->Proxy Server Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->textMaxIntegrator);
    app->clicks += 1;
    maxIntegratorProxyServer(app, app->window);

    unref(e);

}

void i_OnClick_menu_maxIntegrator_opcuaservice(App *app, Event *e)
{
    textview_printf(app->textMaxIntegrator, "maxIntegrator->OPCUA Server Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->textMaxIntegrator);
    app->clicks += 1;
    maxIntegratorOPCUAServer(app, app->window);

    unref(e);

}

void i_OnClick_menu_maxIntegrator_gdsservice(App *app, Event *e)
{
    textview_printf(app->textMaxIntegrator, "maxIntegrator->Global Directory Server Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->textMaxIntegrator);
    app->clicks += 1;
    maxIntegratorGDSServer(app, app->window);

    unref(e);

}

void i_OnClick_menu_maxIntegrator_ldsservice(App *app, Event *e)
{
    textview_printf(app->textMaxIntegrator, "maxIntegrator->Local Directory Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->textMaxIntegrator);
    app->clicks += 1;
    maxIntegratorLDSServer(app, app->window);

    unref(e);

}

/**/
void i_OnClick_menu_maxscale_instancesetup(App *app, Event *e)
{
    textview_printf(app->text, "maxScale->Setup Instance Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    maxScaleSetupInstance(app, app->window);

    unref(e);

}


void i_OnClick_menu_maxscale_configuration(App *app, Event *e)
{
    textview_printf(app->text, "maxScale->Configuration Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    maxScaleConfiguration(app, app->window);

    unref(e);

}

void i_OnClick_menu_maxOrchestrator_start(App *app, Event *e)
{
    textview_printf(app->text, "maxOrchestrator->Start Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->textMaxOrchestrator);
    app->clicks += 1;
    maxOrchestratorStart(app, app->window);

    unref(e);

}

void i_OnClick_menu_maxOrchestrator_stop(App *app, Event *e)
{
    textview_printf(app->textMaxOrchestrator, "maxOrchestrator->Stop Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->textMaxOrchestrator);
    app->clicks += 1;
    maxOrchestratorStop(app, app->window);

    unref(e);

}

void i_OnClick_menu_maxOrchestrator_defineDataflow(App *app, Event *e)
{
    textview_printf(app->textMaxOrchestrator, "maxOrchestrator->Define dataflow Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->textMaxOrchestrator);
    app->clicks += 1;
    maxOrchestratorDefineDataflow(app, app->window);

    unref(e);

}


void i_OnClick_menu_maxmind_digitaltwin(App *app, Event *e)
{
    textview_printf(app->text, "maxMind->Digital Twin Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    maxMindDigitalTwin(app, app->window);

    unref(e);

}


void i_OnClick_menu_maxmind_analytics(App *app, Event *e)
{
    textview_printf(app->text, "maxMind->Real time Analytics Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    maxMindRealTimeAnalytics(app, app->window);

    unref(e);

}


void i_OnClick_menu_maxmind_machinelearning(App *app, Event *e)
{
    textview_printf(app->text, "maxMind->Machine Learning Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    maxMindMachineLearning(app, app->window);

    unref(e);

}


void i_OnClick_menu_maxgate_start(App *app, Event *e)
{
    textview_printf(app->text, "maxGate->Start Instance Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    maxGateStartInstance(app, app->window);

    unref(e);

}


void i_OnClick_menu_maxgate_stop(App *app, Event *e)
{
    textview_printf(app->text, "maxGate->Stop Instance Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    maxGateStopInstance(app, app->window);

    unref(e);

}


void i_OnClick_menu_maxgate_inspect(App *app, Event *e)
{
    textview_printf(app->text, "maxGate->Inspect Instance Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    maxGateInspectInstance(app, app->window);

    unref(e);

}


void i_OnClick_menu_maxgate_manualconfiguration_add(App *app, Event *e)
{
    textview_printf(app->text, "maxGate->Manual Configuration Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    maxGateManualConfiguration(app, app->window);

    unref(e);

}

void i_OnClick_menu_maxLicense_activate(App *app, Event *e)
{


}

void i_OnClick_menu_maxLicense_inspect(App *app, Event *e)
{


}

void i_OnClick_menu_maxLicense_request(App *app, Event *e)
{



}


void i_OnClick_menu_maxservices_usersaccount(App *app, Event *e)
{
    textview_printf(app->text, "maxServices->Users Account Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

}

void i_OnClick_menu_maxservices_systemsaccount(App *app, Event *e)
{
    textview_printf(app->text, "maxServices->Systems Account Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;


}

void i_OnClick_menu_maxservices_generatesslcertificates(App *app, Event *e)
{

    textview_printf(app->text, "maxServices->Generate SSL certificate Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

}


void i_OnClick_client_add(App *app, Event *e)
{
    textview_printf(app->text, "client->Add Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    ClientAdd(app, app->window);

    unref(e);
}

void i_OnClick_client_remove(App *app, Event *e)
{
    textview_printf(app->text, "client->Remove Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    ClientRemove(app, app->window);

    unref(e);
}

void i_OnClick_client_connect(App *app, Event *e)
{
    textview_printf(app->text, "client->Connect Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    ClientConnect(app, app->window);

    unref(e);
}

void i_OnClick_client_disconnect(App *app, Event *e)
{
    textview_printf(app->text, "client->Disconnect Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    ClientDisconnect(app, app->window);

    unref(e);
}

void i_OnClick_client_properties(App *app, Event *e)
{
    textview_printf(app->text, "client->Properties Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    ClientProperties(app, app->window);

    unref(e);
}

void i_OnClick_client_changeuser(App *app, Event *e)
{
    textview_printf(app->text, "client->Change User Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;
    ClientChangeUser(app, app->window);

    unref(e);
}

void i_OnClick_client_changepassword(App *app, Event *e)
{
    textview_printf(app->text, "client->Change Password Menu click (%d)\n", app->clicks);
    app->clicks += 1;
    textview_scroll_caret(app->text);
    ClientChangePassword(app, app->window);

    unref(e);
}

void i_OnClick_server_start(App *app, Event *e)
{
    textview_printf(app->text, "server->Start Menu click (%d)\n", app->clicks);
    app->clicks += 1;
    textview_scroll_caret(app->text);
    ServerStart(app, app->window);

    unref(e);
}

void i_OnClick_server_stop(App *app, Event *e)
{
    textview_printf(app->text, "server->Stop Menu click (%d)\n", app->clicks);
    app->clicks += 1;
    textview_scroll_caret(app->text);
    ServerStop(app, app->window);

    unref(e);
}

void i_OnClick_server_properties(App *app, Event *e)
{
    textview_printf(app->text, "server->Properties Menu click (%d)\n", app->clicks);
    app->clicks += 1;
    textview_scroll_caret(app->text);
    ServerProperties(app, app->window);

    unref(e);
}

void i_OnClick_server_adduser(App *app, Event *e)
{
    textview_printf(app->text, "server->Add User  Menu click (%d)\n", app->clicks);
    app->clicks += 1;
    textview_scroll_caret(app->text);
    ServerAdduser(app, app->window);

    unref(e);
}

void i_OnClick_server_edituser(App *app, Event *e)
{
    textview_printf(app->text, "server->Edit User Menu click (%d)\n", app->clicks);
    app->clicks += 1;
    textview_scroll_caret(app->text);
    ServerEdituser(app, app->window);

    unref(e);
}

void i_OnClick_document_add(App *app, Event *e)
{
    textview_printf(app->text, "Document->Add Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    unref(e);

}

void i_OnClick_document_remove(App *app, Event *e)
{
    textview_printf(app->text, "Document->Remove Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    unref(e);

}

void i_OnClick_document_hide_unhide(App *app, Event *e)
{
    textview_printf(app->text, "Document->Hide/ Unhide all dock widgets Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    unref(e);

}

void i_OnClick_settings_plugins(App *app, Event *e)
{
    textview_printf(app->text, "Settings->Plugins Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    unref(e);

}

void i_OnClick_settings_configure_OPCSvr(App *app, Event *e)
{
    textview_printf(app->text, "Settings->Configure->OPCSvr Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    unref(e);

}

void i_OnClick_settings_configure_LDS(App *app, Event *e)
{
    textview_printf(app->text, "Settings->Configure->LDS Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    unref(e);
}

void i_OnClick_settings_configure_GDS(App *app, Event *e)
{
    textview_printf(app->text, "Settings->Configure->GDS Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    unref(e);
}

void i_OnClick_settings_interfaces_modbusTCP(App *app, Event *e)
{
    textview_printf(app->text, "Settings->Interfaces->modbusTCP Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    interfacesModbusTCP(app, app->window);
    unref(e);

}

void i_OnClick_settings_interfaces_modbusRTU(App *app, Event *e)
{
    textview_printf(app->text, "Settings->Interfaces->modbusRTU click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    interfacesModbusRTU(app, app->window);
    unref(e);

}

void i_OnClick_settings_interfaces_EtherCAT(App *app, Event *e)
{
#ifdef INFO
etherlab.org
#endif
    textview_printf(app->text, "Settings->Interfaces->EtherCAT click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    interfacesEtherCAT(app, app->window);
    unref(e);

}

void i_OnClick_settings_interfaces_TwinCATADS(App *app, Event *e)
{
#ifdef INFO
github.com/Beckhoff/ADS
#endif
    textview_printf(app->text, "Settings->Interfaces->TwinCAT ADS click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    interfacesTwinCATADS(app, app->window);
    unref(e);

}

void i_OnClick_settings_interfaces_EthernetIP(App *app, Event *e)
{
#ifdef INFO
github.ccom/nimbuscontrols/EIPScanner
#endif

    textview_printf(app->text, "Settings->Interfaces->Ethernet/IP click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    interfacesEthernetIP(app, app->window);
    unref(e);
}

void i_OnClick_settings_interfaces_ProfiNet(App *app, Event *e)
{
#ifdef INFO
github.com/rtlabs-com/p-net
#endif

    textview_printf(app->text, "Settings->Interfaces->Ethernet/IP click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    interfacesProfiNet(app, app->window);
    unref(e);
}


void i_OnClick_settings_configure_message_broker(App *app, Event *e)
{
    textview_printf(app->text, "Settings->Configure->MSB Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    unref(e);


}

void i_OnClick_settings_managecertificates(App *app, Event *e)
{
    textview_printf(app->text, "Settings->Manage Certificates Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    unref(e);

}

void i_OnClick_menu_help_manual(App *app, Event *e)
{
    textview_printf(app->text, "Help->Manual Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    unref(e);

}

void i_OnClick_menu_help_whatsthis(App *app, Event *e)
{
    textview_printf(app->text, "Help->What's This? Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    unref(e);

}

void i_OnClick_menu_help_licensestatus(App *app, Event *e)
{
    textview_printf(app->text, "Help->License Status Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    unref(e);

}

void i_OnClick_menu_help_checkforupdates(App *app, Event *e)
{
    textview_printf(app->text, "Help->Check for UpdatesMenu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    unref(e);

}

void i_OnClick_menu_help_about(App *app, Event *e)
{
    textview_printf(app->text, "Help->About Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->text);
    app->clicks += 1;

    helpAbout(app, app->window);
    unref(e);

}

void createMenus(App *app)
{
    Menu *topmenu;
    /* *view */
    MenuItem *project, *client, *server, *document, *settings, *toolbars, *help;
    MenuItem *maxEngine, *maxCore, *maxIntegrator, *maxAdapter, *maxScale, *maxOrchestrator, *maxMind, *maxGate, *maxLicense, *maxServices;
    /* *submenu_view */
    Menu *submenu_project, *submenu_client, *submenu_server, *submenu_document, *submenu_settings, *submenu_toolbars, *submenu_help;
    Menu *submenu_maxEngine, *submenu_maxCore, *submenu_maxIntegrator, *submenu_maxAdapter, *submenu_maxScale, *submenu_maxOrchestrator;
    Menu *submenu_maxMind, *submenu_maxGate, *submenu_maxLicense, *submenu_maxServices;
    Menu *submenu_settings_configure, *submenu_settings_interfaces;

    MenuItem *project_new, *project_open, *project_save, *project_saveAs, *project_recentprojects, *project_separator, *project_close, *project_quit;
    /* the following menuitems view->XXX  are declared in app */
    MenuItem *view_separator; /* *view_project, *view_addressspace, *view_log, *view_attributes, *view_references, *view_documenttoolbar;*/
    MenuItem *client_add, *client_remove, *client_connect, *client_disconnect, *client_properties, *client_separator, *client_changeuser, *client_changepassword;
    MenuItem *server_start, *server_stop, *server_properties, *server_separator, *server_adduser, *server_edituser;
    MenuItem *document_add, *document_remove, *document_hide_unhide;
    MenuItem *settings_plugins, *settings_configure, *settings_interfaces, *settings_separator, *settings_managecertificates;
    MenuItem *help_manual, *help_whatsthis, *help_licensestatus, *help_checkforupdates, *help_separator, *help_about;
    MenuItem *toolbar_separator;

    MenuItem *maxEngine_Start, *maxEngine_Stop, *maxEngine_ViewStatistics;
    MenuItem *maxEngine_separator;

    MenuItem *maxCore_Start, *maxCore_Stop, *maxCore_separator;
    MenuItem *maxCore_RegisterMaxAdapters, *maxCore_LogsManagement, *maxCore_StartupParameters, *maxCore_ViewStatistics, *maxCore_WebSocketService;

    MenuItem *maxAdapter_HistorianService, *maxAdapter_AlarmsAndConditions, *maxAdapter_Events, *maxAdapter_LogsManagement, *maxAdapter_ReverseConnect;
    MenuItem *maxAdapter_StartupParameters, *maxAdapter_Communications, *maxAdapter_ViewStatistics, *maxAdapter_WebSocketService;
    MenuItem *maxAdapter_Discovery, *maxAdapter_Generate, *maxAdapter_SimRun, *maxAdapter_NodesetEditor, *maxAdapter_ManualConfiguration;
    MenuItem *maxAdapter_separator, *maxAdapter_separator1, *maxAdapter_separator2, *maxAdapter_separator3, *maxAdapter_separator4;

    MenuItem *maxIntegrator_Start, *maxIntegrator_Stop;
    MenuItem *maxIntegrator_RadiusService, *maxIntegrator_LdapService, *maxIntegrator_IamService, *maxIntegrator_SyslogService;
    MenuItem *maxIntegrator_separator, *maxIntegrator_separator1, *maxIntegrator_separator2, *maxIntegrator_separator3;
    MenuItem *maxIntegrator_AmqpService, *maxIntegrator_MqttService, *maxIntegrator_WebapiService, *maxIntegrator_WebsocketService, *maxIntegrator_ProxyService;
    MenuItem *maxIntegrator_OpcUAService, *maxIntegrator_GdsService, *maxIntegrator_LdsService;
    MenuItem *maxIntegrator_ViewStatistics;

    MenuItem *maxScale_InstanceSetup, *maxScale_Configuration;
    MenuItem *maxOrchestrator_Start, *maxOrchestrator_Stop, *maxOrchestrator_DefineFlow, *maxOrchestrator_separator;

    MenuItem *maxLicense_Activate, *maxLicense_Inspect, *maxLicense_Request;
    MenuItem *maxMind_DigitalTwin, *maxMind_Analytics, *maxMind_MachineLearning;
    MenuItem *maxGate_Start, *maxGate_Stop, *maxGate_Inspect, *maxGate_separator, *maxGate_ManualConfiguration;
    MenuItem *maxServices_GenerateSSLCertificates, *maxServices_UsersAccount, *maxServices_SystemsAccount;
    MenuItem *configure_OPCSvr, *configure_LDS, *configure_GDS, *configure_MSB;
    MenuItem *interfaces_modbusTCP, *interfaces_modbusRTU, *interfaces_EtherCAT, *interfaces_TwinCATADS, *interfaces_EthernetIP, *interfaces_ProfiNet;

    Image *image_project_new, *image_project_open, *image_project_save, *image_project_saveAs, *image_project_close, *image_project_quit;
    Image *image_view_interconnectivity, *image_view_project, *image_view_addressspace, *image_view_log, *image_view_attributes, *image_view_references;
    Image *image_view_maxAdapter, *image_view_maxGate, *image_view_maxIntegrator;
    Image *image_view_fileToolbar, *image_view_viewToolbar, *image_view_documentToolbar;
    Image *image_view_maxEngineToolbar, *image_view_maxCoreToolbar, *image_view_maxIntegratorToolbar, *image_view_maxAdapterToolbar, *image_view_maxGateToolbar;
    Image *image_view_maxScaleToolbar, *image_view_maxOrchestratorToolbar;
    Image *image_view_maxMindToolbar, *image_view_maxLicenseToolbar, *image_view_maxServicesToolbar;
    Image *image_maxEngine_start, *image_maxEngine_stop, *image_maxEngine_viewstatistics, *image_maxEngine_viewlivelogs;

    Image *image_maxCore_start, *image_maxCore_stop, *image_maxCore_registermaxadapters, *image_maxCore_logsmanagement, *image_maxCore_startupparameters;
    Image  *image_maxCore_viewstatistics, *image_maxCore_viewlivelogs, *image_maxCore_websocketservice;

    Image *image_maxAdapter_historianservice, *image_maxAdapter_alarmsandconditions, *image_maxAdapter_events, *image_maxAdapter_logsmanagement, *image_maxAdapter_reverseconnect;
    Image *image_maxAdapter_usersaccount, *image_maxAdapter_systemsaccount;
    Image *image_maxAdapter_generatesslcertificates, *image_maxAdapter_registermaxadapters, *image_maxAdapter_startupparameters, *image_maxAdapter_communications;
    Image *image_maxAdapter_viewstatistics, *image_maxAdapter_viewlivelogs;

    Image *image_maxIntegrator_start, *image_maxIntegrator_stop;
    Image *image_maxIntegrator_radiusservice, *image_maxIntegrator_ldapservice, *image_maxIntegrator_iamservice, *image_maxIntegrator_syslogservice;
    Image *image_maxIntegrator_amqpservice, *image_maxIntegrator_mqttservice, *image_maxIntegrator_webapiservice, *image_maxIntegrator_websocketservice;
    Image *image_maxIntegrator_proxyservice, *image_maxIntegrator_gdsservice, *image_maxIntegrator_ldsservice, *image_maxIntegrator_opcuaservice;
    Image *image_maxIntegrator_viewstatistics, *image_maxIntegrator_viewlivelogs;
    Image *image_maxAdapter_start, *image_maxAdapter_stop, *image_maxAdapter_websocketservice;
    Image *image_maxAdapter_discover, *image_maxAdapter_generate, *image_maxAdapter_simrun, *image_maxAdapter_nodeseteditor, *image_maxAdapter_manualconfiguration;
    Image *image_maxScale_instancesetup, *image_maxScale_configuration;
    Image *image_maxOrchestrator_start, *image_maxOrchestrator_stop, *image_maxOrchestrator_defineflow;
    Image *image_maxMind_digitaltwin, *image_maxMind_analytics, *image_maxMind_machinelearning;
    Image *image_maxGate_start, *image_maxGate_stop, *image_maxGate_inspect, *image_maxGate_manualconfiguration;
    Image *image_maxLicense_activate, *image_maxLicense_inspect, *image_maxLicense_request;
    Image *image_maxServices_usersaccount, *image_maxServices_systemsaccount, *image_maxServices_generatesslcertificates;
    Image *image_help_manual, *image_help_whatsthis, *image_help_licensestatus, *image_help_checkforupdates, *image_help_about;

/* step 1 */
    /* create top level menu */
    topmenu = menu_create();
    app->top_menu = topmenu;

    osapp_menubar(topmenu, app->window);

    project = menuitem_create();
    app->view = menuitem_create();
    maxEngine = menuitem_create();
    maxCore = menuitem_create();
    maxIntegrator = menuitem_create();
    maxAdapter = menuitem_create();
    maxScale = menuitem_create();
    maxMind = menuitem_create();
    maxGate = menuitem_create();
    maxOrchestrator = menuitem_create();
    maxLicense = menuitem_create();
    maxServices = menuitem_create();
    client = menuitem_create();
    server = menuitem_create();
    document = menuitem_create();
    settings = menuitem_create();
    toolbars = menuitem_create();
    help = menuitem_create();

    /* set keyboard shortcut */
    menuitem_key(project, ekKEY_F, ekMKEY_ALT);
    menuitem_key(app->view, ekKEY_V, ekMKEY_ALT);
    menuitem_key(maxEngine, ekKEY_E, ekMKEY_ALT);
    menuitem_key(maxIntegrator, ekKEY_I, ekMKEY_ALT);
    menuitem_key(maxAdapter, ekKEY_A, ekMKEY_ALT);
    menuitem_key(maxScale, ekKEY_S, ekMKEY_ALT);
    menuitem_key(maxMind, ekKEY_M, ekMKEY_ALT);
    menuitem_key(maxGate, ekKEY_G, ekMKEY_ALT);
    menuitem_key(maxOrchestrator, ekKEY_O, ekMKEY_ALT);
    menuitem_key(maxLicense, ekKEY_L, ekMKEY_ALT);
    menuitem_key(help, ekKEY_H, ekMKEY_ALT);

    /* label the menu items */
    menuitem_text(project, "Project");
    menuitem_text(app->view, "View");
    menuitem_text(maxEngine, "maxEngine");
    menuitem_text(maxAdapter, "maxAdapter");
    menuitem_text(maxCore, "maxCore");
    menuitem_text(maxIntegrator, "maxIntegrator");
    menuitem_text(maxScale, "maxScale");
    menuitem_text(maxMind, "maxMind");
    menuitem_text(maxGate, "maxGate");
    menuitem_text(maxOrchestrator, "maxOrchestrator");
    menuitem_text(maxLicense, "maxLicense");
    menuitem_text(maxServices, "maxServices");
    menuitem_text(client, "OPC Client");
    menuitem_text(server, "OPC Server");
    menuitem_text(document, "Document");
    menuitem_text(settings, "Settings");
    menuitem_text(toolbars, "Toolbars");
    menuitem_text(help, "Help");

    /* add the menu items to the top level menu */
    menu_add_item(topmenu, project);
    menu_add_item(topmenu, app->view);
    menu_add_item(topmenu, maxEngine);
    menu_add_item(topmenu, maxAdapter);
    menu_add_item(topmenu, maxCore);
    menu_add_item(topmenu, maxOrchestrator);
    menu_add_item(topmenu, maxIntegrator);
    menu_add_item(topmenu, maxScale);
    menu_add_item(topmenu, maxMind);
    menu_add_item(topmenu, maxGate);
    menu_add_item(topmenu, maxLicense);
    menu_add_item(topmenu, maxServices);

#ifdef TESTING
    menu_add_item(topmenu, client);
    menu_add_item(topmenu, server);
#endif
    menu_add_item(topmenu, document);
    menu_add_item(topmenu, toolbars);
#ifdef TESTING
    menu_add_item(topmenu, settings);
#endif
    menu_add_item(topmenu, help);

#ifndef WAIT
/* step 2 */
    /* create drop-down menus (submenus) */

    /* drop down menu items for 'File' */
    submenu_project = menu_create();
    osapp_menubar(submenu_project, app->window);
      project_new = menuitem_create(); menuitem_enabled(project_new, 1); menuitem_visible(project_new, 1);
      project_open = menuitem_create(); menuitem_enabled(project_open, 1); menuitem_visible(project_open, 1);
      project_save = menuitem_create(); menuitem_enabled(project_save, 1); menuitem_visible(project_save, 1);
      project_saveAs = menuitem_create(); menuitem_enabled(project_saveAs, 1); menuitem_visible(project_saveAs, 1);
      project_recentprojects = menuitem_create();
      project_separator = menuitem_separator();
      project_close = menuitem_create(); menuitem_enabled(project_close, 1), menuitem_visible(project_close, 1);
      project_quit = menuitem_create(); menuitem_enabled(project_quit, 1); menuitem_visible(project_quit, 1);

      menuitem_text(project_new,            "New       Ctrl+N");
      menuitem_text(project_open,           "Open      Ctrl+O");
      menuitem_text(project_save,           "Save      Ctrl+S");
      menuitem_text(project_saveAs,         "Save As ..      ");
      menuitem_text(project_recentprojects, "Recents Projects");
      menuitem_text(project_close,          "Close           ");
      menuitem_text(project_quit,           "Quit            ");

      image_project_new = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-new-file-24.png", NULL);
      image_project_open = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-opened-folder-24.png", NULL);
      image_project_save = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-save-25.png", NULL);
      image_project_saveAs = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-save-as-25.png", NULL);
      image_project_close = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-close-window-24.png", NULL);
      image_project_quit = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-exit-24.png", NULL);

      menu_add_item(submenu_project, project_new); menuitem_image(project_new, image_project_new);
      menu_add_item(submenu_project, project_open); menuitem_image(project_open, image_project_open);
      menu_add_item(submenu_project, project_save); menuitem_image(project_save, image_project_save);
      menu_add_item(submenu_project, project_saveAs); menuitem_image(project_saveAs, image_project_saveAs);
      menu_add_item(submenu_project, project_recentprojects);
      menu_add_item(submenu_project, project_separator);
      menu_add_item(submenu_project, project_close); menuitem_image(project_close, image_project_close);
      menu_add_item(submenu_project, project_quit); menuitem_image(project_quit, image_project_quit);

      menuitem_submenu(project, &submenu_project);

      menuitem_OnClick(project_new, listener(app, i_OnClick_menu_project_new, App));
      menuitem_OnClick(project_open, listener(app, i_OnClick_menu_project_open, App));
      menuitem_OnClick(project_save, listener(app, i_OnClick_menu_project_save, App));
      menuitem_OnClick(project_saveAs, listener(app, i_OnClick_menu_project_saveAs, App));
      menuitem_OnClick(project_close, listener(app, i_OnClick_menu_project_close, App));
      menuitem_OnClick(project_quit, listener(app, i_OnClick_menu_project_quit, App));

    /* drop down menu items for View */
    app->submenu_view = menu_create();
    osapp_menubar(app->submenu_view, app->window);
      app->view_interconnectivity = menuitem_create(); menuitem_enabled(app->view_interconnectivity, 1); menuitem_visible(app->view_interconnectivity, 1);
      app->view_project = menuitem_create(); menuitem_enabled(app->view_project, 1); menuitem_visible(app->view_project, 1);
      app->view_attributes = menuitem_create(); menuitem_enabled(app->view_attributes, 1); menuitem_visible(app->view_attributes, 1);
      app->view_log = menuitem_create(); menuitem_enabled(app->view_log, 1); menuitem_visible(app->view_log, 1);
      app->view_addressspace =  menuitem_create(); menuitem_enabled(app->view_addressspace, 1); menuitem_visible(app->view_addressspace, 1);
      app->view_references = menuitem_create(); menuitem_enabled(app->view_references, 1); menuitem_visible(app->view_references, 1);
      view_separator = menuitem_separator();
      app->view_maxAdapter = menuitem_create(); menuitem_enabled(app->view_maxAdapter,1); menuitem_visible(app->view_maxAdapter,1);
      app->view_maxGate = menuitem_create(); menuitem_enabled(app->view_maxGate,1); menuitem_visible(app->view_maxGate,1);
      app->view_maxIntegrator = menuitem_create(); menuitem_enabled(app->view_maxIntegrator,1); menuitem_visible(app->view_maxIntegrator,1);

/**/
/**/

      image_view_interconnectivity = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-interconnect-24.png", NULL);
      image_view_project = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-project-24.png", NULL);   /* to replace with a new icon file */
      image_view_attributes = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-genealogy-26.png", NULL);  /* to replace with a new icon file */
      image_view_log = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-log-24.png", NULL);  /* to replace with a new icon file */
      image_view_addressspace = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-atom-26.png", NULL);  /* to replace with a new icon file */
      image_view_maxAdapter = image_from_file("/home/pi/nappgui_src/jacky/img/maxAdapterIcon.png", NULL);  /* to replace with a new icon file */
      image_view_maxGate = image_from_file("/home/pi/nappgui_src/jacky/img/maxGateIcon.png", NULL);  /* to replace with a new icon file */
      image_view_maxIntegrator = image_from_file("/home/pi/nappgui_src/jacky/img/maxIntegratorIcon.png", NULL);  /* to replace with a new icon file */

      image_view_references = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-coderwall-24.png", NULL);  /* to replace with a new icon file */
      image_view_fileToolbar = image_from_file("/home/pi/nappgui_src/jacky/img/maxFileIcon.png", NULL); /*  to replace with a new icon file */
      image_view_viewToolbar = image_from_file("/home/pi/nappgui_src/jacky/img/maxViewIcon.png", NULL);
      image_view_maxEngineToolbar = image_from_file("/home/pi/nappgui_src/jacky/img/maxEngineIcon.png", NULL);  /* to replace with a new icon file */
      image_view_maxCoreToolbar = image_from_file("/home/pi/nappgui_src/jacky/img/maxEngineIcon.png", NULL);  /* to replace with a new icon file */
      image_view_maxIntegratorToolbar = image_from_file("/home/pi/nappgui_src/jacky/img/maxIntegratorIcon.png", NULL);  /* to replace with a new icon file */
      image_view_maxAdapterToolbar = image_from_file("/home/pi/nappgui_src/jacky/img/maxAdapterIcon.png", NULL);  /* to replace with a new icon file */
      image_view_maxGateToolbar = image_from_file("/home/pi/nappgui_src/jacky/img/maxGateIcon.png", NULL);  /* to replace with a new icon file */
      image_view_maxScaleToolbar = image_from_file("/home/pi/nappgui_src/jacky/img/maxScaleIcon.png", NULL);  /* to replace with a new icon file */
      image_view_maxOrchestratorToolbar = image_from_file("/home/pi/nappgui_src/jacky/img/maxOrchestratorIcon.png", NULL);  /* to replace with a new icon file */
      image_view_maxMindToolbar = image_from_file("/home/pi/nappgui_src/jacky/img/maxMindIcon.png", NULL);  /* to replace with a new icon file */
      image_view_maxLicenseToolbar = image_from_file("/home/pi/nappgui_src/jacky/img/maxLicenseIcon.png", NULL);  /* to replace with a new icon file */
      image_view_documentToolbar = image_from_file("/home/pi/nappgui_src/jacky/img/maxDocumentIcon.png", NULL); /* to replace with a new icon file */
      image_view_maxServicesToolbar =image_from_file("/home/pi/nappgui_src/jacky/img/maxIntegratorIcon.png", NULL);  /* to replace with a new icon file */ 

      /* displays a tick next to the menuitem if it is selected, tracked in app */
      menuitem_text(app->view_interconnectivity,      "Interconnectivity       "); menuitem_state(app->view_interconnectivity, ekGUI_ON); //view_interconnectivity = TRUE;
      menuitem_text(app->view_project,                "Project                 "); menuitem_state(app->view_project, ekGUI_ON); //view_project = TRUE;
      menuitem_text(app->view_attributes,             "Attributes              "); menuitem_state(app->view_attributes, ekGUI_ON); //view_attributes = TRUE;
      menuitem_text(app->view_references,             "References              "); menuitem_state(app->view_references, ekGUI_ON); //view_references = TRUE;
      menuitem_text(app->view_addressspace,           "Address Space           "); menuitem_state(app->view_addressspace, ekGUI_ON); //view_addressspace = TRUE;
      menuitem_text(app->view_maxAdapter,             "maxAdapter              "); menuitem_state(app->view_maxAdapter, ekGUI_ON); //view_maxAdapter = TRUE;
      menuitem_text(app->view_maxGate,                "maxGate                 "); menuitem_state(app->view_maxGate, ekGUI_ON); //view_maxGate = TRUE;
      menuitem_text(app->view_maxIntegrator,          "maxIntegrator           "); menuitem_state(app->view_maxIntegrator, ekGUI_ON); //view_maxIntegrator = TRUE;
      menuitem_text(app->view_log,                    "Log                     "); menuitem_state(app->view_log, ekGUI_ON); //view_log = TRUE;

      /* adds the image icon to the menu item */
      menu_add_item(app->submenu_view, app->view_interconnectivity); menuitem_image(app->view_interconnectivity, image_view_interconnectivity);
      menu_add_item(app->submenu_view, app->view_project);  menuitem_image(app->view_project, image_view_project);
      menu_add_item(app->submenu_view, app->view_attributes); menuitem_image(app->view_attributes, image_view_attributes);
      menu_add_item(app->submenu_view, app->view_references); menuitem_image(app->view_references, image_view_references);
      menu_add_item(app->submenu_view, app->view_addressspace); menuitem_image(app->view_addressspace, image_view_addressspace);
      menu_add_item(app->submenu_view, app->view_maxAdapter); menuitem_image(app->view_maxAdapter, image_view_maxAdapter);
      menu_add_item(app->submenu_view, app->view_maxGate); menuitem_image(app->view_maxGate, image_view_maxGate);
      menu_add_item(app->submenu_view, app->view_maxIntegrator);menuitem_image(app->view_maxIntegrator, image_view_maxIntegrator);
      menu_add_item(app->submenu_view, app->view_log); menuitem_image(app->view_log, image_view_log);
      menu_add_item(app->submenu_view, view_separator);

      menuitem_submenu(app->view, &app->submenu_view);

      menuitem_OnClick(app->view_interconnectivity, listener(app, i_OnClick_menu_view_interconnectivity, App));
      menuitem_OnClick(app->view_project, listener(app, i_OnClick_menu_view_project, App));
      menuitem_OnClick(app->view_attributes, listener(app, i_OnClick_menu_view_attributes, App));
      menuitem_OnClick(app->view_references, listener(app, i_OnClick_menu_view_references, App));
      menuitem_OnClick(app->view_addressspace, listener(app, i_OnClick_menu_view_addressspace, App));
      menuitem_OnClick(app->view_maxAdapter, listener(app, i_OnClick_menu_view_maxAdapter, App));
      menuitem_OnClick(app->view_maxGate, listener(app, i_OnClick_menu_view_maxGate, App));
      menuitem_OnClick(app->view_maxIntegrator, listener(app, i_OnClick_menu_view_maxIntegrator, App));
      menuitem_OnClick(app->view_log, listener(app, i_OnClick_menu_view_log, App));

    /* drop down menu items for maxEngine */
    submenu_maxEngine = menu_create();
    osapp_menubar(submenu_maxEngine, app->window);
      maxEngine_Start = menuitem_create(); menuitem_enabled(maxEngine_Start, 1); menuitem_visible(maxEngine_Start, 1);
      maxEngine_Stop = menuitem_create(); menuitem_enabled(maxEngine_Stop, 1); menuitem_visible(maxEngine_Stop, 1);
      maxEngine_separator = menuitem_separator();
      maxEngine_ViewStatistics = menuitem_create(); menuitem_enabled(maxEngine_ViewStatistics, 1); menuitem_visible(maxEngine_ViewStatistics, 1);
      app->maxEngine_ViewLiveLogs = menuitem_create(); menuitem_enabled(app->maxEngine_ViewLiveLogs, 1); menuitem_visible(app->maxEngine_ViewLiveLogs, 1);

      image_maxEngine_start = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-start-24.png", NULL);
      image_maxEngine_stop = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-stop-24.png", NULL);
      image_maxEngine_viewstatistics = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-heat-map-24.png", NULL);
      image_maxEngine_viewlivelogs = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-glasses-24.png", NULL);

      menuitem_text(maxEngine_Start,                   "One-click Start          ");
      menuitem_text(maxEngine_Stop,                    "One-click Stop           ");
      menuitem_text(maxEngine_ViewStatistics,	       "View Statistics          ");
      menuitem_text(app->maxEngine_ViewLiveLogs,            "View Live Logs           ");

      menu_add_item(submenu_maxEngine, maxEngine_Start); menuitem_image(maxEngine_Start, image_maxEngine_start);
      menu_add_item(submenu_maxEngine, maxEngine_Stop);  menuitem_image(maxEngine_Stop, image_maxEngine_stop);
      menu_add_item(submenu_maxEngine, maxEngine_separator);
      menu_add_item(submenu_maxEngine, maxEngine_ViewStatistics); menuitem_image(maxEngine_ViewStatistics, image_maxEngine_viewstatistics);
      menu_add_item(submenu_maxEngine, app->maxEngine_ViewLiveLogs); menuitem_image(app->maxEngine_ViewLiveLogs, image_maxEngine_viewlivelogs);

      menuitem_submenu(maxEngine, &submenu_maxEngine);

      menuitem_OnClick(maxEngine_Start, listener(app, i_OnClick_menu_maxengine_oneclickstart, App));
      menuitem_OnClick(maxEngine_Stop, listener(app, i_OnClick_menu_maxengine_oneclickstop, App));
      menuitem_OnClick(maxEngine_ViewStatistics, listener(app, i_OnClick_menu_maxengine_viewstatistics, App));
      menuitem_OnClick(app->maxEngine_ViewLiveLogs, listener(app, i_OnClick_menu_maxengine_viewlivelogs, App));


    /* drop down menu items for maxCore */
    submenu_maxCore = menu_create();
    osapp_menubar(submenu_maxCore, app->window);
      maxCore_Start = menuitem_create(); menuitem_enabled(maxCore_Start, 1); menuitem_visible(maxCore_Start, 1);
      maxCore_Stop = menuitem_create(); menuitem_enabled(maxCore_Stop, 1); menuitem_visible(maxCore_Stop, 1); menuitem_state(maxCore_Stop, ekGUI_ON);
      maxCore_separator = menuitem_separator();
      maxCore_RegisterMaxAdapters = menuitem_create(); menuitem_enabled(maxCore_RegisterMaxAdapters, 1); menuitem_visible(maxCore_RegisterMaxAdapters, 1);
      maxCore_LogsManagement = menuitem_create(); menuitem_enabled(maxCore_LogsManagement, 1); menuitem_visible(maxCore_LogsManagement, 1);
      maxCore_StartupParameters = menuitem_create(); menuitem_enabled(maxCore_StartupParameters, 1); menuitem_visible(maxCore_StartupParameters, 1);
      maxCore_ViewStatistics = menuitem_create(); menuitem_enabled(maxCore_ViewStatistics, 1); menuitem_visible(maxCore_ViewStatistics, 1);
      app->maxCore_ViewLiveLogs = menuitem_create(); menuitem_enabled(app->maxCore_ViewLiveLogs, 1); menuitem_visible(app->maxCore_ViewLiveLogs, 1);
      maxCore_WebSocketService = menuitem_create(); menuitem_enabled(maxCore_WebSocketService, 1); menuitem_visible(maxCore_WebSocketService, 1);

      image_maxCore_start = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-start-24.png", NULL);
      image_maxCore_stop = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-stop-24.png", NULL);
      image_maxCore_registermaxadapters = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-edit-property-24.png", NULL);
      image_maxCore_logsmanagement = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-file-configuration-24.png", NULL);
      image_maxCore_startupparameters = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-start-26.png", NULL);
      image_maxCore_viewstatistics = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-heat-map-24.png", NULL);
      image_maxCore_viewlivelogs = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-glasses-24.png", NULL);
      image_maxCore_websocketservice = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-azure-relay-hybrid-connection-24.png", NULL);

      menuitem_text(maxCore_Start, "Start instance");
      menuitem_text(maxCore_Stop, "Stop instance");
      menuitem_text(maxCore_RegisterMaxAdapters, "Register maxAdapters");
      menuitem_text(maxCore_LogsManagement, "Logs Management");
      menuitem_text(maxCore_StartupParameters, "Startup Parameters");
      menuitem_text(maxCore_WebSocketService, "WebSocket Service");
      menuitem_text(maxCore_ViewStatistics, "View Statistics");
      menuitem_text(app->maxCore_ViewLiveLogs, "View Live logs");

      menu_add_item(submenu_maxCore, maxCore_Start); menuitem_image(maxCore_Start, image_maxCore_start);
      menu_add_item(submenu_maxCore, maxCore_Stop); menuitem_image(maxCore_Stop, image_maxCore_stop);
      menu_add_item(submenu_maxCore, maxCore_separator);
      menu_add_item(submenu_maxCore, maxCore_RegisterMaxAdapters); menuitem_image(maxCore_RegisterMaxAdapters, image_maxCore_registermaxadapters);
      menu_add_item(submenu_maxCore, maxCore_LogsManagement); menuitem_image(maxCore_LogsManagement, image_maxCore_logsmanagement);
      menu_add_item(submenu_maxCore, maxCore_StartupParameters); menuitem_image(maxCore_StartupParameters, image_maxCore_startupparameters);
      menu_add_item(submenu_maxCore, maxCore_WebSocketService); menuitem_image(maxCore_WebSocketService, image_maxCore_websocketservice);
      menu_add_item(submenu_maxCore, maxCore_separator);
      menu_add_item(submenu_maxCore, maxCore_ViewStatistics); menuitem_image(maxCore_ViewStatistics, image_maxCore_viewstatistics);
      menu_add_item(submenu_maxCore, app->maxCore_ViewLiveLogs); menuitem_image(app->maxCore_ViewLiveLogs, image_maxCore_viewlivelogs);

      menuitem_submenu(maxCore, &submenu_maxCore);

      menuitem_OnClick(app->maxCore_ViewLiveLogs, listener(app, i_OnClick_menu_maxcore_viewlivelogs, App));

    /* drop down menu items for maxAdapter */
    submenu_maxAdapter = menu_create();
    osapp_menubar(submenu_maxAdapter, app->window);
      app->maxAdapter_Start = menuitem_create(); menuitem_enabled(app->maxAdapter_Start, 1); menuitem_visible(app->maxAdapter_Start, 1);
      app->maxAdapter_Stop = menuitem_create(); menuitem_enabled(app->maxAdapter_Stop, 1); menuitem_visible(app->maxAdapter_Stop, 1); menuitem_state(app->maxAdapter_Stop, ekGUI_ON);
      maxAdapter_HistorianService = menuitem_create(); menuitem_enabled(maxAdapter_HistorianService, 1); menuitem_visible(maxAdapter_HistorianService, 1);
      maxAdapter_AlarmsAndConditions = menuitem_create(); menuitem_enabled(maxAdapter_AlarmsAndConditions, 1); menuitem_visible(maxAdapter_AlarmsAndConditions, 1);
      maxAdapter_Events = menuitem_create(); menuitem_enabled(maxAdapter_Events, 1); menuitem_visible(maxAdapter_Events,1);
      maxAdapter_LogsManagement = menuitem_create(); menuitem_enabled(maxAdapter_LogsManagement, 1); menuitem_visible(maxAdapter_LogsManagement, 1);
      maxAdapter_ReverseConnect = menuitem_create(); menuitem_enabled(maxAdapter_ReverseConnect, 1); menuitem_visible(maxAdapter_ReverseConnect, 1);
//      maxEngine_UsersAccount = menuitem_create(); menuitem_enabled(maxEngine_UsersAccount, 1); menuitem_visible(maxEngine_UsersAccount, 1);
//      maxEngine_SystemsAccount = menuitem_create(); menuitem_enabled(maxEngine_SystemsAccount, 1); menuitem_visible(maxEngine_SystemsAccount, 1);
//      maxEngine_GenerateSSLCertificates = menuitem_create(); menuitem_enabled(maxEngine_GenerateSSLCertificates, 1); menuitem_visible(maxEngine_GenerateSSLCertificates, 1);
      maxAdapter_StartupParameters = menuitem_create(); menuitem_enabled(maxAdapter_StartupParameters, 1); menuitem_visible(maxAdapter_StartupParameters, 1);
      maxAdapter_Communications = menuitem_create(); menuitem_enabled(maxAdapter_Communications, 1); menuitem_visible(maxAdapter_Communications, 1);
      maxAdapter_ViewStatistics = menuitem_create(); menuitem_enabled(maxAdapter_ViewStatistics, 1); menuitem_visible(maxAdapter_ViewStatistics, 1);
      app->maxAdapter_ViewLiveLogs = menuitem_create(); menuitem_enabled(app->maxAdapter_ViewLiveLogs, 1); menuitem_visible(app->maxAdapter_ViewLiveLogs, 1);
      maxAdapter_WebSocketService = menuitem_create(); menuitem_enabled(maxAdapter_WebSocketService, 1); menuitem_visible(maxAdapter_WebSocketService, 1);

      image_maxAdapter_historianservice = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-database-24.png", NULL);
      image_maxAdapter_alarmsandconditions = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-alarm-24.png", NULL);
      image_maxAdapter_events = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-events-24.png", NULL);
      image_maxAdapter_logsmanagement = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-file-configuration-24.png", NULL);
      image_maxAdapter_reverseconnect = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-return-24.png", NULL);
      image_maxAdapter_usersaccount = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-users-24.png", NULL);
      image_maxAdapter_systemsaccount = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-access-24.png", NULL);
      image_maxAdapter_generatesslcertificates = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-security-ssl-24.png", NULL);
      image_maxAdapter_registermaxadapters = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-edit-property-24.png", NULL);
      image_maxAdapter_startupparameters = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-start-26.png", NULL);
      image_maxAdapter_communications = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-computers-connecting-24.png", NULL);
      image_maxAdapter_viewstatistics = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-heat-map-24.png", NULL);
      image_maxAdapter_viewlivelogs = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-glasses-24.png", NULL);

      maxAdapter_ManualConfiguration = menuitem_create(); menuitem_enabled(maxAdapter_ManualConfiguration, 1); menuitem_visible(maxAdapter_ManualConfiguration, 1);
      maxAdapter_Discovery = menuitem_create(); menuitem_enabled(maxAdapter_Discovery, 1); menuitem_visible(maxAdapter_Discovery, 1);
      maxAdapter_Generate = menuitem_create(); menuitem_enabled(maxAdapter_Generate, 1); menuitem_visible(maxAdapter_Generate, 1);
      maxAdapter_SimRun = menuitem_create(); menuitem_enabled(maxAdapter_SimRun, 1); menuitem_visible(maxAdapter_SimRun, 1);
      maxAdapter_NodesetEditor = menuitem_create(); menuitem_enabled(maxAdapter_NodesetEditor, 1); menuitem_visible(maxAdapter_NodesetEditor, 1);
      maxAdapter_separator = menuitem_separator();
      maxAdapter_separator1 = menuitem_separator();
      maxAdapter_separator2 = menuitem_separator();
      maxAdapter_separator3 = menuitem_separator();
      maxAdapter_separator4 = menuitem_separator();


      image_maxAdapter_start = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-start-24.png", NULL);
      image_maxAdapter_stop = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-stop-24.png", NULL);
      image_maxAdapter_discover = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-radar-24.png", NULL);
      image_maxAdapter_generate = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-gear-24.png", NULL);
      image_maxAdapter_simrun = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-connect-24.png", NULL);
      image_maxAdapter_nodeseteditor = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-connected-no-data-24.png", NULL);
      image_maxAdapter_manualconfiguration = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-open-end-wrench-24.png", NULL);
      image_maxAdapter_websocketservice = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-azure-relay-hybrid-connection-24.png", NULL);

      menuitem_text(app->maxAdapter_Start, "Start instance");
      menuitem_text(app->maxAdapter_Stop, "Stop instance");
      menuitem_text(maxAdapter_HistorianService,        "Historian Server        ");
      menuitem_text(maxAdapter_AlarmsAndConditions,     "Alarms & Conditions      ");
      menuitem_text(maxAdapter_Events,                  "Events                   ");
      menuitem_text(maxAdapter_LogsManagement,          "Logs Management          ");
      menuitem_text(maxAdapter_ReverseConnect,          "Reverse Connect          ");
      menuitem_text(maxAdapter_StartupParameters,       "Startup Parameters       ");
      menuitem_text(maxAdapter_Communications,          "Communications Protocols ");
      menuitem_text(maxAdapter_Discovery,           "Discover devices    ");
      menuitem_text(maxAdapter_Generate,            "Auto generate       ");
      menuitem_text(maxAdapter_SimRun,              "Simulate and connect");
      menuitem_text(maxAdapter_NodesetEditor,       "Edit device nodeset ");
      menuitem_text(maxAdapter_ManualConfiguration, "Manual Configuration");
      menuitem_text(maxAdapter_WebSocketService,    "WebSocket Service");
      menuitem_text(maxAdapter_ViewStatistics,      "View Statistics          ");
      menuitem_text(app->maxAdapter_ViewLiveLogs,        "View Live Logs           ");

      menu_add_item(submenu_maxAdapter, app->maxAdapter_Start); menuitem_image(app->maxAdapter_Start, image_maxAdapter_start);
      menu_add_item(submenu_maxAdapter, app->maxAdapter_Stop); menuitem_image(app->maxAdapter_Stop, image_maxAdapter_stop);
      menu_add_item(submenu_maxAdapter, maxAdapter_separator);
      menu_add_item(submenu_maxAdapter, maxAdapter_HistorianService); menuitem_image(maxAdapter_HistorianService, image_maxAdapter_historianservice);
      menu_add_item(submenu_maxAdapter, maxAdapter_AlarmsAndConditions); menuitem_image(maxAdapter_AlarmsAndConditions, image_maxAdapter_alarmsandconditions);
      menu_add_item(submenu_maxAdapter, maxAdapter_Events); menuitem_image(maxAdapter_Events, image_maxAdapter_events);
      menu_add_item(submenu_maxAdapter, maxAdapter_LogsManagement); menuitem_image(maxAdapter_LogsManagement, image_maxAdapter_logsmanagement);
      menu_add_item(submenu_maxAdapter, maxAdapter_ReverseConnect); menuitem_image(maxAdapter_ReverseConnect, image_maxAdapter_reverseconnect);
      menu_add_item(submenu_maxAdapter, maxAdapter_separator1);
      menu_add_item(submenu_maxAdapter, maxAdapter_StartupParameters); menuitem_image(maxAdapter_StartupParameters, image_maxAdapter_startupparameters);
      menu_add_item(submenu_maxAdapter, maxAdapter_Communications); menuitem_image(maxAdapter_Communications, image_maxAdapter_communications);
      menu_add_item(submenu_maxAdapter, maxAdapter_separator2);
      menu_add_item(submenu_maxAdapter, maxAdapter_Discovery); menuitem_image(maxAdapter_Discovery, image_maxAdapter_discover);
      menu_add_item(submenu_maxAdapter, maxAdapter_Generate); menuitem_image(maxAdapter_Generate, image_maxAdapter_generate);
      menu_add_item(submenu_maxAdapter, maxAdapter_SimRun); menuitem_image(maxAdapter_SimRun, image_maxAdapter_simrun);
      menu_add_item(submenu_maxAdapter, maxAdapter_separator3);
      menu_add_item(submenu_maxAdapter, maxAdapter_NodesetEditor); menuitem_image(maxAdapter_NodesetEditor, image_maxAdapter_nodeseteditor);
      menu_add_item(submenu_maxAdapter, maxAdapter_ManualConfiguration); menuitem_image(maxAdapter_ManualConfiguration, image_maxAdapter_manualconfiguration);
      menu_add_item(submenu_maxAdapter, maxAdapter_WebSocketService); menuitem_image(maxAdapter_WebSocketService, image_maxAdapter_websocketservice);
      menu_add_item(submenu_maxAdapter, maxAdapter_separator4);
      menu_add_item(submenu_maxAdapter, maxAdapter_ViewStatistics); menuitem_image(maxAdapter_ViewStatistics, image_maxAdapter_viewstatistics);
      menu_add_item(submenu_maxAdapter, app->maxAdapter_ViewLiveLogs); menuitem_image(app->maxAdapter_ViewLiveLogs, image_maxAdapter_viewlivelogs);

      menuitem_submenu(maxAdapter, &submenu_maxAdapter);

      menuitem_OnClick(app->maxAdapter_Start, listener(app, i_OnClick_menu_maxadapter_start, App));
      menuitem_OnClick(app->maxAdapter_Stop, listener(app, i_OnClick_menu_maxadapter_stop, App));
      menuitem_OnClick(maxAdapter_HistorianService, listener(app, i_OnClick_menu_maxAdapter_historianservice, App));
      menuitem_OnClick(maxAdapter_AlarmsAndConditions, listener(app, i_OnClick_menu_maxadapter_alarmsandconditions, App));
      menuitem_OnClick(maxAdapter_Events, listener(app, i_OnClick_menu_maxadapter_events, App));
      menuitem_OnClick(maxAdapter_LogsManagement, listener(app, i_OnClick_menu_maxadapter_logsmanagement, App));
      menuitem_OnClick(maxAdapter_ReverseConnect, listener(app, i_OnClick_menu_maxadapter_reverseconnect, App));
      menuitem_OnClick(maxAdapter_StartupParameters, listener(app, i_OnClick_menu_maxadapter_startupparameters, App));
      menuitem_OnClick(maxAdapter_Communications, listener(app, i_OnClick_menu_maxadapter_communications, App));
      menuitem_OnClick(maxAdapter_ViewStatistics, listener(app, i_OnClick_menu_maxadapter_viewstatistics, App));
      menuitem_OnClick(app->maxAdapter_ViewLiveLogs, listener(app, i_OnClick_menu_maxadapter_viewlivelogs, App));
      menuitem_OnClick(maxAdapter_Discovery, listener(app, i_OnClick_menu_maxadapter_discoverdevices, App));
      menuitem_OnClick(maxAdapter_Generate, listener(app, i_OnClick_menu_maxadapter_autogenerate, App));
      menuitem_OnClick(maxAdapter_SimRun, listener(app, i_OnClick_menu_maxadapter_simrun, App));
      menuitem_OnClick(maxAdapter_NodesetEditor, listener(app, i_OnClick_menu_maxadapter_nodeseteditor, App));
      menuitem_OnClick(maxAdapter_ManualConfiguration, listener(app, i_OnClick_menu_maxadapter_manualconfiguration, App));



    /* drop down menu items for maxIntegrator */
    submenu_maxIntegrator = menu_create();
    osapp_menubar(submenu_maxIntegrator, app->window);
      maxIntegrator_Start = menuitem_create(); menuitem_enabled(maxIntegrator_Start, 1); menuitem_visible(maxIntegrator_Start, 1);
      maxIntegrator_Stop = menuitem_create(); menuitem_enabled(maxIntegrator_Stop, 1); menuitem_visible(maxIntegrator_Stop, 1); menuitem_state(maxIntegrator_Stop, ekGUI_ON);
      maxIntegrator_separator1 = menuitem_separator();
      maxIntegrator_RadiusService = menuitem_create(); menuitem_enabled(maxIntegrator_RadiusService, 1); menuitem_visible(maxIntegrator_RadiusService, 1);
      maxIntegrator_LdapService = menuitem_create(); menuitem_enabled(maxIntegrator_LdapService, 1); menuitem_visible(maxIntegrator_LdapService, 1);
      maxIntegrator_IamService = menuitem_create(); menuitem_enabled(maxIntegrator_IamService, 1); menuitem_visible(maxIntegrator_IamService, 1);
      maxIntegrator_SyslogService = menuitem_create(); menuitem_enabled(maxIntegrator_SyslogService, 1); menuitem_visible(maxIntegrator_SyslogService, 1);
      maxIntegrator_separator2 = menuitem_separator();
      maxIntegrator_AmqpService = menuitem_create(); menuitem_enabled(maxIntegrator_AmqpService, 1); menuitem_visible(maxIntegrator_AmqpService, 1);
      maxIntegrator_MqttService = menuitem_create(); menuitem_enabled(maxIntegrator_MqttService, 1); menuitem_visible(maxIntegrator_MqttService, 1);
      maxIntegrator_WebapiService = menuitem_create(); menuitem_enabled(maxIntegrator_WebapiService, 1); menuitem_visible(maxIntegrator_WebapiService, 1);
      maxIntegrator_WebsocketService = menuitem_create(); menuitem_enabled(maxIntegrator_WebsocketService, 1); menuitem_visible(maxIntegrator_WebsocketService, 1);
      maxIntegrator_ProxyService = menuitem_create(); menuitem_enabled(maxIntegrator_ProxyService, 1); menuitem_visible(maxIntegrator_ProxyService, 1);
      maxIntegrator_separator3 = menuitem_separator();
      maxIntegrator_OpcUAService = menuitem_create(); menuitem_enabled(maxIntegrator_OpcUAService, 1); menuitem_visible(maxIntegrator_OpcUAService, 1);
      maxIntegrator_GdsService = menuitem_create(); menuitem_enabled(maxIntegrator_GdsService, 1); menuitem_visible(maxIntegrator_GdsService, 1);
      maxIntegrator_LdsService = menuitem_create(); menuitem_enabled(maxIntegrator_LdsService, 1); menuitem_visible(maxIntegrator_LdsService, 1);
      maxIntegrator_separator = menuitem_separator();
      maxIntegrator_ViewStatistics = menuitem_create(); menuitem_enabled(maxIntegrator_ViewStatistics, 1); menuitem_visible(maxIntegrator_ViewStatistics, 1);
      app->maxIntegrator_ViewLiveLogs = menuitem_create(); menuitem_enabled(app->maxIntegrator_ViewLiveLogs, 1); menuitem_visible(app->maxIntegrator_ViewLiveLogs, 1);

      image_maxIntegrator_start = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-start-24.png", NULL);
      image_maxIntegrator_stop = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-stop-24.png", NULL);
      image_maxIntegrator_radiusservice = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-radius-24.png", NULL);
      image_maxIntegrator_ldapservice = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-active-directory-24.png", NULL);
      image_maxIntegrator_iamservice = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-individual-server-24.png", NULL);
      image_maxIntegrator_syslogservice = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-logbook-24.png", NULL);
      image_maxIntegrator_amqpservice = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-data-exchange-24.png", NULL);
      image_maxIntegrator_mqttservice = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-change-16.png", NULL);
      image_maxIntegrator_webapiservice = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-rest-api-24.png", NULL);
      image_maxIntegrator_websocketservice = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-azure-relay-hybrid-connection-24.png", NULL);
      image_maxIntegrator_proxyservice = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-gyroscope-24.png", NULL);
      image_maxIntegrator_opcuaservice = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-communications-24.png", NULL);
      image_maxIntegrator_gdsservice = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-globe-24.png", NULL);
      image_maxIntegrator_ldsservice = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-networking-manager-24.png", NULL);
      image_maxIntegrator_viewstatistics = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-heat-map-24.png", NULL);
      image_maxIntegrator_viewlivelogs = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-glasses-24.png", NULL);

      menuitem_text(maxIntegrator_Start, 		"Start instance");
      menuitem_text(maxIntegrator_Stop, 		"Stop instance");
      menuitem_text(maxIntegrator_RadiusService,        "Radius Server           ");
      menuitem_text(maxIntegrator_LdapService,          "Ldap Server             ");
      menuitem_text(maxIntegrator_IamService,           "Identity & Access Server");
      menuitem_text(maxIntegrator_SyslogService,        "Syslog Server           ");
      menuitem_text(maxIntegrator_AmqpService,          "Rabbit AMQP Broker	 ");
      menuitem_text(maxIntegrator_MqttService, 		"MQTT Broker             ");
      menuitem_text(maxIntegrator_WebapiService,        "WebAPI Server           ");	/* instantiate own webApi server to provide data */
      menuitem_text(maxIntegrator_WebsocketService,     "WebSocket Server        ");	/* instantiate own websocket server to provide data */
      menuitem_text(maxIntegrator_ProxyService,           "Proxy Server            ");
      menuitem_text(maxIntegrator_OpcUAService,         "OPCUA Server            ");	/* instantiate own OPCUA Server to provide data */
      menuitem_text(maxIntegrator_GdsService,           "Global Directory Server ");
      menuitem_text(maxIntegrator_LdsService,           "Local Directory Server  ");
      menuitem_text(maxIntegrator_ViewStatistics,       "View Statistics         ");
      menuitem_text(app->maxIntegrator_ViewLiveLogs,         "View Live Logs          ");

      menu_add_item(submenu_maxIntegrator, maxIntegrator_Start); menuitem_image(maxIntegrator_Start, image_maxIntegrator_start);
      menu_add_item(submenu_maxIntegrator, maxIntegrator_Stop); menuitem_image(maxIntegrator_Stop, image_maxIntegrator_stop);
      menu_add_item(submenu_maxIntegrator, maxIntegrator_separator1);
      menu_add_item(submenu_maxIntegrator, maxIntegrator_RadiusService); menuitem_image(maxIntegrator_RadiusService, image_maxIntegrator_radiusservice);
      menu_add_item(submenu_maxIntegrator, maxIntegrator_LdapService); menuitem_image(maxIntegrator_LdapService, image_maxIntegrator_ldapservice);
      menu_add_item(submenu_maxIntegrator, maxIntegrator_IamService); menuitem_image(maxIntegrator_IamService, image_maxIntegrator_iamservice);
      menu_add_item(submenu_maxIntegrator, maxIntegrator_SyslogService); menuitem_image(maxIntegrator_SyslogService, image_maxIntegrator_syslogservice);
      menu_add_item(submenu_maxIntegrator, maxIntegrator_separator2);
      menu_add_item(submenu_maxIntegrator, maxIntegrator_AmqpService); menuitem_image(maxIntegrator_AmqpService, image_maxIntegrator_amqpservice);
      menu_add_item(submenu_maxIntegrator, maxIntegrator_MqttService); menuitem_image(maxIntegrator_MqttService, image_maxIntegrator_mqttservice);
      menu_add_item(submenu_maxIntegrator, maxIntegrator_WebapiService); menuitem_image(maxIntegrator_WebapiService, image_maxIntegrator_webapiservice);
      menu_add_item(submenu_maxIntegrator, maxIntegrator_WebsocketService); menuitem_image(maxIntegrator_WebsocketService, image_maxIntegrator_websocketservice);
      menu_add_item(submenu_maxIntegrator, maxIntegrator_ProxyService); menuitem_image(maxIntegrator_ProxyService, image_maxIntegrator_proxyservice);
      menu_add_item(submenu_maxIntegrator, maxIntegrator_separator3);
      menu_add_item(submenu_maxIntegrator, maxIntegrator_OpcUAService); menuitem_image(maxIntegrator_OpcUAService, image_maxIntegrator_opcuaservice);
      menu_add_item(submenu_maxIntegrator, maxIntegrator_GdsService); menuitem_image(maxIntegrator_GdsService, image_maxIntegrator_gdsservice);
      menu_add_item(submenu_maxIntegrator, maxIntegrator_LdsService); menuitem_image(maxIntegrator_LdsService, image_maxIntegrator_ldsservice);
      menu_add_item(submenu_maxIntegrator, maxIntegrator_separator);
      menu_add_item(submenu_maxIntegrator, maxIntegrator_ViewStatistics); menuitem_image(maxIntegrator_ViewStatistics, image_maxIntegrator_viewstatistics);
      menu_add_item(submenu_maxIntegrator, app->maxIntegrator_ViewLiveLogs); menuitem_image(app->maxIntegrator_ViewLiveLogs, image_maxIntegrator_viewlivelogs);

      menuitem_submenu(maxIntegrator, &submenu_maxIntegrator);

      menuitem_OnClick(maxIntegrator_Start, listener(app, i_OnClick_menu_maxIntegrator_start, App));
      menuitem_OnClick(maxIntegrator_Stop, listener(app, i_OnClick_menu_maxIntegrator_stop, App));
      menuitem_OnClick(maxIntegrator_RadiusService, listener(app, i_OnClick_menu_maxIntegrator_radiusservice, App));
      menuitem_OnClick(maxIntegrator_LdapService, listener(app, i_OnClick_menu_maxIntegrator_ldapservice, App));
      menuitem_OnClick(maxIntegrator_IamService, listener(app, i_OnClick_menu_maxIntegrator_iamservice, App));
      menuitem_OnClick(maxIntegrator_SyslogService, listener(app, i_OnClick_menu_maxIntegrator_syslogservice, App));
      menuitem_OnClick(maxIntegrator_AmqpService, listener(app, i_OnClick_menu_maxIntegrator_amqpservice, App));
      menuitem_OnClick(maxIntegrator_MqttService, listener(app, i_OnClick_menu_maxIntegrator_mqttservice, App));
      menuitem_OnClick(maxIntegrator_WebapiService, listener(app, i_OnClick_menu_maxIntegrator_webapiservice, App));
      menuitem_OnClick(maxIntegrator_WebsocketService, listener(app, i_OnClick_menu_maxIntegrator_websocketservice, App));
      menuitem_OnClick(maxIntegrator_ProxyService, listener(app, i_OnClick_menu_maxIntegrator_proxyservice, App));
      menuitem_OnClick(maxIntegrator_OpcUAService, listener(app, i_OnClick_menu_maxIntegrator_opcuaservice, App));
      menuitem_OnClick(maxIntegrator_GdsService, listener(app, i_OnClick_menu_maxIntegrator_gdsservice, App));
      menuitem_OnClick(maxIntegrator_LdsService, listener(app, i_OnClick_menu_maxIntegrator_ldsservice, App));
      menuitem_OnClick(maxIntegrator_ViewStatistics, listener(app, i_OnClick_menu_maxIntegrator_viewstatistics, App));
      menuitem_OnClick(app->maxIntegrator_ViewLiveLogs, listener(app, i_OnClick_menu_maxIntegrator_viewlivelogs, App));

    /* drop down menu items for maxScale */
    submenu_maxScale = menu_create();
    osapp_menubar(submenu_maxScale, app->window);
      maxScale_InstanceSetup = menuitem_create(); menuitem_enabled(maxScale_InstanceSetup, 1); menuitem_visible(maxScale_InstanceSetup, 1);
      maxScale_Configuration = menuitem_create(); menuitem_enabled(maxScale_Configuration, 1); menuitem_visible(maxScale_Configuration, 1);

      image_maxScale_instancesetup = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-expand-24.png", NULL);
      image_maxScale_configuration = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-open-end-wrench-24.png", NULL);

      menuitem_text(maxScale_InstanceSetup, "Setup Instance");
      menuitem_text(maxScale_Configuration, "Configuration ");

      menu_add_item(submenu_maxScale, maxScale_InstanceSetup); menuitem_image(maxScale_InstanceSetup, image_maxScale_instancesetup);
      menu_add_item(submenu_maxScale, maxScale_Configuration); menuitem_image(maxScale_Configuration, image_maxScale_configuration);

      menuitem_submenu(maxScale, &submenu_maxScale);

      menuitem_OnClick(maxScale_InstanceSetup, listener(app, i_OnClick_menu_maxscale_instancesetup, App));
      menuitem_OnClick(maxScale_Configuration, listener(app, i_OnClick_menu_maxscale_instancesetup, App));

    /* drop down menu items for maxMind */

    submenu_maxMind = menu_create();
    osapp_menubar(submenu_maxMind, app->window);
      maxMind_DigitalTwin = menuitem_create(); menuitem_enabled(maxMind_DigitalTwin, 1); menuitem_visible(maxMind_DigitalTwin, 1);
      maxMind_Analytics = menuitem_create(); menuitem_enabled(maxMind_Analytics, 1); menuitem_visible(maxMind_Analytics, 1);
      maxMind_MachineLearning = menuitem_create(); menuitem_enabled(maxMind_MachineLearning, 1); menuitem_visible(maxMind_MachineLearning, 1);

      image_maxMind_digitaltwin = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-clone-24.png", NULL);
      image_maxMind_analytics = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-chart-24.png", NULL);
      image_maxMind_machinelearning = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-machine-learning-24.png", NULL);

      menuitem_text(maxMind_DigitalTwin, "Digital Twin");
      menuitem_text(maxMind_Analytics, "Real time Analytics");
      menuitem_text(maxMind_MachineLearning, "Machine Learning");

      menu_add_item(submenu_maxMind, maxMind_DigitalTwin); menuitem_image(maxMind_DigitalTwin, image_maxMind_digitaltwin);
      menu_add_item(submenu_maxMind, maxMind_Analytics); menuitem_image(maxMind_Analytics, image_maxMind_analytics);
      menu_add_item(submenu_maxMind, maxMind_MachineLearning); menuitem_image(maxMind_MachineLearning, image_maxMind_machinelearning);

      menuitem_submenu(maxMind, &submenu_maxMind);

      menuitem_OnClick(maxMind_DigitalTwin, listener(app, i_OnClick_menu_maxmind_digitaltwin, App));
      menuitem_OnClick(maxMind_Analytics, listener(app, i_OnClick_menu_maxmind_analytics, App));
      menuitem_OnClick(maxMind_MachineLearning, listener(app, i_OnClick_menu_maxmind_machinelearning, App));

    /* drop down menu items for maxGate */
    submenu_maxGate = menu_create();
    osapp_menubar(submenu_maxGate, app->window);
      maxGate_Start = menuitem_create(); menuitem_enabled(maxGate_Start, 1); menuitem_visible(maxGate_Start, 1);
      maxGate_Stop = menuitem_create(); menuitem_enabled(maxGate_Stop, 1); menuitem_visible(maxGate_Stop, 1); menuitem_state(maxGate_Stop, ekGUI_ON);
      maxGate_Inspect = menuitem_create();  menuitem_enabled(maxGate_Inspect, 1); menuitem_visible(maxGate_Inspect, 1);
      maxGate_ManualConfiguration = menuitem_create(); menuitem_enabled(maxGate_ManualConfiguration, 1); menuitem_visible(maxGate_ManualConfiguration, 1);
      maxGate_separator = menuitem_separator();

      image_maxGate_start = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-start-24.png", NULL);
      image_maxGate_stop = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-stop-24.png", NULL);
      image_maxGate_inspect = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-inspect-24.png", NULL);
      image_maxGate_manualconfiguration = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-open-end-wrench-24.png", NULL);

      menuitem_text(maxGate_Start, "Start instance");
      menuitem_text(maxGate_Stop, "Stop instance");
      menuitem_text(maxGate_Inspect, "Inspect instance");
      menuitem_text(maxGate_ManualConfiguration, "Manual Configuration");

      menu_add_item(submenu_maxGate, maxGate_Start); menuitem_image(maxGate_Start, image_maxGate_start);
      menu_add_item(submenu_maxGate, maxGate_Stop); menuitem_image(maxGate_Stop, image_maxGate_stop);
      menu_add_item(submenu_maxGate, maxGate_Inspect); menuitem_image(maxGate_Inspect, image_maxGate_inspect);
      menu_add_item(submenu_maxGate, maxGate_separator);
      menu_add_item(submenu_maxGate, maxGate_ManualConfiguration); menuitem_image(maxGate_ManualConfiguration, image_maxGate_manualconfiguration);

      menuitem_submenu(maxGate, &submenu_maxGate);

      menuitem_OnClick(maxGate_Start, listener(app, i_OnClick_menu_maxgate_start, App));
      menuitem_OnClick(maxGate_Stop, listener(app, i_OnClick_menu_maxgate_stop, App));
      menuitem_OnClick(maxGate_Inspect, listener(app, i_OnClick_menu_maxgate_inspect, App));
      menuitem_OnClick(maxGate_ManualConfiguration, listener(app, i_OnClick_menu_maxgate_manualconfiguration_add, App));

    /* drop down menu items for maxLicense */
    submenu_maxLicense = menu_create();
    osapp_menubar(submenu_maxLicense, app->window);
      maxLicense_Activate = menuitem_create(); menuitem_enabled(maxLicense_Activate, 1); menuitem_visible(maxLicense_Activate, 1);
      maxLicense_Inspect = menuitem_create(); menuitem_enabled(maxLicense_Inspect, 1); menuitem_visible(maxLicense_Inspect, 1);
      maxLicense_Request = menuitem_create(); menuitem_enabled(maxLicense_Request, 1); menuitem_visible(maxLicense_Request, 1);

      image_maxLicense_activate = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-natural-user-interface-26.png", NULL);
      image_maxLicense_inspect = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-inspect-code-24.png", NULL);
      image_maxLicense_request = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-software-license-24.png", NULL);

      menuitem_text(maxLicense_Activate, "Activate License");
      menuitem_text(maxLicense_Inspect, "Inspect ...");
      menuitem_text(maxLicense_Request, "Request licenses");

      menu_add_item(submenu_maxLicense, maxLicense_Activate); menuitem_image(maxLicense_Activate, image_maxLicense_activate);
      menu_add_item(submenu_maxLicense, maxLicense_Inspect); menuitem_image(maxLicense_Inspect, image_maxLicense_inspect);
      menu_add_item(submenu_maxLicense, maxLicense_Request); menuitem_image(maxLicense_Request, image_maxLicense_request);

      menuitem_submenu(maxLicense, &submenu_maxLicense);

      menuitem_OnClick(maxLicense_Activate, listener(app, i_OnClick_menu_maxLicense_activate, App));
      menuitem_OnClick(maxLicense_Inspect, listener(app, i_OnClick_menu_maxLicense_inspect, App));
      menuitem_OnClick(maxLicense_Request, listener(app, i_OnClick_menu_maxLicense_request, App));

    /* drop down menu items for maxOrchestrator */
    submenu_maxOrchestrator = menu_create();
    osapp_menubar(submenu_maxOrchestrator, app->window);
      maxOrchestrator_Start = menuitem_create(); menuitem_enabled(maxOrchestrator_Start, 1); menuitem_visible(maxOrchestrator_Start, 1);
      maxOrchestrator_Stop = menuitem_create(); menuitem_enabled(maxOrchestrator_Stop, 1); menuitem_visible(maxOrchestrator_Stop, 1); menuitem_state(maxOrchestrator_Stop, ekGUI_ON);
      maxOrchestrator_DefineFlow = menuitem_create(); menuitem_enabled(maxOrchestrator_DefineFlow, 1); menuitem_visible(maxOrchestrator_DefineFlow, 1);
      maxOrchestrator_separator = menuitem_separator();

      image_maxOrchestrator_start = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-start-24.png", NULL);
      image_maxOrchestrator_stop = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-stop-24.png", NULL);
      image_maxOrchestrator_defineflow = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-flow-24.png", NULL);

      menuitem_text(maxOrchestrator_Start, "Start instance");
      menuitem_text(maxOrchestrator_Stop, "Stop instance");
      menuitem_text(maxOrchestrator_DefineFlow, "Define dataflow ...");

      menu_add_item(submenu_maxOrchestrator, maxOrchestrator_Start); menuitem_image(maxOrchestrator_Start, image_maxOrchestrator_start);
      menu_add_item(submenu_maxOrchestrator, maxOrchestrator_Stop); menuitem_image(maxOrchestrator_Stop, image_maxOrchestrator_stop);
      menu_add_item(submenu_maxOrchestrator, maxOrchestrator_separator);
      menu_add_item(submenu_maxOrchestrator, maxOrchestrator_DefineFlow); menuitem_image(maxOrchestrator_DefineFlow, image_maxOrchestrator_defineflow);

      menuitem_submenu(maxOrchestrator, &submenu_maxOrchestrator);

      menuitem_OnClick(maxOrchestrator_Start, listener(app, i_OnClick_menu_maxOrchestrator_start, App));
      menuitem_OnClick(maxOrchestrator_Stop, listener(app, i_OnClick_menu_maxOrchestrator_stop, App));
      menuitem_OnClick(maxOrchestrator_DefineFlow, listener(app, i_OnClick_menu_maxOrchestrator_defineDataflow, App));



    /* drop down menu items for maxServices */
    submenu_maxServices = menu_create();
    osapp_menubar(submenu_maxServices, app->window);
      maxServices_UsersAccount = menuitem_create(); menuitem_enabled(maxServices_UsersAccount, 1); menuitem_visible(maxServices_UsersAccount, 1);
      maxServices_SystemsAccount = menuitem_create(); menuitem_enabled(maxServices_SystemsAccount, 1); menuitem_visible(maxServices_SystemsAccount, 1);
      maxServices_GenerateSSLCertificates = menuitem_create(); menuitem_enabled(maxServices_GenerateSSLCertificates, 1); menuitem_visible(maxServices_GenerateSSLCertificates, 1);

      image_maxServices_usersaccount = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-users-24.png", NULL);
      image_maxServices_systemsaccount = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-access-24.png", NULL);
      image_maxServices_generatesslcertificates = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-security-ssl-24.png", NULL);

      menuitem_text(maxServices_UsersAccount, "Users Account            ");
      menuitem_text(maxServices_SystemsAccount,	"Systems Account          ");
      menuitem_text(maxServices_GenerateSSLCertificates, "Generate SSL Certificates");

      menu_add_item(submenu_maxServices, maxServices_UsersAccount); menuitem_image(maxServices_UsersAccount, image_maxServices_usersaccount);
      menu_add_item(submenu_maxServices, maxServices_SystemsAccount); menuitem_image(maxServices_SystemsAccount, image_maxServices_systemsaccount);
      menu_add_item(submenu_maxServices, maxServices_GenerateSSLCertificates); menuitem_image(maxServices_GenerateSSLCertificates, image_maxServices_generatesslcertificates);

      menuitem_submenu(maxServices, &submenu_maxServices);

      menuitem_OnClick(maxServices_UsersAccount, listener(app, i_OnClick_menu_maxservices_usersaccount, App));
      menuitem_OnClick(maxServices_SystemsAccount, listener(app, i_OnClick_menu_maxservices_systemsaccount, App));
      menuitem_OnClick(maxServices_GenerateSSLCertificates, listener(app, i_OnClick_menu_maxservices_generatesslcertificates, App));

    /* drop down menu items for Client */
    submenu_client = menu_create();
    osapp_menubar(submenu_client, app->window);
      client_add = menuitem_create(); menuitem_enabled(client_add, 1); menuitem_visible(client_add, 1);
      client_remove = menuitem_create(); menuitem_enabled(client_remove, 1); menuitem_visible(client_remove, 1);
      client_connect = menuitem_create(); menuitem_enabled(client_connect, 1); menuitem_visible(client_connect, 1);
      client_disconnect = menuitem_create(); menuitem_enabled(client_disconnect, 1); menuitem_visible(client_disconnect, 1);
      client_properties = menuitem_create(); menuitem_enabled(client_properties, 1); menuitem_visible(client_properties, 1);
      client_separator = menuitem_separator();
      client_changeuser = menuitem_create(); menuitem_enabled(client_changeuser, 1); menuitem_visible(client_changeuser, 1);
      client_changepassword = menuitem_create(); menuitem_enabled(client_changepassword, 1); menuitem_visible(client_changepassword, 1);

      menuitem_text(client_add,            "Add ...             ");
      menuitem_text(client_remove,         "Remove              ");
      menuitem_text(client_connect,        "Connect             ");
      menuitem_text(client_disconnect,     "Disconnect          ");
      menuitem_text(client_properties,     "Properties          ");
      menuitem_text(client_changeuser,     "Change user...      ");
      menuitem_text(client_changepassword, "Change password...  ");

      menu_add_item(submenu_client, client_add);
      menu_add_item(submenu_client, client_remove);
      menu_add_item(submenu_client, client_connect);
      menu_add_item(submenu_client, client_disconnect);
      menu_add_item(submenu_client, client_properties);
      menu_add_item(submenu_client, client_separator);
      menu_add_item(submenu_client, client_changeuser);
      menu_add_item(submenu_client, client_changepassword);

      menuitem_submenu(client, &submenu_client);

      menuitem_OnClick(client_add, listener(app, i_OnClick_client_add, App));
      menuitem_OnClick(client_remove, listener(app, i_OnClick_client_remove, App));
      menuitem_OnClick(client_connect, listener(app, i_OnClick_client_connect, App));
      menuitem_OnClick(client_disconnect, listener(app, i_OnClick_client_disconnect, App));
      menuitem_OnClick(client_properties, listener(app, i_OnClick_client_properties, App));
      menuitem_OnClick(client_changeuser, listener(app, i_OnClick_client_changeuser, App));
      menuitem_OnClick(client_changepassword, listener(app, i_OnClick_client_changepassword, App));

    /* drop down menu items for Server */
    submenu_server = menu_create();
    osapp_menubar(submenu_server, app->window);
      server_start = menuitem_create(); menuitem_enabled(server_start, 1); menuitem_visible(server_start, 1);
      server_stop = menuitem_create(); menuitem_enabled(server_stop, 1); menuitem_visible(server_stop, 1);
      server_properties = menuitem_create(); menuitem_enabled(server_properties, 1); menuitem_visible(server_properties, 1);
      server_separator = menuitem_separator();
      server_adduser = menuitem_create(); menuitem_enabled(server_adduser, 1); menuitem_visible(server_adduser, 1);
      server_edituser = menuitem_create(); menuitem_enabled(server_edituser, 1); menuitem_visible(server_edituser, 1);

      menuitem_text(server_start, "Start");
      menuitem_text(server_stop, "Stop");
      menuitem_text(server_properties, "Properties");
      menuitem_text(server_adduser, "Add users");
      menuitem_text(server_edituser, "Edit users");

      menu_add_item(submenu_server, server_start);
      menu_add_item(submenu_server, server_stop);
      menu_add_item(submenu_server, server_properties);
      menu_add_item(submenu_server, server_separator);
      menu_add_item(submenu_server, server_adduser);
      menu_add_item(submenu_server, server_edituser);

      menuitem_submenu(server, &submenu_server);
      menuitem_OnClick(server_start, listener(app, i_OnClick_server_start, App));
      menuitem_OnClick(server_stop, listener(app, i_OnClick_server_stop, App));
      menuitem_OnClick(server_properties, listener(app, i_OnClick_server_properties, App));
      menuitem_OnClick(server_adduser, listener(app, i_OnClick_server_adduser, App));
      menuitem_OnClick(server_edituser, listener(app, i_OnClick_server_edituser, App));

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

    /* drop down menu items for Toolbars */
    submenu_toolbars = menu_create();
    osapp_menubar(submenu_toolbars, app->window);

      app->view_fileToolbar = menuitem_create(); menuitem_enabled(app->view_fileToolbar, 1); menuitem_visible(app->view_fileToolbar, 1);
      app->view_viewToolbar = menuitem_create(); menuitem_enabled(app->view_viewToolbar, 1); menuitem_visible(app->view_viewToolbar, 1);
      app->view_maxEngineToolbar = menuitem_create(); menuitem_enabled(app->view_maxEngineToolbar, 1); menuitem_visible(app->view_maxEngineToolbar, 1);
      app->view_maxCoreToolbar = menuitem_create(); menuitem_enabled(app->view_maxCoreToolbar, 1); menuitem_visible(app->view_maxCoreToolbar, 1);
      app->view_maxIntegratorToolbar = menuitem_create(); menuitem_enabled(app->view_maxIntegratorToolbar, 1); menuitem_visible(app->view_maxIntegratorToolbar, 1);
      app->view_maxAdapterToolbar = menuitem_create(); menuitem_enabled(app->view_maxAdapterToolbar, 1); menuitem_visible(app->view_maxAdapterToolbar, 1);
      app->view_maxGateToolbar = menuitem_create(); menuitem_enabled(app->view_maxGateToolbar, 1); menuitem_visible(app->view_maxGateToolbar, 1);
      app->view_maxScaleToolbar = menuitem_create(); menuitem_enabled(app->view_maxScaleToolbar, 1); menuitem_visible(app->view_maxScaleToolbar, 1);
      app->view_maxOrchestratorToolbar = menuitem_create(); menuitem_enabled(app->view_maxOrchestratorToolbar, 1); menuitem_visible(app->view_maxOrchestratorToolbar, 1);
      app->view_maxMindToolbar = menuitem_create();  menuitem_enabled(app->view_maxMindToolbar, 1); menuitem_visible(app->view_maxMindToolbar, 1);
      app->view_maxLicenseToolbar = menuitem_create();  menuitem_enabled(app->view_maxLicenseToolbar, 1); menuitem_visible(app->view_maxLicenseToolbar, 1);
      app->view_maxServicesToolbar = menuitem_create(); menuitem_enabled(app->view_maxServicesToolbar, 1); menuitem_visible(app->view_maxServicesToolbar, 1);
      app->view_documentToolbar = menuitem_create(); menuitem_enabled(app->view_documentToolbar, 1); menuitem_visible(app->view_documentToolbar, 1);

      menuitem_text(app->view_fileToolbar,            "Project             ");
	if (app->view_fileToolbar_IsShown)
		menuitem_state(app->view_fileToolbar, ekGUI_ON);
	else
		menuitem_state(app->view_fileToolbar, ekGUI_OFF);

      menuitem_text(app->view_viewToolbar,            "View             "); menuitem_state(app->view_viewToolbar, ekGUI_ON);
      menuitem_text(app->view_maxEngineToolbar,       "maxEngine        "); menuitem_state(app->view_maxEngineToolbar, ekGUI_ON);
      menuitem_text(app->view_maxAdapterToolbar,      "maxAdapter       "); menuitem_state(app->view_maxAdapterToolbar, ekGUI_ON);
      menuitem_text(app->view_maxCoreToolbar, 	      "maxCore          "); menuitem_state(app->view_maxCoreToolbar, ekGUI_ON);
      menuitem_text(app->view_maxOrchestratorToolbar, "maxOrchestrator  "); menuitem_state(app->view_maxOrchestratorToolbar, ekGUI_ON);
      menuitem_text(app->view_maxIntegratorToolbar,   "maxIntegrator    "); menuitem_state(app->view_maxIntegratorToolbar, ekGUI_ON);
      menuitem_text(app->view_maxScaleToolbar,        "maxScale         "); menuitem_state(app->view_maxScaleToolbar, ekGUI_ON);
      menuitem_text(app->view_maxMindToolbar,         "maxMind          "); menuitem_state(app->view_maxMindToolbar, ekGUI_ON);
      menuitem_text(app->view_maxGateToolbar,         "maxGate          "); menuitem_state(app->view_maxGateToolbar, ekGUI_ON);
      menuitem_text(app->view_maxLicenseToolbar,      "maxLicense       "); menuitem_state(app->view_maxLicenseToolbar, ekGUI_ON);
      menuitem_text(app->view_maxServicesToolbar,     "maxServices      "); menuitem_state(app->view_maxServicesToolbar, ekGUI_ON);
      menuitem_text(app->view_documentToolbar,        "Document         "); menuitem_state(app->view_documentToolbar, ekGUI_ON);


      toolbar_separator = menuitem_separator();
      menu_add_item(submenu_toolbars, app->view_fileToolbar); menuitem_image(app->view_fileToolbar, image_view_fileToolbar);
      menu_add_item(submenu_toolbars, app->view_viewToolbar); menuitem_image(app->view_viewToolbar, image_view_viewToolbar);
      menu_add_item(submenu_toolbars, toolbar_separator);
      menu_add_item(submenu_toolbars, app->view_maxEngineToolbar); menuitem_image(app->view_maxEngineToolbar, image_view_maxEngineToolbar);
      menu_add_item(submenu_toolbars, app->view_maxAdapterToolbar); menuitem_image(app->view_maxAdapterToolbar, image_view_maxAdapterToolbar);
      menu_add_item(submenu_toolbars, app->view_maxCoreToolbar); menuitem_image(app->view_maxCoreToolbar, image_view_maxCoreToolbar);
      menu_add_item(submenu_toolbars, app->view_maxOrchestratorToolbar); menuitem_image(app->view_maxOrchestratorToolbar, image_view_maxOrchestratorToolbar);
      menu_add_item(submenu_toolbars, app->view_maxIntegratorToolbar); menuitem_image(app->view_maxIntegratorToolbar, image_view_maxIntegratorToolbar);
      menu_add_item(submenu_toolbars, app->view_maxScaleToolbar); menuitem_image(app->view_maxScaleToolbar, image_view_maxScaleToolbar);
      menu_add_item(submenu_toolbars, app->view_maxMindToolbar); menuitem_image(app->view_maxMindToolbar, image_view_maxMindToolbar);
      menu_add_item(submenu_toolbars, app->view_maxGateToolbar); menuitem_image(app->view_maxGateToolbar, image_view_maxGateToolbar);
      menu_add_item(submenu_toolbars, app->view_maxLicenseToolbar); menuitem_image(app->view_maxLicenseToolbar, image_view_maxLicenseToolbar);
      menu_add_item(submenu_toolbars, app->view_maxServicesToolbar); menuitem_image(app->view_maxServicesToolbar, image_view_maxServicesToolbar);
      menu_add_item(submenu_toolbars, app->view_documentToolbar); menuitem_image(app->view_documentToolbar, image_view_documentToolbar);

      menuitem_submenu(toolbars, &submenu_toolbars);

      menuitem_OnClick(app->view_fileToolbar, listener(app, i_OnClick_menu_view_filetoolbar, App));
      menuitem_OnClick(app->view_viewToolbar, listener(app, i_OnClick_menu_view_viewtoolbar, App));
      menuitem_OnClick(app->view_maxEngineToolbar, listener(app, i_OnClick_menu_view_maxEnginetoolbar, App));
      menuitem_OnClick(app->view_maxCoreToolbar, listener(app, i_OnClick_menu_view_maxCoretoolbar, App));
      menuitem_OnClick(app->view_maxIntegratorToolbar, listener(app, i_OnClick_menu_view_maxIntegratortoolbar, App));
      menuitem_OnClick(app->view_maxAdapterToolbar, listener(app, i_OnClick_menu_view_maxAdaptertoolbar, App));
      menuitem_OnClick(app->view_maxGateToolbar, listener(app, i_OnClick_menu_view_maxGatetoolbar, App));
      menuitem_OnClick(app->view_maxOrchestratorToolbar, listener(app, i_OnClick_menu_view_maxOrchestratortoolbar, App));
      menuitem_OnClick(app->view_maxMindToolbar, listener(app, i_OnClick_menu_view_maxMindtoolbar, App));
      menuitem_OnClick(app->view_maxLicenseToolbar, listener(app, i_OnClick_menu_view_maxLicensetoolbar, App));
      menuitem_OnClick(app->view_maxServicesToolbar, listener(app, i_OnClick_menu_view_maxServicestoolbar, App));
      menuitem_OnClick(app->view_documentToolbar, listener(app, i_OnClick_menu_view_documenttoolbar, App));

    /* drop down menu items for Settings */
    submenu_settings = menu_create();
    osapp_menubar(submenu_settings, app->window);
      settings_plugins = menuitem_create(); menuitem_enabled(settings_plugins, 1); menuitem_visible(settings_plugins, 1);
      settings_configure = menuitem_create(); menuitem_enabled(settings_configure, 1); menuitem_visible(settings_configure, 1);
      settings_interfaces = menuitem_create(); menuitem_enabled(settings_interfaces, 1); menuitem_visible(settings_interfaces, 1);
      settings_separator = menuitem_separator();
      settings_managecertificates = menuitem_create(); menuitem_enabled(settings_managecertificates, 1); menuitem_visible(settings_managecertificates, 1);

      menuitem_text(settings_plugins,   "Plugins...                ");
      menuitem_text(settings_configure, "Configure ...     ");
      menuitem_text(settings_interfaces, "Interfaces ...    ");
      menuitem_text(settings_managecertificates, "Manage Certificates    ");

      menu_add_item(submenu_settings, settings_plugins);
      menu_add_item(submenu_settings, settings_configure);
      menu_add_item(submenu_settings, settings_interfaces);
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

      /* =========== submenu for Settings->Interfaces */
      /* here we create a submenu of industrial interfaces */
      submenu_settings_interfaces = menu_create();
      osapp_menubar(submenu_settings_interfaces, app->window);
      interfaces_modbusTCP = menuitem_create();  menuitem_enabled(interfaces_modbusTCP, 1); menuitem_visible(interfaces_modbusTCP, 1);
      interfaces_modbusRTU = menuitem_create(); menuitem_enabled(interfaces_modbusRTU, 1); menuitem_visible(interfaces_modbusRTU, 1);
      interfaces_EtherCAT = menuitem_create(); menuitem_enabled(interfaces_EtherCAT, 1); menuitem_visible(interfaces_EtherCAT, 1);
      interfaces_TwinCATADS = menuitem_create(); menuitem_enabled(interfaces_TwinCATADS, 1); menuitem_visible(interfaces_TwinCATADS, 1);
      interfaces_EthernetIP = menuitem_create(); menuitem_enabled(interfaces_EthernetIP, 1); menuitem_visible(interfaces_EthernetIP, 1);
      interfaces_ProfiNet = menuitem_create(); menuitem_enabled(interfaces_ProfiNet, 1); menuitem_visible(interfaces_ProfiNet, 1);

      menuitem_text(interfaces_modbusTCP, "Modbus TCP");
      menuitem_text(interfaces_modbusRTU, "Modbus RTU");
      menuitem_text(interfaces_EtherCAT, "EtherCAT");
      menuitem_text(interfaces_TwinCATADS, "TwinCAT ADS");
      menuitem_text(interfaces_EthernetIP, "Ethernet/IP");
      menuitem_text(interfaces_ProfiNet, "ProfiNet");

      menu_add_item(submenu_settings_interfaces, interfaces_modbusTCP);
      menu_add_item(submenu_settings_interfaces, interfaces_modbusRTU);
      menu_add_item(submenu_settings_interfaces, interfaces_EtherCAT);
      menu_add_item(submenu_settings_interfaces, interfaces_TwinCATADS);
      menu_add_item(submenu_settings_interfaces, interfaces_EthernetIP);
      menu_add_item(submenu_settings_interfaces, interfaces_ProfiNet);

      menuitem_submenu(settings_interfaces, &submenu_settings_interfaces);


      /* assign callbacks */
      menuitem_OnClick(settings_plugins, listener(app, i_OnClick_settings_plugins, App));
      menuitem_OnClick(configure_OPCSvr, listener(app, i_OnClick_settings_configure_OPCSvr, App));
      menuitem_OnClick(configure_LDS, listener(app, i_OnClick_settings_configure_LDS, App));
      menuitem_OnClick(configure_GDS, listener(app, i_OnClick_settings_configure_GDS, App));
      menuitem_OnClick(configure_MSB, listener(app, i_OnClick_settings_configure_message_broker, App));
      menuitem_OnClick(interfaces_modbusTCP, listener(app, i_OnClick_settings_interfaces_modbusTCP, App));
      menuitem_OnClick(interfaces_modbusTCP, listener(app, i_OnClick_settings_interfaces_modbusRTU, App));
      menuitem_OnClick(interfaces_EtherCAT, listener(app, i_OnClick_settings_interfaces_EtherCAT, App));
      menuitem_OnClick(interfaces_TwinCATADS, listener(app, i_OnClick_settings_interfaces_TwinCATADS, App));
      menuitem_OnClick(interfaces_EthernetIP, listener(app, i_OnClick_settings_interfaces_EthernetIP, App));
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

      image_help_manual = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-manual-24.png", NULL);
      image_help_whatsthis = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-info-24.png", NULL);
      image_help_licensestatus = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-license-24.png", NULL);
      image_help_checkforupdates = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-available-updates-24.png", NULL);
      image_help_about = image_from_file("/home/pi/nappgui_src/jacky/img/maxMachines-logo-clear.png", NULL);
      /*image_help_about = image_from_file("/home/pi/nappgui_src/jacky/img/icons-MaxMachines-24.jpeg", NULL);*/

      menuitem_text(help_manual,          "Manual                ");
      menuitem_text(help_whatsthis,       "What's This?          ");
      menuitem_text(help_licensestatus,   "License Status...     ");
      menuitem_text(help_checkforupdates, "Check for Updates...  ");
      menuitem_text(help_about,           "About MaxMachines     ");

      menu_add_item(submenu_help, help_manual); menuitem_image(help_manual, image_help_manual);
      menu_add_item(submenu_help, help_whatsthis); menuitem_image(help_whatsthis, image_help_whatsthis);
      menu_add_item(submenu_help, help_licensestatus); menuitem_image(help_licensestatus, image_help_licensestatus);
      menu_add_item(submenu_help, help_checkforupdates); menuitem_image(help_checkforupdates, image_help_checkforupdates);
      menu_add_item(submenu_help, help_separator);
      menu_add_item(submenu_help, help_about); menuitem_image(help_about, image_help_about);

      menuitem_submenu(help, &submenu_help);

      menuitem_OnClick(help_manual, listener(app, i_OnClick_menu_help_manual, App));
      menuitem_OnClick(help_whatsthis, listener(app, i_OnClick_menu_help_whatsthis, App));
      menuitem_OnClick(help_licensestatus, listener(app, i_OnClick_menu_help_licensestatus, App));
      menuitem_OnClick(help_checkforupdates, listener(app, i_OnClick_menu_help_checkforupdates, App));
      menuitem_OnClick(help_about, listener(app, i_OnClick_menu_help_about, App));
#endif

}
