/*
   Noiasca UTF8
   
   mapping to convert UTF-8 characters to their plain ASCII (Lower ANSI) represantation
   
   ASCII
   ****
   The full UTF-8 ASCII mapping will take around 1500 bytes 
   and covers characters which are used only in some specific languages
   there are also some smaller subsets available
   
   language families:
   ******************
   language families combine several languages and most of Europe can be covered quite well with
   
   gmq - west germanic
   gmq - north germanic
   roa - romance
   sla - slavic
   
   language specific
   ******************
   the smallest flash usage can be achieved with language specific mappings. 
   They are available  if I need them or if a language doesn't fit 
   well in one of the above language families.
   
   en - English - only for test purposes, English has some deprecated letters
   es - Spanish - also includes Catalan ca
   fr - French - but large anyway. So you still can use romance-roa instead
   fi - Finnisch - this Uralic language doesn't fit to well into the existing language families 
   ge - German - as it is my native language
   hu - Hungarian - this Uralic language doesn't fit to well into the existing language families
   
   Cyrillic
   ******************
   cyrillic_GOST16876_71_1 - a smaller set of Cyrillic converted according GOST16876-71 (1)
   
   Open topics
   
   by noiasca
   2021-02-14 replaced ANSI by ASCII, include guard
   2021-02-12 Cyrillic converter   
   2020-12-20 initial version
*/

#pragma once
#ifndef NOIASCA_UTF8_H
#define NOIASCA_UTF8_H
// the structure of the UTF8 -> single character (mapping)
struct Mapping {
  uint16_t utf8; // the 2 least significant bytes of the 4 byte UTF-8 character
  uint8_t c;     // the final 1 byte charactter to print
};


// Latin-1 Supplement (without c2 control, reduced c2 symbols)
// not included are
//   0xc280 - 0xc29F these are control bytes, only in Windows-1252 (CP-1252) which is a superset of ISO 8859-1, also called ISO Latin-1, these are printable characters
//   0xc29F - 0xc2BF as these are mostly symbols (beside two added for Spanish)
// Latin Extended-A 
// Latin Extended-B 
// Spacing Modifier Letters (without cb modifier, 
// Cobining Ciacritical Marks (cc combining, )
// Greek and Coptic (cd greek, )
// Cyrillic (d0 cyrillic)
// Cyrillic Supplement
   
