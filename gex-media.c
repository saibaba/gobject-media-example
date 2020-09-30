#include "gex-media.h"

// create private structure to store instance variables

// G_DECLARE_DERIVABLE_TYPE(GexMedia, gex_media, GEX, MEDIA, GObject)

typedef struct _GexMediaPrivate
{
  GObject parent_instance;
  gboolean orig_package;
  guint inv_nr;
} GexMediaPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(GexMedia, gex_media, G_TYPE_OBJECT)

enum {
  PROP_MEDIA_0,
  PROP_INV_NR,
  PROP_ORIG_PACKAGE
};

enum {
  UNPACKED,
  THROW_OUT,
  LAST_SIGNAL
};

static guint media_signal[LAST_SIGNAL] = { 0, 0 };

GexMedia *gex_media_new()
{
  return GEX_MEDIA(g_object_new(GEX_TYPE_MEDIA, 0));
}

guint media_get_inv_nr(GexMedia *self)
{
  GexMedia *media;

  g_return_val_if_fail(GEX_IS_MEDIA(self), 0);

  media = GEX_MEDIA(self);
 
  GexMediaPrivate *priv = gex_media_get_instance_private(self);

  return priv->inv_nr;
}

static void gex_media_set_property(GObject *self, guint prop_id, const GValue *value, GParamSpec *pspec)
{
  guint new_inv_nr;
  gboolean new_orig_package;
  GexMedia *media = GEX_MEDIA(self);
  GexMediaPrivate *priv = gex_media_get_instance_private(media);
  switch(prop_id) 
  {
    case PROP_INV_NR:
      new_inv_nr = g_value_get_uint(value);
      if (priv->inv_nr != new_inv_nr)
      {
        priv->inv_nr = new_inv_nr;
      }
      break;
    case PROP_ORIG_PACKAGE:
      new_orig_package = g_value_get_boolean(value);
      if (priv->orig_package != new_orig_package)
      {
        priv->orig_package = new_orig_package;
      }
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(self, prop_id, pspec);
  }
}

static void gex_media_get_property(GObject *self, guint prop_id, GValue *value, GParamSpec *pspec)
{
  GexMedia *media = GEX_MEDIA(self);
  GexMediaPrivate *priv = gex_media_get_instance_private(media);
  switch(prop_id) 
  {
    case PROP_INV_NR:
      g_value_set_uint(value, priv->inv_nr);
      break;
    case PROP_ORIG_PACKAGE:
      g_value_set_boolean(value, priv->orig_package);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(self, prop_id, pspec);
  }
}

static void gex_media_unpacked(GexMedia *self)
{
  GexMediaPrivate *priv = gex_media_get_instance_private(self);
  if (priv->orig_package) 
  {
    g_object_set(self, "orig-package", FALSE, NULL);
    g_print("Media Unpacked.\n");
  }
  else
  {
    g_print("media already unpacked\n");
  }
}

static void gex_media_throw_out(GexMedia *self, gboolean permanent)
{
  if (permanent)
  {
    g_print("Trashing media.\n");
  }
  else
  {
    g_print("media not in the dumpster quite yet.\n");
  }
}

static void gex_media_class_init(GexMediaClass *klass)
{

  GParamSpec *inv_nr_param, *orig_package_param;
  
  inv_nr_param = g_param_spec_uint("inventory-id", "inventory number", "number on inventory label", 0, UINT_MAX, 0, G_PARAM_READWRITE);
  orig_package_param = g_param_spec_boolean("orig-package", "original package?", "is item in its original package?", FALSE, G_PARAM_READWRITE);
 
  GObjectClass *g_object_class = G_OBJECT_CLASS(klass);

  // override base object methods
  g_object_class->set_property = gex_media_set_property;
  g_object_class->get_property = gex_media_get_property;

  g_object_class_install_property(g_object_class, PROP_INV_NR, inv_nr_param);
  g_object_class_install_property(g_object_class, PROP_ORIG_PACKAGE, orig_package_param);

  klass->unpacked = gex_media_unpacked;
  klass->throw_out = gex_media_throw_out;

  media_signal[UNPACKED]  = g_signal_new("unpacked", GEX_TYPE_MEDIA, G_SIGNAL_RUN_LAST | G_SIGNAL_DETAILED, G_STRUCT_OFFSET(GexMediaClass, unpacked), NULL, NULL, g_cclosure_marshal_VOID__VOID, G_TYPE_NONE, 0);
  media_signal[THROW_OUT]  = g_signal_new("throw_out", GEX_TYPE_MEDIA, G_SIGNAL_RUN_LAST | G_SIGNAL_DETAILED, G_STRUCT_OFFSET(GexMediaClass, throw_out), NULL, NULL, g_cclosure_marshal_VOID__BOOLEAN, G_TYPE_NONE, 1, G_TYPE_BOOLEAN);

  g_print("gex_media_class_init called\n");
}

static void gex_media_init(GexMedia *self)
{
  GexMediaPrivate *priv = gex_media_get_instance_private(self);
  priv->inv_nr = 101;
  priv->orig_package = TRUE;
  g_print("gex_media_init called\n");
}
