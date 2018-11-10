#include <iostream>
#include<sstream>
#include <fstream>
#include <string>
#include <math.h>
#include <cstdint>
#include <vector>
#include <iterator>
bool fexists(const std::string& filename) {
  std::ifstream ifile(filename.c_str());
  return (bool)ifile;
}

#pragma pack(push,2)
class Header{
private:


    unsigned char data[2];
    unsigned int fileSize;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int dataOffset;
    unsigned int header_size;
    unsigned int width;
    unsigned int height;
    signed short number_color_planes;
    signed short bits_per_pixel;
    unsigned int compression_method;
    unsigned int image_size;
    unsigned int horizontal_resolution;
    unsigned int vertical_resolution;
    unsigned int number_colors;
    unsigned int number_important_colors;


public:
    Header();
    void readHeader(std::ifstream &fin);
    void writeHeader(std::ofstream &fout);
    void printHeader()const;
    int rowSize();
    unsigned int getfilesize()const{
        return this->fileSize;
    }
    unsigned int getimagesize()const{
        return this->image_size;
    }
    unsigned int getheadersize()const{
        return this->header_size;
    }
    signed short getBitsPerPixel()const{
        return this->bits_per_pixel;
    }
    unsigned int getHeight()const{
        return this->height;
    }

    unsigned int getdataOffset()const{
        return this->dataOffset;
    }
    void setFileSize(const unsigned int f){
        this->fileSize = f;
    }
    void setWidth(const unsigned int f){
        this->width = f;
    }
    void setHeight(const unsigned int f){
        this->height = f;
    }
    void setImageSize(const unsigned int f){
        this->image_size = f;
    }



};
#pragma pack(pop)
Header :: Header(){

    this->data[0] = this->data[1] = 0;
    this->fileSize = 0;
    this->reserved1 = 0;
    this->reserved2 = 0;
    this->dataOffset = 0;
    this->header_size = 0;
    this->width = 0;
    this->height = 0;
    this->number_color_planes = 0;
    this->bits_per_pixel = 0;
    this->compression_method = 0;
    this->image_size = 0;
    this->horizontal_resolution = 0;
    this->vertical_resolution = 0;
    this->number_colors = 0;
    this->number_important_colors = 0;


}

void Header :: readHeader(std::ifstream &fin){

    if(!fin){
        return;
    }

    fin.read((char*)&this->data , sizeof(this->data));
    fin.read((char*)&this->fileSize , sizeof(fileSize));
    fin.read((char*)&this->reserved1 , sizeof(reserved1));
    fin.read((char*)&this->reserved2 , sizeof(reserved2));
    fin.read((char*)&this->dataOffset , sizeof(dataOffset));
    fin.read((char*)&this->header_size , sizeof(header_size));
    fin.read((char*)&this->width , sizeof(width));
    fin.read((char*)&this->height , sizeof(height));
    fin.read((char*)&this->number_color_planes , sizeof(number_color_planes));
    fin.read((char*)&this->bits_per_pixel , sizeof(bits_per_pixel));
    fin.read((char*)&this->compression_method , sizeof(compression_method));
    fin.read((char*)&this->image_size , sizeof(image_size));
    fin.read((char*)&this->horizontal_resolution , sizeof(horizontal_resolution));
    fin.read((char*)&this->vertical_resolution , sizeof(vertical_resolution));
    fin.read((char*)&this->number_colors , sizeof(number_colors));
    fin.read((char*)&this->number_important_colors , sizeof(number_important_colors));


}

void Header :: printHeader()const{

    std::cout<<"+ Signature  : " << this->data[0]<<this->data[1]<<std::endl;
    std::cout<<"+ File Size  : " << this->fileSize<<" byte(s)"<<std::endl;
    std::cout<<"+ Reserved1  : " << this->reserved1<<std::endl;
    std::cout<<"+ Reserved2  : " << this->reserved2<<std::endl;
    std::cout<<"+ Data Offset: " << this->dataOffset<<" byte(s)"<<std::endl;
    std::cout<<"+ Header size: " << this->header_size <<std::endl;
    std::cout<<"+ Width: " << this->width <<std::endl;
    std::cout<<"+ Height: " << this->height <<std::endl;
    std::cout<<"+ Color planes: " << this->number_color_planes <<std::endl;
    std::cout<<"+ Bits per pixel: " << this->bits_per_pixel <<std::endl;
    std::cout<<"+ Compression method: " << this->compression_method <<std::endl;
    std::cout<<"+ Image size: " << this->image_size<<" byte(s)" <<std::endl;
    std::cout<<"+ Horizontal rez: " << this->horizontal_resolution <<std::endl;
    std::cout<<"+ Vertical rez: " << this->vertical_resolution <<std::endl;
    std::cout<<"+ Number colors: " << this->number_colors <<std::endl;
    std::cout<<"+ Number Important colors: " << this->number_important_colors <<std::endl;



}

