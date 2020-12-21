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
	std::cout << this->toString(tabulation);
	return;
}


std::string TcpFrame::toString(int tabulation) {
	std::string tableau = std::string(tabulation, '\t');

	std::string res;
	std::stringstream stream;

	res.append(tableau); res.append("====Transmission Control Protocol====\n");
	res.append(tableau); res.append("Source Port: "); res.append(std::to_string(this->srcPort)); res.append("\n");
	res.append(tableau); res.append("Destination Port: "); res.append(std::to_string(this->destPort)); res.append("\n");
	res.append(tableau); res.append("Sequence number:"); res.append(std::to_string(this->seqNum)); res.append("\n");
	res.append(tableau); res.append("Acknowledgment number: "); res.append(std::to_string(this->ackNum)); res.append("\n");
	res.append(tableau); res.append("Header length : "); res.append(std::to_string(this->dataOffset)); res.append(" octets\n");

	stream << std::hex << std::setw(3) << std::setfill('0') << this->flags;

	res.append(tableau); res.append("Flags : 0x"); res.append(stream.str()); res.append("\n");
	res.append(tableau); res.append("\t.."); res.append(std::to_string(this->URG)); res.append(". .... = Urgent : ");
	if (this->URG == 0) { res.append("Not "); } res.append("set\n");
	res.append(tableau); res.append("\t..."); res.append(std::to_string(this->ACK)); res.append(" .... = Acknowledgment: ");
	if (this->ACK == 0) { res.append("Not "); } res.append("set\n");
	res.append(tableau); res.append("\t.... "); res.append(std::to_string(this->PSH)); res.append("... = Push: ");
	if (this->PSH == 0) { res.append("Not "); } res.append("set\n");
	res.append(tableau); res.append("\t.... ."); res.append(std::to_string(this->RST)); res.append(".. = Reset: ");
	if (this->RST == 0) { res.append("Not "); } res.append("set\n");
	res.append(tableau); res.append("\t.... .."); res.append(std::to_string(this->SYN)); res.append(". = Syn: ");
	if (this->SYN == 0) { res.append("Not "); } res.append("set\n");
	res.append(tableau); res.append("\t.... ..."); res.append(std::to_string(this->FIN)); res.append(" = Fin: ");
	if (this->FIN == 0) { res.append("Not "); }	res.append("set\n");
	res.append(tableau); res.append("Window size value : "); res.append(std::to_string(this->window)); res.append("\n");
	stream.str("");
	stream << std::hex << std::setw(4) << std::setfill('0') << this->checksum;
	res.append(tableau); res.append("Checksum: 0x"); res.append(stream.str()); res.append("\n");
	res.append(tableau); res.append("Urgent pointer: "); res.append(std::to_string(this->urgentPointer)); res.append("\n");

	return res;
}
