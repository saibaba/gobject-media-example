#include "gex-cleanable.h"

static guint cleanable_base_init_count = 0;

static void gex_cleanable_default_init(GexCleanableInterface *klass)
{
  cleanable_base_init_count++;
  if (cleanable_base_init_count == 1)
  {
    g_print("cleanable_base_init_count = 1\n");
  }
  g_print("gex_cleanable_base_init\n");
}

/*
static void gex_cleanable_base_finalize(GexCleanableInterface *cleanable_class)
{
  cleanable_base_init_count--;
  if (cleanable_base_init_count == 0)
  {
    g_print("cleanable_base_init_count = 0\n");
  }
  g_print("gex_cleanable_base_finalize\n");
}
*/

G_DEFINE_INTERFACE(GexCleanable, gex_cleanable, G_TYPE_OBJECT);

void gex_cleanable_clean(GexCleanable *self)
{
  GexCleanableInterface *iface = GEX_CLEANABLE_GET_IFACE(self);
  
  g_return_if_fail(iface->clean != NULL);
  
  iface->clean(self);
}

// G_DEFINE_INTERFACE(GexCleanable, gex_cleanable, GEX_TYPE_CLEANABLE);
