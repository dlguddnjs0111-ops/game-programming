癤?*
 *  100???섏뼱??: ?꾩씠??移대뱶 諛고?
 *  - ?먮낯 "100???섏뼱?? 寃뚯엫 ?낃렇?덉씠??踰꾩쟾
 *  - 二쇱꽍??[?꿓] ?쒖떆??PPT??"?낃렇?덉씠??N" 踰덊샇? 媛숈뒿?덈떎.
 */
#define _CRT_SECURE_NO_WARNINGS          /* [??] Visual Studio scanf/fopen ?ㅻ쪟 諛⑹? */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

/* ================= [??] 留ㅼ쭅 ?섎쾭 -> ?곸닔 ================= */
#define MAX_SCORE    100     /* ???レ옄瑜??섍린硫??밸━            */
#define MIN_NUM      1       /* ?レ옄 移대뱶 理쒖냼媛?                */
#define MAX_NUM      10      /* ?レ옄 移대뱶 理쒕?媛?                */
#define ITEM_SLOT    3       /* [??7] ?꾩씠???щ’ ??           */
#define START_ITEM   2       /* [??7] ?쒖옉 ?꾩씠????           */
#define BONUS_TURN   4       /* [??2] 蹂대꼫???꾩씠??二쇨린(??    */
#define MINUS_VALUE  10      /* [??9] ?⑷퀎 媛먯냼??              */
#define TIME_LIMIT   20      /* [??5] ?쒗븳 ?쒓컙(珥?             */
#define LOG_LINES    5       /* [??1] 濡쒓렇 以???               */
#define HISTORY_MAX  10      /* 理쒓렐 ???レ옄 ?쒖떆 媛쒖닔           */
#define GAUGE_LEN    40      /* [??7] 寃뚯씠吏 湲몄씠               */
#define SAVE_FILE    "save.dat"     /* [??4] */
#define RECORD_FILE  "record.txt"   /* [??6] */
#define SAVE_MAGIC   20261105       /* [??5] ????뚯씪 ?뺤씤??踰덊샇 */

#define COM   0
#define USER  1

/* [??6] ??肄붾뱶 (諛⑺뼢?ㅻ뒗 1000???뷀빐???쇰컲 臾몄옄? 援щ텇) */
#define KEY_UP     (1000 + 72)
#define KEY_DOWN   (1000 + 80)
#define KEY_LEFT   (1000 + 75)
#define KEY_RIGHT  (1000 + 77)
#define KEY_ENTER  13
#define KEY_ESC    27

/* [??1] ?됱긽 */
enum { C_GRAY = 7, C_DARK = 8, C_BLUE = 9, C_GREEN = 10, C_CYAN = 11,
       C_RED = 12, C_MAGENTA = 13, C_YELLOW = 14, C_WHITE = 15 };

/* [??7] ?꾩씠??醫낅쪟 */
enum { ITEM_NONE = 0, ITEM_DOUBLE, ITEM_MINUS, ITEM_SKIP, ITEM_SEAL, ITEM_KIND };
const char *ITEM_NAME[ITEM_KIND] = { "(鍮덉뭏)", "?붾툝 x2", "?⑷퀎 -10", "???ㅽ궢", "遊됱씤" };
const char *ITEM_DESC[ITEM_KIND] = {
    "",
    "[?붾툝 x2] ?대쾲 ?댁뿉 ?대뒗 ?レ옄媛 2諛곌? ?⑸땲??",
    "[?⑷퀎 -10] ?꾩옱 ?⑷퀎瑜?10 以꾩엯?덈떎. (?곷????밸━ ?吏??",
    "[???ㅽ궢] ?곷????ㅼ쓬 ?댁쓣 嫄대꼫?곌퀬 ?닿? ??踰????⑸땲??",
    "[遊됱씤] ?곷???媛?????レ옄 移대뱶瑜??ㅼ쓬 1???숈븞 紐??곌쾶 ?⑸땲??"
};

/* [??3] ?쒖씠??*/
enum { EASY = 0, NORMAL, HARD };
const char *DIFF_NAME[3] = { "?ъ?", "蹂댄넻", "?대젮?" };
const char *WHO_NAME[2]  = { "而댄벂??, "?ъ슜?? };

typedef struct {
    int used[MAX_NUM + 1];      /* 1?대㈃ ?대? ???レ옄          */
    int sealed[MAX_NUM + 1];    /* [??1] 1?대㈃ 遊됱씤???レ옄     */
    int items[ITEM_SLOT];       /* [??7] 蹂댁쑀 ?꾩씠??          */
    int history[HISTORY_MAX];   /* 理쒓렐 ???レ옄                 */
    int history_count;
    int item_used_total;        /* [??7] ?듦퀎??               */
} Player;

typedef struct {
    int magic;                  /* [??5] ????뚯씪 ?뺤씤??     */
    Player p[2];                /* p[COM], p[USER]              */
    int sum;
    int turn;                   /* 吏湲?李⑤? (COM / USER)       */
    int round;                  /* 吏꾪뻾??????                */
    int difficulty;
    int double_on;              /* [??8] ?붾툝 ?곸슜 以?         */
    int skip_next;              /* [??0] ???ㅽ궢 ?덉빟          */
    char log[LOG_LINES][80];    /* [??1] 寃뚯엫 濡쒓렇             */
} Game;

typedef struct { int win, lose, draw; } Record;

int sound_on = 1;               /* [??2] ?뚮━ ON/OFF */

