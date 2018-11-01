#include <iostream>
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
    int pixelArraysize();
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
    int realsize(int n);


};

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

    fin.read((char*)this , sizeof(Header));


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

int Header :: pixelArraysize(){
    int rows = floor((this->bits_per_pixel * width + 31)/32) * 4;
    int pixelarray = rows * abs(height);
    return pixelarray;
}

//int Header :: realsize(int n){
//    stigam do redowe i togava delq na broiq na bitowe w edin piksel i zakruglqm, sled tova subiram wsichki redowe flornati i umnojavam s height;
//    return 1;
//}

void Header :: writeHeader(std::ofstream &fout){

    if(!fout.is_open()){return;}
    fout.write((const char*)this, sizeof(Header));
    fout.close();
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
        ColorScheme(const ColorScheme& other);
        ColorScheme& operator = (const ColorScheme& other);
        ~ColorScheme();
        void push(const char c);
        void pushNElements(int num);
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

void ColorScheme :: pushNElements(int num){
    for(int i = 0; i < num; i++){
        this->push('a');
    }
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
        Pixel(const Pixel& other);
        Pixel& operator = (const Pixel& other);
        ~Pixel();
        void readPixel(std::ifstream &fin);
        void push(const char c);
        void pushNElements(int n);
        size_t getPixelSize()const;
        void printPixel();
        void writePixel(std::ofstream& fout);
};

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

void Pixel :: pushNElements(int num){
    for(int i = 0; i < num; i++){
        this->push('a');
    }
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



class Pixelmap{
   private:
       std::vector<Pixel> pixels;
   public:
       Pixelmap();
       void resizePixelmap(int elements, int bits_pixel);
       void readPixelMap(std::ifstream& fin);
       void print();
       void writePixelmap(std::ofstream& fout);



};

void Pixelmap :: writePixelmap(std::ofstream& fout){
    if(!fout.is_open())return;


    for(size_t i = 0; i < this->pixels.size(); i++){
        this->pixels[i].writePixel(fout);
    }
}

Pixelmap :: Pixelmap(){
    this->pixels = std::vector<Pixel>(0);
}

void Pixelmap :: resizePixelmap(int elements, int bits_pixel){
    this->pixels = std::vector<Pixel>(elements);
    for(size_t i = 0; i < this->pixels.size(); i++){
        pixels[i].pushNElements(bits_pixel);
    }


}

void Pixelmap :: readPixelMap(std::ifstream& fin){
    if(!fin)return;


    for(size_t i = 0; i < this->pixels.size(); i++){
        this->pixels[i].readPixel(fin);
    }
}

void Pixelmap :: print(){
    for(size_t i = 0; i < this->pixels.size(); i++){
        pixels[i].printPixel();
        std::cout<<std::endl;
    }
}
class Bitmap{

private:
    Header header;
    ColorScheme colorscheme;
    Pixelmap pixelarr;
public:
    Bitmap(std::ifstream& fin);
    void printBitmap();
    void write(std::ofstream& fout);

};

Bitmap :: Bitmap(std::ifstream& fin){

    header.readHeader(fin);
    colorscheme.push(header.getfilesize() - (header.getheadersize() + header.getimagesize() + 14));
    colorscheme.readColorScheme(fin);
    pixelarr.resizePixelmap(header.getimagesize() / header.getBitsPerPixel(),header.getBitsPerPixel());
    pixelarr.readPixelMap(fin);
}

void Bitmap :: printBitmap(){
    header.printHeader();
    std::cout<<std::endl;
    colorscheme.printScheme();
    std::cout<<std::endl;
    pixelarr.print();

}

void Bitmap :: write(std::ofstream& fout){

        this->header.writeHeader(fout);
        this->colorscheme.writeScheme(fout);
        this->pixelarr.writePixelmap(fout);


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
//    std::ifstream fin("45013082_245809212757397_965008924400943104_n.bmp" , std::ios::binary);
//    Header h;
//    h.readHeader(fin);
//    h.printHeader();
//    std::cout<<h.pixelArraysize()<<std::endl;

//    ColorScheme c;
//    c.pushNElements(5);
//    std::ifstream fin("test.txt", std::ios::binary);
//    c.readColorScheme(fin);
//    c.printScheme();

//      Pixel p;
//      p.pushNElements(5);
//      std::ifstream fin("test.txt", std::ios::binary);
//      p.readPixel(fin);
//      p.printPixel();
//      std::cout<<p.getPixelSize();

//        Pixelmap p;
//        p.resizePixelmap(4,8);
//        std::ifstream fin("test.txt", std::ios::binary);
//        p.readPixelMap(fin);
//        p.print();

    std::ifstream fin("45013082_245809212757397_965008924400943104_n.bmp" , std::ios::binary);
    std::ofstream fout("plswork.txt", std::ios::binary);
    Bitmap bit(fin);
    bit.write(fout);
    bit.printBitmap();

    return 0;
}
