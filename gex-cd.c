#include "gex-cd.h"
#include "gex-cleanable.h"

typedef struct _GexCD
{
  GexMedia parent_instance;
  gboolean writable;
} GexCD;


static void gex_cd_cleanable_init(gpointer interface, gpointer data);

G_DEFINE_TYPE_WITH_CODE(GexCD, gex_cd, GEX_TYPE_MEDIA, G_IMPLEMENT_INTERFACE(GEX_TYPE_CLEANABLE, gex_cd_cleanable_init))

static void gex_cd_clean(GexCleanable *cleanable)
{
  GEX_IS_CD(GEX_CD(cleanable));
  g_print("Cleaning CD.\n");
}

static void gex_cd_cleanable_init(gpointer interface, gpointer data)
{
  GexCleanableInterface *cleanable = interface;
  g_assert(G_TYPE_FROM_INTERFACE(cleanable) == GEX_TYPE_CLEANABLE);

  // g_assert(cleanable_base_init_count > 0);

  cleanable->clean = gex_cd_clean;
}


GexCD *gex_cd_new()
{
  return GEX_CD(g_object_new(GEX_TYPE_CD, 0));
}

gboolean gex_cd_get_writable(GexCD *self)
{
  GexCD *cd;

  g_return_val_if_fail(GEX_IS_CD(self), 0);

  cd = GEX_CD(self);
 
  return cd->writable;
}

static void unpacked_cd()
{
  g_print("Hi!\n");
}

static void gex_cd_class_init(GexCDClass *klass)
{

  // GObjectClass *g_object_class;
  GexMediaClass *media_class;
  media_class = GEX_MEDIA_CLASS(klass);
  media_class->unpacked = unpacked_cd;

  g_print("gex_cd_class_init called\n");
}

static void gex_cd_init(GexCD *self)
{
  self->writable = FALSE;
  g_print("gex_cd_init called\n");
}
