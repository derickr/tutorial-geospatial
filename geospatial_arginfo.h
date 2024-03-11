/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 6ca63a11b62e12c7337361d21d2be465502e273e */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_rdp_simplify, 0, 2, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, coordinates, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, epsilon, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Geospatial_GeoJSON_LineString___construct, 0, 0, 1)
	ZEND_ARG_TYPE_INFO(0, points, IS_ARRAY, 0)
ZEND_END_ARG_INFO()


ZEND_FUNCTION(rdp_simplify);
ZEND_METHOD(Geospatial_GeoJSON_LineString, __construct);


static const zend_function_entry ext_functions[] = {
	ZEND_FE(rdp_simplify, arginfo_rdp_simplify)
	ZEND_FE_END
};


static const zend_function_entry class_Geospatial_GeoJSON_LineString_methods[] = {
	ZEND_ME(Geospatial_GeoJSON_LineString, __construct, arginfo_class_Geospatial_GeoJSON_LineString___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_Geospatial_GeoJSON_LineString(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Geospatial\\GeoJSON", "LineString", class_Geospatial_GeoJSON_LineString_methods);
	class_entry = zend_register_internal_class_ex(&ce, NULL);
	class_entry->ce_flags |= ZEND_ACC_FINAL;

	zval property_points_default_value;
	ZVAL_UNDEF(&property_points_default_value);
	zend_string *property_points_name = zend_string_init("points", sizeof("points") - 1, 1);
	zend_declare_typed_property(class_entry, property_points_name, &property_points_default_value, ZEND_ACC_PRIVATE|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_ARRAY));
	zend_string_release(property_points_name);

	return class_entry;
}
