#include <string>
#include <vector>
#include <fstream>
#include <iostream>

// this makes me cry
#include <stdio.h>




class AssetPNG
{
public:
    AssetPNG(std::string _file_path): file_path(_file_path)
    {

        _read_and_verify();
        // std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(fd), {});



    }
    ~AssetPNG()
    {
        // clear / delete the vector here
    }


private:
    int asset_size_x;
    int asset_size_y;
    std::string file_path;
    std::vector<unsigned char> *buffer;

    void _read_and_verify()
    {
        std::ifstream fd(file_path, std::ios::binary);
        if(!fd)
        {
            fprintf(stderr, "Failed to open asset file: %s\n", file_path.c_str());
        }
        buffer = new std::vector<unsigned char>(std::istreambuf_iterator<char>(fd), {});
        fd.close();

        std::cout << "size: " << buffer->size() << std::endl;
        // for (const unsigned char& b: buffer)
            // std::cout << b;

    }
    void _get_size()
    {
    }

};


int main(int argc, char** argv)
{
    AssetPNG("../small.png");
}
