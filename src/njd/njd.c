#ifndef NJD_C
#define NJD_C

#ifdef __cplusplus
#define NJD_C_START extern "C" {
#define NJD_C_END   }
#else
#define NJD_C_START
#define NJD_C_END
#endif                          /* __CPLUSPLUS */

NJD_C_START;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "njd.h"

#define MAXBUFLEN 1024

static int get_token_from_string(const char *str, int *index, char *buff, char d)
{
   char c;
   int i;

   buff[0] = '\0';

   c = str[(*index)];
   if (c == '\0')
      return 0;
   if (c == d) {
      (*index)++;
      return 0;
   }

   while (c == '\n' || c == '\r' || c == '\t') {
      if (c == '\0')
         return 0;
      c = str[++(*index)];
   }

   for (i = 0; c != d && c != '\n' && c != '\r' && c != '\t' && c != '\0'; i++) {
      buff[i] = c;
      c = str[++(*index)];
   }
   if (c == d)
      (*index)++;

   buff[i] = '\0';
   return i;
}

static int get_token_from_fp(FILE * fp, char *buff, char d)
{
   char c;
   int i;

   buff[0] = '\0';

   if (feof(fp))
      return 0;
   c = fgetc(fp);
   if (c == d) {
      buff[0] = '\0';
      return 0;
   }

   while (c == '\n' || c == '\r' || c == '\t') {
      if (feof(fp))
         return 0;
      c = getc(fp);
   }

   for (i = 0; c != d && c != '\n' && c != '\r' && c != '\t' && !feof(fp); i++) {
      buff[i] = c;
      c = fgetc(fp);
   }

   buff[i] = '\0';
   return i;
}

void NJD_initialize(NJD * njd)
{
   njd->head = NULL;
   njd->tail = NULL;
}

void NJD_load(NJD * njd, const char *str)
{
   int i = 0;
   NJDNode *node = NULL;
   char string[MAXBUFLEN];
   char pos[MAXBUFLEN];
   char pos_group1[MAXBUFLEN];
   char pos_group2[MAXBUFLEN];
   char pos_group3[MAXBUFLEN];
   char ctype[MAXBUFLEN];
   char cform[MAXBUFLEN];
   char orig[MAXBUFLEN];
   char read[MAXBUFLEN];
   char pron[MAXBUFLEN];
   char acc[MAXBUFLEN];
   char mora_size[MAXBUFLEN];
   char chain_rule[MAXBUFLEN];
   char chain_flag[MAXBUFLEN];

   if (strlen(str) < 1) {
      fprintf(stderr, "WARNING: NJD_load() in njd.c: Input string should not be empty.");
      return;
   }

   while (1) {
      get_token_from_string(str, &i, string, ',');
      if (get_token_from_string(str, &i, pos, ',') <= 0)
         break;
      if (get_token_from_string(str, &i, pos_group1, ',') <= 0)
         break;
      if (get_token_from_string(str, &i, pos_group2, ',') <= 0)
         break;
      if (get_token_from_string(str, &i, pos_group3, ',') <= 0)
         break;
      if (get_token_from_string(str, &i, ctype, ',') <= 0)
         break;
      if (get_token_from_string(str, &i, cform, ',') <= 0)
         break;
      get_token_from_string(str, &i, orig, ',');
      get_token_from_string(str, &i, read, ',');
      get_token_from_string(str, &i, pron, ',');
      if (get_token_from_string(str, &i, acc, '/') <= 0)
         break;
      if (get_token_from_string(str, &i, mora_size, ',') <= 0)
         break;
      get_token_from_string(str, &i, chain_rule, ',');
      if (get_token_from_string(str, &i, chain_flag, ',') <= 0)
         break;
      node = (NJDNode *) calloc(1, sizeof(NJDNode));
      NJDNode_initialize(node);
      NJDNode_set_string(node, string);
      NJDNode_set_pos(node, pos);
      NJDNode_set_pos_group1(node, pos_group1);
      NJDNode_set_pos_group2(node, pos_group2);
      NJDNode_set_pos_group3(node, pos_group3);
      NJDNode_set_ctype(node, ctype);
      NJDNode_set_cform(node, cform);
      NJDNode_set_orig(node, orig);
      NJDNode_set_read(node, read);
      NJDNode_set_pron(node, pron);
      NJDNode_set_acc(node, atoi(acc));
      NJDNode_set_mora_size(node, atoi(mora_size));
      NJDNode_set_chain_rule(node, chain_rule);
      NJDNode_set_chain_flag(node, atoi(chain_flag));
      NJD_push_node(njd, node);
   }
}

