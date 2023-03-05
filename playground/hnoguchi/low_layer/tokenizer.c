/*
 * 「低レイヤを知りたい人のためのCコンパイラ作成入門」
 * ステップ３；トークナイザの導入
 * https://www.sigbus.info/compilerbook#%E3%82%B9%E3%83%86%E3%83%83%E3%83%973%E3%83%88%E3%83%BC%E3%82%AF%E3%83%8A%E3%82%A4%E3%82%B6%E3%82%92%E5%B0%8E%E5%85%A5
 * 「単語（トークン）」とは、空白文字で区切られた各文字列のこと。
 * 「トークナイズする」とは、文字列と空白文字が交互に連なった文字列を「単語（トークン）」毎に分割すること。
 *
 * 文字列を「トークナイズする」メリットの１つは、
 * 分割した「トークン」を分類し、型を付けることができるようになる。
 * これによって、「トークン」の解釈を行う処理を軽くすることができる。
 *
 *
 * 加減算の数式を「トークナイズする」処理の実装例
 */
#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// token type
typedef enum {
	TK_RESERVED,	// sign
	TK_NUM,			// number
	TK_EOF			// \0
}	TokenKind;

typedef struct Token Token;

// Token type
struct Token {
	TokenKind	kind;	// token type
	Token		*next;
	int			val;	// (Kind == TK_NUM)
	char		*str;	// (Kind == TK_RESERVED)
};

// 現在着目しているトークン
Token	*token;

// エラーを報告する関数
// printfと同じ引数をとる
void	error(char *fmt, ...)
{
	va_list	ap;

	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
	exit(1);
}

// 次のトークンが期待している記号の時、トークンを１つ読み進め、真を返す。
// それ以外の場合、偽を返す。
bool	consume(char op)
{
	if (token->kind != TK_RESERVED || token->str[0] != op)
	{
		return (false);
	}
	token = token->next;
	return (true);
}

// 次のトークンが期待している記号の時、トークンを１つ読み進める。
// それ以外の場合、エラーを返す。
void	expect(char op)
{
	if (token->kind != TK_RESERVED || token->str[0] != op)
	{
		error("Not [%c]", op);
	}
	token = token->next;
}

// 次のトークンが数値の場合、トークンを１つ読み進めてその数値を返す。
// 数値でなければ、エラーを返す。
int	expect_number()
{
	int	val;

	if (token->kind != TK_NUM)
	{
		error("Not num...");
	}
	val = token->val;
	token = token->next;
	return (val);
}

bool	at_eof()
{
	return (token->kind == TK_EOF);
}

// Tokenize function
// 新しいトークンを作成し、curに繋げる
Token	*new_token(TokenKind kind, Token *cur, char *str)
{
	Token	*tok;

	tok = calloc(1, sizeof(Token));
	tok->kind = kind;
	tok->str = str;
	cur->next = tok;
	return (tok);
}

// 入力文字列pをトークナイズし、それを返す
Token	*tokenize(char *p)
{
	Token	head;
	Token	*cur;

	head.next = NULL;
	cur = &head;

	while (*p)
	{
		// skip space
		if (isspace(*p))
		{
			p++;
			continue ;
		}
		// create token. Type Reserved
		if (*p == '+' || *p == '-')
		{
			cur = new_token(TK_RESERVED, cur, p);
			p++;
			continue;
		}
		// create token. Type Num
		if (isdigit(*p))
		{
			cur = new_token(TK_NUM, cur, p);
			cur->val = strtol(p, &p, 10);
			continue ;
		}
		error("Do'nt tokenize....");
	}
	new_token(TK_EOF, cur, p);
	return (head.next);
}

int	main (int argc, char **argv)
{
	if (argc != 2)
	{
		error("Not arguments...");
		return (1);
	}
	token = tokenize(argv[1]);
	// Check first token is num
	printf("	mov rax, %d\n", expect_number());
	while (!at_eof())
	{
		if (consume('+'))
		{
			printf("	add rax, %d\n", expect_number());
			continue ;
		}
		expect('-');
		printf("	sub rax, %d\n", expect_number());
	}
	printf("	ret\n");
	return (0);
}
