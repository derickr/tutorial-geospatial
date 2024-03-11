<?php
/**
 * @generate-class-entries
 */

namespace {
function rdp_simplify(array $coordinates, float $epsilon) : array {}
}

namespace Geospatial\GeoJSON {

final class LineString
{
	private readonly array $points;

	public function __construct(array $points) {}

	public function getCoordinates() : array {}
	public function simplify(float $epsilon) : LineString {}
}

}
