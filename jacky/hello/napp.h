#include <nappgui.h>
#include <osapp/osmain.h>
//#include "open62541.h"
#include <stdio.h>
#include "mongoose.h"
#include <ogl3d/ogl3d.h>

       typedef struct _CKeyValuePair {
                char *key;
                char *value;
        } CKeyValuePair;

        typedef struct _CMapData {
                CKeyValuePair *pairs;
                int count;
        } CMapData;

char* searchKeyValuePairResults(const char *);


typedef struct _treenode_t TreeNode;
typedef struct _appdata_t AppData;

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

typedef struct _basic_info_t BasicInfo;
struct _basic_info_t
{
        char version[10];
        char author[50];
        char company[50];
};

typedef struct _Ua_client_t UaClient;
struct _Ua_client_t
{
/* follows the definition in open62541/include/open62541/client.h */
    char sensor_ip[20];
    char sensor_port[20];
    char UaServer_ip[20];
    char UaServer_port[20];
    char UaServer_userid[100];
    char UaServer_password[100];
    char UaServer_hashpassword[100];

    char env_sslcertificateloc[100];
    char env_privatekeyloc[100];
    char env_trustlistloc[100];
//    UA_ByteString certificate;
//    UA_ByteString privatekey;
//    UA_ByteString *trustList;
    size_t trustListSize;
//    UA_ByteString *revocationList;
    size_t revocationListSize;

    void *clientContext;
//    UA_Logger *logging;
//    UA_Int32 timeout;
//    UA_ApplicationDescription clientDescription;
//    UA_String endpointUri;
    /**
     * Connection configuration
    **/
//    UA_ExtensionObject userIdentityToken;
//    UA_MessageSecurityMode securityMode;
//    UA_String securityPolicyUri;
//    UA_Boolean noSession;
//    UA_Boolean noReconnect;
//    UA_Boolean noNewSession;
//    UA_EndpointDescription endpoint;
//    UA_UserTokenPolicy userTokenPolicy;
//    UA_String applicationUri;
    /**
     * Custom Data Types
    **/
//    const UA_DataTypeArray *customDataTypes;
    /**
     * Advanced Client Configuration
     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
//    UA_UInt32 secureChannelLifeTime; 
//    UA_UInt32 requestedSessionTimeout;
//    UA_ConnectionConfig localConnectionConfig;
//    UA_UInt32 connectivityCheckInterval;
    /* EventLoop */
 //   UA_EventLoop *eventLoop;
 //   UA_Boolean externalEventLoop; 
    /* Available SecurityPolicies */
    size_t securityPoliciesSize;
//    UA_SecurityPolicy *securityPolicies;
    /* Certificate Verification Plugin */
//    UA_CertificateVerification certificateVerification;
    size_t authSecurityPoliciesSize;
//    UA_SecurityPolicy *authSecurityPolicies;
    /* SecurityPolicyUri for the Authentication. */
//    UA_String authSecurityPolicyUri;
//    void (*stateCallback)(UA_Client *client,
//                          UA_SecureChannelState channelState,
//                          UA_SessionState sessionState,
//                          UA_StatusCode connectStatus);
//    void (*inactivityCallback)(UA_Client *client);
    /* Number of PublishResponse queued up in the server */
//    UA_UInt16 outStandingPublishRequests;
//    void (*subscriptionInactivityCallback)(UA_Client *client,
//                                           UA_UInt32 subscriptionId,
//                                           void *subContext);
    /* Session config */
//    UA_String sessionName;
//    UA_LocaleId *sessionLocaleIds;
    size_t sessionLocaleIdsSize;
#ifdef UA_ENABLE_ENCRYPTION
    UA_StatusCode (*privateKeyPasswordCallback)(UA_ClientConfig *cc,
                                                UA_ByteString *password);
#endif
};

typedef struct _app_t App;
struct _app_t
{
    Mutex *mutex;
    int wsclient_callback_state;
    byte_t *wsclient_callback_text;

