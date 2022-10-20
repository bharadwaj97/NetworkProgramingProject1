#pragma once
#include<vector>
#include<string>
class Buffer {
public:
	Buffer(size_t  size);
	void WriteInt32LE(std::size_t index, int32_t value);
	void WriteInt32LE(int32_t value);
	void WriteString(std::size_t index, uint8_t value);
	void WriteString(uint8_t value);

	uint32_t ReadUInt32LE(std::size_t index);
	uint32_t ReadUInt32LE();

	/*
* [m_WriteeIndex++]
* [++m_WriteIndex]
* m_WriteIndex+=4;
*/

private:
	//call m_Buffer.resize in your constructor
	std::vector<uint8_t> m_Buffer;

	//Initialize these at 0
	int m_WriteIndex;
	int m_ReadIndex;


};