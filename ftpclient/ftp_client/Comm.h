#pragma once

class Comm
{
private:
	SOCKET m_sockComm;

public:
	Comm(void);
	~Comm(void);

	SOCKET SockComm() const { return m_sockComm; }
	void SockComm(SOCKET val) { m_sockComm = val; }
};
