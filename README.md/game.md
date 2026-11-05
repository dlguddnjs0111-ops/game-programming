# 🃏 100을 넘어라 : 아이템 카드 배틀 (C언어 콘솔 게임)

C언어로 개발된 턴제 전략 콘솔 게임입니다. 기본 숫자 누적 게임인 **'100을 넘어라'** 원본을 기반으로, 화려한 콘솔 UI와 아이템 배틀 시스템, 그리고 AI 난이도를 더해 크게 업그레이드한 프로젝트입니다.

---

## 🎮 게임 개요
컴퓨터와 사용자가 번갈아 가며 1~10 사이의 숫자 카드를 냅니다. 낸 숫자는 합계에 누적되며, **최초로 합계 100을 넘기는 사람**이 승리합니다. 
단순한 덧셈을 넘어 4가지의 '특수 아이템'과 시간 제한, 3단계의 AI 난이도를 도입하여 쫄깃한 전략적 재미를 제공합니다.

---

## ✨ 핵심 기능 및 업그레이드 내역 (Features)

### 1. 기본 버전 (Original)
- 1~10 난수 생성 및 사용자 입력 시스템.
- 배열을 활용한 숫자 중복 사용 방지 알고리즘.
- `Windows.h`의 `gotoxy`를 활용한 기본적인 콘솔 좌표 제어.

### 2. 업그레이드 버전 (Item Card Battle)
- **방향키 UI 도입**: `scanf` 텍스트 입력 대신 키보드 방향키(←, →)와 엔터(Enter)를 이용한 직관적인 카드 선택 시스템.
- **아이템 시스템**: 
  - `[더블 x2]` : 이번 턴에 내는 숫자가 2배로 적용됨.
  - `[합계 -10]` : 현재 합계를 10 줄여 상대의 승리를 방해.
  - `[턴 스킵]` : 상대의 턴을 건너뛰고 내가 연속으로 플레이.
  - `[봉인]` : 다음 1턴 동안 상대방의 가장 큰 숫자 카드를 사용 불가 상태로 만듦.
- **AI 난이도 세분화**: 
  - `쉬움 (EASY)`: 무작위 숫자 선택
  - `보통 (NORMAL)`: 승리 각이 보이면 이기는 수 선택
  - `어려움 (HARD)`: 상대방의 수를 읽고 상황에 맞게 아이템을 적극 활용
- **몰입감 넘치는 시스템**: 시간 제한(20초 타이머), 효과음(Beep음), 컬러 콘솔 UI, 세이브/로드 기능 및 누적 전적 기록 시스템 추가.

---

## 💻 실행 방법 및 환경 (How to Run)

- **개발 환경:** Dev C++ (MinGW GCC Compiler)
- **운영체제:** Windows (Windows API 사용)
- **컴파일 주의사항:**
  한글 깨짐 현상을 방지하기 위해 파일 인코딩을 `ANSI (EUC-KR)`로 설정하여 컴파일하거나, 콘솔 환경에 맞게 `chcp 65001` 옵션을 조율하여 실행하세요.
- **조작법:**
  - `↑ / ↓` : 숫자 카드 / 아이템 카드 영역 전환
  - `← / →` : 카드 선택 이동
  - `Enter` : 카드 내기 (확정)
  - `S` : 게임 저장
  - `ESC` : 메뉴로 돌아가기 (일시정지)

---

## 📂 파일 구성
- `original_game.c` : 100을 넘어라 기본 버전 소스 코드
- `card_battle_100.c` : 아이템 배틀 적용 업그레이드 소스 코드
- `save.dat` : 게임 진행 세이브 데이터 (자동 생성)
- `record.txt` : 게임 승패 누적 전적 데이터 (자동 생성)

---

## 👨‍💻 Developer
- **작성자:** [본인 이름 또는 닉네임 입력]
- 이 프로젝트는 C언어의 배열, 포인터, 구조체, Windows API 콘솔 제어 및 파일 입출력을 학습하기 위해 제작되었습니다.


# 🎮 100을 넘어라 : 아이템 카드 배틀
## 38개 업그레이드 상세 설명서

---

## 🔴 PHASE 1: 버그 수정 (1~8)

### 업그레이드 1️⃣ - 입력 범위 검사

**문제점**
```
사용자가 1~10이 아닌 숫자를 입력했을 때:
- 999를 입력 → 합계가 999 증가 → 한 번에 게임 끝
- -50을 입력 → 합계가 줄어듦 → 게임 규칙 파괴
```

**이전 코드**
```c
int user_number(int i, int user_array[])
{
    int j, number;
    again:;
    gotoxy(1, 7);
    printf("사용자 숫자 입력후 Enter>");
    scanf("%d", &number);
    // ❌ 범위 검사 없음!
    user_array[i]=number;
    return user_array[i];
}
```

**변경된 코드**
```c
int user_number(int i, int user_array[])
{
    int number, result;
    while (1)
    {
        clear_line(7);
        gotoxy(1, 7);
        printf("사용자 숫자 입력후 Enter> ");
        result = scanf("%d", &number);

        clear_line(8);
        gotoxy(1, 8);
        
        // ✅ 1~10 범위 검사 추가!
        if (result != 1)
            printf("숫자만 입력하세요.");
        else if (number < MIN_NUM || number > MAX_NUM)
            printf("%d~%d 사이의 숫자만 입력하세요.", MIN_NUM, MAX_NUM);
        else if (is_duplicate(i, user_array, number))
            printf("이미 사용한 숫자입니다.");
        else
            break;
    }
    user_array[i] = number;
    return number;
}
```

**메커니즘**
- `scanf` 실패(`result != 1`)를 먼저 확인
- 그 다음 `number < MIN_NUM || number > MAX_NUM` 조건으로 범위 체크
- 모든 조건을 통과한 수만 `break`로 반복문 탈출
- 실패하면 오류 메시지를 보여주고 다시 입력 유도

**왜 수정했나?**
- 게임의 핵심 규칙("1~10")을 강제해야 공정한 게임이 됨
- 사용자가 실수로 잘못된 숫자를 입력해도 게임이 깨지지 않음

---

### 업그레이드 2️⃣ - 문자 입력 무한 루프 해결

**문제점**
```
사용자가 문자를 입력했을 때:
- "abc" 입력 → scanf가 실패 → 'a', 'b', 'c'가 입력 버퍼에 그대로 남음
- 다음 scanf 호출 → 바로 'a'를 읽고 실패 → 무한 루프
- 프로그램이 반응 없음 (Ctrl+C로만 종료 가능)
```

**이전 코드**
```c
again:;
scanf("%d", &number);  // ❌ 버퍼에 'a', 'b', 'c' 남음
for(j=0;j<i;j+=1)
    if (user_array[j]==number)
        goto again;   // ❌ 다시 scanf 호출 → 'a'를 읽음 → 계속 실패
```

**변경된 코드**
```c
void clear_input_buffer(void)  // ✅ 새로운 함수
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    // '\n'이 나올 때까지 버퍼를 계속 비움
}

// 게임 루프에서
while (1)
{
    result = scanf("%d", &number);
    clear_input_buffer();  // ✅ 버퍼 비우기
    
    if (result != 1)
        printf("숫자만 입력하세요.");
    else
        break;
}
```

**메커니즘**
- `scanf("%d", &number)`는 "abc" 입력에서 실패하고 'a', 'b', 'c'를 버퍼에 남김
- `clear_input_buffer()`가 `getchar()`를 계속 호출하면서 '\n'(Enter 키)이 나올 때까지 모든 문자를 버림
- 버퍼가 비워졌으므로 다음 `scanf`는 깨끗한 상태에서 새로운 입력을 받을 수 있음

**왜 수정했나?**
- 입력 버퍼 오염 → 프로그램 멈춤 → 사용자 경험 최악
- 튼튼한 입력 처리는 게임의 기본

---

### 업그레이드 3️⃣ - 화면 잔상 제거

**문제점**
```
사용자가 "10"을 입력했다가 중복으로 다시 "3"을 입력했을 때:
- 이전 오류 메시지("중복된 숫자입니다")가 화면에 남아 있음
- 새로운 입력 프롬프트("사용자 숫자 입력후 Enter>")가 뒤에 붙음
- 화면이 지저분하고 뭐가 뭔지 모름

시각적 혼란:
[이전]
사용자 숫자 입력후 Enter> 10
중복된 숫자입니다.
사용자 숫자 입력후 Enter> 3
```

**이전 코드**
```c
gotoxy(1, 7);
printf("사용자 숫자 입력후 Enter>");
scanf("%d", &number);

for(j=0;j<i;j+=1)
    if (user_array[j]==number)
    {
        gotoxy(1, 8);
        printf("중복된 숫자를 입력했습니다. \n");  // ❌ 이전 메시지가 남음
        goto again;
    }
```

**변경된 코드**
```c
void clear_line(int y)  // ✅ 새로운 함수
{
    gotoxy(1, y);
    printf("%70s", "");  // 공백 70개로 한 줄을 지움
}

// 게임 루프에서
while (1)
{
    clear_line(7);  // ✅ 입력칸 지우기
    gotoxy(1, 7);
    printf("사용자 숫자 입력후 Enter> ");
    scanf("%d", &number);

    clear_line(8);  // ✅ 오류 메시지 칸 미리 지우기
    gotoxy(1, 8);
    
    if (...)
        printf("범위 초과...");  // 새로운 메시지만 보임
}
```

**메커니즘**
- 매 루프마다 시작하기 전에 `clear_line(7)`으로 입력 칸을 공백으로 채워서 지움
- 오류 메시지를 출력하기 직전에 `clear_line(8)`로 이전 메시지를 지움
- 그 다음 새로운 메시지를 출력 → 항상 깨끗한 화면 유지

**왜 수정했나?**
- 사용자가 화면을 명확하게 읽을 수 있어야 함
- 게임의 전문성과 사용자 경험 향상

---

### 업그레이드 4️⃣ - win 변수 초기화

**문제점**
```c
int win;  // ❌ 초기화하지 않음 (쓰레기 값)

for(i=0;i<10;i+=1)
{
    // 게임 진행...
    if (sum > 100) {
        win = 1;  // 여기서 처음 할당
        break;
    }
}

if (100개 턴을 다 돌아도 100을 못 넘으면)
    conclusion(win);  // ❌ win이 쓰레기 값이거나 정의되지 않은 값
```

**이전 코드**
```c
void game_control(void)
{
    int com_array[10]={0}, user_array[10]={0}, number;
    int i, sum=0, win;  // ❌ win 초기화 없음
    
    for(i=0;i<10;i+=1)
    {
        // ...
    }
    conclusion(win);  // ❌ 위험!
}
```

**변경된 코드**
```c
void game_control(void)
{
    int com_array[MAX_TURN] = {0}, user_array[MAX_TURN] = {0};
    int i, number, sum = 0;
    int win = 0;  // ✅ 초기값 설정

    for (i = 0; i < MAX_TURN; i++)
    {
        // ...
        if (sum > MAX_SCORE) { win = 1; break; }
        // ...
        if (sum > MAX_SCORE) { win = 2; break; }
    }
    conclusion(win);
}
```

**메커니즘**
- `int win = 0;`으로 명시적으로 초기화
- 게임 진행 중 조건에 따라 `win = 1` 또는 `win = 2`로 변경
- `conclusion()` 함수에서 `win == 0`인 경우를 무승부로 처리 가능

**왜 수정했나?**
- 초기화하지 않은 변수는 메모리에 있던 쓰레기 값을 읽음
- 매번 다른 값이 될 수 있어 디버깅 불가능 (심각한 버그)
- C 표준에서 정의되지 않은 동작이므로 절대 금지

---

### 업그레이드 5️⃣ - 결과 위치 고정과 창 바로 닫힘 해결

**문제점**
```
1. 결과 메시지가 화면의 아무 위치나 출력됨
   - "컴퓨터가 이겼습니다"가 (25, 15)에 출력 → 사용자가 못 찾음

2. 결과가 나오자마자 프로그램이 즉시 끝남
   - 결과를 읽기도 전에 콘솔 창이 닫힘
```

**이전 코드**
```c
void conclusion(int check)
{
    if (check==1)
        printf("컴퓨터가 이겼습니다. \n");  // ❌ 위치 지정 없음
    else
        printf("사용자가 이겼습니다. \n");
}

void game_control(void)
{
    // ...
    conclusion(win);
    // ❌ 바로 main() 종료 → 프로그램 끝
}
```

**변경된 코드**
```c
void conclusion(int win)
{
    gotoxy(1, 9);  // ✅ 정확한 위치 지정 (1, 9)
    if (win == 1)
        printf("컴퓨터가 이겼습니다.");
    else if (win == 2)
        printf("사용자가 이겼습니다.");
    else
        printf("무승부입니다.");
}

void game_control(void)
{
    // ...
    conclusion(win);
    press_any_key();  // ✅ 사용자가 키를 누를 때까지 대기
}

void press_any_key(void)
{
    gotoxy(1, 10);
    printf("아무키나 누르시오..");
    _getch();  // 엔터 키 입력 대기
}
```