    V2Df sys_resolution;        /* equivalent to the size of the app window */
    V2Df screen_coordinate;     /* this is the current position of the app window */

    Window *window;
    Menu *top_menu;

    MenuItem *view;
    Menu *submenu_view;

    Panel *statusPanel;
    uint32_t layoutIndexMaxEngine, layoutIndexMaxAdapter, layoutIndexMaxCore, layoutIndexMaxOrchestrator, layoutIndexMaxIntegrator, layoutIndexMaxScale;
    uint32_t layoutIndexMaxMind, layoutIndexMaxGate, layoutIndexMaxLicense, layoutIndexMaxServices, layoutIndexMaxManage;
    Layout *statusLayoutMaxEngine, *statusLayoutMaxAdapter, *statusLayoutMaxCore, *statusLayoutMaxOrchestrator, *statusLayoutMaxIntegrator;
    Layout *statusLayoutMaxScale, *statusLayoutMaxMind, *statusLayoutMaxGate, *statusLayoutMaxLicense, *statusLayoutMaxServices, *statusLayoutMaxManage;

    Layout *buttonLayout, *canvasLayout;
    Progress *bar;

    TableView *dataTableLeftTop1;

    View *viewA;
    Panel *panelATop, *panelABottom;
    Layout *layoutATop, *layoutABottom;
    OGLCtx *gl_context;

    TextView *text;
    TextView *textMaxEngine, *textMaxCore, *textMaxAdapter, *textMaxOrchestrator, *textMaxIntegrator, *textMaxScale, *textMaxMind, *textMaxGate, *textMaxLicense, *textMaxServices;
    TextView *textMaxManage;
    uint32_t clicks;

    /* at initial launch, there is no filename indicated, so nofilename = 1 */
    int nofilename;
    const char *savedFile;
    FILE *fp;

    /* used in ServerAdd() */
    const char *ServerName;

    int nocertificate;
    const char *certificate;
    FILE *fp_certificate;
/*    Edit *edit_certificate; */

    int noprivatekey;
    const char *privatekey;
    FILE *fp_privatekey;
/*    Edit *edit_privatekey; */

/*    Button *pushCertificate, *pushPrivateKey; */
    Button *buttonFileNew; 

    /* handle to the active modal window */
    Window *modalWindow;

    FlyOut *View_Interconnectivity;
    int View_Interconnectivity_IsShown;
    FlyOut *View_Project;
    int View_Project_IsShown;
    FlyOut *View_Attributes;
    int View_Attributes_IsShown;
    FlyOut *View_References;
    int View_References_IsShown;
    FlyOut *View_AddressSpace;
    int View_AddressSpace_IsShown;

    FlyOut *View_maxAdapter;
    int View_maxAdapter_IsShown;
    FlyOut *View_maxGate;
    int View_maxGate_IsShown;
    FlyOut *View_maxIntegrator;
    int View_maxIntegrator_IsShown;

    FlyOut *View_Log;
    int View_Log_IsShown;

    MenuItem *view_interconnectivity, *view_project, *view_attributes, *view_log, *view_addressspace, *view_maxAdapter, *view_maxGate, *view_maxIntegrator, *view_references;
    MenuItem *view_fileToolbar, *view_viewToolbar, *view_documentToolbar;
    MenuItem *view_maxEngineToolbar, *view_maxCoreToolbar, *view_maxIntegratorToolbar, *view_maxAdapterToolbar, *view_maxGateToolbar, *view_maxScaleToolbar;
    MenuItem *view_maxOrchestratorToolbar, *view_maxMindToolbar, *view_maxLicenseToolbar, *view_maxServicesToolbar;
    MenuItem *maxAdapter_Start, *maxAdapter_Stop;
    MenuItem *maxEngine_ViewLiveLogs, *maxAdapter_ViewLiveLogs, *maxCore_ViewLiveLogs, *maxIntegrator_ViewLiveLogs;

