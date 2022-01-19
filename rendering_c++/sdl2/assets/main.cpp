#include <string>
#include <vector>
#include <fstream>
#include <iostream>

// this makes me cry
#include <stdio.h>
#include <errno.h>
#include <cstring>




class AssetPNG
{
public:
    AssetPNG(std::string _file_path): file_path(_file_path)
    {
        _read();
        _verify();
    }

    ~AssetPNG()
    {
        // Clear and delete the vector
        // to avoid memory leaks
        buffer->clear();
        delete buffer;
    }


private:
    int asset_size_x;
    int asset_size_y;
    std::string file_path;
    std::vector<unsigned char> *buffer;

    /*
     * Function makes opens and reads a
     * file, handling errors.
     */
    void _read()
    {
        std::ifstream fd(file_path, std::ios::binary);
        if(!fd)
        {
            fprintf(stderr, "Failed to open asset file: '%s'\n", file_path.c_str());
            exit(ENOENT);
        }
        buffer = new std::vector<unsigned char>(std::istreambuf_iterator<char>(fd), {});
        fd.close();
    }

    void _verify()
    {
        if ((*buffer)[1] != 'P' || (*buffer)[2] != 'N' || (*buffer)[3] != 'G')
        {
            fprintf(stderr, "ERROR: Asset file is not a png!");
            exit(EINVAL);
        }
    }
};


int main(int argc, char** argv)
{
    std::string asset_file = argv[1];
    // NOTE: should find a better way of doing this
    AssetPNG(asset_file.c_str());
}
