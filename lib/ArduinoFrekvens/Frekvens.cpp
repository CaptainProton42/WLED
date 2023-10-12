// Frekvens.cpp
// Simple library for controlling the IKEA FREKVENS LED panel.
// (c) John Wigg 2023 MIT License

#include "Frekvens.h"

#include <Arduino.h>
#include <SPI.h>

#define SCK 2
#define MOSI 3
#define EN 4
#define LAK 5

#define BASE_CLOCK 120

Frekvens::Frekvens()
	: m_bit(1u)
	, m_maxBit(63u)
	, m_gamma(2.2f)
	, m_maxValue(127.0f)
	, m_sck(2)
	, m_mosi(3)
	, m_en(4)
	, m_lak(5)
	, m_baseClock(120) {};

void Frekvens::SetMaxValue(uint8_t const i_maxValue) {
	m_maxValue = static_cast<float>(i_maxValue);
	m_maxBit = i_maxValue >> 1;
}

void Frekvens::SetGamma(float const i_gamma) {
	m_gamma = i_gamma;
}

void Frekvens::SetBitmap(uint8_t const i_bitmap[256]) {
	memcpy(m_bitmap, i_bitmap, 256);
}

void Frekvens::SetPixel(size_t const i_x, size_t const i_y, uint8_t i_value) {
	m_bitmap[i_x + 16 * i_y] = i_value;
}

void Frekvens::SetPixelGamma(int const i_x, int const i_y, float const i_value) {
	m_bitmap[i_x + 16 * i_y] = static_cast<uint8_t>(round(pow(i_value, m_gamma) * m_maxValue));
}

uint8_t Frekvens::GetPixel(int const i_x, int const i_y) const {
	return m_bitmap[i_x + 16 * i_y];
}

void Frekvens::Clear() {
	memset(m_bitmap, 0, 256);
}

void Frekvens::Init() {
	pinMode(m_lak, OUTPUT);
	pinMode(m_en, OUTPUT);
	//SPI.setTX(m_mosi);
	//SPI.setSCK(m_sck);
	SPI.begin(m_sck, -1, m_mosi);
}

void Frekvens::Update() {
	m_t2 = micros();
	if ( m_t2 - m_t1 > m_baseClock * m_bit )
	{
		m_t1 = m_t2;
		if (m_bit > m_maxBit) m_bit = 1;
		else m_bit = m_bit << 1;

		for (int y = 0; y < 32; ++y) {
			uint8_t line = 0;
			for (int x = 0; x < 8; ++x) {
				int j = y % 16;
				int i = x + 8 * (y / 16);

				if (m_bitmap[i + 16*j] & m_bit)
				{
					line |= (1 << (7-x));
				}
			}
			SPI.transfer(line);
		}
		digitalWrite(m_lak, HIGH);
		digitalWrite(m_lak, LOW);
	}
};