/* ---------------- ?⑥닔 ?좎뼵 ---------------- */
/* 肄섏넄/?붾㈃ */
void gotoxy(int x, int y);
void set_color(int color);
void hide_cursor(void);
void setup_console(void);
void clear_line(int y);
void print_at(int x, int y, int color, const char *fmt, ...);
void show_msg(int color, const char *fmt, ...);
int  get_key(void);
void press_any_key(int y);
int  menu_select(int x, int y, const char *items[], int n, int start);
/* ?뚮━ */
void snd_move(void); void snd_select(void); void snd_error(void);
void snd_item(void); void snd_card(void);  void snd_win(void); void snd_lose(void);
/* ?붾㈃ */
void splash_screen(void);
int  main_menu(void);
void rules_screen(void);
void record_screen(void);
void ending_screen(Game *g, int winner);
/* 寃뚯엫 */
void new_game(Game *g, int difficulty);
int  select_difficulty(void);
int  coin_toss(void);
int  play_game(Game *g);
void run_game(Game *g);
int  user_turn(Game *g);
int  computer_turn(Game *g);
void use_item(Game *g, int who, int slot);
void give_bonus(Game *g);
void add_log(Game *g, const char *fmt, ...);
void add_history(Player *p, int card);
/* 洹몃━湲?*/
void draw_game(Game *g);
void draw_gauge(Game *g);
void draw_status(Game *g);
void draw_log(Game *g);
void draw_box(int x, int y, int w, const char *text, int color, int selected);
void draw_hand(Game *g, int row, int col, int item_used);
/* ?먮떒 */
int  playable(Player *p, int n);
int  max_playable(Player *p);
int  min_playable(Player *p);
int  random_playable(Player *p);
int  all_used(Player *p);
int  find_item(Player *p, int type);
int  item_count(Player *p);
int  next_max(Player *p);
int  winning_card(Game *g, Player *me);
int  safe_card(Game *g);
int  ai_easy(Game *g);
int  ai_normal(Game *g);
int  ai_hard(Game *g);
/* ?뚯씪 */
int  save_game(Game *g);
int  load_game(Game *g);
void load_record(Record *r);
void save_record(Record *r);

/* ============================================================
 *  main
 * ============================================================ */
int main(void)
{
    Game g;
    int sel;

    srand((unsigned)time(NULL));
    setup_console();                 /* [??]  */
    hide_cursor();                   /* [??0] */
    splash_screen();                 /* [??2] */

    while (1)                        /* [??8] 寃뚯엫???앸굹??硫붾돱濡??뚯븘? ?ㅼ떆 ?섍린 */
    {
        sel = main_menu();           /* [??3] */
        if (sel == 0) {                                  /* ??寃뚯엫 */
            int diff = select_difficulty();
            if (diff < 0) continue;
            new_game(&g, diff);
            run_game(&g);
        }
        else if (sel == 1) {                             /* ?댁뼱?섍린 */
            if (load_game(&g)) run_game(&g);
            else {
                show_msg(C_RED, "??λ맂 寃뚯엫???놁뒿?덈떎.");
                snd_error();
                Sleep(1000);
            }
        }
        else if (sel == 2) rules_screen();               /* 寃뚯엫 諛⑸쾿 */
        else if (sel == 3) record_screen();              /* ?꾩쟻 */
        else if (sel == 4) sound_on = !sound_on;         /* ?뚮━ */
        else {                                           /* 醫낅즺 */
            system("cls");
            print_at(25, 12, C_CYAN, "?뚮젅?댄빐 二쇱뀛??媛먯궗?⑸땲??");
            Sleep(1000);
            set_color(C_GRAY);
            return 0;
        }
    }
}

/* ============================================================
 *  肄섏넄 湲곕낯 湲곕뒫
 * ============================================================ */
void gotoxy(int x, int y)
{
    COORD pos = { (SHORT)(x - 1), (SHORT)(y - 1) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/* [??1] 湲????諛붽씀湲?*/
void set_color(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)color);
}

/* [??0] 源쒕묀?대뒗 而ㅼ꽌 ?④린湲?*/
void hide_cursor(void)
{
    CONSOLE_CURSOR_INFO ci;
    ci.dwSize = 1;
    ci.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);
}

/* [??] 李??쒕ぉ, 李??ш린 ?ㅼ젙 */
void setup_console(void)
{
    SetConsoleTitleA("100???섏뼱??: ?꾩씠??移대뱶 諛고?");
    system("mode con cols=80 lines=32");
}

/* [??] ??以?吏?곌린 (?붿긽 ?쒓굅) */
void clear_line(int y)
{
    gotoxy(1, y);
    printf("%79s", "");
}

void print_at(int x, int y, int color, const char *fmt, ...)
{
    va_list ap;
    gotoxy(x, y);
    set_color(color);
    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);
    set_color(C_GRAY);
}

/* 留??꾨옒 硫붿떆吏 以?*/
void show_msg(int color, const char *fmt, ...)
{
    va_list ap;
    clear_line(29);
    gotoxy(3, 29);
    set_color(color);
    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);
    set_color(C_GRAY);
}

/* [??6] ???낅젰 (諛⑺뼢?ㅻ뒗 1000+肄붾뱶濡??뚮젮以? */
int get_key(void)
{
    int c = _getch();                       /* [??] getch -> _getch */
    if (c == 0 || c == 224)
        return 1000 + _getch();
    return c;
}

void press_any_key(int y)
{
    print_at(3, y, C_DARK, "?꾨Т ?ㅻ굹 ?꾨Ⅴ?몄슂...");
    get_key();
}

/* [??3] 諛⑺뼢??硫붾돱 (怨듭슜 ?⑥닔) - ?좏깮??踰덊샇 諛섑솚, ESC??-1 */
int menu_select(int x, int y, const char *items[], int n, int start)
{
    int sel = start, i, key;
    while (1)
    {
        for (i = 0; i < n; i++) {
            if (i == sel) print_at(x, y + i * 2, C_YELLOW, "??%-30s", items[i]);
            else          print_at(x, y + i * 2, C_GRAY,   "   %-30s", items[i]);
        }
        key = get_key();
        if (key == KEY_UP)        { sel = (sel + n - 1) % n; snd_move(); }
        else if (key == KEY_DOWN) { sel = (sel + 1) % n;     snd_move(); }
        else if (key == KEY_ENTER){ snd_select(); return sel; }
        else if (key == KEY_ESC)  return -1;
    }
}

/* ============================================================
 *  [??2] ?④낵??
 * ============================================================ */