**메커니즘**
- `gotoxy(1, 9)`로 결과 메시지가 항상 같은 위치에 출력되도록 고정
- `press_any_key()`에서 사용자가 키를 누를 때까지 프로그램을 중단
- 사용자가 결과를 충분히 읽을 수 있는 시간 제공

**왜 수정했나?**
- 사용자가 결과를 확인할 수 있어야 함
- 결과 위치가 일정해야 게임이 전문적으로 보임

---

### 업그레이드 6️⃣ - Visual Studio 컴파일 오류 해결

**문제점**
```
Visual Studio에서 컴파일 시:
1. scanf 경고:
   error C4996: 'scanf': This function or variable may be unsafe
2. getch 오류:
   error C4996: 'getch': The POSIX name for this item is deprecated
```

**이전 코드**
```c
#include <stdio.h>
// ❌ 이 매크로 없음

scanf("%d", &number);  // ❌ VS에서 경고/오류
getch();               // ❌ VS에서 오류
```

**변경된 코드**
```c
#define _CRT_SECURE_NO_WARNINGS  // ✅ 맨 처음에 추가

#include <stdio.h>
#include <time.h>
#include <conio.h>
// ...

scanf("%d", &number);  // 이제 경고 없음
_getch();              // ✅ 표준 이름 사용
```

**메커니즘**
- `#define _CRT_SECURE_NO_WARNINGS`는 Microsoft 특화 보안 경고 무시
  - VS가 "scanf는 버퍼 오버플로우 위험" 경고를 하지 않음
- `getch()`는 비표준 함수이고 `_getch()`가 VS의 표준 이름
- 만약 다른 컴파일러(gcc, clang)를 쓸 때는 `#define _CRT_SECURE_NO_WARNINGS` 부분만 지우면 됨

**왜 수정했나?**
- Visual Studio에서 오류 없이 컴파일되어야 함
- 오류 메시지가 많으면 실제 오류를 놓칠 수 있음

---

### 업그레이드 7️⃣ - goto 제거

**문제점**
```
goto를 사용한 코드:
1. 흐름 추적이 어려움
   - 어디서 점프했는지 한눈에 안 보임
   - 복잡한 로직에서는 "스파게티 코드"가 됨

2. 디버깅이 힘듦
   - 반복이 정확히 몇 번 되는지 불명확
   - 변수 초기화 누락 위험

3. 코드 리뷰 시 낮은 평가
   - "왜 반복문을 안 썼나?" 질문 받음
```

**이전 코드**
```c
int computer_number(int i, int com_array[])
{
    int j, number;
    again:;  // ❌ 레이블
    number=rand()%10+1;
    for(j=0;j<i;j+=1)
        if (com_array[j]==number)
            goto again;  // ❌ 레이블로 점프
    com_array[i]=number;
    return com_array[i];
}
```

**변경된 코드**
```c
// ✅ 중복 검사를 함수로 분리
int is_duplicate(int count, int arr[], int number)
{
    int j;
    for (j = 0; j < count; j++)
        if (arr[j] == number)
            return 1;  // 중복 있음
    return 0;         // 중복 없음
}

// ✅ do-while 반복문으로 변경
int computer_number(int i, int com_array[])
{
    int number;
    do {
        number = rand() % (MAX_NUM - MIN_NUM + 1) + MIN_NUM;
    } while (is_duplicate(i, com_array, number));
    // 중복이 없을 때까지 반복
    
    com_array[i] = number;
    return number;
}
```

**메커니즘**
- `do-while` 반복문: 먼저 한 번 실행 후 조건 확인
  ```
  do { 숫자 생성 } while (중복이 있음)
  → 중복이 없으면 탈출
  ```
- 중복 검사 로직을 `is_duplicate()` 함수로 분리
  - 가독성 향상
  - 테스트 용이
  - 중복 코드 방지 (2곳에서 필요하니까)

**왜 수정했나?**
- 현대적이고 읽기 쉬운 코드
- 대학교과 및 업계 표준 (goto는 거의 안 씀)
- 유지보수가 훨씬 쉬움

---

### 업그레이드 8️⃣ - 매직 넘버 상수화

**문제점**
```
코드에 숫자가 직접 박혀 있을 때:
1. 규칙 변경이 어려움
   - 100을 120으로 바꾸려면? → "100"을 모두 찾아서 바꿈
   - 10을 15로 바꾸려면? → "10"을 모두 찾아서 바꿈 (변수명도 있어서 위험!)

2. 의미가 불명확함
   - 코드에서 "10"을 봤을 때 "카드 최대 개수"인지 "최대 번호"인지 애매함

3. 버그 위험
   - 잘못된 "10"을 바꾸면 게임이 깨짐
```

**이전 코드**
```c
for(i=0;i<10;i+=1)  // ❌ 10의 의미? 최대 턴 수?
{
    if (max<sum)  // ❌ max가 뭐지? 100이겠지만 명확하지 않음
    {
        win=1;
        break;
    }
}

int user_number(int i, int user_array[])
{
    int j, number;
    again:;
    number=rand()%10+1;  // ❌ 1~10이 코드에 흩어져 있음
```

**변경된 코드**
```c
// ✅ 상수 정의 (파일 맨 위)
#define MAX_SCORE 100   // 목표 점수
#define MAX_TURN  10    // 최대 턴 수
#define MIN_NUM   1     // 최소 숫자
#define MAX_NUM   10    // 최대 숫자

// 게임 루프
for(i=0;i<MAX_TURN;i+=1)  // ✅ 의미 명확
{
    if (sum > MAX_SCORE)  // ✅ 의미 명확
    {
        win=1;
        break;
    }
}

// 난수 생성
int computer_number(int i, int com_array[])
{
    int number;
    do {
        number = rand() % (MAX_NUM - MIN_NUM + 1) + MIN_NUM;
        // ✅ 1~10 생성 (MIN_NUM ~ MAX_NUM)
    } while (is_duplicate(i, com_array, number));
    // ...
}
```

**메커니즘**
- `#define 상수이름 값` 형태로 정의
- 프리프로세서가 컴파일 전에 모든 `MAX_SCORE`를 `100`으로 치환
- 코드에서는 의미 있는 이름 사용
- 규칙 변경 시 상수 정의 부분만 수정하면 전체 적용됨

**왜 수정했나?**
- 게임 규칙을 한눈에 파악 가능 (첫 10줄만 보면 됨)
- 나중에 "120점 넘기 게임으로 바꿔"라고 해도 `#define MAX_SCORE 120` 한 줄만 바꿈
- 코드의 의도가 명확함 (전문적)

---

## 🔵 PHASE 2: 화면과 연출 (9~22)

### 업그레이드 9️⃣ - 콘솔 창 설정

**문제점**
```
기본 콘솔 창:
1. 제목이 "C:\\Users\\...\\a.exe" → 뭐하는 게임인지 모름
2. 크기가 일정하지 않음 → 화면 배치가 엉망
3. 창이 작으면 화면이 삐져나가거나 줄바꿈됨
```

**이전 코드**
```c
int main(void)
{
    srand(time(NULL));
    intro_game();  // ❌ 콘솔 설정 없음
    return 0;
}
```

**변경된 코드**
```c
void setup_console(void)  // ✅ 새로운 함수
{
    // 콘솔 창 제목 설정
    SetConsoleTitleA("100을 넘어라 : 아이템 카드 배틀");
    
    // 콘솔 창 크기 설정 (80열 x 32행)
    SMALL_RECT srctWindow = { 0, 0, 79, 31 };
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &srctWindow);
    
    // 콘솔 버퍼 크기 설정
    COORD coordScreen = { 80, 32 };
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coordScreen);
}

int main(void)
{
    srand((unsigned)time(NULL));
    setup_console();  // ✅ 먼저 콘솔 설정
    intro_game();
    game_control();
    return 0;
}
```

**메커니즘**
- `SetConsoleTitleA()`: 윈도우 창의 제목을 "100을 넘어라 : 아이템 카드 배틀"로 변경
- `SetConsoleScreenBufferSize()`: 버퍼 크기를 80x32로 고정
- `SetConsoleWindowInfo()`: 화면 표시 영역을 80x32로 고정
- 이제 모든 사용자의 화면이 동일하게 보임

**왜 수정했나?**
- 게임을 "제목이 있는 프로그램"처럼 보이게 함 (전문성)
- 고정 크기로 화면 레이아웃을 정확히 제어 가능
- 다른 컴퓨터에서 실행해도 같은 화면 유지

---

### 업그레이드 🔟 - 커서 숨기기

**문제점**
```
기본 커서:
1. 깜빡이는 커서 (|)가 화면에 표시됨 → 산만함
2. 게임 중에 커서가 자리를 차지함 → 화면이 지저분해 보임
```

**이전 코드**
```c
// ❌ 커서가 보임
void gotoxy(int x, int y)
{
    COORD Pos = { (SHORT)(x - 1), (SHORT)(y - 1) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
```

**변경된 코드**
```c
void hide_cursor(void)  // ✅ 새로운 함수
{
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = FALSE;  // 커서 숨기기
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

int main(void)
{
    srand((unsigned)time(NULL));
    setup_console();
    hide_cursor();  // ✅ 커서 숨기기
    intro_game();
    game_control();
    return 0;
}
```

**메커니즘**
- `GetConsoleCursorInfo()`: 현재 커서 정보 읽어오기
- `cursorInfo.bVisible = FALSE`: 커서 표시 여부를 "숨김"으로 설정
- `SetConsoleCursorInfo()`: 변경된 커서 정보 다시 설정
- 이제 커서가 화면에 보이지 않음 (깜빡이지 않음)

**왜 수정했나?**
- 화면이 깔끔해 보임
- 게임이 더 전문적으로 느껴짐
- 시각적 집중도 향상

---

### 업그레이드 1️⃣1️⃣ - 색상 시스템

**문제점**
```
흰색 글자만 있을 때:
1. 구분이 어려움
   - 컴퓨터 턴인지 사용자 턴인지 헷갈림
   - 오류 메시지가 일반 글자처럼 보임

2. 게임이 심심해 보임
```

**이전 코드**
```c
printf("컴퓨터 숫자 : ");  // ❌ 모두 흰색
printf("사용자 숫자 : ");  // ❌ 모두 흰색
```

**변경된 코드**
```c
// ✅ 색상 상수 정의
#define COLOR_WHITE    7
#define COLOR_RED      12  // 컴퓨터
#define COLOR_BLUE     9   // 사용자
#define COLOR_YELLOW   14  // 경고

void set_text_color(int color)  // ✅ 새로운 함수
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void number_display(int i, int com_array[], int user_array[], int sum)
{
    // 컴퓨터 숫자 출력 (빨강)
    set_text_color(COLOR_RED);
    gotoxy(1, 2);
    printf("컴퓨터 숫자 : ");
    for (j = 0; j <= i; j++)
        printf("%2d ", com_array[j]);

    // 사용자 숫자 출력 (파랑)
    set_text_color(COLOR_BLUE);
    gotoxy(1, 3);
    printf("사용자 숫자 : ");
    for (j = 0; j <= i; j++)
        if (user_array[j] != 0)
            printf("%2d ", user_array[j]);

    // 합계 출력 (흰색)
    set_text_color(COLOR_WHITE);
    gotoxy(1, 5);
    printf("현재 합계 : %3d", sum);
}

// 오류 메시지 (노랑)
void user_number(int i, int user_array[])
{
    // ...
    if (result != 1) {
        set_text_color(COLOR_YELLOW);
        printf("숫자만 입력하세요.");
    }
}
```

**메커니즘**
- Windows API `SetConsoleTextAttribute()` 사용
- 색상 코드:
  - 7 = 흰색 (기본)
  - 12 = 빨강 (컴퓨터)
  - 9 = 파랑 (사용자)
  - 14 = 노랑 (경고)
- 매 출력 전에 `set_text_color()`로 색상 변경

**왜 수정했나?**
- 게임 진행 상황이 한눈에 보임
- 게임이 훨씬 매력적으로 보임
- 사용자가 누구 턴인지 혼동하지 않음

---

### 업그레이드 1️⃣2️⃣ - 1초 로고 화면

**문제점**
```
게임을 실행하면 바로 설명 화면이 나옴:
1. 첫 인상이 약함 → 게임 같지 않은 느낌
2. 로딩 효과가 없음 → 단순함
```

**이전 코드**
```c
int main(void)
{
    srand((unsigned)time(NULL));
    intro_game();  // ❌ 바로 소개 화면
    game_control();
    return 0;
}

void intro_game(void)
{
    system("cls");
    printf("100을 넘어라 게임\n\n");
    printf("컴퓨터와 사용자가 번갈아가며\n");
    // ...
}
```

