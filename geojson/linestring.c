#include "php.h"

#include "php_geospatial.h"
#include "geospatial_arginfo.h"

#include "../lib/rdp.h"

extern zend_class_entry *geospatial_geojson_linestring_ce;

static bool valid_linestring(int argument_nr, zval *points)
{
	HashTable *ht = HASH_OF(points);
	zval *element, *longitude, *latitude;
	size_t element_num = 0;

	if (zend_hash_num_elements(ht) < 2) {
		zend_argument_value_error(argument_nr, "must have at least two elements");
		return false;
	}

	ZEND_HASH_FOREACH_VAL(ht, element) {
		if (Z_TYPE_P(element) != IS_ARRAY) {
			zend_argument_value_error(argument_nr, "array element #%zd is not an array", element_num);
			return false;
		}

		if (zend_hash_num_elements(HASH_OF(element)) != 2) {
			zend_argument_value_error(argument_nr, "array element #%zd does not contain a two element coordinate pair", element_num);
			return false;
		}

		longitude = zend_hash_index_find(HASH_OF(element), 0);
		if (!longitude || (Z_TYPE_P(longitude) != IS_LONG && Z_TYPE_P(longitude) != IS_DOUBLE)) {
			zend_argument_value_error(argument_nr, "array element #%zd does not contain a two element coordinate pair", element_num);
			return false;
		}
		if (Z_TYPE_P(longitude) == IS_LONG && (Z_LVAL_P(longitude) < -180 || Z_LVAL_P(longitude) > 180)) {
			zend_argument_value_error(argument_nr, "array element #%zd longitude (%ld) is out of range [-180, 180]", element_num, Z_LVAL_P(longitude));
			return false;
		}
		if (Z_TYPE_P(longitude) == IS_DOUBLE && (Z_DVAL_P(longitude) < -180 || Z_DVAL_P(longitude) > 180)) {
			zend_argument_value_error(argument_nr, "array element #%zd longitude (%f) is out of range [-180, 180]", element_num, Z_DVAL_P(longitude));
			return false;
		}


		latitude = zend_hash_index_find(HASH_OF(element), 1);
		if (!latitude || (Z_TYPE_P(latitude) != IS_LONG && Z_TYPE_P(latitude) != IS_DOUBLE)) {
			zend_argument_value_error(argument_nr, "array element #%zd does not contain a two element coordinate pair", element_num);
			return false;
		}
		if (Z_TYPE_P(latitude) == IS_LONG && (Z_LVAL_P(latitude) < -90 || Z_LVAL_P(latitude) > 90)) {
			zend_argument_value_error(argument_nr, "array element #%zd latitude (%ld) is out of range [-90, 90]", element_num, Z_LVAL_P(latitude));
			return false;
		}
		if (Z_TYPE_P(latitude) == IS_DOUBLE && (Z_DVAL_P(latitude) < -90 || Z_DVAL_P(latitude) > 90)) {
			zend_argument_value_error(argument_nr, "array element #%zd latitude (%f) is out of range [-90, 90]", element_num, Z_DVAL_P(latitude));
			return false;
		}

		++element_num;
	} ZEND_HASH_FOREACH_END();

	return true;
}

ZEND_METHOD(Geospatial_GeoJSON_LineString, __construct)
{
	zval *points;

	ZEND_PARSE_PARAMETERS_START(1,1)
		Z_PARAM_ARRAY(points)
	ZEND_PARSE_PARAMETERS_END();

	if (!valid_linestring(1, points)) {
		RETURN_THROWS();
	}

	zend_update_property(Z_OBJCE_P(ZEND_THIS), Z_OBJ_P(ZEND_THIS), "points", strlen("points"), points);
}

ZEND_METHOD(Geospatial_GeoJSON_LineString, getCoordinates)
{
	ZEND_PARSE_PARAMETERS_NONE();

	RETURN_ZVAL(
		zend_read_property(Z_OBJCE_P(ZEND_THIS), Z_OBJ_P(ZEND_THIS), "points", strlen("points"), false, NULL),
		true,
		false
	);
}

ZEND_METHOD(Geospatial_GeoJSON_LineString, simplify)
{
	double epsilon;
	geo_array *points;
	zval simplified_points;
	int i;

	ZEND_PARSE_PARAMETERS_START(1,1)
		Z_PARAM_DOUBLE(epsilon)
	ZEND_PARSE_PARAMETERS_END();

	/* Prepare return value */
	array_init(&simplified_points);

	/* Convert PHP variables into algorithm data structures */
	points = geo_hashtable_to_array(
		zend_read_property(Z_OBJCE_P(ZEND_THIS), Z_OBJ_P(ZEND_THIS), "points", strlen("points"), false, NULL)
	);
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

		add_next_index_zval(&simplified_points, &pair);
	}

	/* Clean Up */
	geo_array_dtor(points);

	/* Return values in new object */
	object_init_ex(return_value, geospatial_geojson_linestring_ce);
	zend_update_property(Z_OBJCE_P(return_value), Z_OBJ_P(return_value), "points", strlen("points"), &simplified_points);
	zval_ptr_dtor(&simplified_points);
}

