--TEST--
Test for LineString::getCoordinates()
--FILE--
<?php
$ls = new \Geospatial\GeoJSON\LineString(
	[
		[   0, 52.5 ],
		[ 7.2, 60.3 ]
	]
);
var_dump($ls->getCoordinates());
?>
--EXPECT--
array(2) {
  [0]=>
  array(2) {
    [0]=>
    int(0)
    [1]=>
    float(52.5)
  }
  [1]=>
  array(2) {
    [0]=>
    float(7.2)
    [1]=>
    float(60.3)
  }
}
