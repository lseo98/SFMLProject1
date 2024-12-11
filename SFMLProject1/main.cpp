// Script 출력 코드
// main 코드 전체로 업로드

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Stage.h"
#include <vector>
#include <iostream>
#include <string>
#include <Windows.h>
#include "Game.h"
#include <ctime> // time() 함수 사용
#pragma comment(lib, "user32.lib")
int WINDOWWIDTH = 1800;    // 맵 너비
int WINDOWHEIGHT = 900;    // 맵 높이
// 콘솔 화면을 지우는 함수
void clearConsole() {
    system("cls"); // Windows 전용
    // ANSI 표준 사용 시: std::cout << "\033[2J\033[1;1H";
}

void waitForEnter() {
    while (true) {
        if (GetAsyncKeyState(VK_RETURN) & 0x8000) { // 엔터 키 확인
            break;
        }
    }
}

void printScript(const std::string& script) {
    std::string separator = " ";
    int curPosition = 0;
    int position;

    clearConsole(); // 콘솔 화면 초기화
    std::cout << "\t\t\t\t\t\t\t\t\t\t\t\tEnter 키를 입력하여 계속" << std::endl;
    for(int i= 1;i<=7;i++)
        std::cout<< "" << std::endl;

    while ((position = script.find(separator, curPosition)) != std::string::npos) {
        int len = position - curPosition;

        // 현재 단어 출력
        std::string result = script.substr(curPosition, len);
        std::cout << result << " ";

        Sleep(100); // 0.1초 대기
        curPosition = position + 1;
    }

    // 마지막 단어 출력
    std::string result = script.substr(curPosition);
    std::cout << result << std::endl;

    // 엔터 입력 대기
    waitForEnter();
}
void printTutorialScript(std::string script) {
    std::string seperator = " ";
    int curPosition = 0;
    int position;

    while ((position = script.find(seperator, curPosition)) != std::string::npos) {
        int len = position - curPosition;
        if (GetAsyncKeyState(VK_RETURN)) {
            std::string result = script.substr(curPosition);
            std::cout << result << std::endl << std::endl;
            Sleep(1000);
            return;
        }
        std::string result = script.substr(curPosition, len);
        std::cout << result << " ";
        Sleep(100);
        curPosition = position + 1;
    }

    std::string result = script.substr(curPosition);
    std::cout << result << std::endl << std::endl;

    if (GetAsyncKeyState(VK_RETURN)) {
        return;
    }
    Sleep(1000);
}


void beforeGameScript() {
    printScript("project 1984 시작");
    printScript("1984년, 전 세계는 단 하나의 제국 아래 굴복했고, <민족사회당>은 모든 진실과 기억, 감정을 조작하며 인류를 옥죄고 있다.\n그러나 이런 폭압적 질서 속에서도, 수많은 인종과 사상을 초월한 무장 해방 단체 <민주해방전선>은 오직 세계 해방이라는 단 하나의 신념으로 결집했다.\n내가 바로 이 민주해방전선의 야전 지휘관이자 상징적 리더였다.\n수많은 전투를 승리로 이끌어냈고, 사람들에게 자유에 대한 희망을 불어넣었다.\n");
    printScript("하지만 그 희망도 잠시, 내부에 잠복한 제국의 첩자가 우리의 전방 기지를 노출시켰고, 나는 제국 정보부 특수군의 기습에 결국 생포되었다.\n이제 제국은 나를 공개 처형함으로써 전 세계에 저항이 무의미하다는 공포를 심으려 한다.\n한껏 어두운 감옥 속에 갇힌 지금, 제국의 눈길은 내 모든 숨결, 생각까지 감시한다.\n");
    system("cls");
    printTutorialScript(" < 튜 토 리 얼 >");
    printTutorialScript("WASD           : 상하좌우 이동 - 하늘, 바다 스테이지");
    printTutorialScript("AD             : 좌우 이동 - 땅 스테이지");
    printTutorialScript("좌우 방향키    : 특수 공격 발사체 방향 조작");
    printTutorialScript("Q              : 스테이지 별 필살기, 쿨타임 30초");
    printTutorialScript("E              : 스테이지 별 특수 공격, 쿨타임 2초 (일반 유닛 10마리 처치 시 3초간 쿨타임 0.2초)");
    printTutorialScript("스테이지 이동  : 좌측 명령창에 [skymap], [seamap], [landmap] 중 원하는 스테이지를 입력  ");
    printTutorialScript("숫자 키        : 미니게임 진행 중 목표 키 입력");
    printTutorialScript("정신력 수치는 적의 공격에 피격당할 때마다 1씩 감소하며, 정신력 수치가 0이 되면 간수에게 끌려가 심문 미니게임에 돌입. 심문 미니게임을 클리어 시 다시 스테이지로 복귀하며, 클리어하지 못할 시 즉결 처형되니 주의하기 바란다.");
    printTutorialScript("미니게임은 시도 횟수가 늘어날수록 난이도가 증가하니 최대한 미니게임에 진입하는 상황을 줄이는 방향으로 노력하도록.");
    printTutorialScript("스테이지마다 정해진 수의 정예 유닛을 처치해야 일반 스테이지가 최종적으로 클리어되며, 보스를 처치하여 세계를 구할 기회가 주어진다.");
    printTutorialScript("정해진 시간마다, 다른 스테이지에서 지휘 요청이 들어와 자동으로 시점이 전환된다.");
    printTutorialScript("보스는 일반적이지 않은 패턴을 가지고 있으니 조심하여 꼭 세상을 구하길 바란다.");
    printTutorialScript("Enter 키를 입력하여 작전개시");
    waitForEnter();

    system("cls");
}