const Mapping UTF8_ASCII[] PROGMEM = {
  {0xc2a1, '!'},      // ??	INVERTED EXCLAMATION MARK
  {0xc2aa, 'a'},      // ??	FEMININE ORDINAL INDICATOR
  {0xc2ba, 'o'},      // ??	MASCULINE ORDINAL INDICATOR
  {0xc2bf, '?'},      // ??  INVERTED QUESTION MARK  
  {0xc380, 'A'},      // ??	LATIN CAPITAL LETTER A WITH GRAVE
  {0xc381, 'A'},      // ??	LATIN CAPITAL LETTER A WITH ACUTE
  {0xc382, 'A'},      // ??	LATIN CAPITAL LETTER A WITH CIRCUMFLEX
  {0xc383, 'A'},      // ??	LATIN CAPITAL LETTER A WITH TILDE
  {0xc384, 'A'},      // ??	LATIN CAPITAL LETTER A WITH DIAERESIS
  {0xc385, 'A'},      // ??	LATIN CAPITAL LETTER A WITH RING ABOVE
  {0xc386, 'A'},      // ??	LATIN CAPITAL LETTER AE
  {0xc387, 'C'},      // ??	LATIN CAPITAL LETTER C WITH CEDILLA
  {0xc388, 'E'},      // ??	LATIN CAPITAL LETTER E WITH GRAVE
  {0xc389, 'E'},      // ??	LATIN CAPITAL LETTER E WITH ACUTE
  {0xc38a, 'E'},      // ??	LATIN CAPITAL LETTER E WITH CIRCUMFLEX
  {0xc38b, 'E'},      // ??	LATIN CAPITAL LETTER E WITH DIAERESIS
  {0xc38c, 'I'},      // ??	LATIN CAPITAL LETTER I WITH GRAVE
  {0xc38d, 'I'},      // ??	LATIN CAPITAL LETTER I WITH ACUTE
  {0xc38e, 'I'},      // ??	LATIN CAPITAL LETTER I WITH CIRCUMFLEX
  {0xc38f, 'I'},      // ??	LATIN CAPITAL LETTER I WITH DIAERESIS
  {0xc390, 'D'},      // ??	LATIN CAPITAL LETTER ETH
  {0xc391, 'N'},      // ??	LATIN CAPITAL LETTER N WITH TILDE
  {0xc392, 'O'},      // ??	LATIN CAPITAL LETTER O WITH GRAVE
  {0xc393, 'O'},      // ??	LATIN CAPITAL LETTER O WITH ACUTE
  {0xc394, 'O'},      // ??	LATIN CAPITAL LETTER O WITH CIRCUMFLEX
  {0xc395, 'O'},      // ??	LATIN CAPITAL LETTER O WITH TILDE
  {0xc396, 'O'},      // ??	LATIN CAPITAL LETTER O WITH DIAERESIS
  {0xc397, '*'},      // ??	MULTIPLICATION SIGN
  {0xc398, 'O'},      // ??	LATIN CAPITAL LETTER O WITH STROKE
  {0xc399, 'U'},      // ??	LATIN CAPITAL LETTER U WITH GRAVE
  {0xc39a, 'U'},      // ??	LATIN CAPITAL LETTER U WITH ACUTE
  {0xc39b, 'U'},      // ??	LATIN CAPITAL LETTER U WITH CIRCUMFLEX
  {0xc39c, 'U'},      // ??	LATIN CAPITAL LETTER U WITH DIAERESIS
  {0xc39d, 'Y'},      // ??	LATIN CAPITAL LETTER Y WITH ACUTE
  {0xc39e, 'p'},      // ??	LATIN CAPITAL LETTER THORN - somehow
  {0xc39f, 's'},      // ??	LATIN SMALL LETTER SHARP S
  {0xc3a0, 'a'},      // ??	LATIN SMALL LETTER A WITH GRAVE
  {0xc3a1, 'a'},      // ??	LATIN SMALL LETTER A WITH ACUTE
  {0xc3a2, 'a'},      // ??	LATIN SMALL LETTER A WITH CIRCUMFLEX
  {0xc3a3, 'a'},      // ??	LATIN SMALL LETTER A WITH TILDE
  {0xc3a4, 'a'},      // ??	LATIN SMALL LETTER A WITH DIAERESIS
  {0xc3a5, 'a'},      // ??	LATIN SMALL LETTER A WITH RING ABOVE
  {0xc3a6, 'a'},      // ??	LATIN SMALL LETTER AE
  {0xc3a7, 'c'},      // ??	LATIN SMALL LETTER C WITH CEDILLA
  {0xc3a8, 'e'},      // ??	LATIN SMALL LETTER E WITH GRAVE
  {0xc3a9, 'e'},      // ??	LATIN SMALL LETTER E WITH ACUTE
  {0xc3aa, 'e'},      // ??	LATIN SMALL LETTER E WITH CIRCUMFLEX
  {0xc3ab, 'e'},      // ??	LATIN SMALL LETTER E WITH DIAERESIS
  {0xc3ac, 'i'},      // ??	LATIN SMALL LETTER I WITH GRAVE
  {0xc3ad, 'i'},      // ??	LATIN SMALL LETTER I WITH ACUTE
  {0xc3ae, 'i'},      // ??	LATIN SMALL LETTER I WITH CIRCUMFLEX
  {0xc3af, 'i'},      // ??	LATIN SMALL LETTER I WITH DIAERESIS
  {0xc3b0, 'e'},      // ??	LATIN SMALL LETTER ETH
  {0xc3b1, 'n'},      // ??	LATIN SMALL LETTER N WITH TILDE
  {0xc3b2, 'o'},      // ??	LATIN SMALL LETTER O WITH GRAVE
  {0xc3b3, 'o'},      // ??	LATIN SMALL LETTER O WITH ACUTE
  {0xc3b4, 'o'},      // ??	LATIN SMALL LETTER O WITH CIRCUMFLEX
  {0xc3b5, 'o'},      // ??	LATIN SMALL LETTER O WITH TILDE
  {0xc3b6, 'o'},      // ??	LATIN SMALL LETTER O WITH DIAERESIS
  {0xc3b7, '/'},      // ??	DIVISION SIGN - somehow
  {0xc3b8, 'o'},      // ??	LATIN SMALL LETTER O WITH STROKE
  {0xc3b9, 'u'},      // ??	LATIN SMALL LETTER U WITH GRAVE
  {0xc3ba, 'u'},      // ??	LATIN SMALL LETTER U WITH ACUTE
  {0xc3bb, 'u'},      // ??	LATIN SMALL LETTER U WITH CIRCUMFLEX
  {0xc3bc, 'u'},      // ??	LATIN SMALL LETTER U WITH DIAERESIS
  {0xc3bd, 'y'},      // ??	LATIN SMALL LETTER Y WITH ACUTE
  {0xc3be, 'p'},      // ??	LATIN SMALL LETTER THORN - somehow
  {0xc3bf, 'y'},      // ??	LATIN SMALL LETTER Y WITH DIAERESIS
  {0xc480, 'A'},      // ??	LATIN CAPITAL LETTER A WITH MACRON
  {0xc481, 'a'},      // ??	LATIN SMALL LETTER A WITH MACRON
  {0xc482, 'A'},      // ??	LATIN CAPITAL LETTER A WITH BREVE
  {0xc483, 'a'},      // ??	LATIN SMALL LETTER A WITH BREVE
  {0xc484, 'A'},      // ??	LATIN CAPITAL LETTER A WITH OGONEK
  {0xc485, 'a'},      // ??	LATIN SMALL LETTER A WITH OGONEK
  {0xc486, 'C'},      // ??	LATIN CAPITAL LETTER C WITH ACUTE
  {0xc487, 'c'},      // ??	LATIN SMALL LETTER C WITH ACUTE
  {0xc488, 'C'},      // ??	LATIN CAPITAL LETTER C WITH CIRCUMFLEX
  {0xc489, 'c'},      // ??	LATIN SMALL LETTER C WITH CIRCUMFLEX
  {0xc48a, 'C'},      // ??	LATIN CAPITAL LETTER C WITH DOT ABOVE
  {0xc48b, 'c'},      // ??	LATIN SMALL LETTER C WITH DOT ABOVE
  {0xc48c, 'C'},      // ??	LATIN CAPITAL LETTER C WITH CARON
  {0xc48d, 'c'},      // ??	LATIN SMALL LETTER C WITH CARON
  {0xc48e, 'D'},      // ??	LATIN CAPITAL LETTER D WITH CARON
  {0xc48f, 'd'},      // ??	LATIN SMALL LETTER D WITH CARON
  {0xc490, 'D'},      // ??	LATIN CAPITAL LETTER D WITH STROKE
  {0xc491, 'd'},      // ??	LATIN SMALL LETTER D WITH STROKE
  {0xc492, 'E'},      // ??	LATIN CAPITAL LETTER E WITH MACRON
  {0xc493, 'e'},      // ??	LATIN SMALL LETTER E WITH MACRON
  {0xc494, 'E'},      // ??	LATIN CAPITAL LETTER E WITH BREVE
  {0xc495, 'e'},      // ??	LATIN SMALL LETTER E WITH BREVE
  {0xc496, 'E'},      // ??	LATIN CAPITAL LETTER E WITH DOT ABOVE
  {0xc497, 'e'},      // ??	LATIN SMALL LETTER E WITH DOT ABOVE
  {0xc498, 'E'},      // ??	LATIN CAPITAL LETTER E WITH OGONEK
  {0xc499, 'e'},      // ??	LATIN SMALL LETTER E WITH OGONEK
  {0xc49a, 'E'},      // ??	LATIN CAPITAL LETTER E WITH CARON
  {0xc49b, 'e'},      // ??	LATIN SMALL LETTER E WITH CARON
  {0xc49c, 'G'},      // ??	LATIN CAPITAL LETTER G WITH CIRCUMFLEX
  {0xc49d, 'g'},      // ??	LATIN SMALL LETTER G WITH CIRCUMFLEX
  {0xc49e, 'G'},      // ??	LATIN CAPITAL LETTER G WITH BREVE
  {0xc49f, 'g'},      // ??	LATIN SMALL LETTER G WITH BREVE
  {0xc4a0, 'G'},      // ??	LATIN CAPITAL LETTER G WITH DOT ABOVE
  {0xc4a1, 'g'},      // ??	LATIN SMALL LETTER G WITH DOT ABOVE
  {0xc4a2, 'G'},      // ??	LATIN CAPITAL LETTER G WITH CEDILLA
  {0xc4a3, 'g'},      // ??	LATIN SMALL LETTER G WITH CEDILLA
  {0xc4a4, 'H'},      // ??	LATIN CAPITAL LETTER H WITH CIRCUMFLEX
  {0xc4a5, 'h'},      // ??	LATIN SMALL LETTER H WITH CIRCUMFLEX
  {0xc4a6, 'H'},      // ??	LATIN CAPITAL LETTER H WITH STROKE
  {0xc4a7, 'h'},      // ??	LATIN SMALL LETTER H WITH STROKE
  {0xc4a8, 'I'},      // ??	LATIN CAPITAL LETTER I WITH TILDE
  {0xc4a9, 'i'},      // ??	LATIN SMALL LETTER I WITH TILDE
  {0xc4aa, 'I'},      // ??	LATIN CAPITAL LETTER I WITH MACRON
  {0xc4ab, 'i'},      // ??	LATIN SMALL LETTER I WITH MACRON
  {0xc4ac, 'I'},      // ??	LATIN CAPITAL LETTER I WITH BREVE
  {0xc4ad, 'i'},      // ??	LATIN SMALL LETTER I WITH BREVE
  {0xc4ae, 'I'},      // ??	LATIN CAPITAL LETTER I WITH OGONEK
  {0xc4af, 'i'},      // ??	LATIN SMALL LETTER I WITH OGONEK
  {0xc4b0, 'I'},      // ??	LATIN CAPITAL LETTER I WITH DOT ABOVE
  {0xc4b1, 'i'},      // ??	LATIN SMALL LETTER DOTLESS I
  {0xc4b2, 'I'},      // ??	LATIN CAPITAL LIGATURE IJ  - somehow - J should be added for Dutch
  {0xc4b3, 'i'},      // ??	LATIN SMALL LIGATURE IJ - somehow - J should be added for Dutch
  {0xc4b4, 'J'},      // ??	LATIN CAPITAL LETTER J WITH CIRCUMFLEX
  {0xc4b5, 'j'},      // ??	LATIN SMALL LETTER J WITH CIRCUMFLEX
  {0xc4b6, 'K'},      // ??	LATIN CAPITAL LETTER K WITH CEDILLA
  {0xc4b7, 'k'},      // ??	LATIN SMALL LETTER K WITH CEDILLA
  {0xc4b8, 'k'},      // ??	LATIN SMALL LETTER KRA
  {0xc4b9, 'L'},      // ??	LATIN CAPITAL LETTER L WITH ACUTE
  {0xc4ba, 'l'},      // ??	LATIN SMALL LETTER L WITH ACUTE
  {0xc4bb, 'L'},      // ??	LATIN CAPITAL LETTER L WITH CEDILLA
  {0xc4bc, 'l'},      // ??	LATIN SMALL LETTER L WITH CEDILLA
  {0xc4bd, 'L'},      // ??	LATIN CAPITAL LETTER L WITH CARON
  {0xc4be, 'l'},      // ??	LATIN SMALL LETTER L WITH CARON
  {0xc4bf, 'L'},      // ??	LATIN CAPITAL LETTER L WITH MIDDLE DOT
  {0xc580, 'l'},      // ??	LATIN SMALL LETTER L WITH MIDDLE DOT
  {0xc581, 'L'},      // ??	LATIN CAPITAL LETTER L WITH STROKE
  {0xc582, 'l'},      // ??	LATIN SMALL LETTER L WITH STROKE
  {0xc583, 'N'},      // ??	LATIN CAPITAL LETTER N WITH ACUTE
  {0xc584, 'n'},      // ??	LATIN SMALL LETTER N WITH ACUTE
  {0xc585, 'N'},      // ??	LATIN CAPITAL LETTER N WITH CEDILLA
  {0xc586, 'n'},      // ??	LATIN SMALL LETTER N WITH CEDILLA
  {0xc587, 'N'},      // ??	LATIN CAPITAL LETTER N WITH CARON
  {0xc588, 'n'},      // ??	LATIN SMALL LETTER N WITH CARON
  {0xc589, 'n'},      // ??	LATIN SMALL LETTER N PRECEDED BY APOSTROPHE
  {0xc58a, 'N'},      // ??	LATIN CAPITAL LETTER ENG
  {0xc58b, 'n'},      // ??	LATIN SMALL LETTER ENG
  {0xc58c, 'O'},      // ??	LATIN CAPITAL LETTER O WITH MACRON
  {0xc58d, 'o'},      // ??	LATIN SMALL LETTER O WITH MACRON
  {0xc58e, 'O'},      // ??	LATIN CAPITAL LETTER O WITH BREVE
  {0xc58f, 'o'},      // ??	LATIN SMALL LETTER O WITH BREVE
  {0xc590, 'O'},      // ??	LATIN CAPITAL LETTER O WITH DOUBLE ACUTE
  {0xc591, 'o'},      // ??	LATIN SMALL LETTER O WITH DOUBLE ACUTE
  {0xc592, 'O'},      // ??	LATIN CAPITAL LIGATURE OE
  {0xc593, 'o'},      // ??	LATIN SMALL LIGATURE OE
  {0xc594, 'R'},      // ??	LATIN CAPITAL LETTER R WITH ACUTE
  {0xc595, 'r'},      // ??	LATIN SMALL LETTER R WITH ACUTE
  {0xc596, 'R'},      // ??	LATIN CAPITAL LETTER R WITH CEDILLA
  {0xc597, 'r'},      // ??	LATIN SMALL LETTER R WITH CEDILLA
  {0xc598, 'R'},      // ??	LATIN CAPITAL LETTER R WITH CARON
  {0xc599, 'r'},      // ??	LATIN SMALL LETTER R WITH CARON
  {0xc59a, 'S'},      // ??	LATIN CAPITAL LETTER S WITH ACUTE
  {0xc59b, 'S'},      // ??	LATIN SMALL LETTER S WITH ACUTE
  {0xc59c, 'S'},      // ??	LATIN CAPITAL LETTER S WITH CIRCUMFLEX
  {0xc59d, 's'},      // ??	LATIN SMALL LETTER S WITH CIRCUMFLEX
  {0xc59e, 'S'},      // ??	LATIN CAPITAL LETTER S WITH CEDILLA
  {0xc59f, 's'},      // ??	LATIN SMALL LETTER S WITH CEDILLA
  {0xc5a0, 'S'},      // ??	LATIN CAPITAL LETTER S WITH CARON
  {0xc5a1, 's'},      // ??	LATIN SMALL LETTER S WITH CARON
  {0xc5a2, 'T'},      // ??	LATIN CAPITAL LETTER T WITH CEDILLA
  {0xc5a3, 't'},      // ??	LATIN SMALL LETTER T WITH CEDILLA
  {0xc5a4, 'T'},      // ??	LATIN CAPITAL LETTER T WITH CARON
  {0xc5a5, 't'},      // ??	LATIN SMALL LETTER T WITH CARON
  {0xc5a6, 'T'},      // ??	LATIN CAPITAL LETTER T WITH STROKE
  {0xc5a7, 't'},      // ??	LATIN SMALL LETTER T WITH STROKE
  {0xc5a8, 'U'},      // ??	LATIN CAPITAL LETTER U WITH TILDE
  {0xc5a9, 'u'},      // ??	LATIN SMALL LETTER U WITH TILDE
  {0xc5aa, 'U'},      // ??	LATIN CAPITAL LETTER U WITH MACRON
  {0xc5ab, 'u'},      // ??	LATIN SMALL LETTER U WITH MACRON
  {0xc5ac, 'U'},      // ??	LATIN CAPITAL LETTER U WITH BREVE
  {0xc5ad, 'u'},      // ??	LATIN SMALL LETTER U WITH BREVE
  {0xc5ae, 'U'},      // ??	LATIN CAPITAL LETTER U WITH RING ABOVE
  {0xc5af, 'u'},      // ??	LATIN SMALL LETTER U WITH RING ABOVE
  {0xc5b0, 'U'},      // ??	LATIN CAPITAL LETTER U WITH DOUBLE ACUTE
  {0xc5b1, 'u'},      // ??	LATIN SMALL LETTER U WITH DOUBLE ACUTE
  {0xc5b2, 'U'},      // ??	LATIN CAPITAL LETTER U WITH OGONEK
  {0xc5b3, 'u'},      // ??	LATIN SMALL LETTER U WITH OGONEK
  {0xc5b4, 'W'},      // ??	LATIN CAPITAL LETTER W WITH CIRCUMFLEX
  {0xc5b5, 'w'},      // ??	LATIN SMALL LETTER W WITH CIRCUMFLEX
  {0xc5b6, 'Y'},      // ??	LATIN CAPITAL LETTER Y WITH CIRCUMFLEX
  {0xc5b7, 'y'},      // ??	LATIN SMALL LETTER Y WITH CIRCUMFLEX
  {0xc5b8, 'Y'},      // ??	LATIN CAPITAL LETTER Y WITH DIAERESIS
  {0xc5b9, 'Z'},      // ??	LATIN CAPITAL LETTER Z WITH ACUTE
  {0xc5ba, 'z'},      // ??	LATIN SMALL LETTER Z WITH ACUTE
  {0xc5bb, 'Z'},      // ??	LATIN CAPITAL LETTER Z WITH DOT ABOVE
  {0xc5bc, 'z'},      // ??	LATIN SMALL LETTER Z WITH DOT ABOVE
  {0xc5bd, 'Z'},      // ??	LATIN CAPITAL LETTER Z WITH CARON
  {0xc5be, 'z'},      // ??	LATIN SMALL LETTER Z WITH CARON
  {0xc5bf, 's'},      // ??	LATIN SMALL LETTER LONG S
  {0xc680, 'b'},      // ??	LATIN SMALL LETTER B WITH STROKE
  {0xc681, 'B'},      // ??	LATIN CAPITAL LETTER B WITH HOOK
  {0xc682, 'B'},      // ??	LATIN CAPITAL LETTER B WITH TOPBAR
  {0xc683, 'b'},      // ??	LATIN SMALL LETTER B WITH TOPBAR
  {0xc684, 'B'},      // ??	LATIN CAPITAL LETTER TONE SIX - somehow
  {0xc685, 'b'},      // ??	LATIN SMALL LETTER TONE SIX - somehow
  {0xc686, 'O'},      // ??	LATIN CAPITAL LETTER OPEN O
  {0xc687, 'C'},      // ??	LATIN CAPITAL LETTER C WITH HOOK
  {0xc688, 'c'},      // ??	LATIN SMALL LETTER C WITH HOOK
  {0xc689, 'D'},      // ??	LATIN CAPITAL LETTER AFRICAN D
  {0xc68a, 'D'},      // ??	LATIN CAPITAL LETTER D WITH HOOK
  {0xc68b, 'D'},      // ??	LATIN CAPITAL LETTER D WITH TOPBAR
  {0xc68c, 'd'},      // ??	LATIN SMALL LETTER D WITH TOPBAR
  //{0xc68d, ''},      // ??	LATIN SMALL LETTER TURNED DELTA
  {0xc68e, 'E'},      // ??	LATIN CAPITAL LETTER REVERSED E
  //{0xc68f, ''},      // ??	LATIN CAPITAL LETTER SCHWA
  {0xc690, 'E'},      // ??	LATIN CAPITAL LETTER OPEN E
  {0xc691, 'F'},      // ??	LATIN CAPITAL LETTER F WITH HOOK
  {0xc692, 'f'},      // ??	LATIN SMALL LETTER F WITH HOOK
  {0xc693, 'G'},      // ??	LATIN CAPITAL LETTER G WITH HOOK
  //{0xc694, ''},      // ??	LATIN CAPITAL LETTER GAMMA
  //{0xc695, ''},      // ??	LATIN SMALL LETTER HV
  //{0xc696, ''},      // ??	LATIN CAPITAL LETTER IOTA
  {0xc697, 'I'},       // ??	LATIN CAPITAL LETTER I WITH STROKE
  {0xc698, 'K'},       // ??	LATIN CAPITAL LETTER K WITH HOOK
  {0xc699, 'k'},       // ??	LATIN SMALL LETTER K WITH HOOK
  {0xc69a, 'l'},       // ??	LATIN SMALL LETTER L WITH BAR
  //{0xc69b, ''},      // ??	LATIN SMALL LETTER LAMBDA WITH STROKE
  {0xc69c, 'M'},       // ??	LATIN CAPITAL LETTER TURNED M
  {0xc69d, 'N'},       // ??	LATIN CAPITAL LETTER N WITH LEFT HOOK
  {0xc69e, 'n'},       // ??	LATIN SMALL LETTER N WITH LONG RIGHT LEG
  {0xc69f, 'O'},       // ??	LATIN CAPITAL LETTER O WITH MIDDLE TILDE
  {0xc6a0, 'o'},       // ??	LATIN SMALL LETTER O WITH HORN
  //{0xc6a2, ''},      // ??	LATIN CAPITAL LETTER OI
  //{0xc6a3, ''},      // ??	LATIN SMALL LETTER OI
  {0xc6a4, 'P'},       // ??	LATIN CAPITAL LETTER P WITH HOOK
  {0xc6a5, 'p'},       // ??	LATIN SMALL LETTER P WITH HOOK
  //{0xc6a6, ''},      // ??	LATIN LETTER YR
  //{0xc6a7, ''},      // ??	LATIN CAPITAL LETTER TONE TWO
  //{0xc6a8, ''},      // ??	LATIN SMALL LETTER TONE TWO
  //{0xc6a9, ''},      // ??	LATIN CAPITAL LETTER ESH
  //{0xc6aa, ''},      // ??	LATIN LETTER REVERSED ESH LOOP
  {0xc6ab, 't'},       // ??	LATIN SMALL LETTER T WITH PALATAL HOOK
  {0xc6ac, 'T'},       // ??	LATIN CAPITAL LETTER T WITH HOOK
  {0xc6ad, 't'},       // ??	LATIN SMALL LETTER T WITH HOOK
  {0xc6ae, 'T'},       // ??	LATIN CAPITAL LETTER T WITH RETROFLEX HOOK
  {0xc6af, 'U'},       // ??	LATIN CAPITAL LETTER U WITH HORN
  {0xc6b0, 'u'},       // ??	LATIN SMALL LETTER U WITH HORN
  //{0xc6b1, ''},      // ??	LATIN CAPITAL LETTER UPSILON
  {0xc6b2, 'V'},       // ??	LATIN CAPITAL LETTER V WITH HOOK
  {0xc6b3, 'Y'},       // ??	LATIN CAPITAL LETTER Y WITH HOOK
  {0xc6b4, 'y'},       // ??	LATIN SMALL LETTER Y WITH HOOK
  {0xc6b5, 'Z'},       // ??	LATIN CAPITAL LETTER Z WITH STROKE
  {0xc6b6, 'z'},       // ??	LATIN SMALL LETTER Z WITH STROKE
  //{0xc6b7, ''},      // ??	LATIN CAPITAL LETTER EZH
  //{0xc6b8, ''},      // ??	LATIN CAPITAL LETTER EZH REVERSED
  //{0xc6b9, ''},      // ??	LATIN SMALL LETTER EZH REVERSED
  //{0xc6ba, ''},      // ??	LATIN SMALL LETTER EZH WITH TAIL
  //{0xc6bb, ''},      // ??	LATIN LETTER TWO WITH STROKE
  //{0xc6bc, ''},      // ??	LATIN CAPITAL LETTER TONE FIVE
  //{0xc6bd, ''},      // ??	LATIN SMALL LETTER TONE FIVE
  //{0xc6be, ''},      // ??	LATIN LETTER INVERTED GLOTTAL STOP WITH STROKE
  //{0xc6bf, ''},      // ??	LATIN LETTER WYNN
  //{0xc780, ''},      // ??	LATIN LETTER DENTAL CLICK
  //{0xc781, ''},      // ??	LATIN LETTER LATERAL CLICK
  //{0xc782, ''},      // ??	LATIN LETTER ALVEOLAR CLICK
  //{0xc783, ''},      // ??	LATIN LETTER RETROFLEX CLICK
  {0xc784, 'D'},      // ??	LATIN CAPITAL LETTER DZ WITH CARON
  {0xc785, 'D'},      // ??	LATIN CAPITAL LETTER D WITH SMALL LETTER Z WITH CARON
  {0xc786, 'd'},      // ??	LATIN SMALL LETTER DZ WITH CARON
  {0xc787, 'L'},      // ??	LATIN CAPITAL LETTER LJ
  {0xc788, 'L'},      // ??	LATIN CAPITAL LETTER L WITH SMALL LETTER J
  {0xc789, 'l'},      // ??	LATIN SMALL LETTER LJ
  {0xc78a, 'N'},      // ??	LATIN CAPITAL LETTER NJ
  {0xc78b, 'N'},      // ??	LATIN CAPITAL LETTER N WITH SMALL LETTER J
  {0xc78c, 'n'},      // ??	LATIN SMALL LETTER NJ
  {0xc78d, 'A'},      // ??	LATIN CAPITAL LETTER A WITH CARON
  {0xc78e, 'a'},      // ??	LATIN SMALL LETTER A WITH CARON
  {0xc78f, 'I'},      // ??	LATIN CAPITAL LETTER I WITH CARON
  {0xc790, 'i'},      // ??	LATIN SMALL LETTER I WITH CARON
  {0xc791, 'O'},      // ??	LATIN CAPITAL LETTER O WITH CARON
  {0xc792, 'o'},      // ??	LATIN SMALL LETTER O WITH CARON
  {0xc793, 'U'},      // ??	LATIN CAPITAL LETTER U WITH CARON
  {0xc794, 'u'},      // ??	LATIN SMALL LETTER U WITH CARON
  {0xc795, 'U'},      // ??	LATIN CAPITAL LETTER U WITH DIAERESIS AND MACRON
  {0xc796, 'u'},      // ??	LATIN SMALL LETTER U WITH DIAERESIS AND MACRON
  {0xc797, 'U'},      // ??	LATIN CAPITAL LETTER U WITH DIAERESIS AND ACUTE
  {0xc798, 'u'},      // ??	LATIN SMALL LETTER U WITH DIAERESIS AND ACUTE
  {0xc799, 'U'},      // ??	LATIN CAPITAL LETTER U WITH DIAERESIS AND CARON
  {0xc79a, 'u'},      // ??	LATIN SMALL LETTER U WITH DIAERESIS AND CARON
  {0xc79b, 'U'},      // ??	LATIN CAPITAL LETTER U WITH DIAERESIS AND GRAVE
  {0xc79c, 'u'},      // ??	LATIN SMALL LETTER U WITH DIAERESIS AND GRAVE
  {0xc79d, 'e'},      // ??	LATIN SMALL LETTER TURNED E
  {0xc79e, 'A'},      // ??	LATIN CAPITAL LETTER A WITH DIAERESIS AND MACRON
  {0xc79f, 'a'},      // ??	LATIN SMALL LETTER A WITH DIAERESIS AND MACRON
  {0xc7a0, 'A'},      // ??	LATIN CAPITAL LETTER A WITH DOT ABOVE AND MACRON
  {0xc7a1, 'a'},      // ??	LATIN SMALL LETTER A WITH DOT ABOVE AND MACRON
  {0xc7a2, 'A'},      // ??	LATIN CAPITAL LETTER AE WITH MACRON
  {0xc7a3, 'a'},      // ??	LATIN SMALL LETTER AE WITH MACRON
  {0xc7a4, 'G'},      // ??	LATIN CAPITAL LETTER G WITH STROKE
  {0xc7a5, 'g'},      // ??	LATIN SMALL LETTER G WITH STROKE
  {0xc7a6, 'G'},      // ??	LATIN CAPITAL LETTER G WITH CARON
  {0xc7a7, 'g'},      // ??	LATIN SMALL LETTER G WITH CARON
  {0xc7a8, 'K'},      // ??	LATIN CAPITAL LETTER K WITH CARON
  {0xc7a9, 'k'},      // ??	LATIN SMALL LETTER K WITH CARON
  {0xc7aa, 'O'},      // ??	LATIN CAPITAL LETTER O WITH OGONEK
  {0xc7ab, 'o'},      // ??	LATIN SMALL LETTER O WITH OGONEK
  {0xc7ac, 'O'},      // ??	LATIN CAPITAL LETTER O WITH OGONEK AND MACRON
  {0xc7ad, 'o'},      // ??	LATIN SMALL LETTER O WITH OGONEK AND MACRON
  //{0xc7ae, ''},      // ??	LATIN CAPITAL LETTER EZH WITH CARON
  //{0xc7af, ''},      // ??	LATIN SMALL LETTER EZH WITH CARON
  {0xc7b0, 'J'},      // ??	LATIN SMALL LETTER J WITH CARON
  {0xc7b1, 'D'},      // ??	LATIN CAPITAL LETTER DZ
  {0xc7b2, 'd'},      // ??	LATIN CAPITAL LETTER D WITH SMALL LETTER Z
  {0xc7b3, 'd'},      // ??	LATIN SMALL LETTER DZ
  {0xc7b4, 'G'},      // ??	LATIN CAPITAL LETTER G WITH ACUTE
  {0xc7b5, 'g'},      // ??	LATIN SMALL LETTER G WITH ACUTE
  //{0xc7b6, ''},      // ??	LATIN CAPITAL LETTER HWAIR
  //{0xc7b7, ''},      // ??	LATIN CAPITAL LETTER WYNN
  {0xc7b8, 'N'},      // ??	LATIN CAPITAL LETTER N WITH GRAVE
  {0xc7b9, 'n'},      // ??	LATIN SMALL LETTER N WITH GRAVE
  {0xc7ba, 'A'},      // ??	LATIN CAPITAL LETTER A WITH RING ABOVE AND ACUTE
  {0xc7bb, 'a'},      // ??	LATIN SMALL LETTER A WITH RING ABOVE AND ACUTE
  {0xc7bc, 'A'},      // ??	LATIN CAPITAL LETTER AE WITH ACUTE
  {0xc7bd, 'a'},      // ??	LATIN SMALL LETTER AE WITH ACUTE
  {0xc7be, 'O'},      // ??	LATIN CAPITAL LETTER O WITH STROKE AND ACUTE
  {0xc7bf, 'o'},      // ??	LATIN SMALL LETTER O WITH STROKE AND ACUTE
  {0xc880, 'A'},      // ??	LATIN CAPITAL LETTER A WITH DOUBLE GRAVE
  {0xc881, 'a'},      // ??	LATIN SMALL LETTER A WITH DOUBLE GRAVE
  {0xc882, 'A'},      // ??	LATIN CAPITAL LETTER A WITH INVERTED BREVE
  {0xc883, 'a'},      // ??	LATIN SMALL LETTER A WITH INVERTED BREVE
  {0xc884, 'E'},      // ??	LATIN CAPITAL LETTER E WITH DOUBLE GRAVE
  {0xc885, 'e'},      // ??	LATIN SMALL LETTER E WITH DOUBLE GRAVE
  {0xc886, 'E'},      // ??	LATIN CAPITAL LETTER E WITH INVERTED BREVE
  {0xc887, 'e'},      // ??	LATIN SMALL LETTER E WITH INVERTED BREVE
  {0xc888, 'I'},      // ??	LATIN CAPITAL LETTER I WITH DOUBLE GRAVE
  {0xc889, 'i'},      // ??	LATIN SMALL LETTER I WITH DOUBLE GRAVE
  {0xc88a, 'I'},      // ??	LATIN CAPITAL LETTER I WITH INVERTED BREVE
  {0xc88b, 'i'},      // ??	LATIN SMALL LETTER I WITH INVERTED BREVE
  {0xc88c, 'O'},      // ??	LATIN CAPITAL LETTER O WITH DOUBLE GRAVE
  {0xc88d, 'o'},      // ??	LATIN SMALL LETTER O WITH DOUBLE GRAVE
  {0xc88e, 'O'},      // ??	LATIN CAPITAL LETTER O WITH INVERTED BREVE
  {0xc88f, 'o'},      // ??	LATIN SMALL LETTER O WITH INVERTED BREVE
  {0xc890, 'R'},      // ??	LATIN CAPITAL LETTER R WITH DOUBLE GRAVE
  {0xc891, 'r'},      // ??	LATIN SMALL LETTER R WITH DOUBLE GRAVE
  {0xc892, 'R'},      // ??	LATIN CAPITAL LETTER R WITH INVERTED BREVE
  {0xc893, 'r'},      // ??	LATIN SMALL LETTER R WITH INVERTED BREVE
  {0xc894, 'U'},      // ??	LATIN CAPITAL LETTER U WITH DOUBLE GRAVE
  {0xc895, 'u'},      // ??	LATIN SMALL LETTER U WITH DOUBLE GRAVE
  {0xc896, 'U'},      // ??	LATIN CAPITAL LETTER U WITH INVERTED BREVE
  {0xc897, 'u'},      // ??	LATIN SMALL LETTER U WITH INVERTED BREVE
  {0xc898, 'S'},      // ??	LATIN CAPITAL LETTER S WITH COMMA BELOW
  {0xc899, 's'},      // ??	LATIN SMALL LETTER S WITH COMMA BELOW
  {0xc89a, 'T'},      // ??	LATIN CAPITAL LETTER T WITH COMMA BELOW
  {0xc89b, 't'},      // ??	LATIN SMALL LETTER T WITH COMMA BELOW
  //{0xc89c, ''},      // ??	LATIN CAPITAL LETTER YOGH
  //{0xc89d, ''},      // ??	LATIN SMALL LETTER YOGH
  {0xc89e, 'H'},      // ??	LATIN CAPITAL LETTER H WITH CARON
  {0xc89f, 'h'},      // ??	LATIN SMALL LETTER H WITH CARON
  {0xc8a0, 'N'},      // ??	LATIN CAPITAL LETTER N WITH LONG RIGHT LEG
  {0xc8a1, 'd'},      // ??	LATIN SMALL LETTER D WITH CURL
  {0xc8a2, 'O'},      // ??	LATIN CAPITAL LETTER OU
  {0xc8a3, 'o'},      // ??	LATIN SMALL LETTER OU
  {0xc8a4, 'Z'},      // ??	LATIN CAPITAL LETTER Z WITH HOOK
  {0xc8a5, 'z'},      // ??	LATIN SMALL LETTER Z WITH HOOK
  {0xc8a6, 'A'},      // ??	LATIN CAPITAL LETTER A WITH DOT ABOVE
  {0xc8a7, 'a'},      // ??	LATIN SMALL LETTER A WITH DOT ABOVE
  {0xc8a8, 'E'},      // ??	LATIN CAPITAL LETTER E WITH CEDILLA
  {0xc8a9, 'e'},      // ??	LATIN SMALL LETTER E WITH CEDILLA
  {0xc8aa, 'O'},      // ??	LATIN CAPITAL LETTER O WITH DIAERESIS AND MACRON
  {0xc8ab, 'o'},      // ??	LATIN SMALL LETTER O WITH DIAERESIS AND MACRON
  {0xc8ac, 'O'},      // ??	LATIN CAPITAL LETTER O WITH TILDE AND MACRON
  {0xc8ad, 'o'},      // ??	LATIN SMALL LETTER O WITH TILDE AND MACRON
  {0xc8ae, 'O'},      // ??	LATIN CAPITAL LETTER O WITH DOT ABOVE
  {0xc8af, 'o'},      // ??	LATIN SMALL LETTER O WITH DOT ABOVE
  {0xc8b0, 'O'},      // ??	LATIN CAPITAL LETTER O WITH DOT ABOVE AND MACRON
  {0xc8b1, 'o'},      // ??	LATIN SMALL LETTER O WITH DOT ABOVE AND MACRON
  {0xc8b2, 'y'},      // ??	LATIN CAPITAL LETTER Y WITH MACRON
  {0xc8b3, 'y'},      // ??	LATIN SMALL LETTER Y WITH MACRON
  {0xc8b4, 'l'},      // ??	LATIN SMALL LETTER L WITH CURL
  {0xc8b5, 'n'},      // ??	LATIN SMALL LETTER N WITH CURL
  {0xc8b6, 't'},      // ??	LATIN SMALL LETTER T WITH CURL
  {0xc8b7, 'j'},      // ??	LATIN SMALL LETTER DOTLESS J
  //{0xc8b8, ''},      // ??	LATIN SMALL LETTER DB DIGRAPH
  //{0xc8b9, ''},      // ??	LATIN SMALL LETTER QP DIGRAPH
  {0xc8ba, 'A'},      // ??	LATIN CAPITAL LETTER A WITH STROKE
  {0xc8bb, 'C'},      // ??	LATIN CAPITAL LETTER C WITH STROKE
  {0xc8bc, 'c'},      // ??	LATIN SMALL LETTER C WITH STROKE
  {0xc8bd, 'L'},      // ??	LATIN CAPITAL LETTER L WITH BAR
  {0xc8be, 'T'},      // ??	LATIN CAPITAL LETTER T WITH DIAGONAL STROKE
  {0xc8bf, 's'},      // ??	LATIN SMALL LETTER S WITH SWASH TAIL
  {0xc980, 'z'},      // ??	LATIN SMALL LETTER Z WITH SWASH TAIL
  //{0xc981, ''},      // ??	LATIN CAPITAL LETTER GLOTTAL STOP
  //{0xc982, ''},      // ??	LATIN SMALL LETTER GLOTTAL STOP
  {0xc983, 'B'},      // ??	LATIN CAPITAL LETTER B WITH STROKE
  {0xc984, 'U'},      // ??	LATIN CAPITAL LETTER U BAR
  {0xc985, 'V'},      // ??	LATIN CAPITAL LETTER TURNED V
  {0xc986, 'E'},      // ??	LATIN CAPITAL LETTER E WITH STROKE
  {0xc987, 'e'},      // ??	LATIN SMALL LETTER E WITH STROKE
  {0xc988, 'J'},      // ??	LATIN CAPITAL LETTER J WITH STROKE
  {0xc989, 'j'},      // ??	LATIN SMALL LETTER J WITH STROKE
  {0xc98a, 'Q'},      // ??	LATIN CAPITAL LETTER SMALL Q WITH HOOK TAIL
  {0xc98b, 'q'},      // ??	LATIN SMALL LETTER Q WITH HOOK TAIL
  {0xc98c, 'R'},      // ??	LATIN CAPITAL LETTER R WITH STROKE
  {0xc98d, 'r'},      // ??	LATIN SMALL LETTER R WITH STROKE
  {0xc98e, 'Y'},      // ??	LATIN CAPITAL LETTER Y WITH STROKE
  {0xc98f, 'y'},      // ??	LATIN SMALL LETTER Y WITH STROKE
  {0xc990, 'a'},      // ??	LATIN SMALL LETTER TURNED A
  //{0xc991, ''},      // ??	LATIN SMALL LETTER ALPHA
  //{0xc992, ''},      // ??	LATIN SMALL LETTER TURNED ALPHA
  {0xc993, 'b'},      // ??	LATIN SMALL LETTER B WITH HOOK
  {0xc994, 'o'},      // ??	LATIN SMALL LETTER OPEN O
  {0xc995, 'c'},      // ??	LATIN SMALL LETTER C WITH CURL
  {0xc996, 'd'},      // ??	LATIN SMALL LETTER D WITH TAIL
  {0xc997, 'd'},      // ??	LATIN SMALL LETTER D WITH HOOK
  {0xc998, 'e'},      // ??	LATIN SMALL LETTER REVERSED E
  //{0xc999, ''},      // ??	LATIN SMALL LETTER SCHWA
  //{0xc99a, ''},      // ??	LATIN SMALL LETTER SCHWA WITH HOOK
  {0xc99b, 'e'},      // ??	LATIN SMALL LETTER OPEN E
  {0xc99c, 'e'},      // ??	LATIN SMALL LETTER REVERSED OPEN E
  {0xc99d, 'e'},      // ??	LATIN SMALL LETTER REVERSED OPEN E WITH HOOK
  {0xc99e, 'e'},      // ??	LATIN SMALL LETTER CLOSED REVERSED OPEN E
  {0xc99f, 'j'},      // ??	LATIN SMALL LETTER DOTLESS J WITH STROKE
  {0xc9a0, 'g'},      // ??	LATIN SMALL LETTER G WITH HOOK
  {0xc9a1, 'g'},      // ??	LATIN SMALL LETTER SCRIPT G
  {0xc9a2, 'G'},      // ??	LATIN LETTER SMALL CAPITAL G
  //{0xc9a3, ''},      // ??	LATIN SMALL LETTER GAMMA
  //{0xc9a4, ''},      // ??	LATIN SMALL LETTER RAMS HORN
  {0xc9a5, 'h'},      // ??	LATIN SMALL LETTER TURNED H
  {0xc9a6, 'h'},      // ??	LATIN SMALL LETTER H WITH HOOK
  //{0xc9a7, ''},      // ??	LATIN SMALL LETTER HENG WITH HOOK
  {0xc9a8, 'i'},      // ??	LATIN SMALL LETTER I WITH STROKE
  //{0xc9a9, ''},      // ??	LATIN SMALL LETTER IOTA
  {0xc9aa, 'i'},      // ??	LATIN LETTER SMALL CAPITAL I
  {0xc9ab, 'l'},      // ??	LATIN SMALL LETTER L WITH MIDDLE TILDE
  {0xc9ac, 'l'},      // ??	LATIN SMALL LETTER L WITH BELT
  {0xc9ad, 'l'},      // ??	LATIN SMALL LETTER L WITH RETROFLEX HOOK
  //{0xc9ae, ''},      // ??	LATIN SMALL LETTER LEZH
  {0xc9af, 'm'},      // ??	LATIN SMALL LETTER TURNED M
  {0xc9b0, 'm'},      // ??	LATIN SMALL LETTER TURNED M WITH LONG LEG
  {0xc9b1, 'm'},      // ??	LATIN SMALL LETTER M WITH HOOK
  {0xc9b2, 'n'},      // ??	LATIN SMALL LETTER N WITH LEFT HOOK
  {0xc9b3, 'n'},      // ??	LATIN SMALL LETTER N WITH RETROFLEX HOOK
  {0xc9b4, 'n'},      // ??	LATIN LETTER SMALL CAPITAL N
  {0xc9b5, 'o'},      // ??	LATIN SMALL LETTER BARRED O
  {0xc9b6, 'o'},      // ??	LATIN LETTER SMALL CAPITAL OE
  {0xc9b7, 'o'},      // ??	LATIN SMALL LETTER CLOSED OMEGA
  //{0xc9b8, ''},      // ??	LATIN SMALL LETTER PHI
  {0xc9b9, 'r'},      // ??	LATIN SMALL LETTER TURNED R
  {0xc9ba, 'r'},      // ??	LATIN SMALL LETTER TURNED R WITH LONG LEG
  {0xc9bb, 'r'},      // ??	LATIN SMALL LETTER TURNED R WITH HOOK
  {0xc9bc, 'r'},      // ??	LATIN SMALL LETTER R WITH LONG LEG
  {0xc9bd, 'r'},      // ??	LATIN SMALL LETTER R WITH TAIL
  {0xc9be, 'r'},      // ??	LATIN SMALL LETTER R WITH FISHHOOK
  {0xc9bf, 'r'},      // ??	LATIN SMALL LETTER REVERSED R WITH FISHHOOK
  {0xca80, 'r'},      // ??	LATIN LETTER SMALL CAPITAL R
  {0xca81, 'R'},      // ??	LATIN LETTER SMALL CAPITAL INVERTED R
  {0xca82, 's'},      // ??	LATIN SMALL LETTER S WITH HOOK
  //{0xca83, ''},      // ??	LATIN SMALL LETTER ESH
  //{0xca84, ''},      // ??	LATIN SMALL LETTER DOTLESS J WITH STROKE AND HOOK
  //{0xca85, ''},      // ??	LATIN SMALL LETTER SQUAT REVERSED ESH
  //{0xca86, ''},      // ??	LATIN SMALL LETTER ESH WITH CURL
  {0xca87, 't'},      // ??	LATIN SMALL LETTER TURNED T
  {0xca88, 't'},      // ??	LATIN SMALL LETTER T WITH RETROFLEX HOOK
  {0xca89, 'u'},      // ??	LATIN SMALL LETTER U BAR
  {0xca8a, 'u'},      // ??	LATIN SMALL LETTER UPSILON
  {0xca8b, 'v'},      // ??	LATIN SMALL LETTER V WITH HOOK
  {0xca8c, 'v'},      // ??	LATIN SMALL LETTER TURNED V
  {0xca8d, 'w'},      // ??	LATIN SMALL LETTER TURNED W
  {0xca8e, 'y'},      // ??	LATIN SMALL LETTER TURNED Y
  {0xca8f, 'y'},      // ??	LATIN LETTER SMALL CAPITAL Y
  {0xca90, 'z'},      // ??	LATIN SMALL LETTER Z WITH RETROFLEX HOOK
  {0xca91, 'z'},      // ??	LATIN SMALL LETTER Z WITH CURL
  //{0xca92, ''},      // ??	LATIN SMALL LETTER EZH
  //{0xca93, ''},      // ??	LATIN SMALL LETTER EZH WITH CURL
  //{0xca94, ''},      // ??	LATIN LETTER GLOTTAL STOP
  //{0xca95, ''},      // ??	LATIN LETTER PHARYNGEAL VOICED FRICATIVE
  //{0xca96, ''},      // ??	LATIN LETTER INVERTED GLOTTAL STOP
  {0xca97, 'c'},      // ??	LATIN LETTER STRETCHED C
  //{0xca98, ''},      // ??	LATIN LETTER BILABIAL CLICK
  {0xca99, 'b'},      // ??	LATIN LETTER SMALL CAPITAL B
  {0xca9a, 'e'},      // ??	LATIN SMALL LETTER CLOSED OPEN E
  {0xca9b, 'g'},      // ??	LATIN LETTER SMALL CAPITAL G WITH HOOK
  {0xca9c, 'h'},      // ??	LATIN LETTER SMALL CAPITAL H
  {0xca9d, 'j'},      // ??	LATIN SMALL LETTER J WITH CROSSED-TAIL
  {0xca9e, 'k'},      // ??	LATIN SMALL LETTER TURNED K
  {0xca9f, 'l'},      // ??	LATIN LETTER SMALL CAPITAL L
  {0xcaa0, 'q'},      // ??	LATIN SMALL LETTER Q WITH HOOK
  //{0xcaa1, ''},      // ??	LATIN LETTER GLOTTAL STOP WITH STROKE
  //{0xcaa2, ''},      // ??	LATIN LETTER REVERSED GLOTTAL STOP WITH STROKE
  {0xcaa3, 'd'},      // ??	LATIN SMALL LETTER DZ DIGRAPH
  {0xcaa4, 'd'},      // ??	LATIN SMALL LETTER DEZH DIGRAPH
  {0xcaa5, 'd'},      // ??	LATIN SMALL LETTER DZ DIGRAPH WITH CURL
  {0xcaa6, 't'},      // ??	LATIN SMALL LETTER TS DIGRAPH
  {0xcaa7, 't'},      // ??	LATIN SMALL LETTER TESH DIGRAPH
  {0xcaa8, 't'},      // ??	LATIN SMALL LETTER TC DIGRAPH WITH CURL
  {0xcaa9, 'f'},      // ??	LATIN SMALL LETTER FENG DIGRAPH
  {0xcaaa, 'l'},      // ??	LATIN SMALL LETTER LS DIGRAPH
  {0xcaab, 'l'},      // ??	LATIN SMALL LETTER LZ DIGRAPH
  //{0xcaac, ''},      // ??	LATIN LETTER BILABIAL PERCUSSIVE
  //{0xcaad, ''},      // ??	LATIN LETTER BIDENTAL PERCUSSIVE
  {0xcaae, 'h'},      // ??	LATIN SMALL LETTER TURNED H WITH FISHHOOK
  {0xcaaf, 'h'},      // ??	LATIN SMALL LETTER TURNED H WITH FISHHOOK AND TAIL
  {0xcb96, '+'},      // ??	MODIFIER LETTER PLUS SIGN
  {0xcb97, '-'},      // ??	MODIFIER LETTER MINUS SIGN
  {0xcba1, 'l'},      // ??	MODIFIER LETTER SMALL L
  {0xcba2, 's'},      // ??	MODIFIER LETTER SMALL S
  {0xcba3, 'x'},      // ??	MODIFIER LETTER SMALL X
  {0xcda3, 'a'},      // ??	COMBINING LATIN SMALL LETTER A
  {0xcda4, 'e'},      // ??	COMBINING LATIN SMALL LETTER E
  {0xcda5, 'i'},      // ??	COMBINING LATIN SMALL LETTER I
  {0xcda6, 'o'},      // ??	COMBINING LATIN SMALL LETTER O
  {0xcda7, 'u'},      // ??	COMBINING LATIN SMALL LETTER U
  {0xcda8, 'c'},      // ??	COMBINING LATIN SMALL LETTER C
  {0xcda9, 'd'},      // ??	COMBINING LATIN SMALL LETTER D
  {0xcdaa, 'h'},      // ??	COMBINING LATIN SMALL LETTER H
  {0xcdab, 'm'},      // ??	COMBINING LATIN SMALL LETTER M
  {0xcdac, 'r'},      // ??	COMBINING LATIN SMALL LETTER R
  {0xcdad, 't'},      // ??	COMBINING LATIN SMALL LETTER T
  {0xcdae, 'v'},      // ??	COMBINING LATIN SMALL LETTER V
  {0xcdaf, 'x'},      // ??	COMBINING LATIN SMALL LETTER X
};