void snd_move(void)   { if (sound_on) Beep(600, 25); }
void snd_select(void) { if (sound_on) Beep(900, 60); }
void snd_error(void)  { if (sound_on) Beep(200, 150); }
void snd_card(void)   { if (sound_on) Beep(750, 50); }
void snd_item(void)   { if (sound_on) { Beep(1200, 70); Beep(1600, 90); } }
void snd_win(void)
{
    int note[] = { 523, 659, 784, 1046 }, i;     /* ??誘?????*/
    if (!sound_on) return;
    for (i = 0; i < 4; i++) Beep(note[i], 150);
    Beep(1046, 400);
}
void snd_lose(void)
{
    int note[] = { 784, 659, 523, 392 }, i;      /* ??誘?????*/
    if (!sound_on) return;
    for (i = 0; i < 4; i++) Beep(note[i], 200);
}

/* ============================================================
 *  ?붾㈃??
 * ============================================================ */
/* [??2] 1珥?濡쒓퀬 ?붾㈃ */
void splash_screen(void)
{
    int i;
    system("cls");
    print_at(20, 6,  C_YELLOW, "   ##     ####     ####  ");
    print_at(20, 7,  C_YELLOW, "  ###    ##  ##   ##  ## ");
    print_at(20, 8,  C_YELLOW, "   ##    ##  ##   ##  ## ");
    print_at(20, 9,  C_YELLOW, "   ##    ##  ##   ##  ## ");
    print_at(20, 10, C_YELLOW, "  ####    ####     ####  ");
    print_at(26, 12, C_WHITE,  "????????!");
    print_at(23, 14, C_CYAN,   "- ITEM CARD BATTLE -");
    print_at(20, 18, C_DARK,   "[                        ]");
    for (i = 0; i < 24; i++) {                  /* ??1珥?濡쒕뵫 諛?*/
        print_at(21 + i, 18, C_GREEN, "#");
        Sleep(40);
    }
    if (sound_on) { Beep(523, 80); Beep(784, 120); }
}