**변경된 코드**
```c
void show_logo(void)  // ✅ 새로운 함수
{
    int i;
    system("cls");
    
    // 큰 "100" 로고 출력
    set_text_color(COLOR_YELLOW);
    gotoxy(25, 8);
    printf(" ███████ █████████ ███████ ");
    gotoxy(25, 9);
    printf(" ██      ██        ██      ");
    gotoxy(25, 10);
    printf(" ███████ ██████    ███████ ");
    gotoxy(25, 11);
    printf("      ██ ██        ██      ");
    gotoxy(25, 12);
    printf(" ███████ █████████ ███████ ");
    
    set_text_color(COLOR_WHITE);
    gotoxy(20, 16);
    printf("아이템 카드 배틀");
    
    // 로딩 바 애니메이션
    gotoxy(25, 20);
    printf("로딩중 ");
    for (i = 0; i < 10; i++)
    {
        printf("█");
        Sleep(100);  // 100ms 대기
    }
    
    // 시작 효과음
    if (sound_on)
        Beep(800, 200);  // 주파수 800Hz, 200ms
    
    Sleep(1000);  // 1초 대기
    system("cls");
}

int main(void)
{
    srand((unsigned)time(NULL));
    setup_console();
    hide_cursor();
    show_logo();     // ✅ 로고 화면 먼저 표시
    intro_game();
    game_control();
    return 0;
}
```

**메커니즘**
- ASCII 아트로 "100" 로고를 만들고 노란색으로 출력
- 로딩 바: 10개의 "█" 문자를 0.1초 간격으로 출력
- `Sleep(100)`: 100ms 동안 프로그램 일시 중단
- `Beep(800, 200)`: 800Hz 음파를 200ms 동안 재생
- `Sleep(1000)`: 1초 대기 후 다음 화면으로

**왜 수정했나?**
- 게임의 첫 인상이 좋아짐
- 프로의 게임처럼 보임
- 사용자가 "이 게임 멋진데?"라고 생각

---

### 업그레이드 1️⃣3️⃣ - 방향키 메인 메뉴

**문제점**
```
소개 화면에서 "아무키나 누르면 시작":
1. 메뉴가 없음 → 선택지가 없음
2. 게임 방법을 보고 싶으면? → 프로그램 종료 후 다시 실행해야 함
3. 게임을 다시 하고 싶으면? → 프로그램 종료 후 다시 실행해야 함
```

**이전 코드**
```c
void intro_game(void)
{
    system("cls");
    printf("100을 넘어라 게임\n\n");
    printf("아무키나 누르면 시작합니다.");
    getch();
    // ❌ 그 다음은 바로 게임 시작
}
```

**변경된 코드**
```c
#define MENU_NEW    0
#define MENU_LOAD   1
#define MENU_HELP   2
#define MENU_RECORD 3
#define MENU_SOUND  4
#define MENU_EXIT   5

void show_menu(void)  // ✅ 새로운 함수
{
    int selected = MENU_NEW;
    int key;
    
    while (1)
    {
        system("cls");
        set_text_color(COLOR_WHITE);
        
        gotoxy(20, 5);
        printf("100을 넘어라 : 아이템 카드 배틀");
        
        gotoxy(30, 10);
        if (selected == MENU_NEW)
            set_text_color(COLOR_YELLOW);  // 선택됨
        printf("►  새 게임");
        
        gotoxy(30, 12);
        set_text_color(COLOR_WHITE);
        if (selected == MENU_LOAD)
            set_text_color(COLOR_YELLOW);
        printf("►  이어하기");
        
        gotoxy(30, 14);
        set_text_color(COLOR_WHITE);
        if (selected == MENU_HELP)
            set_text_color(COLOR_YELLOW);
        printf("►  게임 방법");
        
        gotoxy(30, 16);
        set_text_color(COLOR_WHITE);
        if (selected == MENU_RECORD)
            set_text_color(COLOR_YELLOW);
        printf("►  전적");
        
        gotoxy(30, 18);
        set_text_color(COLOR_WHITE);
        if (selected == MENU_SOUND)
            set_text_color(COLOR_YELLOW);
        printf("►  소리 : %s", sound_on ? "ON" : "OFF");
        
        gotoxy(30, 20);
        set_text_color(COLOR_WHITE);
        if (selected == MENU_EXIT)
            set_text_color(COLOR_YELLOW);
        printf("►  종료");
        
        set_text_color(COLOR_WHITE);
        gotoxy(10, 28);
        printf("↑↓ 이동  Enter 선택");
        
        // 키 입력
        key = _getch();
        
        if (key == 224)  // 방향키 누름
        {
            key = _getch();  // 다음 코드 읽음
            if (key == 72)   // ↑
                selected = (selected - 1 + 6) % 6;  // 위로
            else if (key == 80)  // ↓
                selected = (selected + 1) % 6;  // 아래로
        }
        else if (key == 13)  // Enter
        {
            switch (selected)
            {
            case MENU_NEW:
                game_control();  // 새 게임 시작
                break;
            case MENU_LOAD:
                load_game();  // 이어하기
                break;
            case MENU_HELP:
                show_help();  // 게임 방법
                break;
            case MENU_RECORD:
                show_record();  // 전적 보기
                break;
            case MENU_SOUND:
                sound_on = !sound_on;  // 소리 토글
                break;
            case MENU_EXIT:
                return;  // 프로그램 종료
            }
        }
    }
}
```

**메커니즘**
- `selected` 변수로 현재 선택된 메뉴 추적 (0~5)
- ↑ 누르면 `selected - 1` → 위로 이동
- ↓ 누르면 `selected + 1` → 아래로 이동
- Enter 누르면 `switch-case`로 해당 기능 실행
- 선택된 메뉴는 노란색으로 표시 → 사용자가 자신의 선택을 명확히 봄
- 방향키 처리: Windows에서 방향키는 2개 코드 (224 + 방향)로 전달되므로 2번 읽어야 함

**왜 수정했나?**
- 게임의 모든 기능에 접근 가능
- 사용자가 게임을 계속할 수 있음 (프로그램 재실행 불필요)
- 게임이 완전한 하나의 프로그램처럼 느껴짐

---

### 업그레이드 1️⃣4️⃣ - 게임 방법 화면 개편

**문제점**
```
기존: 한 페이지에 규칙만 표시
1. 아이템 카드가 무엇인지 설명이 없음
2. 사용자가 게임을 시작하면 "아, 이건 뭐지?" 하고 헷갈림
3. 전문성 없어 보임
```

**이전 코드**
```c
void intro_game(void)
{
    system("cls");
    printf("100을 넘어라 게임\n\n");
    printf("컴퓨터와 사용자가 번갈아가며\n");
    printf("숫자를 입력하되 1~10사이의 \n");
    printf("중복되지 않는 숫자를 입력하여 \n\n");
    printf("최초로 100을 넘기면 승자가 됩니다. \n\n");
    printf("컴퓨터가 먼저 시작합니다. \n");
    printf("아무키나 누르면 시작합니다.");
    getch();
}
```

**변경된 코드**
```c
void show_help(void)  // ✅ 새로운 함수 (2페이지)
{
    int page = 0;
    
    while (1)
    {
        system("cls");
        set_text_color(COLOR_WHITE);
        
        if (page == 0)
        {
            gotoxy(20, 3);
            set_text_color(COLOR_YELLOW);
            printf("▶ 기본 규칙");
            
            set_text_color(COLOR_WHITE);
            gotoxy(10, 6);
            printf("• 1~10 사이의 숫자를 선택합니다.");
            gotoxy(10, 8);
            printf("• 각 숫자는 게임 중 최대 1번만 사용합니다.");
            gotoxy(10, 10);
            printf("• 선택한 숫자들의 합을 누적합니다.");
            gotoxy(10, 12);
            printf("• 합계를 처음으로 100을 넘긴 사람이 승자입니다.");
            gotoxy(10, 14);
            printf("• 난이도를 선택할 수 있습니다.");
            gotoxy(10, 16);
            printf("  - 쉬움: 컴퓨터가 무작위 선택");
            gotoxy(10, 18);
            printf("  - 보통: 컴퓨터가 이길 수 있으면 이김");
            gotoxy(10, 20);
            printf("  - 어려움: 컴퓨터가 수를 읽고 아이템까지 씀");
        }
        else if (page == 1)
        {
            gotoxy(20, 3);
            set_text_color(COLOR_YELLOW);
            printf("▶ 아이템 카드");
            
            set_text_color(COLOR_WHITE);
            gotoxy(10, 6);
            printf("더블 (×2)");
            gotoxy(10, 7);
            printf("  이번 턴에 선택한 숫자가 2배가 됩니다.");
            
            gotoxy(10, 9);
            printf("합계 감소 (-10)");
            gotoxy(10, 10);
            printf("  현재 합계를 10 줄입니다. (방어용)");
            
            gotoxy(10, 12);
            printf("턴 스킵 (Skip)");
            gotoxy(10, 13);
            printf("  상대의 턴을 건너뛰고 내가 한 번 더 합니다.");
            
            gotoxy(10, 15);
            printf("봉인 (Seal)");
            gotoxy(10, 16);
            printf("  상대의 가장 큰 카드를 1턴 동안 못 쓰게 합니다.");
            
            gotoxy(10, 18);
            printf("아이템은 4턴마다 1장씩 지급됩니다.");
        }
        
        gotoxy(10, 26);
        if (page == 0)
            printf("← 이전  다음 →  (ESC 메뉴로)");
        else
            printf("← 이전  다음 →  (ESC 메뉴로)");
        
        int key = _getch();
        if (key == 27)  // ESC
            break;
        else if (key == 224)
        {
            key = _getch();
            if (key == 75 && page > 0)      // ← 이전
                page--;
            else if (key == 77 && page < 1) // → 다음
                page++;
        }
    }
}
```

**메커니즘**
- 2개 페이지를 `page` 변수로 관리 (0: 기본 규칙, 1: 아이템)
- 각 페이지에 색상 있는 제목과 목록 출력
- ← / → 방향키로 페이지 전환
- ESC 키로 메뉴로 돌아감

**왜 수정했나?**
- 사용자가 게임을 시작하기 전에 아이템 효과를 이해할 수 있음
- 게임 중 "어? 이 아이템이 뭐지?" 하고 헷갈리지 않음
- 게임이 완전하게 느껴짐

---

### 업그레이드 1️⃣5️⃣ - 카드 모양 UI

**문제점**
```
현재: "숫자 2 3 5 7" 처럼 텍스트로만 표시
1. 어느 카드가 선택된 상태인지 모름
2. 이미 쓴 카드와 새 카드의 구분이 안 됨
3. 봉인된 카드를 표시할 수 없음
4. "게임"이 아니라 "숫자 입력 프로그램"처럼 보임
```

**이전 코드**
```c
void number_display(int i, int com_array[], int user_array[], int sum)
{
    int j;
    gotoxy(1, 2);
    printf("컴퓨터 숫자 : ");
    for(j=0;j<=i;j+=1)
        printf("%2d ", com_array[j]);  // ❌ 그냥 숫자만 나열
    // ...
}
```

**변경된 코드**
```c
void draw_card(int x, int y, int number, int state)
{
    // state: 0=선택가능, 1=이미사용, 2=봉인, 3=현재선택
    
    switch (state)
    {
    case 0:  // 선택 가능 (흰색 박스)
        set_text_color(COLOR_WHITE);
        break;
    case 1:  // 이미 사용 (회색)
        set_text_color(8);  // 어두운 회색
        break;
    case 2:  // 봉인됨 (보라색)
        set_text_color(5);  // 보라색
        break;
    case 3:  // 현재 선택 (노란 박스)
        set_text_color(COLOR_YELLOW);
        break;
    }
    
    gotoxy(x, y);
    printf("┌─────┐");
    gotoxy(x, y + 1);
    printf("│ %2d  │", number);
    gotoxy(x, y + 2);
    printf("└─────┘");
}

void display_player_hand(int turn, int player_cards[], int selected, int sealed_card)
{
    // player_cards: 플레이어가 쓸 수 있는 카드 배열
    // selected: 현재 선택된 카드 인덱스
    // sealed_card: 봉인된 카드 번호 (-1이면 없음)
    
    int i, x = 10;
    
    set_text_color(COLOR_BLUE);
    gotoxy(10, 15);
    printf("당신의 카드 :");
    
    for (i = 0; i < 10; i++)
    {
        int state = 0;  // 기본값: 선택 가능
        
        if (player_cards[i] == 0)
            state = 1;  // 이미 사용
        else if (player_cards[i] == sealed_card)
            state = 2;  // 봉인됨
        
        if (i == selected && player_cards[i] != 0)
            state = 3;  // 현재 선택
        
        draw_card(x, 17, i + 1, state);
        x += 8;  // 다음 카드 위치 (8칸씩 이동)
        if (x > 70)  // 한 줄에 최대 8개
        {
            x = 10;
            // 다음 줄로 (필요시)
        }
    }
}
```

**메커니즘**
- `draw_card()`: 한 개의 카드를 상자 모양으로 그림
- 상태별로 색상 변경:
  - 0 = 흰색 (선택 가능)
  - 1 = 회색 (이미 사용)
  - 2 = 보라색 (봉인됨)
  - 3 = 노란색 (현재 선택)
- `display_player_hand()`: 플레이어의 모든 카드를 한 줄로 표시
- 선택된 카드는 노란색으로 눈에 띄게 표시

