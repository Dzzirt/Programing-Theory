#pragma once
#include <vector>
#include <windows.h>


struct Directory {
	std::string path;
	std::vector<std::string>* filenames;
	std::string* supp_formats;
	int current_image;
	bool is_img_changed;
	bool arr_is_pressed;
};

void GetFilenames(std::vector<std::string>& filenames, wchar_t const* path);

void FileNamesInit(std::vector<std::string> & filenames, char*& arg);

void DirectoryInit(Directory & dir, char*& arg);

void DestroyDirectory(Directory *& directory);