//----------------------------------------------------------------------------
//
//    프로그램명 : 
//
//    만든이     : Han Cheol Cho 
//
//    날  짜     : 2006. 9. 18
//
//    파일명     : PHanFont.h
//
//    내  용     : 
//
//----------------------------------------------------------------------------
/*

  06.08.18  최초 작성


*/


#ifndef _PHANFONTENG_H_
#define _PHANFONTENG_H_


#ifdef   PHANFONTENG_LOCAL
#define  EXT_PHANFONTENG_DEF 
#else
#define  EXT_PHANFONTENG_DEF     extern
#endif

#include "Define.h"


#ifdef   PHANFONTENG_LOCAL


/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
const U8 wEngFon[0x060][16] =
{
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //0x20
{0x00, 0x18, 0x3C, 0x3C, 0x3C, 0x3C, 0x18, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00}, //0x21 '!'
{0x00, 0x36, 0x36, 0x12, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //0x22 '"'
{0x00, 0x36, 0x36, 0x37, 0x3E, 0x76, 0x36, 0x37, 0x3E, 0x76, 0x36, 0x36, 0x36, 0x00, 0x00, 0x00}, //0x23 '#'
{0x00, 0x14, 0x3E, 0x55, 0x55, 0x34, 0x1C, 0x16, 0x15, 0x55, 0x55, 0x3E, 0x14, 0x00, 0x00, 0x00}, //0x24 '$'
{0x00, 0x63, 0x63, 0x66, 0x66, 0x0C, 0x0C, 0x18, 0x18, 0x33, 0x33, 0x63, 0x63, 0x00, 0x00, 0x00}, //0x25 '%'
{0x00, 0x38, 0x6C, 0x6C, 0x64, 0x30, 0x30, 0x5B, 0x5B, 0x6D, 0x6D, 0x66, 0x3B, 0x00, 0x00, 0x00}, //0x26 '&'
{0x00, 0x30, 0x30, 0x10, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //0x27
{0x00, 0x06, 0x0C, 0x18, 0x18, 0x30, 0x30, 0x30, 0x30, 0x18, 0x18, 0x0C, 0x06, 0x00, 0x00, 0x00}, //0x28
{0x00, 0x30, 0x18, 0x0C, 0x0C, 0x06, 0x06, 0x06, 0x06, 0x0C, 0x0C, 0x18, 0x30, 0x00, 0x00, 0x00}, //0x29
{0x00, 0x00, 0x18, 0x18, 0xDB, 0x7E, 0x3C, 0x7E, 0xDB, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00}, //0x2A
{0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x7E, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //0x2B
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x60, 0x20, 0x40, 0x00}, //0x2C
{0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //0x2D
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x60, 0x00, 0x00}, //0x2E
{0x00, 0x03, 0x03, 0x06, 0x06, 0x0C, 0x0C, 0x18, 0x18, 0x30, 0x30, 0x60, 0x60, 0x60, 0x00, 0x00}, //0x2F
{0x00, 0x3E, 0x67, 0x67, 0x67, 0x6B, 0x6B, 0x6B, 0x6B, 0x73, 0x73, 0x73, 0x3E, 0x00, 0x00, 0x00}, //0x30 '0'
{0x00, 0x0C, 0x1C, 0x3C, 0x6C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x00, 0x00, 0x00}, //0x31 '1'
{0x00, 0x3E, 0x63, 0x63, 0x63, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x60, 0x60, 0x7F, 0x00, 0x00, 0x00}, //0x32 '2'
{0x00, 0x3E, 0x63, 0x63, 0x63, 0x03, 0x1E, 0x03, 0x03, 0x63, 0x63, 0x63, 0x3E, 0x00, 0x00, 0x00}, //0x33 '3'
{0x00, 0x18, 0x18, 0x18, 0x30, 0x36, 0x36, 0x66, 0x66, 0x7F, 0x06, 0x06, 0x06, 0x00, 0x00, 0x00}, //0x34 '4'
{0x00, 0x7F, 0x60, 0x60, 0x60, 0x7E, 0x03, 0x03, 0x03, 0x63, 0x63, 0x63, 0x3E, 0x00, 0x00, 0x00}, //0x35 '5'
{0x00, 0x0E, 0x18, 0x30, 0x30, 0x60, 0x7E, 0x63, 0x63, 0x63, 0x63, 0x63, 0x3E, 0x00, 0x00, 0x00}, //0x36 '6'
{0x00, 0x7F, 0x03, 0x06, 0x06, 0x0C, 0x0C, 0x18, 0x18, 0x30, 0x30, 0x60, 0x60, 0x00, 0x00, 0x00}, //0x37 '7'
{0x00, 0x3E, 0x63, 0x63, 0x63, 0x63, 0x3E, 0x63, 0x63, 0x63, 0x63, 0x63, 0x3E, 0x00, 0x00, 0x00}, //0x38 '8'
{0x00, 0x3E, 0x63, 0x63, 0x63, 0x63, 0x63, 0x3F, 0x03, 0x06, 0x06, 0x0C, 0x18, 0x00, 0x00, 0x00}, //0x39 '9'
{0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //0x3A
{0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x18, 0x18, 0x08, 0x10, 0x00, 0x00, 0x00, 0x00}, //0x3B
{0x00, 0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0xC0, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x00, 0x00}, //0x3C
{0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x00, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //0x3D
{0x00, 0xC0, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0xC0, 0x00, 0x00}, //0x3E
{0x00, 0x3E, 0x63, 0x63, 0x63, 0x06, 0x0C, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00}, //0x3F
{0x00, 0x1C, 0x22, 0x59, 0x45, 0x4D, 0x55, 0x55, 0x55, 0x4D, 0x47, 0x22, 0x1C, 0x00, 0x00, 0x00}, //0x40
{0x00, 0x08, 0x1C, 0x36, 0x63, 0x63, 0x63, 0x7F, 0x7F, 0x63, 0x63, 0x63, 0x63, 0x00, 0x00, 0x00}, //0x41 'A'
{0x00, 0x7E, 0x63, 0x63, 0x63, 0x63, 0x7E, 0x63, 0x63, 0x63, 0x63, 0x63, 0x7E, 0x00, 0x00, 0x00}, //0x42
{0x00, 0x3E, 0x63, 0x63, 0x63, 0x60, 0x60, 0x60, 0x60, 0x63, 0x63, 0x63, 0x3E, 0x00, 0x00, 0x00}, //0x43
{0x00, 0x7C, 0x66, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x66, 0x7C, 0x00, 0x00, 0x00}, //0x44
{0x00, 0x7F, 0x60, 0x60, 0x60, 0x60, 0x7E, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7F, 0x00, 0x00, 0x00}, //0x45
{0x00, 0x7F, 0x60, 0x60, 0x60, 0x60, 0x7E, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x00, 0x00, 0x00}, //0x46
{0x00, 0x3E, 0x63, 0x63, 0x63, 0x60, 0x60, 0x6F, 0x63, 0x63, 0x63, 0x63, 0x3E, 0x00, 0x00, 0x00}, //0x47
{0x00, 0x63, 0x63, 0x63, 0x63, 0x63, 0x7F, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x00, 0x00, 0x00}, //0x48
{0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00}, //0x49
{0x00, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x00, 0x00, 0x00}, //0x4A
{0x00, 0x63, 0x66, 0x6C, 0x78, 0x70, 0x78, 0x6C, 0x6C, 0x66, 0x66, 0x63, 0x63, 0x00, 0x00, 0x00}, //0x4B
{0x00, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7F, 0x00, 0x00, 0x00}, //0x4C
{0x00, 0x41, 0x63, 0x63, 0x77, 0x7F, 0x6B, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x00, 0x00, 0x00}, //0x4D
{0x00, 0x63, 0x63, 0x73, 0x73, 0x7B, 0x7B, 0x6F, 0x6F, 0x67, 0x67, 0x63, 0x63, 0x00, 0x00, 0x00}, //0x4E
{0x00, 0x3E, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x3E, 0x00, 0x00, 0x00}, //0x4F
{0x00, 0x7E, 0x63, 0x63, 0x63, 0x63, 0x7E, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x00, 0x00, 0x00}, //0x50
{0x00, 0x3E, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x7B, 0x6D, 0x76, 0x3B, 0x00, 0x00, 0x00}, //0x51
{0x00, 0x7E, 0x63, 0x63, 0x63, 0x63, 0x7E, 0x6C, 0x6C, 0x66, 0x66, 0x63, 0x63, 0x00, 0x00, 0x00}, //0x52
{0x00, 0x3E, 0x63, 0x63, 0x60, 0x30, 0x1C, 0x06, 0x03, 0x63, 0x63, 0x63, 0x3E, 0x00, 0x00, 0x00}, //0x53
{0x00, 0xFF, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00}, //0x54
{0x00, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x3E, 0x00, 0x00, 0x00}, //0x55
{0x00, 0x63, 0x63, 0x63, 0x36, 0x36, 0x36, 0x36, 0x1C, 0x1C, 0x1C, 0x08, 0x08, 0x00, 0x00, 0x00}, //0x56
{0x00, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x6B, 0x7F, 0x77, 0x63, 0x63, 0x41, 0x00, 0x00, 0x00}, //0x57
{0x00, 0x63, 0x63, 0x36, 0x36, 0x1C, 0x1C, 0x1C, 0x1C, 0x36, 0x36, 0x63, 0x63, 0x00, 0x00, 0x00}, //0x58
{0x00, 0xC3, 0xC3, 0x66, 0x66, 0x3C, 0x3C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00}, //0x59
{0x00, 0x7F, 0x03, 0x06, 0x06, 0x0C, 0x0C, 0x18, 0x18, 0x30, 0x30, 0x60, 0x7F, 0x00, 0x00, 0x00}, //0x5A
{0x00, 0x1F, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1F, 0x00, 0x00}, //0x5B
{0x00, 0x60, 0x60, 0x30, 0x30, 0x30, 0x18, 0x18, 0x18, 0x0C, 0x0C, 0x0C, 0x06, 0x06, 0x00, 0x00}, //0x5C
{0x00, 0x7C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x7C, 0x00, 0x00}, //0x5D
{0x08, 0x1C, 0x36, 0x63, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //0x5E
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x00}, //0x5F
{0x00, 0x0C, 0x0C, 0x08, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //0x60
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x06, 0x3E, 0x66, 0x66, 0x66, 0x3F, 0x00, 0x00, 0x00}, //0x61 'a'
{0x00, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7E, 0x63, 0x63, 0x63, 0x63, 0x63, 0x7E, 0x00, 0x00, 0x00}, //0x62 'b'
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x63, 0x60, 0x60, 0x60, 0x63, 0x3E, 0x00, 0x00, 0x00}, //0x63 'c'
{0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x3F, 0x63, 0x63, 0x63, 0x63, 0x63, 0x3F, 0x00, 0x00, 0x00}, //0x64 'd'
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x63, 0x63, 0x7F, 0x60, 0x63, 0x3E, 0x00, 0x00, 0x00}, //0x65 'e'
{0x00, 0x00, 0x00, 0x18, 0x34, 0x30, 0x7C, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00}, //0x66 'f'
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x63, 0x63, 0x63, 0x63, 0x3F, 0x03, 0x03, 0x63, 0x3E}, //0x67 'g'
{0x00, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7E, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x00, 0x00, 0x00}, //0x68 'h'
{0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00}, //0x69 'i'
{0x00, 0x00, 0x00, 0x06, 0x06, 0x00, 0x06, 0x06, 0x06, 0x06, 0x06, 0x66, 0x66, 0x66, 0x66, 0x3C}, //0x6A 'j'
{0x00, 0x00, 0x00, 0x60, 0x60, 0x60, 0x63, 0x66, 0x6C, 0x78, 0x78, 0x6C, 0x67, 0x00, 0x00, 0x00}, //0x6B 'k'
{0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00}, //0x6C 'l'
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x00, 0x00, 0x00}, //0x6D 'm'
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6E, 0x73, 0x63, 0x63, 0x63, 0x63, 0x63, 0x00, 0x00, 0x00}, //0x6E 'n'
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x63, 0x63, 0x63, 0x63, 0x63, 0x3E, 0x00, 0x00, 0x00}, //0x6F
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 0x63, 0x63, 0x63, 0x63, 0x63, 0x7E, 0x60, 0x60, 0x60}, //0x40
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x63, 0x63, 0x63, 0x63, 0x63, 0x3F, 0x03, 0x03, 0x03}, //0x40
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6F, 0x70, 0x60, 0x60, 0x60, 0x60, 0x60, 0x00, 0x00, 0x00}, //0x40
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x63, 0x60, 0x3E, 0x03, 0x63, 0x3E, 0x00, 0x00, 0x00}, //0x40
{0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x7C, 0x30, 0x30, 0x30, 0x30, 0x36, 0x1C, 0x00, 0x00, 0x00}, //0x40
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x63, 0x63, 0x63, 0x63, 0x63, 0x67, 0x3B, 0x00, 0x00, 0x00}, //0x40
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x63, 0x63, 0x36, 0x36, 0x1C, 0x1C, 0x08, 0x00, 0x00, 0x00}, //0x40
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x63, 0x63, 0x63, 0x6B, 0x7F, 0x63, 0x41, 0x00, 0x00, 0x00}, //0x40
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x63, 0x36, 0x1C, 0x08, 0x1C, 0x36, 0x63, 0x00, 0x00, 0x00}, //0x40
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x63, 0x63, 0x36, 0x36, 0x1C, 0x1C, 0x18, 0x18, 0x30, 0x30}, //0x40
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x7F, 0x00, 0x00, 0x00}, //0x40
{0x00, 0x07, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x18, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x07, 0x00, 0x00}, //0x40
{0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00}, //0x40
{0x00, 0x70, 0x18, 0x18, 0x18, 0x18, 0x18, 0x0C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x70, 0x00, 0x00}, //0x40
{0x00, 0x3B, 0x6F, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //0x40
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}  //0x40
};

#else
extern const int wEngFon[0x060][16];
#endif

#endif 