**왜 수정했나?**
- 한눈에 게임 상태를 파악 가능
- 카드 게임 같은 느낌
- 사용자 경험이 훨씬 좋아짐

---

### 업그레이드 1️⃣6️⃣ - 방향키로 카드 선택

**문제점**
```
현재: scanf로 입력 받기
1. 사용자가 잘못된 숫자를 입력할 수 있음 (99, abc 등)
2. 입력 검사 코드가 복잡해짐
3. 게임처럼 느껴지지 않음 (텍스트 입력 같음)
```

**이전 코드**
```c
int user_number(int i, int user_array[])
{
    int j, number, result;
    while (1)
    {
        clear_line(7);
        gotoxy(1, 7);
        printf("사용자 숫자 입력후 Enter> ");
        result = scanf("%d", &number);  // ❌ 항상 검사 필요
        clear_input_buffer();
        
        if (result != 1)
            printf("숫자만 입력하세요.");
        else if (number < 1 || number > 10)
            printf("1~10 사이만");
        else if (is_duplicate(i, user_array, number))
            printf("중복됨");
        else
            break;
    }
    return number;
}
```

**변경된 코드**
```c
int select_card_with_arrow(int player_cards[])
{
    int selected = 0;  // 0번 카드부터 시작
    int key;
    
    while (1)
    {
        // 카드 표시 (선택된 카드는 노란색)
        display_player_hand(-1, player_cards, selected, -1);
        
        // 사용 가능한 카드만 선택
        if (player_cards[selected] == 0)  // 이미 사용됨
            selected++;
        
        key = _getch();
        
        if (key == 224)  // 방향키
        {
            key = _getch();
            if (key == 75)  // ← 왼쪽
                selected = (selected - 1 + 10) % 10;
            else if (key == 77)  // → 오른쪽
                selected = (selected + 1) % 10;
        }
        else if (key == 13)  // Enter
        {
            if (player_cards[selected] != 0)  // 사용 가능
            {
                return selected + 1;  // 1~10 반환
            }
            else
            {
                set_text_color(COLOR_YELLOW);
                gotoxy(10, 24);
                printf("이미 사용한 카드입니다!");
                Sleep(1000);
                set_text_color(COLOR_WHITE);
            }
        }
    }
}

// 게임 루프에서 호출
int user_number(int i, int user_array[])
{
    int number = select_card_with_arrow(user_array);
    user_array[i] = number;
    return number;
}
```

**메커니즘**
- `selected` 변수로 현재 선택된 카드 추적 (0~9)
- ← 누르면 `selected - 1` (앞 카드로)
- → 누르면 `selected + 1` (뒤 카드로)
- Enter 누르면 선택 완료
- 이미 사용한 카드는 건너뜀 (자동)
- 입력 오류가 불가능함 (선택만 가능)

**왜 수정했나?**
- 입력 검사 코드가 완전히 불필요해짐
- 게임처럼 느껴짐
- 사용자가 "내가 뭘 선택했는지" 한눈에 봄
- 버그 가능성 0

---

### 업그레이드 1️⃣7️⃣ - 합계 게이지 바

**문제점**
```
현재: "현재 합계 : 57" 이렇게만 표시
1. 100까지 얼마나 남았는지 한눈에 안 보임
2. 위험도를 직관적으로 느낄 수 없음
3. 수치만 보여줘서 단조로움
```

**이전 코드**
```c
gotoxy(1, 5);
printf("현재 합계 : %3d\n", sum);  // ❌ 숫자만 표시
```

**변경된 코드**
```c
void draw_gauge_bar(int x, int y, int value, int max_value)
{
    int filled = (value * 30) / max_value;  // 30칸 중 몇 칸 채울지
    int i;
    
    set_text_color(COLOR_WHITE);
    gotoxy(x, y);
    printf("합계: %3d / %3d [", value, max_value);
    
    // 30칸의 게이지 바
    for (i = 0; i < 30; i++)
    {
        if (i < filled)
        {
            // 채워진 부분의 색상
            if (value >= 90)
                set_text_color(COLOR_RED);  // 빨강 (위험)
            else if (value >= 70)
                set_text_color(COLOR_YELLOW);  // 노랑 (주의)
            else
                set_text_color(9);  // 파랑 (안전)
            
            printf("█");
        }
        else
        {
            set_text_color(8);  // 회색 (빈 부분)
            printf("░");
        }
    }
    
    set_text_color(COLOR_WHITE);
    printf("]");
}

// 게임 루프에서 호출
void number_display(...)
{
    // ...
    draw_gauge_bar(1, 5, sum, MAX_SCORE);
    // ...
}
```

**메커니즘**
- 합계를 0~100 범위에서 0~30 게이지로 변환
- 게이지 바에 "█" (채워진 부분)와 "░" (빈 부분)로 시각화
- 색상으로 위험도 표시:
  - 0~69: 파랑 (안전)
  - 70~89: 노랑 (주의)
  - 90~100: 빨강 (위험)

**왜 수정했나?**
- 게임 진행 상황을 시각적으로 직관적으로 이해
- 전략 수립이 쉬워짐 ("아, 저 정도면 위험하다")
- 게임이 동적으로 느껴짐

---

### 업그레이드 1️⃣8️⃣ - 화면 깜빡임 줄이기

**문제점**
```
현재: 매 턴마다 system("cls")로 전체 화면을 지움
1. 깜빡깜빡 거림 → 눈이 피로함
2. 카드를 ← 누르면 화면이 깜빡거림 → 산만함
```

**이전 코드**
```c
for(i=0;i<10;i+=1)
{
    system("cls");  // ❌ 매번 전체 화면 삭제
    number=computer_number(i, com_array);
    sum+=number;
    number_display(i, com_array, user_array, sum);  // 전체 화면 다시 그림
    
    number=user_number(i, user_array);  // 이 중간에 ← 누르면 화면 깜빡거림
}
```

**변경된 코드**
```c
void clear_hand_area(void)  // ✅ 손패 영역만 지우기
{
    int y;
    for (y = 15; y <= 22; y++)
    {
        gotoxy(1, y);
        printf("%80s", "");  // 한 줄만 공백으로 채우기
    }
}

void select_card_with_arrow(int player_cards[])
{
    int selected = 0;
    int key;
    int last_selected = -1;
    
    while (1)
    {
        // 선택 변경되었을 때만 다시 그림
        if (selected != last_selected)
        {
            clear_hand_area();  // ✅ 손패 영역만 지우기
            display_player_hand(-1, player_cards, selected, -1);
            last_selected = selected;
        }
        
        key = _getch();
        
        if (key == 224)
        {
            key = _getch();
            if (key == 75)
                selected = (selected - 1 + 10) % 10;
            else if (key == 77)
                selected = (selected + 1) % 10;
        }
        else if (key == 13)
        {
            if (player_cards[selected] != 0)
                return selected + 1;
        }
    }
}
```

**메커니즘**
- `clear_hand_area()`: 손패 영역(15~22줄)만 지우기
- 다른 부분(점수, 합계 등)은 그대로 유지
- 카드를 선택할 때만 손패 영역을 다시 그림
- 전체 화면 지우지 않으므로 깜빡거림 거의 없음

**왜 수정했나?**
- 시각적으로 부드러워짐
- 사용자의 시선 흐름이 자연스러움
- 게임에 집중하기 좋음

---

### 업그레이드 1️⃣9️⃣ - 합계 카운트업 애니메이션

**문제점**
```
현재: 합계가 한 번에 표시됨
1. "아, 이 숫자가 더해졌구나" 하는 느낌이 없음
2. 게임이 과정 없이 결과만 보여줌
3. 긴장감이 없음
```

**이전 코드**
```c
sum += number;
printf("현재 합계 : %3d", sum);  // ❌ 한 번에 표시
```

**변경된 코드**
```c
void add_score_animation(int *sum, int add_value)
{
    int original_sum = *sum;
    int steps = abs(add_value);  // 몇 단계로 올릴지
    int i;
    
    if (add_value > 0)  // 증가
    {
        for (i = 0; i < steps; i++)
        {
            *sum = original_sum + i + 1;
            draw_gauge_bar(1, 5, *sum, MAX_SCORE);
            
            if (sound_on)
                Beep(400, 50);  // 짧은 음
            
            Sleep(100);  // 0.1초씩 증가
        }
    }
    else if (add_value < 0)  // 감소 (아이템)
    {
        for (i = 0; i < steps; i++)
        {
            *sum = original_sum - (i + 1);
            draw_gauge_bar(1, 5, *sum, MAX_SCORE);
            
            if (sound_on)
                Beep(200, 50);  // 낮은 음
            
            Sleep(100);
        }
    }
}

// 게임 루프에서 호출
number = computer_number(i, com_array);
add_score_animation(&sum, number);  // ✅ 애니메이션
```

**메커니즘**
- 원래 합계에서 시작해서 1씩 증가 (또는 감소)
- 각 단계마다 게이지 바를 다시 그림
- 100ms 간격으로 표시 → 1초에 10점 증가
- 효과음이 함께 재생 (단계별로 다른 음)
- 사용자가 "아, 이 점수가 천천히 더해지는구나" 하고 느낌

**왜 수정했나?**
- 게임의 긴장감 상승
- 점수 변화를 명확히 인지
- 게임이 "과정이 있는 게임"으로 느껴짐

---

### 업그레이드 2️⃣0️⃣ - 컴퓨터 생각 중 연출

**문제점**
```
현재: 컴퓨터가 즉시 숫자를 선택함
1. 컴퓨터가 "생각"하는 것처럼 보이지 않음
2. 게임이 빨리 끝나서 심심함
3. 컴퓨터가 뭘 하고 있는지 모름
```

**이전 코드**
```c
number = computer_number(i, com_array);  // ❌ 즉시 반환
sum += number;
number_display(...);
```

**변경된 코드**
```c
void show_computer_thinking(void)  // ✅ 새로운 함수
{
    int i;
    set_text_color(COLOR_RED);
    gotoxy(30, 9);
    printf("컴퓨터가 생각 중");
    
    for (i = 0; i < 3; i++)
    {
        printf(".");
        Sleep(600);  // 0.6초마다 점 추가
    }
    
    // 효과음
    if (sound_on)
    {
        Beep(600, 200);
        Sleep(100);
        Beep(800, 200);
    }
}

int computer_number_with_delay(int i, int com_array[])
{
    show_computer_thinking();  // ✅ 생각 중 표시
    Sleep(1000);  // 1초 추가 대기
    
    int number;
    // AI 로직으로 숫자 선택
    if (difficulty == EASY)
        number = rand() % 10 + 1;
    else if (difficulty == NORMAL)
        // ... 이길 수 있으면 이기는 AI
    else
        // ... 최적 전략 AI
    
    // 중복 검사
    while (is_duplicate(i, com_array, number))
    {
        if (difficulty == EASY)
            number = rand() % 10 + 1;
        else
            // AI 로직
    }
    
    com_array[i] = number;
    return number;
}
```

**메커니즘**
- `show_computer_thinking()`: "컴퓨터가 생각 중" 표시 + "..." 점 애니메이션
- 점이 0.6초마다 추가되어 총 1.8초 표시
- 효과음: 600Hz → 800Hz로 상승 (생각이 끝나는 느낌)
- `Sleep(1000)`: 추가 1초 대기
- 총 3초 정도 "생각"함 → 게임이 자연스럽게 진행됨

**왜 수정했나?**
- 게임에 리듬감이 생김
- 컴퓨터가 지능형 존재처럼 느껴짐
- 사용자에게 다음 수에 대해 생각할 시간 제공

---

### 업그레이드 2️⃣1️⃣ - 게임 기록(로그) 창

**문제점**
```
현재: 지나간 일을 추적할 수 없음
1. "아, 컴퓨터가 방금 뭘 냈더라?" 하고 까먹음
2. "내가 뭘 냈지?" 한눈에 안 보임
3. 전략을 짜기 어려움
```

**이전 코드**
```c
// 로그 기능 없음
```

**변경된 코드**
```c
#define MAX_LOG 5

typedef struct {
    char message[50];
    int turn;  // 누구 턴? 0=컴퓨터, 1=사용자
    int card;  // 낸 카드
    int sum;   // 그때 합계
} GameLog;

GameLog game_log[MAX_LOG];
int log_count = 0;

void add_log(const char *message, int turn, int card, int sum)
{
    // 로그가 5개 초과이면 가장 오래된 것 삭제
    if (log_count >= MAX_LOG)
    {
        int i;
        for (i = 0; i < MAX_LOG - 1; i++)
            game_log[i] = game_log[i + 1];
        log_count = MAX_LOG - 1;
    }
    
    strcpy(game_log[log_count].message, message);
    game_log[log_count].turn = turn;
    game_log[log_count].card = card;
    game_log[log_count].sum = sum;
    log_count++;
}

void display_log(void)  // ✅ 새로운 함수
{
    int i, y = 26;
    
    set_text_color(COLOR_WHITE);
    gotoxy(1, 25);
    printf("═ 최근 기록 ═════════════════════════════════════");
    
    for (i = 0; i < log_count; i++)
    {
        if (game_log[i].turn == 0)  // 컴퓨터
            set_text_color(COLOR_RED);
        else
            set_text_color(COLOR_BLUE);
        
        gotoxy(1, y);
        printf("│ %s (카드: %2d, 합계: %3d)", 
               game_log[i].message, 
               game_log[i].card, 
               game_log[i].sum);
        y++;
    }
}

// 게임 루프에서 매 턴마다
number = computer_number(i, com_array);
sum += number;
add_log("카드 선택", 0, number, sum);  // 로그 추가
display_log();  // 화면에 표시
```