    bool_t view_fileToolbar_IsShown, view_viewToolbar_IsShown, view_maxCoreToolbar_IsShown, view_maxEngineToolbar_IsShown, view_maxIntegratorToolbar_IsShown;
    bool_t view_maxAdapterToolbar_IsShown;
    bool_t view_maxGateToolbar_IsShown, view_maxScaleToolbar_IsShown, view_maxOrchestratorToolbar_IsShown, view_maxMindToolbar_IsShown, view_maxLicenseToolbar_IsShown;
    bool_t view_maxServicesToolbar_IsShown, view_documentToolbar_IsShown;

    bool_t maxEngine_viewLiveLogs_IsShown, maxAdapter_viewLiveLogs_IsShown, maxCore_viewLiveLogs_IsShown, maxIntegrator_viewLiveLogs_IsShown;

    Window *imaginaryLeftWindow, *imaginaryTopWindow, *imaginaryRightWindow, *imaginaryBottomWindow;
    Window *PopupBrowserCompany;

    UaClient *ua_Client;

    /* mongoose web socket */
    struct mg_mgr ws_mgr;
    struct mg_connection *ws_mg_client;
    char serverLogs[100];
};

typedef struct _task_data_t TaskData;
struct _task_data_t {
	uint32_t progress;
	bool finished;
	App *app;
};

void initialiseMongooseWebSocketClient(App *);

void createMenus(App *app);
void FileNew(App *app, Window *parent_window);
void FileOpen(App *app, Window *parent_window);
void FileSave(App *app, Window *parent_window);
void FileSaveAs(App *app, Window *parent_window);
void FileClose(App *app, Window *parent_window);
void FileQuit(App *app, Window *parent_window);

void ViewInterconnectivity(App *app, Window *parent_window);
void ViewProject(App *app, Window *parent_window);
void ViewAttributes(App *app, Window *parent_window);
void ViewReferences(App *app, Window *parent_window);
void ViewAddressSpace(App *app, Window *parent_window);
void ViewmaxAdapter(App *app, Window *parent_window);
void ViewmaxGate(App *app, Window *parent_window);
void ViewmaxIntegrator(App *app, Window *parent_window);
void ViewLog(App *app, Window *parent_window);

void maxEngineOneClickStart(App *app, Window *parent_window);
void maxEngineOneClickStop(App *app, Window *parent_window);
void maxEngineViewStatistics(App *app, Window *parent_window);
void maxEngineViewLiveLogs(App *app, Window *parent_window);

void maxCoreRegisterAdapters(App *app, Window *parent_window);
void maxCoreViewLiveLogs(App *app, Window *parent_window);
void maxCoreRegisterMaxAdapter(App *app, Window *parent_window);
void maxCoreLogsManagement(App *app, Window *parent_window);
void maxCoreStartupParameters(App *app, Window *parent_window);
void maxCoreViewStatistics(App *app, Window *parent_window);
void maxCoreViewLiveLogs(App *app, Window *parent_window);
void maxCoreWebSocketService(App *app, Window *parent_window);

void maxAdapterStartInstance(App *app, Window *parent_window);
void maxAdapterStopInstance(App *app, Window *parent_window);
void maxAdapterAlarmsAndConditions(App *app, Window *parent_window);
void maxAdapterEvents(App *app, Window *parent_window);
void maxAdapterLogsManagement(App *app, Window *parent_window);
void maxAdapterReverseConnect(App *app, Window *parent_window);
void maxAdapterStartupParameters(App *app, Window *parent_window);
void maxAdapterCommunicationsProtocol(App *app, Window *parent_window);
void maxAdapterViewStatistics(App *app, Window *parent_window);
void maxAdapterDiscoverDevices(App *app, Window *parent_window);
void maxAdapterAutoGenerate(App *app, Window *parent_window);
void maxAdapterSimulateAndConnect(App *app, Window *parent_window);
void maxAdapterEditDeviceNodeset(App *app, Window *parent_window);
void maxAdapterManualConfiguration(App *app, Window *parent_window);

