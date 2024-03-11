/* geospatial extension for PHP (c) 2024 Derick Rethans */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_geospatial.h"
#include "geospatial_arginfo.h"


/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION(geospatial)
{
#if defined(ZTS) && defined(COMPILE_DL_GEOSPATIAL)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(geospatial)
{
	php_info_print_table_start();
	php_info_print_table_row(2, "geospatial support", "enabled");
	php_info_print_table_row(2, "geospatial version", PHP_GEOSPATIAL_VERSION);
	php_info_print_table_end();
}
/* }}} */

/* {{{ geospatial_module_entry */
zend_module_entry geospatial_module_entry = {
	STANDARD_MODULE_HEADER,
	"geospatial",					/* Extension name */
	ext_functions,					/* zend_function_entry */
	NULL,							/* PHP_MINIT - Module initialization */
	NULL,							/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(geospatial),			/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(geospatial),			/* PHP_MINFO - Module info */
	PHP_GEOSPATIAL_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_GEOSPATIAL
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(geospatial)
#endif
