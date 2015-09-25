

#ifndef _VAR_INT_H_
#define _VAR_INT_H_
#include <stdint.h>
#include <string.h>

inline int32_t atomReadInt32(char *str, bool LE)
{	
	int32_t value = 0x0; 
	char tmp[4];
	int j;
	if(LE){
		memcpy(&tmp, str, sizeof(int32_t));
	}else{
		
		for(j=sizeof(int32_t);j>0;j--)
		{
			tmp[sizeof(int32_t)-j] = str[j];
		}
	}
	for(j=0;j<sizeof(int32_t);j++)
	{
		if(tmp[j] & 128){
			value += (tmp[j] & 127)<<(8*j);
			value += 128<<(8*j);
		}else{
			value += (tmp[j] & 127)<<(8*j);
		}
	}
	return value;
}

inline bool atomPutInt32(char *ptr,int32_t *val, bool LE)
{

	char *tmp;
	tmp = reinterpret_cast<char *>(val);

	if(LE){
		for(int i=0;i<sizeof(int32_t);i++){
			ptr[i] = tmp[i];
		}
	}else{
		for(int i=0;i<sizeof(int32_t);i++){
			ptr[sizeof(int32_t)-i] = tmp[i];
		}
	}
	return true;

}

inline int32_t ReadVarInt32(char *str)
{
	return atomReadInt32(str, true);
}

inline void PutVarInt32(char *dest, int32_t *value)
{
	atomPutInt32(dest, value, true);
}



#endif
