#include "../Headers/directory.h"

using namespace std;

void DirectoryInit(Directory& dir, char*& arg) {
	dir.path = arg;
	dir.filenames = new vector<string>;
	dir.current_image = 0;
	dir.is_img_changed = false;
	dir.arr_is_pressed = false;
	FileNamesInit(*dir.filenames, arg);
}

void DestroyDirectory(Directory*& directory) {
	delete directory->filenames;
	delete directory->supp_formats;
	delete directory;
}

void FileNamesInit(vector<string>& filenames, char*& arg) {

	string arg_path = arg;
	wstring path(arg_path.begin(), arg_path.end());
	path += wchar_t('\\');
	path += wchar_t('*');
	GetFilenames(filenames, path.c_str());

}

void GetFilenames(vector<string>& filenames, wchar_t const* path) {
	WIN32_FIND_DATAW data;
	HANDLE const hFind = FindFirstFileW(path, &data);
	while (NULL != FindNextFileW(hFind, &data)) {
		wchar_t* w_filename = &data.cFileName[0];
		if (!(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
			wstring ws(w_filename);
			string filename(ws.begin(), ws.end());
			filenames.push_back(filename);
		}
	}
	FindClose(hFind);
}
