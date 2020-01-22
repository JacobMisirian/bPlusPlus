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
          add_token (lexer, ASSIGN_TOK, &cur, 1);
        } else {
          add_token (lexer, OP_TOK, &cur, 1);
        }
        break;
      case '=':
        if (next == '=') {
          tmp [0] = cur;
          tmp [1] = '=';
          read_char (lexer);
          add_token (lexer, COMP_TOK, tmp, 2);
        } else {
          add_token (lexer, ASSIGN_TOK, &cur, 1);
        }
        break;
      case '!':
        if (next == '=') {
          tmp [0] = cur;
          tmp [1] = '=';
          read_char (lexer);
          add_token (lexer, COMP_TOK, tmp, 2);
        } else {
          add_token (lexer, OP_TOK, &cur, 1);
        }
        break;
      case '<':
      case '>':
        if (next == '=') {
          tmp [0] = cur;
          tmp [1] = '=';
          read_char (lexer);
          add_token (lexer, COMP_TOK, tmp, 2);
        } else if (cur == next) {
          tmp [0] = cur;
          tmp [1] = next;
          read_char (lexer);
          add_token (lexer, OP_TOK, tmp, 2);
        } else {
          add_token (lexer, COMP_TOK, &cur, 1);
        }
        break;
      case '(':
        add_token (lexer, OPAREN_TOK, 0, 0);
        break;
      case ')':
        add_token (lexer, CPAREN_TOK, 0, 0);
        break;
      case '{':
        add_token (lexer, OBRACE_TOK, 0, 0);
        break;
      case '}':
        add_token (lexer, CBRACE_TOK, 0, 0);
        break;
      case '[':
        add_token (lexer, OSQUARE_TOK, 0, 0);
        break;
      case ']':
        add_token (lexer, CSQUARE_TOK, 0, 0);
        break;
      case ',':
        add_token (lexer, COMMA_TOK, 0, 0);
        break;
      case '.':
        add_token (lexer, DOT_TOK, 0, 0);
        break;
      case ':':
        add_token (lexer, COLON_TOK, 0, 0);
        break;
      case ';':
        add_token (lexer, SEMICOLON_TOK, 0, 0);
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

  add_token (lexer, ID_TOK, val, len);
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

  add_token (lexer, INT_TOK, val, len);
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

  add_token (lexer, STRING_TOK, val, len);
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
