class RoadRunnerGenerator {

	constructor( inputSchemas, data ) {

		this.drawingMode = true;	
		this.images = [];

		this.info = this.shapeData = null; 
		this.pause = this.ready = false;
		this.newRoadRunner = new RoadRunner();

	}

	setData( data ) {

		this.info = data;

		let shape = [];

		for ( let counter = 0; counter < this.imageAnalyzer.data.length; counter++ ) {
			shape.push( 
				this.getPetalDistancesPerZone( this.imageAnalyzer.data[ counter ].petalZones ) 
			);
		}

		this.shapeGen = 
			new ShapeGenerator( 
				this.imageAnalyzer.info, 
				shape  
			);

		this.pistilGen = 
			new PistilGenerator( 
				{
					centerRadius : this.imageAnalyzer.info.centerRadius,
					centerColors: [] 
				} 
			);

		this.stemGen = 
			new StemGenerator(
				{
					widthCoordinates: this.getWidthCoordinates(),
					stemWidth: this.getStemAverageWidth()
				}
			);

		// this.colorGen =
		// 	new GeneticColorProcessor(
		// 		this.imageAnalyzer.getBestColorPerZone(),
		// 		this.imageAnalyzer.info.petalHeight
		// 	);

		this.distributionTable = new DistributionTable();

		let flatColors = this.imageAnalyzer.getBestColorPerZone();

		this.chromosomaticTable = 
			this.distributionTable.generateTable( 
				flatColors
			);

		this.ready = true;
		this.pause = true;
	}

	getWidthCoordinates() {

		let centerPoint = this.imageAnalyzer.info.centerPoint;
		let radius      = this.imageAnalyzer.info.centerRadius;

		let leftCoordinate  = [ centerPoint[X] - int(radius/2), centerPoint[Y] ];
		let rightCoordinate = [ centerPoint[X] + int(radius/2), centerPoint[Y] ];

		return [ leftCoordinate, rightCoordinate ];
	}

	getStemAverageWidth() {

		return this.imageAnalyzer.info.centerRadius;
	}

	getCenterRadius(topPoint, bottonPoint){
		
		// the center radius, with precondition that the given points is over the other
		return abs(topPoint[Y] - bottonPoint[Y]) / 2;
	}

	getMiddlePointOfCenter(topPoint, bottonPoint){

		let middlePointCenter = [];

		middlePointCenter.push( topPoint[X] );
		middlePointCenter.push( abs( topPoint[Y] - bottonPoint[Y] ) );

		return middlePointCenter;
	}

	getPetalAmount(zonePoints, middlePointCenter) {

		let middlePointZone = zonePoints[ zonePoints.length / 2 ];

		let width = 2 * ( abs( middlePointZone[X] - middlePointCenter[X] ) );
		let petalBase = (zonePoints[1][X] - middlePointCenter[X]) * 2;
		
		let circunference = 
			2 * PI * ( 
				abs(middlePointCenter[Y] - middlePointZone[Y])
			);

		return int( circunference / petalBase ) ;
	}

	getPetalHeight( zonePointsPerPetal ) {

		let yInitialPoint = zonePointsPerPetal[ 0 ][ Y ];
		let yFinalPoint   = zonePointsPerPetal[ MAX_POINTS_ZONES - 1 ][ Y ];

		let height = abs( yFinalPoint - yInitialPoint );

		return height;
	}

	getPetalDistancesPerZone( zonePoints ) {

		let zoneDistances = [];

		for ( let zoneCounter = 0; zoneCounter < zonePoints.length; zoneCounter++ )  {

			let currentDistance = ( zonePoints[ zoneCounter ][X] - zonePoints[0][X] );
			zoneDistances.push( currentDistance > 0 ? int(currentDistance) : 0  );
		}
		
		return zoneDistances;
	}

	normalizeData( zonePoints ) {

		let normalizedData = [];

		// X value to normalize
		for ( let zoneCounter = 0; zoneCounter < zonePoints.length; zoneCounter++ ) {

			let xValue = zonePoints[zoneCounter][ 0 ][ X ];
			let yValue = zonePoints[zoneCounter][ zonePoints.length - 1 ][ Y ];

			let normalizedZone = [];

			let currentZone = zonePoints[zoneCounter];

			for (let pointCounter = 0; pointCounter < currentZone.length; pointCounter++) {

				let xPointValue = currentZone[ pointCounter ][ X ] - xValue; 
				let yPointValue = currentZone[ pointCounter ][ Y ] - yValue;

				normalizedZone.push( [ xPointValue, yPointValue ] );
			}

			normalizedData.push( normalizedZone );
		}

		return normalizedData;
	}
}
