
let guiHandler, imageLoader, programMode, 
	roadRunnerGenerator, imageIndex;

const ProgramMode = {
	JSON_Mode:       0,
	User_Input_Mode: 1
};

function preload() {

	imageIndex = IMAGE_INDEX
	imageLoader = new ImageHandler();
	imageLoader.loadImages( imageIndex );
}

function setup() {

	angleMode(DEGREES);

	programMode = ProgramMode.User_Input_Mode; // to switch the mode
	guiHandler = new LoopHandler( imageLoader.getImages() );

	roadRunnerGenerator = new RoadRunnerGenerator();
	guiHandler.setMode( programMode );


		createCanvas(
			CANVAS_WIDTH,
			CANVAS_HEIGHT
		);
}

function draw() {
	guiHandler.loop();
}

function mousePressed() {

	if ( guiHandler.mode == LOOP_USER_INPUT )
		guiHandler.inputHandler.controlMouse(
			guiHandler.inputMode
		);
}

function keyTyped() {
	if ( flowerGenerator != null )
		flowerGenerator.pause = !flowerGenerator.pause;
}

function readTextFile(file, callback) {

	let rawFile = new XMLHttpRequest();
	
	rawFile.overrideMimeType("application/json");
	rawFile.open("GET", file, true);

	rawFile.onreadystatechange = 
		() => {
		  if (rawFile.readyState === 4 && rawFile.status == "200")
		      callback(rawFile.responseText);
		}

    rawFile.send(null);
}



function filterImagesUsingJson(jsonData) {

	// filter the images with the given images indexes

	let data = [];

	for (let counter = 0; counter < imagesIndexes.length; counter++ )
		data.push( jsonData[ imagesIndexes[ counter ] ] );	

	return data;
}
