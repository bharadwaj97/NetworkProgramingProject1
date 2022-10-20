

#include"Buffer.h"
using namespace std;

Buffer::Buffer(size_t size) {
	m_Buffer.resize(size);
	m_WriteIndex = 0;
	m_ReadIndex = 0;
}

void Buffer::WriteInt32LE(size_t index, int32_t value) {
	m_Buffer[index] = value;
	m_Buffer[index + 1] = value >> 8;
	m_Buffer[index + 2] = value >> 16;
	m_Buffer[index + 3] = value >> 24;

}

void Buffer::WriteInt32LE(int32_t value) {
	m_Buffer[m_WriteIndex] = value;
	m_Buffer[m_WriteIndex + 1] = value >> 8;
	m_Buffer[m_WriteIndex + 2] = value >> 16;
	m_Buffer[m_WriteIndex + 3] = value >> 24;

}
void Buffer::WriteString(size_t index, uint8_t value) {
	m_Buffer[index] = value;
}

void Buffer::WriteString(uint8_t value) {
	m_Buffer[m_WriteIndex] = value;
}

uint32_t Buffer::ReadUInt32LE(size_t index) {
	uint32_t value = m_Buffer[index];
	value |= m_Buffer[index + 1] << 8;
	value |= m_Buffer[index + 2] << 16;
	value |= m_Buffer[index + 3] << 24;

	return value;
}

uint32_t Buffer::ReadUInt32LE() {
	uint32_t value = m_Buffer[m_ReadIndex];
	value |= m_Buffer[m_ReadIndex + 1] << 8;
	value |= m_Buffer[m_ReadIndex + 2] << 16;
	value |= m_Buffer[m_ReadIndex + 3] << 24;

	return value;
}