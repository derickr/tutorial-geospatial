dnl config.m4 for extension geospatial

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary.

dnl If your extension references something external, use 'with':

PHP_ARG_ENABLE([geospatial],
  [whether to enable geospatial support],
  [AS_HELP_STRING([--enable-geospatial],
    [Enable geospatial support])],
  [no])

if test "$PHP_GEOSPATIAL" != "no"; then
  AC_DEFINE(HAVE_GEOSPATIAL, 1, [ Have geospatial support ])

  PHP_NEW_EXTENSION(geospatial, geospatial.c lib/rdp.c lib/geo_array.c, $ext_shared)
fi
