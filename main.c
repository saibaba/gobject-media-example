#include "gex-media.h"

#include <glib.h>
#include <locale.h>

typedef struct {
} GexMediaFixture;


static void
gex_media_fixture_set_up (GexMediaFixture *fixture,
                            gconstpointer user_data)
{
}

static void
gex_media_fixture_tear_down (GexMediaFixture *fixture,
                               gconstpointer user_data)
{
}

static void test_new(GexMediaFixture *fixture,
                     gconstpointer user_data)
{
  GexMedia *m = gex_media_new();
  g_assert_nonnull(m);

  g_object_unref(m);
}

static void test_dflt_inv_nr(GexMediaFixture *fixture,
                             gconstpointer user_data)
{
  GexMedia *m = gex_media_new();
  g_assert(media_get_inv_nr(m) == 101);
  g_object_unref(m);
}

static void test_inv_nr_property(GexMediaFixture *fixture,
                                 gconstpointer user_data)
{
  GexMedia *m = gex_media_new();
  guint nr;

  g_object_set(m, "inventory-id", 37, NULL);
  g_object_get(m, "inventory_id", &nr, NULL);

  g_assert(nr == 37); 
  g_object_unref(m);
}

static void test_dflt_orig_package(GexMediaFixture *fixture,
                                   gconstpointer user_data)
{
  GexMedia *m = gex_media_new();
  gboolean orig_package;

  g_object_get(m, "orig-package", &orig_package, NULL);
  g_assert(orig_package);
  g_object_unref(m);
}

static void test_orig_package_property(GexMediaFixture *fixture,
                                 gconstpointer user_data)
{
  GexMedia *m = gex_media_new();
  gboolean orig_package;

  g_object_set(m, "orig-package", FALSE, NULL);
  g_object_get(m, "orig-package", &orig_package, NULL);

  g_assert(orig_package == FALSE); 
  g_object_unref(m);
}

static void test_throw_out_signals(GexMediaFixture *fixture,
                         gconstpointer user_data)
{
  GexMedia *m = gex_media_new();
  gboolean return_value;
  g_signal_emit_by_name(m, "throw-out", FALSE, &return_value);
  g_object_unref(m);
}

static void test_unpacked_signals(GexMediaFixture *fixture,
                         gconstpointer user_data)
{
  GexMedia *m = gex_media_new();
  gboolean return_value;

  gboolean orig_package;
  g_object_get(m, "orig-package", &orig_package, NULL);
  g_assert(orig_package);

  g_signal_emit_by_name(m, "unpacked", &return_value);
  g_object_get(m, "orig-package", &orig_package, NULL);
  g_assert(!orig_package);
  g_object_unref(m);
}

int main(int argc, char **argv) {

  setlocale (LC_ALL, "");

  g_test_init (&argc, &argv, NULL);

  g_test_add("/media/test_new", GexMediaFixture, "some-user-data",  gex_media_fixture_set_up, test_new, gex_media_fixture_tear_down);
  g_test_add("/media/test_dflt_inv_nr", GexMediaFixture, "some-user-data",  gex_media_fixture_set_up, test_dflt_inv_nr, gex_media_fixture_tear_down);
  g_test_add("/media/test_inv_nr_property", GexMediaFixture, "some-user-data",  gex_media_fixture_set_up, test_inv_nr_property, gex_media_fixture_tear_down);
  g_test_add("/media/test_dflt_orig_package", GexMediaFixture, "some-user-data",  gex_media_fixture_set_up, test_dflt_orig_package, gex_media_fixture_tear_down);
  g_test_add("/media/test_orig_package_property", GexMediaFixture, "some-user-data",  gex_media_fixture_set_up, test_orig_package_property, gex_media_fixture_tear_down);
  g_test_add("/media/test_throw_out_signals", GexMediaFixture, "some-user-data",  gex_media_fixture_set_up, test_throw_out_signals, gex_media_fixture_tear_down);
  g_test_add("/media/test_unpacked_signals", GexMediaFixture, "some-user-data",  gex_media_fixture_set_up, test_unpacked_signals, gex_media_fixture_tear_down);
  return g_test_run();
}