void maxServicesUsersAccount(App *app, Window *parent_window);
void maxServicesSystemsAccount(App *app, Window *parent_window);
void maxServicesGenerateSSLCertificates(App *app, Window *parent_window);

void maxIntegratorRadiusServer(App *app, Window *parent_window);
void maxIntegratorLdapServer(App *app, Window *parent_window);
void maxIntegratorIAMServer(App *app, Window *parent_window);
void maxIntegratorSyslogServer(App *app, Window *parent_window);
void maxIntegratorAmqpServer(App *app, Window *parent_window);
void maxIntegratorMessageBrokerServer(App *app, Window *parent_window);
void maxIntegratorWebAPIServer(App *app, Window *parent_window);
void maxIntegratorWebSocketServer(App *app, Window *parent_window);
void maxIntegratorProxyServer(App *app, Window *parent_window);
void maxIntegratorOPCUAServer(App *app, Window *parent_window);
void maxIntegratorGDSServer(App *app, Window *parent_window);
void maxIntegratorLDSServer(App *app, Window *parent_window);
void maxIntegratorHistorianServer(App *app, Window *parent_window);

void maxAdapterDiscoverDevices(App *app, Window *parentWindow);
void maxAdapterAutoGenerate(App *app, Window *parentWindow);
void maxAdapterSimRun(App *app, Window *parentWindow);
void maxAdapterNodesetEditor(App *app, Window *parentWindow);
void maxAdapterManualConfiguration(App *app, Window *parentWindow);

void maxScaleSetupInstance(App *app, Window *parentWindow);
void maxScaleConfiguration(App *app, Window *parentWindow);

void maxOrchestratorDefineDataflow(App *app, Window *parent_window);

void maxMindDigitalTwin(App *app, Window *parentWindow);
void maxMindRealTimeAnalytics(App *app, Window *parentWindow);
void maxMindMachineLearning(App *app, Window *parentWindow);

void maxGateStartInstance(App *app, Window *parentWindow);
void maxGateStopInstance(App *app, Window *parentWindow);
void maxGateInspectInstance(App *app, Window *parentWindow);
void maxGateManualConfiguration(App *app, Window *parentWindow);

void CertificateOpen(App *app, Window *parent_window);
void PrivateKeyOpen(App *app, Window *parent_window);


void ClientAdd(App *app, Window *parent_window);
void ClientRemove(App *app, Window *parent_window);
void ClientConnect(App *app, Window *parent_window);
void ClientDisconnect(App *app, Window *parent_window);
void ClientProperties(App *app, Window *parent_window);
void ClientChangeUser(App *app, Window *parent_window);
void ClientChangePassword(App *app, Window *parent_window);

void ServerStart(App *app, Window *parent_window);
void ServerStop(App *app, Window *parent_window);
void ServerProperties(App *app, Window *parent_window);
void ServerAdduser(App *app, Window *parent_window);
void ServerEdituser(App *app, Window *parent_window);

void interfacesModbusTCP(App *app, Window *parent_window);
void interfacesModbusRTU(App *app, Window *parent_window);
void interfacesEtherCAT(App *app, Window *parent_window);
void interfacesTwinCATADS(App *app, Window *parent_window);
void interfacesEthernetIP(App *app, Window *parent_window);
void interfacesProfiNet(App *app, Window *parent_window);

void helpAbout(App *app, Window *parent_window);


