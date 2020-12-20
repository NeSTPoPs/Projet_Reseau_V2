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
  char[] host;
  int accept;
  char[] acceptLanguage;
  char[] connection;
  int acceptEncoding;
  char[] userAgent;
};

#endif
