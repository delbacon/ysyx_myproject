/***************************************************************************************
* Copyright (c) 2014-2024 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include <isa.h>
#include <ctype.h>

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>


#define EXPRLEN 65536
enum {
  TK_NOTYPE = 256, TK_EQ,

  /* TODO: Add more token types */
  TK_NUM   ,   // 十进制整数
};

static struct rule {
  const char *regex;
  int token_type;
} rules[] = {

  /* TODO: Add more rules.
   * Pay attention to the precedence level of different rules.
   */

  {" +",     TK_NOTYPE },         // spaces
  {"\\+",    '+'       },         // plus
  {"==",     TK_EQ     },         // equal
  {"[0-9]+", TK_NUM    },         // 0-9
  {"\\-",    '-'       },         // minus
  {"\\*",    '*'       },         // multi
  {"/"  ,    '/'       },         // division
  {"\\(",    '('       },         // left parentheses
  {"\\)",    ')'       },         // right parentheses

};

#define NR_REGEX ARRLEN(rules)

static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i ++) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0) {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}



typedef struct token {
  int type;
  char str[32];
} Token;

static Token tokens[EXPRLEN] __attribute__((used)) = {};
static int nr_token __attribute__((used))  = 0;

static bool make_token(char *e) {
  int position = 0;
  int i;
  regmatch_t pmatch;

  nr_token = 0;

  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i ++) {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
            i, rules[i].regex, position, substr_len, substr_len, substr_start);

        position += substr_len;


        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */
        //如果是空格，直接跳过
        if (rules[i].token_type == TK_NOTYPE) {
          break;
        }
        //其他存在的符号则存一次type
        tokens[nr_token].type = rules[i].token_type;

        //switch用来处理特殊情况，如需要存子串
        switch (rules[i].token_type) {
          case TK_EQ     ://暂时不用处理
            break;
          case TK_NUM    :
            if(substr_len >= EXPRLEN) {
              printf("Error: token too long (>=32 chars): %.*s\n", substr_len, substr_start);
              return false;
            }
            strncpy(tokens[nr_token].str, substr_start, substr_len);
            tokens[nr_token].str[substr_len] = '\0';
            break;
          default: 
            break;
        }
        nr_token++;
        break;
      }
    }

    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }

  return true;
}

int check_parentheses(int p, int q) {
    if(tokens[p].type == '(' && tokens[q].type == ')'){//如果式子左右两端都有括号
    int flag = 0;
      for(int j=p ;j<=q;j++){
        if(tokens[j].type == ')'){
          flag -- ;
        }else if(tokens[j].type == '('){
          flag ++ ;
        }
        if (flag == 0) return j==q;
      }
    }
  return false;
}


/*
int find_main_op(int p, int q) 
{
  int ret = -1, par = 0, op_type = 0;
  for (int i = p; i <= q; i++) {
    if (tokens[i].type == TK_NUM) {
      continue;
    }
    if (tokens[i].type == '(') {
      par++;
    } else if (tokens[i].type == ')') {
      if (par == 0) {
        return -1;
      }
      par--;
    } else if (par > 0) {
      continue;
    } else {
      int tmp_type = 0;
      switch (tokens[i].type) {
      case '*': case '/': tmp_type = 1; break;
      case '+': case '-': tmp_type = 2; break;
      default: assert(0);
      }
      if (tmp_type >= op_type) {
        op_type = tmp_type;
        ret = i;
      }
    }
  }
  if (par != 0) return -1;
  return ret;
}
*/
int find_main_op(int p, int q) 
{
  int flag_min = 0;
  int cnt = 0;
  for(int i=p;i<=q;i++){
    if (tokens[i].type == TK_NUM) {
      continue;
    }

    if(tokens[i].type == '('){
      cnt++;
    }else if(tokens[i].type == ')'){
      if(cnt == 0) return -1;
      cnt--;
    }else if(cnt > 0) continue;
    else if (tokens[i].type == '+' || tokens[i].type == '-'){
      flag_min = 1 ;
    }
  }

  if(cnt != 0){ 
    printf("Error: ( ) not match\n");
    return -1;
  }

  for(int i=q;i>=p;i--){
    //最后选择同级运算符里最后面的输出
    if(flag_min == 0){
      if(tokens[i].type == '*' || tokens[i].type == '/'){
        return i;
      }
    }else{
      if(tokens[i].type == '+' || tokens[i].type == '-'){
        return i;
      }
    }
  }
  return -1;
}

static word_t eval(int p,int q, bool *legal) {
  if (p > q) {
    /* Bad expression */
    *legal = false;
    printf("Error: bad expression\n");
  }
  else if (p == q) {
    /* Single token.
     * For now this token should be a number.
     * Return the value of the number.
     */
    *legal = true;
    if(tokens[p].type != TK_NUM){
      *legal = false;
      printf("Error: the first token is not a number\n");
      return 0;
    }
    word_t n = strtol(tokens[p].str, NULL, 10);
    return n;
  }
  else if (check_parentheses(p, q) == true) {
    /* The expression is surrounded by a matched pair of parentheses.
     * If that is the case, just throw away the parentheses.
     */

    return eval(p + 1, q - 1, legal);
  }
  else {
    int op = find_main_op(p, q);
    if(op == -1){
      printf("Error: no operator found\n");
      return 0;
    }
    
    word_t val1 = eval(p, op - 1, legal);
    word_t val2 = eval(op + 1, q, legal);

    switch (tokens[op].type) {
      case '+': return val1 + val2;
      case '-': return val1 - val2;
      case '*': return val1 * val2;
      case '/': 
        if(val2 == 0){
          *legal = false;
          printf("Error: division by zero\n");
          return 0;
        }else {
          return (sword_t)val1 / (sword_t)val2;
        }
      default: printf( "invalid op type");
    }
  }
  return 0;
}


word_t expr(char *e, bool *success) {
  if (!make_token(e)) {
    *success = false;
    return 0;
  }
  *success = true;

  /* TODO: Insert codes to evaluate the expression. */  
  word_t ans = eval(0, nr_token - 1, success);
  
  if(success == false){
    printf("Error: invalid expression\n");
    return 0;
  }else{
    return ans;
  }
}
