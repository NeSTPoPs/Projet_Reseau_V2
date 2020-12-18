#ifndef DEF_IPFRAME
#define DEF_IPFRAME

#include "Data.h"
#include "IcmpFrame.h"
#include "TcpFrame.h"

class IpFrame : public Data
{
public:
	IpFrame();
	IpFrame(char* chaine);
	~IpFrame();
	std::string lire();
	void construireData(char chaine[]);
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
	IcmpFrame* icmpF;
};

#endif
