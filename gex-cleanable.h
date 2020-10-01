#ifndef __GEX_CLEANABLE_H__
#define __GEX_CLEANABLE_H__

#include "glib-object.h"

G_BEGIN_DECLS


G_DECLARE_INTERFACE(GexCleanable, gex_cleanable, GEX, CLEANABLE, GObject)

struct _GexCleanableInterface
{
  GTypeInterface g_iface;
  void (* clean) (GexCleanable *self);
};

#define GEX_TYPE_CLEANABLE (gex_cleanable_get_type())

void gex_cleanable_clean(GexCleanable *self);

G_END_DECLS

#endif /* __GEX_CLEANABLE_H__ */
