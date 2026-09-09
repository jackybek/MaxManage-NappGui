#include <nappgui.h>
#include <osapp/osmain.h>
#include <stdio.h>
#include <string.h>
#include "napp.h"

void FileNew(App *app, Window *parent_window)
{


}

void FileOpen(App *app, Window *parent_window)
{
	const char_t *selected_file;
        const char_t *filetypeslist = {"uap"};
        const uint32_t size=1;

	//selected_file = comwin_open_file(parent_window, &filetypeslist, size, NULL);
        selected_file = comwin_open_file(parent_window,
                                        "caption",
                                        &filetypeslist,
                                        size, NULL, NULL);
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

void FileExportToXML(App *app, Window *parent_window)
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

void FileExportToJSON(App *app, Window *parent_window)
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

void FileSave(App *app, Window *parent_window)
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
		//saved_file = comwin_save_file(parent_window, filetypeslist, size, NULL);
        	saved_file = comwin_open_file(parent_window,
                                        "caption",
                                        filetypeslist,
                                        size, NULL, NULL);
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
                                	sprintf(title, "MaxMachines demonstration : %s", saved_file);
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

void FileSaveAs(App *app, Window *parent_window)
{
	/* regardless whether there is a previous filename, still launch the saveAs dialog */
	/* for debugging purposes, show it in the text widget */

        const char_t *saved_file;
        const char_t *filetypeslist[] = {"uap", "xml", "json"};
        const uint32_t size=3;
	char title[100];

        textview_printf(app->text, "Filename is %s, nofilename is %d \n", app->savedFile, app->nofilename);
        textview_scroll_caret(app->text);
		//saved_file = comwin_save_file(parent_window, filetypeslist, size, NULL);
        	saved_file = comwin_open_file(parent_window,
                                        "caption",
                                        filetypeslist,
                                        size, NULL, NULL);

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
				sprintf(title, "MaxMachines demonstration : %s", saved_file);
				window_title(app->window, title);
                        }
                        else
                        {
                                /* error creating file, show a dialog box */

                        }
                }

}

void FileClose(App *app, Window *parent_window)
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
	window_title(app->window, "MaxMachines demonstration");

	textview_printf(app->text, "Filename is %s, nofilename is %d \n", app->savedFile, app->nofilename);
        textview_scroll_caret(app->text);
}

void FileQuit(App *app, Window *parent_window)
{

}

