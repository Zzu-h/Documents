```c++
void Sbox::extended_euclid(uint8_t t) {
	uint8_t a = polynomial[ver], b = t % polynomial[ver];

	xyr[0] = 1;
	xyr[1] = 0;
	xyr[2] = a;

	if ((a == b)|| (b == 0)) 
		return;
	else {
		int xyr2[3] = { 0, 1, b };
		int xyr_t[3] = { 0, };

		while (xyr2[2] != 0) {
			int q = xyr[2] / xyr2[2];

			for (size_t i = 0; i < 3; i++)
				xyr_t[i] = (xyr[i] - q * xyr2[i]);

			for (size_t i = 0; i < 3; i++)
				xyr[i] = xyr2[i];
			for (size_t i = 0; i < 3; i++)
				xyr2[i] = xyr_t[i];
		}
		return;
	}
}
uint8_t Sbox::get_m_inv(uint8_t a) {
	extended_euclid(a);
	if (xyr[2] != 1)
		return 0;
	else
		while (xyr[1] < 0)
			xyr[1] += polynomial[ver];
		return xyr[1] % polynomial[ver];
}
```