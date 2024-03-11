/* geospatial extension for PHP (c) 2024 Derick Rethans */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_geospatial.h"
#include "lib/geo_array.h"
#include "lib/rdp.h"
#include "geospatial_arginfo.h"

zend_class_entry *geospatial_geojson_linestring_ce;

static void geospatial_register_classes(void)
{
	geospatial_geojson_linestring_ce = register_class_Geospatial_GeoJSON_LineString();
}

PHP_MINIT_FUNCTION(geospatial)
{
	geospatial_register_classes();
}

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
	PHP_MINIT(geospatial),			/* PHP_MINIT - Module initialization */
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

static bool parse_points_pair(zval *coordinates, double *lon, double *lat)
{
	HashTable *coords;
	zval *z_lon, *z_lat;

	if (Z_TYPE_P(coordinates) != IS_ARRAY) {
		zend_argument_value_error(1, "expected an array coordinate pair, but %s given", zend_zval_type_name(coordinates));
		return false;
	}

	coords = HASH_OF(coordinates);

	if (zend_hash_num_elements(coords) != 2) {
		zend_argument_value_error(1, "a coordinate pair must have 2 elements, %d given", zend_hash_num_elements(coords));
		return false;
	}

	if ((z_lon = zend_hash_index_find(coords, 0)) == NULL) {
		zend_argument_value_error(1, "a coordinate pair misses index #0");
		return false;
	}
	if ((z_lat = zend_hash_index_find(coords, 1)) == NULL) {
		zend_argument_value_error(1, "a coordinate pair misses index #1");
		return false;
	}

	convert_to_double_ex(z_lon);
	convert_to_double_ex(z_lat);
	*lon = Z_DVAL_P(z_lon);
	*lat = Z_DVAL_P(z_lat);

	return true;
}

geo_array *geo_hashtable_to_array(zval *array)
{
	geo_array *tmp;
	zval *entry;
	int i = 0;
	double lon, lat;

	tmp = geo_array_ctor(zend_hash_num_elements(Z_ARRVAL_P(array)));

	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(array), entry) {
		if (!parse_points_pair(entry, &lon, &lat)) {
			goto failure;
		}

		tmp->x[i] = lon;
		tmp->y[i] = lat;
		tmp->status[i] = true;

		i++;
	} ZEND_HASH_FOREACH_END();

	return tmp;

failure:
	geo_array_dtor(tmp);
	return NULL;
}

ZEND_FUNCTION(rdp_simplify)
{
	zval *points_array;
	double epsilon;
	geo_array *points;
	int i;

	/* Parse incoming arguments */
	ZEND_PARSE_PARAMETERS_START(2,2)
		Z_PARAM_ARRAY(points_array)
		Z_PARAM_DOUBLE(epsilon)
	ZEND_PARSE_PARAMETERS_END();

	/* Prepare return value */
	array_init(return_value);

	/* Convert PHP variables into algorithm data structures */
	points = geo_hashtable_to_array(points_array);
	if (!points) {
		return;
	}

	/* Run algorithm */
	rdp_simplify(points, epsilon, 0, points->count -1);

	/* Prepare and return result */
	for (i = 0; i < points->count; i++)
	{
		zval pair;

		if (!points->status[i]) {
			continue;
		}

		array_init(&pair);
		add_next_index_double(&pair, points->x[i]);
		add_next_index_double(&pair, points->y[i]);

		add_next_index_zval(return_value, &pair);
	}

	/* Clean Up */
	geo_array_dtor(points);
}