// West Germanic - gmw
// de en nl (sco fy)
const Mapping lang_gmw[] PROGMEM = {
  {0xC384, 'A'},      // ??   // large Umlauts may be overwritten in the write method
  {0xc386, 'A'},      // ??	LATIN CAPITAL LETTER AE
  {0xc384, 'A'},      // ??	LATIN CAPITAL LETTER A WITH DIAERESIS
  {0xc38b, 'E'},      // ??	LATIN CAPITAL LETTER E WITH DIAERESIS
  {0xc38f, 'I'},      // ??	LATIN CAPITAL LETTER I WITH DIAERESIS
  {0xc396, 'O'},      // ??	LATIN CAPITAL LETTER O WITH DIAERESIS
  {0xc39c, 'U'},      // ??	LATIN CAPITAL LETTER U WITH DIAERESIS 
  {0xC39F, 's'},      // ?? 
  {0xc3a4, 'a'},      // ??	LATIN SMALL LETTER A WITH DIAERESIS
  {0xc3a6, 'a'},      // ??	LATIN SMALL LETTER AE
  {0xc3af, 'i'},      // ??	LATIN SMALL LETTER I WITH DIAERESIS
  {0xc3ab, 'e'},      // ??	LATIN SMALL LETTER E WITH DIAERESIS
  {0xc3b6, 'o'},      // ??	LATIN SMALL LETTER O WITH DIAERESIS
  {0xc3bc, 'u'},      // ??	LATIN SMALL LETTER U WITH DIAERESIS
  {0xc4b2, 'I'},      // ??	LATIN CAPITAL LIGATURE IJ  - somehow - J should be added for Dutch
  {0xc4b3, 'i'}       // ??	LATIN SMALL LIGATURE IJ - somehow - J should be added for Dutch
};