void i_OnClick_menu_file_new(App *app, Event *e);
void i_OnClick_menu_file_open(App *app, Event *e);
void i_OnClick_menu_file_save(App *app, Event *e);
void i_OnClick_menu_file_saveAs(App *app, Event *e);
void i_OnClick_menu_file_clode(App *app, Event *e);
void i_OnClick_menu_file_quit(App *app, Event *e);
void i_OnClick_menu_project_new(App *app, Event *e);
void i_OnClick_menu_project_open(App *app, Event *e);
void i_OnClick_menu_project_save(App *app, Event *e);
void i_OnClick_menu_project_saveAs(App *app, Event *e);
void i_OnClick_menu_project_close(App *app, Event *e);
void i_OnClick_menu_project_quit(App *app, Event *e);

void i_OnClick_project_new(App *app, Event *e);
void i_OnClick_project_open(App *app, Event *e);
void i_OnClick_project_save(App *app, Event *e);
void i_OnClick_project_saveAs(App *app, Event *e);
void i_OnClick_project_close(App *app, Event *e);
void i_OnClick_project_quit(App *app, Event *e);


void i_OnClick_ButtonCancel(App *app, Event *e);
void i_OnClick_ButtonCertificate(App *app, Event *e);
void i_OnClick_ButtonPrivateKey(App *app, Event *e);
void i_OnClick_radioAnonymous(App *app, Event *e);
void i_OnClick_radioUsernamePassword(App *app, Event *e);
void i_OnClick_radioCertificateKey(App *app, Event *e);
void i_destroy_modal_data(ModalData** data);
void moveToCentre(Window *window, App *app);

void i_OnClick_menu_view_interconnectivity(App *app, Event *e);
void i_OnClick_menu_view_project(App *app, Event *e);
void i_OnClick_menu_view_attributes(App *app, Event *e);
void i_OnClick_menu_view_references(App *app, Event *e);
void i_OnClick_menu_view_addressspace(App *app, Event *e);
void i_OnClick_menu_view_maxAdapter(App *app, Event *e);
void i_OnClick_menu_view_maxGate(App *app, Event *e);
void i_OnClick_menu_view_maxIntegrator(App *app, Event *e);
void i_OnClick_menu_view_log(App *app, Event *e);
void i_OnClick_menu_view_filetoolbar(App *app, Event *e);
void i_OnClick_menu_view_viewtoolbar(App *app, Event *e);
void i_OnClick_menu_view_maxEnginetoolbar(App *app, Event *e);
void i_OnClick_menu_view_maxIntegratortoolbar(App *app, Event *e);
void i_OnClick_menu_view_maxAdaptertoolbar(App *app, Event *e);
void i_OnClick_menu_view_maxGatetoolbar(App *app, Event *e);
void i_OnClick_menu_view_maxScaletoolbar(App *app, Event *e);
void i_OnClick_menu_view_maxOrchestratortoolbar(App *app, Event *e);
void i_OnClick_menu_view_maxMindtoolbar(App *app, Event *e);
void i_OnClick_menu_view_maxLicensetoolbar(App *app, Event *e);
void i_OnClick_menu_view_documenttoolbar(App *app, Event *e);

void i_OnClick_menu_maxengine_start(App *app, Event *e);
void i_OnClick_menu_maxengine_stop(App *app, Event *e);
void i_OnClick_menu_maxengine_viewstatistics(App *app, Event *e);
void i_OnClick_menu_maxengine_viewlivelogs(App *app, Event *e);

void i_OnClick_menu_maxcore_start(App *app, Event *e);
void i_OnClick_menu_maxcore_stop(App *app, Event *e);
void i_OnClick_menu_maxcore_registermaxadapters(App *app, Event *e);
void i_OnClick_menu_maxcore_startupparameters(App *app, Event *e);
void i_OnClick_menu_maxcore_viewstatistics(App *app, Event *e);
void i_OnClick_menu_maxcore_viewlivelogs(App *app, Event *e);
void i_OnClick_menu_maxcore_websocketservice(App *app, Event *e);