int Header :: rowSize(){
    int rows = floor((this->bits_per_pixel * width + 31)/32) * 4;
    return rows;
}


void Header :: writeHeader(std::ofstream &fout){

    if(!fout.is_open()){return;}
    fout.write((char*)&this->data , sizeof(this->data));
    fout.write((char*)&this->fileSize , sizeof(fileSize));
    fout.write((char*)&this->reserved1 , sizeof(reserved1));
    fout.write((char*)&this->reserved2 , sizeof(reserved2));
    fout.write((char*)&this->dataOffset , sizeof(dataOffset));
    fout.write((char*)&this->header_size , sizeof(header_size));
    fout.write((char*)&this->width , sizeof(width));
    fout.write((char*)&this->height , sizeof(height));
    fout.write((char*)&this->number_color_planes , sizeof(number_color_planes));
    fout.write((char*)&this->bits_per_pixel , sizeof(bits_per_pixel));
    fout.write((char*)&this->compression_method , sizeof(compression_method));
    fout.write((char*)&this->image_size , sizeof(image_size));
    fout.write((char*)&this->horizontal_resolution , sizeof(horizontal_resolution));
    fout.write((char*)&this->vertical_resolution , sizeof(vertical_resolution));
    fout.write((char*)&this->number_colors , sizeof(number_colors));
    fout.write((char*)&this->number_important_colors , sizeof(number_important_colors));

}

class ColorScheme{
    private:

        char * colorscheme;
        size_t size;
        size_t capacity;
        void copy(const ColorScheme& other);
        void resize();
        void erase();

    public:
        ColorScheme();
        ColorScheme(int n);
        ColorScheme(const ColorScheme& other);
        ColorScheme& operator = (const ColorScheme& other);
        ~ColorScheme();
        void push(const char c);
        void readColorScheme(std::ifstream& fin);
        size_t getSchemesize()const;
        void printScheme();
        void writeScheme(std::ofstream &fout);



};


void ColorScheme :: writeScheme(std::ofstream &fout){
    if(!fout.is_open()){
        return;
    }
    fout.write((char*)this->colorscheme, this->size);
}

void ColorScheme :: copy(const ColorScheme& other){
    this->capacity = other.capacity;
    this->size = other.size;
    this->colorscheme = new char[other.capacity];
    for(size_t i = 0; i < this->size; i++){
        this->colorscheme[i] = other.colorscheme[i];
    }
}

void ColorScheme :: erase(){
    delete[]this->colorscheme;
}

void ColorScheme :: resize(){
    if(this->size >= this->capacity){
        capacity *= 2;
    }
}

ColorScheme :: ColorScheme(){
    this->size = 0;
    this->capacity = 4;
    this->colorscheme = new char[capacity];
}

ColorScheme :: ColorScheme(const ColorScheme& other){
    this->copy(other);
}

ColorScheme& ColorScheme :: operator = (const ColorScheme& other){
    if(this != &other){
        this->erase();
        this->copy(other);
    }
    return *this;
}

ColorScheme :: ~ColorScheme(){
    this->erase();
}

void ColorScheme :: push(const char c){
    this->resize();
    this->colorscheme[size++] = c;
}


ColorScheme :: ColorScheme(int n){
    this->size = n;
    this->colorscheme = new char[n];
    this->capacity = 2 * n;
}

void ColorScheme :: readColorScheme(std::ifstream& fin){
    if(!fin){
        return;
    }
    fin.read((char*)this->colorscheme, this->size);
}


size_t ColorScheme :: getSchemesize()const{
    return this->size;
}

void ColorScheme :: printScheme(){
    for(size_t i = 0; i < this->size; i++){
        std::cout<<colorscheme[i];
    }
}


