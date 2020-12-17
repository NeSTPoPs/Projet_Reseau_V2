#ifndef DEF_IPFRAME
#define DEF_IPFRAME

#include "Data.h"

class IpFrame : public Data
{
public:
	IpFrame();
	~IpFrame();
	std::string lire();
	const char * strProtocol();
	void construireData(char chaine[], int type);
	void afficherData(const int tabulation);
private:
	int version;
	int ihl;
	int tos;
	int totalLength;
	int identification;
	int flags;
	int fragmentOffset;
	int ttl;
	int protocol;
	int headerChecksum;
	int srcAdd[4];
	int destAdd[4];
	int options;
	Data* d;
};

#endif
