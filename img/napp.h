#include <nappgui.h>
#include <osapp/osmain.h>
//#include "open62541.h"
#include <stdio.h>

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
    V2Df sys_resolution;        /* equivalent to the size of the app window */
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

    int nocertificate;
    const char *certificate;
    FILE *fp_certificate;
/*    Edit *edit_certificate; */

    int noprivatekey;
    const char *privatekey;
    FILE *fp_privatekey;
/*    Edit *edit_privatekey; */

/*    Button *pushCertificate, *pushPrivateKey; */

    /* handle to the active modal window */
    Window *modalWindow;

    FlyOut *View_Interconnectivity;
    int View_Interconnectivity_IsShown;
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

    MenuItem *view_interconnectivity, *view_project, *view_addressspace, *view_log, *view_attributes, *view_references;
    MenuItem *view_fileToolbar, *view_documentToolbar;
    MenuItem *view_maxEngineToolbar, *view_maxIntegratorToolbar, *view_maxAdapterToolbar, *view_maxGateToolbar, *view_maxScaleToolbar;
    MenuItem *view_maxOrchestratorToolbar, *view_maxMindToolbar, *view_maxLicenseToolbar;

    Window *imaginaryLeftWindow, *imaginaryTopWindow, *imaginaryRightWindow, *imaginaryBottomWindow;

    UaClient *ua_Client;
};

void createMenus(App *app);
void FileNew(App *app, Window *parent_window);
void FileOpen(App *app, Window *parent_window);
void FileSave(App *app, Window *parent_window);
void FileSaveAs(App *app, Window *parent_window);
void FileClose(App *app, Window *parent_window);
void FileQuit(App *app, Window *parent_window);

void ViewProject(App *app, Window *parent_window);
void ViewAddressSpace(App *app, Window *parent_window);
void ViewLog(App *app, Window *parent_window);
void ViewAttributes(App *app, Window *parent_window);
void ViewReferences(App *app, Window *parent_window);

void maxEngineStart(App *app, Window *parent_window);
void maxEngineStop(App *app, Window *parent_window);
void maxEngineAlarmsAndConditions(App *app, Window *parent_window);
void maxEngineLogsManagement(App *app, Window *parent_window);
void maxEngineReverseConnect(App *app, Window *parent_window);
void maxEngineUsersAccount(App *app, Window *parent_window);
void maxEngineSystemsAccount(App *app, Window *parent_window);
void maxEngineGenerateSSLCertificates(App *app, Window *parent_window);
void maxEngineRegisterAdapters(App *app, Window *parent_window);
void maxEngineStartupParameters(App *app, Window *parent_window);
void maxEngineCommunicationsProtocol(App *app, Window *parent_window);
void maxEngineViewStatistics(App *app, Window *parent_window);
void maxEngineViewLiveLogs(App *app, Window *parent_window);

void maxIntegratorRadiusServer(App *app, Window *parent_window);
void maxIntegratorLdapServer(App *app, Window *parent_window);
void maxIntegratorIAMServer(App *app, Window *parent_window);
void maxIntegratorGDSServer(App *app, Window *parent_window);
void maxIntegratorLDSServer(App *app, Window *parent_window);
void maxIntegratorSyslogServer(App *app, Window *parent_window);
void maxIntegratorHistorianServer(App *app, Window *parent_window);
void maxIntegratorWebAPIServer(App *app, Window *parent_window);

void maxAdapterDiscoverDevices(App *app, Window *parentWindow);
void maxAdapterAutoGenerate(App *app, Window *parentWindow);
void maxAdapterSimRun(App *app, Window *parentWindow);
void maxAdapterManualConfiguration(App *app, Window *parentWindow);

void maxScaleSetupInstance(App *app, Window *parentWindow);
void maxScaleConfiguration(App *app, Window *parentWindow);

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


void i_OnClick_menu_file_open(App *app, Event *e);
void i_OnClick_menu_file_save(App *app, Event *e);
void i_OnClick_menu_file_saveAs(App *app, Event *e);
void i_OnClick_menu_file_close(App *app, Event *e);
void i_OnClick_file_open(App *app, Event *e);
void i_OnClick_file_save(App *app, Event *e);
void i_OnClick_file_saveAs(App *app, Event *e);
void i_OnClick_file_close(App *app, Event *e);

void i_OnClick_ButtonCancel(App *app, Event *e);
void i_OnClick_ButtonCertificate(App *app, Event *e);
void i_OnClick_ButtonPrivateKey(App *app, Event *e);
void i_OnClick_radioAnonymous(App *app, Event *e);
void i_OnClick_radioUsernamePassword(App *app, Event *e);
void i_OnClick_radioCertificateKey(App *app, Event *e);
void i_destroy_modal_data(ModalData** data);
void moveToCentre(Window *window, App *app);