class Pixel{
    private:
        char * pixelsize;
        size_t size;
        size_t capacity;
        void copy(const Pixel& other);
        void resize();
        void erase();
    public:
        Pixel();
        Pixel(int n);
        Pixel(const Pixel& other);
        Pixel& operator = (const Pixel& other);
        ~Pixel();
        void readPixel(std::ifstream &fin);
        void push(const char c);
        size_t getPixelSize()const;
        void printPixel();
        void writePixel(std::ofstream& fout);
};

Pixel :: Pixel(int n){
    this->size = n;
    this->capacity = 2 * n;
    this->pixelsize = new char[n];
}

void Pixel :: writePixel(std::ofstream& fout){
        if(!fout.is_open()){
        return;
    }
    fout.write((char*)this->pixelsize, this->size);
}

void Pixel :: copy(const Pixel& other){
    this->capacity = other.capacity;
    this->size = other.size;
    this->pixelsize = new char[other.capacity];
    for(size_t i = 0; i < this->size; i++){
        this->pixelsize[i] = other.pixelsize[i];
    }
}

void Pixel :: erase(){
    delete[]this->pixelsize;
}

void Pixel :: resize(){
    if(this->size >= this->capacity){
        capacity *= 2;
    }
}

Pixel :: Pixel(){
    this->size = 0;
    this->capacity = 4;
    this->pixelsize = new char[capacity];
}

Pixel :: Pixel(const Pixel& other){
    this->copy(other);
}

Pixel& Pixel :: operator = (const Pixel& other){
    if(this != &other){
        this->erase();
        this->copy(other);
    }
    return *this;
}

Pixel :: ~Pixel(){
    this->erase();
}

void Pixel :: push(const char c){
    this->resize();
    this->pixelsize[size++] = c;
}


void Pixel :: readPixel(std::ifstream& fin){
    if(!fin){
        return;
    }
    fin.read((char*)this->pixelsize, this->size);
}


size_t Pixel :: getPixelSize()const{
    return this->size;
}

void Pixel :: printPixel(){
    for(size_t i = 0; i < this->size; i++){
        std::cout<<pixelsize[i];
    }
}


class Rowmap{
   private:
       std::vector<Pixel> pixels;

   public:
       Rowmap();
       Rowmap(int elements, int bits_pixel, int rowsize);
       void readPixelMap(std::ifstream& fin);
       Rowmap& copyRow(int x, int width);
       void print();
       void writePixelmap(std::ofstream& fout);
       void addBits();
       size_t getSize()const;


};

Rowmap& Rowmap :: copyRow(int x, int width){
    Rowmap * temp = new Rowmap();
    for(int i = 0; i < width; i++){
        temp->pixels.push_back(this->pixels[x + i]);
    }
    return *temp;
}

void Rowmap :: addBits(){
    this->pixels.push_back(Pixel(1));
}

size_t Rowmap :: getSize()const{
    return this->pixels.size();
}

void Rowmap :: writePixelmap(std::ofstream& fout){
    if(!fout.is_open())return;


    for(size_t i = 0; i < this->pixels.size(); i++){
        this->pixels[i].writePixel(fout);
    }

}

Rowmap :: Rowmap(){
    this->pixels = std::vector<Pixel>(0);
}

Rowmap :: Rowmap(int elements, int bits_pixel, int rowsize){ //
    int bonusbits = rowsize - (elements * bits_pixel);
    this->pixels = std::vector<Pixel>(elements + bonusbits);
    for(int i = 0; i < elements; i++){
        pixels[i] = Pixel(bits_pixel);
    }
    for(int j = 0; j < bonusbits; j++){
        pixels[elements + j] = Pixel(1);
    }

}


void Rowmap :: readPixelMap(std::ifstream& fin){
    if(!fin)return;


    for(size_t i = 0; i < this->pixels.size(); i++){
        this->pixels[i].readPixel(fin);
    }
}

void Rowmap :: print(){
    for(size_t i = 0; i < this->pixels.size(); i++){
        pixels[i].printPixel();


    }
}


