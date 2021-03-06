#ifndef NJD_SET_LONG_VOWEL_RULE_H
#define NJD_SET_LONG_VOWEL_RULE_H

#ifdef __cplusplus
#define NJD_SET_LONG_VOWEL_RULE_H_START extern "C" {
#define NJD_SET_LONG_VOWEL_RULE_H_END   }
#else
#define NJD_SET_LONG_VOWEL_RULE_H_START
#define NJD_SET_LONG_VOWEL_RULE_H_END
#endif                          /* __CPLUSPLUS */

NJD_SET_LONG_VOWEL_RULE_H_START;

static const char njd_set_long_vowel_kanji_range[] = {
#ifdef CHARSET_EUC_JP
   2, 0xA1, 0xFE,
   3, 0x8F, 0x8F,
#endif                          /* CHARSET_EUC_JP */
#ifdef CHARSET_SHIFT_JIS
   2, 0x81, 0xFC,
#endif                          /* CHARSET_SHIFT_JIS */
#ifdef CHARSET_UTF_8
   2, 0xC0, 0xDF,
   3, 0xE0, 0xEF,
   4, 0xF0, 0xF7,
#endif                          /* CHARSET_UTF_8 */
   -1, -1, -1
};

static const char *njd_set_long_vowel_table[] = {
   "\xa5\xa8\xa5\xa4", "\xa5\xa8\xa1\xbc",
   "\xa5\xb1\xa5\xa4", "\xa5\xb1\xa1\xbc",
   "\xa5\xbb\xa5\xa4", "\xa5\xbb\xa1\xbc",
   "\xa5\xc6\xa5\xa4", "\xa5\xc6\xa1\xbc",
   "\xa5\xcd\xa5\xa4", "\xa5\xcd\xa1\xbc",
   "\xa5\xd8\xa5\xa4", "\xa5\xd8\xa1\xbc",
   "\xa5\xe1\xa5\xa4", "\xa5\xe1\xa1\xbc",
   "\xa5\xec\xa5\xa4", "\xa5\xec\xa1\xbc",
   "\xa5\xb2\xa5\xa4", "\xa5\xb2\xa1\xbc",
   "\xa5\xbc\xa5\xa4", "\xa5\xbc\xa1\xbc",
   "\xa5\xc7\xa5\xa4", "\xa5\xc7\xa1\xbc",
   "\xa5\xd9\xa5\xa4", "\xa5\xd9\xa1\xbc",
   "\xa5\xda\xa5\xa4", "\xa5\xda\xa1\xbc",
   "\xa5\xf1\xa5\xa4", "\xa5\xf1\xa1\xbc",
   NULL, NULL
};

NJD_SET_LONG_VOWEL_RULE_H_END;

#endif                          /* !NJD_SET_LONG_VOWEL_RULE_H */