void i_OnClick_menu_maxadapter_start(App *app, Event *e);
void i_OnClick_menu_maxadapter_stop(App *app, Event *e);
void i_OnClick_menu_maxadapter_alarmsandconditions(App *app, Event *e);
void i_OnClick_menu_maxadapter_events(App *app, Event *e);
void i_OnClick_menu_maxadapter_logsmanagement(App *app, Event *e);
void i_OnClick_menu_maxadapter_reverseconnect(App *app, Event *e);
void i_OnClick_menu_maxadapter_startupparameters(App *app, Event *e);
void i_OnClick_menu_maxadapter_communications(App *app, Event *e);
void i_OnClick_menu_maxadapter_viewstatistics(App *app, Event *e);
void i_OnClick_menu_maxadapter_discoverdevices(App *app, Event *e);
void i_OnClick_menu_maxadapter_autogenerate(App *app, Event *e);
void i_OnClick_menu_maxadapter_nodeseteditor(App *app, Event *e);
void i_OnClick_menu_maxadapter_simrun(App *app, Event *e);
void i_OnClick_menu_maxadapter_manualconfiguration(App *app, Event *e);

void i_OnClick_menu_maxIntegrator_radiusservice(App *app, Event *e);
void i_OnClick_menu_maxIntegrator_ldapservice(App *app, Event *e);
void i_OnClick_menu_maxIntegrator_iamservice(App *app, Event *e);
void i_OnClick_menu_maxIntegrator_syslogservice(App *app, Event *e);
void i_OnClick_menu_maxIntegrator_amqpservice(App *app, Event *e);
void i_OnClick_menu_maxIntegrator_mqttservice(App *app, Event *e);
void i_OnClick_menu_maxIntegrator_websocketservice(App *app, Event *e);
void i_OnClick_menu_maxIntegrator_webapiservice(App *app, Event *e);
void i_OnClick_menu_maxIntegrator_proxyservice(App *app, Event *e);
void i_OnClick_menu_maxIntegrator_opcuaservice(App *app, Event *e);
void i_OnClick_menu_maxIntegrator_gdsservice(App *app, Event *e);
void i_OnClick_menu_maxIntegrator_ldsservice(App *app, Event *e);
void i_OnClick_menu_maxIntegrator_historianservice(App *app, Event *e);

void i_OnClick_menu_maxscale_instancesetup(App *app, Event *e);
void i_OnClick_menu_maxscale_configuration(App *app, Event *e);

void i_OnClick_menu_maxOrchestrator_defineDataflow(App *app, Event *e);

void i_OnClick_menu_maxmind_digitaltwin(App *app, Event *e);
void i_OnClick_menu_maxmind_analytics(App *app, Event *e);
void i_OnClick_menu_maxmind_machinelearning(App *app, Event *e);

void i_OnClick_menu_maxgate_start(App *app, Event *e);
void i_OnClick_menu_maxgate_stop(App *app, Event *e);
void i_OnClick_menu_maxgate_inspect(App *app, Event *e);
void i_OnClick_menu_maxgate_manualconfiguration_add(App *app, Event *e);

void i_OnClick_menu_maxLicense_activate(App *app, Event *e);
void i_OnClick_menu_maxLicense_inspect(App *app, Event *e);
void i_OnClick_menu_maxLicense_request(App *app, Event *e);

void i_OnClick_menu_maxservices_usersaccount(App *app, Event *e);
void i_OnClick_menu_maxservices_systemsaccount(App *app, Event *e);
void i_OnClick_menu_maxservices_generatesslcertificates(App *app, Event *e);


void i_OnClick_settings_configure_OPCSvr(App *app, Event *e);
void i_OnClick_settings_configure_LDS(App *app, Event *e);
void i_OnClick_settings_configure_GDS(App *app, Event *e);

