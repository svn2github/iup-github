/** \file
 * \brief Frame Control
 *
 * See Copyright Notice in "iup.h"
 */

#include <gtk/gtk.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <stdarg.h>

#include "iup.h"

#include "iup_object.h"
#include "iup_layout.h"
#include "iup_attrib.h"
#include "iup_str.h"
#include "iup_dialog.h"
#include "iup_drv.h"
#include "iup_drvfont.h"
#include "iup_stdcontrols.h"

#include "iupgtk_drv.h"


void iupdrvFrameGetDecorOffset(int *x, int *y)
{
  *x = 2;
  *y = 2;
}

int iupdrvFrameHasClientOffset(void)
{
  return 0;
}

static char* gtkFrameGetTitleAttrib(Ihandle* ih)
{
  GtkFrame* frame = (GtkFrame*)ih->handle;
  return iupStrGetMemoryCopy(iupgtkStrConvertFromUTF8(gtk_frame_get_label(frame)));
}

static int gtkFrameSetTitleAttrib(Ihandle* ih, const char* value)
{
  if (iupAttribGetStr(ih, "_IUPFRAME_HAS_TITLE"))
  {
    GtkFrame* frame = (GtkFrame*)ih->handle;
    gtk_frame_set_label(frame, iupgtkStrConvertToUTF8(value));
  }
  return 0;
}

static int gtkFrameSetBgColorAttrib(Ihandle* ih, const char* value)
{
  unsigned char r, g, b;
  GtkWidget* label = gtk_frame_get_label_widget((GtkFrame*)ih->handle);

  if (!iupStrToRGB(value, &r, &g, &b))
    return 0;

  if (label)
    iupgtkSetBgColor(label, r, g, b);

  if (iupAttribGet(ih, "_IUPFRAME_HAS_BGCOLOR"))
  {
    GtkWidget* inner_parent = gtk_bin_get_child((GtkBin*)ih->handle);
    iupgtkSetBgColor(inner_parent, r, g, b);
  }

  return 1;
}

static int gtkFrameSetFgColorAttrib(Ihandle* ih, const char* value)
{
  unsigned char r, g, b;
  GtkWidget* label = gtk_frame_get_label_widget((GtkFrame*)ih->handle);
  if (!label) return 0;

  if (!iupStrToRGB(value, &r, &g, &b))
    return 0;

  iupgtkSetFgColor(label, r, g, b);

  return 1;
}

static int gtkFrameSetStandardFontAttrib(Ihandle* ih, const char* value)
{
  iupdrvSetStandardFontAttrib(ih, value);

  if (ih->handle)
  {
    GtkWidget* label = gtk_frame_get_label_widget((GtkFrame*)ih->handle);
    if (!label) return 1;

#if GTK_CHECK_VERSION(3, 0, 0)
    gtk_widget_override_font((GtkWidget*)label, (PangoFontDescription*)iupgtkGetPangoFontDescAttrib(ih));
#else
    gtk_widget_modify_font((GtkWidget*)label, (PangoFontDescription*)iupgtkGetPangoFontDescAttrib(ih));
#endif

    iupgtkFontUpdatePangoLayout(ih, gtk_label_get_layout((GtkLabel*)label));
  }
  return 1;
}

static void* gtkFrameGetInnerNativeContainerHandleMethod(Ihandle* ih, Ihandle* child)
{
  (void)child;
  return (void*)gtk_bin_get_child((GtkBin*)ih->handle);
}

static int gtkFrameMapMethod(Ihandle* ih)
{
  char *value, *title;
  GtkWidget *inner_parent;

  if (!ih->parent)
    return IUP_ERROR;

  title = iupAttribGet(ih, "TITLE");

  ih->handle = gtk_frame_new(NULL);
  if (!ih->handle)
    return IUP_ERROR;

  if (title)
    iupAttribSetStr(ih, "_IUPFRAME_HAS_TITLE", "1");
  else
  {
    value = iupAttribGetStr(ih, "SUNKEN");
    if (iupStrBoolean(value))
      gtk_frame_set_shadow_type((GtkFrame*)ih->handle, GTK_SHADOW_IN);
    else
      gtk_frame_set_shadow_type((GtkFrame*)ih->handle, GTK_SHADOW_ETCHED_IN);

    if (iupAttribGet(ih, "BGCOLOR"))
      iupAttribSetStr(ih, "_IUPFRAME_HAS_BGCOLOR", "1");
  }

  /* the container that will receive the child element. */
  inner_parent = iupgtkNativeContainerNew(0);
  if (iupAttribGet(ih, "_IUPFRAME_HAS_BGCOLOR"))
    iupgtkNativeContainerSetHasWindow(inner_parent, TRUE);
  gtk_container_add((GtkContainer*)ih->handle, inner_parent);
  gtk_widget_show(inner_parent);

  /* Add to the parent, all GTK controls must call this. */
  iupgtkAddToParent(ih);

  gtk_widget_realize(ih->handle);

  return IUP_NOERROR;
}

void iupdrvFrameInitClass(Iclass* ic)
{
  /* Driver Dependent Class functions */
  ic->Map = gtkFrameMapMethod;
  ic->GetInnerNativeContainerHandle = gtkFrameGetInnerNativeContainerHandleMethod;

  /* Driver Dependent Attribute functions */

  /* Overwrite Common */
  iupClassRegisterAttribute(ic, "STANDARDFONT", NULL, gtkFrameSetStandardFontAttrib, IUPAF_SAMEASSYSTEM, "DEFAULTFONT", IUPAF_NO_SAVE|IUPAF_NOT_MAPPED);

  /* Visual */
  iupClassRegisterAttribute(ic, "BGCOLOR", NULL, gtkFrameSetBgColorAttrib, IUPAF_SAMEASSYSTEM, "DLGBGCOLOR", IUPAF_DEFAULT);

  /* Special */
  iupClassRegisterAttribute(ic, "FGCOLOR", NULL, gtkFrameSetFgColorAttrib, IUPAF_SAMEASSYSTEM, "DLGFGCOLOR", IUPAF_DEFAULT);
  iupClassRegisterAttribute(ic, "TITLE", gtkFrameGetTitleAttrib, gtkFrameSetTitleAttrib, NULL, NULL, IUPAF_NO_DEFAULTVALUE|IUPAF_NO_INHERIT);
}