**메커니즘**
- `game_log` 배열: 최근 5개의 로그 저장
- 새 로그 추가 시 5개 초과이면 가장 오래된 것 삭제 (FIFO)
- 각 로그에는: 메시지, 턴(누구), 카드 번호, 그때 합계
- 화면 맨 아래에 최근 5개 로그 표시

**왜 수정했나?**
- 게임 흐름을 추적 가능
- 전략 수립이 쉬워짐
- 게임 진행 상황이 명확해짐

---

### 업그레이드 2️⃣2️⃣ - 효과음과 소리 ON/OFF

**문제점**
```
현재: 소리가 없음
1. 게임이 단조로움
2. 사용자가 피드백을 받지 못함
3. "이건 진짜 게임인가?" 하고 의심함

하지만:
2. 도서관이나 학교 교실에서는 소리를 켤 수 없음
```

**이전 코드**
```c
// 소리 기능 없음
```

**변경된 코드**
```c
// 전역 변수
int sound_on = 1;  // 1=ON, 0=OFF

// 효과음 함수들
void play_move_sound(void)
{
    if (sound_on)
        Beep(300, 100);  // 낮은 음
}

void play_select_sound(void)
{
    if (sound_on)
        Beep(800, 150);  // 높은 음 (선택됨)
}

void play_error_sound(void)
{
    if (sound_on)
    {
        Beep(100, 200);  // 낮고 긴 음 (오류)
        Sleep(100);
        Beep(100, 200);
    }
}

void play_item_sound(void)
{
    if (sound_on)
    {
        Beep(600, 100);  // 중간 음
        Sleep(50);
        Beep(800, 100);  // 높은 음 (상승)
    }
}

void play_win_sound(void)
{
    if (sound_on)
    {
        int i;
        for (i = 0; i < 3; i++)
        {
            Beep(800, 200);
            Sleep(100);
        }
    }
}

void play_lose_sound(void)
{
    if (sound_on)
    {
        Beep(400, 300);
        Sleep(100);
        Beep(300, 300);
    }
}

// 게임 루프에서
if (key == 224)
{
    key = _getch();
    if (key == 75)
    {
        selected--;
        play_move_sound();  // ✅ 이동음
    }
    else if (key == 77)
    {
        selected++;
        play_move_sound();
    }
}
else if (key == 13)
{
    if (player_cards[selected] != 0)
    {
        play_select_sound();  // ✅ 선택음
        return selected + 1;
    }
    else
    {
        play_error_sound();  // ✅ 오류음
    }
}

// 메인 메뉴에서 소리 ON/OFF
case MENU_SOUND:
    sound_on = !sound_on;  // 토글
    if (sound_on)
        Beep(800, 200);  // 켜짐 신호
    else
        Beep(200, 200);  // 꺼짐 신호
    break;
```

**메커니즘**
- 전역 변수 `sound_on`으로 소리 제어
- 각 상황별 효과음:
  - 이동: 낮은 음 (300Hz)
  - 선택: 높은 음 (800Hz)
  - 오류: 낮고 길게 (100Hz x2)
  - 아이템: 상승음 (600→800Hz)
  - 승리: 3번 울림 (800Hz)
  - 패배: 하강음 (400→300Hz)
- `Beep(주파수, 시간)`로 소리 재생
- 메뉴에서 ON/OFF 토글 가능

**왜 수정했나?**
- 게임이 생생하게 느껴짐
- 사용자 피드백 향상 (버튼을 눌렀을 때 "소리"로 반응)
- 필요시 소리를 끌 수 있음 (공공장소 대비)

---

## 🟣 PHASE 3: 게임 시스템 (23~26)

### 업그레이드 2️⃣3️⃣ - 난이도 3단계 AI

**문제점**
```
현재: 컴퓨터가 항상 무작위로 선택
1. "무작위네, 이건 재미없네" → 항상 이김
2. "어? 컴퓨터가 똑똑한데?" 할 때도 있고, 멍청할 때도 있음
3. 난이도 조정 불가능
```

**이전 코드**
```c
int computer_number(int i, int com_array[])
{
    int number;
    do {
        number = rand() % 10 + 1;  // ❌ 항상 무작위
    } while (is_duplicate(i, com_array, number));
    
    com_array[i] = number;
    return number;
}
```

**변경된 코드**
```c
#define DIFFICULTY_EASY     0
#define DIFFICULTY_NORMAL   1
#define DIFFICULTY_HARD     2

int difficulty = DIFFICULTY_NORMAL;

int computer_ai_easy(int i, int com_array[], int user_array[], int current_sum)
{
    // ✅ 쉬움: 무작위 선택
    int number;
    do {
        number = rand() % 10 + 1;
    } while (is_duplicate(i, com_array, number));
    return number;
}

int computer_ai_normal(int i, int com_array[], int user_array[], int current_sum)
{
    // ✅ 보통: 이길 수 있으면 이김
    int j, number;
    
    // 100을 넘을 수 있는 카드 찾기
    for (number = 10; number >= 1; number--)
    {
        if (!is_duplicate(i, com_array, number))
        {
            if (current_sum + number > MAX_SCORE)
                return number;  // 이길 수 있음 → 즉시 선택
        }
    }
    
    // 이길 수 없으면 가장 큰 수 선택 (더 빨리 이기기 위해)
    for (number = 10; number >= 1; number--)
    {
        if (!is_duplicate(i, com_array, number))
            return number;
    }
    
    return 1;  // 혹시 모르니 (사실 여기는 도달 불가)
}

int computer_ai_hard(int i, int com_array[], int user_array[], int current_sum)
{
    // ✅ 어려움: 미니맥스 알고리즘 (간단 버전)
    int j, k, number, best_number = 1, best_score = -1;
    
    // 각 수에 대해 "점수"를 계산
    for (number = 10; number >= 1; number--)
    {
        if (is_duplicate(i, com_array, number))
            continue;
        
        int new_sum = current_sum + number;
        int score = 0;
        
        if (new_sum > MAX_SCORE)
            score = 1000;  // 이기는 수 → 최고 점수
        else
        {
            // "사용자가 이길 가능성"을 역으로 계산
            // 사용자가 100을 넘을 수 있는 가장 작은 수
            int user_min_to_win = MAX_SCORE - new_sum + 1;
            
            int available_count = 0;
            for (j = user_min_to_win; j <= 10; j++)
            {
                if (!is_duplicate(i, user_array, j))
                    available_count++;
            }
            
            // available_count가 작을수록 "사용자가 이기기 어려움" → 좋은 수
            score = 100 - available_count * 10;
            
            // 더 가까이 가는 것도 중요
            score += (new_sum - current_sum);
        }
        
        if (score > best_score)
        {
            best_score = score;
            best_number = number;
        }
    }
    
    return best_number;
}

int computer_number(int i, int com_array[], int user_array[], int current_sum)
{
    int number;
    
    if (difficulty == DIFFICULTY_EASY)
        number = computer_ai_easy(i, com_array, user_array, current_sum);
    else if (difficulty == DIFFICULTY_NORMAL)
        number = computer_ai_normal(i, com_array, user_array, current_sum);
    else
        number = computer_ai_hard(i, com_array, user_array, current_sum);
    
    com_array[i] = number;
    return number;
}
```

**메커니즘**

**쉬움 (EASY)**:
- 무작위 선택 (원래대로)

**보통 (NORMAL)**:
- 100을 넘을 수 있는 수가 있으면 즉시 선택
- 없으면 가장 큰 수 선택 (더 빨리 이기기 위해)

**어려움 (HARD)**:
- 각 수에 대해 "점수" 계산
  - 1000점: 이기는 수
  - 나머지: (사용자가 이기기 어려운 정도) + (합계 증가도)
- 가장 점수 높은 수 선택

**왜 수정했나?**
- 게임을 반복 플레이할 때 난이도 조정 가능
- 초보자는 쉬움, 고수는 어려움으로 도전
- AI가 "똑똑해 보임" → 게임이 더 재미있음

---

### 업그레이드 2️⃣4️⃣ - 동전 던지기로 선공 정하기

**문제점**
```
현재: 항상 컴퓨터가 먼저 함
1. "왜 항상 컴퓨터가 먼저야?" → 불공평해 보임
2. 사용자가 "선택의 자유"를 못 느낌
3. 게임이 정해진 대로만 진행되는 느낌
```

**이전 코드**
```c
void game_control(void)
{
    // ...
    for(i=0;i<10;i+=1)
    {
        number=computer_number(i, com_array);  // ❌ 항상 컴퓨터 먼저
        // ...
    }
}
```

**변경된 코드**
```c
void coin_toss(void)  // ✅ 새로운 함수
{
    int coin, user_choice, result;
    
    system("cls");
    set_text_color(COLOR_YELLOW);
    gotoxy(20, 10);
    printf("동전 던지기 (선공 정하기)");
    
    set_text_color(COLOR_WHITE);
    gotoxy(15, 14);
    printf("동전의 앞뒷면을 선택하세요.");
    gotoxy(20, 16);
    printf("(1) 앞면  (2) 뒷면");
    
    gotoxy(20, 20);
    printf("선택 > ");
    
    scanf("%d", &user_choice);
    clear_input_buffer();
    
    // 동전 던지기
    coin = rand() % 2;  // 0 또는 1
    
    gotoxy(15, 24);
    if (coin == 0)
    {
        set_text_color(COLOR_YELLOW);
        printf("▼ 앞면이 나왔습니다!");
    }
    else
    {
        set_text_color(COLOR_YELLOW);
        printf("▼ 뒷면이 나왔습니다!");
    }
    
    if ((user_choice == 1 && coin == 0) || (user_choice == 2 && coin == 1))
    {
        gotoxy(15, 26);
        set_text_color(COLOR_BLUE);
        printf("당신이 먼저 시작합니다!");
        return 1;  // 사용자가 먼저
    }
    else
    {
        gotoxy(15, 26);
        set_text_color(COLOR_RED);
        printf("컴퓨터가 먼저 시작합니다!");
        return 0;  // 컴퓨터가 먼저
    }
}

void game_control(void)
{
    int com_array[MAX_TURN] = {0}, user_array[MAX_TURN] = {0};
    int i, number, sum = 0;
    int win = 0;
    int user_first = coin_toss();  // ✅ 선공 정하기

    for (i = 0; i < MAX_TURN; i++)
    {
        system("cls");
        
        if (user_first)
        {
            // 사용자가 먼저
            number = user_number(i, user_array);
            sum += number;
            number_display(i, com_array, user_array, sum);
            if (sum > MAX_SCORE) { win = 2; break; }

            number = computer_number(i, com_array, user_array, sum);
            sum += number;
            number_display(i, com_array, user_array, sum);
            if (sum > MAX_SCORE) { win = 1; break; }
        }
        else
        {
            // 컴퓨터가 먼저 (원래 방식)
            number = computer_number(i, com_array, user_array, sum);
            sum += number;
            number_display(i, com_array, user_array, sum);
            if (sum > MAX_SCORE) { win = 1; break; }

            number = user_number(i, user_array);
            sum += number;
            number_display(i, com_array, user_array, sum);
            if (sum > MAX_SCORE) { win = 2; break; }
        }
        
        press_any_key();
    }
    conclusion(win);
    press_any_key();
}
```

**메커니즘**
- 사용자가 "앞"과 "뒷"을 선택
- 난수(0 또는 1)로 동전 던지기
- 선택이 맞으면 사용자가 먼저, 틀리면 컴퓨터가 먼저
- 반환된 값에 따라 게임 루프를 다르게 구성

**왜 수정했나?**
- 공정성 향상
- 사용자가 "내가 선택했다"는 느낌
- 게임의 변수성 증가 → 반복 플레이 유도

---

### 업그레이드 2️⃣5️⃣ - 제한 시간 20초

**문제점**
```
현재: 시간 제한이 없음
1. 사용자가 "차라리 계산기로 최적 수를 찾자" → 게임이 변함
2. 게임의 속도감이 없음
```

**이전 코드**
```c
int user_number(int i, int user_array[])
{
    // ... 무한정 대기
    scanf("%d", &number);
}
```