class ArrayofPixels{
private:
    std::vector<Rowmap> rowmaps;

public:
       ArrayofPixels();
       ArrayofPixels(int height, int elements, int bits_pixel, int rowsize);
       void readArray(std::ifstream& fin);//padd
       void printArray();
       ArrayofPixels& copypixels(int y, int height,int x, int width);
       void writeArray(std::ofstream& fout);


};
ArrayofPixels& ArrayofPixels :: copypixels(int y, int height, int x, int width){
    ArrayofPixels * arr = new ArrayofPixels();
    for(int i = 0 ; i < height; i++){
        arr->rowmaps.push_back(this->rowmaps[y + i].copyRow(x, width));
    }
    return * arr;
}

ArrayofPixels :: ArrayofPixels(){
    this->rowmaps = std::vector<Rowmap>(0);
}

ArrayofPixels :: ArrayofPixels(int height,int elements, int bits_pixel, int rowsize){
    this->rowmaps = std::vector<Rowmap>(height);
    for(size_t i = 0; i < this->rowmaps.size(); i++){
        this->rowmaps[i] = Rowmap(elements, bits_pixel, rowsize);
    }
}

void ArrayofPixels :: readArray(std::ifstream& fin){
    if(!fin){
        return;
    }

    for(size_t i = 0; i < this->rowmaps.size(); i++){
        this->rowmaps[i].readPixelMap(fin);
    }

}


void ArrayofPixels :: writeArray(std::ofstream& fout){
    if(!fout.is_open())return;


    for(size_t i = 0; i < this->rowmaps.size(); i++){
        this->rowmaps[i].writePixelmap(fout);
    }
}

void ArrayofPixels :: printArray(){
    for(size_t i = 0; i < this->rowmaps.size(); i++){
        this->rowmaps[i].print();

    }
}

class Bitmap{

private:
    Header header;
    ColorScheme colorscheme;
    ArrayofPixels pixelarr;
public:
    Bitmap();
    Bitmap(std::ifstream& fin);
    void printBitmap();
    void write(std::ofstream& fout);
    void cut(std::ifstream& fin);
    Bitmap& createNew(int x, int y, int width, int height);

};

Bitmap& Bitmap :: createNew(int x, int y, int width, int height){
    Bitmap * b = new Bitmap();
    b->header = this->header;
    b->header.setHeight(height);
    b->header.setWidth(width);
    int filesize = floor(((header.getBitsPerPixel() * width + 31) / 32) * 4) * height + 54;
    int imaagesize = floor(((header.getBitsPerPixel() * width + 31) / 32) * 4);
    b->header.setFileSize(filesize);
    b->header.setImageSize(imaagesize);
    b->pixelarr = this->pixelarr.copypixels(y, height, x, width);
    b->colorscheme = this->colorscheme;
    return * b;

}

Bitmap :: Bitmap(){
    this->header = Header();
    this->colorscheme = ColorScheme();
    this->pixelarr = ArrayofPixels();
}

Bitmap :: Bitmap(std::ifstream& fin){

    header.readHeader(fin);
    colorscheme = ColorScheme(header.getfilesize() - (header.getheadersize() + header.getimagesize() + 14));
    colorscheme.readColorScheme(fin);
    fin.seekg(header.getdataOffset(), fin.beg);
    pixelarr = ArrayofPixels(header.getHeight(), ceil(header.rowSize() / header.getBitsPerPixel()) ,header.getBitsPerPixel(), header.rowSize());
    pixelarr.readArray(fin);


}

void Bitmap :: printBitmap(){
    header.printHeader();
    std::cout<<std::endl;
    colorscheme.printScheme();
    std::cout<<std::endl;
    pixelarr.printArray();

}

