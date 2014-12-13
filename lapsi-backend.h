#ifndef LAPSI_BACKEND_H
#define LAPSI_BACKEND_H
#include <string.h>
#include <gtk/gtk.h>
#include <gst/gst.h>
#include <gdk/gdk.h>
#include <gdk/gdkx.h>
#include <gst/video/videooverlay.h>

typedef struct _CustomData {
  GstElement *playbin;           /* Our one and only pipeline */

  GtkWidget *slider;              /* Slider widget to keep track of current position */
  GtkWidget *streams_list;        /* Text widget to display info about the streams */
  gulong slider_update_signal_id; /* Signal ID for the slider update signal */

  GstState state;                 /* Current state of the pipeline */
  gint64 duration;                /* Duration of the clip, in nanoseconds */
} CustomData;

static void
  realize_cb (GtkWidget *, CustomData *);


static void
  play_cb (GtkButton *, CustomData *);

static void
  pause_cb (GtkButton *, CustomData *);

static void
  stop_cb (GtkButton *, CustomData *);

static void
  delete_event_cb (GtkWidget *, GdkEvent *, CustomData *);

static gboolean
  draw_cb (GtkWidget *, GdkEventExpose *, CustomData *);

static void
  slider_cb (GtkRange *, CustomData *);

static void
  create_ui (CustomData *);

static gboolean
  refresh_ui (CustomData *);

static void
  tags_cb (GstElement *, gint , CustomData *);

static void
  error_cb (GstBus *, GstMessage *, CustomData *);

static void
  eos_cb (GstBus *, GstMessage *, CustomData *);

static void
  state_changed_cb (GstBus *, GstMessage *, CustomData *);

static void
  analyze_streams(CustomData *);

static GstBusSyncReply
  busSyncHandler (GstBus *, GstMessage *, gpointer);
extern int
  play_file(CustomData *);
extern int
  lapsi_backend_init(CustomData *,int * ,char***);

#endif /*lapsi-backend*/
