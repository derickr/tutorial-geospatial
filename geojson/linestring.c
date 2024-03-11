#include "php.h"

#include "php_geospatial.h"
#include "geospatial_arginfo.h"

ZEND_METHOD(Geospatial_GeoJSON_LineString, __construct)
{
	zval *points;

	ZEND_PARSE_PARAMETERS_START(1,1)
		Z_PARAM_ARRAY(points)
	ZEND_PARSE_PARAMETERS_END();

	zend_update_property(Z_OBJCE_P(ZEND_THIS), Z_OBJ_P(ZEND_THIS), "points", strlen("points"), points);
}