// North Germanic languages gmq
const Mapping lang_gmq[] PROGMEM = {
  {0xc386, 'A'},      // ??	LATIN CAPITAL LETTER AE
  {0xc384, 'A'},      // ??	LATIN CAPITAL LETTER A WITH DIAERESIS
  {0xc38b, 'E'},      // ??	LATIN CAPITAL LETTER E WITH DIAERESIS
  {0xc38f, 'I'},      // ??	LATIN CAPITAL LETTER I WITH DIAERESIS
  {0xc396, 'O'},      // ??	LATIN CAPITAL LETTER O WITH DIAERESIS
  {0xc39c, 'U'},      // ??	LATIN CAPITAL LETTER U WITH DIAERESIS  
  {0xc3a6, 'a'},      // ??	LATIN SMALL LETTER AE
  {0xc3a4, 'a'},      // ??	LATIN SMALL LETTER A WITH DIAERESIS
  {0xc3ab, 'e'},      // ??	LATIN SMALL LETTER E WITH DIAERESIS
  {0xc3af, 'i'},      // ??	LATIN SMALL LETTER I WITH DIAERESIS
  {0xc3b6, 'o'},      // ??	LATIN SMALL LETTER O WITH DIAERESIS
  {0xc3bc, 'u'},      // ??	LATIN SMALL LETTER U WITH DIAERESIS
  {0xc385, 'A'},      // ??  LATIN CAPITAL LETTER A WITH RING ABOVE
  {0xc392, 'O'},      // ??	LATIN CAPITAL LETTER O WITH GRAVE
  {0xc398, 'O'},      // ??	LATIN CAPITAL LETTER O WITH STROKE    
  {0xc3a5, 'a'},      // ??  LATIN SMALL LETTER A WITH RING ABOVE
  {0xc3b2, 'o'},      // ??	LATIN SMALL LETTER O WITH GRAVE
  {0xc3b8, 'o'}       // ??	LATIN SMALL LETTER O WITH STROKE
};

