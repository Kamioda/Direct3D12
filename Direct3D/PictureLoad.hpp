#ifndef __PICTURELOAD_HPP__
#define __PICTURELOAD_HPP__
#include <Windows.h>
#include <string>
#include <vector>

class PngImage {
private:
	uint32_t Width, Height;
	std::vector<BYTE> Data;
	typedef std::vector<BYTE>::iterator iterator;
	typedef std::vector<BYTE>::const_iterator const_iterator;
	typedef std::vector<BYTE>::reverse_iterator reverse_iterator;
	typedef std::vector<BYTE>::const_reverse_iterator const_reverse_iterator;
public:
	PngImage() = default;
	PngImage(const std::string GraphPath);
	PngImage(void* PngImage, size_t Size);
	unsigned int GetWidth() const noexcept { return this->Width; }
	unsigned int GetHeight() const noexcept { return this->Height; }
	BYTE operator [] (const size_t Count) const { return this->Data.at(Count); }
	std::vector<BYTE> operator * () const { return this->Data; }
	size_t size() const noexcept { return this->Data.size(); }
	iterator begin() noexcept { return this->Data.begin(); }
	const_iterator begin() const noexcept { return this->Data.begin(); }
	iterator end() noexcept { return this->Data.end(); }
	const_iterator end() const noexcept { return this->Data.end(); }
	const_iterator cbegin() const noexcept { return this->Data.cbegin(); }
	const_iterator cend() const noexcept { return this->Data.cend(); }
	reverse_iterator rbegin() noexcept { return this->Data.rbegin(); }
	const_reverse_iterator rbegin() const noexcept { return this->Data.rbegin(); }
	reverse_iterator rend() noexcept { return this->Data.rend(); }
	const_reverse_iterator rend() const noexcept { return this->Data.rend(); }
	const_reverse_iterator crbegin() const noexcept { return this->Data.crbegin(); }
	const_reverse_iterator crend() const noexcept { return this->Data.crend(); }
};

class JpgImage {
private:
	unsigned int Width, Height;
	int Depth;
	std::vector<BYTE> Data;
	typedef std::vector<BYTE>::iterator iterator;
	typedef std::vector<BYTE>::const_iterator const_iterator;
	typedef std::vector<BYTE>::reverse_iterator reverse_iterator;
	typedef std::vector<BYTE>::const_reverse_iterator const_reverse_iterator;
public:
	JpgImage() = default;
	JpgImage(const std::string FilePath);
	unsigned int GetWidth() const noexcept { return this->Width; }
	unsigned int GetHeight() const noexcept { return this->Height; }
	int GetDepth() const noexcept { return this->Depth; }
	BYTE operator [] (const size_t Count) const { return this->Data.at(Count); }
	std::vector<BYTE> operator * () const { return this->Data; }
	size_t size() const noexcept { return this->Data.size(); }
	iterator begin() noexcept { return this->Data.begin(); }
	const_iterator begin() const noexcept { return this->Data.begin(); }
	iterator end() noexcept { return this->Data.end(); }
	const_iterator end() const noexcept { return this->Data.end(); }
	const_iterator cbegin() const noexcept { return this->Data.cbegin(); }
	const_iterator cend() const noexcept { return this->Data.cend(); }
	reverse_iterator rbegin() noexcept { return this->Data.rbegin(); }
	const_reverse_iterator rbegin() const noexcept { return this->Data.rbegin(); }
	reverse_iterator rend() noexcept { return this->Data.rend(); }
	const_reverse_iterator rend() const noexcept { return this->Data.rend(); }
	const_reverse_iterator crbegin() const noexcept { return this->Data.crbegin(); }
	const_reverse_iterator crend() const noexcept { return this->Data.crend(); }
};
#endif