**변경된 코드**
```c
#include <sys/types.h>
#include <time.h>

int select_card_with_timeout(int player_cards[])
{
    int selected = 0;
    int key;
    time_t start_time = time(NULL);
    int time_limit = 20;  // 20초
    
    while (1)
    {
        int elapsed = (int)(time(NULL) - start_time);
        int remaining = time_limit - elapsed;
        
        // 시간 표시
        gotoxy(60, 7);
        if (remaining <= 0)
        {
            set_text_color(COLOR_RED);
            printf("시간 초과!");
            Sleep(500);
            return rand() % 10 + 1;  // 무작위 선택
        }
        else if (remaining <= 5)
        {
            set_text_color(COLOR_RED);
            printf("⏱ %d초 남음", remaining);
            // 경고음
            if (remaining % 2 == 0 && sound_on)
                Beep(200, 100);
        }
        else
        {
            set_text_color(COLOR_YELLOW);
            printf("⏱ %d초 남음", remaining);
        }
        
        // 카드 선택 (논블로킹)
        if (_kbhit())  // 키가 눌렸는지 확인 (기다리지 않음)
        {
            key = _getch();
            
            if (key == 224)
            {
                key = _getch();
                if (key == 75)
                    selected--;
                else if (key == 77)
                    selected++;
            }
            else if (key == 13)  // Enter
            {
                if (player_cards[selected] != 0)
                    return selected + 1;
            }
        }
        
        Sleep(100);  // 100ms마다 확인
    }
}
```

**메커니즘**
- `time()` 함수로 경과 시간 추적
- 남은 시간을 화면에 표시
- 5초 이하 시 빨간색 + 경고음
- `_kbhit()`: 키 입력 여부를 확인 (기다리지 않음)
- 시간 초과 시 무작위로 카드 선택
- 100ms마다 갱신 (끊기지 않는 듯한 느낌)

**왜 수정했나?**
- 게임에 긴장감 추가
- 사용자가 빠르게 판단해야 함
- 게임 속도감 향상

---

### 업그레이드 2️⃣6️⃣ - 숫자 카드 리필 규칙

**문제점**
```
현재: 각 플레이어가 1~10을 한 번씩만 사용
1. 10턴을 다 돌면 어느 쪽도 100을 못 넘을 수 있음
   - 컴퓨터: 1~10 합 = 55
   - 사용자: 1~10 합 = 55
   - 총 110이므로 항상 누군가는 100을 넘음
   - 사실 100% 결정적임 (운의 요소가 없음)

2. 또는 게임이 "카드가 떨어져서" 무승부 상태가 될 수 있음
```

**이전 코드**
```c
int computer_number(int i, int com_array[])
{
    int number;
    do {
        number = rand() % 10 + 1;
    } while (is_duplicate(i, com_array, number));  // ❌ 항상 중복 확인만
    // ...
}
```

**변경된 코드**
```c
int get_available_cards(int used_count, int used_array[], int available[])
{
    // ✅ 사용 가능한 카드 목록 반환
    int i, count = 0;
    
    // 1~10 카드 중에서
    for (i = 1; i <= 10; i++)
    {
        // 이미 사용했는지 확인
        if (used_count > 0 && used_array[used_count - 1] == i)
            continue;  // 사용 중인 카드 제외
        
        available[count++] = i;
    }
    
    return count;  // 사용 가능한 카드 개수
}

int computer_number(int i, int com_array[], int user_array[], int current_sum)
{
    int available[10], count, idx, number;
    
    // 사용 가능한 카드 목록 얻기
    count = get_available_cards(i, com_array, available);
    
    if (count == 0)
    {
        // ✅ 카드가 떨어지면 다시 채우기 (리필)
        for (idx = 0; idx < 10; idx++)
            com_array[idx] = 0;  // 초기화
        
        for (idx = 0; idx < 10; idx++)
            available[idx] = idx + 1;
        
        count = 10;
    }
    
    // AI에 따라 선택
    if (difficulty == DIFFICULTY_EASY)
    {
        idx = rand() % count;
        number = available[idx];
    }
    else if (difficulty == DIFFICULTY_NORMAL)
    {
        // 100을 넘을 수 있으면 그 수 선택
        for (idx = count - 1; idx >= 0; idx--)
        {
            number = available[idx];
            if (current_sum + number > MAX_SCORE)
                break;
        }
    }
    else  // HARD
    {
        // 미니맥스 (생략)
    }
    
    // 카드 기록
    if (i < 10)
        com_array[i] = number;
    else  // 리필 후
        com_array[i % 10] = number;
    
    return number;
}
```

**메커니즘**
- `get_available_cards()`: 아직 사용하지 않은 카드 목록 반환
- 카드가 없으면 (count == 0) 리필 (배열 초기화)
- 그 후 계속 게임 진행
- 이제 게임이 무한정 계속될 수 있음

**왜 수정했나?**
- 게임이 항상 결론에 도달
- 카드 부족 상황 처리
- 게임 규칙이 더 명확함 (반복 가능)

---

## 🟢 PHASE 4: 아이템 카드 배틀 (27~33)

### 업그레이드 2️⃣7️⃣ - 아이템 시스템 도입

**문제점**
```
현재: 숫자 카드만 있음
1. 전략의 깊이가 얕음 (큰 수 내면 이김)
2. "아이템이 있었으면"하는 아쉬움
3. 역전이 불가능 (100에 가까우면 무조건 패배)
```

**코드: 아이템 데이터 구조**
```c
#define ITEM_NONE    -1
#define ITEM_DOUBLE  0   // x2
#define ITEM_MINUS10 1   // -10
#define ITEM_SKIP    2   // 턴 스킵
#define ITEM_SEAL    3   // 봉인

#define MAX_ITEMS    3   // 슬롯 3칸

typedef struct {
    int item[MAX_ITEMS];  // 아이템 종류
    int count;             // 보유 개수
} ItemDeck;

ItemDeck player_items, computer_items;

void init_items(void)  // ✅ 새로운 함수
{
    // 게임 시작 시 각 플레이어에게 아이템 2개 지급
    player_items.item[0] = ITEM_DOUBLE;
    player_items.item[1] = ITEM_MINUS10;
    player_items.item[2] = ITEM_NONE;
    player_items.count = 2;
    
    computer_items.item[0] = ITEM_DOUBLE;
    computer_items.item[1] = ITEM_MINUS10;
    computer_items.item[2] = ITEM_NONE;
    computer_items.count = 2;
}

int use_item(int player, int item_slot)
{
    // player: 0=컴퓨터, 1=사용자
    ItemDeck *items = (player == 0) ? &computer_items : &player_items;
    
    if (item_slot < 0 || item_slot >= MAX_ITEMS)
        return -1;  // 잘못된 인덱스
    
    if (items->item[item_slot] == ITEM_NONE)
        return -1;  // 빈 슬롯
    
    int item_type = items->item[item_slot];
    
    // 아이템 사용 처리 (업26~29에서)
    
    // 슬롯에서 제거
    items->item[item_slot] = ITEM_NONE;
    items->count--;
    
    return item_type;
}

void add_item(int player, int item_type)
{
    // player: 0=컴퓨터, 1=사용자
    ItemDeck *items = (player == 0) ? &computer_items : &player_items;
    
    int i;
    for (i = 0; i < MAX_ITEMS; i++)
    {
        if (items->item[i] == ITEM_NONE)
        {
            items->item[i] = item_type;
            items->count++;
            return;
        }
    }
}

void display_items(int player, int x, int y)
{
    // 아이템 표시
    ItemDeck *items = (player == 0) ? &computer_items : &player_items;
    int i;
    
    if (player == 0)
        set_text_color(COLOR_RED);
    else
        set_text_color(COLOR_BLUE);
    
    gotoxy(x, y);
    if (player == 0)
        printf("컴퓨터 아이템:");
    else
        printf("당신의 아이템:");
    
    for (i = 0; i < MAX_ITEMS; i++)
    {
        gotoxy(x + 15 + i * 10, y);
        
        if (items->item[i] == ITEM_NONE)
            printf("[  비움  ]");
        else if (items->item[i] == ITEM_DOUBLE)
            printf("[ ×2    ]");
        else if (items->item[i] == ITEM_MINUS10)
            printf("[ -10   ]");
        else if (items->item[i] == ITEM_SKIP)
            printf("[ SKIP  ]");
        else if (items->item[i] == ITEM_SEAL)
            printf("[ 봉인  ]");
    }
}
```

**메커니즘**
- `ItemDeck` 구조체: 각 플레이어의 아이템 슬롯 3칸 관리
- `init_items()`: 게임 시작 시 각각 x2, -10 아이템 지급
- `use_item()`: 특정 슬롯의 아이템 사용 (슬롯에서 제거)
- `add_item()`: 새 아이템 추가 (빈 슬롯에 저장)
- `display_items()`: 아이템 상태 표시

**왜 수정했나?**
- 게임에 전략 요소 추가
- 역전 가능성 생김 (아이템으로 상황 반전)
- 게임의 깊이 증가

---

### 업그레이드 2️⃣8️⃣ - 더블 x2

**문제점**
```
이전: 아이템은 있지만 효과가 없음
```

**코드**
```c
int apply_double_item(int *card_value)
{
    // ✅ 새로운 함수
    *card_value *= 2;  // 카드 값 2배
    return 1;  // 성공
}

// 게임 루프에서
int card_value = select_card_with_arrow(player_cards);
int use_item = ask_use_item(player);  // 아이템 사용 여부

if (use_item == ITEM_DOUBLE)
{
    apply_double_item(&card_value);
    add_log("더블 사용", player, card_value, sum);
    play_item_sound();  // 아이템 효과음
}

sum += card_value;
add_score_animation(&sum, card_value);
```

**메커니즘**
- `apply_double_item()`: 카드 값을 2배로 변경
- 예: 카드 5 → 10점으로 계산
- 로그에 "더블 사용" 기록

**왜 수정했나?**
- 역전의 기회 제공
- 전략: "지금 사용할까? 나중에 사용할까?"

---

### 업그레이드 2️⃣9️⃣ - 합계 -10 아이템

**코드**
```c
int apply_minus10_item(int *sum)
{
    // ✅ 새로운 함수
    *sum -= 10;
    if (*sum < 0)
        *sum = 0;  // 음수 방지
    return 1;
}

// 게임 루프에서
if (use_item == ITEM_MINUS10)
{
    apply_minus10_item(&sum);
    add_log("방어! 합계 -10", player, 0, sum);
    play_item_sound();
}
```

**메커니즘**
- 합계를 10 줄임
- 상대가 100에 가까워졌을 때 사용 → 방어 기능
- 점수를 음수로 만들지 않도록 처리

**왜 수정했나?**
- 방어 전략 추가
- "위기 탈출" 느낌

---

### 업그레이드 3️⃣0️⃣ - 턴 스킵 아이템

**코드**
```c
int apply_skip_item(void)
{
    // ✅ 새로운 함수
    return 1;  // 다음 턴 건너뛰기 신호
}

// 게임 루프에서
if (use_item == ITEM_SKIP)
{
    int skip_opponent = apply_skip_item();
    add_log("스킵! 상대 턴 건너뜀", player, 0, sum);
    play_item_sound();
    
    // 다음 루프에서 상대 턴을 건너뜀
    // (방법: 루프 제어 변수 수정)
}
```

**메커니즘**
- 상대 턴을 건너뜀
- 자신이 연속으로 2턴을 함

**왜 수정했나?**
- 공격적 전략 제공

---

### 업그레이드 3️⃣1️⃣ - 봉인 아이템

**코드**
```c
int apply_seal_item(int target_player)
{
    // ✅ 새로운 함수
    // 상대 플레이어의 가장 큰 카드를 찾음
    int sealed_card = -1;
    int i, max_card = 0;
    
    int *target_cards = (target_player == 0) ? 
        get_computer_available_cards() : 
        get_user_available_cards();
    
    for (i = 0; i < 10; i++)
    {
        if (target_cards[i] > max_card)
            max_card = target_cards[i];
    }
    
    return max_card;  // 봉인된 카드 번호
}

// 전역 변수
int sealed_card_computer = -1;
int sealed_card_user = -1;
int seal_remaining_turns = 0;  // 봉인 남은 턴 수

// 게임 루프에서
if (use_item == ITEM_SEAL)
{
    if (player == 0)  // 컴퓨터가 사용
        sealed_card_user = apply_seal_item(1);
    else  // 사용자가 사용
        sealed_card_computer = apply_seal_item(0);
    
    seal_remaining_turns = 1;  // 1턴 동안 봉인
    add_log("봉인! 상대 카드 봉인됨", player, sealed_card, sum);
    play_item_sound();
}

// 턴이 끝날 때마다
if (seal_remaining_turns > 0)
{
    seal_remaining_turns--;
    if (seal_remaining_turns == 0)
    {
        sealed_card_computer = -1;
        sealed_card_user = -1;
    }
}

// 카드 선택 시 봉인 확인
int card = select_card_with_arrow(player_cards);
if ((player == 0 && card == sealed_card_computer) ||
    (player == 1 && card == sealed_card_user))
{
    printf("이 카드는 봉인되었습니다!");
    return -1;  // 다시 선택
}
```

**메커니즘**
- 상대 플레이어의 가장 큰 카드를 찾음
- 그 카드를 1턴 동안 못 쓰게 함
- 봉인된 카드는 보라색으로 표시 (업15에서)

**왜 수정했나?**
- 상대의 최적 수를 막을 수 있음
- 전술적 깊이 증가

