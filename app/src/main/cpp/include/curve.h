#ifndef __HEADER_CURVE_H
#define __HEADER_CURVE_H

static unsigned char SM2_SystemParameter[]={
		0x00, 0x00, 0x00, 0x01, 0x72, 0x35, 0x09, 0x75,
		0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03,
		0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x72, 0x03, 0xdf, 0x6b, 0x21, 0xc6, 0x05, 0x2b, 0x53, 0xbb, 0xf4, 0x09, 0x39, 0xd5, 0x41, 0x23,
		0x1e, 0xb5, 0xe4, 0x12, 0xa2, 0x2b, 0x3d, 0x3b, 0x62, 0x0f, 0xc8, 0x4c, 0x3a, 0xff, 0xe0, 0xd4, 0x34, 0x64, 0x50, 0x4a, 0xde, 0x6f, 0xa2, 0xfa, 0x90, 0x11, 0x92, 0xaf, 0x7c, 0x11, 0x4f, 0x20,
		0xff, 0xff, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc,
		0x91, 0x16, 0x7a, 0x5e, 0xe1, 0xc1, 0x3b, 0x05, 0xd6, 0xa1, 0xed, 0x99, 0xac, 0x24, 0xc3, 0xc3, 0x3e, 0x79, 0x81, 0xed, 0xdc, 0xa6, 0xc0, 0x50, 0x61, 0x32, 0x89, 0x90, 0xf4, 0x18, 0x02, 0x9e,
		0x63, 0xcd, 0x65, 0xd4, 0x81, 0xd7, 0x35, 0xbd, 0x8d, 0x4c, 0xfb, 0x06, 0x6e, 0x2a, 0x48, 0xf8, 0xc1, 0xf5, 0xe5, 0x78, 0x8d, 0x32, 0x95, 0xfa, 0xc1, 0x35, 0x4e, 0x59, 0x3c, 0x2d, 0x0d, 0xdd,
		0xc9, 0xe6, 0x50, 0x40, 0x56, 0x8b, 0x4c, 0x56, 0x68, 0x00, 0xf6, 0x96, 0x51, 0x9b, 0x4c, 0x35, 0x2b, 0xf7, 0x13, 0x0e, 0x91, 0x54, 0xd3, 0x77, 0x7b, 0x9f, 0x56, 0x1a, 0x8a, 0x91, 0x4b, 0x50,
		0x63, 0x56, 0xcf, 0x46, 0x8c, 0x16, 0x67, 0x47, 0x1f, 0xff, 0x9e, 0x3d, 0x40, 0x56, 0x2e, 0x5f, 0x78, 0x1a, 0x12, 0xf6, 0xe2, 0x11, 0xce, 0x1e, 0x30, 0x70, 0x6e, 0x00, 0x6d, 0x98, 0xa3, 0x31,
		0x5c, 0x01, 0xaf, 0x69, 0xa3, 0x03, 0xef, 0x24, 0xfa, 0x0b, 0xd6, 0xc0, 0x07, 0xf7, 0xce, 0xb5, 0x38, 0x25, 0xd8, 0x0c, 0x66, 0xf7, 0x5b, 0x0d, 0x96, 0xc4, 0xe4, 0xf3, 0x89, 0x75, 0x18, 0xd9,
		0x6f, 0x35, 0x08, 0x80, 0x16, 0x8c, 0xcb, 0x86, 0x51, 0x93, 0x62, 0xc6, 0x95, 0x37, 0x34, 0x21, 0x8b, 0xfe, 0x4a, 0x53, 0x24, 0x8d, 0xce, 0xae, 0xdd, 0x75, 0xcf, 0x9e, 0x6b, 0xfc, 0xbc, 0x92,
		0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC,//a
		0x28, 0xE9, 0xFA, 0x9E, 0x9D, 0x9F, 0x5E, 0x34, 0x4D, 0x5A, 0x9E, 0x4B, 0xCF, 0x65, 0x09, 0xA7, 0xF3, 0x97, 0x89, 0xF5, 0x15, 0xAB, 0x8F, 0x92, 0xDD, 0xBC, 0xBD, 0x41, 0x4D, 0x94, 0x0E, 0x93,//b
		0x32, 0xC4, 0xAE, 0x2C, 0x1F, 0x19, 0x81, 0x19, 0x5F, 0x99, 0x04, 0x46, 0x6A, 0x39, 0xC9, 0x94, 0x8F, 0xE3, 0x0B, 0xBF, 0xF2, 0x66, 0x0B, 0xE1, 0x71, 0x5A, 0x45, 0x89, 0x33, 0x4C, 0x74, 0xC7,//GX
		0xBC, 0x37, 0x36, 0xA2, 0xF4, 0xF6, 0x77, 0x9C, 0x59, 0xBD, 0xCE, 0xE3, 0x6B, 0x69, 0x21, 0x53, 0xD0, 0xA9, 0x87, 0x7C, 0xC6, 0x2A, 0x47, 0x40, 0x02, 0xDF, 0x32, 0xE5, 0x21, 0x39, 0xF0, 0xA0,//GY

};
#endif