--TEST--
Test for LineString::simplify
--FILE--
<?php
$contents = file_get_contents(__DIR__ . '/geojson-belgium.json');
$data = json_decode($contents);

$points = $data[0]->geometry->coordinates[0];

$ls = new Geospatial\GeoJson\LineString($points);

$result1 = $ls->simplify(0.001);
$result2 = $ls->simplify(0.01);

var_dump(get_class($result1), get_class($result2));

var_dump(
	count($points),
	count($result1->getCoordinates()),
	count($result2->getCoordinates())
);

?>
--EXPECT--
string(29) "Geospatial\GeoJSON\LineString"
string(29) "Geospatial\GeoJSON\LineString"
int(1146)
int(1029)
int(261)
