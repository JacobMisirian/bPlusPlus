#include <lexer/lexer.h>

struct lexer * init_lexer (char * source) {
  struct lexer * lexer;

  lexer = calloc (1, sizeof(struct lexer));

  lexer->source = source;
  lexer->pos    = 0;
  lexer->len    = strlen(source);
  lexer->tokens = init_vector ();
}

void free_lexer (struct lexer * lexer) {
  for (int i = 0; i < lexer->tokens->count; i++) {
    free_token (vector_get (lexer->tokens, i));
  }
  free_vector (lexer->tokens);

  free        (lexer);
}

static void scan_id     (struct lexer * lexer);
static void scan_int    (struct lexer * lexer);
static void scan_string (struct lexer * lexer);

static void add_token      (struct lexer * lexer, token_type_t type, char * val, int len);
static void eat_whitespace (struct lexer * lexer);

static int peek_char (struct lexer * lexer);
static int next_char (struct lexer * lexer);
static int read_char (struct lexer * lexer);

void lexer_scan (struct lexer * lexer) {
  char cur, next;
  char tmp[3];

  while (peek_char (lexer) != -1) {
    eat_whitespace (lexer);

    cur  = (char) read_char (lexer);
    next = (char) peek_char (lexer);

    if (isalpha (cur) || cur == '_') {
      scan_id (lexer);
      continue;
    } else if (isdigit (cur)) {
      scan_int (lexer);
      continue;
    }

    switch (cur) {
      case '"':
        scan_string (lexer);
        break;
      case '+':
      case '-':
      case '*':
      case '/':
        if (next == '=') {
          read_char (lexer);
          add_token (lexer, TOK_ASSIGN, &cur, 1);
        } else {
          add_token (lexer, TOK_OP, &cur, 1);
        }
        break;
      case '=':
        if (next == '=') {
          tmp [0] = cur;
          tmp [1] = '=';
          read_char (lexer);
          add_token (lexer, TOK_COMP, tmp, 2);
        } else {
          add_token (lexer, TOK_ASSIGN, &cur, 1);
        }
        break;
      case '!':
        if (next == '=') {
          tmp [0] = cur;
          tmp [1] = '=';
          read_char (lexer);
          add_token (lexer, TOK_COMP, tmp, 2);
        } else {
          add_token (lexer, TOK_OP, &cur, 1);
        }
        break;
      case '<':
      case '>':
        if (next == '=') {
          tmp [0] = cur;
          tmp [1] = '=';
          read_char (lexer);
          add_token (lexer, TOK_COMP, tmp, 2);
        } else if (cur == next) {
          tmp [0] = cur;
          tmp [1] = next;
          read_char (lexer);
          add_token (lexer, TOK_OP, tmp, 2);
        } else {
          add_token (lexer, TOK_COMP, &cur, 1);
        }
        break;
      case '(':
        add_token (lexer, TOK_OPAREN, 0, 0);
        break;
      case ')':
        add_token (lexer, TOK_CPAREN, 0, 0);
        break;
      case '{':
        add_token (lexer, TOK_OBRACE, 0, 0);
        break;
      case '}':
        add_token (lexer, TOK_CBRACE, 0, 0);
        break;
      case '[':
        add_token (lexer, TOK_OSQUARE, 0, 0);
        break;
      case ']':
        add_token (lexer, TOK_CSQUARE, 0, 0);
        break;
      case ',':
        add_token (lexer, TOK_COMMA, 0, 0);
        break;
      case '.':
        add_token (lexer, TOK_DOT, 0, 0);
        break;
      case ':':
        add_token (lexer, TOK_COLON, 0, 0);
        break;
      case ';':
        add_token (lexer, TOK_SEMICOLON, 0, 0);
        break;
      default:
        printf ("Unknown char %d '%c'\n", cur, cur);
        break;
    }
  }
}

static void scan_id (struct lexer * lexer) {
  char * val;
  int    len;

  lexer->pos --; // Move back one since we read over the first char.

  val = lexer->source + lexer->pos;
  len = 0;

  while (peek_char (lexer) != -1) {
    if (isalnum ((char) peek_char(lexer)) == 0 || ((char) peek_char (lexer)) == '_') {
      break;
    }

    read_char (lexer);
    len ++;
  }

  add_token (lexer, TOK_IDENTIFIER, val, len);
}

static void scan_int (struct lexer * lexer) {
  char * val;
  int    len;

  lexer->pos --;

  val = lexer->source + lexer->pos;
  len = 0;

  while (peek_char (lexer) != -1) {
    if (isdigit ((char) peek_char(lexer)) == 0) {
      break;
    }

    read_char (lexer);
    len ++;
  }

  add_token (lexer, TOK_INTEGER, val, len);
}

static void scan_string (struct lexer * lexer) {
  char * val;
  int    len;

  val = lexer->source + lexer->pos;
  len = 0;

  // Opening " already read by lexer_scan
  while (peek_char (lexer) != -1) {
    if ((char) peek_char (lexer) == '"') {
      read_char (lexer); // burn closing "
      break;
    }

    read_char (lexer);
    len ++;
  }

  add_token (lexer, TOK_STRING, val, len);
}

static void add_token (struct lexer * lexer, token_type_t type, char * val, int size) {
  vector_push (lexer->tokens, init_token (type, val, size));
}

static void eat_whitespace (struct lexer * lexer) {
  while (peek_char (lexer) != -1) {
    if (isspace ((char) peek_char (lexer)) == 0) {
      break;
    }

    read_char (lexer);
  }
}

static int peek_char (struct lexer * lexer) {
  return lexer->pos < lexer->len ? lexer->source [lexer->pos] : -1;
}

static int next_char (struct lexer *  lexer) {
  return (lexer->pos + 1) < lexer->len ? lexer->source [(lexer->pos + 1)] : -1;
}

static int read_char (struct lexer * lexer) {
  return lexer->pos < lexer->len ? lexer->source [lexer->pos ++] : -1;
}