// Romance - roa
// https://en.wikipedia.org/wiki/Romance_languages
// ca es et fr it pt ro
const Mapping lang_roa[] PROGMEM = {
  {0xc380, 'A'},      // ??	LATIN CAPITAL LETTER A WITH GRAVE
  {0xc381, 'A'},      // ??	LATIN CAPITAL LETTER A WITH ACUTE
  {0xc383, 'A'},      // ??	LATIN CAPITAL LETTER A WITH TILDE
  {0xc382, 'A'},      // ??	LATIN CAPITAL LETTER A WITH CIRCUMFLEX
  {0xc386, 'A'},      // ??	LATIN CAPITAL LETTER AE 
  {0xc387, 'C'},      // ??	LATIN CAPITAL LETTER C WITH CEDILLA
  {0xc388, 'E'},      // ??	LATIN CAPITAL LETTER E WITH GRAVE
  {0xc389, 'E'},      // ??	LATIN CAPITAL LETTER E WITH ACUTE  
  {0xc38a, 'E'},      // ??	LATIN CAPITAL LETTER E WITH CIRCUMFLEX
  {0xc38b, 'E'},      // ??	LATIN CAPITAL LETTER E WITH DIAERESIS
  {0xc38c, 'I'},      // ??	LATIN CAPITAL LETTER I WITH GRAVE  
  {0xc38d, 'I'},      // ??	LATIN CAPITAL LETTER I WITH ACUTE  
  {0xc38e, 'I'},      // ??	LATIN CAPITAL LETTER I WITH CIRCUMFLEX
  {0xc38f, 'I'},      // ??	LATIN CAPITAL LETTER I WITH DIAERESIS
  {0xc391, 'N'},      // ??	LATIN CAPITAL LETTER N WITH TILDE - for Spanish words
  {0xc392, 'O'},      // ??	LATIN CAPITAL LETTER O WITH GRAVE
  {0xc393, 'O'},      // ??	LATIN CAPITAL LETTER O WITH ACUTE 
  {0xc394, 'O'},      // ??	LATIN CAPITAL LETTER O WITH CIRCUMFLEX
  {0xc395, 'O'},      // ??	LATIN CAPITAL LETTER O WITH TILDE
  {0xc39a, 'U'},      // ??	LATIN CAPITAL LETTER U WITH ACUTE  
  {0xc39b, 'U'},      // ??	LATIN CAPITAL LETTER U WITH CIRCUMFLEX
  {0xc39c, 'U'},      // ??	LATIN CAPITAL LETTER U WITH DIAERESIS  
  {0xc399, 'U'},      // ??	LATIN CAPITAL LETTER U WITH GRAVE
  {0xc5b8, 'Y'},      // ??	LATIN CAPITAL LETTER Y WITH DIAERESIS
  {0xc3a0, 'a'},      // ??	LATIN SMALL LETTER A WITH GRAVE
  {0xc3a1, 'a'},      // ??	LATIN SMALL LETTER A WITH ACUTE 
  {0xc3a2, 'a'},      // ??	LATIN SMALL LETTER A WITH CIRCUMFLEX
  {0xc3a3, 'a'},      // ??	LATIN SMALL LETTER A WITH TILDE  
  {0xc3a6, 'a'},      // ??	LATIN SMALL LETTER AE 
  {0xc3a7, 'c'},      // ??	LATIN SMALL LETTER C WITH CEDILLA 
  {0xc3a8, 'e'},      // ??	LATIN SMALL LETTER E WITH GRAVE
  {0xc3a9, 'e'},      // ??	LATIN SMALL LETTER E WITH ACUTE   
  {0xc3aa, 'e'},      // ??	LATIN SMALL LETTER E WITH CIRCUMFLEX
  {0xc3ab, 'e'},      // ??	LATIN SMALL LETTER E WITH DIAERESIS
  {0xc3ac, 'i'},      // ??	LATIN SMALL LETTER I WITH GRAVE  
  {0xc3ad, 'i'},      // ??	LATIN SMALL LETTER I WITH ACUTE
  {0xc3ae, 'i'},      // ??	LATIN SMALL LETTER I WITH CIRCUMFLEX
  {0xc3af, 'i'},      // ??	LATIN SMALL LETTER I WITH DIAERESIS
  {0xc3b1, 'n'},      // ??	LATIN SMALL LETTER N WITH TILDE
  {0xc3b2, 'o'},      // ??  LATIN SMALL LETTER O WITH GRAVE   
  {0xc3b3, 'o'},      // ??	LATIN SMALL LETTER O WITH ACUTE  
  {0xc3b4, 'o'},      // ??	LATIN SMALL LETTER O WITH CIRCUMFLEX
  {0xc3b5, 'o'},      // ??	LATIN SMALL LETTER O WITH TILDE  
  {0xc3ba, 'u'},      // ??	LATIN SMALL LETTER U WITH ACUTE   
  {0xc3bb, 'u'},      // ??	LATIN SMALL LETTER U WITH CIRCUMFLEX
  {0xc3bc, 'u'},      // ??	LATIN SMALL LETTER U WITH DIAERESIS  
  {0xc3b9, 'u'},      // ??	LATIN SMALL LETTER U WITH GRAVE
  {0xc3bf, 'y'},      // ??	LATIN SMALL LETTER Y WITH DIAERESIS
  {0xc3a9, 'e'},      // ??	LATIN SMALL LETTER E WITH ACUTE
  {0xc482, 'A'},      // ??	LATIN CAPITAL LETTER A WITH BREVE
  {0xc483, 'a'},      // ??	LATIN SMALL LETTER A WITH BREVE  
  {0xc592, 'O'},      // ??	LATIN CAPITAL LIGATURE OE
  {0xc593, 'o'},      // ??	LATIN SMALL LIGATURE OE
  {0xc898, 'S'},      // ??	LATIN CAPITAL LETTER S WITH COMMA BELOW
  {0xc899, 's'},      // ??	LATIN SMALL LETTER S WITH COMMA BELOW
  {0xc89a, 'T'},      // ??	LATIN CAPITAL LETTER T WITH COMMA BELOW
  {0xc89b, 't'},      // ??	LATIN SMALL LETTER T WITH COMMA BELOW 
  // for Spanish
  {0xc2a1, '!'},      // ??	INVERTED EXCLAMATION MARK
  {0xc2aa, 'a'},      // ??	FEMININE ORDINAL INDICATOR
  {0xc2ba, 'o'},      // ??	MASCULINE ORDINAL INDICATOR
  {0xc2bf, '?'}       // ??  INVERTED QUESTION MARK
};

