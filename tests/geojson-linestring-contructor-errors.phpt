--TEST--
Test for LineString constructor errors
--FILE--
<?php
$tests = [
	[],
	[ [ 0, 52.5 ] ],
	// [ [ 0, 52.5 ], [ 7.1, 59.6 ] ], correct
	[ [ 52.5 ], [ 7.1, 59.6 ] ],
	[ [ 0, "52.5" ], [ 7.1, 59.6 ] ],
	[ [ 0, 52.5 ], [ "7.1", 59.6 ] ],
	[ [ false, 52.5 ], [ 7.1, 59.6 ] ],
	[ [ 0, 52.5 ], [ new stdClass, 59.6 ] ],
	
	[ [ -190, 52.5 ], [ 7.1, 59.6 ] ],
	[ [ +190, 52.5 ], [ 7.1, 59.6 ] ],
	[ [ 0, 52.5 ], [ 7.1, -99.6 ] ],
	[ [ 0, 52.5 ], [ 7.1, +99.6 ] ],
];

foreach ($tests as $test) {
	try {
		$ls = new Geospatial\GeoJSON\LineString($test);
	} catch (ValueError $e) {
		echo get_class($e), ': ', $e->getMessage(), "\n";
	}
}

?>
--EXPECTF--
ValueError: Geospatial\GeoJSON\LineString::__construct(): Argument #1 ($points) must have at least two elements
ValueError: Geospatial\GeoJSON\LineString::__construct(): Argument #1 ($points) must have at least two elements
ValueError: Geospatial\GeoJSON\LineString::__construct(): Argument #1 ($points) array element #0 does not contain a two element coordinate pair
ValueError: Geospatial\GeoJSON\LineString::__construct(): Argument #1 ($points) array element #0 does not contain a two element coordinate pair
ValueError: Geospatial\GeoJSON\LineString::__construct(): Argument #1 ($points) array element #1 does not contain a two element coordinate pair
ValueError: Geospatial\GeoJSON\LineString::__construct(): Argument #1 ($points) array element #0 does not contain a two element coordinate pair
ValueError: Geospatial\GeoJSON\LineString::__construct(): Argument #1 ($points) array element #1 does not contain a two element coordinate pair
ValueError: Geospatial\GeoJSON\LineString::__construct(): Argument #1 ($points) array element #0 longitude (-190) is out of range [-180, 180]
ValueError: Geospatial\GeoJSON\LineString::__construct(): Argument #1 ($points) array element #0 longitude (190) is out of range [-180, 180]
ValueError: Geospatial\GeoJSON\LineString::__construct(): Argument #1 ($points) array element #1 latitude (-99.600000) is out of range [-90, 90]
ValueError: Geospatial\GeoJSON\LineString::__construct(): Argument #1 ($points) array element #1 latitude (99.600000) is out of range [-90, 90]
