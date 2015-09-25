
#include "types/sstr.h"

int main(int argc, char **argv)
{
	char *str = "wwwwww";
	char *ssr = "bbbbbb";
	Sstr ssy;
	ssy.append(str, sizeof(str));
	ssy.append(ssr, sizeof(ssr));
}
