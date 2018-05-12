#include "PictureLoad.hpp"
#include <png.h>
#include <pngconf.h>
#include <type_traits>
#include <tuple>

namespace {
	template<typename Func, std::enable_if_t<
		std::is_same<
			decltype(std::declval<Func>()(std::declval<png_image*>()), std::true_type{}),
			std::true_type>::value, 
		std::nullptr_t
	> = nullptr>
	std::tuple<std::vector<BYTE>, std::uint32_t, std::uint32_t> Read(Func&& png_image_begin_read) {
		std::vector<BYTE> Data;
		png_image png{};
		png.version = PNG_IMAGE_VERSION;
		png_image_begin_read(&png);
		if (PNG_IMAGE_FAILED(png)) throw std::runtime_error(png.message);
		uint32_t stride = PNG_IMAGE_ROW_STRIDE(png);
		Data.resize(PNG_IMAGE_BUFFER_SIZE(png, stride));
		png_image_finish_read(&png, NULL, reinterpret_cast<void*>(Data.data()), stride, nullptr);
		const std::uint32_t w = png.width, h = png.height;
		png_image_free(&png);
		return { Data, w, h };
	}
}

PngImage::PngImage(const std::string FilePath) {
	std::tie(this->Data, this->Width, this->Height) = Read([&FilePath](png_image* png) { png_image_begin_read_from_file(png, FilePath.c_str()); });
}

PngImage::PngImage(void* PngImage, size_t Size) {
	std::tie(this->Data, this->Width, this->Height) = Read([PngImage, Size](png_image* png) { png_image_begin_read_from_memory(png, PngImage, Size); });
}

