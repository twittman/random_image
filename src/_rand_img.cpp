#include <Magick++.h>
#include <tabulate/tabulate.hpp>
#include <random>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <filesystem>
#include "util.hpp"
#include <cxxopts.hpp>
#ifdef _WIN32
#include <Windows.h>
#elif
#include <uinstd.h>
#endif
#define OOF_IMPL
#include <oof.h>

void printList(std::list<std::string> const& list) {
	for (auto const& i : list) {
		std::cout << i << std::endl;
	}
}

void enumConvert(int& enumBlend, std::string o, int& debug) {
	std::vector<std::string> enumVec;
	enumVec = { "UndefinedCompositeOp",
				"AlphaCompositeOp",
				"AtopCompositeOp",
				"BlendCompositeOp",
				"BlurCompositeOp",
				"BumpmapCompositeOp",
				"ChangeMaskCompositeOp",
				"ClearCompositeOp",
				"ColorBurnCompositeOp",
				"ColorDodgeCompositeOp",
				"ColorizeCompositeOp",
				"CopyBlackCompositeOp",
				"CopyBlueCompositeOp",
				"CopyCompositeOp",
				"CopyCyanCompositeOp",
				"CopyGreenCompositeOp",
				"CopyMagentaCompositeOp",
				"CopyAlphaCompositeOp",
				"CopyRedCompositeOp",
				"CopyYellowCompositeOp",
				"DarkenCompositeOp",
				"DarkenIntensityCompositeOp",
				"DifferenceCompositeOp",
				"DisplaceCompositeOp",
				"DissolveCompositeOp",
				"DistortCompositeOp",
				"DivideDstCompositeOp",
				"DivideSrcCompositeOp",
				"DstAtopCompositeOp",
				"DstCompositeOp",
				"DstInCompositeOp",
				"DstOutCompositeOp",
				"DstOverCompositeOp",
				"ExclusionCompositeOp",
				"HardLightCompositeOp",
				"HardMixCompositeOp",
				"HueCompositeOp",
				"InCompositeOp",
				"IntensityCompositeOp",
				"LightenCompositeOp",
				"LightenIntensityCompositeOp",
				"LinearBurnCompositeOp",
				"LinearDodgeCompositeOp",
				"LinearLightCompositeOp",
				"LuminizeCompositeOp",
				"MathematicsCompositeOp",
				"MinusDstCompositeOp",
				"MinusSrcCompositeOp",
				"ModulateCompositeOp",
				"ModulusAddCompositeOp",
				"ModulusSubtractCompositeOp",
				"MultiplyCompositeOp",
				"NoCompositeOp",
				"OutCompositeOp",
				"OverCompositeOp",
				"OverlayCompositeOp",
				"PegtopLightCompositeOp",
				"PinLightCompositeOp",
				"PlusCompositeOp",
				"ReplaceCompositeOp",
				"SaturateCompositeOp",
				"ScreenCompositeOp",
				"SoftLightCompositeOp",
				"SrcAtopCompositeOp",
				"SrcCompositeOp",
				"SrcInCompositeOp",
				"SrcOutCompositeOp",
				"SrcOverCompositeOp",
				"ThresholdCompositeOp",
				"VividLightCompositeOp",
				"XorCompositeOp",
				"StereoCompositeOp" };

	int number = enumBlend;
	auto count = enumVec.size();
	if (debug == 1) {
		std::cout << o << " blending mode: " << enumVec.at(number) << std::endl;
	}
}

std::filesystem::path GetExeDir() {
#ifdef _WIN32
	wchar_t sizePath[MAX_PATH];
	GetModuleFileNameW(NULL, sizePath, MAX_PATH);
#else
	char sizePath[PATH_MAX];
	ssize_t count = readLink("/proc/self/exe", sizePath, PATH_MAX);
	if (count < 0 || count >= PATH_MAX)
		return {};
	sizePath[count] = '\0';
#endif
	return std::filesystem::path{ sizePath }.parent_path() / "";
}

std::string pickFont()
{
	std::vector<std::string> FONTsample{ "AlienLeagueII",
										"AlienLeagueIIExpanded",
										"Arial",
										"Calibri",
										"Consolas",
										"CarlitoB",
										"CourierNew",
										"DejaVuSans",
										"FiraCode",
										"Giger",
										"LiberationSerif",
										"LucidaConsole",
										"Mangaspeak2",
										"NotoSans",
										"PokemonGB",
										"SegoeUI",
										"SourceCodePro",
										"TimesNewRomanBI",
										"Ubuntu",
										"UbuntuMono"
	};
	std::mt19937 generator(std::random_device{}());
	std::uniform_int_distribution<std::size_t> distribution(0, FONTsample.size() - 1);
	std::size_t number = distribution(generator);
	return FONTsample[number];
}

