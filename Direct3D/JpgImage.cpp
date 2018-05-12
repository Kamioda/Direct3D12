#include "PictureLoad.hpp"
#include <jpeglib.h>
#include <Shlwapi.h>

JpgImage::JpgImage(const std::string FilePath) {
	if (FALSE == PathFileExistsA(FilePath.c_str())) throw std::runtime_error(FilePath + " : file is not found.");
	jpeg_decompress_struct info;
	jpeg_error_mgr jerr;
	FILE* fp;
	info.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&info);
	if (0 != fopen_s(&fp, FilePath.c_str(), "rb")) throw std::runtime_error(FilePath + " : failed to open file.");
	jpeg_stdio_src(&info, fp);
	jpeg_read_header(&info, TRUE);
	this->Depth = info.num_components;
	if (0 == this->Depth) throw std::runtime_error("color components error.");
	this->Width = info.image_width;
	this->Height = info.image_height;
	if (0 == this->Width || 0 == this->Height) throw std::runtime_error("image size error.");
	jpeg_start_decompress(&info);
	JSAMPARRAY Buf = (*info.mem->alloc_sarray)((j_common_ptr)&info, JPOOL_IMAGE, this->Width * this->Depth, (JDIMENSION)1);
	BYTE* image = new BYTE[this->Width * this->Height * static_cast<unsigned int>(this->Depth)];
	BYTE* dest = image;
	BYTE* src{};
	while (info.output_scanline < static_cast<unsigned int>(this->Height)) {
		jpeg_read_scanlines(&info, Buf, 1);
		src = Buf[0];
		for (unsigned int i = 0; i < this->Width * this->Height; i++) *dest++ = *src++;
	}
	jpeg_finish_decompress(&info);
	jpeg_destroy_decompress(&info);
	fclose(fp);
	this->Data.resize(this->Width * this->Height * static_cast<unsigned int>(this->Depth));
	for (unsigned int i = 0; i < this->Width * this->Height * static_cast<unsigned int>(this->Depth); i++) this->Data[i] = std::move(image[i]);
	delete[] src;
	delete[] dest;
	delete[] image;
}