/* [??3] 硫붿씤 硫붾돱 */
int main_menu(void)
{
    static int last = 0;
    const char *items[6];
    items[0] = "??寃뚯엫";
    items[1] = "?댁뼱?섍린";
    items[2] = "寃뚯엫 諛⑸쾿";
    items[3] = "?꾩쟻 蹂닿린";
    items[4] = sound_on ? "?뚮━ : ON" : "?뚮━ : OFF";
    items[5] = "醫낅즺";

    system("cls");
    print_at(22, 3, C_YELLOW, "??100???섏뼱??: ?꾩씠??移대뱶 諛고? ??);
    print_at(22, 4, C_DARK,   "-------------------------------------");
    print_at(22, 26, C_DARK,  "?묅넃 : ?대룞     Enter : ?좏깮");
    last = menu_select(30, 8, items, 6, last);
    if (last < 0) last = 5;
    return last;
}

/* [??4] 寃뚯엫 諛⑸쾿 (2?섏씠吏) */
void rules_screen(void)
{
    int i;
    system("cls");
    print_at(3, 2, C_YELLOW, "[ 寃뚯엫 諛⑸쾿 1/2 : 湲곕낯 洹쒖튃 ]");
    print_at(3, 4,  C_WHITE, "1. 而댄벂?곗? ?ъ슜?먭? 踰덇컝??1~10 ?レ옄 移대뱶瑜????μ뵫 ?낅땲??");
    print_at(3, 5,  C_WHITE, "2. ???レ옄???⑷퀎???뷀빐吏怨? 媛숈? ?レ옄???ㅼ떆 ?????놁뒿?덈떎.");
    print_at(3, 6,  C_WHITE, "3. ?⑷퀎瑜?泥섏쓬?쇰줈 %d蹂대떎 ?ш쾶 留뚮뱺 ?щ엺???밸━?⑸땲??", MAX_SCORE);
    print_at(3, 7,  C_WHITE, "4. 10?μ쓣 紐⑤몢 ?곕㈃ ?レ옄 移대뱶媛 ?ㅼ떆 梨꾩썙吏묐땲??");
    print_at(3, 8,  C_WHITE, "5. ?좉났? ?숈쟾 ?섏?湲곕줈 ?뺥빀?덈떎.");
    print_at(3, 9,  C_WHITE, "6. ??李⑤??먮뒗 %d珥??덉뿉 怨⑤씪???⑸땲?? (?쒓컙 珥덇낵 ??臾댁옉??", TIME_LIMIT);
    print_at(3, 12, C_CYAN,  "[ 議곗옉踰?]");
    print_at(3, 13, C_GRAY,  "?먥넂 : 移대뱶 ?대룞     ?묅넃 : ?レ옄 以?/ ?꾩씠??以??꾪솚");
    print_at(3, 14, C_GRAY,  "Enter : ?좏깮       S : ???      ESC : 硫붾돱濡?);
    press_any_key(20);

    system("cls");
    print_at(3, 2, C_YELLOW, "[ 寃뚯엫 諛⑸쾿 2/2 : ?꾩씠??移대뱶 ]");
    print_at(3, 4, C_WHITE,  "- ?쒖옉?????꾩씠??%d?? %d?대쭏??蹂대꼫???꾩씠??1??(理쒕? %d??",
             START_ITEM, BONUS_TURN, ITEM_SLOT);
    print_at(3, 5, C_WHITE,  "- ?꾩씠?쒖? ???댁뿉 1踰? ?レ옄 移대뱶瑜??닿린 ?꾩뿉 ?ъ슜?⑸땲??");
    for (i = 1; i < ITEM_KIND; i++)
        print_at(3, 7 + i * 2, C_GREEN, "%s", ITEM_DESC[i]);
    press_any_key(20);
}

/* [??6] ?꾩쟻 蹂닿린 */
void record_screen(void)
{
    Record r;
    int total;
    load_record(&r);
    total = r.win + r.lose + r.draw;
    system("cls");
    print_at(30, 5, C_YELLOW, "[ ?섏쓽 ?꾩쟻 ]");
    print_at(30, 8,  C_BLUE,  "?밸━ : %3d", r.win);
    print_at(30, 10, C_RED,   "?⑤같 : %3d", r.lose);
    print_at(30, 12, C_GRAY,  "臾댁듅遺 : %3d", r.draw);
    print_at(30, 14, C_GREEN, "?밸쪧 : %5.1f%%", total ? r.win * 100.0 / total : 0.0);
    press_any_key(20);
}

/* [??7] ?붾뵫 ?붾㈃ (?밸━ / ?⑤같 + ?듦퀎) */
void ending_screen(Game *g, int winner)
{
    Record r;
    int color = (winner == USER) ? C_YELLOW : C_RED;

    load_record(&r);                              /* [??6] ?꾩쟻 ???*/
    if (winner == USER) r.win++;
    else if (winner == COM) r.lose++;
    else r.draw++;
    save_record(&r);
    remove(SAVE_FILE);                            /* ?앸궃 寃뚯엫? ?댁뼱?섍린 遺덇? */

    system("cls");
    if (winner == USER) {
        print_at(18, 3, color, " #   #  ###  #   #     #   #  ###  #   #");
        print_at(18, 4, color, "  # #  #   # #   #     #   #   #   ##  #");
        print_at(18, 5, color, "   #   #   # #   #     # # #   #   # # #");
        print_at(18, 6, color, "   #   #   # #   #     ## ##   #   #  ##");
        print_at(18, 7, color, "   #    ###   ###      #   #  ###  #   #");
        print_at(30, 9, C_WHITE, "?ъ슜?먭? ?닿꼈?듬땲??");
    } else if (winner == COM) {
        print_at(15, 3, color, " #   #  ###  #   #     #      ###   ####  #####");
        print_at(15, 4, color, "  # #  #   # #   #     #     #   # #      #    ");
        print_at(15, 5, color, "   #   #   # #   #     #     #   #  ###   #### ");
        print_at(15, 6, color, "   #   #   # #   #     #     #   #     #  #    ");
        print_at(15, 7, color, "   #    ###   ###      ####   ###  ####   #####");
        print_at(30, 9, C_WHITE, "而댄벂?곌? ?닿꼈?듬땲??..");
    } else {
        print_at(33, 6, C_GRAY, "臾댁듅遺?낅땲??");
    }

    print_at(25, 12, C_CYAN, "========== 寃뚯엫 寃곌낵 ==========");
    print_at(27, 14, C_GRAY, "?쒖씠??         : %s", DIFF_NAME[g->difficulty]);
    print_at(27, 15, C_GRAY, "理쒖쥌 ?⑷퀎       : %d", g->sum);
    print_at(27, 16, C_GRAY, "吏꾪뻾????      : %d", g->round + 1);
    print_at(27, 17, C_GRAY, "?ъ슜???꾩씠??  : ??%d / 而댄벂??%d",
             g->p[USER].item_used_total, g->p[COM].item_used_total);
    print_at(25, 19, C_CYAN, "===============================");
    print_at(27, 21, C_GREEN, "?꾩쟻 ?꾩쟻 : %d??%d??%d臾?, r.win, r.lose, r.draw);

    if (winner == USER) snd_win(); else snd_lose();
    press_any_key(25);
}

/* ============================================================
 *  寃뚯엫 以鍮?
 * ============================================================ */
/* [??3] ?쒖씠???좏깮 */
int select_difficulty(void)
{
    const char *items[3] = { "?ъ?   - ?꾨Т嫄곕굹 ?대뒗 而댄벂??,
                             "蹂댄넻   - ?닿만 ???덉쑝硫??닿린??而댄벂??,
                             "?대젮? - ?섎? ?쎄퀬 ?꾩씠?쒖쓣 ?곕뒗 而댄벂?? };
    system("cls");
    print_at(25, 3, C_YELLOW, "[ ?쒖씠?꾨? ?좏깮?섏꽭??]");
    print_at(25, 20, C_DARK, "ESC : ?ㅻ줈");
    return menu_select(18, 7, items, 3, 1);
}

/* [??4] ?숈쟾 ?섏?湲곕줈 ?좉났 ?뺥븯湲?*/
int coin_toss(void)
{
    const char *items[2] = { "?욌㈃", "?룸㈃" };
    int guess, result, i;

    system("cls");
    print_at(22, 3, C_YELLOW, "[ ?숈쟾 ?섏?湲곕줈 ?좉났???뺥빀?덈떎 ]");
    print_at(22, 5, C_GRAY,   "?욌㈃怨??룸㈃ 以??섎굹瑜?怨좊Ⅴ?몄슂.");
    guess = menu_select(32, 8, items, 2, 0);
    if (guess < 0) guess = 0;

    result = rand() % 2;
    for (i = 0; i < 12; i++) {                      /* ?숈쟾 ?뚯븘媛???곗텧 */
        print_at(33, 14, (i % 2) ? C_YELLOW : C_WHITE, "(  %s  )", items[i % 2]);
        if (sound_on) Beep(1000, 20);
        Sleep(60 + i * 15);
    }
    print_at(33, 14, C_YELLOW, "(  %s  )", items[result]);
    if (guess == result) print_at(27, 17, C_BLUE, "留욏삍?듬땲?? ?ъ슜?먭? 癒쇱? ?⑸땲??");
    else                 print_at(27, 17, C_RED,  "??몄뒿?덈떎! 而댄벂?곌? 癒쇱? ?⑸땲??");
    Sleep(1500);
    return (guess == result) ? USER : COM;
}

void new_game(Game *g, int difficulty)
{
    int i, w;
    memset(g, 0, sizeof(Game));
    g->magic = SAVE_MAGIC;
    g->difficulty = difficulty;
    for (w = 0; w < 2; w++)                         /* [??7] ?쒖옉 ?꾩씠??吏湲?*/
        for (i = 0; i < START_ITEM; i++)
            g->p[w].items[i] = rand() % (ITEM_KIND - 1) + 1;
    g->turn = coin_toss();
    add_log(g, "寃뚯엫 ?쒖옉! ?쒖씠?? %s, ?좉났: %s", DIFF_NAME[difficulty], WHO_NAME[g->turn]);
}

void run_game(Game *g)
{
    int winner = play_game(g);
    if (winner >= 0)
        ending_screen(g, winner);
}

/* ============================================================
 *  寃뚯엫 吏꾪뻾 (?먮낯 game_control ?泥?
 *  諛섑솚: ?뱀옄(COM/USER), 以묎컙???섍?硫?-1
 * ============================================================ */
int play_game(Game *g)
{
    while (1)
    {
        int who = g->turn;
        Player *me = &g->p[who];
        int card, value, i;

        /* [??6] ?レ옄 移대뱶 10?μ쓣 ???곕㈃ ?ㅼ떆 梨꾩슦湲?*/
        if (all_used(me)) {
            memset(me->used, 0, sizeof(me->used));
            add_log(g, "%s???レ옄 移대뱶瑜?紐⑤몢 ?⑥꽌 ?ㅼ떆 梨꾩썱?듬땲??", WHO_NAME[who]);
        }

        draw_game(g);

        /* [??1] ?⑥? 移대뱶媛 ?꾨? 遊됱씤?섎㈃ ???섍린湲?*/
        if (max_playable(me) == 0) {
            add_log(g, "%s: ?????덈뒗 移대뱶媛 ?놁뼱 ?댁쓣 ?섍퉩?덈떎.", WHO_NAME[who]);
            memset(me->sealed, 0, sizeof(me->sealed));
            g->turn = 1 - who;
            draw_log(g);
            Sleep(1000);
            continue;
        }

        if (who == USER) {
            card = user_turn(g);
            if (card == 0) return -1;                /* [??8] 硫붾돱濡??섍?湲?*/
        } else {
            card = computer_turn(g);
        }

        /* 移대뱶 ?곸슜 */
        value = card * (g->double_on ? 2 : 1);       /* [??8] ?붾툝 */
        me->used[card] = 1;
        add_history(me, card);
        memset(me->sealed, 0, sizeof(me->sealed));   /* [??1] 遊됱씤? 1?대쭔 */
        if (g->double_on)
            add_log(g, "%s: %d 移대뱶 x2 ??+%d", WHO_NAME[who], card, value);
        else
            add_log(g, "%s: %d 移대뱶 ??+%d", WHO_NAME[who], card, value);
        g->double_on = 0;
        draw_game(g);
        snd_card();

        /* [??9] ?⑷퀎 移댁슫?몄뾽 ?좊땲硫붿씠??*/
        for (i = 0; i < value; i++) {
            g->sum++;
            draw_gauge(g);
            Sleep(35);
        }

        if (g->sum > MAX_SCORE)
            return who;

        g->round++;
        if (g->round % BONUS_TURN == 0)              /* [??2] 蹂대꼫???꾩씠??*/
            give_bonus(g);

        if (g->skip_next) {                          /* [??0] ???ㅽ궢 */
            g->skip_next = 0;
            add_log(g, "???ㅽ궢 ?④낵! %s媛 ??踰????⑸땲??", WHO_NAME[who]);
        } else {
            g->turn = 1 - who;
        }
        draw_log(g);
        Sleep(600);
    }
}

/* [??][??][??6][??5] ?ъ슜??李⑤?
 *  諛⑺뼢???좏깮?대씪 踰붿쐞 諛??レ옄/臾몄옄 ?낅젰???먯쿇?곸쑝濡?遺덇???*/
int user_turn(Game *g)
{
    Player *me = &g->p[USER];
    int row = 0, col = max_playable(me) - 1;
    int item_used = 0, key, remain, last_sec = -1;
    clock_t start = clock(), pause_start;

    draw_hand(g, row, col, item_used);
    while (1)
    {
        /* [??5] ?쒗븳 ?쒓컙 */
        remain = TIME_LIMIT - (int)((clock() - start) / CLOCKS_PER_SEC);
        if (remain != last_sec) {
            last_sec = remain;
            print_at(3, 28, remain <= 5 ? C_RED : C_GRAY, "?⑥? ?쒓컙 : %2d珥?", remain < 0 ? 0 : remain);
            if (remain <= 5 && remain > 0 && sound_on) Beep(1000, 30);
        }
        if (remain <= 0) {
            int n = random_playable(me);
            add_log(g, "?쒓컙 珥덇낵! ?ъ슜??移대뱶媛 臾댁옉?꾨줈 ?좏깮?먯뒿?덈떎.");
            snd_error();
            return n;
        }
        if (!_kbhit()) { Sleep(30); continue; }

        key = get_key();
        if (key == KEY_LEFT || key == KEY_RIGHT) {
            int len = (row == 0) ? MAX_NUM : ITEM_SLOT;
            col = (key == KEY_LEFT) ? (col + len - 1) % len : (col + 1) % len;
            snd_move();
        }
        else if (key == KEY_UP || key == KEY_DOWN) {
            row = 1 - row;
            if (row == 1 && col >= ITEM_SLOT) col = ITEM_SLOT - 1;
            snd_move();
        }
        else if (key == KEY_ENTER) {
            if (row == 0) {
                if (playable(me, col + 1)) { snd_select(); return col + 1; }
                show_msg(C_RED, me->sealed[col + 1] ? "遊됱씤??移대뱶?낅땲??" : "?대? ?ъ슜???レ옄?낅땲??");
                snd_error();
            } else {
                if (item_used)                        show_msg(C_RED, "?꾩씠?쒖? ???댁뿉 1踰덈쭔 ?????덉뒿?덈떎!");
                else if (me->items[col] == ITEM_NONE) show_msg(C_RED, "鍮??щ’?낅땲??");
                else {
                    use_item(g, USER, col);
                    item_used = 1;
                    row = 0;
                    col = max_playable(me) - 1;
                    draw_game(g);
                    draw_hand(g, row, col, item_used);
                    last_sec = -1;
                    continue;
                }
                snd_error();
            }
        }
        else if (key == 's' || key == 'S') {          /* [??4] ???*/
            if (item_used)        show_msg(C_RED, "?꾩씠?쒖쓣 ???댁뿉????ν븷 ???놁뒿?덈떎.");
            else if (save_game(g)) show_msg(C_GREEN, "寃뚯엫????ν뻽?듬땲?? (硫붾돱 > ?댁뼱?섍린)");
            else                  show_msg(C_RED, "??μ뿉 ?ㅽ뙣?덉뒿?덈떎.");
        }
        else if (key == KEY_ESC) {                    /* [??8] ?쇱떆?뺤? */
            pause_start = clock();
            show_msg(C_YELLOW, "?쇱떆?뺤? - 硫붾돱濡??섍컝源뚯슂? ???????吏꾪뻾? ?щ씪吏묐땲??(Y/N)");
            key = get_key();
            if (key == 'y' || key == 'Y') return 0;
            start += clock() - pause_start;           /* 硫덉텣 ?쒓컙留뚰겮 ??대㉧ 蹂댁젙 */
            clear_line(29);
        }
        draw_hand(g, row, col, item_used);
    }
}

/* [??0] 而댄벂??李⑤? (?앷컖 以??곗텧 + ?쒖씠?꾨퀎 AI) */
int computer_turn(Game *g)
{
    int i;
    show_msg(C_RED, "而댄벂?곌? ?앷컖 以?);
    for (i = 0; i < 3; i++) { printf("."); Sleep(300); }
    clear_line(29);

    if (g->difficulty == EASY)   return ai_easy(g);
    if (g->difficulty == NORMAL) return ai_normal(g);
    return ai_hard(g);
}

/* [??7~31] ?꾩씠???ъ슜 */
void use_item(Game *g, int who, int slot)
{
    Player *me = &g->p[who], *opp = &g->p[1 - who];
    int type = me->items[slot], n;

    me->items[slot] = ITEM_NONE;
    me->item_used_total++;
    snd_item();

    switch (type) {
    case ITEM_DOUBLE:                                 /* [??8] */
        g->double_on = 1;
        add_log(g, "%s: [?붾툝 x2] ?ъ슜! ?대쾲 ?レ옄媛 2諛곌? ?⑸땲??", WHO_NAME[who]);
        break;
    case ITEM_MINUS:                                  /* [??9] */
        g->sum -= MINUS_VALUE;
        if (g->sum < 0) g->sum = 0;
        add_log(g, "%s: [?⑷퀎 -10] ?ъ슜! ?⑷퀎媛 %d濡?以꾩뿀?듬땲??", WHO_NAME[who], g->sum);
        break;
    case ITEM_SKIP:                                   /* [??0] */
        g->skip_next = 1;
        add_log(g, "%s: [???ㅽ궢] ?ъ슜! ?곷? ?댁쓣 嫄대꼫?곷땲??", WHO_NAME[who]);
        break;
    case ITEM_SEAL:                                   /* [??1] */
        n = max_playable(opp);
        if (n) {
            opp->sealed[n] = 1;
            add_log(g, "%s: [遊됱씤] ?ъ슜! ?곷???%d 移대뱶瑜?遊됱씤?덉뒿?덈떎.", WHO_NAME[who], n);
        } else {
            add_log(g, "%s: [遊됱씤] ?ъ슜... 遊됱씤??移대뱶媛 ?놁뒿?덈떎.", WHO_NAME[who]);
        }
        break;
    }
}

/* [??2] 蹂대꼫???꾩씠??*/
void give_bonus(Game *g)
{
    int w, i;
    for (w = 0; w < 2; w++)
        for (i = 0; i < ITEM_SLOT; i++)
            if (g->p[w].items[i] == ITEM_NONE) {
                g->p[w].items[i] = rand() % (ITEM_KIND - 1) + 1;
                break;
            }
    add_log(g, "%d??蹂대꼫?? ?묒そ???꾩씠??1?μ뵫 吏湲?(鍮??щ’???덉쓣 ??", BONUS_TURN);
    if (sound_on) { Beep(880, 60); Beep(1320, 60); }
}

/* [??1] 濡쒓렇 異붽? (?ㅻ옒??以꾩? ?꾨줈 諛?ㅻ궓) */
void add_log(Game *g, const char *fmt, ...)
{
    va_list ap;
    int i;
    for (i = 0; i < LOG_LINES - 1; i++)
        strcpy(g->log[i], g->log[i + 1]);
    va_start(ap, fmt);
    vsnprintf(g->log[LOG_LINES - 1], sizeof(g->log[0]), fmt, ap);
    va_end(ap);
}

void add_history(Player *p, int card)
{
    int i;
    if (p->history_count == HISTORY_MAX) {
        for (i = 0; i < HISTORY_MAX - 1; i++) p->history[i] = p->history[i + 1];
        p->history_count--;
    }
    p->history[p->history_count++] = card;
}

/* ============================================================
 *  洹몃━湲?
 * ============================================================ */
void draw_game(Game *g)
{
    int i, n;
    Player *com = &g->p[COM], *user = &g->p[USER];

    system("cls");
    /* ?곷떒 ?뺣낫 */
    print_at(2, 1, C_CYAN, "100???섏뼱??: ?꾩씠??移대뱶 諛고?");
    print_at(50, 1, C_GRAY, "?쒖씠??: %-6s ??: %d", DIFF_NAME[g->difficulty], g->round + 1);
    print_at(1, 2, C_DARK, "-------------------------------------------------------------------------------");

    /* 而댄벂???곸뿭 */
    print_at(2, 3, g->turn == COM ? C_RED : C_DARK, "[而댄벂??%s", g->turn == COM ? " ? 李⑤?" : "");
    print_at(18, 3, C_GRAY, "?レ옄 :");
    for (n = MIN_NUM; n <= MAX_NUM; n++) {
        int c = com->used[n] ? C_DARK : (com->sealed[n] ? C_MAGENTA : C_RED);
        print_at(25 + (n - 1) * 3, 3, c, "%2d", n);
    }
    print_at(18, 4, C_GRAY, "?꾩씠??:");
    for (i = 0; i < ITEM_SLOT; i++)
        print_at(27 + i * 4, 4, com->items[i] ? C_RED : C_DARK, com->items[i] ? "[?]" : "[ ]");
    print_at(18, 5, C_GRAY, "理쒓렐 :");
    for (i = 0; i < com->history_count; i++)
        print_at(25 + i * 3, 5, C_RED, "%2d", com->history[i]);

    draw_gauge(g);
    draw_status(g);

    print_at(1, 10, C_DARK, "------------------------------- 寃뚯엫 湲곕줉 -------------------------------------");
    draw_log(g);
    print_at(1, 16, C_DARK, "-------------------------------------------------------------------------------");

    /* ?ъ슜???곸뿭 */
    print_at(2, 17, g->turn == USER ? C_BLUE : C_DARK, "[?ъ슜??%s", g->turn == USER ? " ? 李⑤?" : "");
    print_at(18, 17, C_GRAY, "理쒓렐 :");
    for (i = 0; i < user->history_count; i++)
        print_at(25 + i * 3, 17, C_BLUE, "%2d", user->history[i]);

    draw_hand(g, 0, -1, 0);
    print_at(3, 27, C_DARK, "?먥넂:?대룞  ?묅넃:?レ옄/?꾩씠???꾪솚  Enter:?좏깮  S:??? ESC:硫붾돱");
}

/* [??7] ?⑷퀎 寃뚯씠吏 諛?*/
void draw_gauge(Game *g)
{
    int i, fill = g->sum * GAUGE_LEN / MAX_SCORE;
    int color = g->sum < 70 ? C_GREEN : (g->sum < 90 ? C_YELLOW : C_RED);
    if (fill > GAUGE_LEN) fill = GAUGE_LEN;

    print_at(2, 7, C_WHITE, "?⑷퀎 %3d / %d  ", g->sum, MAX_SCORE);
    set_color(C_DARK);  printf("[");
    set_color(color);
    for (i = 0; i < GAUGE_LEN; i++) printf(i < fill ? "#" : " ");
    set_color(C_DARK);  printf("]");
    set_color(C_GRAY);
}

/* ?꾩옱 嫄몃젮 ?덈뒗 ?④낵 ?쒖떆 */
void draw_status(Game *g)
{
    clear_line(8);
    gotoxy(2, 8);
    if (g->double_on) { set_color(C_YELLOW);  printf("[?붾툝 ?곸슜 以? "); }
    if (g->skip_next) { set_color(C_CYAN);    printf("[???ㅽ궢 ?덉빟] "); }
    set_color(C_MAGENTA); printf("  蹂대씪???レ옄 = 遊됱씤??移대뱶");
    set_color(C_GRAY);
}

void draw_log(Game *g)
{
    int i;
    for (i = 0; i < LOG_LINES; i++) {
        clear_line(11 + i);
        print_at(3, 11 + i, i == LOG_LINES - 1 ? C_WHITE : C_DARK, "%s", g->log[i]);
    }
}

/* [??5] 移대뱶 紐⑥뼇 洹몃━湲?*/
void draw_box(int x, int y, int w, const char *text, int color, int selected)
{
    int i;
    set_color(color);
    gotoxy(x, y);
    printf("+");
    for (i = 0; i < w - 2; i++) printf(selected ? "=" : "-");
    printf("+");
    gotoxy(x, y + 1);
    printf("|%-*s|", w - 2, text);
    gotoxy(x, y + 2);
    printf("+");
    for (i = 0; i < w - 2; i++) printf(selected ? "=" : "-");
    printf("+");
    set_color(C_GRAY);
}

/* [??5][??8] ?먰뙣留??ㅼ떆 洹몃━湲?(?붾㈃ ?꾩껜瑜?吏?곗? ?딆븘 源쒕묀??媛먯냼) */
void draw_hand(Game *g, int row, int col, int item_used)
{
    Player *me = &g->p[USER];
    char buf[20];
    int n, i, color, sel;

    print_at(3, 18, row == 0 && col >= 0 ? C_WHITE : C_DARK, "?レ옄 移대뱶");
    for (n = MIN_NUM; n <= MAX_NUM; n++) {
        sel = (row == 0 && col == n - 1);
        if (me->used[n])        color = C_DARK;
        else if (me->sealed[n]) color = C_MAGENTA;
        else                    color = C_WHITE;
        if (sel) color = C_YELLOW;
        sprintf(buf, " %2d ", n);
        draw_box(3 + (n - 1) * 7, 19, 6, buf, color, sel);
    }

    print_at(3, 22, row == 1 ? C_WHITE : C_DARK, "?꾩씠??移대뱶%s", item_used ? " (?대쾲 ???ъ슜 ?꾨즺)" : "                    ");
    for (i = 0; i < ITEM_SLOT; i++) {
        sel = (row == 1 && col == i);
        if (me->items[i] == ITEM_NONE || item_used) color = C_DARK;
        else                                        color = C_GREEN;
        if (sel) color = C_YELLOW;
        sprintf(buf, " %s", ITEM_NAME[me->items[i]]);
        draw_box(3 + i * 14, 23, 12, buf, color, sel);
    }

    /* ?좏깮???꾩씠???ㅻ챸 */
    clear_line(26);
    if (row == 1 && me->items[col] != ITEM_NONE)
        print_at(3, 26, C_GREEN, "%s", ITEM_DESC[me->items[col]]);
}

/* ============================================================
 *  ?먮떒 ?꾩슦誘?+ [??3][??3] AI
 * ============================================================ */
int playable(Player *p, int n) { return !p->used[n] && !p->sealed[n]; }

int max_playable(Player *p)
{
    int n;
    for (n = MAX_NUM; n >= MIN_NUM; n--) if (playable(p, n)) return n;
    return 0;
}

int min_playable(Player *p)
{
    int n;
    for (n = MIN_NUM; n <= MAX_NUM; n++) if (playable(p, n)) return n;
    return 0;
}

int random_playable(Player *p)
{
    int list[MAX_NUM], cnt = 0, n;
    for (n = MIN_NUM; n <= MAX_NUM; n++) if (playable(p, n)) list[cnt++] = n;
    return cnt ? list[rand() % cnt] : 0;
}

int all_used(Player *p)
{
    int n;
    for (n = MIN_NUM; n <= MAX_NUM; n++) if (!p->used[n]) return 0;
    return 1;
}

int find_item(Player *p, int type)
{
    int i;
    for (i = 0; i < ITEM_SLOT; i++) if (p->items[i] == type) return i;
    return -1;
}

int item_count(Player *p)
{
    int i, cnt = 0;
    for (i = 0; i < ITEM_SLOT; i++) if (p->items[i] != ITEM_NONE) cnt++;
    return cnt;
}

/* ?곷?媛 ?ㅼ쓬 ?댁뿉 ?????덈뒗 媛?????レ옄 (???쇱쑝硫?由ы븘?섎?濡?MAX_NUM) */
int next_max(Player *p)
{
    int n, any = 0;
    for (n = MAX_NUM; n >= MIN_NUM; n--) {
        if (!p->used[n]) {
            any = 1;
            if (!p->sealed[n]) return n;
        }
    }
    return any ? 0 : MAX_NUM;
}

/* 吏湲??대㈃ 諛붾줈 ?닿린??媛???묒? 移대뱶 (?놁쑝硫?0) */
int winning_card(Game *g, Player *me)
{
    int n, mul = g->double_on ? 2 : 1;
    for (n = MIN_NUM; n <= MAX_NUM; n++)
        if (playable(me, n) && g->sum + n * mul > MAX_SCORE) return n;
    return 0;
}

/* ?닿퀬 ?섏꽌???곷?媛 諛붾줈 紐??닿린??移대뱶 以?媛????寃?(?놁쑝硫?0) */
int safe_card(Game *g)
{
    Player *me = &g->p[COM], *opp = &g->p[USER];
    int n, mul = g->double_on ? 2 : 1;
    int threat = next_max(opp) * (find_item(opp, ITEM_DOUBLE) >= 0 ? 2 : 1);
    for (n = MAX_NUM; n >= MIN_NUM; n--)
        if (playable(me, n) && g->sum + n * mul + threat <= MAX_SCORE) return n;
    return 0;
}

/* ?ъ? : 臾댁옉?? ?꾩씠????? */
int ai_easy(Game *g)
{
    return random_playable(&g->p[COM]);
}

/* 蹂댄넻 : ?닿만 ???덉쑝硫??닿린怨? 媛???꾩씠?쒖쓣 ?꾨Т嫄곕굹 ? */
int ai_normal(Game *g)
{
    Player *me = &g->p[COM];
    int c = winning_card(g, me), slot;
    if (c) return c;

    if (item_count(me) > 0 && rand() % 100 < 30) {
        do { slot = rand() % ITEM_SLOT; } while (me->items[slot] == ITEM_NONE);
        use_item(g, COM, slot);
        draw_game(g);
        Sleep(500);
        c = winning_card(g, me);
        if (c) return c;
    }
    return random_playable(me);
}

/* ?대젮? : ?밸━?????덉쟾?????꾩씠?쒖쑝濡??꾧린 ?덉텧 (?꾩씠?쒖? ?대떦 1媛? */
int ai_hard(Game *g)
{
    Player *me = &g->p[COM], *opp = &g->p[USER];
    int c, slot, n;

    /* 1) 諛붾줈 ?닿만 ???덉쑝硫??밸━ */
    if ((c = winning_card(g, me)) != 0) return c;

    /* 2) ?붾툝???곕㈃ ?닿만 ???덉쑝硫??ъ슜 */
    slot = find_item(me, ITEM_DOUBLE);
    if (slot >= 0 && g->sum + max_playable(me) * 2 > MAX_SCORE) {
        use_item(g, COM, slot);
        draw_game(g); Sleep(500);
        return winning_card(g, me);
    }

    /* 3) ?곷??먭쾶 ?밸━ 湲고쉶瑜?二쇱? ?딅뒗 移대뱶 */
    if ((c = safe_card(g)) != 0) return c;

    /* 4) ?꾧린! ?꾩씠?쒖쑝濡?留됯린 */
    slot = find_item(me, ITEM_SEAL);
    if (slot >= 0 && (n = max_playable(opp)) != 0) {
        opp->sealed[n] = 1;                 /* 誘몃━ 遊됱씤??蹂닿퀬 */
        c = safe_card(g);
        opp->sealed[n] = 0;                 /* ?먮옒?濡?*/
        if (c) {
            use_item(g, COM, slot);
            draw_game(g); Sleep(500);
            return safe_card(g);
        }
    }
    slot = find_item(me, ITEM_MINUS);
    if (slot >= 0) {
        use_item(g, COM, slot);
        draw_game(g); Sleep(500);
        c = safe_card(g);
        return c ? c : min_playable(me);
    }
    slot = find_item(me, ITEM_SKIP);
    if (slot >= 0) {
        use_item(g, COM, slot);
        draw_game(g); Sleep(500);
        return max_playable(me);
    }

    /* 5) 諛⑸쾿???놁쑝硫?媛???묒? ?섎줈 踰꾪떚湲?*/
    return min_playable(me);
}

/* ============================================================
 *  [??4][??5][??6] ?뚯씪 ???/ 遺덈윭?ㅺ린
 * ============================================================ */
int save_game(Game *g)
{
    FILE *fp = fopen(SAVE_FILE, "wb");
    if (fp == NULL) return 0;
    fwrite(g, sizeof(Game), 1, fp);
    fclose(fp);
    return 1;
}

int load_game(Game *g)
{
    FILE *fp = fopen(SAVE_FILE, "rb");
    int ok;
    if (fp == NULL) return 0;
    ok = (fread(g, sizeof(Game), 1, fp) == 1) && (g->magic == SAVE_MAGIC);
    fclose(fp);
    if (ok) add_log(g, "??λ맂 寃뚯엫??遺덈윭?붿뒿?덈떎.");
    return ok;
}

void load_record(Record *r)
{
    FILE *fp = fopen(RECORD_FILE, "r");
    r->win = r->lose = r->draw = 0;
    if (fp == NULL) return;
    if (fscanf(fp, "%d %d %d", &r->win, &r->lose, &r->draw) != 3)
        r->win = r->lose = r->draw = 0;
    fclose(fp);
}

void save_record(Record *r)
{
    FILE *fp = fopen(RECORD_FILE, "w");
    if (fp == NULL) return;
    fprintf(fp, "%d %d %d\n", r->win, r->lose, r->draw);
    fclose(fp);
}
