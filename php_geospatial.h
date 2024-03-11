/* geospatial extension for PHP (c) 2024 Derick Rethans */

#ifndef PHP_GEOSPATIAL_H
# define PHP_GEOSPATIAL_H

extern zend_module_entry geospatial_module_entry;
# define phpext_geospatial_ptr &geospatial_module_entry

# define PHP_GEOSPATIAL_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_GEOSPATIAL)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#include "lib/geo_array.h"
geo_array *geo_hashtable_to_array(zval *array);


#endif	/* PHP_GEOSPATIAL_H */
