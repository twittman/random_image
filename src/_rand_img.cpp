#include <Magick++.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <map>
#include <filesystem>
#include "util.hpp"
#include <cxxopts.hpp>

Magick::Image brightNess( Magick::Image& inputImgHR )
{
	double gammaNum = twitls::randgen::randomDouble( 0.50, 1.50 );

	Magick::Image inImgHR;
	inImgHR = inputImgHR;

	inImgHR.level( 0.0, QuantumRange, gammaNum );

	return inImgHR;
}

Magick::Image hueHueHue( Magick::Image& inputImgHR )
{
	double hue_number = twitls::randgen::randomDouble( 0, 200 );

	Magick::Image inImgHR;
	inImgHR = inputImgHR;

	inImgHR.modulate( 100, 100, hue_number );

	return inImgHR;
}

Magick::Image flipFlop( Magick::Image& inputImgHR )
{
	int flipOrFlop = twitls::randgen::randomNumber( 0, 3 );

	Magick::Image inImgHR;
	inImgHR = inputImgHR;

	if ( flipOrFlop == 0 ) {
		inImgHR.flip();
	}
	else if ( flipOrFlop == 1 ) {
		inImgHR.flop();
	}
	else {

	}
	return inImgHR;
}

Magick::Image rotateOrNotToRotate( Magick::Image& inputImgHR )
{
	int rotateMaybe = twitls::randgen::randomNumber( 0, 2 );

	Magick::Image inImgHR;
	inImgHR = inputImgHR;

	if ( rotateMaybe == 0 ) {
		inImgHR.rotate( 90 );
	}
	else if ( rotateMaybe == 1 ) {
		inImgHR.rotate( 180 );
	}
	else {

	}
	return inImgHR;
}

Magick::Image invertOrNot( Magick::Image& inputImgHR )
{
	int inversion = twitls::randgen::randomNumber( 0, 5 );

	Magick::Image inImgHR;
	inImgHR = inputImgHR;

	if ( inversion == 0 ) {
		inImgHR.negate();
	}
	else {

	}
	return inImgHR;
}

Magick::Image sharpening( Magick::Image& inputImgHR )
{
	int sharpMaybe = twitls::randgen::randomNumber( 0, 9 );

	Magick::Image inImgHR;
	inImgHR = inputImgHR;

	if ( sharpMaybe == 0 ) {
		inImgHR.adaptiveSharpen( 0, 0.62 );
	}
	else if ( sharpMaybe == 1 ) {
		inImgHR.adaptiveSharpen( 0, 1.2 );
	}
	else {

	}
	return inImgHR;
}

Magick::Image nonLinearStretch( Magick::Image& inputImgHR, size_t& width, size_t& height )
{
	int stretchMaybe = twitls::randgen::randomNumber( 0, 4 );
	double stretchWidth_one = twitls::randgen::randomDouble( 2.0, 4.0 );
	double stretchWidth_two = twitls::randgen::randomDouble( 0.1, 2.1 );

	double stretchHeight_one = twitls::randgen::randomDouble( 2.0, 4.0 );
	double stretchHeight_two = twitls::randgen::randomDouble( 0.1, 2.1 );

	int w = twitls::randgen::randomNumber( width / stretchWidth_one, width * stretchWidth_two );
	int h = twitls::randgen::randomNumber( height / stretchHeight_one, height * stretchHeight_two );

	std::string geoSize = std::to_string( w ) + "x" + std::to_string( h );
	std::string oriSize = std::to_string( width ) + "x" + std::to_string( height );

	Magick::Image inImgHR;
	inImgHR = inputImgHR;

	if ( stretchMaybe == 1 ) {
		inImgHR.liquidRescale( Magick::Geometry( geoSize ) );
		inImgHR.liquidRescale( Magick::Geometry( oriSize ) );
	}
	return inImgHR;
}

Magick::Image localCont( Magick::Image& inputImgHR )
{
	int contMaybe = twitls::randgen::randomNumber( 0, 7 );
	double radii = twitls::randgen::randomDouble( 3.0, 30.0 );
	double strength = twitls::randgen::randomDouble( 40.00, 150.00 );

	Magick::Image inImgHR;
	inImgHR = inputImgHR;

	if ( contMaybe == 0 ) {
		inImgHR.localContrast( radii, strength );
	}
	else if ( contMaybe == 1 ) {
		inImgHR.localContrast( 0, 0 );
	}
	else {
		inImgHR.localContrast( 0, 0 );
	}
	return inImgHR;
}

void runProc(std::string& inFile, std::string& outFile)
{
	try {

		Magick::Image image;

		image.read( inFile );
		image.alpha( false );

		auto width = image.baseRows();
		auto height = image.baseColumns();

		image = brightNess( image );
		image = hueHueHue( image );
		image = flipFlop( image );
		image = rotateOrNotToRotate( image );
		image = invertOrNot( image );
		image = sharpening( image );
		//image = nonLinearStretch( image, width, height );
		image = localCont( image );

		image.write( outFile );
	}
	catch ( Magick::Exception& error_ ) {
		std::cerr << "Caught exception: " << error_.what() << std::endl;
	}
}


std::string getOutputName( std::string& fileName, std::string& fileDir )
{
	std::string outName;
	outName += fileDir;
	outName += "\\";
	outName += fileName;

	return outName;
}

void runOnDir( std::string& input,
			   std::string& outDirNameStr )
{
	for ( const auto& entry : std::filesystem::directory_iterator( input ) ) {
		if ( is_regular_file( entry.path() ) )
		{
			std::string inFile = entry.path().string();
			std::string inFileNoEXT = entry.path().stem().string();
			const auto index_01 = inFile.find_last_of( "/\\" );
			std::string inFileNoPath = inFile.substr( index_01 + 1 );
			std::string ExtensionType = entry.path().extension().string();
			// output filename
			std::string outFile = getOutputName( inFileNoEXT, outDirNameStr ) + ".png";

			runProc( inFile, outFile );
		}
	}
}

void multiOutPutDir( int& multi, 
				  std::string& input )
{
	int dirNum = 1;
	for ( int i = 0; i < multi; i++ ) {
		std::string endNum = std::to_string( dirNum++ );
		std::ostringstream outDirName;

		std::filesystem::path path{ std::filesystem::path( input ).parent_path() };

		std::string outputPath{ path.string() + "_" };

		outDirName << outputPath << std::setw( 3 ) << std::setfill( '0' ) << endNum << "/";
		std::string outDirNameStr = outDirName.str();

		std::cout << "Directory: " << endNum << " created" << std::endl;
		std::filesystem::create_directory( outDirNameStr );

		runOnDir( input, outDirNameStr );
	}
}

int main(int argc, char** argv)
{
	cxxopts::Options options( argv[0] );
	options.add_options()
		( "i, input", "HR directory", cxxopts::value<std::string>() )
		( "m, multi", "multiple output folders", cxxopts::value<int>() )
		( "h, help", "print help" )
		;

	auto result = options.parse( argc, argv );

	if ( result.count( "help" ) )
	{
		std::cout << options.help() << std::endl;
		exit( 0 );
	}

	std::string input;
	int multi;

	if ( result.count( "input" ) )
		input = result["input"].as<std::string>();

	if ( result.count( "multi" ) )
		multi = result["multi"].as<int>();

	multiOutPutDir( multi, input );

}