Magick::Image saturNation(Magick::Image& inputImgHR)
{
	double shart = twitls::randgen::randomNumber(0, 200);

	Magick::Image inImgHR;
	inImgHR = inputImgHR;

	inImgHR.modulate(100, shart, 100);

	return inImgHR;
}

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
	double hue_number = twitls::randgen::randomDouble( 10, 150 );

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
	else if (sharpMaybe == 1) {
		inImgHR.adaptiveSharpen(0, 1.2);
	}
	else if (sharpMaybe == 2) {
		inImgHR.adaptiveSharpen(0, 1.7);
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
	std::string oriSize = std::to_string( width ) + "x" + std::to_string( height ) + "!";

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

Magick::Image randomText( Magick::Image& inputImgHR, int& length, int& xP, int& yP, std::vector<std::string>& words, int& debug) {

	auto widthImg = inputImgHR.columns();
	auto heightImg = inputImgHR.rows();

	double textSepF;
	double textSepMin;
	double textSepMax;

	double fontsizeF;
	double fontsizeMin;
	double fontsizeMax;

	if (widthImg <= heightImg) {
		fontsizeF = (static_cast<double>(heightImg) / 11.3);
		textSepF = (static_cast<double>(heightImg) / 7.8);
	}
	else {
		fontsizeF = (static_cast<double>(widthImg) / 11.3);
		textSepF = (static_cast<double>(widthImg) / 7.8);
	}
	if (fontsizeF <= 10) {
		fontsizeF = 10;
	}
	else {
		fontsizeF = fontsizeF;
	}
	fontsizeMin = fontsizeF - 15;
	fontsizeMax = fontsizeF + 50;

	textSepMin = textSepF - 8;
	textSepMax = textSepF + 8;


	//int fontSize = twitls::randgen::randomNumber(fontsizeMin, fontsizeMax);
	double fontSizeD = twitls::randgen::randomDouble(fontsizeMin, fontsizeMax);
	int charNum = twitls::randgen::randomNumber(8, 32);
	int charNum2 = twitls::randgen::randomNumber(8, 32);
	int rotateOne = twitls::randgen::randomNumber(0, 6);
	double rotation = twitls::randgen::randomDouble(-20.0, 20.0);
	double yT = twitls::randgen::randomDouble(textSepMin, textSepMax);



	//std::list<std::string> outWords;
	//for (int i = 0; i < 2; ++i) {
	//	std::string t = twitls::randgen::randomWordsFromVector(words);
	//	outWords.push_back(t);
	//}
	//printList(outWords);

	std::string genText = twitls::randgen::randomWordsFromVector(words);
	std::string genText2 = twitls::randgen::randomWordsFromVector(words);

	if (debug == 1) {
		std::cout << "   Chosen words: " << genText << " " << genText2 << std::endl;
	}


	//std::string genText = twitls::randgen::randomNameGen(charNum);
	//std::string genText2 = twitls::randgen::randomNameGen(charNum);
	int R;
	int G;
	int B;

	R = twitls::randgen::randomNumber(0, 255);
	G = twitls::randgen::randomNumber(0, 255);
	B = twitls::randgen::randomNumber(0, 255);

	std::string rgbCol;
	rgbCol += "rgb";
	rgbCol += '(';
	rgbCol += std::to_string(R);
	rgbCol += ', ';
	rgbCol += std::to_string(G);
	rgbCol += ', ';
	rgbCol += std::to_string(B);
	rgbCol += ')';
	
	std::string dims = std::to_string(xP*3) + "x" + std::to_string(yP*3);

	Magick::Image inImgHR, 
		inImgTxtLayer(Magick::Geometry(dims), "transparent"),
		inImgBG(Magick::Geometry(dims), "red");
	inImgHR = inputImgHR;
	std::string fontM = pickFont();

	inImgTxtLayer.fontPointsize(fontSizeD);
	inImgTxtLayer.font(fontM);
	inImgTxtLayer.fillColor(Magick::Color(rgbCol));
	inImgTxtLayer.textGravity(Magick::CenterGravity);

	int textmaybe = 1;
	Magick::CompositeOperator compOpp = twitls::randgen::compOps();

	std::string o = "   Text";
	int enumBlend = compOpp;
	enumConvert(enumBlend, o, debug);

	if (textmaybe == 1) {
		inImgTxtLayer.alpha(true);
		inImgTxtLayer.draw(Magick::DrawableText(0, 0, genText));
		inImgTxtLayer.draw(Magick::DrawableText(0, yT, genText2));
		inImgTxtLayer.trim();
		inImgTxtLayer.backgroundColor("rgba(0,0,0,0)");

		if (rotateOne == 1) {
			inImgTxtLayer.rotate(rotation);
		}
		else if (rotateOne == 2) {
			inImgTxtLayer.rotate(90);
		}
		else if (rotateOne == 3) {
			inImgTxtLayer.rotate(180);
		}
		else if (rotateOne == 4) {
			inImgTxtLayer.rotate(270);
		}
		else {
			inImgTxtLayer.rotate(rotation);
		}
		inImgTxtLayer.repage();

		// maybe try to keep rotated text from rendering outside of the image???
		auto txtDimX = inImgTxtLayer.columns();
		auto txtDimY = inImgTxtLayer.rows();
		int xPos = twitls::randgen::randomNumber(1, (xP - txtDimX));
		int yPos = twitls::randgen::randomNumber(1, (yP - txtDimY));


		if (debug == 1) {
			std::cout << "\tFont size: " << std::to_string(fontSizeD) << "\n";
			std::cout << "\tImage width: " << xP << "\n";
			std::cout << "\tImage height: " << yP << "\n";
			std::cout << "\tText layer width: " << txtDimX << "\n";
			std::cout << "\tText layer height: " << txtDimY << "\n";
			std::cout << "\tX position: " << xPos << "\n";
			std::cout << "\tY position: " << yPos << "\n\n";
		}

		inImgHR.alpha(false);
		inImgHR.alpha(true);
		inImgHR.composite(inImgTxtLayer, xPos, yPos, compOpp);
	}
	else {
	}
	return inImgHR;
}

Magick::Image randomCamo(	Magick::Image& inputImgHR, 
							auto width, auto height, 
							std::filesystem::path& exeLocalPath, 
							std::string& localDir, int& debug) {

	std::string camoDir = localDir + "_rand-img_resources\\images";
	int count = twitls::count::countfiles(camoDir);

	Magick::Image inImgHR, camoImg;
	std::vector<std::string> imageList;
	std::string size;

	inImgHR = inputImgHR;

	int w = int(width) + 64;
	int h = int(height) + 64;
	size = std::to_string(w) + "x" + std::to_string(h) + "!";

	for (const auto& entry : std::filesystem::directory_iterator(camoDir)) {
		if (is_regular_file(entry.path()))
		{
			std::string inFile = entry.path().string();
			std::string inFileNoEXT = entry.path().stem().string();
			const auto index_01 = inFile.find_last_of("/\\");
			std::string inFileNoPath = inFile.substr(index_01 + 1);
			std::string ExtensionType = entry.path().extension().string();

			imageList.push_back(inFile);
		}
	}
	std::random_device seed;
	std::mt19937 engine(seed());
	std::uniform_int_distribution<int> choose(0, imageList.size() - 1);

	std::string chooseCamo = imageList[choose(engine)];

	Magick::CompositeOperator comp;
	int xR, yR;
	xR = twitls::randgen::randomNumber(-50, 0);
	yR = twitls::randgen::randomNumber(-50, 0);
	comp = twitls::randgen::compOps2();

	std::string o = "   Camo";
	int enumBlend = comp;
	enumConvert(enumBlend, o, debug);

	camoImg.read(chooseCamo);
	camoImg.filterType(Magick::HammingFilter);

	camoImg = flipFlop(camoImg);
	camoImg = hueHueHue(camoImg);
	camoImg = rotateOrNotToRotate(camoImg);
	camoImg = localCont(camoImg);
	camoImg = sharpening(camoImg);
	camoImg = nonLinearStretch(camoImg, width, height);
	camoImg.resize(Magick::Geometry(size));
	
	inImgHR.alpha(false);
	inImgHR.alpha(true);
	inImgHR.composite(camoImg, xR, yR, comp);

	return inImgHR;
}

void runProc(	std::string& inFile, std::string& outFile, 
				int& combo, std::vector<std::string>& words, 
				std::filesystem::path& exeLocalPath, std::string& localDir, int& debug)
{
	
	try {
		Magick::Image image;

		image.read( inFile );
		//image.alpha( true );
		//image.alpha( false );

		auto width = image.baseColumns();
		auto height = image.baseRows();

		int xP = static_cast<int>(width);
		int yP = static_cast<int>(height);

		int length = twitls::randgen::randomNumber(10, 50);

		switch (combo) {
		case 0:
			image = randomCamo(image, width, height, exeLocalPath, localDir, debug); break;
		case 1:
			image = hueHueHue(image);
			image = saturNation(image);
			image = randomCamo(image, width, height, exeLocalPath, localDir, debug);
			image = randomText(image, length, xP, yP, words, debug); break;
		case 2:
			image = hueHueHue(image);
			image = randomCamo(image, width, height, exeLocalPath, localDir, debug); break;
		case 3:
			image = saturNation(image);
			image = randomText(image, length, xP, yP, words, debug); break;
		case 4:
			image = hueHueHue(image);
			image = saturNation(image); break;
		case 5:
			image = hueHueHue(image);
			image = saturNation(image); break;
		case 6:
			image = randomText(image, length, xP, yP, words, debug); break;
		case 7:
			image = sharpening(image); break;
		case 8 :
			image = hueHueHue(image);
			image = sharpening(image);
			image = brightNess(image); break;
		}



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
			   std::string& outDirNameStr, int& combo, 
			   std::filesystem::path& exeLocalPath, int& debug)
{

	/// //////////////////////////////////// ///
	/// load word list file					 ///
	///										 ///
	std::string localDir = exeLocalPath.string();
	std::string listDirTxt = localDir + "_rand-img_resources\\lists\\wordlist.txt";
	std::string pickedWord;
	// get list of words and place in vector //
	std::ifstream listInput(listDirTxt);
	std::vector<std::string> words;
	
	std::string word;
	while (listInput >> word)
		words.push_back(word);
	///										 ///
	/// //////////////////////////////////// ///


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

			runProc( inFile, outFile, combo, words, exeLocalPath, localDir, debug);
		}
	}
}