void i_OnClick_settings_interfaces_modbusTCP(App *app, Event *e);
void i_OnClick_settings_interfaces_modbusRTU(App *app, Event *e);
void i_OnClick_settings_interfaces_EtherCAT(App *app, Event *e);
void i_OnClick_settings_interfaces_TwinCATADS(App *app, Event *e);
void i_OnClick_settings_interfaces_EthernetIP(App *app, Event *e);
void i_OnClick_settings_interfaces_ProfiNet(App *app, Event *e);
void i_OnClick_settings_configure_message_broker(App *app, Event *e);
void i_OnClick_settings_managecertificates(App *app, Event *e);

void i_OnClick_menu_help_manual(App *app, Event *e);
void i_OnClick_menu_help_whatsthis(App *app, Event *e);
void i_OnClick_menu_help_licensestatus(App *app, Event *e);
void i_OnClick_menu_help_checkforupdates(App *app, Event *e);
void i_OnClick_menu_help_about(App *app, Event *e);

void i_OnClick_client_add(App *app, Event *e);
void i_OnClick_client_remove(App *app, Event *e);
void i_OnClick_client_connect(App *app, Event *e);
void i_OnClick_client_disconnect(App *app, Event *e);
void i_OnClick_client_properties(App *app, Event *e);
void i_OnClick_client_changeuser(App *app, Event *e);
void i_OnClick_client_changepassword(App *app, Event *e);

void i_OnClick_server_start(App *app, Event *e);
void i_OnClick_server_stop(App *app, Event *e);
void i_OnClick_server_properties(App *app, Event *e);
void i_OnClick_server_adduser(App *app, Event *e);
void i_OnClick_server_edituser(App *app, Event *e);

void i_OnClick_document_add(App *app, Event *e);
void i_OnClick_document_remove(App *app, Event *e);
void i_OnClick_document_hide_unhide(App *app, Event *e);
void i_OnClick_settings_plugins(App *app, Event *e);


void i_OnClick_ButtonLoginCancel(App *app, Event *e);
void i_OnClick_ButtonLoginOK(App *app, Event *e);
void i_OnClick_maxEngine_viewstatistics(App *app, Event *e);
void i_OnClick_maxEngine_viewlivelogs(App *app, Event *e);
void i_OnClick_maxcore_registermaxadapters(App *app, Event *e);
void i_OnClick_maxcore_registermaxadapters(App *app, Event *e);
void i_OnClick_maxCore_registermaxadapters(App *app, Event *e);
void i_OnClick_maxCore_startupparameters(App *app, Event *e);
void i_OnClick_maxCore_viewlivelogs(App *app, Event *e);
void i_OnClick_maxCore_viewstatistics(App *app, Event *e);
void i_OnClick_maxServices_usersaccount(App *app, Event *e);
void i_OnClick_maxServices_systemsaccount(App *app, Event *e);
void i_OnClick_maxServices_generatesslcertificates(App *app, Event *e);
void i_OnClick_maxAdapter_reverseconnect(App *app, Event *e);
void i_OnClick_maxAdapter_startupparameters(App *app, Event *e);
void i_OnTreeDataTableLeftBottom1(AppData *app, Event *e);

void LoginDialog(App *app, Window *parent_window);
void read_json_config(App *app);
char *readfile(const char *file);

Panel *split_panel(App *app);
void i_OnClick_tab(App *app, Event *e);

void FileExportToXML(App *app, Window *parent_window);
void FileExportToJSON(App *app, Window *parent_window);
void i_OnClick_webview_WindowClose(App *app, Event *e);

void maxAdapterViewLiveLogs(App *app, Window *parent_window, bool StartOrStop);

void maxIntegratorRabbitAqmpServer(App *app, Window *parent_window);
void maxIntegratorMqttServer(App *app, Window *parent_window);

void maxIntegratorViewStatistics(App *app, Window *parent_window);
void maxIntegratorViewLiveLogs(App *app, Window *parent_window);

void maxOrchestratorStart(App *app, Window *parent_window);
void maxOrchestratorStop(App *app, Window *parent_window);


void mgtimer_fn(void *arg);
