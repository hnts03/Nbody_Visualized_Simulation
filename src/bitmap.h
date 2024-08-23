/*  
	This is toy-project to build nbody-simulation from scratch.
	* Author:	hnts03
	* Date:		24.08.22
	* Update:	-
*/

#include <cstdint>
#include <fstream>

using namespace std;



/*	The Bitmap file has two headers for metadata. First header (bitmap
 *	file header) tells that this binary file is a bitmap file. The next
 *	header (bitmap info header) contains additional meta-data about the
 *	image.
 *	For bitmap file header(14 bytes) we need to create the following data
 *	structure:
 */
struct BmpHeader {
	char bitmapSignatureBytes[2] = {'B', 'M'};
	uint32_t sizeOfBitmapFile = 54 + 786432;	// 
	uint32_t reservedBytes = 0;
	uint32_t pixelDataOffset = 54;
	
	void saveOnFile(FILE *fp){
		fwrite(&bitmapSignatureBytes, sizeof(char), 2, fp);
		fwrite(&sizeOfBitmapFile, sizeof(uint32_t), 1, fp);
		fwrite(&reservedBytes, sizeof(uint32_t), 1, fp);
		fwrite(&pixelDataOffset, sizeof(uint32_t), 1, fp);
	}
};


/*	The first two bytes 'B' and 'M' are unique to the bitmap file format.
 *	The next 4 bytes contain total size of the bitmap file in bytes. As
 *	we are creating a 512 x 512 bitmap image, total size is the sum of 
 *	size of metadata (14 + 40 = 54 bytes) and size of pixels (512 x 512
 *	x 3 = 786432, each pixel is of 3 bytes in 24bit bitmap file). The
 *	last field of bitmap file header contains the offset of the pixel 
 *	data of the image from the start of the file. In our case the offset
 *	is 54bytes, as our pixe data is right after the bitmap file header
 *	and info header (14 + 40 = 54).
 *	The bitmap file has various types of info header, but the most common
 *	one is the 40 byte Bitmap info Header, so we need to write it down in
 *	the following data structure:
 */
struct BmpInfoHeader {
	uint32_t	sizeOfThisHeader = 40;
	int32_t		width = 512;  // in pixels
	int32_t		height = 512; // in pixels
	uint16_t	numberOfColorPlanes = 1; // must be 1
	uint16_t	colorDepth = 24;
	uint32_t	compressionMethod = 0;
	uint32_t	rawBitmapDataSize = 0; // generally ignored
	int32_t		horizontalResolution = 3780; // in pixel per meter
	int32_t		verticalResolution = 3780;   // in pixel per meter 
	uint32_t	colorTableEntries = 0;
	uint32_t	importantColors = 0;

	void saveOnFile(FILE *fp){
		fwrite(&sizeOfThisHeader, sizeof(uint32_t), 1, fp);
		fwrite(&width, sizeof(int32_t), 1, fp);
		fwrite(&height, sizeof(int32_t), 1, fp);
		fwrite(&numberOfColorPlanes, sizeof(uint16_t), 1, fp);
		fwrite(&colorDepth, sizeof(uint16_t), 1, fp);
		fwrite(&compressionMethod, sizeof(uint32_t), 1, fp);
		fwrite(&rawBitmapDataSize, sizeof(uint32_t), 1, fp);
		fwrite(&horizontalResolution, sizeof(int32_t), 1, fp);
		fwrite(&verticalResolution, sizeof(int32_t), 1, fp);
		fwrite(&colorTableEntries, sizeof(uint32_t), 1, fp);
		fwrite(&importantColors, sizeof(uint32_t), 1, fp);
	}
};


/*	 Struct for Pixel
 *	 If you want to create mono-color bitmap, make same pixel values
 */
struct Pixel {
	// initialli black
	uint8_t blue	= 0;
	uint8_t green	= 0;
	uint8_t red		= 0;

	void saveOnFile(FILE *fp){
		fwrite(&blue, sizeof(uint8_t), 1, fp);
		fwrite(&green, sizeof(uint8_t), 1, fp);
		fwrite(&red, sizeof(uint8_t), 1, fp);
	}

	void init(){
		blue	= 0;
		green	= 0;
		red		= 0;
	}

	void setColors(uint8_t _blue, uint8_t _green, uint8_t _red){
		blue		= _blue;
		green		= _green;
		red			= _red;
	}
};


/*	Struct of bitmap file
 */
struct BitmapFile {
	struct BmpHeader bmpHeader;
	struct BmpInfoHeader bmpInfoHeader;
	struct Pixel *pixels;
	uint32_t screenSize;
	
	~BitmapFile(){
		cleanup();
	}

	void cleanup(){
		if (pixels != NULL){
			free(pixels);
			pixels = NULL;
		}
	}

	void init(uint32_t bitmapWidth, uint32_t bitmapHeight){
		screenSize = bitmapWidth * bitmapHeight;
		bmpHeader.sizeOfBitmapFile = bmpHeader.pixelDataOffset + 
							screenSize * 3/* channel */;
		bmpInfoHeader.height =	bitmapHeight;
		bmpInfoHeader.width  =	bitmapWidth;

		pixels = (struct Pixel *)malloc(sizeof(struct Pixel) * screenSize);
		for(uint32_t i = 0; i < screenSize; i++){
			pixels[i].init();
		}
	}

	void drawPixel(uint32_t width, uint32_t height){
		pixels[height * bmpInfoHeader.width + width].setColors(255, 255, 255);
		printf("Pixel drawn at %d, %d\n", width, height); // Debugging
	}

	void drawBitmapFile(FILE *fp){
		bmpHeader.saveOnFile(fp);
		bmpInfoHeader.saveOnFile(fp);
		for (uint32_t i = 0; i < screenSize; i++){
			pixels[i].saveOnFile(fp);
		}
	}
};