---

### 업그레이드 3️⃣2️⃣ - 보너스 아이템 지급

**코드**
```c
void grant_bonus_items(int turn)
{
    // ✅ 새로운 함수
    // 4턴마다 각 플레이어에게 아이템 지급
    
    if (turn > 0 && turn % 4 == 0)
    {
        // 아이템 타입을 무작위로 선택
        int item_type = rand() % 4;  // 0~3
        
        add_item(0, item_type);  // 컴퓨터
        add_item(1, item_type);  // 사용자
        
        if (sound_on)
            play_item_sound();
        
        gotoxy(20, 12);
        set_text_color(COLOR_YELLOW);
        printf("★ 보너스 아이템을 받았습니다!");
        Sleep(1500);
    }
}

// 게임 루프에서 매 턴마다
for (i = 0; i < MAX_TURN; i++)
{
    // ...
    grant_bonus_items(i);  // ✅ 아이템 지급 확인
}
```

**메커니즘**
- `turn % 4 == 0`: 4의 배수인 턴마다 실행
- 각 플레이어에게 같은 아이템 지급 (공정)
- 아이템 타입을 무작위로 선택

**왜 수정했나?**
- 게임이 진행될수록 아이템 충전
- 반전의 기회 증가 (중후반부가 흥미로움)
- 게임 시간 조정 (너무 빨리 끝나지 않음)

---

### 업그레이드 3️⃣3️⃣ - AI 아이템 전략

**코드**
```c
int computer_choose_item(int computer_sum, int user_sum)
{
    // ✅ 새로운 함수
    // 컴퓨터 AI가 아이템 사용 여부 결정
    
    int can_win = computer_sum > MAX_SCORE - 10;  // 10점만 내면 이김
    int opponent_dangerous = user_sum > MAX_SCORE - 15;  // 상대가 위험
    
    if (difficulty == DIFFICULTY_EASY)
        return -1;  // 아이템 안 씀
    
    else if (difficulty == DIFFICULTY_NORMAL)
    {
        // 이길 수 있으면 "더블" 사용
        if (can_win && computer_items.count > 0)
            return use_item(0, find_item_slot(0, ITEM_DOUBLE));
        
        return -1;  // 아니면 안 씀
    }
    
    else  // HARD
    {
        // 우선순위:
        // 1. 이길 수 있으면 "더블" 사용
        if (can_win && computer_items.count > 0)
            return use_item(0, find_item_slot(0, ITEM_DOUBLE));
        
        // 2. 상대가 위험하면 방어
        if (opponent_dangerous && computer_items.count > 0)
        {
            // 봉인 → -10 → 스킵 순으로 시도
            if (find_item_slot(0, ITEM_SEAL) >= 0)
                return use_item(0, find_item_slot(0, ITEM_SEAL));
            
            if (find_item_slot(0, ITEM_MINUS10) >= 0)
                return use_item(0, find_item_slot(0, ITEM_MINUS10));
            
            if (find_item_slot(0, ITEM_SKIP) >= 0)
                return use_item(0, find_item_slot(0, ITEM_SKIP));
        }
        
        return -1;
    }
}

int find_item_slot(int player, int item_type)
{
    // ✅ 헬퍼 함수
    ItemDeck *items = (player == 0) ? &computer_items : &player_items;
    int i;
    
    for (i = 0; i < MAX_ITEMS; i++)
    {
        if (items->item[i] == item_type)
            return i;
    }
    
    return -1;  // 해당 아이템 없음
}

// 게임 루프에서
if (player_turn == 0)  // 컴퓨터 턴
{
    int item = computer_choose_item(computer_sum, user_sum);
    if (item >= 0)
    {
        apply_item(0, item);  // 아이템 효과 적용
    }
}
```

**메커니즘**

**쉬움**: 아이템 안 씀 (공정함)

**보통**:
- 이길 수 있으면 더블 사용

**어려움**:
- 이길 수 있으면 더블 (공격)
- 상대가 위험하면 봉인 → -10 → 스킵 순으로 방어

**왜 수정했나?**
- 컴퓨터가 "지능형"으로 보임
- 게임이 거대해짐 (단순한 수 선택 → 전략적 게임)

---

## ⚫ PHASE 5: 저장/불러오기 (34~38)

### 업그레이드 3️⃣4️⃣ - 게임 저장

**문제점**
```
현재: 게임 중 일시정지할 수 없음
1. 갑자기 나가야 할 때 진행 상황이 날라감
2. 완주 불가능
```

**코드**
```c
#include <stdio.h>

typedef struct {
    int com_array[MAX_TURN];
    int user_array[MAX_TURN];
    int computer_sum;
    int user_sum;
    int turn;
    int difficulty;
    ItemDeck computer_items;
    ItemDeck player_items;
    int sealed_card_computer;
    int sealed_card_user;
    int seal_remaining_turns;
    int user_first;
} GameSaveData;

void save_game(GameSaveData *save_data)
{
    // ✅ 새로운 함수
    FILE *fp = fopen("save.dat", "wb");
    
    if (fp == NULL)
    {
        printf("저장 실패!");
        return;
    }
    
    fwrite(save_data, sizeof(GameSaveData), 1, fp);
    fclose(fp);
    
    set_text_color(COLOR_YELLOW);
    gotoxy(20, 12);
    printf("게임이 저장되었습니다!");
    Sleep(1500);
}

int ask_save_game(void)
{
    // ✅ 사용자 턴 중에 'S' 누르면 저장 여부 묻기
    set_text_color(COLOR_WHITE);
    gotoxy(20, 13);
    printf("저장하시겠습니까? (Y/N)");
    
    int key = _getch();
    if (key == 'Y' || key == 'y')
        return 1;
    else
        return 0;
}

// 게임 루프에서
while (1)
{
    // ...
    if (player_turn == 1)  // 사용자 턴
    {
        // 키 입력 대기
        key = _getch();
        
        if (key == 's' || key == 'S')
        {
            if (ask_save_game())
            {
                GameSaveData save_data;
                // ... save_data 구조체 채우기
                save_game(&save_data);
                return;  // 게임 루프 종료 → 메뉴로
            }
        }
    }
}
```

**메커니즘**
- `GameSaveData` 구조체: 게임 상태를 모두 저장
- `fopen("save.dat", "wb")`: 이진 파일로 열기 (쓰기 모드)
- `fwrite()`: 구조체를 파일에 씀
- `fclose()`: 파일 닫기
- 사용자 턴에 'S' 누르면 저장

**왜 수정했나?**
- 게임 도중 나가도 진행상황 유지
- 게임을 "프로그램" 수준으로 격상

---

### 업그레이드 3️⃣5️⃣ - 이어하기(불러오기)

**코드**
```c
int load_game(GameSaveData *save_data)
{
    // ✅ 새로운 함수
    FILE *fp = fopen("save.dat", "rb");
    
    if (fp == NULL)
    {
        set_text_color(COLOR_RED);
        gotoxy(20, 12);
        printf("저장된 게임이 없습니다!");
        Sleep(1500);
        return 0;  // 실패
    }
    
    // 파일이 맞는 크기인지 확인 (손상 확인)
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
    if (file_size != sizeof(GameSaveData))
    {
        set_text_color(COLOR_RED);
        gotoxy(20, 12);
        printf("저장 파일이 손상되었습니다!");
        fclose(fp);
        return 0;  // 실패
    }
    
    // 읽기
    fread(save_data, sizeof(GameSaveData), 1, fp);
    fclose(fp);
    
    set_text_color(COLOR_GREEN);
    gotoxy(20, 12);
    printf("게임을 불러왔습니다!");
    Sleep(1500);
    return 1;  // 성공
}

// 메인 메뉴에서
case MENU_LOAD:
    {
        GameSaveData save_data;
        if (load_game(&save_data))
        {
            // 저장된 상태로 게임 재개
            restore_and_play(&save_data);  // (업35-1)
        }
        break;
    }
```

**메커니즘**
- `fopen("save.dat", "rb")`: 파일 읽기 (이진)
- 파일이 없으면 "저장된 게임이 없습니다" 표시
- 파일 크기 검사 (손상 확인)
- `fread()`: 파일에서 구조체 읽기
- 읽기 성공 시 `restore_and_play()`로 게임 재개

**왜 수정했나?**
- 저장한 게임을 계속할 수 있음
- 파일 검증으로 손상 방지

---

### 업그레이드 3️⃣6️⃣ - 전적 기록 저장과 보기

**코드**
```c
typedef struct {
    int win;
    int lose;
    int draw;
} GameRecord;

GameRecord record = {0, 0, 0};

void save_record(void)
{
    // ✅ 새로운 함수
    FILE *fp = fopen("record.txt", "a");  // 추가 모드
    
    if (fp == NULL)
        return;
    
    // 타임스탬프와 함께 기록
    time_t now = time(NULL);
    struct tm *timeinfo = localtime(&now);
    
    fprintf(fp, "[%04d-%02d-%02d %02d:%02d:%02d] ",
            timeinfo->tm_year + 1900,
            timeinfo->tm_mon + 1,
            timeinfo->tm_mday,
            timeinfo->tm_hour,
            timeinfo->tm_min,
            timeinfo->tm_sec);
    
    if (last_result == 1)  // 승리
        fprintf(fp, "WIN  (난이도: %s)\n", 
               difficulty == 0 ? "쉬움" :
               difficulty == 1 ? "보통" : "어려움");
    else if (last_result == 2)
        fprintf(fp, "LOSE (난이도: %s)\n", ...);
    else
        fprintf(fp, "DRAW (난이도: %s)\n", ...);
    
    fclose(fp);
}

void load_record(void)
{
    // ✅ 새로운 함수
    FILE *fp = fopen("record.txt", "r");
    
    if (fp == NULL)
    {
        record.win = 0;
        record.lose = 0;
        record.draw = 0;
        return;
    }
    
    char line[100];
    while (fgets(line, sizeof(line), fp))
    {
        if (strstr(line, "WIN"))
            record.win++;
        else if (strstr(line, "LOSE"))
            record.lose++;
        else if (strstr(line, "DRAW"))
            record.draw++;
    }
    
    fclose(fp);
}

void show_record(void)
{
    // ✅ 새로운 함수
    system("cls");
    
    set_text_color(COLOR_YELLOW);
    gotoxy(20, 5);
    printf("▶ 전적");
    
    set_text_color(COLOR_WHITE);
    load_record();  // 최신 기록 로드
    
    int total = record.win + record.lose + record.draw;
    float win_rate = (total > 0) ? (record.win * 100.0 / total) : 0;
    
    gotoxy(15, 10);
    printf("총 게임 수 : %d", total);
    gotoxy(15, 12);
    printf("승리 : %d", record.win);
    gotoxy(15, 14);
    printf("패배 : %d", record.lose);
    gotoxy(15, 16);
    printf("무승부 : %d", record.draw);
    
    set_text_color(COLOR_YELLOW);
    gotoxy(15, 18);
    printf("승률 : %.1f%%", win_rate);
    
    set_text_color(COLOR_WHITE);
    gotoxy(15, 24);
    printf("ESC를 누르면 메뉴로 돌아갑니다.");
    
    while (_getch() != 27);  // ESC
}

// 게임 끝날 때마다
conclusion(win);
save_record();  // 기록 저장
```

**메커니즘**
- `record.txt` 텍스트 파일에 기록 추가
- 각 줄에 타임스탐프, 결과, 난이도 기록
- `load_record()`: 파일을 읽으면서 승/패/무 카운트
- 승률 계산: (승리 수 / 전체) × 100

**왜 수정했나?**
- 플레이 기록 남김
- 사용자가 자신의 진전 확인 가능
- 게임에 지속성 부여 (계속 하고 싶어짐)

---

### 업그레이드 3️⃣7️⃣ - 엔딩 화면

**문제점**
```
현재: 결과만 텍스트로 표시
1. "이겼다!"는 느낌이 약함
2. 큰 감정 표현 없음
```

**코드**
```c
void show_ending_screen(int win)
{
    // ✅ 새로운 함수
    system("cls");
    
    if (win == 1)  // 컴퓨터가 이김
    {
        set_text_color(COLOR_RED);
        gotoxy(10, 5);
        printf("▄ ▄ ▄ ▄ ▄ ▄ ▄ ▄ ▄ ▄ ▄");
        gotoxy(20, 8);
        printf("YOU LOSE");
        gotoxy(10, 12);
        printf("▄ ▄ ▄ ▄ ▄ ▄ ▄ ▄ ▄ ▄ ▄");
        
        // 패배 음악
        if (sound_on)
            play_lose_sound();
    }
    else if (win == 2)  // 사용자가 이김
    {
        set_text_color(COLOR_BLUE);
        gotoxy(10, 5);
        printf("█ █ █ █ █ █ █ █ █ █ █");
        gotoxy(20, 8);
        printf("YOU WIN!!!");
        gotoxy(10, 12);
        printf("█ █ █ █ █ █ █ █ █ █ █");
        
        // 승리 음악
        if (sound_on)
            play_win_sound();
    }
    else  // 무승부
    {
        set_text_color(COLOR_YELLOW);
        gotoxy(20, 8);
        printf("DRAW (무승부)");
        
        if (sound_on)
            Beep(600, 300);
    }
    
    // 통계 표시
    set_text_color(COLOR_WHITE);
    gotoxy(15, 16);
    printf("최종 합계: %d", final_sum);
    
    gotoxy(15, 18);
    printf("컴퓨터 카드: ");
    display_all_cards(0);
    
    gotoxy(15, 20);
    printf("당신의 카드: ");
    display_all_cards(1);
    
    // 계속 진행
    gotoxy(15, 26);
    printf("아무키나 누르면 메뉴로...");
    _getch();
}
```

