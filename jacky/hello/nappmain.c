/* NAppGUI Hello World */

#include <nappgui.h>
#include "table.h"
#include "res_guihello.h"
#include <gui/guiall.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "napp.h"
#include "mongoose.h"
#include <json-c/json.h>

CMapData *configKeyValuePair;   // global variable that stores the key-value pairs in airgardConfig file

typedef struct _treenode_t TreeNode;
typedef struct _appdata_t AppData;

struct _treenode_t
{
    char_t name[64];
    ArrPt(TreeNode) *children;
    bool_t expanded;
};

struct _appdata_t
{
    TableView *table;
    TextView *text;
    char_t temp_string[256];
    ArrPt(TreeNode) *tree_roots;
};

static const uint32_t i_NUM_ROOTS = 4;
static const uint32_t i_MAX_DEPTH = 5;
//DeclPt(TreeNode);


void i_OnClick_project_new(App *app, Event *e)
{
    textview_printf(app->textMaxManage, "Project->New Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->textMaxManage);
    app->clicks += 1;
    FileNew(app, app->window);
    unref(e);
}

void i_OnClick_project_open(App *app, Event *e)
{
    textview_printf(app->textMaxManage, "Project->Open Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->textMaxManage);
    app->clicks += 1;
    FileOpen(app, app->window);
    unref(e);
}

void i_OnClick_project_save(App *app, Event *e)
{
    textview_printf(app->textMaxManage, "Project->Save Menu click (%d)\n", app->clicks);
    textview_scroll_caret(app->textMaxManage);

    app->clicks += 1;
    FileSave(app, app->window);

    unref(e);
}

void i_OnClick_project_saveAs(App *app, Event *e)
{
    textview_printf(app->textMaxManage, "Project->Save As button click (%d)\n", app->clicks);
    textview_scroll_caret(app->textMaxManage);
    app->clicks += 1;
    FileSaveAs(app, app->window);
    unref(e);
}

void i_OnClick_project_close(App *app, Event *e)
{
    textview_printf(app->textMaxManage, "Project->Close buttion click (%d)\n", app->clicks);
    textview_scroll_caret(app->textMaxManage);
    app->clicks += 1;
    FileClose(app, app->window);
    unref(e);
}

void i_OnClick_project_quit(App *app, Event *e)
{
    textview_printf(app->textMaxManage, "Project->Quit button click (%d)\n", app->clicks);
    textview_scroll_caret(app->textMaxManage);
    app->clicks += 1;
    FileQuit(app, app->window);
    unref(e);
}


void i_OnClick_maxEngine_viewstatistics(App *app, Event *e)
{
    textview_printf(app->textMaxManage, "maxEngine->View Statistics Button click (%d)\n", app->clicks);
    textview_scroll_caret(app->textMaxManage);
    app->clicks += 1;
    maxEngineViewStatistics(app, app->window);
    unref(e);

}

void i_OnClick_maxEngine_viewlivelogs(App *app, Event *e)
{
    textview_printf(app->textMaxManage, "maxEngine->View Live Logs Button click (%d)\n", app->clicks);
    textview_scroll_caret(app->textMaxManage);
    app->clicks += 1;
    maxEngineViewLiveLogs(app, app->window);
    unref(e);

}

/**/

void i_OnClick_maxcore_registermaxadapters(App *app, Event *e)
{
    textview_printf(app->textMaxManage, "maxCore->Register maxAdapters Button click (%d)\n", app->clicks);
    textview_scroll_caret(app->textMaxManage);
    app->clicks += 1;
    maxCoreRegisterAdapters(app, app->window);
    unref(e);

}

void i_OnClick_maxCore_viewstatistics(App *app, Event *e)
{
    textview_printf(app->textMaxManage, "MaxCore->View statistics click (%d)\n", app->clicks);
    textview_scroll_caret(app->textMaxManage);
    app->clicks += 1;
    unref(e);
}


void i_OnClick_maxCore_registermaxadapters(App *app, Event *e)
{
    textview_printf(app->textMaxManage, "MaxCore->Register maxAdapter click (%d)\n", app->clicks);
    textview_scroll_caret(app->textMaxManage);
    app->clicks += 1;
    unref(e);
}

void i_OnClick_maxCore_startupparameters(App *app, Event *e)
{
    textview_printf(app->textMaxManage, "maxCore->Startup Parameters Button click (%d)\n", app->clicks);
    textview_scroll_caret(app->textMaxManage);
    app->clicks += 1;
    maxCoreStartupParameters(app, app->window);
    unref(e);

}

void i_OnClick_maxCore_viewlivelogs(App *app, Event *e)
{
    textview_printf(app->textMaxManage, "MaxCore->View Live Logs click (%d)\n", app->clicks);
    textview_scroll_caret(app->textMaxManage);
    app->clicks += 1;
    unref(e);
}

/**/
void i_OnClick_maxServices_usersaccount(App *app, Event *e)
{
    textview_printf(app->textMaxManage, "maxServices->Users Account button click (%d)\n", app->clicks);
    textview_scroll_caret(app->textMaxManage);
    app->clicks += 1;
    maxServicesUsersAccount(app, app->window);
    unref(e);

}

void i_OnClick_maxServices_systemsaccount(App *app, Event *e)
{
    textview_printf(app->textMaxManage, "maxServices->Systems Account Button click (%d)\n", app->clicks);
    textview_scroll_caret(app->textMaxManage);
    app->clicks += 1;
    maxServicesSystemsAccount(app, app->window);
    unref(e);

}

void i_OnClick_maxServices_generatesslcertificates(App *app, Event *e)
{
    textview_printf(app->textMaxManage, "maxServices->Generate SSL Certificate Button click (%d)\n", app->clicks);
    textview_scroll_caret(app->textMaxManage);
    app->clicks += 1;
    maxServicesGenerateSSLCertificates(app, app->window);
    unref(e);

}



void i_OnClick_maxAdapter_reverseconnect(App *app, Event *e)
{
    textview_printf(app->textMaxManage, "MaxAdapter->Reverse Connect click (%d)\n", app->clicks);
    textview_scroll_caret(app->textMaxManage);
    app->clicks += 1;
    unref(e);
}

void i_OnClick_maxAdapter_startupparameters(App *app, Event *e)
{
    textview_printf(app->textMaxManage, "MaxAdapter->Startup parameters click (%d)\n", app->clicks);
    textview_scroll_caret(app->textMaxManage);
    app->clicks += 1;
    unref(e);
}

#include <gui/guiall.h>
//static const uint32_t i_NUM_ROOTS = 4;
//static const uint32_t i_MAX_DEPTH = 5;
DeclPt(TreeNode);

//typedef struct _treenode_t TreeNode;
//typedef struct _appdata_t AppData;


void i_OnTreeDataTableLeftTop1(AppData *data, Event *e)
{
    uint32_t etype = event_type(e);

    switch (etype)
    {
    case ekGUI_EVENT_TBL_NROWS:
    {
        uint32_t *n = event_result(e, uint32_t);
        *n = 100;
        break;
    }

    case ekGUI_EVENT_TBL_NCHILDREN:
    {
        void *parent = event_params(e, void);
        uint32_t *n = event_result(e, uint32_t);
        if (parent == NULL)
        {
            *n = i_NUM_ROOTS;
        }
        else
        {
            ArrPt(TreeNode) *children = cast(parent, TreeNode)->children;
            *n = arrpt_size(children, TreeNode);
        }
        break;
    }

    case ekGUI_EVENT_TBL_NODEINFO:
    {
        const EvTbNode *p = event_params(e, EvTbNode);
        EvTbNodeInfo *info = event_result(e, EvTbNodeInfo);
        ArrPt(TreeNode) *children = NULL;
        TreeNode *node = NULL;

        if (p->parent != NULL)
            children = cast(p->parent, TreeNode)->children;
        else
            children = data->tree_roots;

        node = arrpt_get(children, p->ichild, TreeNode);
        info->node = node;
        info->children = node->children != NULL ? (arrpt_size(node->children, TreeNode) > 0) : FALSE;
        info->expanded = node->expanded;
        break;
    }

    case ekGUI_EVENT_TBL_EXPAND:
    {
        const EvTbExpand *p = event_params(e, EvTbExpand);
        cast(p->node, TreeNode)->expanded = p->expanded;
        break;
    }

    case ekGUI_EVENT_TBL_CELL:
    {
        const EvTbPos *pos = event_params(e, EvTbPos);
        EvTbCell *cell = event_result(e, EvTbCell);

        switch (pos->col)
        {
        case 0:
            cell->align = ekLEFT;
            if (pos->node != NULL)
                bstd_sprintf(data->temp_string, sizeof(data->temp_string), "%s", cast_const(pos->node, TreeNode)->name);
            else
                bstd_sprintf(data->temp_string, sizeof(data->temp_string), "Name %d", pos->row);
            break;

        case 1:
            cell->align = ekLEFT;
            if (pos->row % 3 == 0)
                cell->icon = gui_image(ERROR16_PNG);
            else if (pos->row % 3 == 1)
                cell->icon = gui_image(EDIT16_PNG);
            else
                cell->icon = gui_image(DISK16_PNG);

            bstd_sprintf(data->temp_string, sizeof(data->temp_string), "Adress %d", pos->row);
            break;

        case 2:
            cell->align = ekLEFT;
            bstd_sprintf(data->temp_string, sizeof(data->temp_string), "City %d", pos->row);
            break;

        case 3:
            cell->align = ekRIGHT;
            bstd_sprintf(data->temp_string, sizeof(data->temp_string), "%d", pos->row);
            break;

        case 4:
            cell->align = ekRIGHT;
            bstd_sprintf(data->temp_string, sizeof(data->temp_string), "%.2f", 10.5f + (real32_t)pos->row);
            break;

        case 5:
            cell->align = ekCENTER;
            bstd_sprintf(data->temp_string, sizeof(data->temp_string), "Extra Data 1 %d", pos->row);
            break;

        case 6:
            cell->align = ekCENTER;
            bstd_sprintf(data->temp_string, sizeof(data->temp_string), "Extra Data 2 %d", pos->row);
            break;

        case 7:
            cell->align = ekCENTER;
            bstd_sprintf(data->temp_string, sizeof(data->temp_string), "Extra Data 3 %d", pos->row);
            break;

        case 8:
            cell->align = ekCENTER;
            bstd_sprintf(data->temp_string, sizeof(data->temp_string), "Extra Data 4 %d", pos->row);
            break;

        default:
            cassert_default(pos->col);
        }

        cell->text = data->temp_string;

        break;
    }

    default:
        break;
    }

}


void i_OnTreeDataTableLeftBottom1(AppData *app, Event *e)
{
    uint32_t etype = event_type(e);

    switch(etype)
    {
	case ekGUI_EVENT_TBL_NCHILDREN :
	{

/*
		uint32_t *n = event_result(e, uint32_t);
// taken from https://nappgui.com/en/gui/tableview.html#f9

		if (node != NULL)
			*n = app_num_children(app, node);
		else
			*n = app_num_roots(app);
		break;
*/

/*
// taken from guihello/table.c
        	void *parent = event_params(e, void);
        	if (parent == NULL)
        	{
            	*n = i_NUM_ROOTS;
        	}
        	else
        	{
	            ArrPt(TreeNode) *children = cast(parent, TreeNode)->children;
        	    *n = arrpt_size(children, TreeNode);
	        }
		break;
*/

	}
	case ekGUI_EVENT_TBL_NODEINFO :
	{
/*
        const EvTbNode *p = event_params(e, EvTbNode);
        EvTbNodeInfo *info = event_result(e, EvTbNodeInfo);
        ArrPt(TreeNode) *children = NULL;
        TreeNode *node = NULL;

        if (p->parent != NULL)
            children = cast(p->parent, TreeNode)->children;
        else
            children = data->tree_roots;

        node = arrpt_get(children, p->ichild, TreeNode);
        info->node = node;
        info->children = node->children != NULL ? (arrpt_size(node->children, TreeNode) > 0) : FALSE;
        info->expanded = node->expanded;
        break;
*/
/*
		const EvTbNode *p = event_params(e, EvTbNode);
		EvTbNodeInfo *info = event_result(e, EvTbNodeInfo);
		info->node = node_get_child(app, p->node, p->ichild);
		info->expanded = node_is_expanded(app, p->node);
		info->children = node_with_children(app, p->node);
		break;
*/
	break;
	}
	case ekGUI_EVENT_TBL_EXPAND :
	{
/*
		const EvTbExpand *p = event_params(e, EvTbExpand);
		node_set_expanded(app, p->nosw, p->expanded);
		break;
*/
/*
        const EvTbExpand *p = event_params(e, EvTbExpand);
        cast(p->node, TreeNode)->expanded = p->expanded;
        break;
*/
	break;
	}
	case ekGUI_EVENT_TBL_NROWS:
	{
		uint32_t* n = event_result(e, uint32_t);
		*n = 10;
		break;
	}

	case ekGUI_EVENT_TBL_CELL :
	{

		const EvTbPos *pos = event_params(e, EvTbPos);
		EvTbCell *cell = event_result(e, EvTbCell);
		String* str = str_printf("%d-%d", pos->col, pos->row);
		cell->text = tc(str);
	break;
	}

	default: break;
    }
}


void i_OnTreeDataTableCentreTop1(App *app, Event *e)
{
    uint32_t etype = event_type(e);
    switch(etype)
    {
        case ekGUI_EVENT_TBL_NCHILDREN:
        {
/*
            void *node = event_params(e, void);
            uint32_t *n = event_result(e, uint32_t);
            if (node != NULL)
                *n = app_num_children(app, node);
            else
                *n = app_num_roots(app);
*/
            break;
        }

        case ekGUI_EVENT_TBL_NODEINFO:
        {
/*
            const EvTbNode *p = event_params(e, EvTbNode);
            EvTbNodeInfo *info = event_result(e, EvTbNodeInfo);
            info->node = node_get_child(app, p->node, p->ichild);
            info->expanded = node_is_expanded(app, p->node);
            info->children = node_with_children(app, p->node);
*/
            break;
        }

        case ekGUI_EVENT_TBL_EXPAND:
        {
/*
            const EvTbExpand *p = event_params(e, EvTbExpand);
            node_set_expanded(app, p->node, p->expanded);
*/
            break;
        }

        case ekGUI_EVENT_TBL_NROWS:
        {
                uint32_t* n = event_result(e, uint32_t);
                *n = 20;
                break;
        }


	case ekGUI_EVENT_TBL_BEGIN:
	{
            const EvTbRect *rect = event_params(e, EvTbRect);
       //     app->cache = app_fill_cache(app, rect->strow, rect->edrow, rect->stcol, rect->edcol);
            break;
	}


        case ekGUI_EVENT_TBL_CELL:
        {
            const EvTbPos *pos = event_params(e, EvTbPos);
            EvTbCell *cell = event_result(e, EvTbCell);
	    String* str = str_printf("%d-%d", pos->col, pos->row);
	    cell->text = tc(str);
            break;
        }

        case ekGUI_EVENT_TBL_END:
	{
        //    app_delete_cache(app->cache);
            break;
	}

	default: break;

    }

}


void i_OnClick_tab(App *app, Event *e)
{
    const EvButton *p = event_params(e, EvButton);
printf("p->index = %d \n", p->index);

    switch (p->index)
    {
        case 0 : textview_printf(app->textMaxManage, "p->index = %d (maxManage) \n", p->index);
                layout_textview(app->statusLayoutMaxManage, app->textMaxManage, 0, 1);
                panel_visible_layout(app->statusPanel, app->layoutIndexMaxManage);
                panel_update(app->statusPanel);
                textview_scroll_visible(app->textMaxManage, TRUE, TRUE);
                break;
	case 1 : textview_printf(app->textMaxEngine, "p->index = %d (maxEngine) \n", p->index);
		layout_textview(app->statusLayoutMaxEngine, app->textMaxEngine, 0, 1);
		panel_visible_layout(app->statusPanel, app->layoutIndexMaxEngine);
    		panel_update(app->statusPanel);
		textview_scroll_visible(app->textMaxEngine, TRUE, TRUE);
		break;
	case 2 : textview_printf(app->textMaxAdapter, "p->index = %d (maxAdapter) \n", p->index);
		layout_textview(app->statusLayoutMaxAdapter, app->textMaxAdapter, 0, 1);
    		panel_visible_layout(app->statusPanel, app->layoutIndexMaxAdapter);
    		panel_update(app->statusPanel);
		textview_scroll_visible(app->textMaxAdapter, TRUE, TRUE);
		break;
	case 3 : textview_printf(app->textMaxCore, "p->index = %d (maxCore) \n", p->index);
		layout_textview(app->statusLayoutMaxCore, app->textMaxCore, 0, 1);
		panel_visible_layout(app->statusPanel, app->layoutIndexMaxCore);
                panel_update(app->statusPanel);
		textview_scroll_visible(app->textMaxCore, TRUE, TRUE);
		break;
	case 4 : textview_printf(app->textMaxOrchestrator, "p->index = %d (maxOrchestrator) \n", p->index);
		layout_textview(app->statusLayoutMaxOrchestrator, app->textMaxOrchestrator, 0, 1);
		panel_visible_layout(app->statusPanel, app->layoutIndexMaxOrchestrator);
                panel_update(app->statusPanel);
		textview_scroll_visible(app->textMaxOrchestrator, TRUE, TRUE);
		break;
	case 5 : textview_printf(app->textMaxIntegrator, "p->index = %d (maxIntegrator) \n", p->index);
		layout_textview(app->statusLayoutMaxIntegrator, app->textMaxIntegrator, 0, 1);
		panel_visible_layout(app->statusPanel, app->layoutIndexMaxIntegrator);
                panel_update(app->statusPanel);
		textview_scroll_visible(app->textMaxIntegrator, TRUE, TRUE);
		break;
	case 6 : textview_printf(app->textMaxScale, "p->index = %d (maxScale) \n", p->index);
		layout_textview(app->statusLayoutMaxScale, app->textMaxScale, 0, 1);
		panel_visible_layout(app->statusPanel, app->layoutIndexMaxScale);
                panel_update(app->statusPanel);
		textview_scroll_visible(app->textMaxScale, TRUE, TRUE);
		break;
	case 7 : textview_printf(app->textMaxMind, "p->index = %d (maxMind) \n", p->index);
		layout_textview(app->statusLayoutMaxMind, app->textMaxMind, 0, 1);
		panel_visible_layout(app->statusPanel, app->layoutIndexMaxMind);
                panel_update(app->statusPanel);
		textview_scroll_visible(app->textMaxMind, TRUE, TRUE);
		break;
	case 8 : textview_printf(app->textMaxGate, "p->index = %d (maxGate) \n", p->index);
		layout_textview(app->statusLayoutMaxGate, app->textMaxGate, 0, 1);
		panel_visible_layout(app->statusPanel, app->layoutIndexMaxGate);
                panel_update(app->statusPanel);
		textview_scroll_visible(app->textMaxGate, TRUE, TRUE);
		break;
	case 9 : textview_printf(app->textMaxLicense, "p->index = %d (maxLicense) \n", p->index);
                layout_textview(app->statusLayoutMaxLicense, app->textMaxLicense, 0, 1);
		panel_visible_layout(app->statusPanel, app->layoutIndexMaxLicense);
                panel_update(app->statusPanel);
		textview_scroll_visible(app->textMaxLicense, TRUE, TRUE);
                break;
	case 10 : textview_printf(app->textMaxServices, "p->index = %d (maxServices) \n", p->index);
                layout_textview(app->statusLayoutMaxServices, app->textMaxServices, 0, 1);
		panel_visible_layout(app->statusPanel, app->layoutIndexMaxServices);
                panel_update(app->statusPanel);
		textview_scroll_visible(app->textMaxServices, TRUE, TRUE);
                break;

	default : break;

    }
    app->clicks += 1;
    unref(e);

}


static void createButtons(App *app)
{
    ferror_t error= ekFOK;

    Image *fileNewImg, *fileOpenImg, *fileSaveImg, *fileSaveAsImg, *fileCloseImg, *fileQuitImg;
    Image *viewInterconnectivityImg, *viewProjectImg, *viewAddressSpaceImg, *viewLogImg, *viewAttributesImg,*viewReferencesImg;
    Image *maxEngineOneClickStartInstanceImg, *maxEngineOneClickStopInstanceImg;
    //Image *maxEngineStartupParametersImg, *maxEngineCommunicationsProtocolsImg;
    Image *maxEngineViewStatisticsImg, *maxEngineViewLiveLogsImg;

    Image *maxCoreRegisterMaxAdaptersImg, *maxCoreStartupParametersImg, *maxCoreViewStatisticsImg;// *maxCoreViewLiveLogsImg, *maxCoreWebSocketServiceImg;

    Image *maxIntegratorStartInstanceImg, *maxIntegratorStopInstanceImg, *maxIntegratorRadiusServerImg, *maxIntegratorLdapServerImg, *maxIntegratorIdentityAndAccessServerImg;
    Image *maxIntegratorSyslogServerImg;
    Image *maxIntegratorAmqpImg, *maxIntegratorMqttImg, *maxIntegratorWebAPIServerImg, *maxIntegratorWebSocketServerImg;
    Image *maxIntegratorProxyImg, *maxIntegratorOPCUAServerImg, *maxIntegratorGlobalDirectoryServerImg, *maxIntegratorLocalDirectoryServerImg, *maxIntegratorHistorianServerImg;

    Image *maxAdapterAlarmsAndConditionsImg, *maxAdapterEventsImg, *maxAdapterLogsManagementImg, *maxAdapterReverseConnectImg; // *maxAdapterStartupParametersImg;
    Image *maxAdapterCommunicationsProtocolsImg, *maxAdapterViewStatisticsImg;
    Image *maxAdapterDiscoverDevicesImg, *maxAdapterAutoGenerateImg, *maxAdapterSimulateAndConnectImg, *maxAdapterEditDeviceNodesetImg, *maxAdapterManualConfigurationImg;

    Image *maxGateStartInstanceImg, *maxGateStopInstanceImg, *maxGateInspectInstanceImg, *maxGateManualConfigurationImg;
    Image *maxScaleSetupInstanceImg, *maxScaleConfigurationImg;
    Image *maxOrchestratorStartInstanceImg, *maxOrchestratorStopInstanceImg, *maxOrchestratorDefineDataFlowImg;
    Image *maxMindDigitalTwinImg, *maxMindRealTimeAnalyticsImg, *maxMindMachineLearningImg;
    Image *maxHelpManualImg, *maxHelpWhatsThisImg, *maxHelpLicenseStatusImg, *maxHelpCheckforUpdatesImg, *maxHelpAboutMaxMachinesImg;
    Image *maxServiceUsersAccountImg, *maxServiceSystemsAccountImg, *maxServiceGenerateSSLCertificatesImg;

    Button *buttonProjectNew, *buttonProjectOpen, *buttonProjectSave, *buttonProjectSaveAs, *buttonProjectClose, *buttonProjectQuit;
    Button *buttonViewInterconnectivity, *buttonViewProject, *buttonViewAddressSpace, *buttonViewLog, *buttonViewAttributes, *buttonViewReferences;
    Button *buttonmaxEngineOneClickStartInstance, *buttonmaxEngineOneClickStopInstance;
    Button *buttonmaxEngineViewStatistics, *buttonmaxEngineViewLiveLogs;

    Button *buttonmaxCoreStartInstance, *buttonmaxCoreStopInstance, *buttonmaxCoreRegistermaxAdapters, *buttonmaxCoreLogsManagement, *buttonmaxCoreStartupParameters;
    Button *buttonmaxCoreViewStatistics, *buttonmaxCoreViewLiveLogs, *buttonmaxCoreWebSocketService;

    Button *buttonmaxIntegratorStartInstance, *buttonmaxIntegratorStopInstance;
    Button *buttonmaxIntegratorRadiusServer, *buttonmaxIntegratorLdapServer, *buttonmaxIntegratorIdentityAndAccessServer;
    Button *buttonmaxIntegratorSyslogServer, *buttonmaxIntegratorProxyServer, *buttonmaxIntegratorMqttServer, *buttonmaxIntegratorAmqpServer;
    Button *buttonmaxIntegratorWebAPIServer, *buttonmaxIntegratorWebSocketServer;
    Button *buttonmaxIntegratorOPCUAServer, *buttonmaxIntegratorGlobalDirectoryServer, *buttonmaxIntegratorLocalDirectoryServer, *buttonmaxIntegratorHistorianServer;

    Button *buttonmaxAdapterStartInstance, *buttonmaxAdapterStopInstance;
    Button *buttonmaxAdapterAlarmsAndConditions, *buttonmaxAdapterEvents;
    Button *buttonmaxAdapterLogsManagement, *buttonmaxAdapterReverseConnect, *buttonmaxAdapterStartupParameters, *buttonmaxAdapterCommunicationsProtocols;
    Button *buttonmaxAdapterViewStatistics, *buttonmaxAdapterDiscoverDevices, *buttonmaxAdapterAutoGenerate, *buttonmaxAdapterSimulateAndConnect, *buttonmaxAdapterEditDeviceNodeset;
    Button *buttonmaxAdapterManualConfiguration;

    Button *buttonmaxGateStartInstance, *buttonmaxGateStopInstance, *buttonmaxGateInspectInstance, *buttonmaxGateManualConfiguration;
    Button *buttonmaxScaleSetupInstance, *buttonmaxScaleConfiguration;
    Button *buttonmaxOrchestratorStartInstance, *buttonmaxOrchestratorStopInstance, *buttonmaxOrchestratorDefineDataflow;
    Button *buttonmaxMindDigitalTwin, *buttonmaxMindRealTimeAnalytics, *buttonmaxMindMachineLearning;

    Button *buttonmaxServiceUsersAccount, *buttonmaxServiceSystemsAccount, *buttonmaxServiceGenerateSSLCertificates;
    Button *buttonHelpManual, *buttonHelpWhatsThis, *buttonHelpLicenseStatus, *buttonHelpCheckforUpdates, *buttonHelpAboutMaxMachines;

    /* ----------------initialise the objects */
    buttonProjectNew = button_flat(); button_tooltip(buttonProjectNew, "New");
	button_OnClick(buttonProjectNew, listener(app, i_OnClick_project_new, App));
    buttonProjectOpen = button_flat(); button_tooltip(buttonProjectOpen, "Open");
	button_OnClick(buttonProjectOpen, listener(app, i_OnClick_project_open, App));
    buttonProjectSave = button_flat(); button_tooltip(buttonProjectSave, "Save");
	button_OnClick(buttonProjectSave, listener(app, i_OnClick_project_save, App));
    buttonProjectSaveAs = button_flat(); button_tooltip(buttonProjectSaveAs, "Save as ..");
	button_OnClick(buttonProjectSaveAs, listener(app, i_OnClick_project_saveAs, App));
    buttonProjectClose = button_flat(); button_tooltip(buttonProjectClose, "Close");
	button_OnClick(buttonProjectClose, listener(app, i_OnClick_project_close, App));
    buttonProjectQuit = button_flat(); button_tooltip(buttonProjectQuit, "Quit");
	button_OnClick(buttonProjectQuit, listener(app, i_OnClick_project_quit, App));


    buttonViewInterconnectivity = button_flat(); button_tooltip(buttonViewInterconnectivity, "Interconnectivity");
    buttonViewProject = button_flat(); button_tooltip(buttonViewProject, "Project");
    buttonViewAddressSpace = button_flat(); button_tooltip(buttonViewAddressSpace, "Address Space");
    buttonViewLog = button_flat(); button_tooltip(buttonViewLog, "Log");
    buttonViewAttributes = button_flat(); button_tooltip(buttonViewAttributes, "Attributes");
    buttonViewReferences = button_flat(); button_tooltip(buttonViewReferences, "References");

    buttonmaxEngineOneClickStartInstance = button_flat(); button_tooltip(buttonmaxEngineOneClickStartInstance, "Start maxEngine");
    buttonmaxEngineOneClickStopInstance = button_flat(); button_tooltip(buttonmaxEngineOneClickStopInstance, "Stop maxEngine");
    buttonmaxEngineViewStatistics = button_flat(); button_tooltip(buttonmaxEngineViewStatistics, "View Statistics");
    buttonmaxEngineViewLiveLogs = button_flat(); button_tooltip(buttonmaxEngineViewLiveLogs, "View Live Logs");
	button_OnClick(buttonmaxEngineViewLiveLogs, listener(app, i_OnClick_maxEngine_viewlivelogs, App));

    buttonmaxCoreStartInstance = button_flat(); button_tooltip(buttonmaxCoreStartInstance, "Start instance");
    buttonmaxCoreStopInstance = button_flat(); button_tooltip(buttonmaxCoreStopInstance, "Stop instance");
    buttonmaxCoreRegistermaxAdapters = button_flat(); button_tooltip(buttonmaxCoreRegistermaxAdapters, "Register adapter");
	button_OnClick(buttonmaxCoreRegistermaxAdapters, listener(app, i_OnClick_maxCore_registermaxadapters, App));
    buttonmaxCoreLogsManagement = button_flat(); button_tooltip(buttonmaxCoreLogsManagement, "Logs management");
    buttonmaxCoreStartupParameters = button_flat(); button_tooltip(buttonmaxCoreStartupParameters, "Startup parameters");
	button_OnClick(buttonmaxCoreStartupParameters, listener(app, i_OnClick_maxCore_startupparameters, App));
    buttonmaxCoreViewStatistics = button_flat(); button_tooltip(buttonmaxCoreViewStatistics, "View Statistics");
	button_OnClick(buttonmaxCoreViewStatistics, listener(app, i_OnClick_maxCore_viewstatistics, App));

    buttonmaxAdapterStartInstance = button_flat(); button_tooltip(buttonmaxAdapterStartInstance, "Start Adapter");
    buttonmaxAdapterStopInstance = button_flat(); button_tooltip(buttonmaxAdapterStopInstance, "Stop Adapter");
    buttonmaxAdapterAlarmsAndConditions = button_flat(); button_tooltip(buttonmaxAdapterAlarmsAndConditions, "Alarms and Conditions");
    buttonmaxAdapterEvents = button_flat(); button_tooltip(buttonmaxAdapterEvents, "Events");
    buttonmaxAdapterLogsManagement = button_flat(); button_tooltip(buttonmaxAdapterLogsManagement, "Logs management");
    buttonmaxAdapterReverseConnect = button_flat(); button_tooltip(buttonmaxAdapterReverseConnect, "Reverse connect");
	button_OnClick(buttonmaxAdapterReverseConnect, listener(app, i_OnClick_maxAdapter_reverseconnect, App));
    buttonmaxAdapterStartupParameters = button_flat(); button_tooltip(buttonmaxAdapterStartupParameters, "Startup parameters");
	button_OnClick(buttonmaxAdapterStartupParameters, listener(app, i_OnClick_maxAdapter_startupparameters, App));
    buttonmaxAdapterCommunicationsProtocols = button_flat(); button_tooltip(buttonmaxAdapterCommunicationsProtocols, "Communications protocols");
    buttonmaxAdapterViewStatistics = button_flat(); button_tooltip(buttonmaxAdapterViewStatistics, "View statistics");
    buttonmaxAdapterDiscoverDevices = button_flat(); button_tooltip(buttonmaxAdapterDiscoverDevices, "Discover devices");
    buttonmaxAdapterAutoGenerate = button_flat(); button_tooltip(buttonmaxAdapterAutoGenerate, "Auto Generate");
    buttonmaxAdapterSimulateAndConnect = button_flat(); button_tooltip(buttonmaxAdapterSimulateAndConnect, "Simulate and Connect");
    buttonmaxAdapterEditDeviceNodeset = button_flat(); button_tooltip(buttonmaxAdapterEditDeviceNodeset, "Edit device nodeset");
    buttonmaxAdapterManualConfiguration = button_flat(); button_tooltip(buttonmaxAdapterManualConfiguration, "Manual Configuration");

    buttonmaxIntegratorStartInstance = button_flat();
    buttonmaxIntegratorStopInstance = button_flat();
    buttonmaxIntegratorRadiusServer = button_flat();
    buttonmaxIntegratorLdapServer = button_flat();
    buttonmaxIntegratorIdentityAndAccessServer = button_flat();
    buttonmaxIntegratorSyslogServer = button_flat();
    buttonmaxIntegratorProxyServer = button_flat(); button_tooltip(buttonmaxIntegratorProxyServer, "Proxy Server");
    buttonmaxIntegratorMqttServer = button_flat(); button_tooltip(buttonmaxIntegratorMqttServer, "Mqtt Server");
    buttonmaxIntegratorAmqpServer = button_flat(); button_tooltip(buttonmaxIntegratorAmqpServer, "Amqp Server");
    buttonmaxIntegratorWebAPIServer = button_flat();
    buttonmaxIntegratorOPCUAServer = button_flat();
    buttonmaxIntegratorGlobalDirectoryServer = button_flat();
    buttonmaxIntegratorLocalDirectoryServer = button_flat();
    buttonmaxIntegratorHistorianServer = button_flat();
    buttonmaxIntegratorWebSocketServer = button_flat();

    buttonmaxScaleSetupInstance = button_flat();
    buttonmaxScaleConfiguration = button_flat();

    buttonmaxMindDigitalTwin = button_flat();
    buttonmaxMindRealTimeAnalytics = button_flat();
    buttonmaxMindMachineLearning = button_flat();

    buttonmaxGateStartInstance = button_flat();
    buttonmaxGateStopInstance = button_flat();
    buttonmaxGateInspectInstance = button_flat();
    buttonmaxGateManualConfiguration = button_flat();

    buttonmaxOrchestratorStartInstance = button_flat();
    buttonmaxOrchestratorStopInstance = button_flat();
    buttonmaxOrchestratorDefineDataflow = button_flat();

    buttonmaxServiceUsersAccount = button_flat(); button_tooltip(buttonmaxServiceUsersAccount, "Users Account");
	button_OnClick(buttonmaxServiceUsersAccount, listener(app, i_OnClick_maxServices_usersaccount, App));
    buttonmaxServiceSystemsAccount = button_flat(); button_tooltip(buttonmaxServiceSystemsAccount, "Systems Account");
	button_OnClick(buttonmaxServiceSystemsAccount, listener(app, i_OnClick_maxServices_systemsaccount, App));
    buttonmaxServiceGenerateSSLCertificates = button_flat(); button_tooltip(buttonmaxServiceGenerateSSLCertificates, "Generate SSL");
	button_OnClick(buttonmaxServiceGenerateSSLCertificates, listener(app, i_OnClick_maxServices_generatesslcertificates, App));

    buttonHelpManual = button_flat();
    buttonHelpWhatsThis = button_flat();
    buttonHelpLicenseStatus = button_flat();
    buttonHelpCheckforUpdates = button_flat();
    buttonHelpAboutMaxMachines = button_flat();

      /*-------button section */
        /* add a image to the button */
        // https://www.streamlinehq.com/icons/streamline-colors/computers-devices-electronics?search=file+open&icon=ico_gFArBTyXVpOdkYKl
	error = ekFOK;
	fileNewImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-new-file-24.png", &error);
 	if (fileNewImg!= NULL && error==ekFOK) {
		button_image(buttonProjectNew, fileNewImg);
		image_destroy(&fileNewImg);
	}
	else textview_printf(app->textMaxManage, "Error loading image for buttonFileNew\n");

	error = ekFOK;
        fileOpenImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-opened-folder-24.png", &error);
	if (fileSaveImg!=NULL && error==ekFOK) {
		button_image(buttonProjectOpen, fileOpenImg);
		image_destroy(&fileOpenImg);
	}

	error= ekFOK;
        fileSaveImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-save-25.png", &error);
	if (fileSaveImg!=NULL && error==ekFOK) {
                button_image(buttonProjectSave, fileSaveImg);
                image_destroy(&fileSaveImg);
        }

	error = ekFOK;
        fileSaveAsImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-save-as-25.png", &error);
	if (fileSaveAsImg!=NULL && error==ekFOK) {
                button_image(buttonProjectSaveAs, fileSaveAsImg);
                image_destroy(&fileSaveAsImg);
        }

	error = ekFOK;
        fileCloseImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-close-window-24.png", &error);
	if (fileCloseImg!=NULL && error==ekFOK) {
                button_image(buttonProjectClose, fileCloseImg);
                image_destroy(&fileCloseImg);
        }

	error = ekFOK;
	fileQuitImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-exit-24.png", &error);
	if (fileQuitImg!=NULL && error==ekFOK) {
                button_image(buttonProjectQuit, fileQuitImg);
                image_destroy(&fileQuitImg);
        }

	error = ekFOK;
        viewInterconnectivityImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-interconnect-24.png", &error);
        if (viewInterconnectivityImg!=NULL && error==ekFOK) {
                button_image(buttonViewInterconnectivity, viewInterconnectivityImg);
                image_destroy(&viewInterconnectivityImg);
        }

        error = ekFOK;
        viewProjectImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-project-24.png", &error);
        if (viewProjectImg!=NULL && error==ekFOK) {
                button_image(buttonViewProject, viewProjectImg);
                image_destroy(&viewProjectImg);
        }

        error = ekFOK;
        viewAddressSpaceImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-atom-26.png", &error);
        if (viewAddressSpaceImg!=NULL && error==ekFOK) {
                button_image(buttonViewAddressSpace, viewAddressSpaceImg);
                image_destroy(&viewAddressSpaceImg);
        }

        error = ekFOK;
        viewLogImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-log-24.png", &error);
        if (viewLogImg!=NULL && error==ekFOK) {
                button_image(buttonViewLog, viewLogImg);
                image_destroy(&viewLogImg);
        }

        error = ekFOK;
        viewAttributesImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-genealogy-26.png", &error);
        if (viewAttributesImg!=NULL && error==ekFOK) {
                button_image(buttonViewAttributes, viewAttributesImg);
                image_destroy(&viewAttributesImg);
        }

        error = ekFOK;
        viewReferencesImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-coderwall-24.png", &error);
        if (viewReferencesImg!=NULL && error==ekFOK) {
                button_image(buttonViewReferences, viewReferencesImg);
                image_destroy(&viewReferencesImg);
        }

/**/
        error = ekFOK;
        maxEngineOneClickStartInstanceImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-start-24.png", &error);
        if (maxEngineOneClickStartInstanceImg!=NULL && error==ekFOK) {
                button_image(buttonmaxEngineOneClickStartInstance, maxEngineOneClickStartInstanceImg);
                image_destroy(&maxEngineOneClickStartInstanceImg);
        }

        error = ekFOK;
        maxEngineOneClickStopInstanceImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-stop-24.png", &error);
        if (maxEngineOneClickStopInstanceImg!=NULL && error==ekFOK) {
                button_image(buttonmaxEngineOneClickStopInstance, maxEngineOneClickStopInstanceImg);
                image_destroy(&maxEngineOneClickStopInstanceImg);
        }

        error = ekFOK;
        maxEngineViewStatisticsImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-heat-map-24.png", &error);
        if (maxEngineViewStatisticsImg!=NULL && error==ekFOK) {
                button_image(buttonmaxEngineViewStatistics, maxEngineViewStatisticsImg);
                image_destroy(&maxEngineViewStatisticsImg);
        }

        error = ekFOK;
        maxEngineViewLiveLogsImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-glasses-24.png", &error);
        if (maxEngineViewLiveLogsImg!=NULL && error==ekFOK) {
                button_image(buttonmaxEngineViewLiveLogs, maxEngineViewLiveLogsImg);
                image_destroy(&maxEngineViewLiveLogsImg);
        }


/**/
        error = ekFOK;
        maxCoreRegisterMaxAdaptersImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-edit-property-24.png", &error);
        if (maxCoreRegisterMaxAdaptersImg!=NULL && error==ekFOK) {
                button_image(buttonmaxCoreRegistermaxAdapters, maxCoreRegisterMaxAdaptersImg);
                image_destroy(&maxCoreRegisterMaxAdaptersImg);
        }

        error = ekFOK;
        maxCoreStartupParametersImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-start-26.png", &error);
        if (maxCoreStartupParametersImg!=NULL && error==ekFOK) {
                button_image(buttonmaxCoreStartupParameters, maxCoreStartupParametersImg);
                image_destroy(&maxCoreStartupParametersImg);
        }

        error = ekFOK;
        maxCoreViewStatisticsImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-heat-map-24.png", &error);
        if (maxCoreViewStatisticsImg!=NULL && error==ekFOK) {
                button_image(buttonmaxCoreViewStatistics, maxCoreViewStatisticsImg);
                image_destroy(&maxCoreViewStatisticsImg);
        }

/* core dump here
        error = ekFOK;
        maxCoreViewLiveLogsImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-glasses-24.png", &error);
        if (maxCoreViewLiveLogsImg!=NULL && error==ekFOK) {
                button_image(buttonmaxCoreViewLiveLogs, maxCoreViewLiveLogsImg);
                image_destroy(&maxCoreViewLiveLogsImg);
        }
*/

/**/
        error = ekFOK;
        maxAdapterAlarmsAndConditionsImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-alarm-24.png", &error);
        if (maxAdapterAlarmsAndConditionsImg!=NULL && error==ekFOK) {
                button_image(buttonmaxAdapterAlarmsAndConditions, maxAdapterAlarmsAndConditionsImg);
                image_destroy(&maxAdapterAlarmsAndConditionsImg);
        }

        error = ekFOK;
        maxAdapterEventsImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-events-24.png", &error);
        if (maxAdapterEventsImg!=NULL && error==ekFOK) {
                button_image(buttonmaxAdapterEvents, maxAdapterEventsImg);
                image_destroy(&maxAdapterEventsImg);
	}

        error = ekFOK;
        maxAdapterLogsManagementImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-file-configuration-24.png", &error);
        if (maxAdapterLogsManagementImg!=NULL && error==ekFOK) {
                button_image(buttonmaxAdapterLogsManagement, maxAdapterLogsManagementImg);
                image_destroy(&maxAdapterLogsManagementImg);
        }

        error = ekFOK;
        maxAdapterReverseConnectImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-return-24.png", &error);
        if (maxAdapterReverseConnectImg!=NULL && error==ekFOK) {
                button_image(buttonmaxAdapterReverseConnect, maxAdapterReverseConnectImg);
                image_destroy(&maxAdapterReverseConnectImg);
        }

        error = ekFOK;
        maxAdapterCommunicationsProtocolsImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-computers-connecting-24.png", &error);
        if (maxAdapterCommunicationsProtocolsImg!=NULL && error==ekFOK) {
                button_image(buttonmaxAdapterCommunicationsProtocols, maxAdapterCommunicationsProtocolsImg);
                image_destroy(&maxAdapterCommunicationsProtocolsImg);
        }

        error = ekFOK;
        maxAdapterViewStatisticsImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-heat-map-24.png", &error);
        if (maxAdapterViewStatisticsImg!=NULL && error==ekFOK) {
                button_image(buttonmaxAdapterViewStatistics, maxAdapterViewStatisticsImg);
                image_destroy(&maxAdapterViewStatisticsImg);
        }

        error = ekFOK;
        maxAdapterDiscoverDevicesImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-network-manager-24.png", &error);
        if (maxAdapterDiscoverDevicesImg!=NULL && error==ekFOK) {
                button_image(buttonmaxAdapterDiscoverDevices, maxAdapterDiscoverDevicesImg);
                image_destroy(&maxAdapterDiscoverDevicesImg);
        }

        error = ekFOK;
        maxAdapterAutoGenerateImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-network-manager-24.png", &error);
        if (maxAdapterAutoGenerateImg!=NULL && error==ekFOK) {
                button_image(buttonmaxAdapterAutoGenerate, maxAdapterAutoGenerateImg);
                image_destroy(&maxAdapterAutoGenerateImg);
        }

        error = ekFOK;
        maxAdapterSimulateAndConnectImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-network-manager-24.png", &error);
        if (maxAdapterSimulateAndConnectImg!=NULL && error==ekFOK) {
                button_image(buttonmaxAdapterSimulateAndConnect, maxAdapterSimulateAndConnectImg);
                image_destroy(&maxAdapterSimulateAndConnectImg);
        }

        error = ekFOK;
        maxAdapterEditDeviceNodesetImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-network-manager-24.png", &error);
        if (maxAdapterEditDeviceNodesetImg!=NULL && error==ekFOK) {
                button_image(buttonmaxAdapterEditDeviceNodeset, maxAdapterEditDeviceNodesetImg);
                image_destroy(&maxAdapterEditDeviceNodesetImg);
        }

        error = ekFOK;
        maxAdapterManualConfigurationImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-network-manager-24.png", &error);
        if (maxAdapterManualConfigurationImg!=NULL && error==ekFOK) {
                button_image(buttonmaxAdapterManualConfiguration, maxAdapterManualConfigurationImg);
                image_destroy(&maxAdapterManualConfigurationImg);
        }

/**/

        error = ekFOK;
        maxIntegratorStartInstanceImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-radius-24.png", &error);
        if (maxIntegratorStartInstanceImg!=NULL && error==ekFOK) {
                button_image(buttonmaxIntegratorStartInstance, maxIntegratorStartInstanceImg);
                image_destroy(&maxIntegratorStartInstanceImg);
        }

        error = ekFOK;
        maxIntegratorStopInstanceImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-radius-24.png", &error);
        if (maxIntegratorStopInstanceImg!=NULL && error==ekFOK) {
                button_image(buttonmaxIntegratorStopInstance, maxIntegratorStopInstanceImg);
                image_destroy(&maxIntegratorStopInstanceImg);
        }

        error = ekFOK;
        maxIntegratorRadiusServerImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-radius-24.png", &error);
        if (maxIntegratorRadiusServerImg!=NULL && error==ekFOK) {
                button_image(buttonmaxIntegratorRadiusServer, maxIntegratorRadiusServerImg);
                image_destroy(&maxIntegratorRadiusServerImg);
        }

        error = ekFOK;
        maxIntegratorLdapServerImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-active-directory-24.png", &error);
        if (maxIntegratorLdapServerImg!=NULL && error==ekFOK) {
                button_image(buttonmaxIntegratorLdapServer, maxIntegratorLdapServerImg);
                image_destroy(&maxIntegratorLdapServerImg);
        }

        error = ekFOK;
        maxIntegratorIdentityAndAccessServerImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-individual-server-24.png", &error);
        if (maxIntegratorIdentityAndAccessServerImg!=NULL && error==ekFOK) {
                button_image(buttonmaxIntegratorIdentityAndAccessServer, maxIntegratorIdentityAndAccessServerImg);
                image_destroy(&maxIntegratorIdentityAndAccessServerImg);
        }

        error = ekFOK;
        maxIntegratorOPCUAServerImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-individual-server-24.png", &error);
        if (maxIntegratorOPCUAServerImg!=NULL && error==ekFOK) {
                button_image(buttonmaxIntegratorOPCUAServer, maxIntegratorOPCUAServerImg);
                image_destroy(&maxIntegratorOPCUAServerImg);
        }
 
        error = ekFOK;
        maxIntegratorGlobalDirectoryServerImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-globe-24.png", &error);
        if (maxIntegratorGlobalDirectoryServerImg!=NULL && error==ekFOK) {
                button_image(buttonmaxIntegratorGlobalDirectoryServer, maxIntegratorGlobalDirectoryServerImg);
                image_destroy(&maxIntegratorGlobalDirectoryServerImg);
        }

        error = ekFOK;
        maxIntegratorLocalDirectoryServerImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-globe-24.png", &error);
        if (maxIntegratorLocalDirectoryServerImg!=NULL && error==ekFOK) {
                button_image(buttonmaxIntegratorLocalDirectoryServer, maxIntegratorLocalDirectoryServerImg);
                image_destroy(&maxIntegratorLocalDirectoryServerImg);
        }

        error = ekFOK;
        maxIntegratorSyslogServerImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-network-manager-24.png", &error);
        if (maxIntegratorSyslogServerImg!=NULL && error==ekFOK) {
                button_image(buttonmaxIntegratorSyslogServer, maxIntegratorSyslogServerImg);
                image_destroy(&maxIntegratorSyslogServerImg);
        }

        error = ekFOK;
        maxIntegratorHistorianServerImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-network-manager-24.png", &error);
        if (maxIntegratorHistorianServerImg!=NULL && error==ekFOK) {
                button_image(buttonmaxIntegratorHistorianServer, maxIntegratorHistorianServerImg);
                image_destroy(&maxIntegratorHistorianServerImg);
        }

        error = ekFOK;
        maxIntegratorProxyImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-network-manager-24.png", &error);
        if (maxIntegratorProxyImg!=NULL && error==ekFOK) {
                button_image(buttonmaxIntegratorProxyServer, maxIntegratorProxyImg);
                image_destroy(&maxIntegratorProxyImg);
        }

        error = ekFOK;
        maxIntegratorMqttImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-network-manager-24.png", &error);
        if (maxIntegratorMqttImg!=NULL && error==ekFOK) {
                button_image(buttonmaxIntegratorMqttServer, maxIntegratorMqttImg);
                image_destroy(&maxIntegratorMqttImg);
        }

        error = ekFOK;
        maxIntegratorAmqpImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-network-manager-24.png", &error);
        if (maxIntegratorAmqpImg!=NULL && error==ekFOK) {
                button_image(buttonmaxIntegratorAmqpServer, maxIntegratorAmqpImg);
                image_destroy(&maxIntegratorAmqpImg);
        }

        error = ekFOK;
        maxIntegratorWebAPIServerImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-network-manager-24.png", &error);
        if (maxIntegratorWebAPIServerImg!=NULL && error==ekFOK) {
                button_image(buttonmaxIntegratorWebAPIServer, maxIntegratorWebAPIServerImg);
                image_destroy(&maxIntegratorWebAPIServerImg);
        }

        error = ekFOK;
        maxIntegratorWebSocketServerImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-network-manager-24.png", &error);
        if (maxIntegratorWebSocketServerImg!=NULL && error==ekFOK) {
                button_image(buttonmaxIntegratorWebSocketServer, maxIntegratorWebSocketServerImg);
                image_destroy(&maxIntegratorWebSocketServerImg);
        }


/**/
        error = ekFOK;
        maxGateStartInstanceImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-network-manager-24.png", &error);
        if (maxGateStartInstanceImg!=NULL && error==ekFOK) {
                button_image(buttonmaxGateStartInstance, maxGateStartInstanceImg);
                image_destroy(&maxGateStartInstanceImg);
        }

        error = ekFOK;
        maxGateStopInstanceImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-network-manager-24.png", &error);
        if (maxGateStopInstanceImg!=NULL && error==ekFOK) {
                button_image(buttonmaxGateStopInstance, maxGateStopInstanceImg);
                image_destroy(&maxGateStopInstanceImg);
        }

        error = ekFOK;
        maxGateInspectInstanceImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-network-manager-24.png", &error);
        if (maxGateInspectInstanceImg!=NULL && error==ekFOK) {
                button_image(buttonmaxGateInspectInstance, maxGateInspectInstanceImg);
                image_destroy(&maxGateInspectInstanceImg);
        }

        error = ekFOK;
        maxGateManualConfigurationImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-network-manager-24.png", &error);
        if (maxGateManualConfigurationImg!=NULL && error==ekFOK) {
                button_image(buttonmaxGateManualConfiguration, maxGateManualConfigurationImg);
                image_destroy(&maxGateManualConfigurationImg);
        }

/**/
        error = ekFOK;
        maxScaleSetupInstanceImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-network-manager-24.png", &error);
        if (maxScaleSetupInstanceImg!=NULL && error==ekFOK) {
                button_image(buttonmaxScaleSetupInstance, maxScaleSetupInstanceImg);
                image_destroy(&maxScaleSetupInstanceImg);
        }

        error = ekFOK;
        maxScaleConfigurationImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-network-manager-24.png", &error);
        if (maxScaleConfigurationImg!=NULL && error==ekFOK) {
                button_image(buttonmaxScaleConfiguration, maxScaleConfigurationImg);
                image_destroy(&maxScaleConfigurationImg);
        }

/**/
        error = ekFOK;
        maxOrchestratorStartInstanceImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-network-manager-24.png", &error);
        if (maxOrchestratorStartInstanceImg!=NULL && error==ekFOK) {
                button_image(buttonmaxOrchestratorStartInstance, maxOrchestratorStartInstanceImg);
                image_destroy(&maxOrchestratorStartInstanceImg);
        }

        error = ekFOK;
        maxOrchestratorStopInstanceImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-network-manager-24.png", &error);
        if (maxOrchestratorStopInstanceImg!=NULL && error==ekFOK) {
                button_image(buttonmaxOrchestratorStopInstance, maxOrchestratorStopInstanceImg);
                image_destroy(&maxOrchestratorStopInstanceImg);
        }

        error = ekFOK;
        maxOrchestratorDefineDataFlowImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-network-manager-24.png", &error);
        if (maxOrchestratorDefineDataFlowImg!=NULL && error==ekFOK) {
                button_image(buttonmaxOrchestratorDefineDataflow, maxOrchestratorDefineDataFlowImg);
                image_destroy(&maxOrchestratorDefineDataFlowImg);
        }

/**/
        error = ekFOK;
        maxMindDigitalTwinImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-network-manager-24.png", &error);
        if (maxMindDigitalTwinImg!=NULL && error==ekFOK) {
                button_image(buttonmaxMindDigitalTwin, maxMindDigitalTwinImg);
                image_destroy(&maxMindDigitalTwinImg);
        }

        error = ekFOK;
        maxMindRealTimeAnalyticsImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-network-manager-24.png", &error);
        if (maxMindRealTimeAnalyticsImg!=NULL && error==ekFOK) {
                button_image(buttonmaxMindRealTimeAnalytics, maxMindRealTimeAnalyticsImg);
                image_destroy(&maxMindRealTimeAnalyticsImg);
        }

        error = ekFOK;
        maxMindMachineLearningImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-network-manager-24.png", &error);
        if (maxMindMachineLearningImg!=NULL && error==ekFOK) {
                button_image(buttonmaxMindMachineLearning, maxMindMachineLearningImg);
                image_destroy(&maxMindMachineLearningImg);
        }

/**/
        error = ekFOK;
        maxServiceUsersAccountImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-users-24.png", &error);
        if (maxServiceUsersAccountImg!=NULL && error==ekFOK) {
                button_image(buttonmaxServiceUsersAccount, maxServiceUsersAccountImg);
                image_destroy(&maxServiceUsersAccountImg);
        }

        error = ekFOK;
        maxServiceSystemsAccountImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-access-24.png", &error);
        if (maxServiceSystemsAccountImg!=NULL && error==ekFOK) {
                button_image(buttonmaxServiceSystemsAccount, maxServiceSystemsAccountImg);
                image_destroy(&maxServiceSystemsAccountImg);
        }

        error = ekFOK;
        maxServiceGenerateSSLCertificatesImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-security-ssl-24.png", &error);
        if (maxServiceGenerateSSLCertificatesImg!=NULL && error==ekFOK) {
                button_image(buttonmaxServiceGenerateSSLCertificates, maxServiceGenerateSSLCertificatesImg);
                image_destroy(&maxServiceGenerateSSLCertificatesImg);
        }
/**/

        error = ekFOK;
        maxHelpManualImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-network-manager-24.png", &error);
        if (maxHelpManualImg!=NULL && error==ekFOK) {
                button_image(buttonHelpManual, maxHelpManualImg);
                image_destroy(&maxHelpManualImg);
        }

        error = ekFOK;
        maxHelpWhatsThisImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-network-manager-24.png", &error);
        if (maxHelpWhatsThisImg!=NULL && error==ekFOK) {
                button_image(buttonHelpWhatsThis, maxHelpWhatsThisImg);
                image_destroy(&maxHelpWhatsThisImg);
        }

        error = ekFOK;
        maxHelpLicenseStatusImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-network-manager-24.png", &error);
        if (maxHelpLicenseStatusImg!=NULL && error==ekFOK) {
                button_image(buttonHelpLicenseStatus, maxHelpLicenseStatusImg);
                image_destroy(&maxHelpLicenseStatusImg);
        }

        maxHelpCheckforUpdatesImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-network-manager-24.png", &error);
        if (maxHelpCheckforUpdatesImg!=NULL && error==ekFOK) {
                button_image(buttonHelpCheckforUpdates, maxHelpCheckforUpdatesImg);
                image_destroy(&maxHelpCheckforUpdatesImg);
        }

        error = ekFOK;
        maxHelpAboutMaxMachinesImg = image_from_file("/home/pi/nappgui_src/jacky/img/icons8-network-manager-24.png", &error);
        if (maxHelpAboutMaxMachinesImg!=NULL && error==ekFOK) {
                button_image(buttonHelpAboutMaxMachines, maxHelpAboutMaxMachinesImg);
                image_destroy(&maxHelpAboutMaxMachinesImg);
        }

        /* attach buttons to buttonLayout */
	layout_button(app->buttonLayout, buttonProjectNew, 0, 0);
        layout_button(app->buttonLayout, buttonProjectOpen, 1, 0);
        layout_button(app->buttonLayout, buttonProjectSave, 2,0);
        layout_button(app->buttonLayout, buttonProjectSaveAs, 3,0);
        layout_button(app->buttonLayout, buttonProjectClose, 4,0);
 	layout_button(app->buttonLayout, buttonProjectQuit, 5,0);

        layout_button(app->buttonLayout, buttonViewInterconnectivity, 6,0);
        layout_button(app->buttonLayout, buttonViewProject, 7,0);
        layout_button(app->buttonLayout, buttonViewAddressSpace, 8,0);
        layout_button(app->buttonLayout, buttonViewLog, 9,0);
        layout_button(app->buttonLayout, buttonViewAttributes, 10,0);
        layout_button(app->buttonLayout, buttonViewReferences, 11,0);

        layout_button(app->buttonLayout, buttonmaxEngineOneClickStartInstance, 12,0);
	layout_button(app->buttonLayout, buttonmaxEngineOneClickStopInstance, 13,0);
	layout_button(app->buttonLayout, buttonmaxEngineViewStatistics, 14,0);
	layout_button(app->buttonLayout, buttonmaxEngineViewLiveLogs, 15,0);

#ifdef KIV
	layout_button(app->buttonLayout, buttonmaxCoreStartInstance, 16,0);
	layout_button(app->buttonLayout, buttonmaxCoreStopInstance, 17,0);
	layout_button(app->buttonLayout, buttonmaxCoreRegistermaxAdapters, 18,0);
	layout_button(app->buttonLayout, buttonmaxCoreViewStatistics, 19,0);
	layout_button(app->buttonLayout, buttonmaxCoreViewLiveLogs, 20,0);

	layout_button(app->buttonLayout, buttonmaxCoreWebSocketService, 21,0);

	layout_button(app->buttonLayout, buttonmaxAdapterStartInstance, 22,0);
        layout_button(app->buttonLayout, buttonmaxAdapterStopInstance, 23,0);
	layout_button(app->buttonLayout, buttonmaxAdapterAlarmsAndConditions, 24,0);
	layout_button(app->buttonLayout, buttonmaxAdapterEvents, 25,0);
	layout_button(app->buttonLayout, buttonmaxAdapterLogsManagement, 26,0);
	layout_button(app->buttonLayout, buttonmaxAdapterReverseConnect, 27,0);
	layout_button(app->buttonLayout, buttonmaxServiceUsersAccount, 28,0);
	layout_button(app->buttonLayout, buttonmaxServiceSystemsAccount, 29,0);
	layout_button(app->buttonLayout, buttonmaxServiceGenerateSSLCertificates, 30,0);
#endif

/*	layout_button(app->buttonLayout, buttonmaxCoreRegistermaxAdapters, 31,0);
	layout_button(app->buttonLayout, buttonmaxAdapterStartupParameters, 32,0);
	layout_button(app->buttonLayout, buttonmaxAdapterCommunicationsProtocols, 33,0);
	layout_button(app->buttonLayout, buttonmaxAdapterViewStatistics, 34,0);

	layout_button(app->buttonLayout, buttonmaxIntegratorRadiusServer, 35,0);
	layout_button(app->buttonLayout, buttonmaxIntegratorLdapServer, 36,0);
	layout_button(app->buttonLayout, buttonmaxIntegratorIdentityAndAccessServer, 37,0);
	layout_button(app->buttonLayout, buttonmaxIntegratorGlobalDirectoryServer, 38,0);
*/
	// somehow only 1 row 30 cols for quick access buttons
	//layout_button(app->buttonLayout, buttonmaxIntegratorLocalDirectoryServer, 0,1);
	//layout_button(app->buttonLayout, buttonmaxIntegratorSyslogServer, 0,2);
	//layout_button(app->buttonLayout, buttonmaxIntegratorHistorianServer, 0,3);
	//layout_button(app->buttonLayout, buttonmaxIntegratorMessageBroker, 0,4);
	//layout_button(app->buttonLayout, buttonmaxIntegratorWebAPIServer, 0,5);
	//layout_button(app->buttonLayout, buttonmaxIntegratorWebSocketServer, 0,6);

	//layout_button(app->buttonLayout, buttonmaxAdapterDiscoverDevices, 0,7);
	//layout_button(app->buttonLayout, buttonmaxAdapterAutoGenerate, 0,8),
	//layout_button(app->buttonLayout, buttonmaxAdapterSimulateAndConnect, 0,9);
	//layout_button(app->buttonLayout, buttonmaxAdapterEditDeviceNodeset, 0,10);
	//layout_button(app->buttonLayout, buttonmaxAdapterManualConfiguration, 0,11);

	//layout_button(app->buttonLayout, buttonmaxGateStartInstance, 0,12);
	//layout_button(app->buttonLayout, buttonmaxGateStopInstance, 0,13);
	//layout_button(app->buttonLayout, buttonmaxGateInspectInstance, 0,14);
	//layout_button(app->buttonLayout, buttonmaxGateManualConfiguration, 0,15);

	//layout_button(app->buttonLayout, buttonmaxScaleSetupInstance, 0,16);
        //layout_button(app->buttonLayout, buttonmaxScaleConfiguration, 0,17);

        //layout_button(app->buttonLayout, buttonmaxOrchestratorStartInstance, 0,18);
        //layout_button(app->buttonLayout, buttonmaxOrchestratorStopInstance, 0,19);
        //layout_button(app->buttonLayout, buttonmaxOrchestratorDefineDataFlow, 0,20);

        //layout_button(app->buttonLayout, buttonmaxMindDigitalTwin, 0,21);
        //layout_button(app->buttonLayout, buttonmaxMindRealTimeAnalytics, 0,22);
        //layout_button(app->buttonLayout, buttonmaxMindMachineLearning, 0,23);

        //layout_button(app->buttonLayout, buttonHelpManual, 0,24);
        //layout_button(app->buttonLayout, buttonHelpWhatsThis, 0,25);
        //layout_button(app->buttonLayout, buttonHelpLicenseStatus, 0,26);
        //layout_button(app->buttonLayout, buttonHelpCheckForUpdates, 0,27);
        //layout_button(app->buttonLayout, buttonHelpAboutMaxMachines, 0,28);


}

Panel *split_panel(App *app)
{
    // --------------------------------------------------------- Variables Section---------------------------------------

    /*working copy*/
    ferror_t error= ekFOK;
    TextView *textLeftTop1, *textLeftCentre1, *textLeftTop2, *textLeftBottom2, *textLeftTop3, *textLeftBottom3, *textRight, *textRightTop, *textRightBottom ;
    Panel *panel1;
    Layout *layout1, *layout1b, *layout2b, *layout3b;
    SplitView *split1, *split2, *split1b, *split2b, *split3b;
    TableView *tableLeftTop1, *tableLeftBottom1, *tableCentreTop1, *tableCentreBottom1;

    View *viewA;

                Layout *layoutD;
                ImageView *maxMachinesRootFolderImageView;
                Image *maxMachinesRootFolderImage;
		Panel *panelD;

                Layout *layoutA;
		Layout *layoutATop, *layoutABottom;
                ImageView *InterconnectivityImageView00, *InterconnectivityImageView01, *InterconnectivityImageView10, *InterconnectivityImageView11;
                Image *InterconnectivityImage;

		Panel *panelA;
		Panel *panelATop, *panelABottom;

		Layout *layoutB;
		ImageView *maxAdapterStatusImageView;
		Image *maxAdapterStatusImage;
		Panel *panelB;

                Layout *layoutC;
                ImageView *maxIntegratorStatusImageView;
                Image *maxIntegratorStatusImage;
                Panel *panelC;


    //TextView *textLeft = textview_create();  textview_printf(textLeft, "Text View Left");
    textRight = textview_create(); textview_printf(textRight, "Text View Right");
//    textview_size(textLeft, s2df(200, 200));
    textview_size(textRight, s2df(1920, 200));
    //splitview_textview(split1, textLeft, FALSE);
        /* replace textleft with horizontal splitview : add a horizontal splitview */
        //textLeftTop1 = textview_create(); textview_printf(textLeftTop1, "Project");
	//textLeftCentre1 = textview_create(); textview_printf(textLeftCentre1, "Text View Left Centre1");
        //TextView *textLeftBottom1 = textview_create(); textview_printf(textLeftBottom1, "Attributes");

	// left section
	// first do top table
	tableLeftTop1 = tableview_create();
	app->dataTableLeftTop1 = tableLeftTop1;
	tableview_tree(tableLeftTop1, UINT32_MAX);	// set as a treeview

	tableview_size(tableLeftTop1, s2df(200, 300));

	tableview_OnData(tableLeftTop1, listener(app, i_OnTreeDataTableLeftTop1, App));
	tableview_add_column_text(tableLeftTop1);
    tableview_add_column_text(tableLeftTop1);
    tableview_add_column_text(tableLeftTop1);
    tableview_add_column_text(tableLeftTop1);
    tableview_add_column_text(tableLeftTop1);
    tableview_add_column_text(tableLeftTop1);
    tableview_add_column_text(tableLeftTop1);
    tableview_add_column_text(tableLeftTop1);
    tableview_add_column_text(tableLeftTop1);

	tableview_header_clickable(tableLeftTop1, TRUE);
	tableview_header_resizable(tableLeftTop1, TRUE);
	tableview_header_indicator(tableLeftTop1, 1, ekINDDOWN_ARROW);
	tableview_header_indicator(tableLeftTop1, 2, ekINDUP_ARROW);
	tableview_header_title(tableLeftTop1, 0, "Qpro");
	tableview_column_width(tableLeftTop1, 0, 100);
	tableview_column_limits(tableLeftTop1, 2, 50, 100);
	tableview_column_freeze(tableLeftTop1, 1);
	tableview_header_align(tableLeftTop1, 0, ekLEFT);
	tableview_multisel(tableLeftTop1, FALSE, FALSE);
	tableview_header_visible(tableLeftTop1, TRUE);
	tableview_grid(tableLeftTop1, FALSE, FALSE);
	tableview_update(tableLeftTop1);

    	{
        	uint32_t row = 0;
        	tableview_select(tableLeftTop1, &row, 1);
        	tableview_focus_row(tableLeftTop1, row, ekBOTTOM);
    	}

	// now do bottom table
        tableLeftBottom1 = tableview_create(); //textview_printf(textLeftBottom1, "Attributes");
        tableview_size(tableLeftBottom1, s2df(200, 300));

	tableview_OnData(tableLeftBottom1, listener(app, i_OnTreeDataTableLeftBottom1, App));
	tableview_update(tableLeftBottom1);

	// centre section
	tableCentreTop1 = tableview_create();
	tableview_size(tableCentreTop1, s2df(1080,150));
	tableview_OnData(tableCentreTop1, listener(app, i_OnTreeDataTableCentreTop1, App));
	tableview_update(tableCentreTop1);

	tableCentreBottom1 = tableview_create();
	tableview_size(tableCentreBottom1, s2df(1080, 600));

	#ifdef DEFUNCT
        textLeftTop2 = textview_create(); textview_printf(textLeftTop2, "Address space");
        textLeftBottom2 = textview_create(); textview_printf(textLeftBottom2, "Interconnectivity");
        textview_size(textLeftTop2, s2df(1080, 150));
        textview_size(textLeftBottom2, s2df(1080, 450));

        textLeftTop3 = textview_create(); textview_printf(textLeftTop3, "MaxAdapter");
        textLeftBottom3 = textview_create(); textview_printf(textLeftBottom3, "MaxIntegrator");
        textview_size(textLeftTop3, s2df(200, 300));
        textview_size(textLeftBottom3, s2df(200, 300));

	/**/
        textRightTop = textview_create(); textview_printf(textRightTop, "Text View Right Top");
        textRightBottom = textview_create(); textview_printf(textRightBottom, "Text View Right Bottom");
        textview_size(textRightTop, s2df(200, 200));
        textview_size(textRightBottom, s2df(200, 200));
	/**/
	#endif

    // --------------------------------------------------------- Start creating the panel and objects---------------------------------------

    panel1 = panel_scroll(TRUE, TRUE);
    layout1 = layout_create(2,1);
        split1 = splitview_vertical(); // split into LEFT and RIGHT sections (Left)
	splitview_minsize0(split1, 1920*1/7); //splitview_minsize1(split1, 1920*6/7); // only can set minimum width of splitview1 LEFT section
        split2 = splitview_vertical(); // split into LEFT and RIGHT sections (Left)

    layout1b = layout_create(1,2);
        split1b = splitview_horizontal(); // split into TOP, BOTTOM
	//SplitView *split1c = splitview_horizontal();
	splitview_minsize0(split1b, 200); splitview_minsize1(split1b, 200);	// minimum height of splitview TOP and BOTTOM section
	//splitview_minsize0(split1c, 200); splitview_minsize1(split1c, 200);

    layout2b = layout_create(1,2);
	split2b = splitview_horizontal(); // split into TOP, BOTTOM
	splitview_minsize0(split2b, 300); splitview_minsize1(split2b, 300);	// minimum height of splitview TOP and BOTTOM section

    layout3b = layout_create(1,2);
	split3b = splitview_horizontal(); // split into TOP, BOTTOM
	splitview_minsize0(split3b, 200); splitview_minsize1(split3b, 200);	// minimum height of splitview TOP and BOTTOM section


    // --------------------------------------------------------- Left Section---------------------------------------
    #ifndef RW_SPLITVIEW_VERTICAL
       	splitview_splitview(split1, split1b);
       	layout_splitview(layout1b, split1b, 0,0);

	// start with the upper half
	layoutD = layout_create(1,1);
	layout_splitview(layout1b, split1b, 0,0);
	splitview_tableview(split1b, tableLeftTop1, FALSE);
	tableview_add_column_text(tableLeftTop1);
                tableview_header_title(tableLeftTop1,
                       0,
                       "MaxMachines");
        //-->panel_layout()
                panelD = panel_create();
                panel_layout(panelD, layoutD);
        //-->splitview_panel()
                splitview_panel(split1b, panelD);


	// --------------now do the lower half
	layout_splitview(layout1b, split1b, 0,1);
        splitview_tableview(split1b, tableLeftBottom1, FALSE);     // put the child object into split1b
     	tableview_add_column_text(tableLeftBottom1);
		tableview_header_title(tableLeftBottom1,
                       0,
                       "Attribute");
	tableview_add_column_text(tableLeftBottom1);
		tableview_header_title(tableLeftBottom1,
                       1,
                       "Value");

    // --------------------------------------------------------- Middle Section---------------------------------------
	splitview_splitview(split1, split2b);	// put a secondary splitview into the primary splitview
	layout_splitview(layout2b, split2b, 0,0);

#ifndef WORKING

	// --------------start with the upper half
        app->layoutATop = layout_create(1,1);
	layout_splitview(layout2b, split2b, 0,0);
		splitview_tableview(split2b, tableCentreTop1, FALSE);
		tableview_add_column_text(tableCentreTop1);
                tableview_header_title(tableCentreTop1,
                       0,
                       "Nodeset");
		tableview_add_column_text(tableCentreTop1);
                tableview_header_title(tableCentreTop1,
                       1,
                       "Param 1");
		tableview_add_column_text(tableCentreTop1);
                tableview_header_title(tableCentreTop1,
                       2,
                       "Param 2");
		tableview_add_column_text(tableCentreTop1);
                tableview_header_title(tableCentreTop1,
                       3,
                       "Param 3");
		tableview_add_column_text(tableCentreTop1);
                tableview_header_title(tableCentreTop1,
                       4,
                       "Param 4");
                tableview_add_column_text(tableCentreTop1);
                tableview_header_title(tableCentreTop1,
                       5,
                       "Param 5");
                tableview_add_column_text(tableCentreTop1);
                tableview_header_title(tableCentreTop1,
                       6,
                       "Param 6");
                tableview_add_column_text(tableCentreTop1);
                tableview_header_title(tableCentreTop1,
                       7,
                       "Param 7");
                tableview_add_column_text(tableCentreTop1);
                tableview_header_title(tableCentreTop1,
                       8,
                       "Param 8");
                tableview_add_column_text(tableCentreTop1);
                tableview_header_title(tableCentreTop1,
                       9,
                       "Param 9");
                tableview_add_column_text(tableCentreTop1);
                tableview_header_title(tableCentreTop1,
                       10,
                       "Param 10");
                tableview_add_column_text(tableCentreTop1);
                tableview_header_title(tableCentreTop1,
                       11,
                       "Param 11");
                tableview_add_column_text(tableCentreTop1);
                tableview_header_title(tableCentreTop1,
                       12,
                       "Param 12");

        	//--> panel_layout()
                app->panelATop = panel_scroll(TRUE, TRUE); //app->panelABottom = panel_scroll(TRUE, TRUE);
                panel_layout(app->panelATop, app->layoutATop); //panel_layout(app->panelABottom, app->layoutABottom);
		// splitview_panel()
		splitview_panel(split2b, app->panelATop);

	// --------------now do the lower half
		app->layoutABottom = layout_create(1,1);
		layout_splitview(layout2b, split2b, 0,1);

		#ifdef KIV
		layout_tableview(app->layoutABottom, tableCentreBottom1, 0,0);
		tableview_add_column_text(tableCentreBottom1);
                tableview_header_title(tableCentreBottom1,
                       0,
                       "maxOrchestrator");
		#else
		//--> webview_panel() will be created in maxOrchestrator;
		//-->panel_layout();
		app->panelABottom = panel_scroll(TRUE, TRUE);
		panel_layout(app->panelABottom, app->layoutABottom);
		#endif

	// finally assign the 2 panels to the splitview (split2b : horizontal)
		//--> splitview_panel();
                splitview_panel(split2b, app->panelATop);
		splitview_panel(split2b, app->panelABottom);

		//panel_size(panelATop, s2df(400.0f,50.0f)); panel_size(panelABottom, s2df(400.0f, 350.0f));
		//app->viewA = view_custom(TRUE, TRUE);
		//layout_view(app->layoutATop, app->viewA, 0,0); layout_view(app->layoutABottom, app->viewA, 0,0);

		//splitview_panel(split2b, app->panelABottom);
		//splitview_textview(split2b, textLeftTop2, FALSE);        // put the child object into split2b
		//splitview_textview(split2b, textLeftBottom2, FALSE);        // put the child object into split2b

#else
        //--> layout_imageview();
                layoutA = layout_create(1,1);	// 2,2
                //InterconnectivityImageView00 = imageview_create();
                //InterconnectivityImageView01 = imageview_create();
                //InterconnectivityImageView10 = imageview_create();
                //InterconnectivityImageView11 = imageview_create();
                //InterconnectivityImage = image_from_file("/home/pi/nappgui_src/jacky/img/interconnectivity.png", &error);
                //imageview_image(InterconnectivityImageView00, InterconnectivityImage);
                //imageview_image(InterconnectivityImageView01, InterconnectivityImage);
                //imageview_image(InterconnectivityImageView10, InterconnectivityImage);
                //imageview_image(InterconnectivityImageView11, InterconnectivityImage);
                //layout_imageview(layoutA, InterconnectivityImageView00, 0,0);
                //layout_imageview(layoutA, InterconnectivityImageView01, 0,1);
		splitview_splitview(split2, split3b);
		//layout_imageview(layoutA, InterconnectivityImageView10, 1,0);
                //layout_imageview(layoutA, InterconnectivityImageView11, 1,1);
        //--> panel_layout();
                panelA = panel_scroll(TRUE, TRUE);
                panel_layout(panelA, layoutA);
		app->viewA = view_custom(TRUE, TRUE);
		layout_view(layoutA, app->viewA, 0,0);
        //--> splitview_panel();
                splitview_panel(split2b, panelA);
		//imageview_size(InterconnectivityImageView00, s2df(200,600));
		//imageview_scale(InterconnectivityImageView00, ekGUI_SCALE_AUTO);
                //imageview_size(InterconnectivityImageView01, s2df(200,600));
                //imageview_scale(InterconnectivityImageView01, ekGUI_SCALE_AUTO);
                //imageview_size(InterconnectivityImageView10, s2df(200,600));
                //imageview_scale(InterconnectivityImageView10, ekGUI_SCALE_AUTO);
                //imageview_size(InterconnectivityImageView11, s2df(200,600));
                //imageview_scale(InterconnectivityImageView11, ekGUI_SCALE_AUTO);

		splitview_textview(split2b, textLeftTop2, FALSE);        // put the child object into split2b
                splitview_textview(split2b, textLeftBottom2, FALSE);        // put the child object into split2b

#endif

    // --------------------------------------------------------- Right Section---------------------------------------
        splitview_splitview(split2, split3b);
        layout_splitview(layout3b, split3b, 0,0);
	//splitview_minsize0(split2, 1920*5/7); // splitview_minsize1(split2, 1920*1/7); // only can set minimum width of splitview2 LEFT section 
        //splitview_textview(split3b, textLeftTop3, FALSE);        // put the child object into split1b

	//--> layout_imageview();
		layoutB = layout_create(1,1);
		//Label *maxAdapterLabel = label_create(); label_text(maxAdapterLabel, "maxAdapter");
		//label_align(maxAdapterLabel, ekCENTER);
		//layout_label(layoutB, maxAdapterLabel, 0,0);

		maxAdapterStatusImageView = imageview_create();
		maxAdapterStatusImage = image_from_file("/home/pi/nappgui_src/jacky/img/maxAdapterStatus.png", &error);
		imageview_image(maxAdapterStatusImageView, maxAdapterStatusImage);
		layout_imageview(layoutB, maxAdapterStatusImageView, 0,0);
	//-->panel_layout()
		panelB = panel_scroll(TRUE, TRUE);
		panel_layout(panelB, layoutB);
	//-->splitview_panel()
		splitview_panel(split3b, panelB);
		imageview_size(maxAdapterStatusImageView, s2df(200,400));
		imageview_scale(maxAdapterStatusImageView, ekGUI_SCALE_AUTO);


        //splitview_textview(split3b, textLeftBottom3, FALSE);     // put the child object into split1b

	//--> layout_imageview();
                layoutC = layout_create(1,1);
                //Label *maxAdapterLabel = label_create(); label_text(maxAdapterLabel, "maxAdapter");
                //label_align(maxAdapterLabel, ekCENTER);
                //layout_label(layoutB, maxAdapterLabel, 0,0);

                maxIntegratorStatusImageView = imageview_create();
                maxIntegratorStatusImage = image_from_file("/home/pi/nappgui_src/jacky/img/maxIntegratorStatus.png", &error);
                imageview_image(maxIntegratorStatusImageView, maxIntegratorStatusImage);
                layout_imageview(layoutC, maxIntegratorStatusImageView, 0,0);
        //-->panel_layout()
                panelC = panel_scroll(TRUE, TRUE);
                panel_layout(panelC, layoutC);
        //-->splitview_panel()
                splitview_panel(split3b, panelC);
                imageview_size(maxIntegratorStatusImageView, s2df(200,400));
                imageview_scale(maxIntegratorStatusImageView, ekGUI_SCALE_AUTO);


   	//splitview_textview(split1, textRight, FALSE);
    	layout_splitview(layout1, split1, 0,0);	// 1
    	layout_splitview(layout1, split2, 1,0);	// 1

        //splitview_splitview(split1, split2);
        //layout_splitview(layout, split1, 0, 0); // 1 - cannot be here
	//splitview_textview(split2, textRightRight, FALSE);
	//layout_splitview(layout, split2, 2,0);
   #endif

    panel_layout(panel1, layout1);

    return panel1;
}



/*---------------------------------------------------------------------------------------------------------------------*/
/* static Panel *i_panel_original() - instantiates the components of the window */
/*---------------------------------------------------------------------------------------------------------------------*/


static Panel *i_panel_original(App *app)
{
    //Panel *imaginaryLeftPanel, *imaginaryTopPanel, *imaginaryRightPanel, *imaginaryBottomPanel;

    //Layout *imaginaryLayoutLeftRight, *imaginaryLayoutTopBottom;

    //color_t imaginaryColorLeftRight = color_rgb(88,4,47);
    //color_t imaginaryColorTopBottom = color_rgb(50,130,246);
    //S2Df imaginary_leftright_struct, imaginary_topbottom_struct;
    //S2Df canvasSize
    S2Df textSize;
    ImageView *InterconnectivityImageView;
    ImageView *maxOrchestratorImageView;
    Image *InterconnectivityImage, *maxOrchestratorImage;
    Tabs *tabStatus;
    SplitView *SplitViewLeftRight;
    Panel *PanelLeft_SplitViewLeftRight, *PanelRight_SplitViewLeftRight;
    Panel *splitPanel;


    Panel *panel = panel_create();
/* added 18Aug */    //Panel *canvasPanel = panel_create();
/* added 18Aug */    //View *canvasView = view_custom(0,1);        /* scroll, border */ //View_create();

    //TextView *text;
    //Layout *statusLayout;
    //text = textview_create();

    Layout *baseLayout = layout_create(1, 4); /* col, row */
    app->canvasLayout = layout_create(1,1);
    app->buttonLayout = layout_create(30,2);	// maximum col = 30

    layout_hsize(app->canvasLayout, 0, 5*1920/7 );	// 5/7 x 1920
    layout_vsize(app->canvasLayout, 0, 1200);

    /* ----- set the size of the baseLayout */
    layout_hsize(baseLayout, 0, 1920); /* set the width of row 0 */

    layout_vsize(baseLayout, 0, 100); /* set the height of row 0 - quick access button icons section */
    layout_vsize(baseLayout, 1, 1200); /* set the height of row 1 - canvas section */
    layout_vsize(baseLayout, 2, 300); /* set the height of row 2 - status section */

    layout_margin(baseLayout, 5);
    layout_vmargin(baseLayout, 0, 5);
    layout_vmargin(baseLayout, 1, 5);

    app->text = textview_create();

    app->textMaxManage = textview_create(); textview_printf(app->textMaxManage, "initial text in MaxManage Textview object\n");
    app->textMaxEngine = textview_create(); textview_printf(app->textMaxEngine, "initial text in MaxEngine Textview object\n");
    app->textMaxAdapter = textview_create(); textview_printf(app->textMaxAdapter, "initial text in MaxAdapter Textview object\n");
    app->textMaxCore = textview_create(); textview_printf(app->textMaxCore, "initial text in MaxCore Textview object\n");
    app->textMaxOrchestrator = textview_create(); textview_printf(app->textMaxOrchestrator, "initial text in MaxOrchestrator Textview object\n");
    app->textMaxIntegrator = textview_create(); textview_printf(app->textMaxIntegrator, "initial text in MaxIntegrator Textview object\n");
    app->textMaxScale = textview_create(); textview_printf(app->textMaxScale, "initial text in MaxScale Textview object\n");
    app->textMaxMind = textview_create(); textview_printf(app->textMaxMind, "initial text in MaxMind Textview object\n");
    app->textMaxGate = textview_create(); textview_printf(app->textMaxGate, "initial text in MaxGate Textview object\n");
    app->textMaxLicense = textview_create(); textview_printf(app->textMaxLicense, "initial text in MaxLicense Textview object\n");
    app->textMaxServices = textview_create(); textview_printf(app->textMaxServices, "initial text in MaxServices Textview object\n");


    //imaginaryColorLeftRight = color_rgb(88,4,47);
    //imaginaryColorTopBottom = color_rgb(50,130,246);

    InterconnectivityImageView = imageview_create();
    InterconnectivityImage = image_from_file("/home/pi/nappgui_src/jacky/img/interconnectivity.jpg", NULL);
    imageview_image(InterconnectivityImageView, InterconnectivityImage);

    maxOrchestratorImageView = imageview_create();
    maxOrchestratorImage = image_from_file("/home/pi/nappgui_src/jacky/img/maxOrchestrator.png", NULL);
    imageview_image(maxOrchestratorImageView, maxOrchestratorImage);
    layout_imageview(app->canvasLayout, maxOrchestratorImageView, 0,0);


/* block on 18Aug */   // View *canvasView = view_custom(0,1);        /* scroll, border */


// *tabStatusMaxEngine, *tabStatusMaxAdapter, *tabmaxEngine, *tabAdapter, *tabmaxCore, *tabmaxOrchestrator, *tabmaxIntegrator, *tabmaxScale, *tabmaxMind, *tabmaxGate, *tabmaxLicense, *tabmaxServices;


    /* ----- buttons section */
    createButtons(app);


    /* ----- canvas section */
    SplitViewLeftRight = splitview_vertical();
//    SplitView *SplitViewTopBottom = splitview_horizontal();

    splitview_minsize0(SplitViewLeftRight, 500);
    splitview_minsize1(SplitViewLeftRight, 1800);
    splitview_visible0(SplitViewLeftRight, true);
    splitview_visible1(SplitViewLeftRight, true);

    PanelLeft_SplitViewLeftRight = panel_scroll(TRUE, TRUE);	// create a panel to be inserted into the leftside splitviewLeftRight
    PanelRight_SplitViewLeftRight = panel_scroll(TRUE, TRUE);	// create a panel to be inserted into the rightside splitviewLeftRight


//    splitview_minsize0(SplitViewTopBottom, 150);
//    splitview_minsize1(SplitViewTopBottom, 150);
//    splitview_visible0(SplitViewTopBottom, true);
//    splitview_visible1(SplitViewTopBottom, true);

    /* put a left/right splitview in the canvasLayout */
    splitview_panel(SplitViewLeftRight, PanelLeft_SplitViewLeftRight);
    splitview_panel(SplitViewLeftRight, PanelRight_SplitViewLeftRight);
    // this cause segmentation fault!!!
//    layout_splitview(app->canvasLayout, SplitViewLeftRight, 0,0);

    /* put a top/bottom splitview in the splitviewLeftRight */
    //splitview_splitview(SplitViewLeftRight, SplitViewTopBottom);

	#ifdef INFINITE
    /* create a child top/bottom splitview in the left section */
    SplitView *childSplitView = splitview_horizontal();
    splitview_splitview(SplitViewLeftRight, childSplitView);
    splitview_minsize0(childSplitView, 100);
    splitview_minsize1(childSplitView, 100);
    splitview_visible0(childSplitView, true);
    splitview_visible1(childSplitView, true);
    //splitview_panel(SplitViewLeftRight, Panel_SplitViewLeftRight);
	#endif


    /* ------ status section */

    /* attach tab controls to statusLayout */
    //TabsData *tdata = heap_new0(TabsData);
    tabStatus = tabs_create(ekGUI_POS_TOP);
    tabs_length(tabStatus, 300);
    tabs_add_elem(tabStatus, "maxManage", NULL); tabs_OnSelect(tabStatus, listener(app, i_OnClick_tab, App));
    tabs_add_elem(tabStatus, "maxEngine", NULL); tabs_OnSelect(tabStatus, listener(app, i_OnClick_tab, App));
    tabs_add_elem(tabStatus, "maxAdapter", NULL); tabs_OnSelect(tabStatus, listener(app, i_OnClick_tab, App));
    tabs_add_elem(tabStatus, "maxCore", NULL); tabs_OnSelect(tabStatus, listener(app, i_OnClick_tab, App));
    tabs_add_elem(tabStatus, "maxOrchestrator", NULL); tabs_OnSelect(tabStatus, listener(app, i_OnClick_tab, App));
    tabs_add_elem(tabStatus, "maxIntegrator", NULL); tabs_OnSelect(tabStatus, listener(app, i_OnClick_tab, App));
    tabs_add_elem(tabStatus, "maxScale", NULL); tabs_OnSelect(tabStatus, listener(app, i_OnClick_tab, App));
    tabs_add_elem(tabStatus, "maxMind", NULL); tabs_OnSelect(tabStatus, listener(app, i_OnClick_tab, App));
    tabs_add_elem(tabStatus, "maxGate", NULL); tabs_OnSelect(tabStatus, listener(app, i_OnClick_tab, App));
    tabs_add_elem(tabStatus, "maxLicense", NULL); tabs_OnSelect(tabStatus, listener(app, i_OnClick_tab, App));
    tabs_add_elem(tabStatus, "maxServices", NULL); tabs_OnSelect(tabStatus, listener(app, i_OnClick_tab, App));

    /* attach tabStatus to statusLayout */
//    layout_tabs(app->statusLayoutMaxEngine, tabStatus, 0,0);

    /* attach textview control to statusLayout */
    textSize.width = 250;
    textSize.height = 1000;
    textview_size(app->textMaxManage, textSize);
    textview_size(app->textMaxEngine, textSize);
    textview_size(app->textMaxAdapter, textSize);
    textview_size(app->textMaxCore, textSize);
    textview_size(app->textMaxOrchestrator, textSize);
    textview_size(app->textMaxIntegrator, textSize);
    textview_size(app->textMaxScale, textSize);
    textview_size(app->textMaxMind, textSize);
    textview_size(app->textMaxGate, textSize);
    textview_size(app->textMaxLicense, textSize);
    textview_size(app->textMaxServices, textSize);

    /* 1.1 add a layout to panel e.g LayoutMaxEngine = 0, LayoutMaxAdapter = 1, ... */
    app->statusPanel = panel_create();
    app->statusLayoutMaxManage = layout_create(1,2);
    app->statusLayoutMaxEngine = layout_create(1,2);
    app->statusLayoutMaxAdapter = layout_create(1,2);
    app->statusLayoutMaxCore = layout_create(1,2);
    app->statusLayoutMaxOrchestrator = layout_create(1,2);
    app->statusLayoutMaxIntegrator = layout_create(1,2);
    app->statusLayoutMaxScale = layout_create(1,2);
    app->statusLayoutMaxMind = layout_create(1,2);
    app->statusLayoutMaxGate = layout_create(1,2);
    app->statusLayoutMaxLicense = layout_create(1,2);
    app->statusLayoutMaxServices = layout_create(1,2);

    /* 1.2 assign layout to statusPanel */
    app->layoutIndexMaxManage = panel_layout(app->statusPanel, app->statusLayoutMaxManage);
    app->layoutIndexMaxEngine = panel_layout(app->statusPanel, app->statusLayoutMaxEngine);
    app->layoutIndexMaxAdapter = panel_layout(app->statusPanel, app->statusLayoutMaxAdapter);
    app->layoutIndexMaxCore  = panel_layout(app->statusPanel, app->statusLayoutMaxCore);
    app->layoutIndexMaxOrchestrator = panel_layout(app->statusPanel, app->statusLayoutMaxOrchestrator);
    app->layoutIndexMaxIntegrator = panel_layout(app->statusPanel, app->statusLayoutMaxIntegrator);
    app->layoutIndexMaxScale = panel_layout(app->statusPanel, app->statusLayoutMaxScale);
    app->layoutIndexMaxMind = panel_layout(app->statusPanel, app->statusLayoutMaxMind);
    app->layoutIndexMaxGate = panel_layout(app->statusPanel, app->statusLayoutMaxGate);
    app->layoutIndexMaxLicense = panel_layout(app->statusPanel, app->statusLayoutMaxLicense);
    app->layoutIndexMaxServices = panel_layout(app->statusPanel, app->statusLayoutMaxServices);
	    printf(" %d %d \n", app->layoutIndexMaxEngine, app->layoutIndexMaxAdapter);

    /* 1.3 assign textview to the respective layout */
    layout_textview(app->statusLayoutMaxManage, app->textMaxManage, 0,1);
    layout_textview(app->statusLayoutMaxEngine, app->textMaxEngine, 0,1);
	    printf(" %d %d \n", app->layoutIndexMaxEngine, app->layoutIndexMaxAdapter);
    layout_textview(app->statusLayoutMaxAdapter, app->textMaxAdapter, 0,1);
	    printf(" %d %d \n", app->layoutIndexMaxEngine, app->layoutIndexMaxAdapter);
    layout_textview(app->statusLayoutMaxCore, app->textMaxCore, 0,1);
    layout_textview(app->statusLayoutMaxOrchestrator, app->textMaxOrchestrator, 0,1);
    layout_textview(app->statusLayoutMaxIntegrator, app->textMaxIntegrator, 0,1);
    layout_textview(app->statusLayoutMaxScale, app->textMaxScale, 0,1);
    layout_textview(app->statusLayoutMaxMind, app->textMaxMind, 0,1);
    layout_textview(app->statusLayoutMaxGate, app->textMaxGate, 0,1);
    layout_textview(app->statusLayoutMaxLicense, app->textMaxLicense, 0,1);
    layout_textview(app->statusLayoutMaxServices, app->textMaxServices, 0,1);

    /* 1.4 set the active layout = maxManage */
    panel_visible_layout(app->statusPanel, app->layoutIndexMaxEngine);
    panel_update(app->statusPanel);

    /* attach tabStatus to statusLayout */
    layout_tabs(app->statusLayoutMaxManage, tabStatus, 0,0);
    layout_tabs(app->statusLayoutMaxEngine, tabStatus, 0,0);
    layout_tabs(app->statusLayoutMaxAdapter, tabStatus, 0,0);
    layout_tabs(app->statusLayoutMaxCore, tabStatus, 0,0);
    layout_tabs(app->statusLayoutMaxOrchestrator, tabStatus, 0,0);
    layout_tabs(app->statusLayoutMaxIntegrator, tabStatus, 0,0);
    layout_tabs(app->statusLayoutMaxScale, tabStatus, 0,0);
    layout_tabs(app->statusLayoutMaxMind, tabStatus, 0,0);
    layout_tabs(app->statusLayoutMaxGate, tabStatus, 0,0);
    layout_tabs(app->statusLayoutMaxLicense, tabStatus, 0,0);
    layout_tabs(app->statusLayoutMaxServices, tabStatus, 0,0);

    layout_vsize(app->statusLayoutMaxManage, 0, 300);
    layout_vsize(app->statusLayoutMaxEngine, 0, 300);
    layout_vsize(app->statusLayoutMaxAdapter, 0, 300);
    layout_vsize(app->statusLayoutMaxCore, 0, 300);
    layout_vsize(app->statusLayoutMaxOrchestrator, 0, 300);
    layout_vsize(app->statusLayoutMaxIntegrator, 0, 300);
    layout_vsize(app->statusLayoutMaxScale, 0, 300);
    layout_vsize(app->statusLayoutMaxGate, 0, 300);
    layout_vsize(app->statusLayoutMaxLicense, 0, 300);
    layout_vsize(app->statusLayoutMaxServices, 0, 300);

    textview_scroll_visible(app->textMaxManage, TRUE, TRUE);
    textview_scroll_visible(app->textMaxEngine, TRUE, TRUE);
    textview_scroll_visible(app->textMaxAdapter, TRUE, TRUE);
    textview_scroll_visible(app->textMaxCore, TRUE, TRUE);
    textview_scroll_visible(app->textMaxOrchestrator, TRUE, TRUE);
    textview_scroll_visible(app->textMaxScale, TRUE, TRUE);
    textview_scroll_visible(app->textMaxGate, TRUE, TRUE);
    textview_scroll_visible(app->textMaxLicense, TRUE, TRUE);
    textview_scroll_visible(app->textMaxServices, TRUE, TRUE);

    printf(" %d %d \n", app->layoutIndexMaxEngine, app->layoutIndexMaxAdapter);

  /*      layout_vsize(statusLayout, 0, 200);  caused the menu text to disappear */
    /* create 4 imaginery windows */
    /* this is used when view_project windows crosses the boundaries of app->window */

    app->bar = progress_create();
    progress_width(app->bar, 50.0);


    /* ----- place the 3 sublayouts within the base layout */
    splitPanel = split_panel(app);
    layout_layout(baseLayout, app->buttonLayout, 0,0);
    layout_panel(baseLayout, splitPanel, 0,1);
    layout_panel(baseLayout, app->statusPanel, 0,2);
    layout_progress(baseLayout, app->bar, 0,3);

    panel_layout(panel, baseLayout);

#ifdef WAIT
#endif

    return panel;
}

/*---------------------------------------------------------------------------*/
static void i_OnMoved_AppWindow(App *app, Event *e)
{
//#ifdef TEST
        /* update the screen coordinates */
        //app->screen_coordinate.x = window_get_origin(app->window).x;
        //app->screen_coordinate.y = window_get_origin(app->window).y;

        textview_printf(app->textMaxManage, "App->screen coordinate :  %f, %f\n", app->screen_coordinate.x, app->screen_coordinate.y);
        textview_scroll_caret(app->textMaxManage);
        unref(e);
//#endif
}

static void i_OnResize_AppWindow(App *app, Event *e)
{
        /* update the screen resolution */
        app->sys_resolution.x = window_get_size(app->window).width;
        app->sys_resolution.y = window_get_size(app->window).height;

        textview_printf(app->textMaxManage, "App->screen size :  %f, %f\n", app->sys_resolution.x, app->sys_resolution.y);
        textview_scroll_caret(app->textMaxManage);

        /* readjust the layout HERE*/
        /* set a minimum height of the status section */
        layout_vsize(app->canvasLayout, 0, 1000);
        layout_vsize(app->statusLayoutMaxEngine, 0, 50);

        unref(e);
}

static void i_OnClose(App *app, Event *e)
{
    osapp_finish();
    unref(app);
    unref(e);
}

char *readfile(const char *file)
{
    char *buf = 0;
    FILE *fp;
    long unsigned int pos;

    fp = fopen(file, "rb");
    if( fp ) {
        fseek(fp, 0L, SEEK_END);
        pos = (long unsigned int) ftell(fp);
        fseek(fp, 0L, SEEK_SET);
        buf = (char*)malloc( pos + 1 );
        fread(buf, 1, pos, fp);
        buf[pos] = 0;
        fclose(fp);
    }
    return buf;
}

void read_json_config(App *app)
{
	json_object *root;
	json_object *nappgui;
	struct json_object *jversion, *jauthor, *jcompany;
	struct json_object *jua_client, *jsensor_ip, *jsensor_port, *jUaServer_ip, *jUaServer_port, *jUaServer_userid, *jUaServer_password, *jUaServer_hashpassword;
	struct json_object *jenv_sslcertificateloc, *jenv_privatekeyloc, *jenv_trustlistloc;

	char *content;
	BasicInfo basicInfo;
	UaClient uaClient;


	// print the contents of the json file
	content = readfile("/home/pi/nappgui_src/jacky/nappgui.json");
   	printf("Contents of JSON file\n%s\n", content);

	// process the json file
	root = json_object_from_file("/home/pi/nappgui_src/jacky/nappgui.json");

	/* section : nappgui */
	nappgui = json_object_object_get(root, "nappgui");
	if (nappgui != NULL)
	{
		jversion = json_object_object_get(nappgui, "version");
		if (jversion != NULL) {
			strncpy(basicInfo.version, json_object_get_string(jversion), 10);
		}
		jauthor = json_object_object_get(nappgui, "author");
		if (jauthor != NULL) {
	        	strncpy(basicInfo.author, json_object_get_string(jauthor), 50);
		}
		jcompany = json_object_object_get(nappgui, "company");
		if (jcompany != NULL) {
	        	strncpy(basicInfo.company, json_object_get_string(jcompany), 50);
		}

		/* section : ua_client */
		jua_client = json_object_object_get(nappgui, "ua_client");
		if (jua_client != NULL)
		{
			jsensor_ip = json_object_object_get(jua_client, "sensor_ip");
			if (jsensor_ip != NULL) {
				strncpy(uaClient.sensor_ip, json_object_get_string(jsensor_ip), 20);
			}
			jsensor_port = json_object_object_get(jua_client, "sensor_port");
			if (jsensor_port != NULL) {
				strncpy(uaClient.sensor_port, json_object_get_string(jsensor_port), 20);
			}
			jUaServer_ip = json_object_object_get(jua_client, "UAServer_ip");
			if (jUaServer_ip != NULL) {
				strncpy(uaClient.UaServer_ip, json_object_get_string(jUaServer_ip), 20);
			}
			jUaServer_port = json_object_object_get(jua_client, "UAServer_port");
			if (jUaServer_port != NULL) {
				strncpy(uaClient.UaServer_port, json_object_get_string(jUaServer_port), 20);
			}
			jUaServer_userid = json_object_object_get(jua_client, "UAServer_userid");
			if (jUaServer_userid != NULL) {
				strncpy(uaClient.UaServer_userid, json_object_get_string(jUaServer_userid), 100);
			}
                        jUaServer_password= json_object_object_get(jua_client, "UAServer_password");
                        if (jUaServer_password != NULL) {
                                strncpy(uaClient.UaServer_password, json_object_get_string(jUaServer_password), 100);
                        }
                        jUaServer_hashpassword= json_object_object_get(jua_client, "UAServer_hashpassword");
                        if (jUaServer_hashpassword != NULL) {
                                strncpy(uaClient.UaServer_hashpassword, json_object_get_string(jUaServer_hashpassword), 100);
                        }

			jenv_sslcertificateloc = json_object_object_get(jua_client, "env_sslcertificateloc");
			if (jenv_sslcertificateloc != NULL) {
				strncpy(uaClient.env_sslcertificateloc, json_object_get_string(jenv_sslcertificateloc), 100);
			}
			jenv_privatekeyloc =  json_object_object_get(jua_client, "env_privatekeyloc");
			if (jenv_privatekeyloc != NULL) {
				strncpy(uaClient.env_privatekeyloc, json_object_get_string(jenv_privatekeyloc), 100);
			}
                        jenv_trustlistloc =  json_object_object_get(jua_client, "env_trustlistloc");
                        if (jenv_trustlistloc != NULL) {
                                strncpy(uaClient.env_trustlistloc, json_object_get_string(jenv_trustlistloc), 100);
                        }

		}



		textview_printf(app->textMaxManage, "version = %s, author = %s, company = %s \n", basicInfo.version, basicInfo.author, basicInfo.company);
		textview_printf(app->textMaxManage, "sensor_ip = %s, sensor_port = %s, UAServer_ip = %s, UAServer_port = %s, UAServer_userid = %s, UAServer_password = %s, UAServer_hashpassword = %s \n",
				uaClient.sensor_ip, uaClient.sensor_port, uaClient.UaServer_ip, uaClient.UaServer_port, uaClient.UaServer_userid, uaClient.UaServer_password, uaClient.UaServer_hashpassword);
		textview_printf(app->textMaxManage, "env_sslcertificateloc = %s, env_privatekeyloc = %s, env_trustlistloc = %s \n",
				uaClient.env_sslcertificateloc, uaClient.env_privatekeyloc, uaClient.env_trustlistloc);
	}
}

void i_OnClick_ButtonLoginCancel(App *app, Event *e)
{
 
   osapp_finish();
   unref(app);
   unref(e);
   exit(0);
}

void i_OnClick_ButtonLoginOK(App *app, Event *e)
{
    window_stop_modal(app->modalWindow, 300);   /* 300 - value to be returned */
    unref(e);

}

void LoginDialog(App *app, Window *parent_window)
{

    Window *modalLogin;
    V2Df origin;
    float window_x, window_y;
    Panel *panel;
    ModalData *data;
    Layout *MainLayout, *LogoLayout, *TextLayout, *CredentialsLayout, *DecisionLayout;
    Label *label_prompt, *label_username, *label_password;
    Edit *edit_username, *edit_password;
    Button *pushOK, *pushCancel;

    /* get the size of the main window i.e. resolution */
    app->sys_resolution.x = window_get_size(app->window).width;
    app->sys_resolution.y = window_get_size(app->window).height;
    //app->screen_coordinate.x = window_get_origin(app->window).x;
    //app->screen_coordinate.y = window_get_origin(app->window).y;

    textview_printf(app->textMaxManage, "app->window size : width %f height %f \n", app->sys_resolution.x, app->sys_resolution.y);
    textview_scroll_caret(app->textMaxManage);


    /* put the image on a flat button and show it on the dialog box */
//    Button *CompanyLogo;
//    Image *banner;
//    ferror_t error = ekFOK;
//    uint32_t i;

    /* creates a modal window */
    modalLogin = window_create(ekWINDOW_EDGE | ekWINDOW_TITLE | ekWINDOW_CLOSE);
    window_title(modalLogin, "Welcome to MaxMachines");

    panel = panel_create();

    MainLayout = layout_create(1,4); /* col, row */
    LogoLayout = layout_create(1,1);
    TextLayout = layout_create(1,3);
    CredentialsLayout = layout_create(2,2);
    DecisionLayout = layout_create(5, 1);

    label_prompt = label_create();
    label_username = label_create();
    label_password = label_create();
    label_text(label_prompt, "Please enter your login credentials");
    label_text(label_username, "Username "); label_align(label_username, ekRIGHT);
    label_text(label_password, "Password "); label_align(label_password, ekRIGHT);

    edit_username = edit_create();
    edit_password = edit_create();
    edit_passmode(edit_password, TRUE);
#ifdef LOGO_TOO_BIG
    banner = image_from_file("/home/pi/nappgui_src/jacky/img/maxmachines-logo.png", error);
    banner = image_from_file("/home/pi/nappgui_src/jacky/img/maxmachines-banner-3.png", error);
    CompanyLogo = button_flat(); button_image(CompanyLogo, banner);
#endif

    //pushOK = button_push(); button_text(pushOK, "OK");button_OnClick(pushOK, listener(app, i_OnClick_ButtonLoginOK, App));
    pushOK = button_push(); button_text(pushOK, "OK");button_OnClick(pushOK, listener(app, i_OnClick_ButtonCancel, App));
    pushCancel = button_push(); button_text(pushCancel, "Cancel"); button_OnClick(pushCancel, listener(app, i_OnClick_ButtonLoginCancel, App));

    /* assigns the layout to the panel */
    panel_layout(panel, MainLayout);
    layout_layout(MainLayout, LogoLayout, 0,0);
    layout_layout(MainLayout, TextLayout, 0,1);
    layout_layout(TextLayout, CredentialsLayout, 0,1);
    layout_layout(MainLayout, DecisionLayout, 0,3);

    /* sets up margins and col width and row height */
    /* section 0 : col = 1, row = 1 */


    /* Section 1 : col = 1, row = 1 */
    layout_hsize(TextLayout, 0, 500);
//    layout_hmargin(TextLayout,0,5);
        layout_halign(TextLayout, 0,0, ekLEFT);
        layout_vmargin(TextLayout, 0, 0);
    layout_margin(TextLayout, 10); /* sets a fix margin around the border */

    /* Section 2 : col = 2, row = 2 */
    layout_vmargin(CredentialsLayout, 0, 2);
    layout_margin(CredentialsLayout, 10); /* set a fix margin around the border */

    /* Section 3 : col = 5, row = 1 */
//    for(i=0; i<5; i++)
//        layout_hsize(DecisionLayout, i, 10); /* set a fix width of all columns */
//    layout_vmargin(DecisionLayout, 0, 2);
    layout_margin(DecisionLayout, 10); /* set a fix margin around the border */

    /* assigns the interface objects i.e. label, edit, ... to the layout in X(col),Y(row) coordinate, starts with index 0 */
    /* Section 0 : col = 1, row = 1 */
#ifdef LOGO_TOO_BIG
    layout_button(LogoLayout, CompanyLogo, 0,0);
#endif

    /* Section 1 : col = 1, row = 1 */
    layout_label(TextLayout, label_prompt, 0,0);

    /* Section 2 : col = 2, row = 2 */
    layout_label(CredentialsLayout, label_username, 0, 0);
    layout_label(CredentialsLayout, label_password, 0, 1);
    layout_edit(CredentialsLayout, edit_username, 1,0);
    layout_edit(CredentialsLayout, edit_password, 1,1);

    /* Section 3 : col = 5, row = 1 */
    layout_button(DecisionLayout, pushOK, 1,0);
    layout_button(DecisionLayout, pushCancel, 3,0);

    /* assigns the panel to the window and saves the handle to app */
    panel_data(panel, &data, i_destroy_modal_data, ModalData);

    app->modalWindow = modalLogin;
    window_panel(modalLogin, panel);

    /* sets the default button to Cancel */
    window_defbutton(modalLogin, pushCancel);

    /* handle to target window to align centre to app->window centre */
    window_x = window_get_size(modalLogin).width;
    window_y = window_get_size(modalLogin).height;

    /* move the dialog window to the centre of the screen */
    origin.x = app->sys_resolution.x / 2 - window_x / 2 ;
    origin.y = app->sys_resolution.y / 2 - window_y / 2 ;
    //window_origin(modalLogin, window_client_to_screen(modalLogin, origin) );
    window_origin(modalLogin, origin );

textview_printf(app->textMaxManage, "nappmain.c (size_x : %f, size_y : %f)\n", window_x, window_y);
printf("napmmain.c (window size_x : %f, window size_y : %f)\n", window_x, window_y);
textview_printf(app->textMaxManage, "nappmain.c (app->sys_resolution.x = %f, app->sys-resolution.y = %f\n", app->sys_resolution.x, app->sys_resolution.y);
printf("nappmain.c (app->sys_resolution.x = %f, app->sys_resolution.y = %f\n", app->sys_resolution.x, app->sys_resolution.y);
textview_printf(app->textMaxManage, "nappmain.c (origin.x = %f, origin.y = %f\n", origin.x, origin.y);
printf("nappmain.c (origin.x = %f, origin.y = %f\n", origin.x, origin.y);


    //moveToCentre(modalLogin, app);
    window_modal(modalLogin, parent_window);

/*
    if (data != NULL)
        heap_delete(&data, ModalData);
    window_destroy(&app->modalWindow);
*/

}


/*---------------------------------------------------------------------------*/
// Runs in new thread
static uint32_t i_task_mongoose_main(App *app)
{
	// do the task work - do not touch any GUI object
	initialiseMongooseWebSocketClient(app);

	return 0;
}

// Runs in GUI thread
static void i_task_mongoose_update(App *app)
{
	// update the gui here
        bmutex_lock(app->mutex);
        textview_writef(app->textMaxManage, "Websocket Connection opened.. waiting for handshake .. \n");
        textview_scroll_caret(app->textMaxManage);
        bmutex_unlock(app->mutex);

}


// Runs in GUI thread
static void i_task_mongoose_end(App *data)
{
	// finish task code here
}
/*---------------------------------------------------------------------------*/


static App *i_create(void)
{

    //FPtr_task_main i_task_main=0;
    //FPtr_task_update i_task_update=0;
    //FPtr_task_end i_task_end=0;
    //const real32_t updatecycle = 1.0f;
    //TaskData *tdata;

    const double cycle = 0.04;
    Panel *panel;
    App *app = heap_new0(App);
    app->mutex = bmutex_create();
    if (app->mutex == NULL)
	exit(-1);

    // this is for webview - libwebkit2gtk
    // 1. bypass the strict sandbox that causes empty displays on Ubuntu24
    setenv("WEBKIT_DISABLE_SANDBOX_THIS_IS_DANGEROUS", "1", 1);
    // 2. forces stabke software compositing fallback on webkit under X11
    setenv("WEBKIT_DISABLE_DMABUF_RENDERER", "1", 1);


    app->nofilename = 1;        /* at initial launch, there is no filename indicated */
    app->window = window_create(ekWINDOW_EDGE | ekWINDOW_TITLE | ekWINDOW_MAX | ekWINDOW_MIN | ekWINDOW_CLOSE | ekWINDOW_RESIZE);
    window_title(app->window, "MaxMachines Product Demonstration");
    window_origin(app->window, v2df(500, 200));         /* move window to position */

    panel = i_panel_original(app);   /* function to create a panel */
    window_panel(app->window, panel); /* create a panel and attach to app->window */

    // show the main application window
    window_maximize(app->window);
    window_show(app->window);

    /* get the size of the main window i.e. resolution */
//    app->sys_resolution.x = window_get_size(app->window).width;
//    app->sys_resolution.y = window_get_size(app->window).height;
//    app->screen_coordinate.x = window_get_origin(app->window).x;
//    app->screen_coordinate.y = window_get_origin(app->window).y;

//    textview_printf(app->textMaxManage, "app->window size : width %f height %f \n", app->sys_resolution.x, app->sys_resolution.y);
//    textview_scroll_caret(app->textMaxManage);

    /* initialise all menu items under View */
    app->view_fileToolbar_IsShown = TRUE;
    app->view_viewToolbar_IsShown = TRUE;
    app->view_maxEngineToolbar_IsShown = TRUE;
    app->view_maxIntegratorToolbar_IsShown = TRUE;
    app->view_maxAdapterToolbar_IsShown = TRUE;
    app->view_maxGateToolbar_IsShown = TRUE;
    app->view_maxScaleToolbar_IsShown = TRUE;
    app->view_maxOrchestratorToolbar_IsShown = TRUE;
    app->view_maxMindToolbar_IsShown = TRUE;
    app->view_maxLicenseToolbar_IsShown = TRUE;


    // the following caused segmentation fault
    // runs a new thread/ task
#ifdef crashed
    tdata = (TaskData *)malloc(sizeof(TaskData));
    tdata->progress = 0;
    tdata->finished = false;
    tdata->app = app;
#endif
    #ifdef SWITCH_TO_PTHREAD
    //osapp_task(tdata, updatecycle, i_task_main, i_task_update, i_task_end, TaskData);
    #endif

/*ok*/

    createMenus(app);

    // show a login dialog box first
    LoginDialog(app, app->window);


    /*not required to be called upfront, but the individual createXXXWindow() will be invoked when a callback is invoked via the menu */
    /*createSubWindows(app->window); */

    /* on startup, launch all the View windows, then enable the ticks on the menuitem using createmenus()  Reason see below */
#ifdef WAIT
    ViewProject(app, app->window);
    ViewAddressSpace(app, app->window);
    ViewLog(app, app->window);
    ViewAttributes(app, app->window);
    ViewReferences(app, app->window);
#endif

    window_OnClose(app->window, listener(app, i_OnClose, App));
    window_OnMoved(app->window, listener(app, i_OnMoved_AppWindow, App));
    window_OnResize(app->window, listener(app, i_OnResize_AppWindow, App));

#ifdef WAIT
    window_show(app->imaginaryLeftWindow);
    window_show(app->imaginaryTopWindow);
    window_show(app->imaginaryRightWindow);
    window_show(app->imaginaryBottomWindow);
#endif


    read_json_config(app);

    // create a parallel thread
    osapp_task(app, cycle, i_task_mongoose_main, i_task_mongoose_update, i_task_mongoose_end, App);

    return app;
}

/*---------------------------------------------------------------------------*/

static void i_destroy(App **app)
{
    cassert_no_null(app);
    cassert_no_null(*app);
    window_destroy(&(*app)->window);
    heap_delete(app, App);
}



#include <osapp/osmain.h>
osmain(i_create, i_destroy, "", App)

// switch to osmain_sync() to invoke mongoose client every 40 msecs
//osmain_sync(0.04, i_create, i_destroy, i_update, "", App)