void badEndingScript() {
    printScript("나는 지금 철제 의자에 묶여 있다.\n제국 정보부의 지하 처형실은 차가운 금속과 화학 냄새로 가득 차 있다.\n총통을 상징하는 포스터가 벽에서 나를 내려다보고, 민족사회당의 문양이 박힌 무기들이 정렬되어 있다.\n모든 것이 정돈되어 있고, 내가 이방인처럼 낯설다.\n감각은 반쯤 마비되었고, BIOCOMMANDER-II는 오래전부터 신호를 보내지 못한다.\n아군은 패했다.\n마지막 교신은 소음 속에 묻혔고, 전선은 무너졌다.");
    printScript("처형장은 기계적인 절차만 남았다.\n확성기에서 관리의 건조한 목소리가 죄목을 낭독한다.\n“민주해방전선의 야전 지휘관, 세계 질서에 반하는 자, 반역자.”\n목소리가 철창을 타고 울리는 동안, 나는 몸부림칠 수 없다.\n손목과 발목은 금속 고정대에 묶였고, 목덜미를 감은 강철 밧줄이 고개를 들지 못하게 한다.");
    printScript("7일의 마지막 기회는 허무하게 흘렀다.\n아군 구출과 정보부 파괴 계획은 실패했고, 병사들은 전사했다.\nBIOCOMMANDER-II의 존재도 들통났을지 모른다.\n나는 더 이상 저항의 상징이 아니다.\n이제 그들은 나의 처형을 통해 저항이 무의미하다는 메시지를 전할 것이다.");
    printScript("왼편에서 레버가 당겨진다.\n쇳소리가 귀를 찢고, 형광등이 번쩍인다.\n제국군 장교가 미소 짓는 모습이 보이고, 나는 눈을 감는다.\n몇 초 뒤, 날카로운 충격이 온몸을 파고든다.\n모든 감각이 끊어지고, 어둠이 밀려온다.\n");
    printScript("철권 통치의 심장부 한가운데서, 나는 그렇게 사라진다.\n제국의 질서는 이어지고, 세계는 다시 총통의 얼굴 아래 숨죽인다.\n내 마지막 순간은 그들이 원하던 그림 그대로다.");
    printScript("Game Over");
}
void goodEndingScript() {
    printScript("나는 이제 감옥 벽을 등지고 서 있다.\n갓 부순 철문 틈으로 쏟아져 들어오는 외기가 차갑지만 상쾌하다.\n정보부 본부의 심장부를 파괴하며, 제국의 상징적 경계이자 최후의 방어선이었던 열차포 Der Kaiser가 마침내 침묵했다.\n병사들의 함성이 먼 곳에서 메아리치고, 검은 연기와 불길 사이를 뚫고 뛰쳐나온 나의 동료들이 뿌연 황혼을 가르며 달려온다.\n");
    printScript("언젠가 이 감옥에서 숨조차 제대로 쉬지 못하던 내가, 지금은 해방전선의 전사들과 어깨를 나란히 하고 있다.\nBIOCOMMANDER-II를 통해 고통스럽게 지휘해온 지난 7일의 기억이 머릿속을 스친다.\n시간과 체력, 그리고 정신력까지 희박한 상황에서도 우리가 이룬 승리다.\n제국 정보부는 무너졌고, 사상과 언어를 억압하던 완고한 기계장치가 마침내 멈추었다.\n");
    printScript("적의 지도부를 상징하는 마지막 장교인 총통이 쓰러질 때, 그의 눈빛은 공포와 불신으로 뒤섞여 있었다.\n우리가 이루어낸 것은 단순한 군사적 승리를 넘어, 총통의 절대 명령 아래 움직이던 세계를 흔드는 신호다.\n불길이 잠잠해지면, 우리는 자유를 향한 길을 다시 놓을 것이다.\n모여드는 해방전선 병사들의 눈빛은 이제 희망으로 가득 차 있다.\n모든 인종, 언어, 사상을 초월해 '인간다운 삶'을 되찾으려는 의지가 이 순간에 불타고 있다.\n");
    printScript("나는 조용히 BIOCOMMANDER-II를 만지작거린다.\n그 장치는 더 이상 절박한 구조 신호를 내보낼 필요가 없다.\n마침내 이 어두운 감옥 속에서 나오게 되었고, 금속 냄새가 진동하던 처형장의 공포도 지나간 일이다.\n나의 포로 신분은 끝났다.\n긴장에 떨던 동료들이 나를 향해 환호를 보내고, 서로 부축하며 앞으로 걸어나간다.\n");
    printScript("바깥 하늘은 이전보다 맑은 듯하다.\n제국이 조작한 진실과 언어가 더 이상 세계를 옥죌 수 없게 되었음을, 우리는 온몸으로 느끼고 있다.\n이제 신념과 투쟁, 희생을 통해 쟁취한 이 순간을 발판삼아, 새로운 질서를 세울 것이다.\n자유, 진실, 인간성이 살아숨쉬는 세계를 향해.\n");
    printScript("나는 굳게 주먹을 쥐고 걸음을 뗀다.\n뒤를 돌아볼 필요가 없다.\n이제 시작이다.\n우리의 해방은 이뤄졌다.");
}



int main() {

    srand(static_cast<unsigned>(time(0))); // 난수 생성기의 seed를 현재 시간으로 설정
    sf::Event event;

    beforeGameScript();

    Game game;
    bool goodEnding = game.run();
    if (goodEnding) goodEndingScript();
    else  badEndingScript();

    return 0;
}
