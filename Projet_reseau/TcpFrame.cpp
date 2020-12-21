#include "TcpFrame.h"

TcpFrame::TcpFrame()
{
	this->newType("TCP");
	srcPort = -1;
	destPort = -1;
	seqNum = -1;
	ackNum = -1;
	dataOffset = -1;
	flags = -1;
	reserved = -1;
	URG = -1;
	ACK = -1;
	PSH = -1;
	RST = -1;
	SYN = -1;
	FIN = -1;
	window = -1;
	checksum = -1;
	urgentPointer = -1;
	for (int j = 0; j < 16; j++) {
		options[j] = ' ';
	}
	for (int i = 0; i < 63; i++)
		Data[i] = ' ';
	Data[63] = '\0';
}

TcpFrame::TcpFrame(char* chaine)
{
	*this = TcpFrame();
	this->construireData(chaine);
}

void TcpFrame::construireData(char chaine[])
{
	int lecture;
	this->srcPort = fonctionsMaths::hexToDec(&(chaine[0]), 4);
	this->destPort = fonctionsMaths::hexToDec(&(chaine[4]), 4);
	this->seqNum = fonctionsMaths::hexToDec(&(chaine[8]), 8);
	this->ackNum = fonctionsMaths::hexToDec(&(chaine[16]), 8);
	this->dataOffset = fonctionsMaths::hexToDec(&(chaine[24]), 1);
	this->flags = fonctionsMaths::hexToDec(&(chaine[25]), 3);
	lecture = this->flags;
	this->FIN = lecture % 2; lecture = lecture / 2;
	this->SYN = lecture % 2; lecture = lecture / 2;
	this->RST = lecture % 2; lecture = lecture / 2;
	this->PSH = lecture % 2; lecture = lecture / 2;
	this->ACK = lecture % 2; lecture = lecture / 2;
	this->URG = lecture % 2; lecture = lecture / 2;
	this->window = fonctionsMaths::hexToDec(&(chaine[28]), 4);
	this->checksum = fonctionsMaths::hexToDec(&(chaine[32]), 4);
	this->urgentPointer = fonctionsMaths::hexToDec(&(chaine[36]), 4);
	int i = 40;
	int j = 0;
	while ( fonctionsMaths::est_hexadecimal(chaine[i]) ) {
		this->Data[j] = chaine[i];
		j++;
		i++;
	}

}

void TcpFrame::afficherData(const int tabulation)
{
	std::string tableau = std::string(tabulation, '\t');
	char* tab = new char[tableau.length() + 1];
	strcpy(tab, tableau.c_str());

	printf("%s====Transmission Control Protocol====\n", tab);
	printf("%sSource Port: %i\n", tab, this->srcPort);
	printf("%sDestination Port: %i\n", tab, this->destPort);
	printf("%sSequence number: %lu\n", tab, this->seqNum);
	printf("%sAcknowledgment number: %lu\n", tab, this->ackNum);
	printf("%sHeader length : %i octets \n", tab, this->dataOffset);
	printf("%sFlags : 0x%.3x\n", tab, this->flags);
	printf("%s\t..%i. .... = Urgent : ",tab, this->URG);
	if (this->URG == 0) printf("Not ");
	printf("set\n");
	printf("%s\t...%i .... = Acknowledgment: ", tab, this->ACK);
	if (this->ACK == 0) printf("Not ");
	printf("set\n");
	printf("%s\t.... %i... = Push: ", tab, this->PSH);
	if (this->PSH == 0) printf("Not ");
	printf("set\n");
	printf("%s\t.... .%i.. = Reset: ", tab, this->RST);
	if (this->RST == 0) printf("Not ");
	printf("set\n");
	printf("%s\t.... ..%i. = Syn: ", tab, this->SYN);
	if (this->SYN == 0) printf("Not ");
	printf("set\n");
	printf("%s\t.... ...%i = Fin: ", tab, this->FIN);
	if (this->FIN == 0) printf("Not ");
	printf("set\n");
	printf("%sWindow size value : %i\n", tab, this->window);
	printf("%sChecksum: 0x%.4x\n", tab, this->checksum);
	printf("%sUrgent pointer: %i\n", tab, this->urgentPointer);
	delete[] tab;
	return;
}


std::string TcpFrame::toString(int tabulation) {
	std::string tableau = std::string(tabulation, '\t');

	std::string res;

	res.append(tableau); res.append("====Transmission Control Protocol====\n");
	res.append(tableau); res.append("Source Port: "); res.append(std::to_string(this->srcPort)); res.append("\n");
	res.append(tableau); res.append("Destination Port: "); res.append(std::to_string(this->destPort)); res.append("\n");
	res.append(tableau); res.append("Sequence number:"); res.append(std::to_string(this->seqNum)); res.append("\n");
	res.append(tableau); res.append("Acknowledgment number: "); res.append(std::to_string(this->ackNum)); res.append("\n");
	res.append(tableau); res.append("Header length : "); res.append(std::to_string(this->dataOffset)); res.append("\n");res.append(" octets\n");
	res.append(tableau); res.append("Flags : 0x"); res.append(std::to_string(this->flags)); res.append("\n");
	res.append(tableau); res.append("\t..%i. .... = Urgent : "); res.append(std::to_string(this->URG));
	if (this->URG == 0){ res.append("Not "); } res.append("set\n");
	res.append(tableau); res.append("\t...%i .... = Acknowledgment: "); res.append(std::to_string(this->ACK));
	if (this->ACK == 0){ res.append("Not "); } res.append("set\n");
	res.append(tableau); res.append("\t.... %i... = Push:"); res.append(std::to_string(this->PSH));
	if (this->PSH == 0){ res.append("Not ");} res.append("set\n");
	res.append(tableau); res.append("\t.... .%i.. = Reset: "); res.append(std::to_string(this->RST));
	if (this->RST == 0){ res.append("Not ");} res.append("set\n");
	res.append(tableau); res.append("\t.... ..%i. = Syn: "); res.append(std::to_string(this->SYN));
	if (this->SYN == 0){ res.append("Not ");} res.append("set\n");
	res.append(tableau); res.append("	\t.... ...%i = Fin: "); res.append(std::to_string(this->FIN));
	if (this->FIN == 0){ res.append("Not ");}	res.append("set\n");
	res.append(tableau); res.append("Window size value : "); res.append(std::to_string(this->window)); res.append("\n");
	res.append(tableau); res.append("Checksum: 0x"); res.append(std::to_string(this->checksum)); res.append("\n");
	res.append(tableau); res.append("Urgent pointer: "); res.append(std::to_string(this->urgentPointer)); res.append("\n");

	return res;
}