void multiOutPutDir( int& multi, 
				  std::string& input, int& combo, int& debug)
{
	std::filesystem::path exeLocalPath = GetExeDir();
	int dirNum = 1;
	int comboV;
	for ( int i = 0; i < multi; i++ ) {


		std::string endNum = std::to_string( dirNum++ );
		std::ostringstream outDirName;

		std::filesystem::path path{ std::filesystem::path( input ).parent_path() };

		std::string outputPath{ path.string() + "_" };

		outDirName << outputPath << std::setw( 3 ) << std::setfill( '0' ) << endNum << "/";
		std::string outDirNameStr = outDirName.str();

		std::cout << "Directory: " << endNum << " created\n" << std::endl;
		std::filesystem::create_directory( outDirNameStr );

		//int comboValue;
		if (combo >= 9) {
			comboV = twitls::randgen::randomNumber(0, 8);
		}
		else {
			comboV = combo;
		}
		if (debug == 1) {
			std::cout << "Chosen filters:  " << "\n";
			switch (comboV) {
			case 0:
				std::cout << "   Camo only." << "\n\n"; break;
			case 1:
				std::cout << "   Camo, Hue, Sat, Text." << "\n\n"; break;
			case 2:
				std::cout << "   Camo, Hue." << "\n\n"; break;
			case 3:
				std::cout << "   Sat, Text." << "\n\n"; break;
			case 4:
				std::cout << "   Hue, Sat." << "\n\n"; break;
			case 5:
				std::cout << "   Hue, Sat." << "\n\n"; break;
			case 6:
				std::cout << "   Text." << "\n\n"; break;
			case 7:
				std::cout << "   Sharp." << "\n\n"; break;
			case 8 :
				std::cout << "   Hue, Sharp, Bright." << "\n\n"; break;
			}
		}


		runOnDir( input, outDirNameStr, comboV, exeLocalPath, debug );
	}
}


int main(int argc, char** argv)
{	


	cxxopts::Options options( argv[0] );
	options.add_options()
		( "i, input", "HR directory", cxxopts::value<std::string>() )
		( "c, combo", "which combination?, > 9 for random", cxxopts::value<int>() )
		( "m, multi", "multiple output folders", cxxopts::value<int>() )
		( "d, debug", "print out debug info", cxxopts::value<int>() )
		( "h, help", "print help" )
		;

	auto result = options.parse( argc, argv );

	if ( result.count( "help" ) )
	{
		std::cout << options.help() << std::endl;
		exit( 0 );
	}

	std::string input;
	int combo;
	int multi;
	int debug;

	if ( result.count( "input" ) )
		input = result["input"].as<std::string>();

	if (result.count("combo"))
		combo = result["combo"].as<int>();

	if ( result.count( "multi" ) )
		multi = result["multi"].as<int>();

	if (result.count("debug"))
		debug = result["debug"].as<int>();


	multiOutPutDir( multi, input, combo, debug);

}