// German 
// not really used for the LCD
// as currently the HD44780 mapping also contains the German capital Umlauts
const Mapping lang_de[] PROGMEM =  {
  {0xC384, 'A'},      // ??   // large Umlauts may be overwritten in the write method
  {0xC396, 'O'},      // ??
  {0xC39C, 'U'},      // ??
  {0xC39F, 's'},      // ?? 
  {0xC3A4, 'a'},      // ??
  {0xC3B6, 'o'},      // ??
  {0xC3BC, 'u'}       // ??
};


// Slavic
// https://en.wikipedia.org/wiki/Slavic_languages
// cs pl sk sr
const Mapping lang_sla[] PROGMEM = {
// Czech cs
// https://en.wikipedia.org/wiki/Czech_orthography cs 42(!) Letters
  {0xc381, 'A'},      // ??	LATIN CAPITAL LETTER A WITH ACUTE
  {0xc389, 'E'},      // ??	LATIN CAPITAL LETTER E WITH ACUTE
  {0xc38d, 'I'},      // ??	LATIN CAPITAL LETTER I WITH ACUTE
  {0xc393, 'O'},      // ??	LATIN CAPITAL LETTER O WITH ACUTE
  {0xc39a, 'U'},      // ??	LATIN CAPITAL LETTER U WITH ACUTE
  {0xc39d, 'Y'},      // ??	LATIN CAPITAL LETTER Y WITH ACUTE   
  {0xc3a1, 'a'},      // ??	LATIN SMALL LETTER A WITH ACUTE
  {0xc3a9, 'e'},      // ??	LATIN SMALL LETTER E WITH ACUTE
  {0xc3ad, 'i'},      // ??	LATIN SMALL LETTER I WITH ACUTE  
  {0xc3b3, 'o'},      // ??	LATIN SMALL LETTER O WITH ACUTE
  {0xc3ba, 'u'},      // ??	LATIN SMALL LETTER U WITH ACUTE
  {0xc3bd, 'y'},      // ??	LATIN SMALL LETTER Y WITH ACUTE   
  {0xc48c, 'C'},      // ??	LATIN CAPITAL LETTER C WITH CARON
  {0xc48d, 'c'},      // ??	LATIN SMALL LETTER C WITH CARON
  {0xc48e, 'D'},      // ??	LATIN CAPITAL LETTER D WITH CARON
  {0xc48f, 'd'},      // ??	LATIN SMALL LETTER D WITH CARON  
  {0xc49a, 'E'},      // ??	LATIN CAPITAL LETTER E WITH CARON
  {0xc49b, 'e'},      // ??	LATIN SMALL LETTER E WITH CARON
  {0xc587, 'N'},      // ??  LATIN CAPITAL LETTER N WITH CARON
  {0xc588, 'n'},      // ??  LATIN SMALL LETTER N WITH CARON
  {0xc598, 'R'},      // ??	LATIN CAPITAL LETTER R WITH CARON
  {0xc599, 'r'},      // ??	LATIN SMALL LETTER R WITH CARON
  {0xc5a0, 'S'},      // ??	LATIN CAPITAL LETTER S WITH CARON
  {0xc5a1, 's'},      // ??	LATIN SMALL LETTER S WITH CARON
  {0xc5a4, 'T'},      // ??	LATIN CAPITAL LETTER T WITH CARON
  {0xc5a5, 't'},      // ??	LATIN SMALL LETTER T WITH CARON
  {0xc5ae, 'U'},      // ??	LATIN CAPITAL LETTER U WITH RING ABOVE
  {0xc5af, 'u'},      // ??	LATIN SMALL LETTER U WITH RING ABOVE
  {0xc5bd, 'Z'},      // ??	LATIN CAPITAL LETTER Z WITH CARON
  {0xc5be, 'z'},      // ??	LATIN SMALL LETTER Z WITH CARON
  // add on for Slovakian sk
  {0xc394, 'O'},      // ??	LATIN CAPITAL LETTER O WITH CIRCUMFLEX
  {0xc3b4, 'o'},      // ??	LATIN SMALL LETTER O WITH CIRCUMFLEX 
  {0xc4ba, 'l'},      // ??	LATIN SMALL LETTER L WITH ACUTE
  {0xc4b9, 'L'},      // ??  LATIN CAPITAL LETTER L WITH ACUTE 
  {0xc594, 'R'},      // ??	LATIN CAPITAL LETTER R WITH ACUTE
  {0xc595, 'r'},      // ??	LATIN SMALL LETTER R WITH ACUTE
  // add on for Polish pl
  // https://en.wikipedia.org/wiki/Polish_language#Orthography
  {0xc484, 'A'},      // ??  LATIN CAPTIAL LETTER A WITH OGONEK
  {0xc485, 'a'},      // ??  LATIN SMALL LETTER A WITH OGONEK
  {0xc486, 'C'},      // ??  LATIN CAPITAL LETTER C WITH ACUTE
  {0xc487, 'c'},      // ??  LATIN SMALL LETTER C WITH ACUTE
  {0xc498, 'E'},      // ??  LATIN CAPITAL LETTER E WITH OGONEK
  {0xc499, 'e'},      // ??  LATIN SMALL LETTER E WITH OGONEK
  {0xc581, 'L'},      // ??  LATIN CAPITAL LETTER L WITH STROKE
  {0xc582, 'l'},      // ??	LATIN SMALL LETTER L WITH STROKE
  {0xc583, 'N'},      // ??  LATIN CAPITAL LETTER N WITH ACUTE
  {0xc584, 'n'},      // ??  LATIN SMALL LETTER N WITH ACUTE  
  {0xc59a, 'S'},      // ??	LATIN CAPITAL LETTER S WITH ACUTE
  {0xc59b, 's'},      // ??  LATIN SMALL LETTER S WITH ACUTE
  {0xc5b9, 'Z'},      // ??  LATIN CAPITAL LETTER Z WITH ACUTE
  {0xc5ba, 'z'},      // ??  LATIN SMALL LETTER Z WITH ACUTE
  {0xc5bb, 'Z'},      // ??	LATIN CAPITAL LETTER Z WITH DOT ABOVE
  {0xc5bc, 'z'},      // ??	LATIN SMALL LETTER Z WITH DOT ABOVE    
  // Serbian sr
  // https://en.wikipedia.org/wiki/Serbian_language
  {0xc490, 'D'},      // ??	LATIN CAPITAL LETTER D WITH STROKE
  {0xc491, 'd'},      // ??	LATIN SMALL LETTER D WITH STROKE
};