**메커니즘**
- 승패에 따라 큰 글자로 "YOU WIN" 또는 "YOU LOSE" 표시
- 색상으로 감정 표현 (승리=파랑, 패배=빨강)
- 최종 통계 표시
- 멜로디 재생

**왜 수정했나?**
- 게임의 카타르시스 (게임 끝에 만족감)
- "정말 게임했다" 느낌

---

### 업그레이드 3️⃣8️⃣ - 일시정지와 다시 하기

**코드**
```c
int paused = 0;
time_t pause_time = 0;
time_t accumulated_pause = 0;

void pause_game(void)
{
    // ✅ 새로운 함수
    system("cls");
    
    set_text_color(COLOR_YELLOW);
    gotoxy(20, 10);
    printf("▶ 일시정지됨");
    
    set_text_color(COLOR_WHITE);
    gotoxy(15, 14);
    printf("C: 계속하기  M: 메뉴로  Q: 종료");
    
    while (1)
    {
        int key = _getch();
        
        if (key == 'c' || key == 'C')
        {
            paused = 0;
            return;  // 게임 재개
        }
        else if (key == 'm' || key == 'M')
        {
            paused = 0;
            exit(0);  // 메뉴로 (큰 분기 처리 필요)
        }
        else if (key == 'q' || key == 'Q')
        {
            exit(0);
        }
    }
}

// 게임 루프에서
while (1)
{
    key = _getch();
    
    if (key == 27)  // ESC
    {
        pause_game();
        if (paused)
            pause_time = time(NULL);  // 일시정지 시간 기록
    }
    else
    {
        // 다른 키 처리
    }
    
    // 제한 시간 조정
    if (paused)
    {
        accumulated_pause += (time(NULL) - pause_time);
    }
}

// 게임이 끝나면
show_ending_screen(win);

// 메뉴로 돌아가기
int play_again = ask_play_again();
if (play_again)
{
    show_menu();  // 메인 메뉴로
}
```

**메커니즘**
- ESC 누르면 일시정지 화면
- C/M/Q로 "계속 / 메뉴 / 종료" 선택
- 일시정지 시간을 기록하여 제한 시간 조정
- 게임이 끝나면 다시 하기 여부 묻기

**왜 수정했나?**
- 게임을 "정지"할 수 있음
- 완전한 게임 프로그램 (시작~종료까지 모든 기능)

---

## 🎉 모든 업그레이드 완료!

38개 업그레이드를 거쳐:
- 🐞 **버그 수정** (1~8)
- 🎨 **UI/UX 개선** (9~22)
- ⚙️ **게임 시스템** (23~26)
- 🃏 **아이템 시스템** (27~33)
- 💾 **저장/불러오기** (34~38)


## 🔴 PHASE 1: 버그 수정 (1~8)

| # | 슬라이드 제목 | PPT 한 줄 요약 | 시각화 팁 |
|---|---|---|---|
| 1 | 입력 범위 검사 | 999나 -50 같은 범위 외 숫자를 입력해도 받아들이던 문제를 범위 검사로 해결 | 이전: 게임이 한 번에 끝남 / 이후: 검사 후 입력됨 |
| 2 | 문자 입력 무한 루프 해결 | abc를 입력하면 입력 버퍼에 남아 무한 루프가 발생하던 문제를 `clear_input_buffer()`로 해결 | 이전: 멈춤 / 이후: 버퍼 비우고 계속 |
| 3 | 화면 잔상 제거 | 이전 오류 메시지가 화면에 남아 지저분해지던 문제를 `clear_line()` 함수로 해결 | 이전: 글자가 겹침 / 이후: 깔끔 |
| 4 | win 변수 초기화 | 초기화하지 않은 `win` 변수가 쓰레기 값을 가지는 문제를 `int win = 0;`으로 해결 | 이전: 불안정한 결과 / 이후: 안정적 |
| 5 | 결과 위치 고정과 창 바로 닫힘 해결 | 결과 메시지가 아무 위치나 출력되고 창이 바로 닫혀 결과를 못 보던 문제를 `gotoxy`와 `press_any_key()`로 해결 | 이전: 어디로 가는지 모름 / 이후: 고정 위치에 표시 |
| 6 | Visual Studio 컴파일 오류 해결 | `scanf` 오류와 `getch` 지원 불가 문제를 `_CRT_SECURE_NO_WARNINGS`와 `_getch`로 해결 | 이전: 오류 메시지 폭탄 / 이후: 컴파일 성공 |
| 7 | goto 제거 | 읽기 어려운 `goto` 문법을 `do-while`과 중복 검사 함수로 변경 | 이전: 화살표 엉망 / 이후: 선형적 흐름 |
| 8 | 매직 넘버 상수화 | 코드에 박힌 100, 10 같은 숫자를 `#define`으로 정의해서 의도를 명확하게 | 이전: 숫자 흩어짐 / 이후: 상수로 통일 |

---

## 🔵 PHASE 2: 화면과 연출 (9~22)

| # | 슬라이드 제목 | PPT 한 줄 요약 | 시각화 팁 |
|---|---|---|---|
| 9 | 콘솔 창 설정 | 창의 제목을 게임 이름으로, 크기를 80×32로 고정해서 모든 컴퓨터에서 동일한 화면 유지 | 이전: 기본 설정 / 이후: "100을 넘어라" 제목, 고정 크기 |
| 10 | 커서 숨기기 | 깜빡이는 커서를 `SetConsoleCursorInfo()`로 숨겨서 화면을 깔끔하게 | 이전: 커서 보임 / 이후: 커서 없음 |
| 11 | 색상 시스템 | 컴퓨터는 빨강, 사용자는 파랑, 경고는 노랑으로 색상을 구분해서 게임의 의도를 명확하게 | 이전: 흰색만 / 이후: 다채로움 |
| 12 | 1초 로고 화면 | ASCII 아트 "100" 로고, 로딩 바, 효과음으로 게임의 첫 인상을 전문적으로 | 이전: 바로 설명화면 / 이후: 로고 → 설명 |
| 13 | 방향키 메인 메뉴 | 6개 메뉴(새 게임/이어하기/방법/전적/소리/종료)를 ↑↓로 선택할 수 있게 | 이전: 바로 게임시작 / 이후: 메뉴 선택 가능 |
| 14 | 게임 방법 화면 개편 | 기본 규칙과 아이템 설명을 2페이지로 구성해서 사용자가 게임을 이해할 수 있게 | 이전: 1페이지 / 이후: 2페이지 상세 설명 |
| 15 | 카드 모양 UI | 1~10 숫자를 상자 모양 카드로 표현, 사용한 카드는 회색, 봉인 카드는 보라색으로 표시 | 이전: 텍스트만 / 이후: 카드 게임처럼 |
| 16 | 방향키로 카드 선택 | `scanf`를 제거하고 ←→ 방향키로 카드를 선택해서 입력 오류를 완전히 제거 | 이전: 숫자 입력 / 이후: 방향키 선택 |
| 17 | 합계 게이지 바 | 합계를 0~100 범위의 게이지 바로 표시, 70이상은 노랑, 90이상은 빨강으로 위험도 시각화 | 이전: 숫자만 / 이후: 프로그레스 바 |
| 18 | 화면 깜빡임 줄이기 | 카드 선택 시 손패 영역만 갱신해서 전체 화면을 지우지 않아 깜빡거림 제거 | 이전: 전체 화면 깜빡 / 이후: 부분 갱신 |
| 19 | 합계 카운트업 애니메이션 | 합계가 1씩 증가하는 애니메이션 + 효과음으로 점수 변화를 명확하게 | 이전: 한 번에 표시 / 이후: 천천히 증가 |
| 20 | 컴퓨터 생각 중 연출 | "컴퓨터가 생각 중..." 표시 + 점 애니메이션으로 컴퓨터가 "생각"하는 듯한 느낌 | 이전: 즉시 반환 / 이후: 생각 표시 |
| 21 | 게임 기록(로그) 창 | 최근 5개의 행동(카드, 합계)을 로그로 표시해서 게임 진행을 추적 가능하게 | 이전: 로그 없음 / 이후: 최근 5턴 표시 |
| 22 | 효과음과 소리 ON/OFF | 이동/선택/오류/아이템/승패 멜로디를 다르게 설정, 메뉴에서 ON/OFF 토글 가능 | 이전: 무음 / 이후: 효과음 가득 |

---

## 🟣 PHASE 3: 게임 시스템 (23~26)

| # | 슬라이드 제목 | PPT 한 줄 요약 | 시각화 팁 |
|---|---|---|---|
| 23 | 난이도 3단계 AI | 쉬움(무작위), 보통(이길 수 있으면 이김), 어려움(미니맥스 알고리즘)으로 난이도 조정 | 이전: 항상 무작위 / 이후: 3단계 AI |
| 24 | 동전 던지기로 선공 정하기 | 게임 시작 전 사용자가 앞/뒷을 선택해서 선공을 결정, 항상 컴퓨터 먼저 하던 불공평 해결 | 이전: 항상 컴퓨터 먼저 / 이후: 동전 던지기 |
| 25 | 제한 시간 20초 | 카드 선택 시 20초 제한, 5초 이하면 빨강+경고음, 초과하면 무작위 선택 | 이전: 무한정 대기 / 이후: 긴장감 UP |
| 26 | 숫자 카드 리필 규칙 | 10개 숫자를 다 쓰면 자동으로 리필해서 게임이 항상 끝까지 진행 | 이전: 카드 떨어질 수 있음 / 이후: 항상 승부 결정 |

---

## 🟢 PHASE 4: 아이템 카드 배틀 (27~33)

| # | 슬라이드 제목 | PPT 한 줄 요약 | 시각화 팁 |
|---|---|---|---|
| 27 | 아이템 시스템 도입 | 각 플레이어가 슬롯 3칸, 시작 2개 아이템으로 전략 추가 | 이전: 숫자만 / 이후: 아이템 슬롯 3칸 |
| 28 | 더블 x2 | 현재 턴의 카드 값을 2배로 증가시키는 공격 아이템 | 이전: 아이템 없음 / 이후: 2배 가능 |
| 29 | 합계 -10 | 현재 합계를 10 줄이는 방어 아이템, 상대 승리를 지연시킬 수 있음 | 이전: 방어 불가 / 이후: 합계 감소 |
| 30 | 턴 스킵 | 상대의 턴을 건너뛰고 자신이 연속 2턴을 하는 아이템 | 이전: 항상 교대 / 이후: 턴 건너뛰기 가능 |
| 31 | 봉인 | 상대의 가장 큰 카드를 1턴 동안 못 쓰게 하는 전술 아이템 | 이전: 상대 전략 막을 수 없음 / 이후: 카드 봉인 |
| 32 | 보너스 아이템 지급 | 4턴마다 각 플레이어에게 무작위 아이템 1개씩 지급 | 이전: 시작 2개만 / 이후: 4턴마다 +1 |
| 33 | AI 아이템 전략 | 컴퓨터가 난이도별로 아이템을 전략적으로 사용 (쉬움: 안 씀, 보통: 이길 때만, 어려움: 공격/방어 조합) | 이전: AI 아이템 사용 안 함 / 이후: 지능형 사용 |

---

## ⚫ PHASE 5: 저장/불러오기 (34~38)

| # | 슬라이드 제목 | PPT 한 줄 요약 | 시각화 팁 |
|---|---|---|---|
| 34 | 게임 저장 | 게임 중 S 키를 누르면 현재 상태를 `save.dat` 파일에 저장 | 이전: 저장 불가 / 이후: `save.dat` 생성 |
| 35 | 이어하기(불러오기) | 메인 메뉴의 "이어하기"로 저장된 게임을 복구, 파일 손상 검사 포함 | 이전: 불러오기 불가 / 이후: 저장 상태 복구 |
| 36 | 전적 기록 저장과 보기 | 게임 결과를 `record.txt`에 저장, 승률 계산해서 표시 | 이전: 기록 없음 / 이후: 전적 추적 |
| 37 | 엔딩 화면 | 승패에 따라 "YOU WIN" 또는 "YOU LOSE" 큰 글자 표시, 결과 통계 + 멜로디 | 이전: 텍스트 결과만 / 이후: 화려한 엔딩 |
| 38 | 일시정지와 다시 하기 | ESC로 게임을 일시정지, 계속/메뉴/종료 선택 가능 | 이전: 일시정지 불가 / 이후: ESC로 중단 |

