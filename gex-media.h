#ifndef __GEX_MEDIA_H__
#define __GEX_MEDIA_H__

#include "glib-object.h"

G_BEGIN_DECLS

G_DECLARE_DERIVABLE_TYPE(GexMedia, gex_media, GEX, MEDIA, GObject)

typedef struct _GexMediaClass
{
  GObjectClass parent_class;

  void (*unpacked) (GexMedia *media);
  void (*throw_out) (GexMedia *media, gboolean permanent);
} GexMediaClass;

#define GEX_TYPE_MEDIA (gex_media_get_type())

GexMedia *gex_media_new();

guint media_get_inv_nr(GexMedia *self);

G_END_DECLS

#endif /* __GEX_MEDIA_H__ */
