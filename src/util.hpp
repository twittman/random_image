#include <algorithm>
#include <iterator>
#include <vector>
#include <string>
#include <filesystem>

namespace twitls {
	namespace vec_ops {
		template<typename Vector>
		auto split_vector( const Vector& v, unsigned num_lines )
		{
			using Iterator = typename Vector::const_iterator;
			std::vector<Vector> rtn;
			Iterator it = v.cbegin();
			const Iterator end = v.cend();

			while ( it != end ) {
				Vector v;
				std::back_insert_iterator<Vector> inserter( v );
				const auto num_to_copy = std::min( static_cast<unsigned>(
					std::distance( it, end ) ), num_lines );
				std::copy( it, it + num_to_copy, inserter );
				rtn.push_back( std::move( v ) );
				std::advance( it, num_to_copy );
			}
			return rtn;
		}
	}
	namespace imgExt {
		bool is_image_extension( std::string input )
		{
			// apparently this converts the string (input), to lowercase
			transform( input.begin(), input.end(), input.begin(), ::tolower );
			std::vector<std::string> valid_extensions = { ".jpg", ".jpeg", ".png", ".webp", ".tif", ".tiff" };
			for ( auto& i : valid_extensions ) {
				if ( input == i ) {
					return true;
				}
			}
			return false;
		}
	}
	namespace count {
		int countfiles( std::string& directoryCount )
		{
			int numFiles = 0;
			for ( const auto& entry : std::filesystem::directory_iterator( directoryCount ) ) {
				if ( entry.is_regular_file() ) {
					numFiles++;
				}
			}
			return numFiles;
		}
		int countLines(std::string& inputFile) 
		{
			std::ifstream inFile(inputFile);
			inFile.unsetf(std::ios_base::skipws);
			unsigned count = std::count(std::istream_iterator<char>(inFile), 
				std::istream_iterator<char>(), '\n');
			return count;
		}
		auto diff( int dimension, int tileSize )
		{
			double difference;
			return difference = ( ( static_cast<double>( dimension ) + tileSize ) / tileSize );
		}
		auto padd( int difference, int tileSize )
		{
			double padding;
			return padding = ( ( static_cast<double>( difference ) - 1 ) * tileSize );
		}
		auto divv( int dimension, int padding )
		{
			double divizor;
			return divizor = ( static_cast<double>( dimension ) - padding );
		}
		auto isDiff( int W, int H )
		{
			int difference;
			if ( W <= H ) {
				return difference = H;
			}
			else if ( W >= H ) {
				return difference = W;
			}
		}
	}
	namespace randgen {
		std::string randomNameGen( const int length )
		{
			std::string randString;
			static const char alphanum[] =
				"abcdefghijklmnopqrstuvwxyz"
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"0123456789";
			std::random_device rd;
			std::mt19937 generator( rd() );
			randString.reserve( length );
			for ( int i = 0; i < length; ++i ) {
				randString += alphanum[generator() % ( sizeof( alphanum ) - 1 )];
			}
			return randString;
		}
		std::string randomWordsFromVector(std::vector<std::string>& inputVector) {
			std::string chooseWord;
			std::vector<std::string> v = inputVector;
			std::random_device seed01;
			std::mt19937 engine01(seed01());
			std::uniform_int_distribution<int> choose01(0, v.size() - 1);

			chooseWord = v[choose01(engine01)];
			return chooseWord;
		}
		int randomNumber( const int low, const int high )
		{
			std::random_device rd;
			std::mt19937 generator( rd() );
			std::uniform_int_distribution r01( low, high );
			int rNum = r01( generator );
			return rNum;
		}
		double randomDouble( const double low, const double high )
		{
			std::random_device rd;
			std::mt19937 generator( rd() );
			std::uniform_real_distribution r01( low, high );
			double rNum = r01( generator );
			return rNum;
		}
		std::string pickSampling()
		{
			srand( (unsigned int)time( NULL ) );
			const std::string YUVsample[3] = { "yuv422p",
												"yuv420p",
												"yuv410p" };
			return YUVsample[rand() % 3];
		}
		std::string pickCompressor()
		{
			srand( (unsigned int)time( NULL ) );
			const std::string compressor[3] = { "libx264",
												"libx265",
												"libvpx-vp9" };
			return compressor[rand() % 3];
		}
		std::string randomOrderedDither()
		{
			srand( (unsigned int)time( NULL ) );
			const std::string chooseR[2] = { "o4x4,3",
											 "o8x8,3" };
			return chooseR[rand() % 2];
		}
		Magick::FilterType filtersYo()
		{
			std::vector<Magick::FilterType> samList02{	Magick::BlackmanFilter,
														Magick::BohmanFilter,
														Magick::BoxFilter,
														Magick::CatromFilter,
														Magick::CosineFilter,
														Magick::CubicFilter,
														Magick::HannFilter,
														Magick::HermiteFilter,
														Magick::JincFilter,
														Magick::KaiserFilter,
														Magick::LagrangeFilter,
														Magick::Lanczos2Filter,
														Magick::MitchellFilter,
														Magick::ParzenFilter,
														Magick::PointFilter,
														Magick::QuadraticFilter,
														Magick::RobidouxFilter,
														Magick::SincFilter,
														Magick::SplineFilter,
														Magick::TriangleFilter,
														Magick::WelchFilter 
			};
			std::mt19937 generator02(std::random_device{}());
			std::uniform_int_distribution<std::size_t> distribution02(0, samList02.size() - 1);
			std::size_t number02 = distribution02(generator02);
			return samList02[number02];
		}
		Magick::FilterType filtersYoSharp()
		{
			std::vector<Magick::FilterType> samList03{	Magick::PointFilter,
														Magick::BoxFilter,
														Magick::TriangleFilter,
														Magick::Lanczos2Filter,
														Magick::CubicFilter,
														Magick::JincFilter,
														Magick::CosineFilter,
														Magick::SincFilter 
			};
			std::mt19937 generator03(std::random_device{}());
			std::uniform_int_distribution<std::size_t> distribution03(0, samList03.size() - 1);
			std::size_t number03 = distribution03(generator03);
			return samList03[number03];
		}
		Magick::CompositeOperator compOps()
		{
			std::vector<Magick::CompositeOperator> opsList{	Magick::OverlayCompositeOp,
															Magick::ScreenCompositeOp,
															Magick::ColorDodgeCompositeOp,
															Magick::MultiplyCompositeOp,
															Magick::LinearBurnCompositeOp,
															Magick::ExclusionCompositeOp 
			};
			std::mt19937 generator04(std::random_device{}());
			std::uniform_int_distribution<std::size_t> distribution04(0, opsList.size() - 1);
			std::size_t number04 = distribution04(generator04);
			return opsList[number04];
		}
		Magick::CompositeOperator compOps2()
		{
			std::vector<Magick::CompositeOperator> opsList2{	Magick::OverlayCompositeOp,
																Magick::SoftLightCompositeOp,
																Magick::SaturateCompositeOp,
																Magick::BumpmapCompositeOp,
																Magick::ColorizeCompositeOp,
																Magick::BumpmapCompositeOp 
			};
			std::mt19937 generator05(std::random_device{}());
			std::uniform_int_distribution<std::size_t> distribution05(0, opsList2.size() - 1);
			std::size_t number05 = distribution05(generator05);
			return opsList2[number05];
		}
		std::string samplesYo()
		{
			std::vector<std::string> samplesList{	"4:1:0",
													"4:1:1",
													"4:2:0",
													"4:2:2",
													"4:4:0",
													"4:4:4" 
			};
			std::mt19937 generator06(std::random_device{}());
			std::uniform_int_distribution<std::size_t> distribution06(0, samplesList.size() - 1);
			std::size_t number06 = distribution06(generator06);
			return samplesList[number06];
		}
	}
	namespace scriptmake {
		std::string ffmpegScriptShell( std::string directory, int leading_zeros, std::string fps,
									   std::string codec, std::string pixelfmt,
									   std::string CRF, std::string video_name )
		{
			std::string ffmpeg_lead = "%0" + std::to_string( leading_zeros ) + "d";
			std::string ffmpegCall( "ffmpeg" );
			std::string fpsCall = " -framerate " + fps + " ";
			std::string codecCall = " -c:v " + codec;
			std::string pixFmtCall = " -pix_fmt " + pixelfmt;
			std::string crfCall = " -crf " + CRF;
			std::string x265_log_level;
			if ( codec == "libx265" ) {
				x265_log_level = " -x265-params log-level=-1";
			}
			else {
				x265_log_level = "";
			}

			std::string frName( "montage_frame_" );
			std::string full_string_for_script;
			full_string_for_script += ffmpegCall;
			full_string_for_script += " -loglevel quiet";
			full_string_for_script += fpsCall;
			full_string_for_script += "-i ";
			full_string_for_script += directory;
			full_string_for_script += frName;
			full_string_for_script += ffmpeg_lead;
			full_string_for_script += ".png";
			full_string_for_script += pixFmtCall;
			full_string_for_script += codecCall;
			full_string_for_script += x265_log_level;
			full_string_for_script += crfCall;
			full_string_for_script += " ";
			full_string_for_script += video_name;
			return full_string_for_script;
		}
		std::string ffmpegScriptBat( std::string directory, int leading_zeros, std::string fps,
									 std::string codec, std::string pixelfmt,
									 std::string CRF, std::string video_name )
		{
			std::string ffmpeg_lead = "%0" + std::to_string( leading_zeros ) + "d";
			std::string ffmpegCall( "ffmpeg" );
			std::string fpsCall = " -framerate " + fps + " ";
			std::string codecCall = " -c:v " + codec;
			std::string pixFmtCall = " -pix_fmt " + pixelfmt;
			std::string crfCall = " -crf " + CRF;
			std::string x265_log_level;
			if ( codec == "libx265" ) {
				x265_log_level = " -x265-params log-level=-1";
			}
			else {
				x265_log_level = "";
			}

			std::string frName( "montage_frame_" );
			std::string full_string_for_script;
			full_string_for_script += ffmpegCall;
			full_string_for_script += " -loglevel quiet";
			full_string_for_script += fpsCall;
			full_string_for_script += "-i ";
			full_string_for_script += '"';
			full_string_for_script += directory;
			full_string_for_script += frName;
			full_string_for_script += ffmpeg_lead;
			full_string_for_script += ".png";
			full_string_for_script += '"';
			full_string_for_script += pixFmtCall;
			full_string_for_script += codecCall;
			full_string_for_script += x265_log_level;
			full_string_for_script += crfCall;
			full_string_for_script += " ";
			full_string_for_script += video_name;
			return full_string_for_script;
		}
		std::string extractScriptShell( std::string input_Video, int leading_zeros, std::string outputDirectory )
		{
			std::string ffmpeg_lead = "%0" + std::to_string( leading_zeros ) + "d";
			std::string ffmpegCall( "ffmpeg" );

			std::string frName( "montage_frame_" );
			std::string full_extract_string;
			full_extract_string += ffmpegCall;
			full_extract_string += " -loglevel quiet";
			full_extract_string += " -i ";
			full_extract_string += input_Video;
			full_extract_string += " ";
			full_extract_string += outputDirectory;
			full_extract_string += frName;
			full_extract_string += ffmpeg_lead;
			full_extract_string += ".png";
			return full_extract_string;
		}
		std::string extractScriptBat( std::string input_Video, int leading_zeros, std::string outputDirectory )
		{
			std::string ffmpeg_lead = "%0" + std::to_string( leading_zeros ) + "d";
			std::string ffmpegCall( "ffmpeg" );

			std::string frName( "montage_frame_" );
			std::string full_extract_string;
			full_extract_string += ffmpegCall;
			full_extract_string += " -loglevel quiet";
			full_extract_string += " -i ";
			full_extract_string += input_Video;
			full_extract_string += " ";
			full_extract_string += '"';
			full_extract_string += outputDirectory;
			full_extract_string += frName;
			full_extract_string += ffmpeg_lead;
			full_extract_string += ".png";
			full_extract_string += '"';
			return full_extract_string;
		}
	}
}




