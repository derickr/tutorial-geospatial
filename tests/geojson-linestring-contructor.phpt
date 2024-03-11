--TEST--
Test for LineString constructor
--FILE--
<?php
$ls = new \Geospatial\GeoJSON\LineString(
	[
		[   0, 52.5 ],
		[ 7.2, 60.3 ]
	]
);
var_dump($ls);
?>
--EXPECTF--
object(Geospatial\GeoJSON\LineString)#%d (1) {
  ["points":"Geospatial\GeoJSON\LineString":private]=>
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
}
