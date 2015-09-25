


#ifndef _SSTR_H_
#define _SSTR_H_
#include <string>
#include <stdlib.h>

class Sstr
{

public:
	Sstr() { _Data = ""; _Size = 0;}
	Sstr(char *data, int size) { _Data=data; _Size=size; }
	~Sstr() { free(_Data); }

	char *data() { return _Data;}
	int size() { return _Size;}

private:
	char *_Data;
	size_t _Size;

public:

	void append(char *data, size_t size){
		char *_tmp;
		if(_Size == 0){
			_tmp = (char *)malloc(size);
			_Data = _tmp;
		}else{
			_tmp = (char *)realloc(_Data,_Size+size);
			if(_tmp != NULL){
				_Data = _tmp;
			}
			_tmp += _Size;
		}
		_Size += size;
		memset(_tmp, 0, size);
		memcpy(_tmp, data, size);
	}
};

#endif
