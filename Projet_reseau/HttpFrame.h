#ifndef DEF_HTTPFRAME
#define DEF_HTTPFRAME

#include "Data.h"

class HttpFrame : public Data
{
public:
	HttpFrame();
	HttpFrame(char* chaine);
	~HttpFrame();
	void construireData(char chaine[]);
	void afficherData(const int tabulation);
private:
  char host[30];
  int accept;
  char acceptLanguage[30];
  char connection[30];
  int acceptEncoding;
  char userAgent[30];
};

#endif
