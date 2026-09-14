#include <nappgui.h>
#include <osapp/osmain.h>
#include <stdio.h>
#include <string.h>
#include <libssh2.h>
#include <libssh2_sftp.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "napp.h"


void to_uppercase(char *str) {
    if (str == NULL) return; // Safety check

    while (*str != '\0') {
        *str = toupper((unsigned char)*str);
        str++;
    }
}


static int waitsocket(libssh2_socket_t socket_fd, LIBSSH2_SESSION *session)
{
    struct timeval timeout;
    int rc;
    fd_set fd;
    fd_set *writefd = NULL;
    fd_set *readfd = NULL;
    int dir;

    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    FD_ZERO(&fd);

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#endif
    FD_SET(socket_fd, &fd);
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif

    /* now make sure we wait in the correct direction */
    dir = libssh2_session_block_directions(session);

    if(dir & LIBSSH2_SESSION_BLOCK_INBOUND)
        readfd = &fd;

    if(dir & LIBSSH2_SESSION_BLOCK_OUTBOUND)
        writefd = &fd;

    rc = select((int)(socket_fd + 1), readfd, writefd, NULL, &timeout);

    return rc;
}

// this is a common function to start and stop services (maxAdapter, maxIntegrator, haproxy, mqtt, etc
char *run_remote_command(const char *hostname, const char *username, const char *password, const char *command, bool pipe, char *buffer, TextView *widget, char *filename)
{

	printf("[run_remote_command] Command is %s \n", command);
        printf("hostname = %s, username = %s, password = %s, command = %s, filename = %s \n", hostname, username, password, command, filename);
	//textview_printf(widget, "hostname = %s, username = %s, password = %s, command = %s \n", hostname, username, password, command);

        bool error = FALSE;
        char *err_msg;
        int err_len, err_code, exitcode;
        int sock, status, i, auth_pw = 0;
        struct sockaddr_in sin;
        size_t rc; int argc;
        const char *fingerprint;
        LIBSSH2_SESSION *session;
        LIBSSH2_CHANNEL *channel;
        char message[255];
        char *userauthlist;
        //char buffer[1024];
        char password_buffer[1024];

        status = libssh2_init(0);
        if (status)
        {
                printf("failed to initialise libssh2 : %d \n", status);
                error = TRUE;
                goto shutdown;
        }
        else printf("1. Success initialise libssh2 \n");

        sock = socket(AF_INET, SOCK_STREAM, 0);

        sin.sin_family = AF_INET;
        sin.sin_port = htons(22);       // default SSH port is 22
        sin.sin_addr.s_addr = inet_addr(hostname);

        while (connect(sock, (struct sockaddr*)(&sin), sizeof(struct sockaddr_in)) != 0)
        {
                // try again
        }
        #ifdef WAIT
        if (connect(sock, (struct sockaddr*)(&sin), sizeof(struct sockaddr_in)) != 0) {
                printf("failed to connect to host : %s \n", hostname);
                error = TRUE;
                goto shutdown;
        } else
        #endif
        printf("2. Connect to host %s : success \n", hostname);
        //textview_printf(widget, "2. Connect to host %s : success \n", hostname);

        session = libssh2_session_init();
        if (!session) {
                printf("ssh session init failed \n");
                error = TRUE;
                goto shutdown;
        } else
        printf("3. ssh session initialisation : success \n");
        //textview_printf(widget, "3. ssh session initialisation : success \n");

        libssh2_trace(session, LIBSSH2_TRACE_AUTH);
        libssh2_session_set_blocking(session, 1);
        libssh2_session_set_timeout(session, 30000);

        #ifdef WAIT
        if (libssh2_session_startup(session, sock)) {
                fprintf(stderr, "Failure establishing SSH session\n");
                error = TRUE;
                goto shutdown;
        } else
        printf("4. ssh session startup : success \n");
        #endif

        rc = libssh2_session_handshake(session, sock);
        printf("rc = %ld \n", rc);       // -13
        if (rc < 0) {
                //libssh2_session_free(session);
                char *err_msg;
                int err_len;
                libssh2_session_last_error(session, &err_msg, &err_len, 0);
                fprintf(stderr, "Handshake protocol error details: %s\n", err_msg);

                printf("ssh session handshake failed : %ld \n", rc);
                //textview_printf(widget, "ssh session handshake failed : %ld \n", rc);

                error = TRUE;
                goto shutdown;
        } else {
                printf("5. ssh session handshake : success \n");
                //textview_printf(widget, "5. ssh session handshake : success \n");
	}

        rc=1;
        /* At this point we have not yet authenticated.  The first thing to do
         * is check the hostkey's fingerprint against our known hosts Your app
         * may have it hard coded, may go to a file, may present it to the
         * user, that is your call
        */
        fingerprint = libssh2_hostkey_hash(session, LIBSSH2_HOSTKEY_HASH_SHA256);
        fprintf(stderr, "Fingerprint (%s): ", hostname);
        if(!fingerprint) {
                fprintf(stderr, "(null)");
                error = TRUE;
                goto shutdown;
        }
        else
        {
                for(int i = 0; i < 32; i++)
                        fprintf(stderr, "%02X ", (unsigned char)fingerprint[i]);
                fprintf(stderr, "\n");
        }


        /* check what authentication methods are available */
        userauthlist = libssh2_userauth_list(session, username,
                                         (unsigned int)strlen(username));
        if(userauthlist) {
           fprintf(stderr, "6. Authentication methods: %s\n", userauthlist);
           if(strstr(userauthlist, "password"))
                auth_pw |= 1;
           if(strstr(userauthlist, "keyboard-interactive"))
                auth_pw |= 2;
           if(strstr(userauthlist, "publickey"))
                auth_pw |= 4;

           /* check for options */
           /*
           if(argc > 4) {
                if((auth_pw & 1) && !strcmp(argv[4], "-p"))
                        auth_pw = 1;
                if((auth_pw & 2) && !strcmp(argv[4], "-i"))
                        auth_pw = 2;
                if((auth_pw & 4) && !strcmp(argv[4], "-k"))
                        auth_pw = 4;
           }
           */
           auth_pw = 1;

           if(auth_pw & 1) {
                /* We could authenticate via password */
                if(libssh2_userauth_password(session, username, password)) {
                        fprintf(stderr, "Authentication by password failed.\n");
                        //textview_printf(stderr, "Authentication by password failed.\n");
                        goto shutdown;
                }
                else {
                        fprintf(stderr, "7. Authentication by password succeeded.\n");
                        //textview_printf(widget, "7. Authentication by password succeeded.\n");
		}
           }
           #ifdef NO_NEED
           else if(auth_pw & 2) {
                /* Or via keyboard-interactive */
                if(libssh2_userauth_keyboard_interactive(session, username,
                                                     &kbd_callback)) {
                        fprintf(stderr,
                                "Authentication by keyboard-interactive failed.\n");
                        //textview_printf(widget, "Authentication by keyboard-interactive failed.\n");
                        goto shutdown;
                }
                else
                        fprintf(stderr,
                                "Authentication by keyboard-interactive succeeded.\n");
                        textivew_printf(widget, "Authentication by keyboard-interactive succeeded.\n");
           }
           else if(auth_pw & 4) {
                /* Or by public key */
                size_t fn1sz, fn2sz;
                char *fn1, *fn2;
                char const *h = getenv("HOME");
                if(!h || !*h)
                        h = ".";
                /* Silence GCC -Wformat-truncation false positives by allocating
                   2 extra bytes for each buffer. */
                fn1sz = strlen(h) + strlen(pubkey) + 2 + 2;
                fn2sz = strlen(h) + strlen(privkey) + 2 + 2;
                fn1 = malloc(fn1sz);
                fn2 = malloc(fn2sz);
                if(!fn1 || !fn2) {
                        free(fn2);
                        free(fn1);
                        fprintf(stderr, "out of memory\n");
                        //textview_printf(widget, "out of memory\n");
                        goto shutdown;
                }
                /* Avoid false positives */
                /* Using asprintf() here would be much cleaner,
                   but less portable */
                snprintf(fn1, fn1sz, "%s/%s", h, pubkey);
                snprintf(fn2, fn2sz, "%s/%s", h, privkey);
                if(libssh2_userauth_publickey_fromfile(session, username,
                                                   fn1, fn2,
                                                   password)) {
                        fprintf(stderr, "Authentication by public key failed.\n");
                        //textview_printf(widget, "Authentication by public key failed.\n");
                        free(fn2);
                        free(fn1);
                        goto shutdown;
                }
                else {
                        fprintf(stderr, "Authentication by public key succeeded.\n");
                        //textview_printf(widget, "Authentication by public key succeeded.\n");
		}
                free(fn2);
                free(fn1);
           }
           #endif
           else {
            fprintf(stderr, "No supported authentication methods found.\n");
            //textview_printf(widget, "No supported authentication methods found.\n");
            goto shutdown;
           }
        }

        /* Request a session channel on which to run a shell */
        channel =  libssh2_channel_open_session(session);
        if (!channel) {
                err_code = libssh2_session_last_error(session, &err_msg, &err_len, 0);
                printf("Error Code: %d\n", err_code); //textview_printf(widget, "Error Code: %d \n", err_code);
                printf("Error Message: %s\n", err_msg); //textview_printf(widget, "Error Message: %s\n", err_msg);
                printf("ssh channel open session failed \n"); //textview_printf(widget, "ssh channel open session failed \n");
                error = TRUE;
                goto shutdown;
        } else
        printf("8. ssh channel open session : success \n"); //textview_printf(widget, "8. ssh channel open session : success \n");

        /* Request a PTY (pseudo-terminal */
        if (libssh2_channel_request_pty(channel, "xterm") != 0) {
                printf("Failed to allocate PTY \n"); //textview_printf(widget, "Failed to allocate PTY \n");
                error = TRUE;
                goto shutdown;
        } else
        printf("8a. pseudo terminal success \n"); //textview_printf(widget, "8a. pseudo terminal success \n");


        while ((status = libssh2_channel_exec(channel, command)) == LIBSSH2_ERROR_EAGAIN) {
                waitsocket(sock, session);
        }
        if (status != 0) {
                printf("ssh command failed : %d\n", status); //textview_printf(widget, "ssh command failed : %d\n", status);
                error = TRUE;
                goto shutdown;
        } else
        printf("9. ssh channel execute : %s : success %d \n", command, status);
	//textview_printf(widget, "9. ssh channel execute : %s : success %d \n", command, status);

/*
        usleep(50000);
        sprintf(password_buffer, "%s\n", password);
        while ((status = libssh2_channel_exec(channel, password_buffer)) == LIBSSH2_ERROR_EAGAIN) {
                waitsocket(sock, session);
        }
        if (status != 0) {
                printf("libssh2_channel_exec() failed : %d \n", status);
                error = TRUE;
                goto shutdown;
        } else
        printf("10. ssh channel execute : %s : success %d \n", command, status);
*/
        // read the output stream until End-Of-File
        printf("-------Command Output-----------\n"); //textview_printf(widget, "-------Command Output-----------\n");
        while ((rc = libssh2_channel_read_stderr(channel, buffer, sizeof(buffer) -1)) > 0) {
                buffer[rc] = '\0';
                printf("%s", buffer);
		//textview_printf(widget, "%s", buffer);
        }

        while ((rc = libssh2_channel_close(channel)) == LIBSSH2_ERROR_EAGAIN) {
                waitsocket(sock,session);
        }

        exitcode = libssh2_channel_get_exit_status(channel);

        libssh2_channel_send_eof(channel);
        libssh2_channel_wait_eof(channel);
        libssh2_channel_wait_closed(channel);
        printf("-------End Command Output %d-----------\n", exitcode);
	//textview_printf(widget, "-------End Command Output %d-----------\n", exitcode);

        // popup a modal dialog window to inform that process is completed

        if (error == TRUE)
	{
                printf("Fail to execute cmd : %s\n", command);
                sprintf(message, "Fail to execute cmd : %s\n", command);
		textview_printf(widget, "Fail to execute cmd : %s\n", command);
	}
        else
	{
                printf("cmd : %s is executed successfully \n", command);
                sprintf(message, "cmd : %s is executed successfully \n", command);
		textview_printf(widget, "cmd : %s is executed successfully \n", command);
	}


    // if pipe = TRUE, we want to pipe the output of the command <journalctl> to widget
    if (pipe == TRUE) // we want to grab the results of the cmd executed i.e. journalctrl command, CPU stats
    {

	/* --- ftell() cannot work with popen, use stat */
	//char command[1024];
	//sprintf(command, "echo %s | /usr/bin/sudo -S /bin/bash -c '/usr/bin/ssh -T %s@%s && cd /usr/local/src/ && /usr/bin/cat maxAdapterCpu'", password, username, hostname);


	//FILE *pipe = popen(command, "r");
	//if (!pipe) {

	//	printf("napp_common.c : %s : popen() failed \n", __func__);
	//	exit(0); // goto shutdown;
	//}
	//else
	{
		//printf("napp_common.c : %s : popen success \n", __func__);
		LIBSSH2_SFTP *sftp_session = NULL;
		LIBSSH2_SFTP_ATTRIBUTES attrs;
		long long file_size = -1, bytesRead, total_bytes;
		int rc;
		char *sftp_buffer;

		sftp_session = libssh2_sftp_init(session);
		if (!sftp_session) {
			printf("fail to initialise SFTP session on remote file : %s \n", filename);
			sprintf(message, "Unable to init SFTP session context on remote file : %s \n", filename);
			textview_printf(widget, "Unable to init SFTP session context on remote file : %s \n", filename);
		}
		else {
			printf("here : 0 \n");
			memset(&attrs, 0, sizeof(attrs));
			rc = libssh2_sftp_stat(sftp_session, "/usr/local/src/maxAdapterCpu", &attrs);
			if (rc == 0) {
				// Confirm the payload contains an authentic size value 
				if (attrs.flags & LIBSSH2_SFTP_ATTR_SIZE) {
			            file_size = (long long)attrs.filesize;
				    printf("file_size = %lld \n", file_size);

			}

			buffer = (char *)malloc(file_size * sizeof(char));
			#ifdef DEBUG
	                printf("--------------------------\n");
			#endif

			LIBSSH2_SFTP_HANDLE *handle = libssh2_sftp_open(sftp_session, filename, LIBSSH2_FXF_READ, 0);
			bytesRead = libssh2_sftp_read(handle, buffer, file_size-1);
			#ifdef DEBUG
			printf("bytesRead = %lld, file_size = %lld \n", bytesRead, file_size);
			#endif

	                buffer[bytesRead] = '\0';
               		//total_bytes += bytesRead;

			#ifdef DEBUG
	                printf("--------------------------\n");
	                printf("buffer is \n%s \n", buffer);
	                printf("--------------------------\n");
			#endif
		        } else {
				printf("Stat call succeeded, but size attribute flag is missing.\n");
		            	fprintf(stderr, "Stat call succeeded, but size attribute flag is missing.\n");
			}

			#ifdef DEBUG
	                printf("--------------------------\n");
			#endif
			//buffer = (char *)malloc(file_size * sizeof(char));
			//memcpy(buffer, sftp_buffer, file_size);

			//free (sftp_buffer);
			libssh2_sftp_shutdown(sftp_session);
			return buffer;
		}
	}

    }
    else if (pipe == FALSE) // we do not want the results of the cmd executed i.e. start/ stop services
    {
	// do nothing
	return NULL;
    }

    shutdown:
        // cleanup
        libssh2_channel_free(channel);
        libssh2_session_disconnect(session, "Normal shutdown");
        libssh2_session_free(session);
        close(sock);
        libssh2_exit();
    	return -1;
}
