--TEST--
Test for rdp_simplify
--FILE--
<?php
$contents = file_get_contents(__DIR__ . '/geojson-belgium.json');
$data = json_decode($contents);

$points = $data[0]->geometry->coordinates[0];

$result1 = rdp_simplify($points, 0.001);
$result2 = rdp_simplify($points, 0.01);

var_dump(count($points), count($result1), count($result2));

?>
--EXPECT--
int(1146)
int(1029)
int(261)
