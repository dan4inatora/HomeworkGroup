#pragma once
#include <iostream>
#include <fstream>
#include <cstdio>


struct BMPSignature
{
	unsigned char data[2]; //should be equal to 'BM'
	BMPSignature()
	{
		data[0] = data[1] = 0;
	}
};

struct BMPHeader
{
	unsigned int fileSize; // size of file in bytes
	unsigned short reserved1; //reserved; must be zero
	unsigned short reserved2; //reserved; must be zero
	unsigned int dataOffset; // the offset in bytes from the BMPHeader

	BMPHeader() :fileSize(0), reserved1(0), reserved2(0), dataOffset(0)
	{
	}
};

#pragma pack(push,2) //2 byte alignment??
struct InfoHeader
{
	unsigned int size; //number of bytes required
	int width; //width in pixels
	int height; //height in pixels
	unsigned short planes; //number of color planes; must be 1
	unsigned short bitCount; //number of bit per pixel; must be 1, 4, 8, 16, 24, or 32
	unsigned int compression; //type of compression
	unsigned int sizeImage; //size of image in bytes
	int xPelsPerMeter; //number of pixels per meter in x axis
	int yPelsPerMeter; //number of pixels per meter in y axis
	unsigned int clrUsed; //colors information
	unsigned int clrImportant; //colors information
};
#pragma pack(pop) //remove the 2 byte alignment so it doesnt affect
				  //anything outside the struct

void ReadHeader(std::ifstream &pic, BMPSignature &signature, BMPHeader &header)
{
	if (!pic)
		return;

	pic.read((char*)&signature, sizeof(signature));
	pic.read((char*)&header, sizeof(header));
}
void ReadInfoHeader(std::ifstream &pic, InfoHeader &infoHeader)
{
	if (!pic)
		return;

	pic.read((char*)&infoHeader, sizeof(infoHeader));
}
void PrintHeader(BMPSignature signature, BMPHeader header)
{
	std::cout << "BMP Header" << std::endl;
	std::cout << "Signature  : " << signature.data[0] << signature.data[1] << std::endl;
	std::cout << "File Size  : " << header.fileSize << " byte(s)" << std::endl;
	std::cout << "Reserved1  : " << header.reserved1 << std::endl;
	std::cout << "Reserved2  : " << header.reserved2 << std::endl;
	std::cout << "Data Offset: " << header.dataOffset << " byte(s)" << std::endl;
}


void PrintInfoH(InfoHeader infoHeader)
{
	std::cout << std::endl;
	std::cout << "Info Header" << std::endl;
	std::cout << "Size: " << infoHeader.size << " byte(s)" << std::endl;
	std::cout << "Width: " << infoHeader.width << " pixel(s)" << std::endl;
	std::cout << "Height: " << infoHeader.height << " pixel(s)" << std::endl;
	std::cout << "Planes: " << infoHeader.planes << std::endl;
	std::cout << "Bit Count: " << infoHeader.bitCount << std::endl;
	std::cout << "Type of Compression: " << infoHeader.compression << std::endl;
	std::cout << "Size of Image: " << infoHeader.sizeImage << " byte(s)" << std::endl;
	std::cout << "Pixels per Meter in X Axis: " << infoHeader.xPelsPerMeter << std::endl;
	std::cout << "Pixels per Meter in Y Axis: " << infoHeader.yPelsPerMeter << std::endl;
	std::cout << "Colors Used: " << infoHeader.clrUsed << std::endl;
	std::cout << "Important Colours: " << infoHeader.clrImportant << std::endl;
}