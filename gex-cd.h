#ifndef __GEX_CD_H__
#define __GEX_CD_H__

#include "gex-media.h"

G_BEGIN_DECLS

G_DECLARE_FINAL_TYPE(GexCD, gex_cd, GEX, CD, GexMedia)

#define GEX_TYPE_CD (gex_cd_get_type())

GexCD *gex_cd_new();

gboolean gex_cd_get_writable(GexCD *self);

G_END_DECLS

#endif /* __GEX_CD_H__ */