// Spanish es - and Catalan ca
// https://en.wikipedia.org/wiki/Spanish_orthography
const Mapping lang_es[] PROGMEM = {
  {0xc2a1, '!'},      // ??	INVERTED EXCLAMATION MARK
  {0xc2aa, 'a'},      // ??	FEMININE ORDINAL INDICATOR
  {0xc2ba, 'o'},      // ??	MASCULINE ORDINAL INDICATOR
  {0xc2bf, '?'},      // ??  INVERTED QUESTION MARK
  {0xc381, 'A'},      // ??	LATIN CAPITAL LETTER A WITH ACUTE
  {0xc387, 'C'},      // ??	LATIN CAPITAL LETTER C WITH CEDILLA
  {0xc389, 'E'},      // ??	LATIN CAPITAL LETTER E WITH ACUTE
  {0xc38d, 'I'},      // ??	LATIN CAPITAL LETTER I WITH ACUTE
  {0xc391, 'N'},      // ??	LATIN CAPITAL LETTER N WITH TILDE
  {0xc393, 'O'},      // ??	LATIN CAPITAL LETTER O WITH ACUTE
  {0xc39a, 'U'},      // ??	LATIN CAPITAL LETTER U WITH ACUTE
  {0xc39c, 'U'},      // ??	LATIN CAPITAL LETTER U WITH DIAERESIS
  {0xc3a1, 'a'},      // ??	LATIN SMALL LETTER A WITH ACUTE                
  {0xc3a9, 'e'},      // ??	LATIN SMALL LETTER E WITH ACUTE                
  {0xc3ad, 'i'},      // ??	LATIN SMALL LETTER I WITH ACUTE
  {0xc3b1, 'n'},      // ??	LATIN SMALL LETTER N WITH TILDE
  {0xc3b3, 'o'},      // ??	LATIN SMALL LETTER O WITH ACUTE
  {0xc3ba, 'u'},      // ??	LATIN SMALL LETTER U WITH ACUTE                
  {0xc3bc, 'u'},      // ??	LATIN SMALL LETTER U WITH DIAERESIS                
  {0xc3a7, 'c'},      // ??	LATIN SMALL LETTER C WITH CEDILLA
  // add on for catalan
  {0xc380, 'A'},      // ??	LATIN CAPITAL LETTER A WITH GRAVE
  {0xc388, 'E'},      // ??	LATIN CAPITAL LETTER E WITH GRAVE  
  {0xc38f, 'I'},      // ??	LATIN CAPITAL LETTER I WITH DIAERESIS
  {0xc392, 'O'},      // ??	LATIN CAPITAL LETTER O WITH GRAVE
  {0xc3a0, 'a'},      // ??	LATIN SMALL LETTER A WITH GRAVE
  {0xc3a8, 'e'},      // ??  LATIN SMALL LETTER E WITH GRAVE
  {0xc3af, 'i'},      // ??	LATIN SMALL LETTER I WITH DIAERESIS  
  {0xc3b2, 'o'},      // ??  LATIN SMALL LETTER O WITH GRAVE  
};

// French - fr
// https://en.wikipedia.org/wiki/French_orthography
const Mapping lang_fr[] PROGMEM = {
  {0xc380, 'A'},      // ??	LATIN CAPITAL LETTER A WITH GRAVE
  {0xc382, 'A'},      // ??	LATIN CAPITAL LETTER A WITH CIRCUMFLEX
  {0xc386, 'A'},      // ??	LATIN CAPITAL LETTER AE 
  {0xc387, 'C'},      // ??	LATIN CAPITAL LETTER C WITH CEDILLA
  {0xc388, 'E'},      // ??	LATIN CAPITAL LETTER E WITH GRAVE
  {0xc38a, 'E'},      // ??	LATIN CAPITAL LETTER E WITH CIRCUMFLEX
  {0xc38b, 'E'},      // ??	LATIN CAPITAL LETTER E WITH DIAERESIS
  {0xc38e, 'I'},      // ??	LATIN CAPITAL LETTER I WITH CIRCUMFLEX
  {0xc38f, 'I'},      // ??	LATIN CAPITAL LETTER I WITH DIAERESIS
  {0xc391, 'N'},      // ??	LATIN CAPITAL LETTER N WITH TILDE - for Spanish words 
  {0xc394, 'O'},      // ??	LATIN CAPITAL LETTER O WITH CIRCUMFLEX
  {0xc39b, 'U'},      // ??	LATIN CAPITAL LETTER U WITH CIRCUMFLEX
  {0xc39c, 'U'},      // ??	LATIN CAPITAL LETTER U WITH DIAERESIS  
  {0xc399, 'U'},      // ??	LATIN CAPITAL LETTER U WITH GRAVE
  {0xc389, 'E'},      // ??	LATIN CAPITAL LETTER E WITH ACUTE
  {0xc5b8, 'Y'},      // ??	LATIN CAPITAL LETTER Y WITH DIAERESIS
  {0xc3a0, 'a'},      // ??	LATIN SMALL LETTER A WITH GRAVE
  {0xc3a2, 'a'},      // ??	LATIN SMALL LETTER A WITH CIRCUMFLEX
  {0xc3a6, 'a'},      // ??	LATIN SMALL LETTER AE 
  {0xc3a7, 'c'},      // ??	LATIN SMALL LETTER C WITH CEDILLA 
  {0xc3a8, 'e'},      // ??	LATIN SMALL LETTER E WITH GRAVE
  {0xc3aa, 'e'},      // ??	LATIN SMALL LETTER E WITH CIRCUMFLEX
  {0xc3ab, 'e'},      // ??	LATIN SMALL LETTER E WITH DIAERESIS
  {0xc3ae, 'i'},      // ??	LATIN SMALL LETTER I WITH CIRCUMFLEX
  {0xc3af, 'i'},      // ??	LATIN SMALL LETTER I WITH DIAERESIS
  {0xc3b1, 'n'},      // ??	LATIN SMALL LETTER N WITH TILDE - for Spanish words
  {0xc3b4, 'o'},      // ??	LATIN SMALL LETTER O WITH CIRCUMFLEX
  {0xc3bb, 'u'},      // ??	LATIN SMALL LETTER U WITH CIRCUMFLEX
  {0xc3bc, 'u'},      // ??	LATIN SMALL LETTER U WITH DIAERESIS  
  {0xc3b9, 'u'},      // ??	LATIN SMALL LETTER U WITH GRAVE
  {0xc3bf, 'y'},      // ??	LATIN SMALL LETTER Y WITH DIAERESIS
  {0xc3a9, 'e'},      // ??	LATIN SMALL LETTER E WITH ACUTE
  {0xc592, 'O'},      // ??	LATIN CAPITAL LIGATURE OE
  {0xc593, 'o'}       // ??	LATIN SMALL LIGATURE OE
};

// english - en
// MISSING: to be checked if exchangable with north germanic
const Mapping lang_en[] PROGMEM = {
  {0xc386, 'A'},      // ??	LATIN CAPITAL LETTER AE
  {0xc384, 'A'},      // ??	LATIN CAPITAL LETTER A WITH DIAERESIS
  {0xc38b, 'E'},      // ??	LATIN CAPITAL LETTER E WITH DIAERESIS
  {0xc38f, 'I'},      // ??	LATIN CAPITAL LETTER I WITH DIAERESIS
  {0xc396, 'O'},      // ??	LATIN CAPITAL LETTER O WITH DIAERESIS
  {0xc39c, 'U'},      // ??	LATIN CAPITAL LETTER U WITH DIAERESIS  
  {0xc3a6, 'a'},      // ??	LATIN SMALL LETTER AE
  {0xc3a4, 'a'},      // ??	LATIN SMALL LETTER A WITH DIAERESIS
  {0xc3ab, 'e'},      // ??	LATIN SMALL LETTER E WITH DIAERESIS
  {0xc3af, 'i'},      // ??	LATIN SMALL LETTER I WITH DIAERESIS
  {0xc3b6, 'o'},      // ??	LATIN SMALL LETTER O WITH DIAERESIS
  {0xc3bc, 'u'}       // ??	LATIN SMALL LETTER U WITH DIAERESIS
};

