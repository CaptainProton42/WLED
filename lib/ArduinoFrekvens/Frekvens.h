// Frekvens.h
// Simple library for controlling the IKEA FREKVENS LED panel.
// (c) John Wigg 2023 MIT License

#ifndef FREKVENS_H
#define FREKVENS_H

#include <Arduino.h>


class Frekvens {
	public:
		Frekvens();

		void SetMOSI(uint i_mosi) {m_mosi = i_mosi;}
		void SetSCK(uint i_sck) {m_sck = i_sck;}
		void SetEN(uint i_en) {m_en = i_en;}
		void SetLAK(uint i_lak) {m_lak = i_lak;}
		void SetBaseClock(uint i_baseClock) {m_baseClock = i_baseClock;}
		
		void Init();
		void Update();

		void SetMaxValue(uint8_t const i_bits);
		void SetGamma(float const i_gamma);

		void Clear();
		void SetBitmap(uint8_t const i_bitmap[256]);
		void SetPixel(size_t const i_x, size_t const i_y, uint8_t i_value);
		void SetPixelGamma(int const i_x, int const i_y, float const i_value);

		uint8_t GetPixel(int const i_x, int const i_y) const;

	private:
		uint8_t m_bitmap[256];
		uint8_t m_bit;
		uint8_t m_maxBit;

		float m_gamma;
		float m_maxValue;

		uint m_t1;
		uint m_t2;

		uint m_sck;
		uint m_mosi;
		uint m_en;
		uint m_lak;

		uint m_baseClock;
};

#endif // FREKVENS_H