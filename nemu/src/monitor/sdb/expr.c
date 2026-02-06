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
#include "memory/vaddr.h"

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>


#define EXPRLEN 4096
enum {
  TK_NOTYPE = 256, TK_EQ,

  /* TODO: Add more token types */
  TK_NUM   ,   // 十进制整数
  TK_NEQ   ,   // 不等于
  TK_AND   ,   // and
  TK_OR    ,   // or
  TK_HEX   ,   // 十六进制整数
  TK_REG   ,   // 寄存器
  TK_DEREF    ,   // 指针
  TK_NEG   ,   // 负数
};


static struct rule {
  const char *regex;
  int token_type;
} rules[] = {

  /* TODO: Add more rules.
   * Pay attention to the precedence level of different rules.
   */

  {" +",               TK_NOTYPE },    // spaces

  {"0[xX][0-9a-fA-F]+", TK_HEX   },    // hex literal (fixed ++)
  {"[0-9]+",           TK_NUM   },     // decimal number
  {"\\$\\w+",          TK_REG   },     // register, e.g., $eax

  {"==",               TK_EQ    },     // equal
  {"!=",               TK_NEQ   },     // not equal
  {"&&",               TK_AND   },     // logical and
  {"\\|\\|",           TK_OR    },     // optional: logical or

  {"\\+",              '+'      },     // plus
  {"\\-",              '-'      },     // minus
  {"\\*",              '*'      },     // multiplication / TK_TK_DEREF
  {"/",                '/'      },     // division
  {"&",                '&'      },     // bitwise and / address-of

  {"\\(",              '('      },
  {"\\)",              ')'      },

};

#define NR_REGEX ARRLEN(rules)

static regex_t re[NR_REGEX] = {};

#define TOKEN_TYPES(type,types) token_types(type,types,ARRLEN(types))

static int Literals[] = {TK_NUM, TK_HEX, TK_REG};
static int Literals_par[] = {'(', ')', TK_NUM, TK_HEX, TK_REG};
static int Operators[] = {'+', '-', '*', '/', '&', '|'};


static bool token_types(int type, int types[], int len) {
  for (int i = 0; i < len; i++) {
    if (type == *types) {
      return true;
    }
    types++;
  }
  return false;
}

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
          case TK_HEX    :
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
        
        //识别单目运算符
        if ((i == 0 || TOKEN_TYPES(tokens[i - 1].type,Literals_par)==0) ) {
          switch (tokens[i].type)
          {
          case  '*' : 
            tokens[i].type = TK_DEREF;
            break;
          case '-' :
            tokens[i].type = TK_NEG;
            break;
          case '+' :
            tokens[i].type = '+';
            break;
          default:
            break;
          }
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


int get_precedence(int type) {
  switch (type) {
    case TK_OR: return 1;
    case TK_AND: return 2;
    case TK_EQ: case TK_NEQ: return 3;
    case '+': case '-': return 4;
    case '*': case '/': return 5;
    default: return 0; // 一元 or invalid
  }
}

int find_main_op(int p, int q) 
{
  int ret = -1, par = 0;
  int op_pre = 0;
  for (int i = p; i <= q; i++) {
    //跳过所有数字
    if (TOKEN_TYPES(tokens[i].type,Literals)) {
      continue;
    }
    //识别括号并计算是否匹配
    if (tokens[i].type == '(') {
      par++;
    } else if (tokens[i].type == ')') {
      if (par == 0) {
        return -1;
      }
      par--;
    //如果在一对括号之内，直接忽略
    } else if (par > 0) {
      continue;
    //否则判断运算优先级
    } else {
      int tmp_type = 0;
      tmp_type = get_precedence(tokens[i].type);
      //如果优先级更高，则更新返回值ret为优先级更高的位置
      if (tmp_type > op_pre || (tmp_type == op_pre && !TOKEN_TYPES(tokens[i].type, Operators))) {
        op_pre = tmp_type;
        ret = i;
      }
    }
  }
  if (par != 0) {
    printf("Error: unmatched ()\n");
    return -1;
  }
  return ret;
}


static word_t eval_operation(int p, bool *legal) { 
  switch (tokens[p].type)
  {
  case TK_NUM:
    return strtol(tokens[p].str, NULL, 10);
    break;
  case TK_HEX:
    return strtol(tokens[p].str, NULL, 16);
    break;
  case TK_REG:
    return isa_reg_str2val(tokens[p].str, legal);
    break;
  
  default:
    printf("Error: unsupported operator %s\n", tokens[p].str);
    return 0;
    break;
  }
  return 0;
}

static word_t calc1op(int op, word_t val, bool *success) {
  switch (op){
  case TK_NEG: return -val;
  case TK_DEREF: return vaddr_read(val, 4);
  default: *success = false;
  }

  return 0;
}

// binary operator
static word_t calc2op(word_t val1, int op, word_t val2, bool *success) {
  switch(op) {
  case '+': return val1 + val2;
  case '-': return val1 - val2;
  case '*': return val1 * val2;
  case '/': if (val2 == 0) {
              printf("Error: division by zero"); 
              *success = false;
              return 0;
            } 
            return (sword_t)val1 / (sword_t)val2; //
  case TK_AND: return val1 && val2;
  case TK_OR: return val1 || val2;
  case TK_EQ: return val1 == val2;
  case TK_NEQ: return val1 != val2;
  default: *success = false; return 0;
  }
}

static word_t eval(int p,int q, bool *legal) {
  if (p > q) {
    /* Bad expression */
    *legal = false;
    printf("Error: bad expression\n");
    return 0;
  }
  else if (p == q) {
    /* Single token.
     * For now this token should be a number.
     * Return the value of the number.
     */
    /*
    *legal = true;
    if(tokens[p].type != TK_NUM){
      *legal = false;
      printf("Error: the first token is not a number\n");
      return 0;
    }
    word_t n = strtol(tokens[p].str, NULL, 10);
    return n;
    */
    return eval_operation(p, legal);
  }

  //如果最外侧是一对匹配的括号的话
  else if (check_parentheses(p, q) == true) {
    /* The expression is surrounded by a matched pair of parentheses.
     * If that is the case, just throw away the parentheses.
     */

    return eval(p + 1, q - 1, legal);
  }
  else {
    int op = find_main_op(p, q);
    if(op < 0){
      printf("Error: no operator found\n");
      return 0;
    }
    bool *legal1 = 0;
    bool *legal2 = 0;
    word_t val1 = eval(p, op - 1, legal1);
    word_t val2 = eval(op + 1, q, legal2);

    if(legal1){
      word_t val = calc2op(val1, tokens[op].type, val2, legal2);
      return val;
    }else {
      word_t val = calc1op(tokens[op].type, val1, legal);
      return val;
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
