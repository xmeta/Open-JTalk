#ifndef NJD_SET_PRONUNCIATION_C
#define NJD_SET_PRONUNCIATION_C

#ifdef __cplusplus
#define NJD_SET_PRONUNCIATION_C_START extern "C" {
#define NJD_SET_PRONUNCIATION_C_END   }
#else
#define NJD_SET_PRONUNCIATION_C_START
#define NJD_SET_PRONUNCIATION_C_END
#endif                          /* __CPLUSPLUS */

NJD_SET_PRONUNCIATION_C_START;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "njd.h"
#include "njd_set_pronunciation.h"

#ifdef ASCII_HEADER
#if defined(CHARSET_EUC_JP)
#include "njd_set_pronunciation_rule_ascii_for_euc_jp.h"
#elif defined(CHARSET_SHIFT_JIS)
#include "njd_set_pronunciation_rule_ascii_for_shift_jis.h"
#elif defined(CHARSET_UTF_8)
#include "njd_set_pronunciation_rule_ascii_for_utf_8.h"
#else
#error CHARSET is not specified
#endif
#else
#if defined(CHARSET_EUC_JP)
#include "njd_set_pronunciation_rule_euc_jp.h"
#elif defined(CHARSET_SHIFT_JIS)
#include "njd_set_pronunciation_rule_shift_jis.h"
#elif defined(CHARSET_UTF_8)
#include "njd_set_pronunciation_rule_utf_8.h"
#else
#error CHARSET is not specified
#endif
#endif

#define MAXBUFLEN 1024

static int strtopcmp(const char *str, const char *pattern)
{
   int i;

   for (i = 0;; i++) {
      if (pattern[i] == '\0')
         return i;
      if (str[i] == '\0')
         return -1;
      if (str[i] != pattern[i])
         return -1;
   }
}

void njd_set_pronunciation(NJD * njd)
{
   NJDNode *node;
   const char *str;
   int i, j = 0;
   int pos;
   int len;

   for (node = njd->head; node != NULL; node = node->next) {
      if (NJDNode_get_mora_size(node) == 0) {
         NJDNode_set_read(node, NULL);
         NJDNode_set_pron(node, NULL);
         if (strcmp(NJDNode_get_pos(node), NJD_SET_PRONUNCIATION_KIGOU) == 0 || strcmp(NJDNode_get_pos_group1(node), NJD_SET_PRONUNCIATION_KAZU) == 0) {        /* for symbol */
            for (i = 0; njd_set_pronunciation_symbol_list[i] != NULL; i += 2)
               if (strcmp(NJDNode_get_string(node), njd_set_pronunciation_symbol_list[i]) == 0) {
                  NJDNode_set_read(node, (char *) njd_set_pronunciation_symbol_list[i + 1]);
                  NJDNode_set_pron(node, (char *) njd_set_pronunciation_symbol_list[i + 1]);
                  break;
               }
         } else if (strcmp(NJDNode_get_pron(node), "*") == 0) { /* for others */
            str = NJDNode_get_string(node);
            len = strlen(str);
            for (pos = 0; pos < len;) {
               for (i = 0, j = 0; njd_set_pronunciation_list[i] != NULL; i += 3) {
                  j = strtopcmp(&str[pos], njd_set_pronunciation_list[i]);
                  if (j > 0)
                     break;
               }
               if (j > 0) {
                  pos += j;
                  NJDNode_add_read(node, (char *) njd_set_pronunciation_list[i + 1]);
                  NJDNode_add_pron(node, (char *) njd_set_pronunciation_list[i + 1]);
                  NJDNode_add_mora_size(node, atoi(njd_set_pronunciation_list[i + 2]));
               } else {
                  pos++;
               }
            }
            NJDNode_set_pos(node, NJD_SET_PRONUNCIATION_FILLER);
            NJDNode_set_pos_group1(node, NULL);
            NJDNode_set_pos_group2(node, NULL);
            NJDNode_set_pos_group3(node, NULL);
         }
      }
   }
   NJD_remove_silent_node(njd);

   for (node = njd->head; node != NULL; node = node->next) {
      if (node->next != NULL
          && strcmp(NJDNode_get_pron(node->next), NJD_SET_PRONUNCIATION_U) == 0
          && strcmp(NJDNode_get_pos(node->next), NJD_SET_PRONUNCIATION_JODOUSHI) == 0
          && (strcmp(NJDNode_get_pos(node), NJD_SET_PRONUNCIATION_DOUSHI) == 0
              || strcmp(NJDNode_get_pos(node), NJD_SET_PRONUNCIATION_JODOUSHI) == 0)
          && NJDNode_get_mora_size(node) > 0) {
         NJDNode_set_pron(node->next, NJD_SET_PRONUNCIATION_CHOUON);
      }
      if (node->next != NULL
          && strcmp(NJDNode_get_pos(node), NJD_SET_PRONUNCIATION_JODOUSHI) == 0
          && strcmp(NJDNode_get_string(node->next), NJD_SET_PRONUNCIATION_QUESTION) == 0) {
         if (strcmp(NJDNode_get_string(node), NJD_SET_PRONUNCIATION_DESU_STR) == 0)
            NJDNode_set_pron(node, NJD_SET_PRONUNCIATION_DESU_PRON);
         else if (strcmp(NJDNode_get_string(node), NJD_SET_PRONUNCIATION_MASU_STR) == 0)
            NJDNode_set_pron(node, NJD_SET_PRONUNCIATION_MASU_PRON);
      }
   }
}

NJD_SET_PRONUNCIATION_C_END;

#endif                          /* !NJD_SET_PRONUNCIATION_C */