void Bitmap :: write(std::ofstream& fout){

        this->header.writeHeader(fout);
        this->colorscheme.writeScheme(fout);
        this->pixelarr.writeArray(fout);


}
 void Bitmap :: cut(std::ifstream& fin){
    std::string currentline;
    while(std::getline(fin,currentline)){
        if(currentline[0] != ';'){

            std::stringstream nums(currentline);
            std::string number;
            std::vector<std::string> vec;
            while(nums >> number){

                vec.push_back(number);
            }

//            for(size_t i = 0; i < vec.size(); i++){
//                std::cout<<vec[i]<<"!";
//            }

             std::string source = vec[0];
             std::string writefile = vec[vec.size() - 1];

             std::string x1 = vec[1];
             int index1 = x1.find("(");
             int index2 = x1.find(",");
             int length = index2 - index1;
             std::string x = x1.substr(index1 + 1, length - 1);

             int xarg = stoi(x);
             //std::cout<<xarg<<std::endl;

              std::string y1 = vec[2];
              int indexy = y1.find(" ");
              int indexy2 = y1.find(",");
              int lengthy = indexy2 - indexy;
              std::string y = y1.substr(0, lengthy - 1);

              int yarg = stoi(y);
              //std::cout<<yarg<<std::endl;

              std::string width = vec[3];
              int indexw = width.find(" ");
              int indexw2 = width.find(",");
              int length2 = indexw2 - indexw;
              std::string wid = width.substr(0, length2 - 1);

              int widtharg = stoi(wid);
              //std::cout<<wid<<std::endl;

              std::string height = vec[4];
              int indexh = height.find(" ");
              int indexh2 = height.find(")");
              int lengthh = indexh2 - indexh;
              std::string heig = height.substr(0, lengthh - 1);

              //std::cout<<heig<<std::endl;

              int heightarg = stoi(heig);

              std::ifstream curfile(source, std::ios::binary);
              std::ofstream curfilewrite(writefile, std::ios::binary);
              Bitmap *temp = new Bitmap(curfile);
              Bitmap  realcut = temp->createNew(xarg, yarg, widtharg, heightarg);
              realcut.write(curfilewrite);

        }
    }
 }

int main()
{
//    std::string name;
//    std::cout<<"Enter file name: ";
//    getline(std::cin,name);
//    while(!fexists(name)){
//        std::cout<<"No file with such name!"<<std::endl;
//        std::cout<<"Enter file name: ";
//        getline(std::cin,name);
//
//    }
//    std::ifstream file(name);
//    std::string currentline;
//    while(std::getline(file,currentline)){
//        if(currentline[0] != ';'){
//
//            int index_first_space;
//            index_first_space = currentline.find(" ");
//            std::string source;
//            source = currentline.substr(0,index_first_space);
//            std::cout<< source <<std::endl;
//            if(!fexists(source)){
//                std::cout<<"File not found!"<<std::endl;
//            }
//            else{
//
//            }
//        }
//        else{
//            std::cout<<0<<std::endl;
//        }
//    }
//
//    std::ifstream fin1("HelloWorld.bmp" , std::ios::binary);
//    std::ofstream fout("picsssq.txt");
//    Header h;
//    h.readHeader(fin1);
//    h.printHeader();
//    std::cout<<h.rowSize()<<std::endl;

//    ColorScheme c(5);
//    std::ifstream fin("test.txt", std::ios::binary);
//    c.readColorScheme(fin);
//    c.printScheme();

//      Pixel p(12);
//
//      std::ifstream fin("test.txt", std::ios::binary);
//      p.readPixel(fin);
//      p.printPixel();
//      std::cout<<p.getPixelSize();

//        Pixelmap p;
//        p.resizePixelmap(4,8);
//        std::ifstream fin("test.txt", std::ios::binary);
//        p.readPixelMap(fin);
//        p.print();
//
//            Rowmap r(6, 4, 24);
//            std::ifstream fin("test2.txt", std::ios::binary);
//            r.readPixelMap(fin);
//            Rowmap b = r.copyRow(3, 2);
//            b.print();
//            Rowmap ftry = r.copyRow(5,5);
//            ftry.print();
           // r.print();

//            Rowmap c;
//            c= r;
//            c.print();


//    std::ifstream fin("HelloWorld.bmp" , std::ios::binary );
//    std::ofstream fout("pic4.bmp", std::ios::binary );
//    Bitmap bit(fin);
//    bit.write(fout);
//    bit.printBitmap();


//    ArrayofPixels p(100,13,32);
//    std::ifstream fin("HelloWorld.bmp", std::ios::binary);
//    std::ofstream fout("test2.bmp", std::ios::binary);//---------------working
//    p.readArray(fin);
//    p.writeArray(fout);
//    p.printArray();
    //NAMERI KAK DA NAMERISH PADINGA SLED VSEKI RED I DA NE GO ZAPISWASH

    Bitmap f;
    std::ifstream fin("test.txt");
    f.cut(fin);

    return 0;
}