void NJD_load_from_fp(NJD * njd, FILE * fp)
{
   NJDNode *node = NULL;
   char string[MAXBUFLEN];
   char pos[MAXBUFLEN];
   char pos_group1[MAXBUFLEN];
   char pos_group2[MAXBUFLEN];
   char pos_group3[MAXBUFLEN];
   char ctype[MAXBUFLEN];
   char cform[MAXBUFLEN];
   char orig[MAXBUFLEN];
   char read[MAXBUFLEN];
   char pron[MAXBUFLEN];
   char acc[MAXBUFLEN];
   char mora_size[MAXBUFLEN];
   char chain_rule[MAXBUFLEN];
   char chain_flag[MAXBUFLEN];

   if (fp == NULL) {
      fprintf(stderr, "WARNING: NJD_load_from_fp() in njd.c: File pointer should not be null.");
      return;
   }

   while (1) {
      get_token_from_fp(fp, string, ',');
      if (get_token_from_fp(fp, pos, ',') <= 0)
         break;
      if (get_token_from_fp(fp, pos_group1, ',') <= 0)
         break;
      if (get_token_from_fp(fp, pos_group2, ',') <= 0)
         break;
      if (get_token_from_fp(fp, pos_group3, ',') <= 0)
         break;
      if (get_token_from_fp(fp, ctype, ',') <= 0)
         break;
      if (get_token_from_fp(fp, cform, ',') <= 0)
         break;
      get_token_from_fp(fp, orig, ',');
      get_token_from_fp(fp, read, ',');
      get_token_from_fp(fp, pron, ',');
      if (get_token_from_fp(fp, acc, '/') <= 0)
         break;
      if (get_token_from_fp(fp, mora_size, ',') <= 0)
         break;
      get_token_from_fp(fp, chain_rule, ',');
      if (get_token_from_fp(fp, chain_flag, ',') <= 0)
         break;
      node = (NJDNode *) calloc(1, sizeof(NJDNode));
      NJDNode_initialize(node);
      NJDNode_set_string(node, string);
      NJDNode_set_pos(node, pos);
      NJDNode_set_pos_group1(node, pos_group1);
      NJDNode_set_pos_group2(node, pos_group2);
      NJDNode_set_pos_group3(node, pos_group3);
      NJDNode_set_ctype(node, ctype);
      NJDNode_set_cform(node, cform);
      NJDNode_set_orig(node, orig);
      NJDNode_set_read(node, read);
      NJDNode_set_pron(node, pron);
      NJDNode_set_acc(node, atoi(acc));
      NJDNode_set_mora_size(node, atoi(mora_size));
      NJDNode_set_chain_rule(node, chain_rule);
      NJDNode_set_chain_flag(node, atoi(chain_flag));
      NJD_push_node(njd, node);
   }
}

int NJD_get_size(NJD * njd)
{
   int i;
   NJDNode *node = njd->head;

   for (i = 0; node != NULL; i++)
      node = node->next;
   return i;
}

void NJD_push_node(NJD * njd, NJDNode * node)
{
   if (njd->head == NULL) {
      njd->head = node;
   } else {
      njd->tail->next = node;
      node->prev = njd->tail;
   }
   while (node->next != NULL)
      node = node->next;
   njd->tail = node;
}

/* remove node and return next node */
static NJDNode *NJD_remove_node(NJD * njd, NJDNode * node)
{
   NJDNode *next;

   if (node == njd->head && node == njd->tail) {
      njd->head = NULL;
      njd->tail = NULL;
      next = NULL;
   } else if (node == njd->head) {
      njd->head = node->next;
      njd->head->prev = NULL;
      next = njd->head;
   } else if (node == njd->tail) {
      njd->tail = node->prev;
      njd->tail->next = NULL;
      next = NULL;
   } else {
      node->prev->next = node->next;
      node->next->prev = node->prev;
      next = node->next;
   }
   NJDNode_clear(node);
   free(node);
   return next;
}

void NJD_remove_silent_node(NJD * njd)
{
   NJDNode *node;

   for (node = njd->head; node != NULL;)
      if (strcmp(NJDNode_get_pron(node), "*") == 0)
         node = NJD_remove_node(njd, node);
      else
         node = node->next;
}

void NJD_print(NJD * njd)
{
   NJD_fprint(njd, stdout);
}

void NJD_fprint(NJD * njd, FILE * fp)
{
   NJDNode *node;

   for (node = njd->head; node != NULL; node = node->next)
      NJDNode_fprint(node, fp);
}

void NJD_sprint(NJD * njd, char *buff, const char *split_code)
{
   NJDNode *node;

   strcpy(buff, "");
   for (node = njd->head; node != NULL; node = node->next)
      NJDNode_sprint(node, buff, split_code);
}

void NJD_refresh(NJD * njd)
{
   NJD_clear(njd);
   NJD_initialize(njd);
}

void NJD_clear(NJD * njd)
{
   NJDNode *node;

   while (njd->head != NULL) {
      node = njd->head->next;
      NJDNode_clear(njd->head);
      free(njd->head);
      njd->head = node;
   }
   njd->tail = NULL;
}

NJD_C_END;

#endif                          /* !NJD_C */
