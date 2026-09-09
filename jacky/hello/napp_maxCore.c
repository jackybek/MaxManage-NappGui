#include <nappgui.h>
#include <osapp/osmain.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "napp.h"


void maxCoreStartupParameters(App *app, Window *parent_window)
{

}

void maxCoreRegisterAdapters(App *app, Window *parent_window)
{
        ferror_t error= ekFOK;
        ImageView *imgView;
        ImageView *maxEngineRegisterAdaptersView;
        Image *maxEngineRegisterAdaptersImage;

        textview_printf(app->text, "napp_maxEngine.c : Entering maxEngineRegisterAdapters() \n");
        maxEngineRegisterAdaptersView = imageview_create();
        maxEngineRegisterAdaptersImage = image_from_file("/home/pi/nappgui_src/jacky/img/registerAdapters.jpg", &error);
        if (maxEngineRegisterAdaptersImage!=NULL && error==ekFOK) {
                textview_printf(app->text, "napp_maxEngine.c : Here \n");
                /* hide */
                layout_show_col(app->canvasLayout, 0, FALSE);
                layout_show_row(app->canvasLayout, 0, FALSE);
                /* update the image */
                imageview_image(maxEngineRegisterAdaptersView, maxEngineRegisterAdaptersImage);
                imgView = layout_get_imageview(app->canvasLayout, 0,0); // get the handle to the imageView in the layout
                imageview_image(imgView, maxEngineRegisterAdaptersImage); // update the imgView with the new imageView
                layout_imageview(app->canvasLayout, imgView, 0,0); // assign the new imageView back to the layout
                /* show */
                layout_show_col(app->canvasLayout, 0, TRUE);
                layout_show_row(app->canvasLayout, 0, TRUE);
        }
        else
                textview_printf(app->text, "napp_maxEngine.c : Error loading /home/pi/nappgui_src/jacky/img/registerAdapters.jpg\n");
}

void maxCoreViewLiveLogs(App *app, Window *parent_window)
{

}


