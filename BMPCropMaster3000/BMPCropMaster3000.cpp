// BMPCropMaster3000.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "BMPHeader.h"

using namespace std;

int main()
{
	ifstream pic("Test1.BMP", ios::binary); //TEST SUCCESSFUL
	//ifstream pic("dogs2.bmp", ios::binary);  //PRI TOZI TEST GARMI
	//ifstream pic("dogs.bmp", ios::binary);  //TEST SUCCESSFUL

	//initialize all the headers and the signature
	BMPSignature signature;
	BMPHeader header;
	InfoHeader infoHeader;

	//methods
	ReadHeader(pic, signature, header);
	ReadInfoHeader(pic, infoHeader);
	PrintHeader(signature, header);
	PrintInfoH(infoHeader);

    return 0;
}