// Finnish - fi
//
const Mapping lang_fi[] PROGMEM = {
  {0xc384, 'A'},      // ??	LATIN CAPITAL LETTER A WITH DIAERESIS
  {0xc385, 'A'},      // ??  LATIN CAPITAL LETTER A WITH RING ABOVE
  {0xc396, 'O'},      // ??	LATIN CAPITAL LETTER O WITH DIAERESIS
  {0xc3a4, 'a'},      // ??	LATIN SMALL LETTER A WITH DIAERESIS  
  {0xc3a5, 'a'},      // ??  LATIN SMALL LETTER A WITH RING ABOVE
  {0xc3b6, 'o'},      // ??	LATIN SMALL LETTER O WITH DIAERESIS  
  {0xc5a0, 'S'},      // ??	LATIN CAPITAL LETTER S WITH CARON
  {0xc5a1, 's'},      // ??	LATIN SMALL LETTER S WITH CARON  
  {0xc5bd, 'Z'},      // ??	LATIN CAPITAL LETTER Z WITH CARON
  {0xc5be, 'z'}       // ??	LATIN SMALL LETTER Z WITH CARON 
};


// Hungarian - hu
// https://en.wikipedia.org/wiki/Hungarian_alphabet
const Mapping lang_hu[] PROGMEM ={
  {0xc381, 'A'},      // ??	LATIN CAPITAL LETTER A WITH ACUTE
  {0xc389, 'E'},      // ??	LATIN CAPITAL LETTER E WITH ACUTE
  {0xc393, 'O'},      // ??	LATIN CAPITAL LETTER O WITH ACUTE
  {0xc396, 'O'},      // ??	LATIN CAPITAL LETTER O WITH DIAERESIS
  {0xc39a, 'U'},      // ??	LATIN CAPITAL LETTER U WITH ACUTE
  {0xc39c, 'U'},      // ??	LATIN CAPITAL LETTER U WITH DIAERESIS
  {0xc3a1, 'a'},      // ??	LATIN SMALL LETTER A WITH ACUTE            
  {0xc3a9, 'e'},      // ??	LATIN SMALL LETTER E WITH ACUTE           
  {0xc3b3, 'o'},      // ??	LATIN SMALL LETTER O WITH ACUTE
  {0xc3b6, 'o'},      // ??	LATIN SMALL LETTER O WITH DIAERESIS 
  {0xc3ba, 'u'},      // ??	LATIN SMALL LETTER U WITH ACUTE           
  {0xc3bc, 'u'},      // ??	LATIN SMALL LETTER U WITH DIAERESIS 
  {0xc590, 'O'},      // ??	LATIN CAPITAL LETTER O WITH DOUBLE ACUTE
  {0xc591, 'o'},      // ??	LATIN SMALL LETTER O WITH DOUBLE ACUTE            
  {0xc5b0, 'U'},      // ??	LATIN CAPITAL LETTER U WITH DOUBLE ACUTE
  {0xc5b1, 'u'}       // ??	LATIN SMALL LETTER U WITH DOUBLE ACUTE   
};

// Cyrillic
// transliteration https://en.wikipedia.org/wiki/Romanization_of_Russian
// GOST 16876-71(1) because of single character
// smaller subset
const Mapping cyrillic_GOST16876_71_1[] PROGMEM = {
  {0xd081, 'E'},  // ??  CYRILLIC CAPITAL LETTER IO
  {0xd090, 'A'},  // ??  CYRILLIC CAPITAL LETTER A
  {0xd091, 'B'},  // ??  CYRILLIC CAPITAL LETTER BE
  {0xd092, 'V'},  // ??  CYRILLIC CAPITAL LETTER VE
  {0xd093, 'G'},  // ??  CYRILLIC CAPITAL LETTER GHE
  {0xd094, 'D'},  // ??  CYRILLIC CAPITAL LETTER DE
  {0xd095, 'E'},  // ??  CYRILLIC CAPITAL LETTER IE
  {0xd096, 'Z'},  // ??  CYRILLIC CAPITAL LETTER ZHE
  {0xd097, 'Z'},  // ??  CYRILLIC CAPITAL LETTER ZE
  {0xd098, 'I'},  // ??  CYRILLIC CAPITAL LETTER I
  {0xd099, 'J'},  // ??  CYRILLIC CAPITAL LETTER SHORT I
  {0xd09a, 'K'},  // ??  CYRILLIC CAPITAL LETTER KA
  {0xd09b, 'L'},  // ??  CYRILLIC CAPITAL LETTER EL
  {0xd09c, 'M'},  // ??  CYRILLIC CAPITAL LETTER EM
  {0xd09d, 'N'},  // ??  CYRILLIC CAPITAL LETTER EN
  {0xd09e, 'O'},  // ??  CYRILLIC CAPITAL LETTER O
  {0xd09f, 'P'},  // ??  CYRILLIC CAPITAL LETTER PE
  {0xd0a0, 'R'},  // ??  CYRILLIC CAPITAL LETTER ER
  {0xd0a1, 'S'},  // ??  CYRILLIC CAPITAL LETTER ES
  {0xd0a2, 'T'},  // ??  CYRILLIC CAPITAL LETTER TE
  {0xd0a3, 'U'},  // ??  CYRILLIC CAPITAL LETTER U
  {0xd0a4, 'F'},  // ??  CYRILLIC CAPITAL LETTER EF
  {0xd0a5, 'H'},  // ??  CYRILLIC CAPITAL LETTER HA
  {0xd0a6, 'C'},  // ??  CYRILLIC CAPITAL LETTER TSE
  {0xd0a7, 'C'},  // ??  CYRILLIC CAPITAL LETTER CHE
  {0xd0a8, 'S'},  // ??  CYRILLIC CAPITAL LETTER SHA
  {0xd0a9, 'S'},  // ??  CYRILLIC CAPITAL LETTER SHCHA
  {0xd0aa, '"'},  // ??  CYRILLIC CAPITAL LETTER HARD SIGN
  {0xd0ab, 'Y'},  // ??  CYRILLIC CAPITAL LETTER YERU
  {0xd0ac, '\''}, // ??  CYRILLIC CAPITAL LETTER SOFT SIGN
  {0xd0ad, 'E'},  // ??  CYRILLIC CAPITAL LETTER E
  {0xd0ae, 'J'},  // ??  CYRILLIC CAPITAL LETTER YU - JU
  {0xd0af, 'J'},  // ??  CYRILLIC CAPITAL LETTER YA  - JA
  {0xd0b0, 'a'},  // ??  CYRILLIC SMALL LETTER A
  {0xd0b1, 'b'},  // ??  CYRILLIC SMALL LETTER BE
  {0xd0b2, 'v'},  // ??  CYRILLIC SMALL LETTER VE
  {0xd0b3, 'g'},  // ??  CYRILLIC SMALL LETTER GHE
  {0xd0b4, 'd'},  // ??  CYRILLIC SMALL LETTER DE
  {0xd0b5, 'e'},  // ??  CYRILLIC SMALL LETTER IE
  {0xd0b6, 'z'},  // ??  CYRILLIC SMALL LETTER ZHE
  {0xd0b7, 'z'},  // ??  CYRILLIC SMALL LETTER ZE
  {0xd0b8, 'z'},  // ??  CYRILLIC SMALL LETTER I
  {0xd0b9, 'j'},  // ??  CYRILLIC SMALL LETTER SHORT I
  {0xd0ba, 'k'},  // ??  CYRILLIC SMALL LETTER KA
  {0xd0bb, 'l'},  // ??  CYRILLIC SMALL LETTER EL
  {0xd0bc, 'm'},  // ??  CYRILLIC SMALL LETTER EM
  {0xd0bd, 'n'},  // ??  CYRILLIC SMALL LETTER EN
  {0xd0be, 'o'},  // ??  CYRILLIC SMALL LETTER O
  {0xd0bf, 'p'},  // ??  CYRILLIC SMALL LETTER PE
  {0xd180, 'r'},  // ??  CYRILLIC SMALL LETTER ER
  {0xd181, 's'},  // ??  CYRILLIC SMALL LETTER ES
  {0xd182, 't'},  // ??  CYRILLIC SMALL LETTER TE
  {0xd183, 'u'},  // ??  CYRILLIC SMALL LETTER U
  {0xd184, 'f'},  // ??  CYRILLIC SMALL LETTER EF
  {0xd185, 'h'},  // ??  CYRILLIC SMALL LETTER HA
  {0xd186, 'c'},  // ??  CYRILLIC SMALL LETTER TSE
  {0xd187, 'c'},  // ??  CYRILLIC SMALL LETTER CHE
  {0xd188, 's'},  // ??  CYRILLIC SMALL LETTER SHA
  {0xd189, 's'},  // ??  CYRILLIC SMALL LETTER SHCHA
  {0xd18a, '"'},  // ??  CYRILLIC SMALL LETTER HARD SIGN
  {0xd18b, 'y'},  // ??  CYRILLIC SMALL LETTER YERU
  {0xd18c, '\''}, // ??  CYRILLIC SMALL LETTER SOFT SIGN
  {0xd18d, 'e'},  // ??  CYRILLIC SMALL LETTER E
  {0xd18e, 'j'},  // ??  CYRILLIC SMALL LETTER YU
  {0xd18f, 'j'},  // ??  CYRILLIC SMALL LETTER YA
  // Pre 1918 letters
  {0xd086, 'I'},  // ??  CYRILLIC CAPITAL LETTER BYELORUSSIAN-UKRAINIAN I  
  {0xd190, 'i'},  // ??  CYRILLIC SMALL LETTER IE WITH GRAVE
  {0xd191, 'e'},  // ??  CYRILLIC SMALL LETTER IO
  {0xd192, 'e'},  // ??  CYRILLIC SMALL LETTER DJE
  {0xd193, 'y'},  // ??  CYRILLIC SMALL LETTER GJE
  {0xd196, 'i'},  // ??  CYRILLIC SMALL LETTER BYELORUSSIAN-UKRAINIAN I
  {0xd197, 'i'},  // ??  CYRILLIC SMALL LETTER YI
  {0xd1a2, 'E'},  // ??  CYRILLIC CAPITAL LETTER YAT
  {0xd1a3, 'e'},  // ??  CYRILLIC SMALL LETTER YAT  
  {0xd1b2, 'F'},  // ??  CYRILLIC CAPITAL LETTER FITA
  {0xd1b3, 'f'},  // ??  CYRILLIC SMALL LETTER FITA  
  {0xd1b4, 'Y'},  // ??  CYRILLIC CAPITAL LETTER IZHITSA
  {0xd1b5, 'y'},  // ??  CYRILLIC SMALL LETTER IZHITSA
};
#endif
